/******************************************************************
 *  $Id: formatter.c 254826 2013-01-10 12:29:18Z akosteltsev $
 *
 * CSOAP Project:  A SOAP client/server library in C
 * Copyright (C) 2003  Ferhat Ayaz
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA  02111-1307, USA.
 * 
 * Email: ayaz@jprogrammer.net
 ******************************************************************/
#include <string.h>

#include "formatter.h"
#include "tr.h"
#include "util.h"

int formatter_generate_sax_serializer = 0;

/* ------------------------------------------------------------- */

typedef void (*FieldEnumCallBack)(FILE* , HFIELD);
static void enumFields(FILE* f, HCOMPLEXTYPE obj, FieldEnumCallBack callb);

/* ------------------------------------------------------------- */

static int genFieldType(HFIELD field, char *buffer, int forceSingle);
static int genFunctionNameGetter(HFIELD field, char *buffer);
static int genFunctionNameSetter(HFIELD field, char *buffer);
static int genFunctionNameAdder(HFIELD field, char *buffer);
static int genFunctionNameCreate(HCOMPLEXTYPE obj, char *buffer);
static int genFunctionNameFree(HCOMPLEXTYPE obj, char *buffer);
static int genFunctionNameSaxSerialize(HCOMPLEXTYPE obj, char *buffer);
static int genFunctionNameDeserialize(HCOMPLEXTYPE obj, char *buffer);
#if 0
static int genFunctionNameSimpleMinMaxSetter(HCOMPLEXTYPE obj, char *buffer);
#endif
/* ------------------------------------------------------------- */

static void writeFieldDeclare(FILE* f, HFIELD field);
static void writeComplexTypeDeclare(FILE* f, HCOMPLEXTYPE obj);
static void writeFieldPrimitiveList(FILE* f, HFIELD field);
static void writeFieldSetter(FILE* f, HFIELD field);
static void writeFieldGetter(FILE* f, HFIELD field);
static void writeListAdder(FILE* f, HFIELD field);

/* ------------------------------------------------------------- */

static void writeCodeCreate(FILE* f, HCOMPLEXTYPE obj);
static void writeCodeFree(FILE* f, HCOMPLEXTYPE obj);
static void writeCodeSaxSerialize(FILE* f, HCOMPLEXTYPE obj);
static void writeCodeBaseOnStartElement(FILE* f, HCOMPLEXTYPE obj);
static void writeCodeBaseOnEndElement(FILE* f, HCOMPLEXTYPE obj);
static void writeCodeDeserialize(FILE* f, HCOMPLEXTYPE obj);

static void writeCodeFieldInitialize(FILE* f, HFIELD field);
static void writeCodeFieldFreeList(FILE* f, HFIELD field);
static void writeCodeFieldFree(FILE* f, HFIELD field);
static void writeCodeGetter(FILE* f, HFIELD field);
static void writeCodeSetter(FILE* f, HFIELD field);
static void writeCodeAdder(FILE* f, HFIELD field);

/* ------------------------------------------------------------- */
static void writeSimpleMinMaxSetter(FILE* f, HCOMPLEXTYPE obj);
/* ------------------------------------------------------------- */

void writeComplexTypeHeaderFile(FILE* f, HCOMPLEXTYPE obj)
{
  HFIELD field;
  char buffer[1054];

	
  if (obj == NULL)
  {
    fprintf(stderr, "Can not declare a null object!\n");
    return;
  }

  fprintf(f, "/** Generated by xsd2c*/\n");
  fprintf(f, "#ifndef __%s_H__\n", obj->type);
  fprintf(f, "#define __%s_H__\n\n\n", obj->type);

  /* search for includes */
  field = obj->head;
  while (field != NULL)
  {
    if (trGetBuildInFlag(field->type) == 0) 
    {

      fprintf(f, "#include \"%s.h\"\n", trXSDParseNs(field->type)); /* _xsd*/
    }
    field = field->next;
  }

  if (obj->base_type != NULL) 
  {
    fprintf(f, "#include \"%s.h\"\n", trXSDParseNs(obj->base_type));/* _xsd*/
  }
  
  /* include libxml library */
  fprintf(f, "\n#ifndef _DESERIALIZER_DISABLE_\n");
  fprintf(f, "\t#include <libxml/parser.h>\n");
  fprintf(f, "#endif\n\n");
  
  /* write upcasting define macro */
  toUpperCase(obj->type, buffer);
  if (!obj->isSimpleContent && !obj->restriction)
   fprintf(f, "\n#define TO_%s(derived) (derived->__base) \n\n", buffer);

  /* write extern "C" for __cplusplus linking */
  fprintf(f, "\n#ifdef __cplusplus\nextern \"C\" {\n#endif \n\n");

   /* write primitive type list structs */
  enumFields(f, obj, writeFieldPrimitiveList);
  
  /* write object struct */
  writeComplexTypeDeclare(f, obj);


  /* write create function */
  if (genFunctionNameCreate(obj, buffer))
     fprintf(f, "%s;\n", buffer);

  /* write free function */
  if (genFunctionNameFree(obj, buffer))
     fprintf(f, "%s;\n", buffer);

  /* write sax serialize function */
  if (genFunctionNameSaxSerialize(obj, buffer))
     fprintf(f, "%s;\n", buffer);

  /* write derialize function */
  
  if (genFunctionNameDeserialize(obj, buffer)) {
    fprintf(f, "\n#ifndef _DESERIALIZER_DISABLE_\n");
    fprintf(f, "%s;\n", buffer);
    fprintf(f, "#endif\n\n");
  }

  if (obj->isSimpleContent && obj->restriction)
  {
    switch (obj->restriction->mode)
    {
      case RES_MODE_MINMAX:
        /* do nothing yet */
        break;
      case RES_MODE_ENUMERATION:
      break;
    }
  }
  else
  {
    /* write setter functions */
    enumFields(f, obj, writeFieldSetter);
  
    /* write adder functions */
    enumFields(f, obj, writeListAdder);
  
    /* write getter functions */
    enumFields(f, obj, writeFieldGetter);
  }

  /* write extern "C" for __cplusplus linking */
  fprintf(f, "\n\n#ifdef __cplusplus\n};\n#endif /*__cplusplus*/\n\n");

  fprintf(f, "\n\n#endif\n");
}



