SRCD=src
INCD=inc
OBJD=obj
BIND=bin

LEXOUT=lex
P1OUT=al
P3OUT=acomp
P5OUT=avm

CFLAGS = -I$(INCD)/parser/ -I$(INCD)/vm/ -c -std=gnu11 -ggdb#TODO: remove -ggdb in release

__P2OBJ = symtable.o utils.o stack.o $(P3OUT).o $(P1OUT).o target_code_generator.o debug_functions.o
P2OBJ = $(patsubst %, $(OBJD)/parser/%, $(__P2OBJ))

__P4OBJ = alphavm.o
P4OBJ = $(patsubst %, $(OBJD)/vm/%, $(__P4OBJ))

.PHONY: dirs clear_screen clean build

build: dirs $(P3OUT) $(P5OUT)


dirs:
	@mkdir -p obj/
	@mkdir -p obj/parser/
	@mkdir -p obj/vm/
	@mkdir -p bin/

$(P3OUT): dirs $(BIND)/$(P3OUT)

$(P5OUT): dirs $(BIND)/$(P5OUT)

###########################################################################################

$(OBJD)/parser/$(P1OUT).o: $(SRCD)/parser/lex_analyzer.l
	@printf "\e[1mbuilding:\e[0m \e[1;91m%s\e[0m [\e[4m%s\e[0m] \e[0m---\n" $@ $< #TODO: fix
	@flex $<
	@$(CC) $(CFLAGS) -I$(SRCD)/parser $(LEXOUT).c -o $@
	@rm $(LEXOUT).c


$(OBJD)/parser/$(P3OUT).o: $(SRCD)/parser/bison_parser.y
	@printf "\e[1mbuilding:\e[0m \e[1;91m%s\e[0m [\e[4m%s\e[0m] \e[0m---\n" $@ $< #TODO: fix
	bison --yacc --defines --output=$(SRCD)/parser/$(P3OUT).c -v $< #--debug
	@$(CC) $(CFLAGS) $(SRCD)/parser/$(P3OUT).c -o $@


$(BIND)/$(P3OUT): $(P2OBJ)
	$(CC) -I$(INCD) $^ -o $@


$(OBJD)/parser/%.o: $(SRCD)/parser/%.c $(INCD)/parser/%.h
	@printf "\e[1mbuilding:\e[0m \e[1;91m%s\e[0m [\e[4m%s\e[0m / \e[4m%s\e[0m] \e[1m---" $@ $(word 1, $^) $(word 2, $^)
	@$(CC) $(CFLAGS) $< -o $@ 2>> .compile_errors.txt;\
	if [ $$? -eq 0 ]; then\
		printf "\e[92m SUCCESS\e[0m\n";\
	else\
		printf "\e[1;31m FAILURE\e[0;3m\n\n";\
		cat .compile_errors.txt;\
		printf "\n\e[0m";\
		truncate --size=0 .compile_errors.txt;\
	fi

##################################################################################

$(BIND)/$(P5OUT): $(P4OBJ)
	$(CC) -I$(INCD) $^ -o $@


$(OBJD)/vm/%.o: $(SRCD)/vm/%.c $(INCD)/vm/%.h
	@printf "\e[1mbuilding:\e[0m \e[1;91m%s\e[0m [%s / %s] \e[1m---" $@ $(word 1, $^) $(word 2, $^)
	@$(CC) $(CFLAGS) $< -o $@ 2>> .compile_errors.txt;\
	if [ $$? -eq 0 ]; then\
       		printf "\e[92m SUCCESS\e[0m\n";\
	else\
		printf "\e[1;31m FAILURE\e[0;3m\n\n";\
		cat .compile_errors.txt;\
		printf "\n\e[0m";\
		truncate --size=0 .compile_errors.txt;\
	fi


clean:
	-rm $(SRCD)/parser/$(P3OUT).c
	-rm $(SRCD)/parser/$(P3OUT).h
	-rm $(BIND)/$(P3OUT)
	-rm $(BIND)/$(P5OUT)
	-rm $(OBJD)/parser/*.o
	-rm $(OBJD)/vm/*.o
	-rm output.txt
	-rm target_code.txt

cp: build
	./bin/$(P3OUT) tests/phase4/testpap.asc

bis: build	
	./bin/$(P3OUT) tests/phase4/testbis.asc	
