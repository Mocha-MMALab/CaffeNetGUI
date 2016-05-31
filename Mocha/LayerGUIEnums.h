#ifndef LAYERGUIENUMS_H
#define LAYERGUIENUMS_H

namespace LayerGUI
{
    enum Layers
    {
        //Other
        DataBlob,

        //VisionLayer
        ConvolutionLayer,
        PoolingLayer,
        SPPLayer,
        LRNLayer,

        //CommonLayer
        MVNLayer,
        ReshapeLayer,
        SliceLayer,
        InnerProductLayer,
        SoftmaxLayer,
        FlattenLayer,
        EltwiseLayer,
        ConcatLayer,
        ArgMaxLayer,
        ReductionLayer,

        //DataLayer
        DummyDataLayer,
        HDF5OutputLayer,
        HDF5DataLayer,
        WindowDataLayer,
        ImageDataLayer,
        MemoryDataLayer,
        DataLayer,

        //LossLayer
        HingeLossLayer,
        InfogainLossLayer,
        ContrastiveLossLayer,
        MultinomialLogisticLossLayer,
        SigmoidCrossEntropyLossLayer,
        EuclideanLossLayer,
        SoftmaxWithLossLayer,
        AccuracyLayer,

        //NeuroLayer
        PReLULayer,
        ThresholdLayer,
        TanHLayer,
        ReLULayer,
        SigmoidLayer,
        PowerLayer,
        DropoutLayer,
        ExpLayer,
        LogLayer,
        AbsValLayer,
        BNLLLayer
    };

    enum LayerType
    {
        Other,
        VisionLayers,
        CommonLayers,
        DataLayers,
        LossLayers,
        NeuroLayers
    };


}

#endif // LAYERGUIENUMS_H

