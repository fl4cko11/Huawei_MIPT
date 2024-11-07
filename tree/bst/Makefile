bst: bst_funcs.o bst_visual.o bst_main.o
	gcc bst_funcs.o bst_visual.o bst_main.o -o bst

bst_funcs.o: bst_funcs.cpp
	gcc -c bst_funcs.cpp -o bst_funcs.o

bst_visual.o: bst_visual.cpp
	gcc -c bst_visual.cpp -o bst_visual.o

bst_main.o: bst_main.cpp
	gcc -c bst_main.cpp -o bst_main.o

clean:
	rm -f *.o bst