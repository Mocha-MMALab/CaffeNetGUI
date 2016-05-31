#ifndef LAYERPROPERTIES
#define LAYERPROPERTIES

#include <limits.h>
#include <float.h>

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QAction>
#include <QSignalMapper>
#include <QGraphicsTextItem>

#include "LayerGUIEnums.h"

#include "qtpropertymanager.h"
#include "qteditorfactory.h"
#include "qttreepropertybrowser.h"
#include "qtbuttonpropertybrowser.h"
#include "qtgroupboxpropertybrowser.h"
#include "CaffeTools.h"
#include "Layers.h"

class LayerProperties :public QWidget
{
    Q_OBJECT
public:
    LayerProperties(LayerGUI::Layers layer, void* layerObject, LayerParameter layerParam, QGraphicsTextItem* layerNameItem, QGraphicsTextItem *layerInfoItem);

private slots:
    void changeWeightFilter(QtProperty *propertyItem, int type);
    void changeBiasFilter(QtProperty *propertyItem, int type);
    void changeBlobShape(QtProperty *propertyItem, int count);
    void changeBlobShapeDim(QtProperty *propertyItem, int count);

protected:
    void leaveEvent(QEvent * event) Q_DECL_OVERRIDE;
    void showEvent(QShowEvent * event) Q_DECL_OVERRIDE;

private:
    void initEnumString();
    void clearSubProperties(QtProperty *propertyItem);
    void updateGUIProperties();
    void updateGUIProperties(LayerParameter layerParam);
    void applyProperties();
    void applyFilter(QtProperty *propertyItem, FilterType type, void* filter);
    void changFilter(QtProperty *propertyItem, FilterType type);
    void updateFilterGUIProperties(QtProperty *propertyItem, FilterType type, void* filter);
    void updateFilterGUIProperties(QtProperty *propertyItem, FilterType type, caffe::FillerParameter fillerParam);
    void updateBlobShapeProperties(QtProperty *propertyItem, void* shape);
    void updateBlobShapeProperties(QtProperty *propertyItem, caffe::BlobShape shape);
    void applyBlobShape(QtProperty *propertyItem,  void* blobShap);

    int selectFilterType(string type);
    int selectCropMode(string mode);


    QtAbstractPropertyBrowser   *mPropertyBrowser;

    QtIntPropertyManager        *mIntManager;
    QtStringPropertyManager     *mStringManager;
    QtBoolPropertyManager       *mBoolManager;
    QtSizePropertyManager       *mSizeManager;
    QtRectPropertyManager       *mRectManager;
    QtSizePolicyPropertyManager *mSizePolicyManager;
    QtEnumPropertyManager       *mEnumManager;
    QtEnumPropertyManager       *mWeightFilterEnumManager;
    QtEnumPropertyManager       *mBiasFilterEnumManager;
    QtGroupPropertyManager      *mGroupManager;
    QtDoublePropertyManager     *mDoubleManager;
    QtIntPropertyManager        *mBlobShapeIntManager;
    QtIntPropertyManager        *mBlobShapeDimIntManager;

    QGraphicsTextItem      *mLayerNameItem;
    QGraphicsTextItem      *mLayerInfoItem;
    QString              mLayerInfo;
    QGridLayout                 *mLayout;

    LayerGUI::Layers            mLayer;
    void*                       mLayerObject;
    void*                       mDataBlob;

    QStringList                 mPoolMethod;
    QStringList                 mEngine;
    QStringList                 mWeightFilterType;
    QStringList                 mBiasFilterType;
    QStringList                 mReductionOp;
    QStringList                 mEltwiseOp;
    QStringList                 mNorm;
    QStringList                 mNormRegion;
    QStringList                 mDB;
    QStringList                 mFillerParameter;
    QStringList                 mPhase;
    QStringList                 mCropMode;
    QStringList                 mVarianceNorm;

};

#endif // LAYERPROPERTIES