/* ------------------------------------------------------------- */

static
void writeComplexTypeDeclare(FILE* f, HCOMPLEXTYPE obj)
{
  HFIELD field;
  struct Enumeration_value_List *enumList;
  char *type;
  char buffer[250];
  char buffer2[250];
  if (obj == NULL)
  {
    fprintf(stderr, "Can not declare a null object!\n");
    return;
  }

  if (obj->isSimpleContent)
  {
    if (obj->restriction) {
        if (obj->restriction->mode == RES_MODE_ENUMERATION) {
          fprintf(f, "\ntypedef enum _enum_%s {\n", obj->type);
          enumList = Enumeration_Get_value(obj->restriction->enumeration);
          while(enumList) {
           toUpperCase(enumList->value, buffer);
           toUpperCase(obj->type, buffer2);
           fprintf(f, "\t%s_%s, /* Constant for \"%s\" */\n", buffer2, buffer, enumList->value);
           enumList = enumList->next;
          }

          fprintf(f, "}%s;\n", obj->type);

        }
        else {
          fprintf(f, "\n/** type definition for simple content element '%s' */\n", obj->type);
              fprintf(f, "typedef %s %s;\n\n", trXSD2C(obj->restriction->type), obj->type);

        }

        /* === Else List ======== */
        fprintf(f, "\n/**\n *\tLIST: %s_List\n */\n", obj->type);
        fprintf(f, "%s_List\n{\n", obj->type);
        fprintf(f, "\t%s value;\n", obj->type);
        fprintf(f, "\tstruct %s_List* next;\n", obj->type);
        fprintf(f, "};\n\n\n");
    } /* restriction */
  } /* isSimpleContent */
  else
  {  
    /* === */
    fprintf(f, "\n/**\n *\tOBJECT: %s\n */\n", obj->type);
    fprintf(f, "struct %s\n{\n", obj->type);
    
    /* === */
    if (obj->base_type != NULL) 
    {
      type = trXSD2C(obj->base_type);
      if (type != NULL) 
      {
        fprintf(f, "\t%s __base;\n", type);
      }
    }
  
    /* === */
    field = obj->head;
    while (field != NULL)
    {
      printf("%s::writeFieldDeclare(%s)\n", obj->type, field->type);
      writeFieldDeclare(f, field);
      field = field->next;
    }
    fprintf(f, "};\n");

    /* === */
    fprintf(f, "\n/**\n *\tLIST: %s_List\n */\n", obj->type);
    fprintf(f, "struct %s_List\n{\n", obj->type);
    fprintf(f, "\tstruct %s* value;\n", obj->type);
    fprintf(f, "\tstruct %s_List* next;\n", obj->type);
    fprintf(f, "};\n\n\n");
  } /* else of isSimpleContent */

  
}


/* -------------------------------------------------------------- */

static 
void writeFieldDeclare(FILE* f, HFIELD field)
{
  char buffer[1054];
  
  if (!genFieldType(field, buffer, 0)) return;
  
  
  if (field->maxOccurs > 1 || field->maxOccurs == -1)
  {
    printf("OBJ:%s FIELD: %s\n", field->parentObj->type, buffer);
    fprintf(f, "\t%s %s_head;\n", buffer, field->name);
    fprintf(f, "\t%s %s_tail;\n", buffer, field->name);
  }
  else
  {
    fprintf(f, "\t%s %s;\n", buffer, field->name);
  }
}

/* -------------------------------------------------------------- */

static 
int genFunctionNameCreate(HCOMPLEXTYPE obj, char *buffer)
{
  const char *funcname = "struct %s* %s_Create()";
  if (obj->isSimpleContent && obj->restriction) return 0;
  sprintf(buffer, funcname, obj->type, obj->type);
  return 1;
}

/* -------------------------------------------------------------- */

static 
int genFunctionNameFree(HCOMPLEXTYPE obj, char *buffer)
{
  const char *funcname = "void %s_Free(struct %s* obj)";
  if (obj->isSimpleContent && obj->restriction) return 0;
  sprintf(buffer, funcname, obj->type, obj->type);
  return 1;
}

/* -------------------------------------------------------------- */

static 
int genFieldType(HFIELD field, char *buffer, int forceSingle)
{
  char *type;
  const char* stlist = "struct %s_%s_List*";
  if ((field->maxOccurs > 1 || field->maxOccurs == -1) && !forceSingle)
  {
    type = trXSD2CList(field->type);
    if (type == NULL)
      sprintf(buffer, stlist, field->parentObj->type, field->name);
    else
      strcpy(buffer, type);
  }
  else
  {
    type = trXSD2C(field->type);
    if (type == NULL)
    {
      fprintf(stderr, "WARNING: Unregistered type '%s'\n", field->type);
      return 0;
    }
    strcpy(buffer, type);
  }

  return 1;
}

/* -------------------------------------------------------------- */

static int genFunctionNameGetter(HFIELD field, char *buffer)
{
  const char *funcname = "%s %s_Get_%s(struct %s* obj)";
  char type[1054];
  
  if (!genFieldType(field, type, 0)) return 0;

  sprintf(buffer, funcname, type, field->parentObj->type,
    field->name, field->parentObj->type);

  return 1;
}

/* -------------------------------------------------------------- */

