# CaffeNetGUI install step

## Install cuda
```css
1.download cuda at https://developer.nvidia.com/cuda-toolkit
2.'sudo dpkg -i cuda-repo-ubuntu1504-7-5-local_7.5-18_amd64.deb'
3.'sudo apt-get update'
4.'sudo apt-get install cuda'
```

## Install cudnn(optional)
```css
1.download cudnn at https://developer.nvidia.com/rdp/cudnn-download
```

## Install Qt Creator
```css
1.download QtCreator at http://www.qt.io/download-open-source/
```

## Install OpenCV(optional)
```css
1.download OpenCV at http://opencv.org/
```

## QMake Qwt
```css
1.unzip ./Qwt
2.use Qt Creator qmake qwt.pro
3.copy Qwt lib to ./Mocha/Qwt/bin
4.run ./install.sh
5.use Qt build Mocha.pro
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
1.open ./CaffeToolsLib/caffe/Makefile.config
2.cancel comment CPU_ONLY := 1
```
