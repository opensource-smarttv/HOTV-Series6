/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*- */
/* gphoto2-port-usb.c
 *
 * Copyright (c) 2001 Lutz M?ller <lutz@users.sf.net>
 * Copyright (c) 1999-2000 Johannes Erdfelt <johannes@erdfelt.com>
 * Copyright (c) 2005, 2007 Hubert Figuiere <hub@figuiere.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details. 
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "config.h"
#include <gphoto2/gphoto2-port-library.h>

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#ifdef HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif
#include <dirent.h>
#include <string.h>
#ifdef HAVE_MNTENT_H
# include <mntent.h>
#endif
#ifdef HAVE_SYS_MNTENT_H
# include <sys/mntent.h>
#endif
#ifdef HAVE_SYS_MNTTAB_H
# include <sys/mnttab.h>
#endif

/* on Solaris */
#ifndef HAVE_SETMNTENT
#define setmntent(f,m) fopen(f,m)
#endif
#ifndef HAVE_ENDMNTENT
#define endmntent(f) fclose(f)
#endif

#ifdef HAVE_HAL
#include <hal/libhal.h>
#endif

#include <gphoto2/gphoto2-port.h>
#include <gphoto2/gphoto2-port-result.h>
#include <gphoto2/gphoto2-port-log.h>

#ifdef ENABLE_NLS
#  include <libintl.h>
#  undef _
#  define _(String) dgettext (GETTEXT_PACKAGE, String)
#  ifdef gettext_noop
#    define N_(String) gettext_noop (String)
#  else
#    define N_(String) (String)
#  endif
#else
#  define textdomain(String) (String)
#  define gettext(String) (String)
#  define dgettext(Domain,Message) (Message)
#  define dcgettext(Domain,Message,Type) (Message)
#  define bindtextdomain(Domain,Directory) (Domain)
#  define _(String) (String)
#  define N_(String) (String)
#endif

#define CHECK(result) {int r=(result); if (r<0) return (r);}

struct _GPPortPrivateLibrary {
	char *mount_point;
};

GPPortType
gp_port_library_type (void)
{
        return GP_PORT_DISK;
}

