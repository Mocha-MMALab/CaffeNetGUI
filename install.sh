#!/bin/bash

fileLocal=$(pwd)
processor=$(grep 'processor' /proc/cpuinfo | sort -u | wc -l)

LayerLibArray=(BaseLayer CommonLayerParam CommonLayers DataBlob 
DataLayerParam DataLayers LayerEnum LayerParam Layers LossLayerParam 
LossLayers NeuronLayerParam NeuronLayers VisionLayerParam VisionLayers)

NNLibArray=(NNModel)

SolverLibArray=(SolverEnum SolverParam Solver)

#install environmental dependency
sudo apt install build-essential libprotobuf-dev libleveldb-dev libsnappy-dev libopencv-dev libboost-all-dev libhdf5-serial-dev libgflags-dev libgoogle-glog-dev liblmdb-dev protobuf-compiler libatlas-base-dev libgl1-mesa-dev build-essential libgtk2.0-dev libjpeg-dev libtiff5-dev libjasper-dev libopenexr-dev cmake python-dev python-numpy python-tk libtbb-dev libeigen2-dev yasm libfaac-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev libvorbis-dev libxvidcore-dev libx264-dev libqt4-dev libqt4-opengl-dev sphinx-common texlive-latex-extra libv4l-dev libdc1394-22-dev libavcodec-dev libavformat-dev libswscale-dev libgtkglext1-dev libgtkgl2.0-dev libeigen3-dev python-numpy python-scipy python-matplotlib python-sklearn python-skimage python-h5py python-protobuf python-leveldb python-networkx python-nose python-pandas python-gflags Cython ipython protobuf-c-compiler protobuf-compiler python-pip git python-sympy ipython-notebook libyaml-cpp-dev libgflags-dev libgoogle-glog-dev libopencv-dev libleveldb-dev libsnappy-dev liblmdb-dev libhdf5-serial-dev libprotobuf-dev protobuf-compiler libatlas-base-dev python-dev python-pip python-numpy gfortran libboost-all-dev graphviz gunicorn

#link HDF5
cd /usr/lib/x86_64-linux-gnu
sudo ln -s libhdf5_serial.so.8.0.2 libhdf5.so
sudo ln -s libhdf5_serial_hl.so.8.0.2 libhdf5_hl.so

#make caffe
cd $fileLocal/CaffeToolsLib/caffe/build
cmake ..
make all -j$processor
make test -j$processor
make runtest -j$processor
make pycaffe -j$processor

#copy caffe.so to /usr/lib
cd $fileLocal/CaffeToolsLib/caffe/build/lib/
cp ./libcaffe.so.1.0.0-rc3 /usr/lib
cp ./libcaffe.so /usr/lib

#make LayerLib
cd $fileLocal/LayerLib/LayerLib
make clean -j$processor
make -j$processor

#copy LayerLib.h to Mocha/MMALib/include
for LayerLib in ${LayerLibArray[@]}; do
  cp ./$LayerLib.h $fileLocal/Mocha/MMALib/include
done

#make NNLib
cd $fileLocal/NNLib/NNLib
make clean -j$processor
make -j$processor

#copy NNLib.h to Mocha/MMALib/include
for NNLib in ${NNLibArray[@]}; do
  cp ./$NNLib.h $fileLocal/Mocha/MMALib/include
done

#make SolverLib
cd $fileLocal/SolverLib
make clean -j$processor
make -j$processor

#copy SolverLib.h to Mocha/MMALib/include
for SolverLib in ${SolverLibArray[@]}; do
  cp ./$SolverLib.h $fileLocal/Mocha/MMALib/include
done

#make libCaffeTools
cp -r $fileLocal/CaffeToolsLib/caffe/build/include/caffe/proto $fileLocal/CaffeToolsLib/caffe/build/src/caffe
cd $fileLocal/CaffeToolsLib
make clean -j$processor
make -j$processor

#copy CaffeTools.h to Mocha/MMALib/include
cp ./CaffeTools.h $fileLocal/Mocha/MMALib/include

#copy *.so to /usr/lib
sudo cp $fileLocal/Mocha/Qwt/bin/* /usr/lib
