all:
	gcc -fPIC -g -c -Wall src/*.c
	mkdir -p lib
	gcc -shared *.o -o lib/libdecap.so
tests:
	gcc -g -o runtests test/*.c
	./runtests

clean:
	rm -f runtests
	rm -f lib/*.so
	if test -d lib; then rmdir lib;	fi

	rm -f *.o
