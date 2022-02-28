all:
	flex newlex.l
	gcc lex.yy.c -o al
