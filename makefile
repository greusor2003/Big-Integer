all: main factorial test_nchoosek

main:
	make -f makefile_main

factorial:
	make -f makefile_factorial

test_nchoosek:
	make -f makefile_test_nchoosek

clean:
	rm *.o factorial main test_nchoosek
