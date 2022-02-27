all:
<<<<<<< HEAD
	rm lex.yy.c
	flex lex.l
	gcc lex.yy.c -o al
=======
	lex lex.l
	gcc lex.c -o lex.out

execute:
	make all
	./lex.out input.al
>>>>>>> 80ceaa3e2674001240f954f8bb0f8d19bf2c1893
