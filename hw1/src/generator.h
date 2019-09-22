#ifndef GENERATOR_H
#define GENERATOR_H

void fprint_op( FILE *target, ValueType op );
void fprint_expr( FILE *target, Expression *expr );
void gencode( Program prog, FILE * target );

#endif //GENERATOR_H
