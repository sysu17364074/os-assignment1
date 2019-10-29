all : doh cons prod 
dph : doh.c
    gcc -g doh.c -o -lpthread
cons : cons.c
    gcc -g cons.c -o -lpthread
prod : prod.c
    gcc -g prod.c -o -lpthread
clean:
    -rm -f *.o