all : dph cons prod mycall
dph : dph.c
    gcc -g dph.c -o -lpthread
cons : cons.c
    gcc -g cons.c -o -lpthread
prod : prod.c
    gcc -g prod.c -o -lpthread
mycall : mycall.c
    gcc -g mycall.c -o
clean:
    -rm -f *.o
