INCLUDE_FLAG =
EXTRA_CFLAGS = 
CC=g++
AR=ar
INC= -I../../SolverLib
LIBS =
all :
	$(CC) -std=c++11 -fPIC -c -w *.cpp $(EXTRA_CFLAGS) $(INCLUDE_FLAG) $(INC) $(LIBS)
	$(CC) -std=c++11 -shared -o libSolver.so *.o  $(EXTRA_CFLAGS) $(INCLUDE_FLAG) $(INC) $(LIBS)
	$(AR)  rcs libSolver.a 	*.o 

	$ cp ./libSolver.a ../Mocha/MMALib/lib
	$ cp ./libSolver.so ../Mocha/MMALib/bin
	$ sudo cp ./libSolver.so /usr/lib

clean:
	rm -f libSolver.so
	rm -f libSolver.a
	rm -f *.o