static int genFunctionNameSetter(HFIELD field, char *buffer)
{
  const char *funcname = "void %s_Set_%s(struct %s* obj, %s %s)";
  char type[1054];

  if (!genFieldType(field, type, 0)) return 0;

  if (!strcmp(type, "char*")) 
    strcpy(type, "const char*");

  sprintf(buffer, funcname, field->parentObj->type, field->name, 
        field->parentObj->type, type, field->name);
 
  return 1;
}

/* -------------------------------------------------------------- */

static int genFunctionNameAdder(HFIELD field, char *buffer)
{
  const char *funcname = "void %s_Add_%s(struct %s* obj, %s %s)";
  char type[1054];

  if (!genFieldType(field, type, 1)) return 0;

  if (!strcmp(type, "char*")) 
    strcpy(type, "const char*");

  sprintf(buffer, funcname, field->parentObj->type, field->name, 
        field->parentObj->type, type, field->name);

  return 1;
}

/* -------------------------------------------------------------- */

static int genFunctionNameSaxSerialize(HCOMPLEXTYPE obj, char *buffer)
{
  const char *funcname = "void %s_Sax_Serialize(struct %s* obj,\n\t\t const char *root_element_name,\n\t\t %s,\n\t\t %s,\n\t\t %s,\n\t\t void* userData)";
  const char *funcnameSimple = "void %s_Sax_Serialize(%s obj,\n\t\t const char *root_element_name,\n\t\t %s,\n\t\t %s,\n\t\t %s,\n\t\t void* userData)";
  const char *start = "void (*OnStartElement)(const char* element_name, int attr_count, char **keys, char **values, void* userData)";
  const char *chars = "void (*OnCharacters)(const char* element_name, const char* chars, void* userData)";
  const char *end = "void (*OnEndElement)(const char* element_name, void* userData)";

  if (obj->isSimpleContent && obj->restriction) 
    sprintf(buffer, funcnameSimple, obj->type,  obj->type, start, chars, end);
  else
    sprintf(buffer, funcname, obj->type,  obj->type, start, chars, end);
  return 1;
}

/* -------------------------------------------------------------- */

static int genFunctionNameDeserialize(HCOMPLEXTYPE obj, char *buffer)
{
  const char *funcname = "struct %s* %s_Deserialize(xmlNodePtr xmlRoot)";
  const char *funcnameSimple = "%s %s_Deserialize(xmlNodePtr xmlRoot)";

  if (obj->isSimpleContent && obj->restriction) 
    sprintf(buffer, funcnameSimple, obj->type,  obj->type);
  else
    sprintf(buffer, funcname, obj->type,  obj->type);
  return 1;
}

/* -------------------------------------------------------------- */

static 
void writeFieldPrimitiveList(FILE* f, HFIELD field)
{
  char *type, buffer[1054];
  const char* stlist = "struct %s_%s_List";
  
  if (!(field->maxOccurs > 1 || field->maxOccurs == -1)) return;

  if (trGetBuildInFlag(field->type) > 0) 
  {
    type = trXSD2C(field->type);
    if (type == NULL) return;

    sprintf(buffer, stlist, field->parentObj->type, field->name);

    fprintf(f, "\n%s {\n", buffer);
    fprintf(f, "\t%s value;\n", type);
    fprintf(f, "\t%s* next;\n", buffer);
    fprintf(f, "};\n");
  }
}



/* -------------------------------------------------------------- */

static void writeFieldSetter(FILE* f, HFIELD field)
{
  char buffer[1054];

  if (field->maxOccurs != 1) return;

  if (!genFunctionNameSetter(field, buffer)) return;
  fprintf(f, "%s;\n", buffer);
}


/* -------------------------------------------------------------- */

static void writeFieldGetter(FILE* f, HFIELD field)
{
  char buffer[1054];

  if (!genFunctionNameGetter(field, buffer)) return;
  fprintf(f, "%s;\n", buffer);
}

/* -------------------------------------------------------------- */

static void writeListAdder(FILE* f, HFIELD field)
{
  char buffer[1054];

  if (!((field->maxOccurs > 1 || field->maxOccurs == -1))) return;
  
  if (!genFunctionNameAdder(field, buffer)) return;
  fprintf(f, "%s;\n", buffer);
}

/* -------------------------------------------------------------- */

static void enumFields(FILE* f, HCOMPLEXTYPE obj, FieldEnumCallBack callb)
{
  HFIELD field;
  if (obj == NULL)
  {
    fprintf(stderr, "Can not declare a null object!\n");
    return;
  }

  field = obj->head;
  while (field != NULL)
  {
    callb(f, field);
    field = field->next;
  }
}



/* ------------------------------------------------------------- */
/*   SOURCE FILE                                                 */
/* ------------------------------------------------------------- */

void writeComplexTypeSourceFile(FILE* f, HCOMPLEXTYPE obj)
{

  if (obj == NULL)
  {
    fprintf(stderr, "Can not declare a null object!\n");
    return;
  }

  fprintf(f, "/** Generated by xsd2c */\n");
  fprintf(f, "#include <stdio.h>\n");
  fprintf(f, "#include <string.h>\n");
  fprintf(f, "#include <stdlib.h>\n");
  fprintf(f, "#include \"%s.h\"\n\n\n", obj->type); /* _xsd*/


  if (obj->base_type != NULL)
  {
    fprintf(f, "\nstruct Base_Sax_%s_Serializer\n{\n\tstruct %s* obj;\n", obj->type, obj->type);
    fprintf(f, "\tvoid (*OnStartElement)(const char*,int,char**,char**, void*);\n");
    fprintf(f, "\tvoid (*OnCharacters)(const char*,const char*, void*);\n");
    fprintf(f, "\tvoid (*OnEndElement)(const char*, void*);\n");
    fprintf(f, "\tvoid* userData;\n\tint stackDeep;\n};\n\n");
  }

  /* write create function code */
  writeCodeCreate(f, obj);

  /* write free function code */
  writeCodeFree(f, obj);

  if (obj->base_type != NULL)
  {
    writeCodeBaseOnStartElement(f, obj);
    writeCodeBaseOnEndElement(f, obj);
  }

  /* write sax code */
  writeCodeSaxSerialize(f, obj);

  /* write deserializer code */
  writeCodeDeserialize(f, obj);

  /* write getters */
  enumFields(f, obj, writeCodeGetter);

  /* write setters */
  enumFields(f, obj, writeCodeSetter);

  /* write setters */
  enumFields(f, obj, writeCodeAdder);
}

