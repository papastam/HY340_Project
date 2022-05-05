### csd4273, csd4275, csd4569 ###

### directories ###
SRCD   = src
SRCD1  = $(SRCD)/phase1
SRCD2  = $(SRCD)/phase2and3
SRCD3  = $(SRCD)/phase2and3
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

.PHONY: clear_screen clean testp1 all

### project phases ###

######################################################

$(P2OUT): $(OBJD)/symtable.o $(OBJD)/$(P2OUT).o $(OBJD)/$(P1OUT).o $(OBJD)/utils.o
	$(CC) -I$(SRCD2)/ $^ -o $(P2OUT)
	@echo -e "\e[1;32mDONE\e[0m"

$(OBJD)/$(P1OUT).o: $(SRCD)/phase1/lex_analyzer.l
	flex $<
	$(CC) $(CFLAGS) -I$(SRCD2) $(LEXC).c -o $@
	@rm $(LEXC).c
	@echo -e "\e[1;32mLexer Compiled\e[0m\n"

$(OBJD)/utils.o: $(SRCD)/phase2and3/utils.c
	$(CC) $(CFLAGS) $< -o $@

$(OBJD)/symtable.o: $(SRCD2)/symtable.c
	$(CC) $(CFLAGS) $< -o $@

$(OBJD)/$(P2OUT).o: $(SRCD2)/bison_parser.y
	bison --yacc --defines --output=$(SRCD2)/$(P2OUT).c -v $<
	$(CC) $(CFLAGS) $(SRCD2)/$(P2OUT).c -o $@
	@echo -e "\e[1;32mParser Compiled\e[0m\n"

######################################################

all: $(P2OUT) stt

### testing ###

stt: $(SRCD2)/symtable.c $(TESTSD)/etc/hashmap_test_main.c
	$(CC) -ggdb -std=gnu11 $^ -o $@

testp1: $(P2OUT) clear_screen
	@for test in $(TESTS1); \
		do \
		echo "\e[1;91m=========================================================================\e[0m"; \
		echo "\e[32m./$(P1OUT) $$test\e[0m"; \
		./$(P1OUT) $$test; \
		done

testp2: $(P2OUT) clear_screen
	@for test in $(TESTS2); \
		do \
		echo "\e[1;91m=========================================================================\e[0m"; \
		echo "\e[32m./$(P1OUT) $$test\e[0m"; \
		./$(P2OUT) $$test; \
		done

cp: $(P2OUT)
	./$(P2OUT) $(TESTSD)/phase2/testpap.asc

clear_screen:
	@echo -e "\e[2J"

clean:
	-rm $(SRCD2)/$(P2OUT).*
	-rm $(P2OUT)
	-rm $(OBJD)/*
