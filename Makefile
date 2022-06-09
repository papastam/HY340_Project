SRCD=src
INCD=inc
OBJD=obj
BIND=bin

LEXOUT=lex
P1OUT=al
P4OUT=acomp
P5OUT=avm

CFLAGS = -I$(INCD)/parser/ -I$(INCD)/vm/ -c -std=gnu11 -ggdb #TODO: remove -ggdb in release and add -O2

__P4OBJ = symtable.o utils.o stack.o $(P4OUT).o $(P1OUT).o target_code_generator.o debug_functions.o
P4OBJ = $(patsubst %, $(OBJD)/parser/%, $(__P4OBJ))

__P5OBJ = alphavm.o mman.o exec.o vmutils.o
P5OBJ = $(patsubst %, $(OBJD)/vm/%, $(__P5OBJ))

.PHONY: dirs clear_screen clean build

build: dirs $(P4OUT) $(P5OUT)


dirs:
	@mkdir -p obj/
	@mkdir -p obj/parser/
	@mkdir -p obj/vm/
	@mkdir -p bin/

$(P4OUT): dirs $(BIND)/$(P4OUT)

$(P5OUT): dirs $(BIND)/$(P5OUT)

###########################################################################################

$(OBJD)/parser/$(P1OUT).o: $(SRCD)/parser/lex_analyzer.l
	@printf "\e[1mbuilding:\e[0m \e[1;91m%s\e[0m [\e[4m%s\e[0m] \e[0m---\n" $@ $< #TODO: fix
	@flex $<
	@$(CC) $(CFLAGS) -I$(SRCD)/parser $(LEXOUT).c -o $@
	@rm $(LEXOUT).c


$(OBJD)/parser/$(P4OUT).o: $(SRCD)/parser/bison_parser.y
	@printf "\e[1mbuilding:\e[0m \e[1;91m%s\e[0m [\e[4m%s\e[0m] \e[0m---\n" $@ $< #TODO: fix
	bison --yacc --defines --output=$(SRCD)/parser/$(P4OUT).c -v $< #--debug
	@$(CC) $(CFLAGS) $(SRCD)/parser/$(P4OUT).c -o $@


$(BIND)/$(P4OUT): $(P4OBJ)
	@printf "\e[1mbuilding:\e[0m \e[1;33m%s\e[0m [" $@
	@for i in $^; do\
		printf "\e[4m%s\e[0m / " $$i;\
	done
	@printf "\b\b] ---"
	@$(CC) -I$(INCD) $^ -o $@;\
	if [ $$? -eq 0 ]; then\
		printf " \e[1;4;92mSUCCESS\e[0m\n";\
	else\
		printf " \e[1;4;31mFAILURE\e[0;3m\n\n";\
		cat .compile_errors.txt;\
		printf "\n\e[0m";\
		truncate --size=0 .compile_errors.txt;\
	fi


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

$(BIND)/$(P5OUT): $(P5OBJ)
	@printf "\e[1mbuilding:\e[0m \e[1;33m%s\e[0m [" $@
	@for i in $^; do\
		printf "\e[4m%s\e[0m / " $$i;\
	done
	@printf "\b\b] ---"
	@$(CC) -I$(INCD) $^ -o $@;\
	if [ $$? -eq 0 ]; then\
		printf " \e[1;4;92mSUCCESS\e[0m\n";\
	else\
		printf " \e[1;4;31mFAILURE\e[0;3m\n\n";\
		cat .compile_errors.txt;\
		printf "\n\e[0m";\
		truncate --size=0 .compile_errors.txt;\
	fi


$(OBJD)/vm/%.o: $(SRCD)/vm/%.c $(INCD)/vm/%.h
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


clean:
	-rm $(SRCD)/parser/$(P4OUT).c
	-rm $(SRCD)/parser/$(P4OUT).h
	-rm $(BIND)/$(P4OUT)
	-rm $(BIND)/$(P5OUT)
	-rm $(OBJD)/parser/*.o
	-rm $(OBJD)/vm/*.o
	-rm output.txt
	-rm target_code.txt

cp: build
	./bin/$(P4OUT) tests/phase4/testpap.asc

bis: build	
	./bin/$(P4OUT) tests/phase4/testbis.asc	
