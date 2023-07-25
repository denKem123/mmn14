#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"
#define MAX 100

typedef struct Macro {
    char mname[MAX];
    char mcontent[MAX];
    struct Macro* next;
} Macro;

/*We implement a table of macros*/
void add_to_mtable(struct Macro *head , char name[] , char content[]);

/*Prints the macro table*/
void print_macro_table(struct Macro *tail);

/*Checks whether it is the beginning of a macro or the end of a macro*/
int is_macro_or_endm(char line[]);

/*Enter the macro name in the macros table*/
void insert_name(struct Macro *temp, char line[]);

/*Inserts the macro contents into the macros table*/
void insert_content(struct Macro *temp, FILE *fp);

/*Performing the first pass on the file (inserting the macros into the macro table,
                                                        copying the corresponding rows from the table to the file, etc.)*/
int pre_read_file(int i, char *argv[],struct Macro *head);

/*Copy the contents of the corresponding macro to the file from the table, if it is a macro command*/
int is_macro_call(char line[], FILE *fpw,struct Macro *tail);


void pre_write_file(int i, char *argv[],struct Macro *tail);