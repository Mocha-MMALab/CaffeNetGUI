#ifndef __LAYERENUM_H
#define __LAYERENUM_H

/* @namespace MMALab
 * @MMALab namespace
 */
namespace MMALab
{
	enum LayerType
	{
		DATABLOB,
		CONVOLUTION,
		POOLING,
		SPP,
		LRN,
		CONTRASTIVE_LOSS,
                HINGE_LOSS,
		INFOGAIN_LOSS,
		EUCLIDEAN_LOSS,			
		SOFT_MAX_WITH_LOSS,
		ACCURACY,
                MULTINOMIAL_LOGISTIC_Loss,
                SIGMOID_CROSS_ENTROPY_LOSS,
		MVN, 	
		RESHPAE, 
		REDUCTION,	
		SLICE,
		SOFTMAX,
		INNER_PRODUCT, 
		FLATTEN,
		ELTWISE,
		CONCAT,
		ARGMAX,
		PRELU,
		THRESHOLD,
		TANH, 
		SIGMOID, 
		RELU, 
		POWER, 
		DROPOUT,
		EXP,
		LOG,
                ABSVAL,
                BNLL,
		DUMMYDATA,
		HDF5_OUTPUT, 
		HDF5_DATA,
		WINDOW_DATA,
		IMAGE_DATA,
		DATA,
		MEMORY_DATA
	};

	enum FilterType
	{
		NONE,
		GAUSSIAN,
		CONSTANT,
                XAVIER,
                UNIFORM,
                MSRA
	};

	enum VarianceNorm
	{
		FAN_IN,
		FAN_OUT,
		AVERAGE
	};

	enum ReductionOp
	{
		REDUCTIONOP_SUM,
		REDUCTIONOP_ASUM,
		REDUCTIONOP_SUMSQ,
		REDUCTIONOP_MEAN
	};

	enum EltwiseOp
	{
		ELTWISEOP_PROD,
		ELTWISEOP_SUM,
		ELTWISEOP_MAX
	};

	enum CropMode
	{
		WARP,
		SQUARE
	};

	enum PoolMethod
	{
		POOLMETHOD_MAX,
		POOLMETHOD_AVE,
		POOLMETHOD_STOCHASTIC
	};

	enum Engine
	{
		DEFAULT,
		CAFFE,
		CUDNN
	};

	enum Norm
	{
		L1,
		L2
	};	

	enum NormRegion
	{
		ACROSS_CHANNELS,
		WITHIN_CHANNEL
	};

	enum DB 
	{
		LEVELDB,
		LMDB
	};

	enum FillerParameter	
	{
		CONSTANTFILLER,
		UNIFORMFILLER,
		GAUSSIANFILLER,
		POSITIVEUNITBALLFILLER,
		XAVIERFILLER
	};	

	enum Phase
	{
		TRAIN,
		TEST,
		BOTH
	};
}
#endif