/* ------------------------------------------------------------- */

static void writeCodeCreate(FILE* f, HCOMPLEXTYPE obj)
{
  char buffer[1054];

  if (!genFunctionNameCreate(obj, buffer)) return;

  fprintf(f, "%s\n", buffer);
  fprintf(f, "{\n");

  fprintf(f, "\tstruct %s* _res;\n", obj->type);
  fprintf(f, "\t_res = (struct %s*)malloc(sizeof(struct %s));\n\n", 
      obj->type, obj->type);

  if (obj->base_type != NULL) 
    fprintf(f, "\t_res->__base = %s_Create();\n\n", obj->base_type);

  enumFields(f, obj, writeCodeFieldInitialize);
  
  fprintf(f, "\n\treturn _res;\n");
  fprintf(f, "}\n\n");
}

/* ------------------------------------------------------------- */

static void writeCodeFieldInitialize(FILE* f, HFIELD field)
{
  char ns[255];
  char type[255];
  char defvalue[255];

  parseNS(field->type, ns, type);

  if (!strcmp(type, "int") || !strcmp(type, "integer") || !strcmp(type, "boolean"))
    strcpy(defvalue, "0");
  else if (!strcmp(type, "float") || !strcmp(type, "double"))
    strcpy(defvalue, "0.0");
  else if (!strcmp(type, "char"))
    strcpy(defvalue, "'\\0'");
  else
    strcpy(defvalue, "NULL");
  
  if (field->maxOccurs > 1 || field->maxOccurs == -1) 
  {
    fprintf(f, "\t_res->%s_head = NULL;\n",  field->name);
    fprintf(f, "\t_res->%s_tail = NULL;\n",  field->name);
  }
  else
    fprintf(f, "\t_res->%s = %s;\n",  field->name, defvalue);
}


/* ------------------------------------------------------------- */


static void writeCodeGetter(FILE* f, HFIELD field)
{
  char buffer[1054];

  if (!genFunctionNameGetter(field, buffer)) return;

  fprintf(f, "%s\n", buffer);
  fprintf(f, "{\n");
  if (field->maxOccurs > 1 || field->maxOccurs == -1) 
  {
    fprintf(f, "\treturn obj->%s_head;\n",  field->name);  }
  else
    fprintf(f, "\treturn obj->%s;\n",  field->name);
  
  fprintf(f, "}\n\n");

}


/* ------------------------------------------------------------- */


static void writeCodeSetter(FILE* f, HFIELD field)
{
  char buffer[1054];
  char ns[255];
  char type[255];
  char ctype[1054];

  if (field->maxOccurs > 1 || field->maxOccurs == -1) return;

  if (!genFunctionNameSetter(field, buffer)) return;


  fprintf(f, "%s\n", buffer);
  fprintf(f, "{\n");

  parseNS(field->type, ns, type); /* xsd type */
  if (!genFieldType(field, ctype, 0)) return; /* ctype */

  if (!strcmp(ctype, "char*"))
/*  if (!strcmp(type, "string") )  */ /* work aroud for IDREF and IDREFS*/
  {
    fprintf(f, "\tif (obj->%s != NULL) free(obj->%s);\n",
      field->name, field->name);
    fprintf(f, "\tobj->%s = (char*)malloc(strlen(%s)+1);\n", 
      field->name, field->name);
    fprintf(f, "\tstrcpy(obj->%s, %s);\n",
      field->name, field->name);
  }
  else
  {
    fprintf(f, "\tobj->%s = %s;\n", field->name, field->name);
  }
  
  fprintf(f, "}\n\n");
}

/* ------------------------------------------------------------- */

static void writeCodeAdder(FILE* f, HFIELD field)
{
  char buffer[1054];
  char ns[255];
  char type[255];
  char fieldType[1054];
  char fieldTypeNP[1054];

  if (!(field->maxOccurs > 1 || field->maxOccurs == -1)) return;

  if (!genFunctionNameAdder(field, buffer)) return;
  if (!genFieldType(field, fieldType, 0)) return ;
  
  strcpy(fieldTypeNP, fieldType);
  fieldTypeNP[strlen(fieldType)-1] = '\0';

  fprintf(f, "%s\n", buffer);
  fprintf(f, "{\n");

  fprintf(f, "\t%s %s_node;\n", fieldType, field->name);
  fprintf(f, "\t%s_node = (%s)malloc(sizeof(%s));\n", 
    field->name, fieldType, fieldTypeNP);

  parseNS(field->type, ns, type);
  
  if (!strcmp(type, "string")) 
  {
    fprintf(f, "\t%s_node->value = (char*)malloc(strlen(%s)+1);\n",
      field->name, field->name);
    fprintf(f, "\tstrcpy(%s_node->value, %s);\n",
      field->name, field->name);
  }
  else
  {
    fprintf(f, "\t%s_node->value = %s;\n", field->name, field->name);
  }

  fprintf(f, "\t%s_node->next = NULL;\n", field->name);
  fprintf(f, "\tif (obj->%s_tail)\n", field->name);
  fprintf(f, "\t{\n\t\tobj->%s_tail->next = %s_node;\n\t}\n",
    field->name, field->name);
  fprintf(f, "\tif (obj->%s_head == NULL)\n", field->name);
  fprintf(f, "\t{\n\t\tobj->%s_head = %s_node;\n\t}\n",
    field->name, field->name);
  fprintf(f, "\tobj->%s_tail = %s_node;\n",
    field->name, field->name);

  fprintf(f, "}\n\n");
}

