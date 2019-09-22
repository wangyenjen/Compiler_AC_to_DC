#include <stdio.h>
#include <string.h>
#include "header.h"
#include "generator.h"

int lookup_table_for_index(SymbolTable *table, char id[]) {
  for (int i = 0; i < 26; i++) {
    if (strcmp(table->symbol_name[i], id) == 0) {
      return i;
    }
  }
  printf("Error : identifier %s is not declared\n", id);//error
  return -1;  
}

char id_to_char(SymbolTable *table, char id[]) {
  int index = lookup_table_for_index(table, id);
  return index + 'a';
}

void fprint_op( FILE *target, ValueType op, SymbolTable *table )
{
  switch(op){
  case MinusNode:
    fprintf(target,"-\n");
    break;
  case PlusNode:
    fprintf(target,"+\n");
    break;
  case MulNode:
    fprintf(target,"*\n");
    break;
  case DivNode:
    fprintf(target,"/\n");
    break;
  default:
    fprintf(target,"Error in fprintf_op ValueType = %d\n",op);
    break;
  }
}

void fprint_expr( FILE *target, Expression *expr, SymbolTable *table )
{

  if(expr->leftOperand == NULL){
    switch( (expr->v).type ){
    case Identifier:
      fprintf(target,"l%c\n",id_to_char(table, (expr->v).val.id));
      break;
    case IntConst:
      fprintf(target,"%d\n",(expr->v).val.ivalue);
      break;
    case FloatConst:
      fprintf(target,"%f\n", (expr->v).val.fvalue);
      break;
    default:
      fprintf(target,"Error In fprint_left_expr. (expr->v).type=%d\n",(expr->v).type);
      break;
    }
  }
  else{
    fprint_expr(target, expr->leftOperand, table);
    if(expr->rightOperand == NULL){
      fprintf(target,"5k\n");
    }
    else{
      //	fprint_right_expr(expr->rightOperand);
      fprint_expr(target, expr->rightOperand, table);
      fprint_op(target, (expr->v).type, table);
    }
  }
}

void gencode(Program prog, FILE * target, SymbolTable *table)
{
  Statements *stmts = prog.statements;
  Statement stmt;

  while(stmts != NULL){
    stmt = stmts->first;
    switch(stmt.type){
    case Print:
      fprintf(target,"l%c\n",id_to_char(table, stmt.stmt.variable));
      fprintf(target,"p\n");
      break;
    case Assignment:
      fprint_expr(target, stmt.stmt.assign.expr, table);
      /*
	if(stmt.stmt.assign.type == Int){
	fprintf(target,"0 k\n");
	}
	else if(stmt.stmt.assign.type == Float){
	fprintf(target,"5 k\n");
	}*/
      fprintf(target,"s%c\n",id_to_char(table, stmt.stmt.assign.id));
      fprintf(target,"0 k\n");
      break;
    }
    stmts=stmts->rest;
  }

}

