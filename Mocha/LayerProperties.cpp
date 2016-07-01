#include "LayerProperties.h"

using namespace MMALab;

LayerProperties::LayerProperties(LayerGUI::Layers layer, void* layerObject, LayerParameter layerParam, QGraphicsTextItem *layerNameItem, QGraphicsTextItem *layerInfoItem): QWidget()
{
    initEnumString();

    mLayer = layer;
    mLayerObject = layerObject;
    mLayerNameItem = layerNameItem;
    mLayerInfoItem = layerInfoItem;

    this->setWindowTitle(QString::fromStdString("Properties"));

    mLayout = new QGridLayout(this);
    mPropertyBrowser = new QtTreePropertyBrowser();

    mIntManager = new QtIntPropertyManager(this);
    mStringManager = new QtStringPropertyManager(this);
    mBoolManager = new QtBoolPropertyManager(this);
    mSizeManager = new QtSizePropertyManager(this);
    mRectManager = new QtRectPropertyManager(this);
    mSizePolicyManager = new QtSizePolicyPropertyManager(this);
    mWeightFilterEnumManager = new QtEnumPropertyManager(this);
    mBiasFilterEnumManager = new QtEnumPropertyManager(this);
    mEnumManager = new QtEnumPropertyManager(this);
    //mFilterEnumManager = new QtEnumPropertyManager(this);
    mGroupManager = new QtGroupPropertyManager(this);
    mDoubleManager = new QtDoublePropertyManager(this);
    //mFilePathManager = new FilePathManager(this);

    mBlobShapeIntManager  = new QtIntPropertyManager(this);
    mBlobShapeDimIntManager  = new QtIntPropertyManager(this);


    QtCheckBoxFactory *checkBoxFactory = new QtCheckBoxFactory(this);
    QtSpinBoxFactory *spinBoxFactory = new QtSpinBoxFactory(this);
    //QtSliderFactory *sliderFactory = new QtSliderFactory(this);
    //QtScrollBarFactory *scrollBarFactory = new QtScrollBarFactory(this);
    QtLineEditFactory *lineEditFactory = new QtLineEditFactory(this);
    QtEnumEditorFactory *comboBoxFactory = new QtEnumEditorFactory(this);
    QtDoubleSpinBoxFactory *doubleSpinBoxFactory = new QtDoubleSpinBoxFactory(this);
    //FileEditFactory *fileEditFactory = new FileEditFactory(this);

    mPropertyBrowser->setFactoryForManager(mBoolManager, checkBoxFactory);
    mPropertyBrowser->setFactoryForManager(mIntManager, spinBoxFactory);
    mPropertyBrowser->setFactoryForManager(mStringManager, lineEditFactory);
    mPropertyBrowser->setFactoryForManager(mSizeManager->subIntPropertyManager(), spinBoxFactory);
    mPropertyBrowser->setFactoryForManager(mRectManager->subIntPropertyManager(), spinBoxFactory);
    mPropertyBrowser->setFactoryForManager(mSizePolicyManager->subIntPropertyManager(), spinBoxFactory);
    mPropertyBrowser->setFactoryForManager(mSizePolicyManager->subEnumPropertyManager(), comboBoxFactory);
    mPropertyBrowser->setFactoryForManager(mEnumManager, comboBoxFactory);
    mPropertyBrowser->setFactoryForManager(mWeightFilterEnumManager, comboBoxFactory);
    mPropertyBrowser->setFactoryForManager(mBiasFilterEnumManager, comboBoxFactory);
    //mPropertyBrowser->setFactoryForManager(mFilterEnumManager, comboBoxFactory);
    mPropertyBrowser->setFactoryForManager(mDoubleManager, doubleSpinBoxFactory);
    //mPropertyBrowser->setFactoryForManager(mFilePathManager, fileEditFactory);

    mPropertyBrowser->setFactoryForManager(mBlobShapeIntManager, spinBoxFactory);
    mPropertyBrowser->setFactoryForManager(mBlobShapeDimIntManager, spinBoxFactory);


    QtProperty *itemLayerName = mStringManager->addProperty("Layer Name");
    itemLayerName->setEnabled(true);
    mStringManager->setValue(itemLayerName, QString::fromStdString(((MMALab::BaseLayer*)mLayerObject)->getLayerName()));
    mPropertyBrowser->addProperty(itemLayerName);

    //add properties attributes
    switch (mLayer)
    {
        case LayerGUI::ConvolutionLayer:
        {
            QtProperty *itemNumOutput = mIntManager->addProperty("Num Output");
            mIntManager->setRange(itemNumOutput, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemNumOutput);

            QtProperty *itemKernelSize = mIntManager->addProperty("Kernel Size");
            mIntManager->setRange(itemKernelSize, 1, INT_MAX);
            mPropertyBrowser->addProperty(itemKernelSize);

            QtProperty *itemWeightfilterType = mWeightFilterEnumManager->addProperty("Weight Filter Type");
            mWeightFilterEnumManager->setEnumNames(itemWeightfilterType, mWeightFilterType);
            mPropertyBrowser->addProperty(itemWeightfilterType);
            connect (mWeightFilterEnumManager, SIGNAL(valueChanged(QtProperty *, int)), this, SLOT(changeWeightFilter(QtProperty *, int)));

            QtProperty *itemBiasfilterType = mBiasFilterEnumManager->addProperty("Bias Filter Type");
            mBiasFilterEnumManager->setEnumNames(itemBiasfilterType, mBiasFilterType);
            mPropertyBrowser->addProperty(itemBiasfilterType);
            connect (mBiasFilterEnumManager, SIGNAL(valueChanged(QtProperty *, int)), this, SLOT(changeBiasFilter(QtProperty *, int)));

            QtProperty *itemPad = mIntManager->addProperty("Pad");
            mIntManager->setRange(itemPad, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemPad);

            QtProperty *itemStride = mIntManager->addProperty("Stride");
            mIntManager->setRange(itemStride, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemStride);

            QtProperty *itemEngine = mEnumManager->addProperty("Engine");
            mEnumManager->setEnumNames(itemEngine, mEngine);
            mPropertyBrowser->addProperty(itemEngine);

            QtProperty *itemGroup = mIntManager->addProperty("Group");
            mIntManager->setRange(itemGroup, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemGroup);

            QtProperty *biasTerm = mBoolManager->addProperty("Bias Term");
            mPropertyBrowser->addProperty(biasTerm);

            QtProperty *itemFilterLRateMult = mDoubleManager->addProperty("Filter LRateMult");
            mDoubleManager->setRange(itemFilterLRateMult, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemFilterLRateMult);

            QtProperty *itemFilterDecayMult = mDoubleManager->addProperty("Filter DecayMult");
            mDoubleManager->setRange(itemFilterDecayMult, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemFilterDecayMult);

            QtProperty *itemBiasLRateMult = mDoubleManager->addProperty("Bias LRateMult");
            mDoubleManager->setRange(itemBiasLRateMult, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemBiasLRateMult);

            QtProperty *itemBiasDecayMult = mDoubleManager->addProperty("Bias DecayMult");
            mDoubleManager->setRange(itemBiasDecayMult, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemBiasDecayMult);

            break;
        }
        case LayerGUI::PoolingLayer:
        {
            QtProperty *itemKernelSize = mIntManager->addProperty("Kernel Size");
            mIntManager->setRange(itemKernelSize, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemKernelSize);

            /*QtProperty *itemKernelH = mIntManager->addProperty("Kernel H");
            mIntManager->setRange(itemKernelH, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemKernelH);

            QtProperty *itemKernelW = mIntManager->addProperty("Kernel W");
            mIntManager->setRange(itemKernelW, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemKernelW);*/

            QtProperty *itemPad = mIntManager->addProperty("Pad");
            mIntManager->setRange(itemPad, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemPad);

            /*QtProperty *itemPadH = mIntManager->addProperty("Pad H");
            mIntManager->setRange(itemPadH, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemPadH);

            QtProperty *itemPadW = mIntManager->addProperty("Pad W");
            mIntManager->setRange(itemPadW, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemPadW);*/

            QtProperty *itemStride = mIntManager->addProperty("Stride");
            mIntManager->setRange(itemStride, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemStride);

            /*QtProperty *itemStrideH = mIntManager->addProperty("Stride H");
            mIntManager->setRange(itemStrideH, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemStrideH);

            QtProperty *itemStrideW = mIntManager->addProperty("Stride W");
            mIntManager->setRange(itemStrideW, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemStrideW);*/

            QtProperty *itemPoolMethod = mEnumManager->addProperty("Pool");
            mEnumManager->setEnumNames(itemPoolMethod, mPoolMethod);
            mPropertyBrowser->addProperty(itemPoolMethod);

            QtProperty *itemEngine = mEnumManager->addProperty("Engine");
            mEnumManager->setEnumNames(itemEngine, mEngine);
            mPropertyBrowser->addProperty(itemEngine);

            QtProperty *itemGlobalPooling = mBoolManager->addProperty("Global Pooling");
            mPropertyBrowser->addProperty(itemGlobalPooling);

            break;
        }
        case LayerGUI::SPPLayer:
        {
            QtProperty *itemPyramidHeight = mIntManager->addProperty("Pyramid Height");
            mPropertyBrowser->addProperty(itemPyramidHeight);

            QtProperty *itemPoolMethod = mEnumManager->addProperty("Pool");
            mEnumManager->setEnumNames(itemPoolMethod, mPoolMethod);
            mPropertyBrowser->addProperty(itemPoolMethod);

            QtProperty *itemEngine = mEnumManager->addProperty("Engine");
            mEnumManager->setEnumNames(itemEngine, mEngine);
            mPropertyBrowser->addProperty(itemEngine);
            break;
        }
        case LayerGUI::LRNLayer:
        {
            QtProperty *itemLocalSize = mIntManager->addProperty("Local Size");
            mIntManager->setRange(itemLocalSize, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemLocalSize);

            QtProperty *itemAlpha = mDoubleManager->addProperty("Alpha");
            mDoubleManager->setRange(itemAlpha, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemAlpha);

            QtProperty *itemBeta = mDoubleManager->addProperty("Beta");
            mDoubleManager->setRange(itemBeta, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemBeta);

            QtProperty *itemNormRegion = mEnumManager->addProperty("Norm Region");
            mEnumManager->setEnumNames(itemNormRegion, mNormRegion);
            mPropertyBrowser->addProperty(itemNormRegion);

            QtProperty *itemK = mDoubleManager->addProperty("K");
            mDoubleManager->setRange(itemK, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemK);

            QtProperty *itemEngine = mEnumManager->addProperty("Engine");
            mEnumManager->setEnumNames(itemEngine, mEngine);
            mPropertyBrowser->addProperty(itemEngine);

            break;
        }
        case LayerGUI::MVNLayer:
        {
            QtProperty *itemNormalizeVariance = mBoolManager->addProperty("Normalize Variance");
            mPropertyBrowser->addProperty(itemNormalizeVariance);

            QtProperty *itemAcrossChannels = mBoolManager->addProperty("Across Channels");
            mPropertyBrowser->addProperty(itemAcrossChannels);

            QtProperty *itemEps = mDoubleManager->addProperty("Eps");
            mDoubleManager->setRange(itemEps, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemEps);

            break;
        }
        case LayerGUI::ReshapeLayer:
        {
            QtProperty *itemBlobShapeCount = mBlobShapeIntManager->addProperty("Blob Shape Count");
            mBlobShapeIntManager->setRange(itemBlobShapeCount, 0, 1);
            mPropertyBrowser->addProperty(itemBlobShapeCount);
            connect (mBlobShapeIntManager, SIGNAL(valueChanged(QtProperty *, int)), this, SLOT(changeBlobShape(QtProperty *, int)));

            QtProperty *itemAxis = mIntManager->addProperty("Axis");
            mPropertyBrowser->addProperty(itemAxis);

            QtProperty *itemNumAxis = mIntManager->addProperty("Num Axis");
            mPropertyBrowser->addProperty(itemNumAxis);


            break;
        }
        case LayerGUI::SliceLayer:
        {
            QtProperty *itemAxis = mIntManager->addProperty("Axis");
            mPropertyBrowser->addProperty(itemAxis);

            QtProperty *itemSlicePoint = mIntManager->addProperty("Slice Point");
            mIntManager->setRange(itemSlicePoint, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemSlicePoint);

            QtProperty *itemSliceDim = mIntManager->addProperty("Slice Dim");
            mIntManager->setRange(itemSliceDim, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemSliceDim);

            break;
        }
        case LayerGUI::InnerProductLayer:
        {

            QtProperty *itemNumOutput = mIntManager->addProperty("Num Output");
            mIntManager->setRange(itemNumOutput, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemNumOutput);

            QtProperty *itemBiasTerm  = mBoolManager->addProperty("Bias Term ");
            mPropertyBrowser->addProperty(itemBiasTerm);

            QtProperty *itemWeightfilterType = mWeightFilterEnumManager->addProperty("Weight Filter Type");
            mWeightFilterEnumManager->setEnumNames(itemWeightfilterType, mWeightFilterType);
            mPropertyBrowser->addProperty(itemWeightfilterType);
            connect (mWeightFilterEnumManager, SIGNAL(valueChanged(QtProperty *, int)), this, SLOT(changeWeightFilter(QtProperty *, int)));

            QtProperty *itemBiasfilterType = mBiasFilterEnumManager->addProperty("Bias Filter Type");
            mBiasFilterEnumManager->setEnumNames(itemBiasfilterType, mBiasFilterType);
            mPropertyBrowser->addProperty(itemBiasfilterType);
            connect (mBiasFilterEnumManager, SIGNAL(valueChanged(QtProperty *, int)), this, SLOT(changeBiasFilter(QtProperty *, int)));

            QtProperty *itemAxis  = mIntManager->addProperty("Axis ");
            mPropertyBrowser->addProperty(itemAxis );

            QtProperty *itemFilterLRateMult = mDoubleManager->addProperty("Filter LRateMult");
            mDoubleManager->setRange(itemFilterLRateMult, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemFilterLRateMult);

            QtProperty *itemFilterDecayMult = mDoubleManager->addProperty("Filter DecayMult");
            mDoubleManager->setRange(itemFilterDecayMult, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemFilterDecayMult);

            QtProperty *itemBiasLRateMult = mDoubleManager->addProperty("Bias LRateMult");
            mDoubleManager->setRange(itemBiasLRateMult, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemBiasLRateMult);

            QtProperty *itemBiasDecayMult = mDoubleManager->addProperty("Bias DecayMult");
            mDoubleManager->setRange(itemBiasDecayMult, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemBiasDecayMult);

            break;
        }
        case LayerGUI::SoftmaxLayer:
        {
            QtProperty *itemEngine = mEnumManager->addProperty("Engine");
            mEnumManager->setEnumNames(itemEngine, mEngine);
            mPropertyBrowser->addProperty(itemEngine);

            QtProperty *itemAxis = mIntManager->addProperty("Axis");
            mPropertyBrowser->addProperty(itemAxis);
            break;
        }
        case LayerGUI::FlattenLayer:
        {
            QtProperty *itemAxis = mIntManager->addProperty("Axis");
            mPropertyBrowser->addProperty(itemAxis);

            QtProperty *itemEndAxis = mIntManager->addProperty("End Axis");
            mPropertyBrowser->addProperty(itemEndAxis);

            break;
        }
        case LayerGUI::EltwiseLayer:
        {
            QtProperty *itemOperation  = mEnumManager->addProperty("Operation ");
            mEnumManager->setEnumNames(itemOperation, mEltwiseOp);
            mPropertyBrowser->addProperty(itemOperation );

            QtProperty *itemCoeff  = mDoubleManager->addProperty("Coeff ");
            mDoubleManager->setRange(itemCoeff, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemCoeff );

            QtProperty *itemStableProdGrad  = mBoolManager->addProperty("Stable Prod Grad ");
            mPropertyBrowser->addProperty(itemStableProdGrad );
            break;
        }
        case LayerGUI::ConcatLayer:
        {
            QtProperty *itemAxis = mIntManager->addProperty("Axis");
            mPropertyBrowser->addProperty(itemAxis);

            QtProperty *itemConcatDim = mIntManager->addProperty("Concat Dim");
            mIntManager->setRange(itemConcatDim, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemConcatDim);
            break;
        }
        case LayerGUI::ArgMaxLayer:
        {
            QtProperty *itemOutMaxVal = mBoolManager->addProperty("Out Max Val");
            mPropertyBrowser->addProperty(itemOutMaxVal);

            QtProperty *itemTopK = mIntManager->addProperty("Top K");
            mIntManager->setRange(itemTopK, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemTopK);

            QtProperty *itemAxis = mIntManager->addProperty("Axis");
            mPropertyBrowser->addProperty(itemAxis);
            break;
        }
        case LayerGUI::ReductionLayer:
        {
            QtProperty *itemOperation  = mEnumManager->addProperty("Operation");
            mEnumManager->setEnumNames(itemOperation, mReductionOp);
            mPropertyBrowser->addProperty(itemOperation );

            QtProperty *itemAxis = mIntManager->addProperty("Axis");
            mPropertyBrowser->addProperty(itemAxis);

            QtProperty *itemCoeff  = mDoubleManager->addProperty("Coeff");
            mDoubleManager->setRange(itemCoeff, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemCoeff );
            break;
        }
        case LayerGUI::DummyDataLayer:
        {
            QtProperty *itemBlobShapeCount = mBlobShapeIntManager->addProperty("Blob Shape Count");
            mBlobShapeIntManager->setRange(itemBlobShapeCount, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemBlobShapeCount);
            connect (mBlobShapeIntManager, SIGNAL(valueChanged(QtProperty *, int)), this, SLOT(changeBlobShape(QtProperty *, int)));

            break;
        }
        case LayerGUI::HDF5OutputLayer:
        {
            QtProperty *itemFileName = mStringManager->addProperty("File Name");
            mPropertyBrowser->addProperty(itemFileName);
            break;
        }
        case LayerGUI::HDF5DataLayer:
        {
            QtProperty *itemSource = mStringManager->addProperty("Source");
            mPropertyBrowser->addProperty(itemSource);

            QtProperty *itemBatchSize = mIntManager->addProperty("Batch Size");
            mIntManager->setRange(itemBatchSize, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemBatchSize);

            QtProperty *itemShuffle = mBoolManager->addProperty("Shuffle");
            mPropertyBrowser->addProperty(itemShuffle);

            break;
        }
        case LayerGUI::WindowDataLayer:
        {

            QtProperty *itemSource = mStringManager->addProperty("Source");
            mPropertyBrowser->addProperty(itemSource);

            QtProperty *itemScale = mDoubleManager->addProperty("Scale");
            mDoubleManager->setRange(itemScale, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemScale);

            QtProperty *itemMeanFile = mStringManager->addProperty("Mean File");
            mPropertyBrowser->addProperty(itemMeanFile);

            QtProperty *itemBatchSize = mIntManager->addProperty("Batch Size");
            mIntManager->setRange(itemBatchSize, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemBatchSize);

            QtProperty *itemCropSize = mIntManager->addProperty("Crop Size");
            mIntManager->setRange(itemCropSize, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemCropSize);

            QtProperty *itemMirror  = mBoolManager->addProperty("Mirror");
            mPropertyBrowser->addProperty(itemMirror );

            QtProperty *itemFgThreshold  = mDoubleManager->addProperty("Fg Threshold");
            mDoubleManager->setRange(itemFgThreshold, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemFgThreshold );

            QtProperty *itemBgFraction = mDoubleManager->addProperty("Bg Threshold");
            mDoubleManager->setRange(itemBgFraction, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemBgFraction);

            QtProperty *itemFgFraction = mDoubleManager->addProperty("Fg Fraction");
            mDoubleManager->setRange(itemFgFraction, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemFgFraction);

            QtProperty *itemContextPad = mIntManager->addProperty("Context Pad");
            mIntManager->setRange(itemBatchSize, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemContextPad);

            QtProperty *itemCropMode = mEnumManager->addProperty("Crop Mode");
            mEnumManager->setEnumNames(itemCropMode, mCropMode);
            mPropertyBrowser->addProperty(itemCropMode);

            QtProperty *itemCacheImages = mBoolManager->addProperty("Cache Images");
            mPropertyBrowser->addProperty(itemCacheImages);

            QtProperty *itemRootFolder = mStringManager->addProperty("Root Folder");
            mPropertyBrowser->addProperty(itemRootFolder);

            break;
        }
        case LayerGUI::ImageDataLayer:
        {
            QtProperty *itemSource = mStringManager->addProperty("Source");
            mPropertyBrowser->addProperty(itemSource);

            QtProperty *itemBatchSize = mIntManager->addProperty("Batch Size");
            mIntManager->setRange(itemBatchSize, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemBatchSize);

            QtProperty *itemRandSkip = mIntManager->addProperty("Rand Skip");
            mIntManager->setRange(itemRandSkip, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemRandSkip);

            QtProperty *itemShuffle = mBoolManager->addProperty("Shuffle");
            mPropertyBrowser->addProperty(itemShuffle);

            QtProperty *itemNewHeight = mIntManager->addProperty("New Height");
            mIntManager->setRange(itemNewHeight, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemNewHeight);

            QtProperty *itemNewWidth  = mIntManager->addProperty("New Width ");
            mIntManager->setRange(itemNewWidth, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemNewWidth );

            QtProperty *itemIsColor = mBoolManager->addProperty("Is Color");
            mPropertyBrowser->addProperty(itemIsColor);

            QtProperty *itemScale = mDoubleManager->addProperty("Scale");
            mDoubleManager->setRange(itemScale, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemScale);

            QtProperty *itemMeanFile = mStringManager->addProperty("Mean File");
            mPropertyBrowser->addProperty(itemMeanFile);

            QtProperty *itemCropSize = mIntManager->addProperty("Crop Size");
            mIntManager->setRange(itemCropSize, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemCropSize);

            QtProperty *itemMirror  = mBoolManager->addProperty("Mirror ");
            mPropertyBrowser->addProperty(itemMirror );

            QtProperty *itemRootFolder = mStringManager->addProperty("Root Folder");
            mPropertyBrowser->addProperty(itemRootFolder);

            break;
        }
        case LayerGUI::MemoryDataLayer:
        {
            QtProperty *itemBatchSize = mIntManager->addProperty("Batch Size");
            mIntManager->setRange(itemBatchSize, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemBatchSize);

            QtProperty *itemChannels = mIntManager->addProperty("Channels");
            mIntManager->setRange(itemChannels, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemChannels);

            QtProperty *itemHeight = mIntManager->addProperty("Height");
            mIntManager->setRange(itemHeight, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemHeight);

            QtProperty *itemWidth = mIntManager->addProperty("Width");
            mIntManager->setRange(itemWidth, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemWidth);
            break;
        }
        case LayerGUI::DataLayer:
        {
            QtProperty *itemSource = mStringManager->addProperty("Source");
            mPropertyBrowser->addProperty(itemSource);

            QtProperty *itemBatchSize = mIntManager->addProperty("Batch Size");
            mIntManager->setRange(itemBatchSize, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemBatchSize);

            QtProperty *itemRandSkip = mIntManager->addProperty("Rand Skip");
            mIntManager->setRange(itemRandSkip, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemRandSkip);

            QtProperty *itemmBackend = mEnumManager->addProperty("Backend");
            mEnumManager->setEnumNames(itemmBackend, mDB);
            mPropertyBrowser->addProperty(itemmBackend);

            QtProperty *itemScale = mDoubleManager->addProperty("Scale");
            mDoubleManager->setRange(itemScale, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemScale);

            QtProperty *itemMeanfile  = mStringManager->addProperty("Mean File");
            mPropertyBrowser->addProperty(itemMeanfile);

            QtProperty *itemCropSize = mIntManager->addProperty("Crop Size");
            mIntManager->setRange(itemCropSize, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemCropSize);

            QtProperty *itemMirror = mBoolManager->addProperty("Mirror");
            mPropertyBrowser->addProperty(itemMirror);

            QtProperty *itemForceEncodedcolor = mBoolManager->addProperty("Force Encoded Color");
            mPropertyBrowser->addProperty(itemForceEncodedcolor);

            QtProperty *itemPrefetch = mIntManager->addProperty("Prefetch");
            mIntManager->setRange(itemPrefetch, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemPrefetch);
            break;
        }
        case LayerGUI::HingeLossLayer:
        {
            QtProperty *itemNorm = mEnumManager->addProperty("Norm");
            mEnumManager->setEnumNames(itemNorm, mNorm);
            mPropertyBrowser->addProperty(itemNorm);
            break;
        }
        case LayerGUI::InfogainLossLayer:
        {
            QtProperty *itemSource = mStringManager->addProperty("Source");
            mPropertyBrowser->addProperty(itemSource);
            break;
        }
        case LayerGUI::ContrastiveLossLayer:
        {
            QtProperty *itemMargin = mDoubleManager->addProperty("Margin");
            mDoubleManager->setRange(itemMargin, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemMargin);

            QtProperty *itemLegacyVersion  = mBoolManager->addProperty("LegacyVersion");
            mPropertyBrowser->addProperty(itemLegacyVersion);
            break;
        }
        case LayerGUI::MultinomialLogisticLossLayer:
        {
            break;
        }
        case LayerGUI::SigmoidCrossEntropyLossLayer:
        {
            break;
        }
        case LayerGUI::EuclideanLossLayer:
        {
            break;
        }
        case LayerGUI::SoftmaxWithLossLayer:
        {
            QtProperty *itemEngine = mEnumManager->addProperty("Engine");
            mEnumManager->setEnumNames(itemEngine, mEngine);
            mPropertyBrowser->addProperty(itemEngine);

            QtProperty *itemIgnoreLabel = mIntManager->addProperty("Ignore Label");
            mPropertyBrowser->addProperty(itemIgnoreLabel);

            QtProperty *itemAxis = mIntManager->addProperty("Axis");
            mPropertyBrowser->addProperty(itemAxis);

            QtProperty *itemNormalize = mBoolManager->addProperty("Normalize");
            mPropertyBrowser->addProperty(itemNormalize);
            break;
        }
        case LayerGUI::AccuracyLayer:
        {
            QtProperty *itemTopk  = mIntManager->addProperty("Top K");
            mIntManager->setRange(itemTopk, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemTopk);

            QtProperty *itemAxis = mIntManager->addProperty("Axis");
            mIntManager->setRange(itemAxis, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemAxis);

            QtProperty *itemIgnoreLabel = mIntManager->addProperty("Ignore Label");
            mIntManager->setRange(itemIgnoreLabel, 0, INT_MAX);
            mPropertyBrowser->addProperty(itemIgnoreLabel);

            break;
        }
        case LayerGUI::PReLULayer:
        {

            QtProperty *itemFilterType = mWeightFilterEnumManager->addProperty("Filter Type");
            mWeightFilterEnumManager->setEnumNames(itemFilterType, mWeightFilterType);
            mPropertyBrowser->addProperty(itemFilterType);
            connect (mWeightFilterEnumManager, SIGNAL(valueChanged(QtProperty *, int)), this, SLOT(changeWeightFilter(QtProperty *, int)));

            QtProperty *itemChannelShared  = mBoolManager->addProperty("Channel Shared");
            mPropertyBrowser->addProperty(itemChannelShared);

            break;
        }
        case LayerGUI::ThresholdLayer:
        {
            QtProperty *itemThreshold = mDoubleManager->addProperty("Threshold");
            mDoubleManager->setRange(itemThreshold, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemThreshold);
            break;
        }
        case LayerGUI::TanHLayer:
        {
            QtProperty *itemEngine = mEnumManager->addProperty("Engine");
            mEnumManager->setEnumNames(itemEngine, mEngine);
            mPropertyBrowser->addProperty(itemEngine);
            break;
        }
        case LayerGUI::ReLULayer:
        {
            QtProperty *itemNegativeSlope = mDoubleManager->addProperty("Negative Slope");
            mDoubleManager->setRange(itemNegativeSlope, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemNegativeSlope);

            QtProperty *itemEngine = mEnumManager->addProperty("Engine");
            mEnumManager->setEnumNames(itemEngine, mEngine);
            mPropertyBrowser->addProperty(itemEngine);

            break;
        }
        case LayerGUI::SigmoidLayer:
        {
            QtProperty *itemEngine = mEnumManager->addProperty("Engine");
            mEnumManager->setEnumNames(itemEngine, mEngine);
            mPropertyBrowser->addProperty(itemEngine);
            break;
        }
        case LayerGUI::PowerLayer:
        {
            QtProperty *itemBase = mDoubleManager->addProperty("Power");
            mDoubleManager->setRange(itemBase, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemBase);

            QtProperty *itemScale = mDoubleManager->addProperty("Scale");
            mDoubleManager->setRange(itemScale, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemScale);

            QtProperty *itemShift = mDoubleManager->addProperty("Shift");
            mDoubleManager->setRange(itemShift, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemShift);
            break;
        }
        case LayerGUI::DropoutLayer:
        {
            QtProperty *itemDropoutRatio = mDoubleManager->addProperty("Dropout Ratio");
            mDoubleManager->setRange(itemDropoutRatio, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemDropoutRatio);
            break;
        }
        case LayerGUI::ExpLayer:
        {
            QtProperty *itemBase = mDoubleManager->addProperty("Base");
            mDoubleManager->setRange(itemBase, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemBase);

            QtProperty *itemScale = mDoubleManager->addProperty("Scale");
            mDoubleManager->setRange(itemScale, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemScale);

            QtProperty *itemShift = mDoubleManager->addProperty("Shift");
            mDoubleManager->setRange(itemShift, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemShift);
            break;
        }
        case LayerGUI::LogLayer:
        {
            QtProperty *itemBase = mDoubleManager->addProperty("Base");
            mDoubleManager->setRange(itemBase, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemBase);

            QtProperty *itemScale = mDoubleManager->addProperty("Scale");
            mDoubleManager->setRange(itemScale, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemScale);

            QtProperty *itemShift = mDoubleManager->addProperty("Shift");
            mDoubleManager->setRange(itemShift, -FLT_MAX, FLT_MAX);
            mPropertyBrowser->addProperty(itemShift);

            break;
        }
        case LayerGUI::AbsValLayer:
        {
            break;
        }
        case LayerGUI::BNLLLayer:
        {
            break;
        }
        default:
        {
            break;
        }
    }

    if(mLayer !=LayerGUI::DataBlob )
    {
        QtProperty *itemPhase = mEnumManager->addProperty("Phase");
        mEnumManager->setEnumNames(itemPhase, mPhase);
        mPropertyBrowser->addProperty(itemPhase); // .at(mPropertyBrowser->properties().size() - 1)
    }
    if(layerParam.has_type())
    {
        updateGUIProperties(layerParam);
    }
    else
    {
        updateGUIProperties();
    }
    mLayout->addWidget(mPropertyBrowser, 0, 0);

}

