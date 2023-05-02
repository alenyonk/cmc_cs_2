all: program

file1.c: fileh.h

file1.o: file1.c
	gcc -m32 -c -o file1.o file1.c

file2.o: file2.asm
	nasm -f elf32 -o file2.o file2.asm

program: file 1.o file2.o
	gcc -m32 -o program file1.o file 2.o -lm

clean:
	rm -rf file1.o file2.o 
		
