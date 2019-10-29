all : dph cons prod my call
dph : doh.c
    gcc -g doh.c -o -lpthread
cons : cons.c
    gcc -g cons.c -o -lpthread
prod : prod.c
    gcc -g prod.c -o -lpthread
mycall : mycall.c
    gcc -g mycall.c -o
clean:
    -rm -f *.o