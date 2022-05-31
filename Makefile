SRCD=src
INCD=inc
OBJD=obj
BIND=bin

LEXOUT=lex
P1OUT=al
P2OUT=parser

CFLAGS = -I$(INCD)/parser/ -I$(INCD)/vm/ -c -std=gnu11 -ggdb#TODO: remove -ggdb in release

__P2OBJ = symtable.o utils.o stack.o $(P2OUT).o $(P1OUT).o target_code_generator.o
P2OBJ = $(patsubst %, $(OBJD)/parser/%, $(__P2OBJ))

.PHONY: clear_screen clean all

all: dirs $(P2OUT) end


dirs:
	@mkdir -p obj/
	@mkdir -p obj/parser/
	@mkdir -p obj/vm/
	@mkdir -p bin/
	@mkdir -p bin/parser/
	@mkdir -p bin/vm/

$(OBJD)/parser/$(P1OUT).o: $(SRCD)/parser/lex_analyzer.l
	flex $<
	$(CC) $(CFLAGS) -I$(SRCD)/parser $(LEXOUT).c -o $@
	@rm $(LEXOUT).c
	@echo -e "\e[1;32mLEXICAL ANALYZER COMPILED\e[0m\n"

$(OBJD)/parser/$(P2OUT).o: $(SRCD)/parser/bison_parser.y
	bison --yacc --defines --output=$(SRCD)/parser/$(P2OUT).c -v $< #--debug
	$(CC) $(CFLAGS) $(SRCD)/parser/$(P2OUT).c -o $@
	@echo -e "\e[1;32mPARSER COMPILED\e[0m\n"

$(P2OUT): $(P2OBJ)
	$(CC) -I$(INCD) $^ -o bin/parser/$@
	@echo -e "\e[1;32mDONE\e[0m"

$(OBJD)/parser/%.o: $(SRCD)/parser/%.c $(INCD)/parser/%.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm $(SRCD)/parser/$(P2OUT).c
	-rm $(BIND)/*
	-rm $(OBJD)/parser/*
	-rm $(OBJD)/vm/*
	-rm output.txt

end:
	@echo -e "\e[0m"
