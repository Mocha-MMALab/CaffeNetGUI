# Mocha install step

## Install cuda
```css
1.  Download cuda at https://developer.nvidia.com/cuda-toolkit

2.$ sudo dpkg -i cuda-repo-ubuntu1504-7-5-local_7.5-18_amd64.deb
3.$ sudo apt-get update
4.$ sudo apt-get install cuda
```

## Install cudnn(optional)
```css
1.  Download cudnn at https://developer.nvidia.com/rdp/cudnn-download
2.$ cd to cudnn lib64 folder
3.$ sudo cp lib* /usr/local/cuda/lib64/
4.$ cd to cudnn include foolder
5.$ sudo cp cudnn.h /usr/local/cuda/include/
```

## Install Qt Creator
```css
1.  Download QtCreator at http://www.qt.io/download-open-source/
2.  Direct install
```

## Install OpenCV(optional)
```css
1.  Download OpenCV at http://opencv.org/
2.$ cd OpenCV folder
3.$ mkdir build
4.$ cd ./build
5.$ cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local ..
6.$ make
7.$ sudo make install
8.$ sudo ldconfig
```

## QMake Qwt
```css
1.  Unzip Qwt.zip
2.  Use Qt Creator qmake qwt.pro
3.  Copy libqwt.so.* in Qwt lib folder to ./Mocha/Qwt/bin
    (Please create a folder ,when folder does not exist)
4.$ run ./install.sh
5.  Use Qt build Mocha.pro
```

## Suggest
```css
Ubuntu v15.04
OpenCV v3.1.0
caffe v0.14.5
cuDNN v4.0.7
cuda v7.5
QtCreator v5.6.0
```

## Note  
When only cpu, perform the following actions
```css
1.  Open ./CaffeToolsLib/caffe/Makefile.config
2.  Cancel comment CPU_ONLY := 1
```
