#ifndef _COMMONLAYERPARAM_H
#define _COMMONLAYERPARAM_H


#include <string>
#include "LayerEnum.h"
#include "LayerParam.h"

typedef unsigned int uint32;

using namespace std;
using namespace MMALab;

/* @namespace MMALab
 * @MMALab namespace
 */
namespace MMALab
{
	/* @class MVNParam
	 * @basic class of MVN parameter definition
	 */
	class LAYERLIB_API MVNParam
	{
	public:

		/* @MVNParam normalize variance
		 * @details this parameter can be set to false to normalize mean only
		 */
		bool mNormalizeVariance;

		/* @MVNParam across channels
		 * @details this parameter can be set to true to perform DNN-like MVN
		 */
		bool mAcrossChannels;

		/* @MVNParam eps
		 * @details epsilon for not dividing by zero while normalizing variance
		 */
                float mEps;

		/* @MVNParam constructor of MVNParam
		 * @details this class can help user to define parameter of MVN layer
		 */
		MVNParam();

		/* @MVNParam deconsturctor of MVNParam
		 * @details this class will be deconstruct by user
		 */
		~MVNParam();
	};

	/* @class ReshapeParam
	 * @basic class of Reshape parameter definition
	 */
	class LAYERLIB_API ReshapeParam
	{
	public:

		/* @ReshapeParam shape
		 * @details Specify the output dimensions. If some of the dimensions are set to 0,
		 *          the corresponding dimension from the bottom layer is used (unchanged).
		 *          Exactly one dimension may be set to -1, in which case its value is
		 *          inferred from the count of the bottom blob and the remaining dimensions.
		 */
                void* mShape;

		/* @ReshapeParam axis
		 * @details axis may be non-zero to retain some portion of the beginning of the input
		 *          shape (and may be negative to index from the end; e.g., -1 to begin the
		 *          reshape after the last axis, including nothing in the reshape, -2 to 
		 *          include only the last axis, etc.).
		 */
		int mAxis;

		/* @ReshapeParam num axes
		 * @details num_axes specifies the extent of the reshape.
		 *          If num_axes >= 0 (and axis >= 0), the reshape will be performed only on
		 *          input axes in the range [axis, axis+num_axes].
		 *          num_axes may also be -1, the default, to include all remaining axes.
		 */
		int mNumAxis;



		/* @ReshapeParam constructor of ReshapeParam
		 * @details this class can help user to define parameter of Reshape layer
		 */
		ReshapeParam();

		/* @ReshapeParam deconsturctor of ReshapeParam
		 * @details this class will be deconstruct by user
		 */
		~ReshapeParam();
	};

	/* @class ReductionParam
	 * @basic class of Reduction parameter definition
	 */
	class LAYERLIB_API ReductionParam
	{
	public:

		/* @ReductionParam operation
		 * @details reduction operation
		 */
		ReductionOp mOperation;

		/* @ReductionParam axis
		 * @details The first axis to reduce to a scalar -- may be negative to index from the
		 *          end (e.g., -1 for the last axis).
		 */
		int mAxis;

		/* @ReductionParam coeff
		 * @details coefficient for output
		 */
		float mCoeff;

		/* @ReductionParam constructor of ReductionParam
		 * @details this class can help user to define parameter of Reduction layer
		 */
		ReductionParam();

		/* @ReductionParam deconsturctor of ReductionParam
		 * @details this class will be deconstruct by user
		 */
		~ReductionParam();
	};

	/* @class SliceParam
	 * @basic class of Slice parameter definition
	 */
	class LAYERLIB_API SliceParam
	{
	public:

		/* @SliceParam axis
		 * @details The axis along which to slice -- may be negative to index from the end
		 *          (e.g., -1 for the last axis)
		 */
		int mAxis;

		/* @SliceParam slice point
		 * @details by By default, SliceLayer concatenates blobs along the "channels" axis
		 */
                uint32 mSlicePoint;

		/* @SliceParam slice dim
		 * @details alias for "axis" -- does not support negative indexing
		 */
                uint32 mSliceDim;

		/* @SliceParam constructor of SliceParam
		 * @details this class can help user to define parameter of Slice layer
		 */
		SliceParam();

		/* @SliceParam deconsturctor of SliceParam
		 * @details this class will be deconstruct by user
		 */
		~SliceParam();
	};

	/* @class SoftmaxParam
	 * @basic class of Softmax parameter definition
	 */
	class LAYERLIB_API SoftmaxParam
	{
	public:

		/* @SoftmaxParam engine
		 * @details engine
		 */
		Engine mEngine;

		/* @SoftmaxParam axis
		 * @details The axis along which to perform the Softmax -- may be negative to index
		 *          from the end (e.g., -1 for the last axis).
		 *          Any other axes will be evaluated as independent Softmaxes.
		 */
		int mAxis;

		/* @SoftmaxParam constructor of SoftmaxParam
		 * @details this class can help user to define parameter of Softmax layer
		 */
		SoftmaxParam();

