quadro_solution: solver.o in_out.o quadro_main.o
	gcc solver.o in_out.o quadro_main.o -o quadro_solution -lm

quadro_tests: solver.o quadro_tests.o
	gcc solver.o quadro_tests.o -o quadro_tests -lm

in_out.o: in_out.cpp
	gcc -c in_out.cpp -o in_out.o

quadro_main.o: quadro_main.cpp
	gcc -c quadro_main.cpp -o quadro_main.o

solver.o: solver.cpp
	gcc -c solver.cpp -o solver.o

quadro_tests.o: quadro_tests.cpp
	gcc -c quadro_tests.cpp -o quadro_tests.o

clean:
	rm -f *.o quadro_tests quadro_solution