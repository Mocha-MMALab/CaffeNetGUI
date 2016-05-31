INCLUDE_FLAG = -I../../LayerLib/LayerLib
EXTRA_CFLAGS = 
CC=g++
AR=ar
INC= -I../../NNLib/NNLib -I../../LayerLib/LayerLib
LIBS = -L../../LayerLib/LayerLib -lLayers
all :
	$(CC) -std=c++11 -fPIC -c -w *.cpp $(EXTRA_CFLAGS) $(INCLUDE_FLAG) $(INC) $(LIBS)
	$(CC) -std=c++11 -shared -o libNN.so *.o  $(EXTRA_CFLAGS) $(INCLUDE_FLAG) $(INC) $(LIBS)
	$(AR)  rcs libNN.a 	*.o 

	$(CC) -c main.cpp -lNN $(INC)
	
	$ cp ./libNN.a ../../Mocha/MMALib/lib
	$ cp ./libNN.so ../../Mocha/MMALib/bin
	$ sudo cp ./libNN.so /usr/lib
clean:
	rm -f libNN.so
	rm -f libNN.a
	rm -f test_main
	rm -f *.o
