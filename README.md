(1) install cuda
	1.download cuda at https://developer.nvidia.com/cuda-toolkit
	2.'sudo dpkg -i cuda-repo-ubuntu1504-7-5-local_7.5-18_amd64.deb'
	3.'sudo apt-get update'
	4.'sudo apt-get install cuda'

(2) install cudnn(optional)
	1.download cudnn at https://developer.nvidia.com/rdp/cudnn-download

(3) install Qt Creator
	1.download QtCreator at http://www.qt.io/download-open-source/

(4) install OpenCV(optional)
	1.download OpenCV at http://opencv.org/

(5) use Qt Creator qmake Qwt
(6) copy Qwt lib to ./Mocha/Qwt/bin
(7) run install.sh
(8) Done......

Suggest:
 Ubuntu v15.04
 OpenCV v3.1.0
 caffe v0.14.5
 cuDNN v4.0.7
 cuda v7.5
 QtCreator v5.6.0

Note:
(1) Please perform the following actions if only cpu
	1.open ./CaffeToolsLib/caffe/Makefile.config
	2.cancel comment CPU_ONLY := 1
