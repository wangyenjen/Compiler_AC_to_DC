#ifndef HEADER_H
#define HEADER_H

/******************************************************************************************************************************************
    All enumeration literals
       TokenType : Specify the type of the token scanner returns
	   DataType  : The data type of the declared variable
	   StmtType  : Indicate one statement in AcDc program is print or assignment statement.
	   ValueType : The node types of the expression tree that represents the expression on the right hand side of the assignment statement.
	               Identifier, IntConst, FloatConst must be the leaf nodes ex: a, b, c , 1.5 , 3.
				   PlusNode, MinusNode, MulNode, DivNode are the operations in AcDc. They must be the internal nodes.
                   Note that IntToFloatConvertNode to represent the type coercion may appear after finishing type checking. 			  
	   Operation : Specify all arithematic expression, including +, - , *, / and type coercion.
*******************************************************************************************************************************************/

typedef enum TokenType { FloatDeclaration, IntegerDeclaration, PrintOp, AssignmentOp, PlusOp, MinusOp,
			 MulOp, DivOp, VariableName, IntValue, FloatValue, EOFsymbol } TokenType;
typedef enum DataType { Int, Float, Notype }DataType;
typedef enum StmtType { Print, Assignment } StmtType;
typedef enum ValueType { Identifier, IntConst, FloatConst, PlusNode, MinusNode, MulNode, DivNode, IntToFloatConvertNode } ValueType;
typedef enum Operation { Plus, Minus, Mul, Div, Assign, IntToFloatConvert } Operation;


/**************************************************************************************** 
   All structures to facilitate the processes of 
   scanning, parsing, AST, type-checking, building the symbol table, and code generation.
*****************************************************************************************/


/* For scanner */
typedef struct Token{
  TokenType type;
  char tok[1025];
}Token;

/*** The following are nodes of the AST. ***/

/* For decl production or say one declaration statement */
typedef struct Declaration{
  DataType type;
  char name[1025];
}Declaration;

/* 
   For decls production or say all declarations. (
   You can view it as the subtree for decls in AST,
   or just view it as the linked list that stores 
   all declarations. ) 
*/
typedef struct Declarations{
  Declaration first;
  struct Declarations *rest;
}Declarations;

/* For the nodes of the expression on the right hand side of one assignment statement */
typedef struct Value{
  ValueType type;
  union{
    char id[1025];             /* if the node represent the access of the identifier */
    Operation op;              /* store +, -, *, /, =, type_convert */
    int ivalue;                /* for integer constant in the expression */
    float fvalue;              /* for float constant */
  }val;
}Value;


/* 
   The data structure of the expression tree.
   Recall how to deal with expression by tree 
   in data structure course.   
*/
typedef struct Expression{
  Value v;
  struct Expression *leftOperand;
  struct Expression *rightOperand;
  DataType type;
}Expression;


/* For one assignment statement */
typedef struct AssignmentStatement{
  char id[1025];
  Expression *expr;
  DataType type;      /* For type checking to store the type of all expression on the right. */
}AssignmentStatement;


/* For stmt production or say one statement*/
typedef struct Statement{
  StmtType type;
  union{
    char variable[1025];        /* print statement */
    AssignmentStatement assign;
  }stmt;
}Statement;

/* For stmts production or say all productions */
typedef struct Statements{
  struct Statement first;
  struct Statements *rest;
}Statements;

/* For the root of the AST. */
typedef struct Program{
  Declarations *declarations;
  Statements *statements;
}Program;

/* For building the symbol table */
typedef struct SymbolTable{
  int max_index;
  DataType table[26];
  char symbol_name[26][1025];
} SymbolTable;

#endif // HEADER_H
