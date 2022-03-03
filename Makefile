### csd4273, csd4275, csd4569 ###

### directories ###
SRCD   = src
TESTSD = tests

### names ###
LEXC   = lex.yy.c
P1OUT  = al
TESTS1 = $(shell find $(TESTSD)/phase1 -name 'test*')



### project phases ###

all: phase1

phase1:
	flex $(SRCD)/$@/lex_analyzer.l
	$(CC) $(LEXC) -o $(P1OUT)
	@rm $(LEXC)

#phase2:



### testing ###

testp1: all
	@for test in $(TESTS1); \
		do \
		echo '========================================================================='; \
		echo ./$(P1OUT) $$test; \
		./$(P1OUT) $$test; \
		done


clean:
	-rm al
