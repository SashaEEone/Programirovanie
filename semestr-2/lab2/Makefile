all: program

program: libstatic.a
	gcc src/main.c -I ./include -L. -lstatic -o program

libstatic.a: student.o
	ar rcs libstatic.a student.o

student.o: src/student.c
	gcc -c src/student.c -o student.o -I ./include

clean:
	rm -rf *.o *.a program

run: all
	./program
