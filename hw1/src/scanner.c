#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "header.h"
#include "scanner.h"

int checkVariableNameChar(char c) {
  return isgraph(c) &&
    c != '+' &&
    c != '-' &&
    c != '*' &&
    c != '/' &&
    c != '=';
}

Token getNumericToken( FILE *source, char c )
{
  Token token;
  int i = 0;

  while( isdigit(c) ) {
    token.tok[i++] = c;
    c = fgetc(source);
  }

  if( c != '.' ){
    ungetc(c, source);
    token.tok[i] = '\0';
    token.type = IntValue;
    return token;
  }

  token.tok[i++] = '.';

  c = fgetc(source);
  if( !isdigit(c) ){
    ungetc(c, source);
    printf("Expect a digit : %c\n", c);
    exit(1);
  }

  while( isdigit(c) ){
    token.tok[i++] = c;
    c = fgetc(source);
  }

  ungetc(c, source);
  token.tok[i] = '\0';
  token.type = FloatValue;
  return token;
}

Token getVariableNameToken(FILE *source, char c) {
  Token token;
  token.type = VariableName;
  token.tok[0] = c;
  int i = 1;
  c = fgetc(source);
  while (checkVariableNameChar(c)) {
    token.tok[i++] = c;
    c = fgetc(source);
  }
  ungetc(c, source);
  token.tok[i] = '\0';
  return token;
}

Token scanner( FILE *source ) {
  char c;
  Token token;

  while (!feof(source)) {
    c = fgetc(source);

    while (isspace(c)) {
      c = fgetc(source);
    }

    if (isdigit(c)) {
      return getNumericToken(source, c);
    }

    token.tok[0] = c;
    token.tok[1] = '\0';
    if( islower(c) ) {
      char c2 = fgetc(source);
      ungetc(c2, source);
      if(c == 'f' && !checkVariableNameChar(c2)) {
	      token.type = FloatDeclaration;
      } else if(c == 'i' && !checkVariableNameChar(c2)) {
	      token.type = IntegerDeclaration;
      } else if(c == 'p' && !checkVariableNameChar(c2)) {
	      token.type = PrintOp;
      } else {
	      return getVariableNameToken(source, c);
      }
      return token;
    } else if (checkVariableNameChar(c)) {
      return getVariableNameToken(source, c);
    }

    switch(c) {
    case '=':
      token.type = AssignmentOp;
      return token;
    case '+':
      token.type = PlusOp;
      return token;
    case '-':
      token.type = MinusOp;
      return token;
    case '*':
      token.type = MulOp;
      return token;
    case '/':
      token.type = DivOp;
      return token;
    case EOF:
      token.type = EOFsymbol;
      token.tok[0] = '\0';
      return token;
    default:
      printf("Invalid character : %c\n", c);
      exit(1);
    }
  }

  token.tok[0] = '\0';
  token.type = EOFsymbol;
  return token;
}

