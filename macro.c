#include "macro.h"

void add_to_mtable(struct Macro *head, char name[], char content[]) /*implements a table of macros*/
{
  struct Macro *temp = NULL;
  temp = (struct Macro *)malloc(sizeof(struct Macro));
  memset(temp->mname, '\0', MAX);
  memset(temp->mcontent, '\0', MAX);
  strcpy(temp->mname, name);
  strcpy(temp->mcontent, content);
  head->next = temp;
}
void print_macro_table(struct Macro *tail)
{
  struct Macro *temp = NULL;
  temp = (struct Macro *)malloc(sizeof(struct Macro));
  temp = tail->next;
  while (temp != NULL)
  {
    printf("\n mcro name:  %s \n  content:  %s \n", temp->mname, temp->mcontent);
    temp = temp->next;
  }
}

int is_macro_or_endm(char line[])
{
  int index = 0, mindex = 0;
  char macro[MAX];
  memset(macro, '\0', MAX);
  while (isspace(line[index]))
    index++;
  while (!isspace(line[index]) && line[index] != '\n')
  {
    macro[mindex] = line[index];
    mindex++;
    index++;
  }
  if (!strcmp(macro, "mcro"))
    return 1;
  if (!strcmp(macro, "endmcro"))
    return 2;
  return 0;
}

void insert_name(struct Macro *temp, char line[])
{
  int index = 0, nindex = 0;
  char name[MAX];
  memset(name, '\0', MAX);
  while (isspace(line[index]))
    index++;
  while (!isspace(line[index]) && line[index] != '\n')
    index++;
  while (isspace(line[index]))
    index++;
  while (!isspace(line[index]) && line[index] != '\n')
  {
    name[nindex] = line[index];
    nindex++;
    index++;
  }
  strcpy(temp->mname, name);
}

void insert_content(struct Macro *temp, FILE *fp)
{
  char line[MAX];
  char content[MAX];
  memset(line, '\0', MAX);
  memset(content, '\0', MAX);
  fgets(line, MAX, fp);
  while (is_macro_or_endm(line) != 2)
  {
    strncat(content, line, MAX);
    fgets(line, MAX, fp);
  }
  strcpy(temp->mcontent, content);
}

int pre_read_file(int i, char *argv[], struct Macro *head)
{
  char *input_filename;
  char line[MAX];
  FILE *fp;
  memset(line, '\0', MAX);

  /* Concat extensionless filename with .as extension */
  input_filename = strallocat(argv[i], ".as");

  fp = fopen(input_filename, "r");
  if (fp == NULL)
  {
    printf("error: cant open the file: %s \n \n", input_filename);
    free(input_filename);
    return 1;
  }
  while (fgets(line, MAX, fp))
  {
    struct Macro *temp = NULL;
    temp = (struct Macro *)malloc(sizeof(struct Macro));
    if (is_macro_or_endm(line) == 1)
    {
      insert_name(temp, line);
      insert_content(temp, fp);
      head->next = temp;
      head = temp;
    }
  }
  return 0;
}

int is_macro_call(char line[], FILE *fpw, struct Macro *tail)
{
  int index = 0, mindex = 0;
  char Mname[MAX];
  struct Macro *temp = NULL;
  temp = (struct Macro *)malloc(sizeof(struct Macro));
  temp = tail;
  memset(Mname, '\0', MAX);
  while (isspace(line[index]))
    index++;
  while (!isspace(line[index]) && line[index] != '\n')
  {
    Mname[mindex] = line[index];
    mindex++;
    index++;
  }
  while (temp != NULL)
  {
    if (!strcmp(temp->mname, Mname))
    {
      fprintf(fpw, "%s", temp->mcontent);
      return 1;
    }
    temp = temp->next;
  }
  return 0;
}

void pre_write_file(int i, char *argv[], struct Macro *tail)
{
  char *input_filename;
  char *write_filename;
  int macroflag = 0;
  FILE *fpw;
  FILE *fpr;
  char line[MAX];
  memset(line, '\0', MAX);

  /* Concat extensionless filename with .as extension */
  input_filename = strallocat(argv[i], ".as");
  write_filename = strallocat(argv[i], ".am");

  fpr = fopen(input_filename, "r");
  fpw = fopen(write_filename, "w");
  if (fpr == NULL)
  {
    printf("error: cant open the file: %s \n \n", input_filename);
    free(input_filename);
    free(write_filename);
  }

  while (fgets(line, MAX, fpr))
  {
    if (!macroflag)
    {
      if (!is_macro_call(line, fpw, tail))
      {
        if (is_macro_or_endm(line) == 0)
        {
          fprintf(fpw, "%s", line);
        }
        else
        {
          macroflag = 1;
        }
      }
    }
    else
    {
      if (is_macro_or_endm(line) == 2)
        macroflag = 0;
    }
  }
  fclose(fpw);
  fclose(fpr);
}