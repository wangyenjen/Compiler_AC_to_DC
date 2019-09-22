#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "header.h"
#include "parser.h"
#include "symtab.h"
#include "type_check.h"
#include "generator.h"

int main( int argc, char *argv[] )
{
  FILE *source, *target;
  Program program;
  SymbolTable symtab;

  if( argc == 3){
    source = fopen(argv[1], "r");
    target = fopen(argv[2], "w");
    if( !source ){
      printf("can't open the source file\n");
      exit(2);
    }
    else if( !target ){
      printf("can't open the target file\n");
      exit(2);
    }
    else{
      program = parser(source);
      fclose(source);
      symtab = build(program);
      check(&program, &symtab);
      gencode(program, target, &symtab);
    }
  }
  else{
    printf("Usage: %s source_file target_file\n", argv[0]);
  }

  return 0;
}

