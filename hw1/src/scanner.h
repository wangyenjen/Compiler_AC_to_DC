#ifndef SCANNER_H
#define SCANNER_H

int checkVariableNameChar(char c);

Token getNumericToken( FILE *source, char c );
Token getVariableNameToken(FILE *source, char c);
Token scanner( FILE *source );

#endif //SCANNER_H
