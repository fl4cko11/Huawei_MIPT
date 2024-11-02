list: list_funcs.o list_visual.o list_main.o
	gcc list_funcs.o list_visual.o list_main.o -o list

list_funcs.o: list_funcs.cpp
	gcc -c list_funcs.cpp -o list_funcs.o

list_visual.o: list_visual.cpp
	gcc -c list_visual.cpp -o list_visual.o

list_main.o: list_main.cpp
	gcc -c list_main.cpp -o list_main.o

clean:
	rm -f *.o list