/* ------------------------------------------------------------- */

static void writeCodeFree(FILE* f, HCOMPLEXTYPE obj)
{
  char buffer[1054];

  if (!genFunctionNameFree(obj, buffer)) return;

  fprintf(f, "%s\n", buffer);
  fprintf(f, "{\n");
  enumFields(f, obj, writeCodeFieldFreeList);
  fprintf(f, "\tif (obj == NULL) return;\n");

  enumFields(f, obj, writeCodeFieldFree);

  fprintf(f, "\tfree(obj);\n");

  fprintf(f, "}\n\n");
}

/* ------------------------------------------------------------- */

static void writeCodeFieldFreeList(FILE* f, HFIELD field)
{
  char buffer[1054];
  if (field->maxOccurs > 1 || field->maxOccurs == -1) 
  {
    genFieldType(field, buffer, 0);
    fprintf(f, "\t%s %s_cur;\n", buffer, field->name);
    fprintf(f, "\t%s %s_tmp;\n", buffer, field->name);
  }
}

/* ------------------------------------------------------------- */

static void writeCodeFieldFree(FILE* f, HFIELD field)
{
  char ns[255];
  char type[255];

  parseNS(field->type, ns, type);

  if (field->maxOccurs > 1 || field->maxOccurs == -1) 
  {
    fprintf(f, "\n\t%s_cur = obj->%s_head;\n", field->name, field->name);
    fprintf(f, "\twhile (%s_cur != NULL)\n\t{\n", field->name);
    if (!strcmp(type, "string"))
    {
      fprintf(f, "\t\tif (%s_cur->value) free(%s_cur->value);\n", 
        field->name, field->name);
    }
    fprintf(f, "\t\t%s_tmp = %s_cur->next;\n", field->name, field->name);
    fprintf(f, "\t\tfree(%s_cur);\n",  field->name);
    fprintf(f, "\t\t%s_cur = %s_tmp;\n", field->name, field->name);
    fprintf(f, "\t}\n");
  }
  else if (!strcmp(type, "int") || !strcmp(type, "integer") || !strcmp(type, "boolean")) 
  {
  }
  else if (!strcmp(type, "float") || !strcmp(type, "double"))
  {
  }
  else if (!strcmp(type, "char"))
  {
  }
  else if (!strcmp(type, "string"))
  {
    fprintf(f, "\tif (obj->%s != NULL) \n\t{\n\t\tfree(obj->%s);\n\t\tobj->%s = NULL;\n\t}\n",
      field->name, field->name, field->name);
  }
}


/* ------------------------------------------------------------- */

static void setSaxAttrs(FILE* f, HCOMPLEXTYPE obj)
{
   HFIELD field;
   fprintf(f, "\n\tattrCount = 0;\n");

    field = obj->head;
    while (field != NULL)
    {
      if (field->attrName != NULL) 
        fprintf(f, "\tif (obj->%s != NULL) attrCount++;\n", field->name); 
      field = field->next;
    }

    fprintf(f, "\n\tkeys = (char**)malloc(sizeof(char*)*attrCount);\n");
    fprintf(f, "\tvalues = (char**)malloc(sizeof(char*)*attrCount);\n");

    fprintf(f, "\n\tcurCount = 0;\n\n");

    field = obj->head;
    while (field != NULL)
    {
      if (field->attrName != NULL) 
      {
        fprintf(f, "\tif (obj->%s != NULL)\n\t{\n", field->name);
        fprintf(f, "\t\tkeys[curCount] = \"%s\";\n", field->attrName);
        fprintf(f, "\t\tvalues[curCount] = obj->%s;\n", field->name);
        fprintf(f, "\t\tcurCount++;\n\t}\n");
      }
      field = field->next;
    }
}

/* ------------------------------------------------------------- */

static void setSaxAttrsBase(FILE* f, HCOMPLEXTYPE obj)
{
   HFIELD field;

    field = obj->head;
    while (field != NULL)
    {
      if (field->attrName != NULL) 
        fprintf(f, "\tif (bsce->obj->%s != NULL) attrCount++;\n", field->name); 
      field = field->next;
    }

    fprintf(f, "\n\tkeys = (char**)realloc(keys, sizeof(char*)*(attrCount + attr_count));\n");
    fprintf(f, "\tvalues = (char**)realloc(values, sizeof(char*)*(attrCount + attr_count));\n");

    fprintf(f, "\n\tcurCount = 0;\n\n");

    field = obj->head;
    while (field != NULL)
    {
      if (field->attrName != NULL) 
      {
        fprintf(f, "\tif (bsce->obj->%s != NULL)\n\t{\n", field->name);
        fprintf(f, "\t\tkeys[curCount + attr_count] = \"%s\";\n", field->attrName);
        fprintf(f, "\t\tvalues[curCount + attr_count] = bsce->obj->%s;\n", field->name);
        fprintf(f, "\t\tcurCount++;\n\t}\n");
      }
      field = field->next;
    }
}

/* ------------------------------------------------------------- */

static void genFunctionNameBaseOnStartElement(HCOMPLEXTYPE obj, char *buffer, int onlyName)
{
  sprintf(buffer, "%sBase_Sax_%s_StartElement_Callback%s", onlyName?"":"void ", obj->type, onlyName?"":"(const char* element_name, int attr_count, char **keys, char **values, void* userData)");  
}

/* ------------------------------------------------------------- */
static void genFunctionNameBaseOnEndElement(HCOMPLEXTYPE obj, char *buffer, int onlyName)
{
  sprintf(buffer, "%sBase_Sax_%s_EndElement_Callback%s", onlyName?"":"void ", obj->type, onlyName?"":"(const char* element_name, void* userData)");  
}
/* ------------------------------------------------------------- */

