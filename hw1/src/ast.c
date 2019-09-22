#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "ast.h"

Declaration makeDeclarationNode( Token declare_type, Token identifier )
{
  Declaration tree_node;

  switch(declare_type.type){
  case FloatDeclaration:
    tree_node.type = Float;
    break;
  case IntegerDeclaration:
    tree_node.type = Int;
    break;
  default:
    break;
  }
  strcpy(tree_node.name, identifier.tok);

  return tree_node;
}

Declarations *makeDeclarationTree( Declaration decl, Declarations *decls )
{
  Declarations *new_tree = (Declarations *)malloc( sizeof(Declarations) );
  new_tree->first = decl;
  new_tree->rest = decls;

  return new_tree;
}


Statement makeAssignmentNode( char id[], Expression *v, Expression *expr_tail )
{
  Statement stmt;
  AssignmentStatement assign;

  stmt.type = Assignment;
  strcpy(assign.id, id);
  if(expr_tail == NULL)
    assign.expr = v;
  else
    assign.expr = expr_tail;
  stmt.stmt.assign = assign;

  return stmt;
}

Statement makePrintNode( char id[] )
{
  Statement stmt;
  stmt.type = Print;
  strcpy(stmt.stmt.variable, id);

  return stmt;
}

Statements *makeStatementTree( Statement stmt, Statements *stmts )
{
  Statements *new_tree = (Statements *)malloc( sizeof(Statements) );
  new_tree->first = stmt;
  new_tree->rest = stmts;

  return new_tree;
}

