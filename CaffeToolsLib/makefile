INCLUDEPATH += -I./caffe/include \
               -I./caffe/build/src \
               -I/usr/include/hdf5/serial \
               -I/usr/local/cuda/targets/x86_64-linux/include

LIBS += -L/usr/lib/x86_64-linux-gnu/ -lboost_system \
        -L/usr/lib/x86_64-linux-gnu/ -lglog \
        -L/usr/lib/x86_64-linux-gnu/ -lprotobuf \
        -L/usr/lib/x86_64-linux-gnu/ -lgflags \
        -L/usr/local/cuda/lib64/ -lcudart \
	-L./caffe/build/lib/ -lcaffe

CC=g++
AR=ar

all :
	$(CC) -std=c++11 -fPIC -c -w *.cpp $(LIBS) $(INCLUDEPATH)
	$(CC) -std=c++11 -shared -o libCaffeTools.so *.o $(LIBS) $(INCLUDEPATH)
	$(AR) rcs libCaffeTools.a *.o

	$ cp ./libCaffeTools.a ../Mocha/MMALib/lib
	$ cp ./libCaffeTools.so ../Mocha/MMALib/bin
	$ sudo cp ./libCaffeTools.so /usr/lib
clean:
	rm -f libCaffeTools.so
	rm -f libCaffeTools.a
	rm -f *.o