int
gp_port_library_list (GPPortInfoList *list)
{
	GPPortInfo info;
#ifdef HAVE_HAL
        LibHalContext *ctx;
        DBusError error;
        DBusConnection *dbus_connection;
        int i;
        int num_volumes;
        char **volumes;
        char *udi;

        ctx = libhal_ctx_new ();
        if (!ctx) {
		gp_log(GP_LOG_DEBUG, "gphoto2-port/disk", 
		       "failed to initialize HAL!\n");
                goto generic;
        }
        dbus_error_init (&error);

        dbus_connection = dbus_bus_get (DBUS_BUS_SYSTEM, &error);

        if (dbus_error_is_set (&error)) {
		gp_log (GP_LOG_DEBUG, "gphoto2-port/disk", 
			"hal_initialize failed: %s", 
			error.message);
		dbus_error_free (&error);
		libhal_ctx_free(ctx);
                goto generic;
        }

        libhal_ctx_set_dbus_connection (ctx, dbus_connection);

        dbus_error_init (&error);
        volumes = libhal_find_device_by_capability (ctx, "volume",
                                                    &num_volumes, &error);
        if (volumes == NULL) {
		if (dbus_error_is_set (&error)) {
			gp_log (GP_LOG_DEBUG, "gphoto2-port/disk", 
				"libhal: %s", 
				error.message);
			dbus_error_free (&error);
		}
                goto generic;
        }

	gp_log(GP_LOG_DEBUG, "gphoto2-port/disk", "found %d volumes", 
	       num_volumes); 
        for (i = 0; i < num_volumes; i++) {
                udi = volumes [i];
		
                /* don't attempt to mount already mounted volumes */
                if (!libhal_device_property_exists (ctx, udi,
                                                    "volume.is_mounted",
                                                    NULL) ||
                    libhal_device_get_property_bool (ctx, udi,
                                                     "volume.is_mounted",
                                                     NULL)) 
		{
			char *mountpoint = NULL;
			char *mediainfo = NULL;

			if (!libhal_device_property_exists (ctx, udi,
							   "volume.mount_point",
							    NULL)) {
				continue;
			}
 			mountpoint = libhal_device_get_property_string(ctx, udi,
								       "volume.mount_point",
								       &error);
			if (mountpoint == NULL) {
				if (dbus_error_is_set (&error)) {
					gp_log (GP_LOG_DEBUG, 
						"gphoto2-port/disk",
						"libhal: %s", error.message);
					dbus_error_free (&error);
				}
				continue;
			}
			mediainfo = libhal_device_get_property_string(ctx, udi,
								       "info.product",
								       &error);
			info.type = GP_PORT_DISK;
			snprintf (info.name, sizeof(info.name), _("Media '%s'"), 
				  (mediainfo?mediainfo:_("(unknown)")));
			snprintf (info.path, sizeof(info.path), "disk:%s",
				  mountpoint);
			CHECK (gp_port_info_list_append (list, info));
			libhal_free_string(mountpoint);
			if (mediainfo) {
				libhal_free_string(mediainfo);
			}
		}
		
        }

	libhal_free_string_array (volumes);
	libhal_ctx_free (ctx);
	dbus_connection_unref (dbus_connection);
#else
# ifdef HAVE_MNTENT_H
	FILE *mnt;
	struct mntent *mntent;
	char	path[1024];
	struct stat stbuf;

	info.type = GP_PORT_DISK;

	mnt = setmntent ("/etc/fstab", "r");
	if (mnt) {
		while ((mntent = getmntent (mnt))) {
			/* detect floppies so we don't access them with the stat() below */
			gp_log(GP_LOG_DEBUG, "gphoto2-port/disk",
			       "found fstab fsname %s", mntent->mnt_fsname);

			if ((NULL != strstr(mntent->mnt_fsname,"fd"))	||
			    (NULL != strstr(mntent->mnt_fsname,"floppy")) ||
			    (NULL != strstr(mntent->mnt_fsname,"fuse"))	||
			    (NULL != strstr(mntent->mnt_fsname,"nfs"))	||
			    (NULL != strstr(mntent->mnt_fsname,"cifs"))	||
			    (NULL != strstr(mntent->mnt_fsname,"smbfs"))||
			    (NULL != strstr(mntent->mnt_fsname,"afs"))	||
			    (NULL != strstr(mntent->mnt_fsname,"autofs"))||
			    (NULL != strstr(mntent->mnt_fsname,"gphotofs"))
			) {
				continue;
			}
			snprintf (path, sizeof(path), "%s/DCIM", mntent->mnt_dir);
			if (-1 == stat(path, &stbuf)) {
				snprintf (path, sizeof(path), "%s/dcim", mntent->mnt_dir);
				if (-1 == stat(path, &stbuf))
					continue;
			}
			snprintf (info.name, sizeof(info.name), _("Media '%s'"), mntent->mnt_fsname),
			snprintf (info.path, sizeof(info.path), "disk:%s", mntent->mnt_dir);
			if (gp_port_info_list_lookup_path (list, info.path) >= GP_OK)
				continue;
			CHECK (gp_port_info_list_append (list, info));
		}
		endmntent(mnt);
	}
	mnt = setmntent ("/etc/mtab", "r");
	if (mnt) {
		while ((mntent = getmntent (mnt))) {
			/* detect floppies so we don't access them with the stat() below */
			gp_log(GP_LOG_DEBUG, "gphoto2-port/disk",
			       "found mtab fsname %s", mntent->mnt_fsname);

			if ((NULL != strstr(mntent->mnt_fsname,"fd"))	||
			    (NULL != strstr(mntent->mnt_fsname,"floppy")) ||
			    (NULL != strstr(mntent->mnt_fsname,"fuse"))	||
			    (NULL != strstr(mntent->mnt_fsname,"nfs"))	||
			    (NULL != strstr(mntent->mnt_fsname,"smbfs"))||
			    (NULL != strstr(mntent->mnt_fsname,"afs"))	||
			    (NULL != strstr(mntent->mnt_fsname,"autofs"))||
			    (NULL != strstr(mntent->mnt_fsname,"gphotofs"))
			) {
				continue;
			}

			snprintf (path, sizeof(path), "%s/DCIM", mntent->mnt_dir);
			if (-1 == stat(path, &stbuf)) {
				snprintf (path, sizeof(path), "%s/dcim", mntent->mnt_dir);
				if (-1 == stat(path, &stbuf))
					continue;
			}
			/* automount should be blacklist here, but we still need
			 * to look it up first otherwise the automounted camera
			 * won't appear.
			 */
			if (NULL != strstr(mntent->mnt_fsname, "automount")) {
				continue;
			}
			info.type = GP_PORT_DISK;
			snprintf (info.name, sizeof(info.name), _("Media '%s'"), mntent->mnt_fsname),
			snprintf (info.path, sizeof(info.path), "disk:%s", mntent->mnt_dir);
			if (gp_port_info_list_lookup_path (list, info.path) >= GP_OK)
				continue;
			CHECK (gp_port_info_list_append (list, info));
		}
		endmntent(mnt);
	}
# else
#  ifdef HAVE_MNTTAB
	FILE *mnt;
	struct mnttab mnttab;
	char	path[1024];
	struct stat stbuf;

	info.type = GP_PORT_DISK;

	mnt = fopen ("/etc/fstab", "r");
	if (mnt) {
		while (! getmntent (mnt, &mntent)) {
			/* detect floppies so we don't access them with the stat() below */
			if (	(NULL != strstr(mnttab.mnt_special,"fd")) ||
				(NULL != strstr(mnttab.mnt_special,"floppy"))
			)
				continue;

			snprintf (path, sizeof(path), "%s/DCIM", mnttab.mnt_mountp);
			if (-1 == stat(path, &stbuf)) {
				snprintf (path, sizeof(path), "%s/dcim", mnttab.mnt_mountp);
				if (-1 == stat(path, &stbuf))
					continue;
			}
			snprintf (info.name, sizeof(info.name), _("Media '%s'"), mntent.mnt_special),
			snprintf (info.path, sizeof(info.path), "disk:%s", mntent.mnt_mountp);
			if (gp_port_info_list_lookup_path (list, info.path) >= GP_OK)
				continue;
			CHECK (gp_port_info_list_append (list, info));
		}
		fclose(mnt);
	}
	mnt = fopen ("/etc/mtab", "r");
	if (mnt) {
		while (! getmntent (mnt, &mntent)) {
			/* detect floppies so we don't access them with the stat() below */
			if (	(NULL != strstr(mnttab.mnt_special,"fd")) ||
				(NULL != strstr(mnttab.mnt_special,"floppy"))
			)
				continue;

			snprintf (path, sizeof(path), "%s/DCIM", mnttab.mnt_mountp);
			if (-1 == stat(path, &stbuf)) {
				snprintf (path, sizeof(path), "%s/dcim", mnttab.mnt_mountp);
				if (-1 == stat(path, &stbuf))
					continue;
			}
			snprintf (info.name, sizeof(info.name), _("Media '%s'"), mntent.mnt_special),
			snprintf (info.path, sizeof(info.path), "disk:%s", mntent.mnt_mountp);
			if (gp_port_info_list_lookup_path (list, info.path) >= GP_OK)
				continue;
			CHECK (gp_port_info_list_append (list, info));
		}
		fclose(mnt);
	}
#  endif
# endif
#endif
generic:
	/* generic disk:/xxx/ matcher */
	info.type = GP_PORT_DISK;
	memset (info.name, 0, sizeof(info.name));
	snprintf (info.path, sizeof(info.path), "^disk:");
	CHECK (gp_port_info_list_append (list, info));
	return GP_OK;
}

