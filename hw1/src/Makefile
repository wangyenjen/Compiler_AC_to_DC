All: AcDc.o scanner.o parser.o ast.o symtab.o type_check.o optimizer.o generator.o
	gcc AcDc.o scanner.o parser.o ast.o symtab.o type_check.o optimizer.o generator.o -o AcDc
AcDc.o: AcDc.c parser.h symtab.h type_check.h generator.h header.h
	gcc -c AcDc.c
scanner.o: scanner.c scanner.h header.h
	gcc -c scanner.c
parser.o: parser.c scanner.h parser.h ast.h header.h
	gcc -c parser.c
ast.o: ast.c ast.h header.h
	gcc -c ast.c
symtab.o: symtab.c symtab.h header.h
	gcc -c symtab.c
type_check.o: type_check.c type_check.h header.h
	gcc -c type_check.c
optimizer.o: optimizer.c optimizer.h header.h
	gcc -c optimizer.c
generator.o: generator.c generator.h header.h
	gcc -c generator.c
clean:
	rm AcDc
	rm *.o
