assembler: assembler.o error_handler.o export_handler.o helpers.o Instructions_functions.o main.o parser.o instructions_parser.o parser_data_image.o shared_data.o symbol_functions.o data_functions.o
	gcc -g -Wall -ansi -pedantic assembler.o data_functions.o error_handler.o export_handler.o helpers.o Instructions_functions.o main.o parser.o instructions_parser.o parser_data_image.o shared_data.o symbol_functions.o -o assembler

assembler.o: assembler.c assembler.h export_handler.h constants.h helpers.h
	gcc -ansi -pedantic -Wall -c assembler.c -o assembler.o

error_handler.o: error_handler.c error_handler.h constants.h
	gcc -ansi -pedantic -Wall -c error_handler.c -o error_handler.o

data_functions.o: data_functions.c data_functions.h Instructions_functions.h
	gcc -ansi -pedantic -Wall -c data_functions.c -o data_functions.o -lm

export_handler.o: export_handler.c export_handler.h data_functions.h
	gcc -ansi -pedantic -Wall -c export_handler.c -o export_handler.o

helpers.o: helpers.c helpers.h parser.h
	gcc -ansi -pedantic -Wall -c helpers.c -o helpers.o

Instructions_functions.o: Instructions_functions.c Instructions_functions.h symbol_functions.h
	gcc -ansi -pedantic -Wall -c Instructions_functions.c -o Instructions_functions.o

instructions_parser.o: instructions_parser.c instructions_parser.h helpers.h
	gcc -ansi -pedantic -Wall -c instructions_parser.c -o instructions_parser.o

main.o: main.c assembler.h
	gcc -ansi -pedantic -Wall -c main.c -o main.o

parser.o: parser.c parser.h data_functions.h helpers.h parser_data_image.h
	gcc -ansi -pedantic -Wall -c parser.c -o parser.o

parser_data_image.o: parser_data_image.c parser_data_image.h instructions_parser.h
	gcc -ansi -pedantic -Wall -c parser_data_image.c -o parser_data_image.o

shared_data.o: shared_data.c shared_data.h
	gcc -ansi -pedantic -Wall -c shared_data.c -o shared_data.o

symbol_functions.o: symbol_functions.c symbol_functions.h error_handler.h
	gcc -ansi -pedantic -Wall -c symbol_functions.c -o symbol_functions.o