		/* @SoftmaxParam deconsturctor of SoftmaxParam
		 * @details this class will be deconstruct by user
		 */
		~SoftmaxParam();
	};

	/* @class InnerProductParam
	 * @basic class of InnerProduct parameter definition
	 */
	class LAYERLIB_API InnerProductParam
	{
	public:
		
		/* @InnerProductParam num output
		 * @details the number of outputs for the layer
		 */
                uint32 mNumOutput;

		/* @InnerProductParam bias terms
		 * @details whether to have bias terms
		 */
		bool mBiasTerm;		

		/* @InnerProductParam weight filter
		 * @details the filter for the weight
		 */
		void* mWeightFilter;	

		FilterType mWeightFilterType;

		/* @InnerProductParam bias filter
		 * @details the filter for the bias 
		 */
		void* mBiasFilter;

		FilterType mBiasFilterType;

		/* @InnerProductParam axis
		 * @details The first axis to be lumped into a single inner product computation;
		 *          all preceding axes are retained in the output.
		 *          May be negative to index from the end (e.g., -1 for the last axis).
		 */
		int mAxis;

		/* @InnerProductParam constructor of InnerProductParam
		 * @details this class can help user to define parameter of InnerProduct layer
		 */
		InnerProductParam();

		/* @InnerProductParam deconsturctor of InnerProductParam
		 * @details this class will be deconstruct by user
		 */
		~InnerProductParam();
	};

	/* @class FlattenParam
	 * @basic class of Flatten parameter definition
	 */
	class LAYERLIB_API FlattenParam
	{
	public:
		
		/* @FlattenParam axis
		 * @details The first axis to flatten: all preceding axes are retained in the output.
		 *          May be negative to index from the end (e.g., -1 for the last axis).
		 */
		int mAxis;

		/* @FlattenParam end axis
		 * @details The last axis to flatten: all following axes are retained in the output.
		 *          May be negative to index from the end (e.g., the default -1 for the 
		 *          last axis).
		 */
		int mEndAxis;

		/* @FlattenParam constructor of FlattenParam
		 * @details this class can help user to define parameter of Flatten layer
		 */
		FlattenParam();

		/* @FlattenParam deconsturctor of FlattenParam
		 * @details this class will be deconstruct by user
		 */
		~FlattenParam();
	};

	/* @class EltwiseParam
	 * @basic class of Eltwise parameter definition
	 */
	class LAYERLIB_API EltwiseParam
	{
	public:

		/* @EltwiseParam operation
		 * @details element-wise operation
		 */
		EltwiseOp mOperation;

		/* @EltwiseParam coeff
		 * @details blob-wise coefficient for SUM operation
		 */
		float mCoeff;

		/* @EltwiseParam stable prod grad
		 * @details Whether to use an asymptotically slower (for >2 inputs) but stabler 
		 *          method of computing the gradient for the PROD operation. 
		 *          (No effect for SUM op.)
		 */
		bool mStableProdGrad;

		/* @EltwiseParam constructor of EltwiseParam
		 * @details this class can help user to define parameter of Eltwise layer
		 */
		EltwiseParam();

		/* @EltwiseParam deconsturctor of EltwiseParam
		 * @details this class will be deconstruct by user
		 */
		~EltwiseParam();
	};

	/* @class ConcatParam
	 * @basic class of Concat parameter definition
	 */
	class LAYERLIB_API ConcatParam
	{
	public:

		/* @ConcatParam axis
		 * @details The axis along which to concatenate -- may be negative to index 
		 *          from the end (e.g., -1 for the last axis).  
		 *          Other axes must have the same dimension for all the bottom blobs.
		 */
		int mAxis;

		/* @ConcatParam concat dim
		 * @details alias for "axis" -- does not support negative indexing.
		 */
                uint32 mConcatDim;

		/* @ConcatParam constructor of ConcatParam
		 * @details this class can help user to define parameter of Concat layer
		 */
		ConcatParam();

		/* @ConcatParam deconsturctor of ConcatParam
		 * @details this class will be deconstruct by user
		 */
		~ConcatParam();
	};

	/* @class ArgMaxParam
	 * @basic class of ArgMax parameter definition
	 */
	class LAYERLIB_API ArgMaxParam
	{
	public:

		/* @ArgMaxParam out max val
		 * @details If true produce pairs (argmax, maxval)
		 */
		bool mOutMaxVal;

		/* @ArgMaxParam top k
		 * @details top k
		 */
                uint32 mTopK;

		/* @ArgMaxParam axis
		 * @details axis
		 */
		int mAxis;
		/* @ArgMaxParam constructor of ArgMaxParam
		 * @details this class can help user to define parameter of ArgMax layer
		 */
		ArgMaxParam();

		/* @ArgMaxParam deconsturctor of ArgMaxParam
		 * @details this class will be deconstruct by user
		 */
		~ArgMaxParam();
	};


}
#endif //COMMONLAYERPARAM
