# Alpha Compiler

For the project of [HY340](https://www.csd.uoc.gr/~hy340/) (@[CSD](https://www.csd.uoc.gr/)) we created a compiler intended for the alpha programming language, and a virtual machine (Implemented in C) wich runs out generated target code.

## Project Stracture

The project contains the following directories

* inc *(The header files used)*
  + parser
  + vm
* pdfs *(The course's pdfs)*
* src *(The source directory of the project)*
  + parser *(lexer, parser and intermidiate/target code generator)*
  + vm *(Virtual machine in C intended for our parser's target code)*
* tests *(some example testfiles)* 

## Compiling the project
* First of all, you should compile the project using the `make` command<br>
* The `./bin` directory should have been created, containing two executables: `acomp` and `avm`. This sohould mean the project has compiled succesfully! (Addidtional information about the compilation process can be found in the terminal)
* After the project is compiled you can __compile and run__ your alpha code files by using the make rule `make <input file>.asc`

## Runing the Compiler
The compiler executable syntax is as followed:
```bash
./bin/acmop <input file>
```
Our compiler creates three files:
* output.txt (Contains the easily readable quads)
* alpha.out (Binary file intended for the virtual machine)
* output_comparison/parser_generated.txt (A readable version from the contents of the binary file as the parser genrated it)

## Running the Virtual Machine
The virtual machine executable syntax is as followed:
```bash
./bin/avm <input file (alpha.out)>
```
Our virtual machine creates:
* output_comparison/vm_parsed.txt (A readable version from the contents of the binary file as the virtual macined parsed it)

## Demonstration
You can run *(Compile and Run)* all the original testfiles by using the following make rule:
```bash
make tests
```

## Alpha programming language syntax
Specifics about the alpha language syntax can be found on [pdfs/assignments/2_syntax_analysis.pdf](https://github.com/papastam/HY340_Project/blob/master/pdfs/assignments/2_syntax_analysis.pdf)

The Alpha language grammar is as follows:
```
program     ->  stmt*
stmt        ->  expr ;
                | ifstmt
                | whilestmt
                | forstmt
                | returnstmt
                | break ;
                | continue;
                | block
                | funcdef
                |;

expr        ->  assignexpr
                | expr + expr
                | expr - expr
                | expr * expr
                | expr / expr
                | expr % expr
                | expr > expr
                | expr >= expr
                | expr < expr
                | expr <= expr
                | expr == expr
                | expr != expr
                | expr and expr
                | expr or expr
                | term

term        ->  ( expr )
                | - expr
                | not expr
                | ++lvalue
                | lvalue++
                | --lvalue
                | lvalue--
                | primary

assginexpr  ->  lvalue = expr

primary     ->  lvalue
                | call
                | objectdef
                | ( funcdef )
                | const

lvalue      ->  id
                | local id
                | :: id
                | member

member      ->  lvalue . id
                | lvalue [ expr ]
                | call . id
                | call [ expr ]

call        ->  call ( elist )
                | lvalue callsuffix
                | ( funcdef) ( elist )

callsuffix  ->  normcall
                | methodcall

normcall    ->  ( elist )

methodcall  ->  .. id ( elist ) // equivalent to lvalue.id(lvalue, elist)

elist       ->  [ expr [, expr] * ]

objectdef   ->  [ [elist | indexed] ]
indexed     ->  [indexedelem [, indexedelem] * ]
indexedelem ->  { expr : expr }

block       ->  { [stmt*] }
funcdef     ->  function [id] (idlist) block

const       ->  number | string | nil | true | false
idlist      ->  [id [, id] * ]

ifstmt      ->  if ( expr ) stmt [ else stmt ]

whilestmt   ->  while ( expr ) stmt

forstmt     ->  for ( elist; expr; elist) stmt
returnstmt  -> return [expr];
```

## Debugging

### Debugging the compiler
In order for the compiler to print debug information on the terminal, tou have to set yydebug to 1 at `src/parser/bison_parser.y:1308`.<br>
While compiling, the compiler will display reduction information.

### Debugging the Virtual Machine
To debug the VM, you have to set AVMDEBUG definition to 1 at `src/vm/alphavm.h:17` That way, the virtual machine will display execution details in the terminal.

## Co owners

[Orestis Chiotakis](https://github.com/chiotak0)<br>
[Dimitris Bisias](https://github.com/dbisias)