SRCD=src
INCD=inc
OBJD=obj
BIND=bin

LEXOUT=lex
P1OUT=al
P2OUT=acomp
P4OUT=avm

CFLAGS = -I$(INCD)/parser/ -I$(INCD)/vm/ -c -std=gnu11 -ggdb#TODO: remove -ggdb in release

__P2OBJ = symtable.o utils.o stack.o $(P2OUT).o $(P1OUT).o target_code_generator.o debug_functions.o
P2OBJ = $(patsubst %, $(OBJD)/parser/%, $(__P2OBJ))

__P4OBJ = alphavm.o
P4OBJ = $(patsubst %, $(OBJD)/vm/%, $(__P4OBJ))

.PHONY: dirs clear_screen clean all

all: dirs bin/$(P2OUT) bin/$(P4OUT)


dirs:
	@mkdir -p obj/
	@mkdir -p obj/parser/
	@mkdir -p obj/vm/
	@mkdir -p bin/

$(OBJD)/parser/$(P1OUT).o: $(SRCD)/parser/lex_analyzer.l
	flex $<
	$(CC) $(CFLAGS) -I$(SRCD)/parser $(LEXOUT).c -o $@
	@rm $(LEXOUT).c
	@echo -e "\e[1;32mLEXICAL ANALYZER COMPILED\e[0m\n"

$(OBJD)/parser/$(P2OUT).o: $(SRCD)/parser/bison_parser.y
	bison --yacc --defines --output=$(SRCD)/parser/$(P2OUT).c -v $< #--debug
	$(CC) $(CFLAGS) $(SRCD)/parser/$(P2OUT).c -o $@
	@echo -e "\e[1;32mPARSER COMPILED\e[0m\n"

$(BIND)/$(P2OUT): $(P2OBJ)
	$(CC) -I$(INCD) $^ -o $@
	@echo -e "\e[1;32mDONE\e[0m"

$(OBJD)/parser/%.o: $(SRCD)/parser/%.c $(INCD)/parser/%.h
	$(CC) $(CFLAGS) $< -o $@

##################################################################################

$(BIND)/$(P4OUT): $(P4OBJ)
	$(CC) -I$(INCD) $^ -o $@

$(OBJD)/vm/%.o: $(SRCD)/vm/%.c $(INCD)/vm/%.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm $(SRCD)/parser/$(P2OUT).c
	-rm $(SRCD)/parser/$(P2OUT).h
	-rm $(BIND)/$(P2OUT)
	-rm $(BIND)/$(P4OUT)
	-rm $(OBJD)/parser/*.o
	-rm $(OBJD)/vm/*.o
	-rm output.txt

cp: all
	./bin/parser/parser tests/phase3/testpap.asc