static void writeCodeSaxSerialize(FILE* f, HCOMPLEXTYPE obj)
{
  char buffer[1054];
  char buffer2[1054];
  char ns[255];
  char type[255];
  HFIELD field;

  if (!genFunctionNameSaxSerialize(obj, buffer)) return;

  fprintf(f, "%s\n", buffer);
  fprintf(f, "{\n");

  fprintf(f, "\tint attrCount, curCount;\n\tchar **keys;\n\tchar **values;\n\tchar buffer[255];\n\n");

  
  if (obj->base_type != NULL)
  {
    	

    fprintf(f, "\tstruct Base_Sax_%s_Serializer bsce = { obj, OnStartElement, OnCharacters, OnEndElement, userData, 0 };\n\n", obj->type);
    genFunctionNameBaseOnStartElement(obj, buffer, 1);
    genFunctionNameBaseOnEndElement(obj, buffer2, 1);
    fprintf(f, "\n\t%s_Sax_Serialize(obj->__base, root_element_name, %s, OnCharacters, %s, (void*)&bsce);\n\n", 
        obj->base_type, buffer, buffer2);
  }
  else
  {
    field = obj->head;
    while (field != NULL)
    {
      if (field->maxOccurs > 1 || field->maxOccurs == -1)
      {
        genFieldType(field, buffer, 0);
        fprintf(f, "\t%s %s_cur;\n", buffer, field->name); 
      }
      field = field->next;
    }

    setSaxAttrs(f, obj);
    fprintf(f, "\n\tOnStartElement(root_element_name, attrCount, keys, values, userData);\n");

    field = obj->head;
    while (field != NULL)
    {
      if (field->attrName != NULL) 
      {
        field = field->next;
        continue;
      }
      
      if (field->maxOccurs > 1 || field->maxOccurs == -1)
      {
        fprintf(f, "\t%s_cur = obj->%s_head;\n", field->name, field->name);
        fprintf(f, "\twhile (%s_cur != NULL)\n\t{\n", field->name);


        if (trGetBuildInFlag(field->type) == 1) 
        {
          fprintf(f, "\n\t\tOnStartElement(\"%s\", 0, NULL, NULL, userData);\n", field->name);
          parseNS(field->type, ns, type);

          if (!strcmp(type, "string"))
          {
            fprintf(f, "\t\tif (%s_cur->value != NULL)\n\t\tOnCharacters(\"%s\", %s_cur->value, userData);\n",
              field->name, field->name, field->name);
          }
          if (!strcmp(type, "int") || !strcmp(type, "integer"))
          {
            fprintf(f, "\t\tsprintf(buffer, \"%%d\", %s_cur->value);\n", field->name);
            fprintf(f, "\t\tOnCharacters(\"%s\", buffer, userData);\n",
              field->name);
          }
          if (!strcmp(type, "float") || !strcmp(type, "double"))
          {
            fprintf(f, "\t\tsprintf(buffer, \"%%f\", %s_cur->value);\n", field->name);
            fprintf(f, "\t\tOnCharacters(\"%s\", buffer, userData);\n",
              field->name);
          }
          fprintf(f, "\t\tOnEndElement(\"%s\", userData);\n", field->name);
        }
        else
        {
          fprintf(f, "\tif (%s_cur->value)\n", field->name);
          sprintf(buffer, "%s_Sax_Serialize(%s_cur->value, \"%s\", OnStartElement, OnCharacters, OnEndElement, userData);\n",
            trXSDParseNs(field->type), field->name, field->name);
          fprintf(f, "\t\t%s\n", buffer);
        }

        fprintf(f, "\t\t%s_cur = %s_cur->next;\n", field->name , field->name);
        fprintf(f, "\t}\n");
      }
      else 
      {
        if (trGetBuildInFlag(field->type) == 1) 
        {
          fprintf(f, "\n\tOnStartElement(\"%s\", 0, NULL, NULL, userData);\n", field->name);
          parseNS(field->type, ns, type);

          if (!strcmp(type, "string"))
          {
            fprintf(f, "\tif (obj->%s != NULL)\n\t\tOnCharacters(\"%s\", obj->%s, userData);\n",
              field->name, field->name, field->name);
          }
          if (!strcmp(type, "int") || !strcmp(type, "integer"))
          {
            fprintf(f, "\tsprintf(buffer, \"%%d\", obj->%s);\n", field->name);
            fprintf(f, "\tOnCharacters(\"%s\", buffer, userData);\n",
              field->name);
          }
          if (!strcmp(type, "float") || !strcmp(type, "double"))
          {
            fprintf(f, "\tsprintf(buffer, \"%%f\", obj->%s);\n", field->name);
            fprintf(f, "\tOnCharacters(\"%s\", buffer, userData);\n",
              field->name);
          }
          fprintf(f, "\tOnEndElement(\"%s\", userData);\n", field->name);
        }
        else
        {
          fprintf(f, "\tif (obj->%s)\n", field->name);
          sprintf(buffer, "%s_Sax_Serialize(obj->%s, \"%s\", OnStartElement, OnCharacters, OnEndElement, userData);",
            trXSDParseNs(field->type), field->name, field->name);
          fprintf(f, "\t%s\n", buffer );
        }
      }
      field = field->next;
    }
   fprintf(f, "\n\tOnEndElement(root_element_name, userData);\n");
  }


  fprintf(f, "}\n\n");
}



static void writeCodeBaseOnStartElement(FILE* f, HCOMPLEXTYPE obj)
{
  char buffer[1054];

  genFunctionNameBaseOnStartElement(obj, buffer, 0);

  fprintf(f, "\n%s\n{\n", buffer);
  fprintf(f, "\tint attrCount, curCount;\n\tchar buffer[255];\n\n");
  
  fprintf(f, "\tstruct Base_Sax_%s_Serializer* bsce = (struct Base_Sax_%s_Serializer*)userData;\n",
    obj->type, obj->type);

  fprintf(f, "\n\tattrCount = 0;\n");
  fprintf(f, "\tif (bsce->stackDeep == 0)\n{\n");
  setSaxAttrsBase(f, obj);
  fprintf(f, "\t}\n");
  
  fprintf(f, "\tbsce->OnStartElement(element_name, attrCount + attr_count, keys, values, bsce->userData);\n");
  fprintf(f, "\tbsce->stackDeep++;\n");

  fprintf(f, "\n}\n\n");
}

