#ifndef AST_H
#define AST_H

Declaration makeDeclarationNode( Token declare_type, Token identifier );
Declarations *makeDeclarationTree( Declaration decl, Declarations *decls );
Statement makeAssignmentNode( char id[], Expression *v, Expression *expr_tail );
Statement makePrintNode( char id[] );
Statements *makeStatementTree( Statement stmt, Statements *stmts );

#endif //AST_H
