#ifndef OPTIMIZER_H
#define OPTIMIZER_H


typedef struct Pair {
  Value val;
  int res;
} Pair;

void release_expr(Expression *expr);
void optmize_expr(Expression *expr);
void optcode(Program *prog);

#endif //OPTIMIZER_H
