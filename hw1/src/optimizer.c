/***
 *** Author: B06902026, B06902093
 ***/

#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "optimizer.h"

void release_expr(Expression *expr) {
  if (expr == NULL) {
    return;
  }
  if (expr->leftOperand != NULL) {
    release_expr(expr->leftOperand);
  }
  if (expr->rightOperand != NULL) {
    release_expr(expr->rightOperand);
  }
  free(expr);
}

Pair optimize_expr(Expression *expr) {
  Pair res;
  res.res = 1;
  if(expr->leftOperand == NULL){
    switch((expr->v).type) {
      case Identifier:
        res.val = expr->v;
        res.res = 0;
        break;
      case IntConst:
        res.val = expr->v;
        break;
      case FloatConst:
        res.val = expr->v;
        break;
      default:
        fprintf(stdout ,"Error In optimize_left_expr. (expr->v).type=%d\n", (expr->v).type);
        res.val = expr->v;
        res.res = -1;
    }
  }
  else {
    Pair res_l = optimize_expr(expr->leftOperand);
    if (res_l.res != 1) {
      res.val = expr->v;
      res.res = 0;
    }
    if(expr->rightOperand == NULL) {
      if ((expr->v).type == IntToFloatConvertNode) {
        res.val.type = FloatConst;
        res.val.val.fvalue = res_l.val.val.ivalue;
        res.res = res_l.res;
      }
    }
    else {
      Pair res_r = optimize_expr(expr->rightOperand);
        if (res_r.res) {
        switch((expr->v).type){
          case MinusNode:
            if (res_l.val.type == FloatConst) {
              res.val.type = FloatConst;
              res.val.val.fvalue = res_l.val.val.fvalue - res_r.val.val.fvalue;
            } else {
              res.val.type = IntConst;
              res.val.val.ivalue = res_l.val.val.ivalue - res_r.val.val.ivalue;
            }
            break;
          case PlusNode:
            if (res_l.val.type == FloatConst) {
              res.val.type = FloatConst;
              res.val.val.fvalue = res_l.val.val.fvalue + res_r.val.val.fvalue;
            } else {
              res.val.type = IntConst;
              res.val.val.ivalue = res_l.val.val.ivalue + res_r.val.val.ivalue;
            }
            break;
          case MulNode:
            if (res_l.val.type == FloatConst) {
              res.val.type = FloatConst;
              res.val.val.fvalue = res_l.val.val.fvalue * res_r.val.val.fvalue;
            } else {
              res.val.type = IntConst;
              res.val.val.ivalue = res_l.val.val.ivalue * res_r.val.val.ivalue;
            }
            break;
          case DivNode:
            if (res_l.val.type == FloatConst) {
              res.val.type = FloatConst;
              res.val.val.fvalue = res_l.val.val.fvalue / res_r.val.val.fvalue;
            } else {
              res.val.type = IntConst;
              res.val.val.ivalue = res_l.val.val.ivalue / res_r.val.val.ivalue;
            }
            break;
          default:
            fprintf(stdout, "Error in optimize_expr_op ValueType = %d\n", (expr->v).type);
            res.val = expr->v;
            res.res = 0;
        }
      } else {
        res.val = expr->v;
        res.res = 0;
      }
    }
  }
  if (res.res == 1) {
    expr->v = res.val;
    switch(res.val.type) {
      case IntConst:
        expr->type = Int; 
        break;
      case FloatConst:
        expr->type = Float;
        break;
      default: 
        expr->type = Notype;
    }
    release_expr(expr->leftOperand);
    release_expr(expr->rightOperand);
    expr->leftOperand = NULL;
    expr->rightOperand = NULL;
  }
  return res;
}

void optcode(Program *prog) {
  Statements *stmts = prog->statements;
  Statement stmt;

  while (stmts != NULL) {
    stmt = stmts->first;
    if (stmt.type == Assignment) {
      optimize_expr(stmt.stmt.assign.expr);
    }
    stmts = stmts->rest;
  }
}

