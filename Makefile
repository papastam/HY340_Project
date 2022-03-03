### csd4273, csd4275, csd4569 ###

### directories ###
SRCD   = src
INCD   = inc
TESTSD = tests

### names ###
LEXC   = lex.yy.c
P1OUT  = al
TESTS1 = $(shell find $(TESTSD)/phase1 -name 'test*')



### project phases ###

all: phase1

phase1:
	flex $(SRCD)/$@/lex_analyzer.l
	$(CC) -I$(INCD) $(LEXC) -o $(P1OUT)
	@rm $(LEXC)

#phase2:



### testing ###

testp1: all
	@for test in $(TESTS1); \
		do \
		echo "\e[1;91m=========================================================================\e[0m"; \
		echo "\e[32m./$(P1OUT) $$test\e[0m"; \
		./$(P1OUT) $$test; \
		done


clean:
	-rm $(LEXC)
	-rm al
