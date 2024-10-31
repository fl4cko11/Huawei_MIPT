asm: spu_asm_funcs.o spu_asm_main.o
	gcc spu_asm_funcs.o spu_asm_main.o -o asm

spu_asm_funcs.o: spu_asm/spu_asm_funcs.cpp
	gcc -c spu_asm/spu_asm_funcs.cpp -o spu_asm_funcs.o

spu_asm_main.o: spu_asm/spu_asm_main.cpp
	gcc -c spu_asm/spu_asm_main.cpp -o spu_asm_main.o

calc: stack_int_hash.o stack_int_verify.o stack_int_funcs.o spu_calc_funcs.o spu_calc_main.o
	gcc stack_int_hash.o stack_int_verify.o stack_int_funcs.o spu_calc_funcs.o spu_calc_main.o -o calc -lm

stack_int_hash.o: ../stack_int/stack_int_hash.cpp
	gcc -c ../stack_int/stack_int_hash.cpp -o stack_int_hash.o

stack_int_verify.o: ../stack_int/stack_int_verify.cpp
	gcc -c ../stack_int/stack_int_verify.cpp -o stack_int_verify.o

stack_int_funcs.o: ../stack_int/stack_int_funcs.cpp
	gcc -c ../stack_int/stack_int_funcs.cpp -o stack_int_funcs.o

spu_calc_funcs.o: spu_calc/spu_calc_funcs.cpp
	gcc -c spu_calc/spu_calc_funcs.cpp -o spu_calc_funcs.o

spu_calc_main.o: spu_calc/spu_calc_main.cpp
	gcc -c spu_calc/spu_calc_main.cpp -o spu_calc_main.o

clean:
	rm -f *.o asm calc