static void writeCodeBaseOnEndElement(FILE* f, HCOMPLEXTYPE obj)
{
  char buffer[1054];
  HFIELD field;
  char ns[255];
  char type[255];

  genFunctionNameBaseOnEndElement(obj, buffer, 0);

  fprintf(f, "\n%s\n{\n", buffer);
  fprintf(f, "\tchar buffer[255];\n\n");
  
  fprintf(f, "\tstruct Base_Sax_%s_Serializer* bsce = (struct Base_Sax_%s_Serializer*)userData;\n",
     obj->type, obj->type);

  field = obj->head;
  while (field != NULL)
  {
   if (field->maxOccurs > 1 || field->maxOccurs == -1)
   {
     genFieldType(field, buffer, 0);
     fprintf(f, "\t%s %s_cur;\n", buffer, field->name); 
   }
   field = field->next;
  }

  
  fprintf(f, "\n\tbsce->stackDeep--;\n");

  fprintf(f, "\tif (bsce->stackDeep > 0)\n\t{\n\t\tbsce->OnEndElement(element_name, bsce->userData);\n\t}\n");
  fprintf(f, "\telse\n\t{\n");

    field = obj->head;
    while (field != NULL)
    {
      if (field->attrName != NULL) 
      {
        field = field->next;
        continue;
      }
      
      if (field->maxOccurs > 1 || field->maxOccurs == -1)
      {
        fprintf(f, "\t%s_cur = bsce->obj->%s_head;\n", field->name, field->name);
        fprintf(f, "\twhile (%s_cur != NULL)\n\t{\n", field->name);


        if (trGetBuildInFlag(field->type) == 1) 
        {
          fprintf(f, "\n\t\tbsce->OnStartElement(\"%s\", 0, NULL, NULL, bsce->userData);\n", field->name);
          parseNS(field->type, ns, type);

          if (!strcmp(type, "string"))
          {
            fprintf(f, "\t\tif (%s_cur->value != NULL)\n\t\tbsce->OnCharacters(\"%s\", %s_cur->value, bsce->userData);\n",
              field->name, field->name, field->name);
          }
          if (!strcmp(type, "int") || !strcmp(type, "integer"))
          {
            fprintf(f, "\t\tsprintf(buffer, \"%%d\", %s_cur->value);\n", field->name);
            fprintf(f, "\t\tbsce->OnCharacters(\"%s\", buffer, bsce->userData);\n",
              field->name);
          }
          if (!strcmp(type, "float") || !strcmp(type, "double"))
          {
            fprintf(f, "\t\tsprintf(buffer, \"%%f\", %s_cur->value);\n", field->name);
            fprintf(f, "\t\tbsce->OnCharacters(\"%s\", buffer, bsce->userData);\n",
              field->name);
          }
          fprintf(f, "\t\tbsce->OnEndElement(\"%s\", bsce->userData);\n", field->name);
        }
        else
        {
          fprintf(f, "\tif (%s_cur->value)\n", field->name);
          sprintf(buffer, "%s_Sax_Serialize(%s_cur->value, \"%s\", bsce->OnStartElement, bsce->OnCharacters, bsce->OnEndElement, bsce->userData);\n",
            trXSDParseNs(field->type), field->name, field->name);
          fprintf(f, "\t\t%s\n", buffer);
        }

        fprintf(f, "\t\t%s_cur = %s_cur->next;\n", field->name , field->name);
        fprintf(f, "\t}\n");
      }
      else 
      {
        if (trGetBuildInFlag(field->type) == 1) 
        {
          fprintf(f, "\n\tbsce->OnStartElement(\"%s\", 0, NULL, NULL, bsce->userData);\n", field->name);
          parseNS(field->type, ns, type);

          if (!strcmp(type, "string"))
          {
            fprintf(f, "\tif (bsce->obj->%s != NULL)\n\t\tbsce->OnCharacters(\"%s\", bsce->obj->%s, bsce->userData);\n",
              field->name, field->name, field->name);
          }
          if (!strcmp(type, "int") || !strcmp(type, "integer"))
          {
            fprintf(f, "\tsprintf(buffer, \"%%d\", bsce->obj->%s);\n", field->name);
            fprintf(f, "\tbsce->OnCharacters(\"%s\", buffer, bsce->userData);\n",
              field->name);
          }
          if (!strcmp(type, "float") || !strcmp(type, "double"))
          {
            fprintf(f, "\tsprintf(buffer, \"%%f\", bsce->obj->%s);\n", field->name);
            fprintf(f, "\tbsce->OnCharacters(\"%s\", buffer, bsce->userData);\n",
              field->name);
          }
          fprintf(f, "\tbsce->OnEndElement(\"%s\", bsce->userData);\n", field->name);
        }
        else
        {
          fprintf(f, "\tif (obj->%s)\n", field->name);
          sprintf(buffer, "%s_Sax_Serialize(obj->%s, \"%s\", bsce->OnStartElement, bsce->OnCharacters, bsce->OnEndElement, bsce->userData);",
            trXSDParseNs(field->type), field->name, field->name);
          fprintf(f, "\t%s\n", buffer );
        }
      }
      field = field->next;
    }
   fprintf(f, "\n\tbsce->OnEndElement(element_name, userData);\n");


  fprintf(f, "\t}\n");
  fprintf(f, "\n}\n\n");
}


/* ------------------------------------------------------------------------------- */

