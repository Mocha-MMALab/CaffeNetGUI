QT += widgets
CONFIG += c++11

HEADERS = LayerDiagramItem.h \
                    LayerProperties.h \
                    LayerGUIEnums.h \
                    Arrow.h \
                    DiagramScene.h \
                    DiagramTextItem.h \
                    MainWindow.h \
                    TestDialog.h \
                    TimeDialog.h \
                    TrainDialog.h \
                    ParseLog.h \
                    Versions.h

SOURCES = main.cpp \
                    LayerDiagramItem.cpp \
                    LayerProperties.cpp \
                    Arrow.cpp \
                    DiagramScene.cpp \
                    DiagramTextItem.cpp \
                    MainWindow.cpp \
                    TestDialog.cpp \
                    TimeDialog.cpp \
                    TrainDialog.cpp \
                    ParseLog.cpp

RESOURCES   =   DiagramScene.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/graphicsview/diagramscene
INSTALLS += target

win32: LIBS += -L$$PWD/MMALib/lib/ -lLayerLib
else:unix: LIBS += -L$$PWD/MMALib/bin/ -lLayers
INCLUDEPATH += $$PWD/MMALib/include
DEPENDPATH += $$PWD/MMALib/include

win32: PRE_TARGETDEPS += $$PWD/MMALib/lib/LayerLib.lib
else:unix: PRE_TARGETDEPS += $$PWD/MMALib/lib/libLayers.a

win32: LIBS += -L$$PWD/MMALib/lib/ -lNNLib
else:unix: LIBS += -L$$PWD/MMALib/bin/ -lNN

win32: PRE_TARGETDEPS += $$PWD/MMALib/lib/NNLib.lib
else:unix: PRE_TARGETDEPS += $$PWD/MMALib/lib/libNN.a


INCLUDEPATH +=  $$PWD/../CaffeToolsLib/caffe/include \
                $$PWD/../CaffeToolsLib/caffe/build/src \
                $$PWD/Qwt/include \
                /usr/include/hdf5/serial \
                /usr/local/cuda/targets/x86_64-linux/include

LIBS += -L/usr/local/cuda/lib64/ -lcudart \
        -L$$PWD/Qwt/bin/ -lqwt \
        -L$$PWD/../CaffeToolsLib/caffe/build/lib/ -lcaffe \
        -L$$PWD/MMALib/lib/release/ -lCaffeTools \
        -L$$PWD/MMALib/bin/release/ -lLayers \
        -L$$PWD/MMALib/bin/release/ -lNN \

LIBS += -lprotobuf -lglog -lboost_system -lgflags

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/QPropertyBrowser/lib/release/ -lQt5Solutions_PropertyBrowser-head
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/QPropertyBrowser/lib/debug/ -lQt5Solutions_PropertyBrowser-head
else:unix: LIBS += -L$$PWD/QPropertyBrowser/lib/ -lQt5Solutions_PropertyBrowser-head

INCLUDEPATH += $$PWD/QPropertyBrowser/include
DEPENDPATH += $$PWD/QPropertyBrowser/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/QPropertyBrowser/lib/release/libQt5Solutions_PropertyBrowser-head.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/QPropertyBrowser/lib/debug/libQt5Solutions_PropertyBrowser-head.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/QPropertyBrowser/lib/release/Qt5Solutions_PropertyBrowser-head.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/QPropertyBrowser/lib/debug/Qt5Solutions_PropertyBrowser-head.lib
else:unix: PRE_TARGETDEPS += $$PWD/QPropertyBrowser/lib/libQt5Solutions_PropertyBrowser-head.a
