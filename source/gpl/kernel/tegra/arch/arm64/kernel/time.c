/*
 * Based on arch/arm/kernel/time.c
 *
 * Copyright (C) 1991, 1992, 1995  Linus Torvalds
 * Modifications for ARM (C) 1994-2001 Russell King
 * Copyright (C) 2012 ARM Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <linux/export.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/time.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/smp.h>
#include <linux/timex.h>
#include <linux/errno.h>
#include <linux/profile.h>
#include <linux/syscore_ops.h>
#include <linux/timer.h>
#include <linux/irq.h>
#include <linux/delay.h>
#include <linux/clocksource.h>

#include <clocksource/arm_arch_timer.h>

#include <asm/thread_info.h>
#include <asm/stacktrace.h>

#include <asm/mach/arch.h>
#include <asm/mach/time.h>

#ifdef CONFIG_SMP
unsigned long profile_pc(struct pt_regs *regs)
{
	struct stackframe frame;

	if (!in_lock_functions(regs->pc))
		return regs->pc;

	frame.fp = regs->regs[29];
	frame.sp = regs->sp;
	frame.pc = regs->pc;
	do {
		int ret = unwind_frame(&frame);
		if (ret < 0)
			return 0;
	} while (in_lock_functions(frame.pc));

	return frame.pc;
}
EXPORT_SYMBOL(profile_pc);
#endif

#ifndef CONFIG_ARM64
static u64 sched_clock_mult __read_mostly;
#endif

static void dummy_clock_access(struct timespec *ts)
{
	ts->tv_sec = 0;
	ts->tv_nsec = 0;
}

static clock_access_fn __read_persistent_clock = dummy_clock_access;
static clock_access_fn __read_boot_clock = dummy_clock_access;

void read_persistent_clock(struct timespec *ts)
{
	__read_persistent_clock(ts);
}

int __init register_persistent_clock(clock_access_fn read_boot,
				     clock_access_fn read_persistent)
{
	/* Only allow the clockaccess functions to be registered once */
	if (__read_persistent_clock == dummy_clock_access &&
	    __read_boot_clock == dummy_clock_access) {
		if (read_boot)
			__read_boot_clock = read_boot;
		if (read_persistent)
			__read_persistent_clock = read_persistent;

		return 0;
	}

	return -EINVAL;
}

int read_current_timer(unsigned long *timer_value)
{
	*timer_value = arch_timer_read_counter();
	return 0;
}

void __init time_init(void)
{
	u32 arch_timer_rate;

	clocksource_of_init();

	arch_timer_rate = arch_timer_get_rate();
	if (!arch_timer_rate)
		panic("Unable to initialise architected timer.\n");

	/* Calibrate the delay loop directly */
	lpj_fine = arch_timer_rate / HZ;
}
