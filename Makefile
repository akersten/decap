all:
	gcc -fPIC -g -c -Wall src/*.c
	mkdir lib
	gcc -shared *.o -o lib/libdecap.so

clean:
	rm -f lib/*.so
	rmdir lib
	rm -f *.o

