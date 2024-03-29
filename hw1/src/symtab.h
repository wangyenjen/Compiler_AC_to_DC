#ifndef SYMTAB_H
#define SYMTAB_H

void InitializeTable( SymbolTable *table );
void add_table( SymbolTable *table, char id[], DataType t );
SymbolTable build( Program program );

#endif //SYMTAB_H
