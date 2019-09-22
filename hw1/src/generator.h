#ifndef GENERATOR_H
#define GENERATOR_H

int lookup_table_for_index(SymbolTable *table, char id[]);

void fprint_op(FILE *target, ValueType op, SymbolTable *table);
void fprint_expr(FILE *target, Expression *expr, SymbolTable *table);
void gencode(Program prog, FILE * target, SymbolTable *table);

#endif //GENERATOR_H
