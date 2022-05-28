### csd4273, csd4275, csd4569 ###

### directories ###
SRCD   = src
INCD   = inc
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

all: objdir $(P2OUT)

######################################################

$(P2OUT): $(OBJD)/symtable.o $(OBJD)/$(P2OUT).o $(OBJD)/$(P1OUT).o $(OBJD)/utils.o $(OBJD)/stack.o $(OBJD)/target_code_generator.o
	$(CC) -I$(SRCD2)/ $^ -o $(P2OUT)
	@echo -e "\e[1;32mDONE\e[0m"

objdir:
	@mkdir -p obj/

$(OBJD)/$(P1OUT).o: $(SRCD)/lex_analyzer.l
	flex $<
	$(CC) $(CFLAGS) -I$(SRCD) $(LEXC).c -o $@
	@rm $(LEXC).c
	@echo -e "\e[1;32mLexer Compiled\e[0m\n"

$(OBJD)/utils.o: $(SRCD)/utils.c
	$(CC) $(CFLAGS) $< -o $@

$(OBJD)/symtable.o: $(SRCD)/symtable.c
	$(CC) $(CFLAGS) $< -o $@

$(OBJD)/stack.o: $(SRCD)/stack.c
	$(CC) $(CFLAGS) $< -o $@


$(OBJD)/target_code_generator.o: $(SRCD)/target_code_generator.c
	$(CC) $(CFLAGS) $< -o $@

$(OBJD)/$(P2OUT).o: $(SRCD)/bison_parser.y
	bison --yacc --defines --output=$(SRCD)/$(P2OUT).c -v $< #--debug
	$(CC) $(CFLAGS) $(SRCD)/$(P2OUT).c -o $@
	@echo -e "\e[1;32mParser Compiled\e[0m\n"

######################################################

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
	./$(P2OUT) $(TESTSD)/phase3/testpap.asc

bis: $(P2OUT)
	./$(P2OUT) $(TESTSD)/phase3/testbis 

clear_screen:
	@echo -e "\e[2J"

clean:
	-rm $(SRCD)/$(P2OUT).*
	-rm $(P2OUT)
	-rm $(OBJD)/*
	-rm output.txt
