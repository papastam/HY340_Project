### csd4273, csd4275, csd4569 ###

### directories ###
SRCD   = src
INCD   = inc
OBJD   = obj
TESTSD = tests

### names ###
LEXC   = lex.yy.c
P1OUT  = al
TESTS1 = $(shell find $(TESTSD)/phase1 -name 'test*')

CFLAGS = -I$(INCD) -c

### project phases ###

all: $(P1OUT)

$(P1OUT): $(OBJD)/$(P1OUT).o
	$(CC) $< -o $(P1OUT)
	@echo "\e[1;32mDONE\e[0m"

$(OBJD)/$(P1OUT).o: $(SRCD)/phase1/lex_analyzer.l
	flex $<
	$(CC) $(CFLAGS) $(LEXC) -o $@
	@rm $(LEXC)


#phase2:



### testing ###

testp1: clear_screen
	@for test in $(TESTS1); \
		do \
		echo "\e[1;91m=========================================================================\e[0m"; \
		echo "\e[32m./$(P1OUT) $$test\e[0m"; \
		./$(P1OUT) $$test; \
		done

clear_screen:
	@echo "\e[2J"

clean:
	@rm al
	@rm $(OBJD)/*
