
// main.cpp
// #include "base.h"

int main() {
    return foo(40) == 42;
}

// base.h
int foo(int x);


// base_a.cpp
int foo(int x) {
    return x + 1;
}


// base_b.cpp
int foo(int x) {
    return 42;
}

// Makefile 
all: base_a base_b

base_a: main.o base_a.o
    $(CC) main.o base_a.o -o base_a

base_b: main.o base_b.o
    $(CC) main.o base_b.o -o base_b

*.o:
    $(CC) -c %.cpp -o %.o