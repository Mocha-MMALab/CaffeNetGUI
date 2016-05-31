INCLUDE_FLAG =
EXTRA_CFLAGS = 
CC=g++
AR=ar

all :
	$(CC) -std=c++11 -fPIC -c -w *.cpp $(EXTRA_CFLAGS) $(INCLUDE_FLAG)
	$(CC) -std=c++11 -shared -o libLayers.so *.o  $(EXTRA_CFLAGS) $(INCLUDE_FLAG)
	$(AR) rcs libLayers.a 	*.o

	$(CC) -o test_main ./test/main.cpp libLayers.a

	$ cp ./libLayers.a ../../Mocha/MMALib/lib
	$ cp ./libLayers.so ../../Mocha/MMALib/bin
	$ sudo cp ./libLayers.so /usr/lib
clean:
	rm -f libLayers.so
	rm -f libLayers.a
	rm -f test_main
	rm -f *.o