//input Layer attributes
void LayerProperties::applyProperties()
{
    mLayerNameItem->setPlainText(QString::fromStdString(mStringManager->value(mPropertyBrowser->properties().at(0)).toStdString()));
    ((MMALab::BaseLayer*)mLayerObject)->setLayerName(mStringManager->value(mPropertyBrowser->properties().at(0)).toStdString());
    switch (mLayer)
    {
        case LayerGUI::ConvolutionLayer:
        {
            ((MMALab::ConvolutionLayer*)mLayerObject)->setNumOutput(mIntManager->value(mPropertyBrowser->properties().at(1)));
            ((MMALab::ConvolutionLayer*)mLayerObject)->setKernelSize(mIntManager->value(mPropertyBrowser->properties().at(2)));
            applyFilter(mPropertyBrowser->properties().at(3),
                        ((MMALab::ConvolutionLayer*)mLayerObject)->getWeightfilterType(),
                        ((MMALab::ConvolutionLayer*)mLayerObject)->getWeightfilter());
            applyFilter(mPropertyBrowser->properties().at(4),
                        ((MMALab::ConvolutionLayer*)mLayerObject)->getBiasfilterType(),
                        ((MMALab::ConvolutionLayer*)mLayerObject)->getBiasfilter());

            ((MMALab::ConvolutionLayer*)mLayerObject)->setPad(mIntManager->value(mPropertyBrowser->properties().at(5)));
            ((MMALab::ConvolutionLayer*)mLayerObject)->setStride(mIntManager->value(mPropertyBrowser->properties().at(6)));
            ((MMALab::ConvolutionLayer*)mLayerObject)->setEngine((MMALab::Engine)mEnumManager->value(mPropertyBrowser->properties().at(7)));
            ((MMALab::ConvolutionLayer*)mLayerObject)->setGroup(mIntManager->value(mPropertyBrowser->properties().at(8)));
            ((MMALab::ConvolutionLayer*)mLayerObject)->setBiasTerm(mBoolManager->value(mPropertyBrowser->properties().at(9)));

            ((MMALab::ConvolutionLayer*)mLayerObject)->setFilterLRDecayMult(mDoubleManager->value(mPropertyBrowser->properties().at(10)),
                                                                                                                                   mDoubleManager->value(mPropertyBrowser->properties().at(11)));
            ((MMALab::ConvolutionLayer*)mLayerObject)->setBiasLRDecayMult(mDoubleManager->value(mPropertyBrowser->properties().at(12)),
                                                                                                                                   mDoubleManager->value(mPropertyBrowser->properties().at(13)));
            ((MMALab::ConvolutionLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::ConvolutionLayer*)mLayerObject)->getLayerType()) + "\n";
            mLayerInfo += "kerenl size: " + QString::number(((MMALab::ConvolutionLayer*)mLayerObject)->getKernelSize()) + "\n";
            mLayerInfo += "stride: " + QString::number(((MMALab::ConvolutionLayer*)mLayerObject)->getStride()) + "\n";
            mLayerInfo += "pad: " + QString::number(((MMALab::ConvolutionLayer*)mLayerObject)->getPad()) + "\n";
            mLayerInfo += "num output: " + QString::number(((MMALab::ConvolutionLayer*)mLayerObject)->getNumOutput());
            mLayerInfoItem->setPlainText(mLayerInfo);

            break;
        }
        case LayerGUI::PoolingLayer:
        {
            ((MMALab::PoolingLayer*)mLayerObject)->setKernelSize(mIntManager->value(mPropertyBrowser->properties().at(1)));
            //((MMALab::PoolingLayer*)mLayerObject)->setKernelH(mPropertyBrowser->properties().at(2)->valueText().toInt());
            //((MMALab::PoolingLayer*)mLayerObject)->setKernelW(mPropertyBrowser->properties().at(3)->valueText().toInt());
            ((MMALab::PoolingLayer*)mLayerObject)->setPad(mIntManager->value(mPropertyBrowser->properties().at(2)));
            //((MMALab::PoolingLayer*)mLayerObject)->setPadH(mPropertyBrowser->properties().at(5)->valueText().toInt());
            //((MMALab::PoolingLayer*)mLayerObject)->setPadW(mPropertyBrowser->properties().at(6)->valueText().toInt());
            ((MMALab::PoolingLayer*)mLayerObject)->setStride(mIntManager->value(mPropertyBrowser->properties().at(3)));
            //((MMALab::PoolingLayer*)mLayerObject)->setStrideH(mPropertyBrowser->properties().at(8)->valueText().toInt());
            //((MMALab::PoolingLayer*)mLayerObject)->setStrideW(mPropertyBrowser->properties().at(9)->valueText().toInt());
            ((MMALab::PoolingLayer*)mLayerObject)->setPool((MMALab::PoolMethod)mEnumManager->value(mPropertyBrowser->properties().at(4)));
            ((MMALab::PoolingLayer*)mLayerObject)->setEngine((MMALab::Engine)mEnumManager->value(mPropertyBrowser->properties().at(5)));
            ((MMALab::PoolingLayer*)mLayerObject)->setGlobalPooling((bool)mBoolManager->value(mPropertyBrowser->properties().at(6)));
            ((MMALab::PoolingLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            switch (((MMALab::PoolingLayer*)mLayerObject)->getPool())
            {
                case MMALab::PoolMethod::POOLMETHOD_MAX:
                    mLayerInfo = "MAX ";
                    break;
                case MMALab::PoolMethod::POOLMETHOD_AVE:
                    mLayerInfo = "AVE ";
                    break;
                case MMALab::PoolMethod::POOLMETHOD_STOCHASTIC:
                    mLayerInfo = "STOCHASTIC ";
                    break;
                default:
                    break;
            }
            mLayerInfo += QString::fromStdString(((MMALab::PoolingLayer*)mLayerObject)->getLayerType()) + "\n";
            mLayerInfo += "kerenl size: " + QString::number(((MMALab::PoolingLayer*)mLayerObject)->getKernelSize()) + "\n";
            mLayerInfo += "stride: " + QString::number(((MMALab::PoolingLayer*)mLayerObject)->getStride()) + "\n";
            mLayerInfo += "pad: " + QString::number(((MMALab::PoolingLayer*)mLayerObject)->getPad());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::SPPLayer:
        {
            ((MMALab::SPPLayer*)mLayerObject)->setPyramidHeight(mIntManager->value(mPropertyBrowser->properties().at(1)));
            ((MMALab::SPPLayer*)mLayerObject)->setPool((MMALab::PoolMethod)mEnumManager->value(mPropertyBrowser->properties().at(2)));
            ((MMALab::SPPLayer*)mLayerObject)->setEngine((MMALab::Engine)mEnumManager->value(mPropertyBrowser->properties().at(3)));
            ((MMALab::SPPLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::SPPLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::LRNLayer:
        {
            ((MMALab::LRNLayer*)mLayerObject)->setLocalSize(mIntManager->value(mPropertyBrowser->properties().at(1)));
            ((MMALab::LRNLayer*)mLayerObject)->setAlpha(mDoubleManager->value(mPropertyBrowser->properties().at(2)));
            ((MMALab::LRNLayer*)mLayerObject)->setBeta(mDoubleManager->value(mPropertyBrowser->properties().at(3)));
            ((MMALab::LRNLayer*)mLayerObject)->setNormRegion((MMALab::NormRegion)mEnumManager->value(mPropertyBrowser->properties().at(4)));
            ((MMALab::LRNLayer*)mLayerObject)->setK(mDoubleManager->value(mPropertyBrowser->properties().at(5)));
            ((MMALab::LRNLayer*)mLayerObject)->setEngine((MMALab::Engine)mEnumManager->value(mPropertyBrowser->properties().at(6)));
            ((MMALab::LRNLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::LRNLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::MVNLayer:
        {
            ((MMALab::MVNLayer*)mLayerObject)->setNormalizeVariance(mBoolManager->value(mPropertyBrowser->properties().at(1)));
            ((MMALab::MVNLayer*)mLayerObject)->setAcrossChannels(mBoolManager->value(mPropertyBrowser->properties().at(2)));
            ((MMALab::MVNLayer*)mLayerObject)->setEps(mDoubleManager->value(mPropertyBrowser->properties().at(3)));
            ((MMALab::MVNLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::MVNLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::ReshapeLayer:
        {
            applyBlobShape(mPropertyBrowser->properties().at(1), ((MMALab::ReshapeLayer*)mLayerObject)->getShape());
            ((MMALab::ReshapeLayer*)mLayerObject)->setAxis(mIntManager->value(mPropertyBrowser->properties().at(2)));
            ((MMALab::ReshapeLayer*)mLayerObject)->setNumAxis(mIntManager->value(mPropertyBrowser->properties().at(3)));
            ((MMALab::ReshapeLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::ReshapeLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::SliceLayer:
        {
            ((MMALab::SliceLayer*)mLayerObject)->setAxis(mIntManager->value(mPropertyBrowser->properties().at(1)));
            ((MMALab::SliceLayer*)mLayerObject)->setSlicePoint(mIntManager->value(mPropertyBrowser->properties().at(2)));
            ((MMALab::SliceLayer*)mLayerObject)->setSliceDim(mIntManager->value(mPropertyBrowser->properties().at(3)));
            ((MMALab::SliceLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::SliceLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::InnerProductLayer:
        {

            ((MMALab::InnerProductLayer*)mLayerObject)->setNumOutput(mIntManager->value(mPropertyBrowser->properties().at(1)));
            ((MMALab::InnerProductLayer*)mLayerObject)->setBiasTerm(mBoolManager->value(mPropertyBrowser->properties().at(2)));

            applyFilter(mPropertyBrowser->properties().at(3),
                        ((MMALab::InnerProductLayer*)mLayerObject)->getWeightfilterType(),
                        ((MMALab::InnerProductLayer*)mLayerObject)->getWeightfilter());
            applyFilter(mPropertyBrowser->properties().at(4),
                        ((MMALab::InnerProductLayer*)mLayerObject)->getBiasfilterType(),
                        ((MMALab::InnerProductLayer*)mLayerObject)->getBiasfilter());

            ((MMALab::InnerProductLayer*)mLayerObject)->setAxis(mIntManager->value(mPropertyBrowser->properties().at(5)));
            ((MMALab::InnerProductLayer*)mLayerObject)->setFilterLRDecayMult(mDoubleManager->value(mPropertyBrowser->properties().at(6)),
                                                                                                                                   mDoubleManager->value(mPropertyBrowser->properties().at(7)));
            ((MMALab::InnerProductLayer*)mLayerObject)->setBiasLRDecayMult(mDoubleManager->value(mPropertyBrowser->properties().at(8)),
                                                                                                                                   mDoubleManager->value(mPropertyBrowser->properties().at(9)));
            ((MMALab::InnerProductLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::InnerProductLayer*)mLayerObject)->getLayerType()) + "\n";
            mLayerInfo += "num output: " + QString::number(((MMALab::InnerProductLayer*)mLayerObject)->getNumOutput());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::SoftmaxLayer:
        {
            ((MMALab::SoftmaxLayer*)mLayerObject)->setEngine((MMALab::Engine)mEnumManager->value(mPropertyBrowser->properties().at(1)));
            ((MMALab::SoftmaxLayer*)mLayerObject)->setAxis(mIntManager->value(mPropertyBrowser->properties().at(2)));
            ((MMALab::SoftmaxLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::SoftmaxLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::FlattenLayer:
        {
            ((MMALab::FlattenLayer*)mLayerObject)->setAxis(mIntManager->value(mPropertyBrowser->properties().at(1)));
            ((MMALab::FlattenLayer*)mLayerObject)->setEndAxis(mIntManager->value(mPropertyBrowser->properties().at(2)));
            ((MMALab::FlattenLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::FlattenLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::EltwiseLayer:
        {
            ((MMALab::EltwiseLayer*)mLayerObject)->setOperation((MMALab::EltwiseOp)mEnumManager->value(mPropertyBrowser->properties().at(1)));
            ((MMALab::EltwiseLayer*)mLayerObject)->setCoeff(mDoubleManager->value(mPropertyBrowser->properties().at(2)));
            ((MMALab::EltwiseLayer*)mLayerObject)->setStableProdGrad(mBoolManager->value(mPropertyBrowser->properties().at(3)));
            ((MMALab::EltwiseLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::EltwiseLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::ConcatLayer:
        {
            ((MMALab::ConcatLayer*)mLayerObject)->setAxis(mIntManager->value(mPropertyBrowser->properties().at(1)));
            ((MMALab::ConcatLayer*)mLayerObject)->setConcatDim(mIntManager->value(mPropertyBrowser->properties().at(2)));
            ((MMALab::ConcatLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::ConcatLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::ArgMaxLayer:
        {
            ((MMALab::ArgMaxLayer*)mLayerObject)->setOutMaxVal((bool)mBoolManager->value(mPropertyBrowser->properties().at(1)));
            ((MMALab::ArgMaxLayer*)mLayerObject)->setTopK(mIntManager->value(mPropertyBrowser->properties().at(2)));
            ((MMALab::ArgMaxLayer*)mLayerObject)->setAxis(mIntManager->value(mPropertyBrowser->properties().at(3)));
            ((MMALab::ArgMaxLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::ArgMaxLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::ReductionLayer:
        {
            ((MMALab::ReductionLayer*)mLayerObject)->setOperation((MMALab::ReductionOp)mEnumManager->value(mPropertyBrowser->properties().at(1)));
            ((MMALab::ReductionLayer*)mLayerObject)->setAxis(mIntManager->value(mPropertyBrowser->properties().at(2)));
            ((MMALab::ReductionLayer*)mLayerObject)->setCoeff(mDoubleManager->value(mPropertyBrowser->properties().at(3)));
            ((MMALab::ReductionLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::ReductionLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::DummyDataLayer:
        {
            applyBlobShape(mPropertyBrowser->properties().at(1), ((MMALab::DummyDataLayer*)mLayerObject)->getShape());
            ((MMALab::DummyDataLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::DummyDataLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::HDF5OutputLayer:
        {
            ((MMALab::HDF5OutputLayer*)mLayerObject)->setFileName(mStringManager->value(mPropertyBrowser->properties().at(1)).toStdString());
            ((MMALab::HDF5OutputLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::HDF5OutputLayer*)mLayerObject)->getLayerType()) + "\n";
            mLayerInfo += "file name: " + QString::fromStdString(((MMALab::HDF5OutputLayer*)mLayerObject)->getFileName());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::HDF5DataLayer:
        {
            ((MMALab::HDF5DataLayer*)mLayerObject)->setSource(mStringManager->value(mPropertyBrowser->properties().at(1)).toStdString());
            ((MMALab::HDF5DataLayer*)mLayerObject)->setBatchSize(mIntManager->value(mPropertyBrowser->properties().at(2)));
            ((MMALab::HDF5DataLayer*)mLayerObject)->setShuffle(mBoolManager->value(mPropertyBrowser->properties().at(3)));
            ((MMALab::HDF5DataLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::HDF5DataLayer*)mLayerObject)->getLayerType()) + "\n";
            mLayerInfo += "source: " + QString::fromStdString(((MMALab::HDF5DataLayer*)mLayerObject)->getSource()) + "\n";
            mLayerInfo += "batch: " + QString::number(((MMALab::HDF5DataLayer*)mLayerObject)->getBatchSize());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::WindowDataLayer:
        {
            ((MMALab::WindowDataLayer*)mLayerObject)->setSource(mStringManager->value(mPropertyBrowser->properties().at(1)).toStdString());
            ((MMALab::WindowDataLayer*)mLayerObject)->setScale(mDoubleManager->value(mPropertyBrowser->properties().at(2)));
            ((MMALab::WindowDataLayer*)mLayerObject)->setMeanFile(mStringManager->value(mPropertyBrowser->properties().at(3)).toStdString());
            ((MMALab::WindowDataLayer*)mLayerObject)->setBatchSize(mIntManager->value(mPropertyBrowser->properties().at(4)));
            ((MMALab::WindowDataLayer*)mLayerObject)->setCropSize(mIntManager->value(mPropertyBrowser->properties().at(5)));
            ((MMALab::WindowDataLayer*)mLayerObject)->setMirror(mBoolManager->value(mPropertyBrowser->properties().at(6)));
            ((MMALab::WindowDataLayer*)mLayerObject)->setFgThreshold(mDoubleManager->value(mPropertyBrowser->properties().at(7)));
            ((MMALab::WindowDataLayer*)mLayerObject)->setBgThreshold(mDoubleManager->value(mPropertyBrowser->properties().at(8)));
            ((MMALab::WindowDataLayer*)mLayerObject)->setFgFraction(mDoubleManager->value(mPropertyBrowser->properties().at(9)));
            ((MMALab::WindowDataLayer*)mLayerObject)->setContextPad(mIntManager->value(mPropertyBrowser->properties().at(10)));
            ((MMALab::WindowDataLayer*)mLayerObject)->setCropMode((MMALab::CropMode)mEnumManager->value(mPropertyBrowser->properties().at(11)));
            ((MMALab::WindowDataLayer*)mLayerObject)->setCacheImages(mBoolManager->value(mPropertyBrowser->properties().at(12)));
            ((MMALab::WindowDataLayer*)mLayerObject)->setRootFolder(mStringManager->value(mPropertyBrowser->properties().at(13)).toStdString());
            ((MMALab::WindowDataLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::WindowDataLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::ImageDataLayer:
        {
            ((MMALab::ImageDataLayer*)mLayerObject)->setSource(mStringManager->value(mPropertyBrowser->properties().at(1)).toStdString());
            ((MMALab::ImageDataLayer*)mLayerObject)->setBatchSize(mIntManager->value(mPropertyBrowser->properties().at(2)));
            ((MMALab::ImageDataLayer*)mLayerObject)->setRandSkip(mIntManager->value(mPropertyBrowser->properties().at(3)));
            ((MMALab::ImageDataLayer*)mLayerObject)->setShuffle(mBoolManager->value(mPropertyBrowser->properties().at(4)));
            ((MMALab::ImageDataLayer*)mLayerObject)->setNewHeight(mIntManager->value(mPropertyBrowser->properties().at(5)));
            ((MMALab::ImageDataLayer*)mLayerObject)->setNewWidth(mIntManager->value(mPropertyBrowser->properties().at(6)));
            ((MMALab::ImageDataLayer*)mLayerObject)->setIsColor(mBoolManager->value(mPropertyBrowser->properties().at(7)));
            ((MMALab::ImageDataLayer*)mLayerObject)->setScale(mDoubleManager->value(mPropertyBrowser->properties().at(8)));
            ((MMALab::ImageDataLayer*)mLayerObject)->setMeanFile(mStringManager->value(mPropertyBrowser->properties().at(9)).toStdString());
            ((MMALab::ImageDataLayer*)mLayerObject)->setCropSize(mIntManager->value(mPropertyBrowser->properties().at(10)));
            ((MMALab::ImageDataLayer*)mLayerObject)->setMirror(mBoolManager->value(mPropertyBrowser->properties().at(11)));
            ((MMALab::ImageDataLayer*)mLayerObject)->setRootFolder(mStringManager->value(mPropertyBrowser->properties().at(12)).toStdString());
            ((MMALab::ImageDataLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::ImageDataLayer*)mLayerObject)->getLayerType()) + "\n";
            mLayerInfo += "source: " + QString::fromStdString(((MMALab::ImageDataLayer*)mLayerObject)->getSource()) + "\n";
            mLayerInfo += "batch: " + QString::number(((MMALab::ImageDataLayer*)mLayerObject)->getBatchSize());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::MemoryDataLayer:
        {
            ((MMALab::MemoryDataLayer*)mLayerObject)->setBatchSize(mIntManager->value(mPropertyBrowser->properties().at(1)));
            ((MMALab::MemoryDataLayer*)mLayerObject)->setChannels(mIntManager->value(mPropertyBrowser->properties().at(2)));
            ((MMALab::MemoryDataLayer*)mLayerObject)->setHeight(mIntManager->value(mPropertyBrowser->properties().at(3)));
            ((MMALab::MemoryDataLayer*)mLayerObject)->setWidth(mIntManager->value(mPropertyBrowser->properties().at(4)));
            ((MMALab::MemoryDataLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::MemoryDataLayer*)mLayerObject)->getLayerType()) + "\n";
            mLayerInfo += "batch: "+ QString::number(((MMALab::MemoryDataLayer*)mLayerObject)->getBatchSize()) + "\n";
            mLayerInfo += "channels: "+ QString::number(((MMALab::MemoryDataLayer*)mLayerObject)->getChannels()) + "\n";
            mLayerInfo += "height: "+ QString::number(((MMALab::MemoryDataLayer*)mLayerObject)->getHeight()) + "\n";
            mLayerInfo += "width: "+ QString::number(((MMALab::MemoryDataLayer*)mLayerObject)->getWidth());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::DataLayer:
        {
            ((MMALab::DataLayer*)mLayerObject)->setSource(mStringManager->value(mPropertyBrowser->properties().at(1)).toStdString());
            ((MMALab::DataLayer*)mLayerObject)->setBatchSize(mIntManager->value(mPropertyBrowser->properties().at(2)));
            ((MMALab::DataLayer*)mLayerObject)->setRandSkip(mIntManager->value(mPropertyBrowser->properties().at(3)));
            ((MMALab::DataLayer*)mLayerObject)->setBackend((MMALab::DB)mEnumManager->value(mPropertyBrowser->properties().at(4)));
            ((MMALab::DataLayer*)mLayerObject)->setScale(mDoubleManager->value(mPropertyBrowser->properties().at(5)));
            ((MMALab::DataLayer*)mLayerObject)->setMeanfile(mStringManager->value(mPropertyBrowser->properties().at(6)).toStdString());
            ((MMALab::DataLayer*)mLayerObject)->setCropsize(mIntManager->value(mPropertyBrowser->properties().at(7)));
            ((MMALab::DataLayer*)mLayerObject)->setMirror(mBoolManager->value(mPropertyBrowser->properties().at(8)));
            ((MMALab::DataLayer*)mLayerObject)->setForceEncodedcolor(mBoolManager->value(mPropertyBrowser->properties().at(9)));
            ((MMALab::DataLayer*)mLayerObject)->setPrefetch(mIntManager->value(mPropertyBrowser->properties().at(10)));
            ((MMALab::DataLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::DataLayer*)mLayerObject)->getLayerType()) + "\n";
            mLayerInfo += "source: "+ QString::fromStdString(((MMALab::DataLayer*)mLayerObject)->getSource()) + "\n";
            mLayerInfo += "batch: "+ QString::number(((MMALab::DataLayer*)mLayerObject)->getBatchSize());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::HingeLossLayer:
        {
            ((MMALab::HingeLossLayer*)mLayerObject)->setNorm((MMALab::Norm)mEnumManager->value(mPropertyBrowser->properties().at(1)));
            ((MMALab::HingeLossLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::HingeLossLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::InfogainLossLayer:
        {
            ((MMALab::InfogainLossLayer*)mLayerObject)->setSource(mStringManager->value(mPropertyBrowser->properties().at(1)).toStdString());
            ((MMALab::InfogainLossLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::InfogainLossLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::ContrastiveLossLayer:
        {
            ((MMALab::ContrastiveLossLayer*)mLayerObject)->setMargin(mDoubleManager->value(mPropertyBrowser->properties().at(1)));
            ((MMALab::ContrastiveLossLayer*)mLayerObject)->setLegacyVersion((bool)mBoolManager->value(mPropertyBrowser->properties().at(2)));
            ((MMALab::ContrastiveLossLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::ContrastiveLossLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::MultinomialLogisticLossLayer:
        {
            ((MMALab::MultinomialLogisticLossLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::MultinomialLogisticLossLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::SigmoidCrossEntropyLossLayer:
        {
            ((MMALab::SigmoidCrossEntropyLossLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::SigmoidCrossEntropyLossLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::EuclideanLossLayer:
        {
            ((MMALab::EuclideanLossLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::EuclideanLossLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::SoftmaxWithLossLayer:
        {
            ((MMALab::SoftmaxWithLossLayer*)mLayerObject)->setEngine((MMALab::Engine)mEnumManager->value(mPropertyBrowser->properties().at(1)));
            ((MMALab::SoftmaxWithLossLayer*)mLayerObject)->setIgnoreLabel(mIntManager->value(mPropertyBrowser->properties().at(2)));
            ((MMALab::SoftmaxWithLossLayer*)mLayerObject)->setAxis(mIntManager->value(mPropertyBrowser->properties().at(3)));
            ((MMALab::SoftmaxWithLossLayer*)mLayerObject)->setNormalize(mBoolManager->value(mPropertyBrowser->properties().at(4)));
            ((MMALab::SoftmaxWithLossLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::SoftmaxWithLossLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::AccuracyLayer:
        {
            ((MMALab::AccuracyLayer*)mLayerObject)->setTopK(mIntManager->value(mPropertyBrowser->properties().at(1)));
            ((MMALab::AccuracyLayer*)mLayerObject)->setAxis(mIntManager->value(mPropertyBrowser->properties().at(2)));
            ((MMALab::AccuracyLayer*)mLayerObject)->setIgnoreLabel(mIntManager->value(mPropertyBrowser->properties().at(3)));
            ((MMALab::AccuracyLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::AccuracyLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::PReLULayer:
        {
            applyFilter(mPropertyBrowser->properties().at(1),
                        ((MMALab::PReLULayer*)mLayerObject)->getFilterType(),
                        ((MMALab::PReLULayer*)mLayerObject)->getFilter());

            ((MMALab::PReLULayer*)mLayerObject)->setChannelShared(mBoolManager->value(mPropertyBrowser->properties().at(2)));
            ((MMALab::PReLULayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::PReLULayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::ThresholdLayer:
        {
            ((MMALab::ThresholdLayer*)mLayerObject)->setThreshold(mDoubleManager->value(mPropertyBrowser->properties().at(1)));
            ((MMALab::ThresholdLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::ThresholdLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::TanHLayer:
        {
            ((MMALab::TanHLayer*)mLayerObject)->setEngine((MMALab::Engine)mEnumManager->value(mPropertyBrowser->properties().at(1)));
            ((MMALab::TanHLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::TanHLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::ReLULayer:
        {
            ((MMALab::ReLULayer*)mLayerObject)->setNegativeSlope(mDoubleManager->value(mPropertyBrowser->properties().at(1)));
            ((MMALab::ReLULayer*)mLayerObject)->setEngine((MMALab::Engine)mEnumManager->value(mPropertyBrowser->properties().at(2)));
            ((MMALab::ReLULayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::ReLULayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::SigmoidLayer:
        {
            ((MMALab::SigmoidLayer*)mLayerObject)->setEngine((MMALab::Engine)mEnumManager->value(mPropertyBrowser->properties().at(1)));
            ((MMALab::SigmoidLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::SigmoidLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::PowerLayer:
        {
            ((MMALab::PowerLayer*)mLayerObject)->setPower(mDoubleManager->value(mPropertyBrowser->properties().at(1)));
            ((MMALab::PowerLayer*)mLayerObject)->setScale(mDoubleManager->value(mPropertyBrowser->properties().at(2)));
            ((MMALab::PowerLayer*)mLayerObject)->setShift(mDoubleManager->value(mPropertyBrowser->properties().at(3)));
            ((MMALab::PowerLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::PowerLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::DropoutLayer:
        {
            ((MMALab::DropoutLayer*)mLayerObject)->setDropoutRatio(mDoubleManager->value(mPropertyBrowser->properties().at(1)));
            ((MMALab::DropoutLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::DropoutLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::ExpLayer:
        {
            ((MMALab::ExpLayer*)mLayerObject)->setBase(mDoubleManager->value(mPropertyBrowser->properties().at(1)));
            ((MMALab::ExpLayer*)mLayerObject)->setScale(mDoubleManager->value(mPropertyBrowser->properties().at(2)));
            ((MMALab::ExpLayer*)mLayerObject)->setShift(mDoubleManager->value(mPropertyBrowser->properties().at(3)));
            ((MMALab::ExpLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::ExpLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::LogLayer:
        {
            ((MMALab::LogLayer*)mLayerObject)->setBase(mDoubleManager->value(mPropertyBrowser->properties().at(1)));
            ((MMALab::LogLayer*)mLayerObject)->setScale(mDoubleManager->value(mPropertyBrowser->properties().at(2)));
            ((MMALab::LogLayer*)mLayerObject)->setShift(mDoubleManager->value(mPropertyBrowser->properties().at(3)));
            ((MMALab::LogLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::LogLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::AbsValLayer:
        {
            ((MMALab::AbsValLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::AbsValLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        case LayerGUI::BNLLLayer:
        {
            ((MMALab::BNLLLayer*)mLayerObject)->setLayerPhase((MMALab::Phase)mEnumManager->value(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1)));

            mLayerInfo = QString::fromStdString(((MMALab::BNLLLayer*)mLayerObject)->getLayerType());
            mLayerInfoItem->setPlainText(mLayerInfo);
            break;
        }
        default:
        {
            break;
        }
    }

    switch(((MMALab::BaseLayer*)mLayerObject)->getLayerPhase())
    {
        case 0: mLayerInfo += "\n TRAIN"; break;
        case 1: mLayerInfo += "\n TEST"; break;
    }
    mLayerInfoItem->setPlainText(mLayerInfo);
}

//set properties value
void LayerProperties::updateGUIProperties()
{
    mStringManager->setValue(mPropertyBrowser->properties().at(0), mLayerNameItem->toPlainText());
    switch (mLayer)
    {
        case LayerGUI::ConvolutionLayer:
        {
            mIntManager->setValue(mPropertyBrowser->properties().at(1), ((MMALab::ConvolutionLayer*)mLayerObject)->getNumOutput());
            mIntManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::ConvolutionLayer*)mLayerObject)->getKernelSize());
            mWeightFilterEnumManager->setValue(mPropertyBrowser->properties().at(3), ((MMALab::ConvolutionLayer*)mLayerObject)->getWeightfilterType());
            updateFilterGUIProperties(mPropertyBrowser->properties().at(3),
                                      ((MMALab::ConvolutionLayer*)mLayerObject)->getWeightfilterType(),
                                      ((MMALab::ConvolutionLayer*)mLayerObject)->getWeightfilter());
            mBiasFilterEnumManager->setValue(mPropertyBrowser->properties().at(4), ((MMALab::ConvolutionLayer*)mLayerObject)->getBiasfilterType());
            updateFilterGUIProperties(mPropertyBrowser->properties().at(4),
                                      ((MMALab::ConvolutionLayer*)mLayerObject)->getBiasfilterType(),
                                      ((MMALab::ConvolutionLayer*)mLayerObject)->getBiasfilter());
            mIntManager->setValue(mPropertyBrowser->properties().at(5), ((MMALab::ConvolutionLayer*)mLayerObject)->getPad());
            mIntManager->setValue(mPropertyBrowser->properties().at(6), ((MMALab::ConvolutionLayer*)mLayerObject)->getStride());
            mEnumManager->setValue(mPropertyBrowser->properties().at(7), ((MMALab::ConvolutionLayer*)mLayerObject)->getEngine());
            mIntManager->setValue(mPropertyBrowser->properties().at(8), ((MMALab::ConvolutionLayer*)mLayerObject)->getGroup());
            mBoolManager->setValue(mPropertyBrowser->properties().at(9), ((MMALab::ConvolutionLayer*)mLayerObject)->getBiasTerm());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(10), ((MMALab::ConvolutionLayer*)mLayerObject)->mFilterLRateMult);
            mDoubleManager->setValue(mPropertyBrowser->properties().at(11), ((MMALab::ConvolutionLayer*)mLayerObject)->mFilterDecayMult);
            mDoubleManager->setValue(mPropertyBrowser->properties().at(12), ((MMALab::ConvolutionLayer*)mLayerObject)->mBiasLRateMult);
            mDoubleManager->setValue(mPropertyBrowser->properties().at(13), ((MMALab::ConvolutionLayer*)mLayerObject)->mBiasDecayMult);
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::ConvolutionLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::PoolingLayer:
        {
            mIntManager->setValue(mPropertyBrowser->properties().at(1), ((MMALab::PoolingLayer*)mLayerObject)->getKernelSize());
            //mIntManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::PoolingLayer*)mLayerObject)->getKernelH());
            //mIntManager->setValue(mPropertyBrowser->properties().at(3), ((MMALab::PoolingLayer*)mLayerObject)->getKernelW());
            mIntManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::PoolingLayer*)mLayerObject)->getPad());
            //mIntManager->setValue(mPropertyBrowser->properties().at(5), ((MMALab::PoolingLayer*)mLayerObject)->getPadH());
            //mIntManager->setValue(mPropertyBrowser->properties().at(6), ((MMALab::PoolingLayer*)mLayerObject)->getPadW());
            mIntManager->setValue(mPropertyBrowser->properties().at(3), ((MMALab::PoolingLayer*)mLayerObject)->getStride());
            //mIntManager->setValue(mPropertyBrowser->properties().at(8), ((MMALab::PoolingLayer*)mLayerObject)->getStrideH());
            //mIntManager->setValue(mPropertyBrowser->properties().at(9), ((MMALab::PoolingLayer*)mLayerObject)->getStrideW());
            mEnumManager->setValue(mPropertyBrowser->properties().at(4), ((MMALab::PoolingLayer*)mLayerObject)->getPool());
            mEnumManager->setValue(mPropertyBrowser->properties().at(5), ((MMALab::PoolingLayer*)mLayerObject)->getEngine());
            mBoolManager->setValue(mPropertyBrowser->properties().at(6), ((MMALab::PoolingLayer*)mLayerObject)->getGlobalPooling());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::PoolingLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::SPPLayer:
        {
            mIntManager->setValue(mPropertyBrowser->properties().at(1), ((MMALab::SPPLayer*)mLayerObject)->getPyramidHeight());
            mEnumManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::SPPLayer*)mLayerObject)->getPool());
            mEnumManager->setValue(mPropertyBrowser->properties().at(3), ((MMALab::SPPLayer*)mLayerObject)->getEngine());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::SPPLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::LRNLayer:
        {
            mIntManager->setValue(mPropertyBrowser->properties().at(1), ((MMALab::LRNLayer*)mLayerObject)->getLocalSize());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::LRNLayer*)mLayerObject)->getAlpha());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(3), ((MMALab::LRNLayer*)mLayerObject)->getBeta());
            mEnumManager->setValue(mPropertyBrowser->properties().at(4), ((MMALab::LRNLayer*)mLayerObject)->getNormRegion());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(5), ((MMALab::LRNLayer*)mLayerObject)->getK());
            mEnumManager->setValue(mPropertyBrowser->properties().at(6), ((MMALab::LRNLayer*)mLayerObject)->getEngine());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::LRNLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::MVNLayer:
        {
            mBoolManager->setValue(mPropertyBrowser->properties().at(1), ((MMALab::MVNLayer*)mLayerObject)->getNormalizeVariance());
            mBoolManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::MVNLayer*)mLayerObject)->getAcrossChannels());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(3), ((MMALab::MVNLayer*)mLayerObject)->getEps());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::MVNLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::ReshapeLayer:
        {
            updateBlobShapeProperties(mPropertyBrowser->properties().at(1), ((MMALab::ReshapeLayer*)mLayerObject)->getShape());
            mIntManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::ReshapeLayer*)mLayerObject)->getAxis());
            mIntManager->setValue(mPropertyBrowser->properties().at(3), ((MMALab::ReshapeLayer*)mLayerObject)->getNumAxis());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::ReshapeLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::SliceLayer:
        {
            mIntManager->setValue(mPropertyBrowser->properties().at(1), ((MMALab::SliceLayer*)mLayerObject)->getAxis());
            mIntManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::SliceLayer*)mLayerObject)->getSlicePoint());
            mIntManager->setValue(mPropertyBrowser->properties().at(3), ((MMALab::SliceLayer*)mLayerObject)->getSliceDim());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::SliceLayer*)mLayerObject)->getLayerPhase());

            break;
        }
        case LayerGUI::InnerProductLayer:
        {
            mIntManager->setValue(mPropertyBrowser->properties().at(1), ((MMALab::InnerProductLayer*)mLayerObject)->getNumOutput());
            mBoolManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::InnerProductLayer*)mLayerObject)->getBiasTerm());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::InnerProductLayer*)mLayerObject)->getLayerPhase());

            mWeightFilterEnumManager->setValue(mPropertyBrowser->properties().at(3), ((MMALab::InnerProductLayer*)mLayerObject)->getWeightfilterType());
            updateFilterGUIProperties(mPropertyBrowser->properties().at(3),
                                      ((MMALab::InnerProductLayer*)mLayerObject)->getWeightfilterType(),
                                      ((MMALab::InnerProductLayer*)mLayerObject)->getWeightfilter());
            mBiasFilterEnumManager->setValue(mPropertyBrowser->properties().at(4), ((MMALab::InnerProductLayer*)mLayerObject)->getBiasfilterType());
            updateFilterGUIProperties(mPropertyBrowser->properties().at(4),
                                      ((MMALab::InnerProductLayer*)mLayerObject)->getBiasfilterType(),
                                      ((MMALab::InnerProductLayer*)mLayerObject)->getBiasfilter());

            mIntManager->setValue(mPropertyBrowser->properties().at(5), ((MMALab::InnerProductLayer*)mLayerObject)->getAxis());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(6), ((MMALab::InnerProductLayer*)mLayerObject)->mFilterLRateMult);
            mDoubleManager->setValue(mPropertyBrowser->properties().at(7), ((MMALab::InnerProductLayer*)mLayerObject)->mFilterDecayMult);
            mDoubleManager->setValue(mPropertyBrowser->properties().at(8), ((MMALab::InnerProductLayer*)mLayerObject)->mBiasLRateMult);
            mDoubleManager->setValue(mPropertyBrowser->properties().at(9), ((MMALab::InnerProductLayer*)mLayerObject)->mBiasDecayMult);
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::InnerProductLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::SoftmaxLayer:
        {
            mEnumManager->setValue(mPropertyBrowser->properties().at(1), ((MMALab::SoftmaxLayer*)mLayerObject)->getEngine());
            mIntManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::SoftmaxLayer*)mLayerObject)->getAxis());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::SoftmaxLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::FlattenLayer:
        {
            mIntManager->setValue(mPropertyBrowser->properties().at(1), ((MMALab::FlattenLayer*)mLayerObject)->getAxis());
            mIntManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::FlattenLayer*)mLayerObject)->getEndAxis());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::FlattenLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::EltwiseLayer:
        {
            mEnumManager->setValue(mPropertyBrowser->properties().at(1), ((MMALab::EltwiseLayer*)mLayerObject)->getOperation());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::EltwiseLayer*)mLayerObject)->getCoeff());
            mBoolManager->setValue(mPropertyBrowser->properties().at(3), ((MMALab::EltwiseLayer*)mLayerObject)->getStableProdGrad());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::EltwiseLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::ConcatLayer:
        {
            mIntManager->setValue(mPropertyBrowser->properties().at(1), ((MMALab::ConcatLayer*)mLayerObject)->getAxis());
            mIntManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::ConcatLayer*)mLayerObject)->getConcatDim());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::ConcatLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::ArgMaxLayer:
        {
            mBoolManager->setValue(mPropertyBrowser->properties().at(1), ((MMALab::ArgMaxLayer*)mLayerObject)->getOutMaxVal());
            mIntManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::ArgMaxLayer*)mLayerObject)->getTopK());
            mIntManager->setValue(mPropertyBrowser->properties().at(3), ((MMALab::ArgMaxLayer*)mLayerObject)->getAxis());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::ArgMaxLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::ReductionLayer:
        {
            mEnumManager->setValue(mPropertyBrowser->properties().at(1), ((MMALab::ReductionLayer*)mLayerObject)->getOperation());
            mIntManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::ReductionLayer*)mLayerObject)->getAxis());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(3), ((MMALab::ReductionLayer*)mLayerObject)->getCoeff());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::ReductionLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::DummyDataLayer:
        {
            updateBlobShapeProperties(mPropertyBrowser->properties().at(1), ((MMALab::DummyDataLayer*)mLayerObject)->getShape());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::DummyDataLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::HDF5OutputLayer:
        {
            mStringManager->setValue(mPropertyBrowser->properties().at(1), QString::fromStdString(((MMALab::HDF5OutputLayer*)mLayerObject)->getFileName()));
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::HDF5OutputLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::HDF5DataLayer:
        {
            mStringManager->setValue(mPropertyBrowser->properties().at(1), QString::fromStdString(((MMALab::HDF5DataLayer*)mLayerObject)->getSource()));
            mIntManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::HDF5DataLayer*)mLayerObject)->getBatchSize());
            mBoolManager->setValue(mPropertyBrowser->properties().at(3), ((MMALab::HDF5DataLayer*)mLayerObject)->getShuffle());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::HDF5DataLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::WindowDataLayer:
        {
            mStringManager->setValue(mPropertyBrowser->properties().at(1), QString::fromStdString(((MMALab::WindowDataLayer*)mLayerObject)->getSource()));
            mDoubleManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::WindowDataLayer*)mLayerObject)->getScale());
            mStringManager->setValue(mPropertyBrowser->properties().at(3), QString::fromStdString(((MMALab::WindowDataLayer*)mLayerObject)->getMeanFile()));
            mIntManager->setValue(mPropertyBrowser->properties().at(4), ((MMALab::WindowDataLayer*)mLayerObject)->getBatchSize());
            mIntManager->setValue(mPropertyBrowser->properties().at(5), ((MMALab::WindowDataLayer*)mLayerObject)->getCropSize());
            mBoolManager->setValue(mPropertyBrowser->properties().at(6), ((MMALab::WindowDataLayer*)mLayerObject)->getMirror());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(7), ((MMALab::WindowDataLayer*)mLayerObject)->getFgThreshold());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(8), ((MMALab::WindowDataLayer*)mLayerObject)->getBgThreshold());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(9), ((MMALab::WindowDataLayer*)mLayerObject)->getFgFraction());
            mIntManager->setValue(mPropertyBrowser->properties().at(10), ((MMALab::WindowDataLayer*)mLayerObject)->getContextPad());
            mEnumManager->setValue(mPropertyBrowser->properties().at(11), ((MMALab::WindowDataLayer*)mLayerObject)->getCropMode());
            mBoolManager->setValue(mPropertyBrowser->properties().at(12), ((MMALab::WindowDataLayer*)mLayerObject)->getCacheImages());
            mStringManager->setValue(mPropertyBrowser->properties().at(13), QString::fromStdString(((MMALab::WindowDataLayer*)mLayerObject)->getRootFolder()));
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::WindowDataLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::ImageDataLayer:
        {
            mStringManager->setValue(mPropertyBrowser->properties().at(1), QString::fromStdString(((MMALab::ImageDataLayer*)mLayerObject)->getSource()));
            mIntManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::ImageDataLayer*)mLayerObject)->getBatchSize());
            mIntManager->setValue(mPropertyBrowser->properties().at(3), ((MMALab::ImageDataLayer*)mLayerObject)->getRandSkip());
            mBoolManager->setValue(mPropertyBrowser->properties().at(4), ((MMALab::ImageDataLayer*)mLayerObject)->getShuffle());
            mIntManager->setValue(mPropertyBrowser->properties().at(5), ((MMALab::ImageDataLayer*)mLayerObject)->getNewHeight());
            mIntManager->setValue(mPropertyBrowser->properties().at(6), ((MMALab::ImageDataLayer*)mLayerObject)->getNewWidth());
            mBoolManager->setValue(mPropertyBrowser->properties().at(7), ((MMALab::ImageDataLayer*)mLayerObject)->getIsColor());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(8), ((MMALab::ImageDataLayer*)mLayerObject)->getScale());
            mStringManager->setValue(mPropertyBrowser->properties().at(9), QString::fromStdString(((MMALab::ImageDataLayer*)mLayerObject)->getMeanFile()));
            mIntManager->setValue(mPropertyBrowser->properties().at(10), ((MMALab::ImageDataLayer*)mLayerObject)->getCropSize());
            mBoolManager->setValue(mPropertyBrowser->properties().at(11), ((MMALab::ImageDataLayer*)mLayerObject)->getMirror());
            mStringManager->setValue(mPropertyBrowser->properties().at(12), QString::fromStdString(((MMALab::ImageDataLayer*)mLayerObject)->getRootFolder()));
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::ImageDataLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::MemoryDataLayer:
        {
            mIntManager->setValue(mPropertyBrowser->properties().at(1), ((MMALab::MemoryDataLayer*)mLayerObject)->getBatchSize());
            mIntManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::MemoryDataLayer*)mLayerObject)->getChannels());
            mIntManager->setValue(mPropertyBrowser->properties().at(3), ((MMALab::MemoryDataLayer*)mLayerObject)->getHeight());
            mIntManager->setValue(mPropertyBrowser->properties().at(4), ((MMALab::MemoryDataLayer*)mLayerObject)->getWidth());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::MemoryDataLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::DataLayer:
        {
            mStringManager->setValue(mPropertyBrowser->properties().at(1), QString::fromStdString(((MMALab::DataLayer*)mLayerObject)->getSource()));
            mIntManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::DataLayer*)mLayerObject)->getBatchSize());
            mIntManager->setValue(mPropertyBrowser->properties().at(3), ((MMALab::DataLayer*)mLayerObject)->getRandSkip());
            mEnumManager->setValue(mPropertyBrowser->properties().at(4), ((MMALab::DataLayer*)mLayerObject)->getBackend());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(5), ((MMALab::DataLayer*)mLayerObject)->getScale());
            mStringManager->setValue(mPropertyBrowser->properties().at(6), QString::fromStdString(((MMALab::DataLayer*)mLayerObject)->getMeanfile()));
            mIntManager->setValue(mPropertyBrowser->properties().at(7), ((MMALab::DataLayer*)mLayerObject)->getCropsize());
            mBoolManager->setValue(mPropertyBrowser->properties().at(8), ((MMALab::DataLayer*)mLayerObject)->getMirror());
            mBoolManager->setValue(mPropertyBrowser->properties().at(9), ((MMALab::DataLayer*)mLayerObject)->getForceEncodedcolor());
            mIntManager->setValue(mPropertyBrowser->properties().at(10), ((MMALab::DataLayer*)mLayerObject)->getPrefetch());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::DataLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::HingeLossLayer:
        {
            mEnumManager->setValue(mPropertyBrowser->properties().at(1), ((MMALab::HingeLossLayer*)mLayerObject)->getNorm());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::HingeLossLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::InfogainLossLayer:
        {
            mStringManager->setValue(mPropertyBrowser->properties().at(1), QString::fromStdString(((MMALab::InfogainLossLayer*)mLayerObject)->getSource()));
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::InfogainLossLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::ContrastiveLossLayer:
        {
            mDoubleManager->setValue(mPropertyBrowser->properties().at(1), ((MMALab::ContrastiveLossLayer*)mLayerObject)->getMargin());
            mBoolManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::ContrastiveLossLayer*)mLayerObject)->getLegacyVersion());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::ContrastiveLossLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::MultinomialLogisticLossLayer:
        {
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::MultinomialLogisticLossLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::SigmoidCrossEntropyLossLayer:
        {
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::SigmoidCrossEntropyLossLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::EuclideanLossLayer:
        {
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::EuclideanLossLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::SoftmaxWithLossLayer:
        {
            mEnumManager->setValue(mPropertyBrowser->properties().at(1), ((MMALab::SoftmaxWithLossLayer*)mLayerObject)->getEngine());
            mIntManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::SoftmaxWithLossLayer*)mLayerObject)->getIgnoreLabel());
            mIntManager->setValue(mPropertyBrowser->properties().at(3), ((MMALab::SoftmaxWithLossLayer*)mLayerObject)->getAxis());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(4), ((MMALab::SoftmaxWithLossLayer*)mLayerObject)->getNormalize());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::SoftmaxWithLossLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::AccuracyLayer:
        {
            mIntManager->setValue(mPropertyBrowser->properties().at(1), ((MMALab::AccuracyLayer*)mLayerObject)->getTopK());
            mIntManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::AccuracyLayer*)mLayerObject)->getAxis());
            mIntManager->setValue(mPropertyBrowser->properties().at(3), ((MMALab::AccuracyLayer*)mLayerObject)->getIgnoreLabel());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::AccuracyLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::PReLULayer:
        {
            mWeightFilterEnumManager->setValue(mPropertyBrowser->properties().at(1), ((MMALab::PReLULayer*)mLayerObject)->getFilterType());

            updateFilterGUIProperties(mPropertyBrowser->properties().at(1),
                                      ((MMALab::PReLULayer*)mLayerObject)->getFilterType(),
                                      ((MMALab::PReLULayer*)mLayerObject)->getFilter());

            mBoolManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::PReLULayer*)mLayerObject)->getChannelShared());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::PReLULayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::ThresholdLayer:
        {
            mDoubleManager->setValue(mPropertyBrowser->properties().at(1), ((MMALab::ThresholdLayer*)mLayerObject)->getThreshold());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::ThresholdLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::TanHLayer:
        {
            mEnumManager->setValue(mPropertyBrowser->properties().at(1), ((MMALab::TanHLayer*)mLayerObject)->getEngine());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::TanHLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::ReLULayer:
        {
            mDoubleManager->setValue(mPropertyBrowser->properties().at(1), ((MMALab::ReLULayer*)mLayerObject)->getNegativeSlope());
            mEnumManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::ReLULayer*)mLayerObject)->getEngine());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::ReLULayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::SigmoidLayer:
        {
            mEnumManager->setValue(mPropertyBrowser->properties().at(1), ((MMALab::SigmoidLayer*)mLayerObject)->getEngine());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::SigmoidLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::PowerLayer:
        {
            mDoubleManager->setValue(mPropertyBrowser->properties().at(1), ((MMALab::PowerLayer*)mLayerObject)->getPower());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::PowerLayer*)mLayerObject)->getScale());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(3), ((MMALab::PowerLayer*)mLayerObject)->getShift());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::PowerLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::DropoutLayer:
        {
            mDoubleManager->setValue(mPropertyBrowser->properties().at(1), ((MMALab::DropoutLayer*)mLayerObject)->getDropoutRatio());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::DropoutLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::ExpLayer:
        {
            mDoubleManager->setValue(mPropertyBrowser->properties().at(1), ((MMALab::ExpLayer*)mLayerObject)->getBase());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::ExpLayer*)mLayerObject)->getScale());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(3), ((MMALab::ExpLayer*)mLayerObject)->getShift());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::ExpLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::LogLayer:
        {
            mDoubleManager->setValue(mPropertyBrowser->properties().at(1), ((MMALab::LogLayer*)mLayerObject)->getBase());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::LogLayer*)mLayerObject)->getScale());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(3), ((MMALab::LogLayer*)mLayerObject)->getShift());
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::LogLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::AbsValLayer:
        {
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::AbsValLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        case LayerGUI::BNLLLayer:
        {
            mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), ((MMALab::BNLLLayer*)mLayerObject)->getLayerPhase());
            break;
        }
        default:
        {
            break;
        }
    }

}

void LayerProperties::updateGUIProperties(LayerParameter layerParam)
{
    if(mLayer == LayerGUI::DataBlob)
    {
        mStringManager->setValue(mPropertyBrowser->properties().at(0), mLayerNameItem->toPlainText());
    }
    else
    {
        mStringManager->setValue(mPropertyBrowser->properties().at(0), QString::fromStdString(layerParam.name()));
    }
    int phase = MMALab::Phase::BOTH;
    for(unsigned int i = 0; i < layerParam.include_size(); i++)
    {
        if(layerParam.include(i).has_phase())
        {
            phase = layerParam.include(i).phase();
        }
    }
    mEnumManager->setValue(mPropertyBrowser->properties().at(mPropertyBrowser->properties().size() - 1), phase);
    switch (mLayer)
    {
        case LayerGUI::ConvolutionLayer:
        {
            mIntManager->setValue(mPropertyBrowser->properties().at(1), layerParam.convolution_param().num_output());
            for(int k = 0; k < layerParam.convolution_param().kernel_size().size(); k++)
            {
                mIntManager->setValue(mPropertyBrowser->properties().at(2), layerParam.convolution_param().kernel_size().Get(k));
            }
            mWeightFilterEnumManager->setValue(mPropertyBrowser->properties().at(3),  selectFilterType(layerParam.convolution_param().weight_filler().type()));
            updateFilterGUIProperties(mPropertyBrowser->properties().at(3),
                                      FilterType(selectFilterType(layerParam.convolution_param().weight_filler().type())),
                                      layerParam.convolution_param().weight_filler());
            mBiasFilterEnumManager->setValue(mPropertyBrowser->properties().at(4),  selectFilterType(layerParam.convolution_param().bias_filler().type()));
            updateFilterGUIProperties(mPropertyBrowser->properties().at(4),
                                      FilterType(selectFilterType(layerParam.convolution_param().bias_filler().type())),
                                      layerParam.convolution_param().bias_filler());

            for(int k = 0; k < layerParam.convolution_param().pad().size(); k++)
            {
                mIntManager->setValue(mPropertyBrowser->properties().at(5), layerParam.convolution_param().pad().Get(k));
            }
            if(layerParam.convolution_param().stride().size() == 0)
            {
                mIntManager->setValue(mPropertyBrowser->properties().at(6), ((MMALab::ConvolutionLayer*)mLayerObject)->getStride());
            }
            else
            {
                for(int k = 0; k < layerParam.convolution_param().stride().size(); k++)
                {
                    mIntManager->setValue(mPropertyBrowser->properties().at(6), layerParam.convolution_param().stride().Get(k));
                }
            }
            mEnumManager->setValue(mPropertyBrowser->properties().at(7), layerParam.convolution_param().engine());
            mIntManager->setValue(mPropertyBrowser->properties().at(8), layerParam.convolution_param().group());
            mBoolManager->setValue(mPropertyBrowser->properties().at(9), layerParam.convolution_param().bias_term());

            for(unsigned int i = 0; i < layerParam.param_size(); i++)
            {
                switch (i)
                {
                    case 0 :
                        mDoubleManager->setValue(mPropertyBrowser->properties().at(10), (int)layerParam.param(i).lr_mult());
                        mDoubleManager->setValue(mPropertyBrowser->properties().at(11), (float)layerParam.param(i).decay_mult());
                        break;
                    case 1:
                        mDoubleManager->setValue(mPropertyBrowser->properties().at(12), (int)layerParam.param(i).lr_mult());
                        mDoubleManager->setValue(mPropertyBrowser->properties().at(13), (float)layerParam.param(i).decay_mult());
                        break;
                }
            }
            break;
        }
        case LayerGUI::PoolingLayer:
        {
            mIntManager->setValue(mPropertyBrowser->properties().at(1), layerParam.pooling_param().kernel_size());
            //mIntManager->setValue(mPropertyBrowser->properties().at(2), layerParam.pooling_param().kernel_h());
            //mIntManager->setValue(mPropertyBrowser->properties().at(3), layerParam.pooling_param().kernel_w());
            mIntManager->setValue(mPropertyBrowser->properties().at(2), layerParam.pooling_param().pad());
            //mIntManager->setValue(mPropertyBrowser->properties().at(5), layerParam.pooling_param().pad_h());
            //mIntManager->setValue(mPropertyBrowser->properties().at(6), layerParam.pooling_param().pad_w());
            mIntManager->setValue(mPropertyBrowser->properties().at(3), layerParam.pooling_param().stride());
            //mIntManager->setValue(mPropertyBrowser->properties().at(8), layerParam.pooling_param().stride_h());
            //mIntManager->setValue(mPropertyBrowser->properties().at(9), layerParam.pooling_param().stride_w());
            mEnumManager->setValue(mPropertyBrowser->properties().at(4), layerParam.pooling_param().pool());
            mEnumManager->setValue(mPropertyBrowser->properties().at(5), layerParam.pooling_param().engine());
            mBoolManager->setValue(mPropertyBrowser->properties().at(6), layerParam.pooling_param().global_pooling());
            break;
        }
        case LayerGUI::SPPLayer:
        {
            mIntManager->setValue(mPropertyBrowser->properties().at(1), layerParam.spp_param().pyramid_height());
            mEnumManager->setValue(mPropertyBrowser->properties().at(2), layerParam.spp_param().pool());
            mEnumManager->setValue(mPropertyBrowser->properties().at(3), layerParam.spp_param().engine());
            break;
        }
        case LayerGUI::LRNLayer:
        {
            mIntManager->setValue(mPropertyBrowser->properties().at(1), layerParam.lrn_param().local_size());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(2), layerParam.lrn_param().alpha());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(3), layerParam.lrn_param().beta());
            mEnumManager->setValue(mPropertyBrowser->properties().at(4), layerParam.lrn_param().norm_region());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(5), layerParam.lrn_param().k());
            mEnumManager->setValue(mPropertyBrowser->properties().at(6), layerParam.lrn_param().engine());
            break;
        }
        case LayerGUI::MVNLayer:
        {
            mDoubleManager->setValue(mPropertyBrowser->properties().at(1), layerParam.mvn_param().normalize_variance());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(2), layerParam.mvn_param().across_channels());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(3), layerParam.mvn_param().eps());
            break;
        }
        case LayerGUI::ReshapeLayer:
        {
            mBlobShapeIntManager->setValue(mPropertyBrowser->properties().at(1), layerParam.reshape_param().has_shape());
            if(layerParam.reshape_param().has_shape())
            {
                updateBlobShapeProperties(mPropertyBrowser->properties().at(1)->subProperties().at(0), layerParam.reshape_param().shape());
            }
            mIntManager->setValue(mPropertyBrowser->properties().at(2), layerParam.reshape_param().axis());
            mIntManager->setValue(mPropertyBrowser->properties().at(3), layerParam.reshape_param().num_axes());
            break;
        }
        case LayerGUI::SliceLayer:
        {
            mIntManager->setValue(mPropertyBrowser->properties().at(1), layerParam.slice_param().axis());
            for(int k = 0; k < layerParam.slice_param().slice_point().size(); k++)
            {
                mIntManager->setValue(mPropertyBrowser->properties().at(2), layerParam.slice_param().slice_point().Get(k));
            }
            mIntManager->setValue(mPropertyBrowser->properties().at(3), layerParam.slice_param().slice_dim());

            break;
        }
        case LayerGUI::InnerProductLayer:
        {
            mIntManager->setValue(mPropertyBrowser->properties().at(1), layerParam.inner_product_param().num_output());
            mBoolManager->setValue(mPropertyBrowser->properties().at(2), layerParam.inner_product_param().bias_term());

            mWeightFilterEnumManager->setValue(mPropertyBrowser->properties().at(3),  selectFilterType(layerParam.inner_product_param().weight_filler().type()));
            updateFilterGUIProperties(mPropertyBrowser->properties().at(3),
                                      FilterType(selectFilterType(layerParam.inner_product_param().weight_filler().type())),
                                      layerParam.inner_product_param().weight_filler());
            mBiasFilterEnumManager->setValue(mPropertyBrowser->properties().at(4),  selectFilterType(layerParam.inner_product_param().bias_filler().type()));
            updateFilterGUIProperties(mPropertyBrowser->properties().at(4),
                                      FilterType(selectFilterType(layerParam.inner_product_param().bias_filler().type())),
                                      layerParam.inner_product_param().bias_filler());

            mIntManager->setValue(mPropertyBrowser->properties().at(5), layerParam.inner_product_param().axis());

            for(unsigned int i = 0; i < layerParam.param_size(); i++)
            {
                switch (i)
                {
                    case 0 :
                        mDoubleManager->setValue(mPropertyBrowser->properties().at(6), (int)layerParam.param(i).lr_mult());
                        mDoubleManager->setValue(mPropertyBrowser->properties().at(7), (float)layerParam.param(i).decay_mult());
                        break;
                    case 1:
                        mDoubleManager->setValue(mPropertyBrowser->properties().at(8), (int)layerParam.param(i).lr_mult());
                        mDoubleManager->setValue(mPropertyBrowser->properties().at(9), (float)layerParam.param(i).decay_mult());
                        break;
                }
            }
            break;
        }
        case LayerGUI::SoftmaxLayer:
        {
            mEnumManager->setValue(mPropertyBrowser->properties().at(1), layerParam.softmax_param().engine());
            mIntManager->setValue(mPropertyBrowser->properties().at(2), layerParam.softmax_param().axis());
            break;
        }
        case LayerGUI::FlattenLayer:
        {
            mIntManager->setValue(mPropertyBrowser->properties().at(1), layerParam.flatten_param().axis());
            mIntManager->setValue(mPropertyBrowser->properties().at(2), layerParam.flatten_param().end_axis());
            break;
        }
        case LayerGUI::EltwiseLayer:
        {
            mEnumManager->setValue(mPropertyBrowser->properties().at(1), layerParam.eltwise_param().operation());
            for(int k = 0; k < layerParam.eltwise_param().coeff().size(); k++)
            {
                mIntManager->setValue(mPropertyBrowser->properties().at(2), layerParam.eltwise_param().coeff().Get(k));
            }
            mBoolManager->setValue(mPropertyBrowser->properties().at(3), layerParam.eltwise_param().stable_prod_grad());
            break;
        }
        case LayerGUI::ConcatLayer:
        {
            mIntManager->setValue(mPropertyBrowser->properties().at(1), layerParam.concat_param().axis());
            mIntManager->setValue(mPropertyBrowser->properties().at(2), layerParam.concat_param().concat_dim());
            break;
        }
        case LayerGUI::ArgMaxLayer:
        {
            mBoolManager->setValue(mPropertyBrowser->properties().at(1), layerParam.argmax_param().out_max_val());
            mIntManager->setValue(mPropertyBrowser->properties().at(2), layerParam.argmax_param().top_k());
            mIntManager->setValue(mPropertyBrowser->properties().at(3), layerParam.argmax_param().axis());
            break;
        }
        case LayerGUI::ReductionLayer:
        {
            mEnumManager->setValue(mPropertyBrowser->properties().at(1), layerParam.reduction_param().operation());
            mIntManager->setValue(mPropertyBrowser->properties().at(2), layerParam.reduction_param().axis());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(3), layerParam.reduction_param().coeff());
        }
        case LayerGUI::DummyDataLayer:
        {
            mBlobShapeIntManager->setValue(mPropertyBrowser->properties().at(1), layerParam.dummy_data_param().shape_size());
            for(int i = 0; i < layerParam.dummy_data_param().shape_size(); i++)
            {
                updateBlobShapeProperties(mPropertyBrowser->properties().at(1)->subProperties().at(i), layerParam.dummy_data_param().shape(i));
            }
            break;
        }
        case LayerGUI::HDF5OutputLayer:
        {
            mStringManager->setValue(mPropertyBrowser->properties().at(1), QString::fromStdString(layerParam.hdf5_output_param().file_name()));
            break;
        }
        case LayerGUI::HDF5DataLayer:
        {
            mStringManager->setValue(mPropertyBrowser->properties().at(1), QString::fromStdString(layerParam.hdf5_data_param().source()));
            mIntManager->setValue(mPropertyBrowser->properties().at(2), layerParam.hdf5_data_param().batch_size());
            mBoolManager->setValue(mPropertyBrowser->properties().at(3), layerParam.hdf5_data_param().shuffle());
            break;
        }
        case LayerGUI::WindowDataLayer:
        {
            mStringManager->setValue(mPropertyBrowser->properties().at(1), QString::fromStdString(layerParam.window_data_param().source()));
            mDoubleManager->setValue(mPropertyBrowser->properties().at(2), layerParam.window_data_param().scale());
            mStringManager->setValue(mPropertyBrowser->properties().at(3), QString::fromStdString(layerParam.window_data_param().mean_file()));
            mIntManager->setValue(mPropertyBrowser->properties().at(4), layerParam.window_data_param().batch_size());
            mIntManager->setValue(mPropertyBrowser->properties().at(5), layerParam.window_data_param().crop_size());
            mBoolManager->setValue(mPropertyBrowser->properties().at(6), layerParam.window_data_param().mirror());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(7), layerParam.window_data_param().fg_threshold());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(8), layerParam.window_data_param().bg_threshold());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(9), layerParam.window_data_param().fg_fraction());
            mIntManager->setValue(mPropertyBrowser->properties().at(10), layerParam.window_data_param().context_pad());
            mEnumManager->setValue(mPropertyBrowser->properties().at(11), selectCropMode(layerParam.window_data_param().crop_mode()));
            mBoolManager->setValue(mPropertyBrowser->properties().at(12), layerParam.window_data_param().cache_images());
            mStringManager->setValue(mPropertyBrowser->properties().at(13), QString::fromStdString(layerParam.window_data_param().root_folder()));
            break;
        }
        case LayerGUI::ImageDataLayer:
        {
            mStringManager->setValue(mPropertyBrowser->properties().at(1), QString::fromStdString(layerParam.image_data_param().source()));
            mIntManager->setValue(mPropertyBrowser->properties().at(2), layerParam.image_data_param().batch_size());
            mIntManager->setValue(mPropertyBrowser->properties().at(3), layerParam.image_data_param().rand_skip());
            mBoolManager->setValue(mPropertyBrowser->properties().at(4), layerParam.image_data_param().shuffle());
            mIntManager->setValue(mPropertyBrowser->properties().at(5), layerParam.image_data_param().new_height());
            mIntManager->setValue(mPropertyBrowser->properties().at(6), layerParam.image_data_param().new_width());
            mBoolManager->setValue(mPropertyBrowser->properties().at(7), layerParam.image_data_param().is_color());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(8), layerParam.transform_param().scale());
            mStringManager->setValue(mPropertyBrowser->properties().at(9), QString::fromStdString(layerParam.transform_param().mean_file()));
            mIntManager->setValue(mPropertyBrowser->properties().at(10), layerParam.transform_param().crop_size());
            mBoolManager->setValue(mPropertyBrowser->properties().at(11), layerParam.transform_param().mirror());
            mStringManager->setValue(mPropertyBrowser->properties().at(12), QString::fromStdString(layerParam.image_data_param().root_folder()));
            break;
        }
        case LayerGUI::MemoryDataLayer:
        {
            mIntManager->setValue(mPropertyBrowser->properties().at(1), layerParam.memory_data_param().batch_size());
            mIntManager->setValue(mPropertyBrowser->properties().at(2), layerParam.memory_data_param().channels());
            mIntManager->setValue(mPropertyBrowser->properties().at(3), layerParam.memory_data_param().height());
            mIntManager->setValue(mPropertyBrowser->properties().at(4), layerParam.memory_data_param().width());
            break;
        }
        case LayerGUI::DataLayer:
        {
            mStringManager->setValue(mPropertyBrowser->properties().at(1), QString::fromStdString(layerParam.data_param().source()));
            mIntManager->setValue(mPropertyBrowser->properties().at(2), layerParam.data_param().batch_size());
            mIntManager->setValue(mPropertyBrowser->properties().at(3), layerParam.data_param().rand_skip());
            mEnumManager->setValue(mPropertyBrowser->properties().at(4), layerParam.data_param().backend());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(5), layerParam.transform_param().scale());
            mStringManager->setValue(mPropertyBrowser->properties().at(6), QString::fromStdString(layerParam.transform_param().mean_file()));
            mIntManager->setValue(mPropertyBrowser->properties().at(7), layerParam.transform_param().crop_size());
            mBoolManager->setValue(mPropertyBrowser->properties().at(8), layerParam.transform_param().mirror());
            mBoolManager->setValue(mPropertyBrowser->properties().at(9), layerParam.data_param().force_encoded_color());
            mIntManager->setValue(mPropertyBrowser->properties().at(10), layerParam.data_param().prefetch());
            break;
        }
        case LayerGUI::HingeLossLayer:
        {
            mEnumManager->setValue(mPropertyBrowser->properties().at(1), layerParam.hinge_loss_param().norm()-1);
            break;
        }
        case LayerGUI::InfogainLossLayer:
        {
            mStringManager->setValue(mPropertyBrowser->properties().at(1), QString::fromStdString(layerParam.infogain_loss_param().source()));
            break;
        }
        case LayerGUI::ContrastiveLossLayer:
        {
            mDoubleManager->setValue(mPropertyBrowser->properties().at(1), layerParam.contrastive_loss_param().margin());
            mBoolManager->setValue(mPropertyBrowser->properties().at(2), layerParam.contrastive_loss_param().legacy_version());
            break;
        }
        case LayerGUI::MultinomialLogisticLossLayer:
        {
            break;
        }
        case LayerGUI::SigmoidCrossEntropyLossLayer:
        {
            break;
        }
        case LayerGUI::EuclideanLossLayer:
        {
            break;
        }
        case LayerGUI::SoftmaxWithLossLayer:
        {
            mEnumManager->setValue(mPropertyBrowser->properties().at(1), ((MMALab::SoftmaxWithLossLayer*)mLayerObject)->getEngine());
            mIntManager->setValue(mPropertyBrowser->properties().at(2), ((MMALab::SoftmaxWithLossLayer*)mLayerObject)->getIgnoreLabel());
            mIntManager->setValue(mPropertyBrowser->properties().at(3), ((MMALab::SoftmaxWithLossLayer*)mLayerObject)->getAxis());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(4), ((MMALab::SoftmaxWithLossLayer*)mLayerObject)->getNormalize());
            break;
        }
        case LayerGUI::AccuracyLayer:
        {
            mIntManager->setValue(mPropertyBrowser->properties().at(1), layerParam.accuracy_param().top_k());
            mIntManager->setValue(mPropertyBrowser->properties().at(2), layerParam.accuracy_param().axis());
            mIntManager->setValue(mPropertyBrowser->properties().at(3), layerParam.accuracy_param().ignore_label());
            break;
        }
        case LayerGUI::PReLULayer:
        {
        mWeightFilterEnumManager->setValue(mPropertyBrowser->properties().at(1),  selectFilterType(layerParam.prelu_param().filler().type()));
        updateFilterGUIProperties(mPropertyBrowser->properties().at(1),
                                  FilterType(selectFilterType(layerParam.prelu_param().filler().type())),
                                  layerParam.prelu_param().filler());

            mBoolManager->setValue(mPropertyBrowser->properties().at(2), layerParam.prelu_param().channel_shared());
            break;
        }
        case LayerGUI::ThresholdLayer:
        {
            mDoubleManager->setValue(mPropertyBrowser->properties().at(1), layerParam.threshold_param().threshold());
            break;
        }
        case LayerGUI::TanHLayer:
        {
            mEnumManager->setValue(mPropertyBrowser->properties().at(1), layerParam.tanh_param().engine());
            break;
        }
        case LayerGUI::ReLULayer:
        {
            mDoubleManager->setValue(mPropertyBrowser->properties().at(1), layerParam.relu_param().negative_slope());
            mEnumManager->setValue(mPropertyBrowser->properties().at(2), layerParam.relu_param().engine());
            break;
        }
        case LayerGUI::SigmoidLayer:
        {
            mEnumManager->setValue(mPropertyBrowser->properties().at(1), layerParam.sigmoid_param().engine());
            break;
        }
        case LayerGUI::PowerLayer:
        {
            mDoubleManager->setValue(mPropertyBrowser->properties().at(1), layerParam.power_param().power());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(2), layerParam.power_param().scale());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(3), layerParam.power_param().shift());

            break;
        }
        case LayerGUI::DropoutLayer:
        {
            mDoubleManager->setValue(mPropertyBrowser->properties().at(1), layerParam.dropout_param().dropout_ratio());
            break;
        }
        case LayerGUI::ExpLayer:
        {
            mDoubleManager->setValue(mPropertyBrowser->properties().at(1), layerParam.exp_param().base());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(2), layerParam.exp_param().scale());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(3), layerParam.exp_param().shift());
            break;
        }
        case LayerGUI::LogLayer:
        {
            mDoubleManager->setValue(mPropertyBrowser->properties().at(1), layerParam.log_param().base());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(2), layerParam.log_param().scale());
            mDoubleManager->setValue(mPropertyBrowser->properties().at(3), layerParam.log_param().shift());
            break;
        }
        case LayerGUI::AbsValLayer:
        {
            break;
        }
        case LayerGUI::BNLLLayer:
        {
            break;
        }
        default:
        {
            break;
        }
    }

    applyProperties();
}


void LayerProperties::leaveEvent(QEvent * event)
{
    applyProperties();
}

void LayerProperties::showEvent(QShowEvent * event)
{
    updateGUIProperties();
}

//init enum
void LayerProperties::initEnumString()
{
    mPoolMethod << "Max" << "Ave" << "Stochastic";
    mEngine << "Default" << "Caffe" << "Cudnn";
    mWeightFilterType << "None" << "Gaussian" << "Constant" << "Xavier" << "Uniform" << "Msra";
    mBiasFilterType << "None" << "Gaussian" << "Constant" << "Xavier" << "Uniform" << "Msra";
    mReductionOp << "Sum" << "ASum" << "Sum sq" << "Mean";
    mEltwiseOp << "Prod" << "Sum" << "Max";
    mNorm << "L1" << "L2";
    mNormRegion << "Across Channels" << "Within Channel";
    mDB << "Level DB" << "LMDB";
    mFillerParameter << "Constant" << "Uniform" << "Gaussian" << "Positive Unit Ball" << "Xavier";
    mPhase << "Train" << "Test" << "Both";
    mCropMode << "Warp" << "Square";
    mVarianceNorm << "FAN_IN" << "FAN_OUT" << "AVERAGE";

}

//change selete WeightFilter,update properties value
void LayerProperties::changeWeightFilter(QtProperty *propertyItem, int type)
{
    void* filter = NULL;
    switch (mLayer)
    {
        case LayerGUI::ConvolutionLayer:
        {
            filter = ((MMALab::ConvolutionLayer*)mLayerObject)->getWeightfilter();
            break;
        }
        case LayerGUI::InnerProductLayer:
        {
            filter = ((MMALab::InnerProductLayer*)mLayerObject)->getWeightfilter();
            break;
        }
        case LayerGUI::PReLULayer:
        {
            filter = ((MMALab::PReLULayer*)mLayerObject)->getFilter();
            break;
        }
        default:
        {
            break;
        }
    }

    FilterType filterType = (FilterType)type;
    changFilter(propertyItem, filterType);

    switch(filterType)
    {
        case FilterType::GAUSSIAN://gaussian
        {
            if(filter != NULL)
            {
                delete filter;
            }
            filter = new MMALab::Gaussian();
            switch (mLayer)
            {
                case LayerGUI::ConvolutionLayer:
                {
                    ((MMALab::ConvolutionLayer*)mLayerObject)->setWeightfilter(((MMALab::Gaussian*)filter));
                    break;
                }
                case LayerGUI::InnerProductLayer:
                {
                    ((MMALab::InnerProductLayer*)mLayerObject)->setWeightfilter(((MMALab::Gaussian*)filter));
                    break;
                }
                case LayerGUI::PReLULayer:
                {
                    ((MMALab::PReLULayer*)mLayerObject)->setFilter(((MMALab::Gaussian*)filter));
                    break;
                }
                default:
                {
                    break;
                }
            }

            break;
        }
        case FilterType::CONSTANT://constant
        {
            if(filter != NULL)
            {
                delete filter;
            }
            filter = new MMALab::Constant();

            switch (mLayer)
            {
                case LayerGUI::ConvolutionLayer:
                {
                    ((MMALab::ConvolutionLayer*)mLayerObject)->setWeightfilter(((MMALab::Constant*)filter));
                    break;
                }
                case LayerGUI::InnerProductLayer:
                {
                    ((MMALab::InnerProductLayer*)mLayerObject)->setWeightfilter(((MMALab::Constant*)filter));
                    break;
                }
                case LayerGUI::PReLULayer:
                {
                    ((MMALab::PReLULayer*)mLayerObject)->setFilter(((MMALab::Constant*)filter));
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        case FilterType::XAVIER://xavier
        {
            if(filter != NULL)
            {
                delete filter;
            }
            filter = new MMALab::Xavier();

            switch (mLayer)
            {
                case LayerGUI::ConvolutionLayer:
                {
                    ((MMALab::ConvolutionLayer*)mLayerObject)->setWeightfilter(((MMALab::Xavier*)filter));
                    break;
                }
                case LayerGUI::InnerProductLayer:
                {
                    ((MMALab::InnerProductLayer*)mLayerObject)->setWeightfilter(((MMALab::Xavier*)filter));
                    break;
                }
                case LayerGUI::PReLULayer:
                {
                    ((MMALab::PReLULayer*)mLayerObject)->setFilter(((MMALab::Xavier*)filter));
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        case FilterType::UNIFORM://uniform
        {
            if(filter != NULL)
            {
                delete filter;
            }
            filter = new MMALab::Uniform();

            switch (mLayer)
            {
                case LayerGUI::ConvolutionLayer:
                {
                    ((MMALab::ConvolutionLayer*)mLayerObject)->setWeightfilter(((MMALab::Uniform*)filter));
                    break;
                }
                case LayerGUI::InnerProductLayer:
                {
                    ((MMALab::InnerProductLayer*)mLayerObject)->setWeightfilter(((MMALab::Uniform*)filter));
                    break;
                }
                case LayerGUI::PReLULayer:
                {
                    ((MMALab::PReLULayer*)mLayerObject)->setFilter(((MMALab::Uniform*)filter));
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        case FilterType::MSRA://msra
        {
            if(filter != NULL)
            {
                delete filter;
            }
            filter = new MMALab::Msra();

            switch (mLayer)
            {
                case LayerGUI::ConvolutionLayer:
                {
                    ((MMALab::ConvolutionLayer*)mLayerObject)->setWeightfilter(((MMALab::Msra*)filter));
                    break;
                }
                case LayerGUI::InnerProductLayer:
                {
                    ((MMALab::InnerProductLayer*)mLayerObject)->setWeightfilter(((MMALab::Msra*)filter));
                    break;
                }
                case LayerGUI::PReLULayer:
                {
                    ((MMALab::PReLULayer*)mLayerObject)->setFilter(((MMALab::Msra*)filter));
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        default:
        {
            if(filter != NULL)
            {
                delete filter;
            }
            filter = NULL;

            switch (mLayer)
            {
                case LayerGUI::ConvolutionLayer:
                {
                    ((MMALab::ConvolutionLayer*)mLayerObject)->setWeightfilterToNone();
                    break;
                }
                case LayerGUI::InnerProductLayer:
                {
                    ((MMALab::InnerProductLayer*)mLayerObject)->setWeightfilterToNone();
                    break;
                }
                case LayerGUI::PReLULayer:
                {
                    ((MMALab::PReLULayer*)mLayerObject)->setFilterToNone();
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }

    }

    updateFilterGUIProperties(propertyItem,
                              filterType,
                              filter);

}

//chane select BiasFilter, update properties value
void LayerProperties::changeBiasFilter(QtProperty *propertyItem, int type)
{
    void* filter = NULL;
    switch (mLayer)
    {
        case LayerGUI::ConvolutionLayer:
        {
            filter = ((MMALab::ConvolutionLayer*)mLayerObject)->getBiasfilter();
            break;
        }
        case LayerGUI::InnerProductLayer:
        {
            filter = ((MMALab::InnerProductLayer*)mLayerObject)->getBiasfilter();
            break;
        }
        case LayerGUI::PReLULayer:
        {
            filter = ((MMALab::PReLULayer*)mLayerObject)->getFilter();
            break;
        }
        default:
        {
            break;
        }
    }

    FilterType filterType = (FilterType)type;
    changFilter(propertyItem, filterType);

    switch(filterType)
    {
        case FilterType::GAUSSIAN://gaussian
        {
            if(filter != NULL)
            {
                delete filter;
            }
            filter = new MMALab::Gaussian();

            switch (mLayer)
            {
                case LayerGUI::ConvolutionLayer:
                {
                    ((MMALab::ConvolutionLayer*)mLayerObject)->setBiasfilter(((MMALab::Gaussian*)filter));
                    break;
                }
                case LayerGUI::InnerProductLayer:
                {
                    ((MMALab::InnerProductLayer*)mLayerObject)->setBiasfilter(((MMALab::Gaussian*)filter));
                    break;
                }
                case LayerGUI::PReLULayer:
                {
                    ((MMALab::PReLULayer*)mLayerObject)->setFilter(((MMALab::Gaussian*)filter));
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        case FilterType::CONSTANT://constant
        {
            if(filter != NULL)
            {
                delete filter;
            }
            filter = new MMALab::Constant();

            switch (mLayer)
            {
                case LayerGUI::ConvolutionLayer:
                {
                    ((MMALab::ConvolutionLayer*)mLayerObject)->setBiasfilter(((MMALab::Constant*)filter));
                    break;
                }
                case LayerGUI::InnerProductLayer:
                {
                    ((MMALab::InnerProductLayer*)mLayerObject)->setBiasfilter(((MMALab::Constant*)filter));
                    break;
                }
                case LayerGUI::PReLULayer:
                {
                    ((MMALab::PReLULayer*)mLayerObject)->setFilter(((MMALab::Constant*)filter));
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        case FilterType::XAVIER://xavier
        {
            if(filter != NULL)
            {
                delete filter;
            }
            filter = new MMALab::Xavier();

            switch (mLayer)
            {
                case LayerGUI::ConvolutionLayer:
                {
                    ((MMALab::ConvolutionLayer*)mLayerObject)->setBiasfilter(((MMALab::Xavier*)filter));
                    break;
                }
                case LayerGUI::InnerProductLayer:
                {
                    ((MMALab::InnerProductLayer*)mLayerObject)->setBiasfilter(((MMALab::Xavier*)filter));
                    break;
                }
                case LayerGUI::PReLULayer:
                {
                    ((MMALab::PReLULayer*)mLayerObject)->setFilter(((MMALab::Xavier*)filter));
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        case FilterType::UNIFORM://uniform
        {
            if(filter != NULL)
            {
                delete filter;
            }
            filter = new MMALab::Uniform();

            switch (mLayer)
            {
                case LayerGUI::ConvolutionLayer:
                {
                    ((MMALab::ConvolutionLayer*)mLayerObject)->setBiasfilter(((MMALab::Uniform*)filter));
                    break;
                }
                case LayerGUI::InnerProductLayer:
                {
                    ((MMALab::InnerProductLayer*)mLayerObject)->setBiasfilter(((MMALab::Uniform*)filter));
                    break;
                }
                case LayerGUI::PReLULayer:
                {
                    ((MMALab::PReLULayer*)mLayerObject)->setFilter(((MMALab::Uniform*)filter));
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        case FilterType::MSRA://msra
        {
            if(filter != NULL)
            {
                delete filter;
            }
            filter = new MMALab::Msra();
            switch (mLayer)
            {
                case LayerGUI::ConvolutionLayer:
                {
                    ((MMALab::ConvolutionLayer*)mLayerObject)->setBiasfilter(((MMALab::Msra*)filter));
                    break;
                }
                case LayerGUI::InnerProductLayer:
                {
                    ((MMALab::InnerProductLayer*)mLayerObject)->setBiasfilter(((MMALab::Msra*)filter));
                    break;
                }
                case LayerGUI::PReLULayer:
                {
                    ((MMALab::PReLULayer*)mLayerObject)->setFilter(((MMALab::Msra*)filter));
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        default:
        {
            switch (mLayer)
            {
                case LayerGUI::ConvolutionLayer:
                {
                    ((MMALab::ConvolutionLayer*)mLayerObject)->setBiasfilterToNone();
                    break;
                }
                case LayerGUI::InnerProductLayer:
                {
                    ((MMALab::InnerProductLayer*)mLayerObject)->setBiasfilterToNone();
                    break;
                }
                case LayerGUI::PReLULayer:
                {
                    ((MMALab::PReLULayer*)mLayerObject)->setFilterToNone();
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }

    }

    updateFilterGUIProperties(propertyItem,
                              filterType,
                              filter);
}

//change Filter and update properties attributes
void LayerProperties::changFilter(QtProperty *propertyItem, FilterType type)
{
    switch(type)
    {
        case FilterType::GAUSSIAN://gaussian
        {
            this->clearSubProperties(propertyItem);

            QtProperty *itemStd = mDoubleManager->addProperty("Std");
            mDoubleManager->setRange(itemStd, -FLT_MAX, FLT_MAX);
            propertyItem->addSubProperty(itemStd);

            QtProperty *itemMean = mDoubleManager->addProperty("Mean");
            mDoubleManager->setRange(itemMean, -FLT_MAX, FLT_MAX);
            propertyItem->addSubProperty(itemMean);

            QtProperty *itemSparse = mIntManager->addProperty("Sparse");
            mIntManager->setRange(itemSparse, -INT_MAX, INT_MAX);
            propertyItem->addSubProperty(itemSparse);
            break;
        }
        case FilterType::CONSTANT://constant
        {
            this->clearSubProperties(propertyItem);

            QtProperty *itemValue = mDoubleManager->addProperty("Value");
            mDoubleManager->setRange(itemValue, -FLT_MAX, FLT_MAX);
            propertyItem->addSubProperty(itemValue);

            //QtProperty *itemSparse = mIntManager->addProperty("Sparse");
            //mIntManager->setRange(itemSparse, -INT_MAX, INT_MAX);
            //propertyItem->addSubProperty(itemSparse);
            break;
        }
        case FilterType::XAVIER://xavier
        {
            this->clearSubProperties(propertyItem);

            QtProperty *itemStd = mDoubleManager->addProperty("Std");
            mDoubleManager->setRange(itemStd, -FLT_MAX, FLT_MAX);
            propertyItem->addSubProperty(itemStd);

            QtProperty *itemVarianceNorm = mEnumManager->addProperty("VarianceNorm");
            mEnumManager->setEnumNames(itemVarianceNorm, mVarianceNorm);
            propertyItem->addSubProperty(itemVarianceNorm);

            //QtProperty *itemSparse = mIntManager->addProperty("Sparse");
            //mIntManager->setRange(itemSparse, -INT_MAX, INT_MAX);
            //propertyItem->addSubProperty(itemSparse);
            break;
        }
        case FilterType::UNIFORM://uniform
        {
            this->clearSubProperties(propertyItem);

            QtProperty *itemMin = mDoubleManager->addProperty("Min");
            mDoubleManager->setRange(itemMin, -FLT_MAX, FLT_MAX);
            propertyItem->addSubProperty(itemMin);

            QtProperty *itemMax = mDoubleManager->addProperty("Max");
            mDoubleManager->setRange(itemMax, -FLT_MAX, FLT_MAX);
            propertyItem->addSubProperty(itemMax);

            //QtProperty *itemSparse = mIntManager->addProperty("Sparse");
            //mIntManager->setRange(itemSparse, -INT_MAX, INT_MAX);
            //propertyItem->addSubProperty(itemSparse);
            break;
        }
        case FilterType::MSRA://msra
        {
            this->clearSubProperties(propertyItem);

            QtProperty *itemVarianceNorm = mEnumManager->addProperty("VarianceNorm");
            mEnumManager->setEnumNames(itemVarianceNorm, mVarianceNorm);
            propertyItem->addSubProperty(itemVarianceNorm);
            break;
        }
        default:
        {
            this->clearSubProperties(propertyItem);
            break;
        }

    }

}

//change Filter and update properties value
void LayerProperties::updateFilterGUIProperties(QtProperty *propertyItem, FilterType type, void* filter)
{
    switch(type)
    {
        case FilterType::GAUSSIAN://gaussian
        {
            mDoubleManager->setValue(propertyItem->subProperties().at(0), ((MMALab::Gaussian*)filter)->mStd);
            mDoubleManager->setValue(propertyItem->subProperties().at(1), ((MMALab::Gaussian*)filter)->mMean);
            mIntManager->setValue(propertyItem->subProperties().at(2), ((MMALab::Gaussian*)filter)->mSparse);
            break;
        }
        case FilterType::CONSTANT://constant
        {
            mDoubleManager->setValue(propertyItem->subProperties().at(0), ((MMALab::Constant*)filter)->mValue);
            //mIntManager->setValue(propertyItem->subProperties().at(1), ((MMALab::Constant*)filter)->mSparse);
            break;
        }
        case FilterType::XAVIER://xavier
        {
            mDoubleManager->setValue(propertyItem->subProperties().at(0), ((MMALab::Xavier*)filter)->mStd);
            mEnumManager->setValue(propertyItem->subProperties().at(1), ((MMALab::Xavier*)filter)->mVarianceNorm);
            //mIntManager->setValue(propertyItem->subProperties().at(0), ((MMALab::Xavier*)filter)->mSparse);
            break;
        }
        case FilterType::UNIFORM://uniform
        {
            mDoubleManager->setValue(propertyItem->subProperties().at(0), ((MMALab::Uniform*)filter)->mMin);
            mDoubleManager->setValue(propertyItem->subProperties().at(1), ((MMALab::Uniform*)filter)->mMax);
            //mIntManager->setValue(propertyItem->subProperties().at(2), ((MMALab::Uniform*)filter)->mSparse);
            break;
        }
        case FilterType::MSRA://msra
        {
            mEnumManager->setValue(propertyItem->subProperties().at(0), ((MMALab::Msra*)filter)->mVarianceNorm);
            break;
        }
        default:
        {
            break;
        }

    }

}
void LayerProperties::updateFilterGUIProperties(QtProperty *propertyItem, FilterType type, caffe::FillerParameter fillerParam)
{
    switch(type)
    {
        case FilterType::GAUSSIAN://gaussian
        {
            mDoubleManager->setValue(propertyItem->subProperties().at(0), fillerParam.std());
            mDoubleManager->setValue(propertyItem->subProperties().at(1), fillerParam.mean());
            mIntManager->setValue(propertyItem->subProperties().at(2),  fillerParam.sparse());
            break;
        }
        case FilterType::CONSTANT://constant
        {
            mDoubleManager->setValue(propertyItem->subProperties().at(0), fillerParam.value());
            //mIntManager->setValue(propertyItem->subProperties().at(1),  fillerParam.sparse());
            break;
        }
        case FilterType::XAVIER://xavier
        {
            mDoubleManager->setValue(propertyItem->subProperties().at(0), fillerParam.std());
            mEnumManager->setValue(propertyItem->subProperties().at(1), fillerParam.variance_norm());
            //mIntManager->setValue(propertyItem->subProperties().at(0),  fillerParam.sparse());
            break;
        }
        case FilterType::UNIFORM://uniform
        {
            mDoubleManager->setValue(propertyItem->subProperties().at(0), fillerParam.min());
            mDoubleManager->setValue(propertyItem->subProperties().at(1), fillerParam.max());
            //mIntManager->setValue(propertyItem->subProperties().at(2),  fillerParam.sparse());
            break;
        }
        case FilterType::MSRA://msra
        {
            mEnumManager->setValue(propertyItem->subProperties().at(0), fillerParam.variance_norm());
            break;
        }
        default:
        {
            break;
        }

    }

}

//the value input properties
void LayerProperties::applyFilter(QtProperty *propertyItem, FilterType type, void* filter)
{
    switch(type)
    {
        case FilterType::GAUSSIAN://gaussian
        {
            ((MMALab::Gaussian*)filter)->mStd = mDoubleManager->value(propertyItem->subProperties().at(0));
            ((MMALab::Gaussian*)filter)->mMean = mDoubleManager->value(propertyItem->subProperties().at(1));
            ((MMALab::Gaussian*)filter)->mSparse = mIntManager->value(propertyItem->subProperties().at(2));
            break;
        }
        case FilterType::CONSTANT://constant
        {
            ((MMALab::Constant*)filter)->mValue = mDoubleManager->value(propertyItem->subProperties().at(0));
            //((MMALab::Constant*)filter)->mSparse = mIntManager->value(propertyItem->subProperties().at(1));
            break;
        }
        case FilterType::XAVIER://xavier
        {
            ((MMALab::Xavier*)filter)->mStd = mDoubleManager->value(propertyItem->subProperties().at(0));
            ((MMALab::Xavier*)filter)->mVarianceNorm = (MMALab::VarianceNorm)mEnumManager->value(propertyItem->subProperties().at(1));
            //((MMALab::Xavier*)filter)->mSparse = mIntManager->value(propertyItem->subProperties().at(0));
            break;
        }
        case FilterType::UNIFORM://uniform
        {
            ((MMALab::Uniform*)filter)->mMin = mDoubleManager->value(propertyItem->subProperties().at(0));
            ((MMALab::Uniform*)filter)->mMax = mDoubleManager->value(propertyItem->subProperties().at(1));
            //((MMALab::Uniform*)filter)->mSparse = mIntManager->value(propertyItem->subProperties().at(2));
            break;
        }
        case FilterType::MSRA://msra
        {
            ((MMALab::Msra*)filter)->mVarianceNorm = (MMALab::VarianceNorm)mEnumManager->value(propertyItem->subProperties().at(0));
            break;
        }
        default:
        {
            break;
        }
    }
}

//clear properties
void LayerProperties::clearSubProperties(QtProperty *propertyItem)
{
    int counter = propertyItem->subProperties().count();
    for(int i = 0; i < counter; i++)
    {
        propertyItem->removeSubProperty(propertyItem->subProperties().at(0));
    }

}


int LayerProperties::selectFilterType(string type)
{
    if(type == "gaussian")
    {
        return FilterType::GAUSSIAN;
    }
    else if(type == "constant")
    {
        return FilterType::CONSTANT;
    }
    else if(type == "xavier")
    {
        return FilterType::XAVIER;
    }
    else if(type == "uniform")
    {
        return FilterType::UNIFORM;
    }
    else if(type == "msra")
    {
        return FilterType::MSRA;
    }
    else
    {
        return FilterType::NONE;
    }
}

int LayerProperties::selectCropMode(string mode)
{
    if(mode == "square")
    {
        return CropMode::SQUARE;
    }
    else
    {
        return CropMode::WARP;
    }
}


//ttttt
void LayerProperties::changeBlobShape(QtProperty *propertyItem, int count)
{
    void* shape = NULL;

    switch (mLayer)
    {
        case LayerGUI::ReshapeLayer:
            shape  = ((MMALab::ReshapeLayer*)mLayerObject)->getShape();
            break;
        case LayerGUI::DummyDataLayer:
            shape =  ((MMALab::DummyDataLayer*)mLayerObject)->getShape();
            break;
        default:
            break;
    }
    this->clearSubProperties(propertyItem);
    for(int i = 0; i < count; i++)
    {
        QString str = "Shape " +  QString::number(i) + "_Dim Count ";
        QtProperty *itemShape = mBlobShapeDimIntManager->addProperty(str);
        mBlobShapeDimIntManager->setRange(itemShape, 0, INT_MAX);
        propertyItem->addSubProperty(itemShape);
        connect (mBlobShapeDimIntManager, SIGNAL(valueChanged(QtProperty *, int)), this, SLOT(changeBlobShapeDim(QtProperty *, int)));
    }

    if(shape != NULL)
    {
        delete shape;
    }
    shape = new MMALab::BlobShape();
    switch (mLayer)
    {
        case LayerGUI::ReshapeLayer:
            ((MMALab::ReshapeLayer*)mLayerObject)->setShape(((MMALab::BlobShape*)shape));
            break;
        case LayerGUI::DummyDataLayer:
            ((MMALab::DummyDataLayer*)mLayerObject)->setShape(((MMALab::BlobShape*)shape));
            break;
        default:
            break;
    }

    updateBlobShapeProperties(propertyItem, shape);
}
void LayerProperties::changeBlobShapeDim(QtProperty *propertyItem, int count)
{
    this->clearSubProperties(propertyItem);
    for(int i = 0; i < count; i++)
    {
        QString str = "Dim " +  QString::number(i);
        QtProperty *itemDim = mIntManager->addProperty(str);
        mIntManager->setRange(itemDim, 0, INT_MAX);
        propertyItem->addSubProperty(itemDim);
    }
}

void LayerProperties::updateBlobShapeProperties(QtProperty *propertyItem, void* shape)
{
    if((MMALab::BlobShape*)shape!=NULL)
    {
        if(!((MMALab::BlobShape*)shape)->mShape.empty())
         {
            mBlobShapeIntManager->setValue(propertyItem, ((MMALab::BlobShape*)shape)->mShape.size());

            for(int i = 0; i < propertyItem->subProperties().size(); i++)
            {
                mBlobShapeDimIntManager->setValue(propertyItem->subProperties().at(i),
                                                                                    ((MMALab::BlobShape*)shape)->mShape.at(i).size());
                if(!((MMALab::BlobShape*)shape)->mShape.at(i).empty())
                {
                    for(int j = 0; j< propertyItem->subProperties().at(i)->subProperties().size(); j++)
                    {
                        mIntManager->setValue(propertyItem->subProperties().at(i)->subProperties().at(j),
                                                                    ((MMALab::BlobShape*)shape)->mShape.at(i).at(j));
                    }
                }
            }
         }
    }

}

void LayerProperties::updateBlobShapeProperties(QtProperty *propertyItem, caffe::BlobShape shape)
{
    mBlobShapeDimIntManager->setValue(propertyItem, shape.dim_size());
    for(int i = 0; i < shape.dim_size(); i++)
    {
        mIntManager->setValue(propertyItem->subProperties().at(i), shape.dim(i));
    }
}

void LayerProperties::applyBlobShape(QtProperty *propertyItem, void *shap)
{
    if((MMALab::BlobShape*)shap != NULL)
    {
        ((MMALab::BlobShape*)shap)->mShape.clear();
        for(int i = 0; i < mBlobShapeIntManager->value(propertyItem); i++)
        {
            ((MMALab::BlobShape*)shap)->mShape.insert (make_pair (i, MapSmall ()));
            for(int j = 0; j < mBlobShapeDimIntManager->value(propertyItem->subProperties().at(i)); j++)
            {
                int value = mIntManager->value(propertyItem->subProperties().at(i)->subProperties().at(j));
                ((MMALab::BlobShape*)shap)->mShape.at(i).insert(make_pair(j, value));
            }
        }
    }
}
