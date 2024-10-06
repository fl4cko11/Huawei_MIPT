qs: solver.o in_out.o quadro_main.o
	gcc solver.o in_out.o quadro_main.o -o qs -lm

qt: solver.o quadro_tests.o
	gcc solver.o quadro_tests.o -o qt -lm

in_out.o: in_out.cpp
	gcc -c in_out.cpp -o in_out.o

quadro_main.o: quadro_main.cpp
	gcc -c quadro_main.cpp -o quadro_main.o

solver.o: solver.cpp
	gcc -c solver.cpp -o solver.o

quadro_tests.o: quadro_tests.cpp
	gcc -c quadro_tests.cpp -o quadro_tests.o

clean:
	rm -f *.o qt qs