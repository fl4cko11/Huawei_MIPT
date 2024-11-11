akinator: akinator_funcs.o akinator_visual.o akinator_main.o
	gcc akinator_funcs.o akinator_visual.o akinator_main.o -o akinator

akinator_funcs.o: akinator_funcs.cpp
	gcc -c akinator_funcs.cpp -o akinator_funcs.o

akinator_visual.o: akinator_visual.cpp
	gcc -c akinator_visual.cpp -o akinator_visual.o

akinator_main.o: akinator_main.cpp
	gcc -c akinator_main.cpp -o akinator_main.o

clean:
	rm -f *.o akinator