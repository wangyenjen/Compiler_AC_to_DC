#include <stdio.h>
#include <string.h>
#include "header.h"
#include "symtab.h"

void InitializeTable( SymbolTable *table )
{
  int i;

  table->max_index = 0;
  for(i = 0 ; i < 26; i++) {
    table->table[i] = Notype;
    table->symbol_name[i][0] = '\0';
  }
}

void add_table( SymbolTable *table, char id[], DataType t )
{
  for (int i = 0; i < 26; i++) {
    if (strcmp(id, table->symbol_name[i]) == 0) {
      printf("Error : id %s has been declared\n", id);
      table->table[i] = t;
      return;
    }
  }

  int index = table->max_index++;
  table->table[index] = t;
  strcpy(table->symbol_name[index], id);
}

SymbolTable build( Program program )
{
  SymbolTable table;
  Declarations *decls = program.declarations;
  Declaration current;

  InitializeTable(&table);

  while(decls !=NULL){
    current = decls->first;
    add_table(&table, current.name, current.type);
    decls = decls->rest;
  }

  return table;
}

