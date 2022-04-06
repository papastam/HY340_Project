### csd4273, csd4275, csd4569 ###

### directories ###
SRCD   = src
INCD   = inc/
OBJD   = obj
TESTSD = tests

### names ###
LEXC = lex

P1OUT = al
P2OUT = parser

TESTS1 = $(shell find $(TESTSD)/phase1 -name 'test*')
TESTS2 = $(shell find $(TESTSD)/phase2 -name 'test*')

CFLAGS = -I$(INCD) -c -std=gnu11 -ggdb # TODO: remove debug

.PHONY: clear_screen clean testp1

### project phases ###

######################################################

acomp: $(OBJD)/$(P2OUT).o $(OBJD)/$(P1OUT).o
	$(CC) -I$(SRCD)/phase2/ $^ -o $(P2OUT)
	@echo "\e[1;32mDONE\e[0m"

$(OBJD)/$(P1OUT).o: $(SRCD)/phase1/lex_analyzer.l
	flex $<
	$(CC) $(CFLAGS) -Isrc/phase2 $(LEXC).c -o $@
	@rm $(LEXC).c
	@echo "\033[1;32mLexer Compiled\033[0m\n"

$(OBJD)/$(P2OUT).o: $(SRCD)/phase2/bison_parser.y
	bison --yacc --defines --output=$(SRCD)/phase2/$(P2OUT).c $<
	$(CC) $(CFLAGS) $(SRCD)/phase2/$(P2OUT).c -o $@
	@echo "\e[1;32mParser Compiled\e[0m\n"

######################################################

### testing ###

stt: $(SRCD)/phase2/symtable.c $(TESTSD)/etc/hashmap_test_main.c
	$(CC) -ggdb -std=gnu11 $^ -o $@

testp1: acomp clear_screen
	@for test in $(TESTS1); \
		do \
		echo "\e[1;91m=========================================================================\e[0m"; \
		echo "\e[32m./$(P1OUT) $$test\e[0m"; \
		./$(P1OUT) $$test; \
		done

testp2: acomp clear_screen
	@for test in $(TESTS2); \
		do \
		echo "\e[1;91m=========================================================================\e[0m"; \
		echo "\e[32m./$(P1OUT) $$test\e[0m"; \
		./$(P2OUT) $$test; \
		done

clear_screen:
	@echo "\e[2J"

clean:
	-rm $(SRCD)/phase2/$(P2OUT).*
	-rm $(P2OUT)
	-rm $(OBJD)/*
	-rm stt 
