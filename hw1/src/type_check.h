#ifndef TYPE_CHECK_H
#define TYPE_CHECK_H

void convertType( Expression * old, DataType type );
DataType generalize( Expression *left, Expression *right );
DataType lookup_table( SymbolTable *table, char c );
void checkexpression( Expression * expr, SymbolTable * table );
void checkstmt( Statement *stmt, SymbolTable * table );
void check( Program *program, SymbolTable * table);

#endif //TYPE_CHECK_H
