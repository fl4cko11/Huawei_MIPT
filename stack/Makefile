stack: stack_hash.o stack_verify.o stack_funcs.o stack_main.o
	gcc stack_hash.o stack_verify.o stack_funcs.o stack_main.o -o stack

stack_hash.o: stack_hash.cpp
	gcc -c stack_hash.cpp -o stack_hash.o

stack_verify.o: stack_verify.cpp
	gcc -c stack_verify.cpp -o stack_verify.o

stack_funcs.o: stack_funcs.cpp
	gcc -c stack_funcs.cpp -o stack_funcs.o

stack_main.o: stack_main.cpp
	gcc -c stack_main.cpp -o stack_main.o

clean:
	rm -f *.o stack