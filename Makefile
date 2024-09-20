quadro_solution: quadro.cpp
	gcc quadro.cpp -o quadro_solution -lm

quadro_tests: quadro_tests.cpp
	gcc quadro_tests.cpp -o quadro_tests -lm