static void writeCodeDeserialize(FILE* f, HCOMPLEXTYPE obj)
{
  char buffer[1054];
  HFIELD field;
  char ns[255];
  char type[255];

  if (!genFunctionNameDeserialize(obj, buffer)) return;

  fprintf(f, "#ifndef _DESERIALIZER_DISABLED_\n\n");
  fprintf(f, "%s\n", buffer);
  fprintf(f, "{\n");

  fprintf(f, "\txmlNodePtr cur;\n\txmlChar *key;\n");
  
  fprintf(f, "\tstruct %s* obj;\n", obj->type);
  fprintf(f, "\tobj = %s_Create();\n", obj->type);



  /* Begin deserialize base type */
  if (obj->base_type != NULL)
  {
    fprintf(f, "\n\tobj->__base = %s_Deserialize(xmlRoot);\n\n", obj->base_type);
  }

  /* End deserialize base type */

  /* Begin setting attributes */
  field = obj->head;
  while (field != NULL)
  {
    if (field->attrName != NULL) 
    {
      fprintf(f, "\tkey = xmlGetProp(xmlRoot, \"%s\");\n", field->attrName);
      fprintf(f, "\tif (key != NULL) {\n");
      parseNS(field->type, ns, type);

      if (!strcmp(type, "string"))
      {
        fprintf(f, "\t\t%s_Set_%s(obj, (const char*)key);\n", field->parentObj->type, field->name);
      }
      else if (!strcmp(type, "int") || !strcmp(type, "integer"))
      {
        fprintf(f, "\t\t%s_Set_%s(obj, atoi((const char*)key));\n", field->parentObj->type, field->name);
      }
      else if (!strcmp(type, "float") || !strcmp(type, "double"))
      {
        fprintf(f, "\t\t%s_Set_%s(obj, atof((const char*)key));\n", field->parentObj->type, field->name);
      }
      else {
        fprintf(stderr, "WARNING: Type '%s' not found as attribute\n", type);
      }

      fprintf(f, "\t\t/*xmlFree(key);*/\n");
      fprintf(f, "\t}\n");
    }

    field = field->next;
  }
  /* End setting attributes */

  fprintf(f, "\tcur = xmlRoot->xmlChildrenNode;\n");
  fprintf(f, "\twhile (cur != NULL) {\n");
  fprintf(f, "\t\tif (cur->type != XML_ELEMENT_NODE) {\n");
  fprintf(f, "\t\t\tcur = cur->next;\n");
  fprintf(f, "\t\t\tcontinue;\n");
  fprintf(f, "\t\t}\n");

  /* Just debug you can delete this */
/*  fprintf(f, "\t\tprintf(\"%s->%%s\\n\", cur->name);\n", obj->type); */

  field = obj->head;
  while (field != NULL)
  {
		
    if (field->attrName != NULL) 
    {
      field = field->next;
      continue;
    }
    
    fprintf(f, "\t\tif ((!xmlStrcmp(cur->name, (const xmlChar *)\"%s\"))){\n", field->name);

    if (trGetBuildInFlag(field->type) == 1) 
    {
      parseNS(field->type, ns, type);

      if (!strcmp(type, "string"))
      {
        fprintf(f, "\t\t\tkey = xmlNodeListGetString(cur->doc, cur->xmlChildrenNode, 1);\n");
        if (field->maxOccurs > 1 || field->maxOccurs == -1) {
          fprintf(f, "\t\t\t%s_Add_%s(obj, (const char*)key);\n", field->parentObj->type, field->name);
        } else {
          fprintf(f, "\t\t\t%s_Set_%s(obj, (const char*)key);\n", field->parentObj->type, field->name);
        }
        fprintf(f, "\t\t\t/*xmlFree(key);*/\n");
      }
      else if (!strcmp(type, "int") || !strcmp(type, "integer"))
      {
        fprintf(f, "\t\t\tkey = xmlNodeListGetString(cur->doc, cur->xmlChildrenNode, 1);\n");
        if (field->maxOccurs > 1 || field->maxOccurs == -1) {
          fprintf(f, "\t\t\t%s_Add_%s(obj, atoi((const char*)key));\n", field->parentObj->type, field->name);
        } else {
          fprintf(f, "\t\t\t%s_Set_%s(obj, atoi((const char*)key));\n", field->parentObj->type, field->name);
        }
        fprintf(f, "\t\t\t/*xmlFree(key);*/\n");
      }
      else if (!strcmp(type, "float") || !strcmp(type, "double"))
      {
        fprintf(f, "\t\t\tkey = xmlNodeListGetString(cur->doc, cur->xmlChildrenNode, 1);\n");
        if (field->maxOccurs > 1 || field->maxOccurs == -1) {
          fprintf(f, "\t\t\t%s_Add_%s(obj, atof((const char*)key));\n", field->parentObj->type, field->name);
        } else {
          fprintf(f, "\t\t\t%s_Set_%s(obj, atof((const char*)key));\n", field->parentObj->type, field->name);
        }
        fprintf(f, "\t\t\t/*xmlFree(key);*/\n");
      }
    }
    else
    {
        if (field->maxOccurs > 1 || field->maxOccurs == -1) {
          fprintf(f, "\t\t\t%s_Add_%s( obj, %s_Deserialize(cur) );\n", field->parentObj->type, field->name, trXSDParseNs(field->type));
        } else {
          fprintf(f, "\t\t\t%s_Set_%s( obj, %s_Deserialize(cur) );\n", field->parentObj->type, field->name, trXSDParseNs(field->type));
        }
    }

    fprintf(f, "\t\t}\n");
    field = field->next;
  }


  fprintf(f, "\t// TODO: \n");
  fprintf(f, "\t\tcur = cur->next;\n");

  fprintf(f, "\t}\n");
    
  fprintf(f, "\treturn obj;\n");    
  fprintf(f, "}\n");
  fprintf(f, "\n#endif\n");

}