static int gp_port_disk_init (GPPort *dev)
{
	dev->pl = malloc (sizeof (GPPortPrivateLibrary));
	if (!dev->pl) {
		return GP_ERROR_NO_MEMORY;
	}
	memset (dev->pl, 0, sizeof(GPPortPrivateLibrary));

	return GP_OK;
}

static int
gp_port_disk_exit (GPPort *port)
{
	if (port->pl) {
		free (port->pl);
		port->pl = NULL;
	}

	return GP_OK;
}

static int
gp_port_disk_open (GPPort *port)
{
	return GP_OK;
}

static int
gp_port_disk_close (GPPort *port)
{
	return GP_OK;
}

static int
gp_port_disk_write (GPPort *port, const char *bytes, int size)
{
        return GP_OK;
}

static int
gp_port_disk_read(GPPort *port, char *bytes, int size)
{
        return GP_OK;
}

GPPortOperations *
gp_port_library_operations (void)
{
	GPPortOperations *ops;

	ops = malloc (sizeof (GPPortOperations));
	if (!ops) {
		return NULL;
	}
	memset (ops, 0, sizeof (GPPortOperations));

	ops->init   = gp_port_disk_init;
	ops->exit   = gp_port_disk_exit;
	ops->open   = gp_port_disk_open;
	ops->close  = gp_port_disk_close;
	ops->read   = gp_port_disk_read;
	ops->write  = gp_port_disk_write;

	return ops;
}
