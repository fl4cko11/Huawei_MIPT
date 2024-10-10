asm: spu_asm_main.o
	gcc spu_asm_main.o -o asm

spu_asm_main.o: /home/vlados/GitRepos/Huawei/SPU/spu_asm/spu_asm_main.cpp
	gcc -c /home/vlados/GitRepos/Huawei/SPU/spu_asm/spu_asm_main.cpp -o spu_asm_main.o

calc_int: stack_int_hash.o stack_int_verify.o stack_int_funcs.o spu_calc.o spu_calc_main.o
	gcc stack_int_hash.o stack_int_verify.o stack_int_funcs.o spu_calc.o spu_calc_main.o -o calc_int -lm

stack_int_hash.o: /home/vlados/GitRepos/Huawei/stack_int/stack_int_hash.cpp
	gcc -c /home/vlados/GitRepos/Huawei/stack_int/stack_int_hash.cpp -o stack_int_hash.o

stack_int_verify.o: /home/vlados/GitRepos/Huawei/stack_int/stack_int_verify.cpp
	gcc -c /home/vlados/GitRepos/Huawei/stack_int/stack_int_verify.cpp -o stack_int_verify.o

stack_int_funcs.o: /home/vlados/GitRepos/Huawei/stack_int/stack_int_funcs.cpp
	gcc -c /home/vlados/GitRepos/Huawei/stack_int/stack_int_funcs.cpp -o stack_int_funcs.o

spu_calc.o: /home/vlados/GitRepos/Huawei/SPU/spu_calc/spu_calc.cpp
	gcc -c /home/vlados/GitRepos/Huawei/SPU/spu_calc/spu_calc.cpp -o spu_calc.o

spu_calc_main.o: /home/vlados/GitRepos/Huawei/SPU/spu_calc/spu_calc_main.cpp
	gcc -c /home/vlados/GitRepos/Huawei/SPU/spu_calc/spu_calc_main.cpp -o spu_calc_main.o

clean:
	rm -f *.o asm calc_int