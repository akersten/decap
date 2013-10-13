all:
	gcc -fPIC -g -c -Wall src/*.c
	mkdir -p lib
	gcc -shared *.o -o lib/libdecap.so
tests:
	gcc -g -o runtests test/*.c src/*.c
	./runtests

libtests:
	gcc -g -Llib/ -ldecap -o runtestslinked test/*.c
	export LD_LIBRARY_PATH=lib/ ; \
	./runtestslinked

clean:
	rm -f runtests
	rm -f runtestslinked
	rm -f lib/*.so
	if test -d lib; then rmdir lib;	fi

	rm -f *.o
