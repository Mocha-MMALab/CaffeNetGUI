#ifndef _VISIONLAYERPARAM_H
#define _VISIONLAYERPARAM_H

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
	/* @class ConvolutionParam
	 * @basic class of convolution parameter definition
	 */
	class LAYERLIB_API ConvolutionParam
	{
	public:

		/* @ConvolutionParam number of output
		 * @details the number of outputs for this layer
		 */
                uint32	mNumOutput;

		/* @ConvolutionParam kernel size
		 * @details the kernel size(square)
		 */
                uint32	mKernelSize;

		/* @ConvolutionParam weight filter
		 * @details the filter for the weight
		 */
		void* mWeightfilter;

		/* @ConvolutionParam bias filter
		 * @details the filter for the bias
		 */
		void* mBiasfilter;

		/* @ConvolutionParam bias term
		 * @details whether to have bias terms
		 */
		bool mBiasTerm;

		/* @ConvolutionParam pad
		 * @details the padding size(equal in Y, X)
		 */
                uint32	mPad;

		/* @ConvolutionParam stride
		 * @details the stride (equal in Y, X)
		 */
                uint32	mStride;

		/* @ConvolutionParam group
		 * @details the group size for group conv
		 */
                uint32 mGroup;

		/* @ConvolutionParam engine
		 * @details engine
		*/
		Engine mEngine;

		/* @ConvolutionParam constructor of ConvolutionParam
		 * @details this class can help user to define parameter of convolution layer
		 */
		ConvolutionParam();

		/* @ConvolutionParam deconstructor of ConvolutionParam
		 * @details this class will be deconstruct by user
		 */
		~ConvolutionParam();
	
		FilterType mWeightfilterType;

		FilterType mBiasfilterType;
	};
	
	/* @class PoolingParam
	 * @basic class of pooling parameter definition
	 */
	class LAYERLIB_API PoolingParam
	{
	public:

		/* @PoolingParam kernel size
		 * @details the kernel size(square)
		 */
                uint32	mKernelSize;

		/* @PoolingParam kernel H size
		 * @details the kernel H size(2D only)
		 */
         //       uint32	mKernelH;

		/* @PoolingParam kernel W size
		 * @details the kernel W size(2D only)
		 */
         //       uint32	mKernelW;

		/* @PoolingParam pad
		 * @details the padding size(equal in Y, X)
		 */
                uint32	mPad;

		/* @PoolingParam pad H
		 * @details the padding H size(2D only)
		 */
         //       uint32	mPadH;

		/* @PoolingParam pad W
		 * @details the padding W size(2D only)
		 */
         //       uint32	mPadW;

		/* @PoolingParam stride
		 * @details the stride (equal in Y, X)
		 */
                uint32	mStride;

		/* @PoolingParam stride H
		 * @details the stride H (2D only)
		 */
         //       uint32	mStrideH;

		/* @PoolingParam stride W
		 * @details the stride W (2D only)
		 */
         //       uint32	mStrideW;

		/* @PoolingParam pool type
		 * @details choose pool type		
		 */
		PoolMethod mPool;

		/* @PoolingParam engine
		 * @details engine
		 */
		Engine mEngine;

		/* @PoolingParam global pooling
		 * @details If global_pooling then it will pool over the size of the bottom by doing
		 *             kernel_h = bottom->height and kernel_w = bottom->width
		 */
		bool mGlobalPooling;

		/* @PoolingParam constructor of PoolingParam
		 * @details this class can help user to define parameter of pooling layer
		 */
		PoolingParam();

		/* @PoolingParam deconstructor of PoolingParam
		 * @details this class will be deconstruct by user
		 */
		~PoolingParam();

	};

	/* @class SPPParam
	 * @basic class of SPP parameter definition
	 */
	class LAYERLIB_API SPPParam
	{
		public:

			/* @SPPParam PyramidHight size
			 * @detail the mPyramidHight size
			 */
                        uint32 mPyramidHeight;

			/* @SPPParam pool type
			 * @details choose pool type		
			 */
			PoolMethod mPool;

			/* @SPPParam engine type
			 * @detail choose engine type(Default:0, CAFFE:1 CUDNN:2)
			 */
			Engine mEngine;

			/* @SPPParam constructor of SPPParam
			* @details this class can help user to define parameter of pooling layer
			*/
			SPPParam();

			/* @SPPParam deconstructor of SPPParam
			* @details this class will be deconstruct by user
			*/
			~SPPParam();
	};

	/* @class LRNParam
	 * @basic class of LRN parameter definition
	 */
	class LAYERLIB_API LRNParam 
	{
		public:

			/* @LRNParam local size
			 * @detail the mLocalSize
			 */
                        uint32 mLocalSize;

			/* @LRNParam alpha
			 * @detail the alpha
			 */
			float mAlpha;

			/* @LRNParam beta
			 * @detail the beta
			 */
			float mBeta;

			/* @LRNLayer norm_region type
			 * @details choose norm_region type		
			 */
			NormRegion mNormRegion;

			/* @LRNParam k
			 * @detail the k
			 */
			float mK;

                        /* @LRNParam engine type
                         * @detail choose engine type(Default:0, CAFFE:1 CUDNN:2)
                         */
                        Engine mEngine;

			/* @LRNParam constructor of LRNParam
			 * @details this class can help user to define parameter of LRN layer
			 */
			LRNParam();
			
			/* @LRNParam deconstructor of LRNParam
			 * @details this class will be deconstruct by user
			 */
			~LRNParam();
	};
}


#endif //VISIONLAYERPARAM
