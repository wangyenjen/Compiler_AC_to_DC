/***
 *** Author: B06902026, B06902093
 ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "type_check.h"

void convertType( Expression * old, DataType type )
{
  if(old->type == Float && type == Int){
    printf("error : can't convert float to integer\n");
    return;
  }
  if(old->type == Int && type == Float){
    Expression *tmp = (Expression *)malloc( sizeof(Expression) );
    if(old->v.type == Identifier)
      printf("convert to float %s \n",old->v.val.id);
    else
      printf("convert to float %d \n", old->v.val.ivalue);
    tmp->v = old->v;
    tmp->leftOperand = old->leftOperand;
    tmp->rightOperand = old->rightOperand;
    tmp->type = old->type;

    Value v;
    v.type = IntToFloatConvertNode;
    v.val.op = IntToFloatConvert;
    old->v = v;
    old->type = Int;
    old->leftOperand = tmp;
    old->rightOperand = NULL;
  }
}

DataType generalize( Expression *left, Expression *right )
{
  if(left->type == Float || right->type == Float){
    printf("generalize : float\n");
    return Float;
  }
  printf("generalize : int\n");
  return Int;
}

DataType lookup_table( SymbolTable *table, char id[] )
{
  for (int i = 0; i < 26; i++) {
    if (strcmp(table->symbol_name[i], id) == 0) {
      return table->table[i];
    }
  }
  printf("Error : identifier %s is not declared\n", id);//error
  return Notype;
}

void checkexpression( Expression * expr, SymbolTable * table )
{
  char id[1025];
  if(expr->leftOperand == NULL && expr->rightOperand == NULL){
    switch(expr->v.type){
    case Identifier:
      strcpy(id, expr->v.val.id);
      printf("identifier : %s\n",id);
      expr->type = lookup_table(table, id);
      break;
    case IntConst:
      printf("constant : int\n");
      expr->type = Int;
      break;
    case FloatConst:
      printf("constant : float\n");
      expr->type = Float;
      break;
      //case PlusNode: case MinusNode: case MulNode: case DivNode:
    default:
      break;
    }
  }
  else{
    Expression *left = expr->leftOperand;
    Expression *right = expr->rightOperand;

    checkexpression(left, table);
    checkexpression(right, table);

    DataType type = generalize(left, right);
    convertType(left, type);//left->type = type;//converto
    convertType(right, type);//right->type = type;//converto
    expr->type = type;
  }
}

void checkstmt( Statement *stmt, SymbolTable * table )
{
  if(stmt->type == Assignment){
    AssignmentStatement assign = stmt->stmt.assign;
    printf("assignment : %s \n",assign.id);
    checkexpression(assign.expr, table);
    stmt->stmt.assign.type = lookup_table(table, assign.id);
    if (assign.expr->type == Float && stmt->stmt.assign.type == Int) {
      printf("error : can't convert float to integer\n");
    } else {
      convertType(assign.expr, stmt->stmt.assign.type);
    }
  }
  else if (stmt->type == Print){
    printf("print : %s \n",stmt->stmt.variable);
    lookup_table(table, stmt->stmt.variable);
  }
  else printf("error : statement error\n");//error
}

void check( Program *program, SymbolTable * table )
{
  Statements *stmts = program->statements;
  while(stmts != NULL){
    checkstmt(&stmts->first,table);
    stmts = stmts->rest;
  }
}

