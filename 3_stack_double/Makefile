stack_double: stack_double_hash.o stack_double_verify.o stack_double_funcs.o stack_double_main.o
	gcc stack_double_hash.o stack_double_verify.o stack_double_funcs.o stack_double_main.o -o stack_double

stack_double_hash.o: stack_double_hash.cpp
	gcc -c stack_double_hash.cpp -o stack_double_hash.o

stack_double_verify.o: stack_double_verify.cpp
	gcc -c stack_double_verify.cpp -o stack_double_verify.o

stack_double_funcs.o: stack_double_funcs.cpp
	gcc -c stack_double_funcs.cpp -o stack_double_funcs.o

stack_double_main.o: stack_double_main.cpp
	gcc -c stack_double_main.cpp -o stack_double_main.o

clean:
	rm -f *.o stack_double