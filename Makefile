all:
	rm lex.yy.c
	flex lex.l
	gcc lex.yy.c -o al
