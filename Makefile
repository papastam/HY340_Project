all:
	flex newlex.l
	gcc lex.yy.c -o al
x:
	make all
	./al < test
xx:
	./al < test
