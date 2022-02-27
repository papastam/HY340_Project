all:
	lex lex.l
	gcc lex.c -o lex.out

execute:
	make all
	./lex.out input.al