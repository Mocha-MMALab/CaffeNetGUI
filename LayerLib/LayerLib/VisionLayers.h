#ifndef _VISIONLAYERS_H
#define _VISIONLAYERS_H

#include "LayerEnum.h"
#include "BaseLayer.h"
#include "LayerParam.h"
#include "VisionLayerParam.h"

typedef unsigned int uint32;

using namespace std;

/* @namespace MMALab
 * @MMALab namespace
 */
namespace MMALab
{
	class LAYERLIB_API ConvolutionLayer : public  BaseLayer
	{
	public:
		
		/* @ConvolutionLayer constructor of ConvolutionLayer
		 * @details this class can help user to contruct own convolution layer
		 */
		ConvolutionLayer(string name);

		/* @ConvolutionLayer deconstructor of ConvolutionLayer
		 * @details this class will be deconstruct by user
		 */
		~ConvolutionLayer();	

		ConvolutionLayer();

		/* @ConvolutionLayer set number of output
		 * @details set the number of outputs for this layer
		 *
		 * @param	value		the number of outputs
		 */
                void setNumOutput(uint32 value);

		/* @ConvolutionLayer set kernel size
		 * @details set the kernel size
		 *
		 * @param	value		the kernel size(square)
		 */
                void setKernelSize(uint32 value);

		/* @ConvolutionLayer set weight filter
		 * @details set the filter for the weight
		 *
		 * @param	weightfilter			the filter for the weight
		 */
		void setWeightfilter(Gaussian* weightfilter);

		/* @ConvolutionLayer set weight filter
		 * @details set the filter for the weight
		 *
		 * @param	weightfilter			the filter for the weight
		 */
		void setWeightfilter(Constant* weightfilter);

                /* @ConvolutionLayer set weight filter
                 * @details set the filter for the weight
                 *
                 * @param	weightfilter			the filter for the weight
                 */
                void setWeightfilter(Xavier* weightfilter);

                /* @ConvolutionLayer set weight filter
                 * @details set the filter for the weight
                 *
                 * @param	weightfilter			the filter for the weight
                 */
                void setWeightfilter(Uniform* weightfilter);

                /* @ConvolutionLayer set weight filter
                 * @details set the filter for the weight
                 *
                 * @param	weightfilter			the filter for the weight
                 */
                void setWeightfilter(Msra* weightfilter);

		/* @ConvolutionLayer set bias filter
		 * @details set the filter for the bias
		 *
		 * @param	biasfilter			the filter for the weight
		 */
		void setBiasfilter(Gaussian* biasfilter);

                /* @ConvolutionLayer set bias filter
                 * @details set the filter for the bias
                 *
                 * @param	biasfilter			the filter for the weight
                 */
                void setBiasfilter(Constant* biasfilter);

                /* @ConvolutionLayer set bias filter
                 * @details set the filter for the bias
                 *
                 * @param	biasfilter			the filter for the weight
                 */
                void setBiasfilter(Xavier* biasfilter);

                /* @ConvolutionLayer set bias filter
                 * @details set the filter for the bias
                 *
                 * @param	biasfilter			the filter for the weight
                 */
                void setBiasfilter(Uniform* biasfilter);

                /* @ConvolutionLayer set bias filter
                 * @details set the filter for the bias
                 *
                 * @param	biasfilter			the filter for the weight
                 */
                void setBiasfilter(Msra* biasfilter);

		/* @ConvolutionLayer set bias term
		 * @details set whether to have bias terms
		 * 
		 * @param	bool			whether to have the bias terms
		 */
		void setBiasTerm(bool biasTerm);

		/* @ConvolutionLayer set engine
		 * @details set engine
		 * 
		 * @param	engine			engine
		 */
		void setEngine(Engine type);

		/* @ConvolutionLayer set group
		 * @details set the group size for group conv
		 * 
		 * @param	value			the group size for group conv
		 */
                void setGroup(uint32 value);

		/* @ConvolutionLayer set pad
		 * @details set the padding size
		 * 
		 * @param	value		the padding size(equal in Y, X)
		 */
                void setPad(uint32 value);

		/* @ConvolutionLayer set stride
		 * @details set the stride
		 *
		 * @param	value		the stride(equal in Y, X)
		 */
                void setStride(uint32 value);

		/* @ConvolutionLayer get number of output
		 * @details get the number of outputs for this layer
		 *
		 * @return	int			the number of outputs for this layer
		 */
                uint32 getNumOutput();

		/* @ConvolutionLayer get kernel size
		 * @details get kernel size
		 * 
		 * @return	int			the kernel size(equal)
		 */
                uint32 getKernelSize();

		/* @ConvolutionLayer get engine
		 * @details get engine
		 * 
		 * @return	engine			engine
		 */
		Engine getEngine();

		/* @ConvolutionLayer get group
		 * @details get group
		 * 
		 * @return	int			the group
		 */
                uint32 getGroup();

		/* @ConvolutionLayer get weight filter
		 * @details get the filter for the weight
		 *
		 * @return	string		the filter for the weight
		 */
		void* getWeightfilter();

		/* @ConvolutionLayer get bias filter
		 * @details get the filter for the bias
		 *
		 * @return	string		the filter for the bias
		 */
		void* getBiasfilter();

		/* @ConvolutionLayer get bias term
		 * @details get whether to have bias term
		 * 
		 * @return	string		whether to have bias term
		 */
		bool getBiasTerm();

		/* @ConvolutionLayer get pad
		 * @details get the padding size
		 * 
		 * @return	int			the padding size(equal in Y, X)
		 */
                uint32 getPad();

		/* @ConvolutionLayer get stride
		 * @details get the stride
		 *
		 * @return int			the stride(equal in Y, X)
		 */
                uint32 getStride();

		string convet2CaffeFormat();

		//learning rate and decay multipliers for the filters
		float mFilterLRateMult;
		float mFilterDecayMult;
		//learning rate and decay multipliers for the biases
		float mBiasLRateMult;
		float mBiasDecayMult;

		//set learning rate and decay multipliers for the filters
		void setFilterLRDecayMult(float lr, float decay);
		//set learning rate and decay multipliers for the biases
		void setBiasLRDecayMult(float lr, float decay);

		FilterType getWeightfilterType();

		FilterType getBiasfilterType();

		void setWeightfilterToNone();

		void setBiasfilterToNone();
	};
			
	class LAYERLIB_API PoolingLayer: public  BaseLayer
	{
	public:

		/* @PoolingLayer  constructor of PoolingLayer
		 * @details this class can help user to contruct own Pooling layer
		 */
		PoolingLayer(string name);

		PoolingLayer();

		/* @PoolingLayer deconstructor of PoolingLayer
		 * @details this class will be deconstruct by user
		 */
		~PoolingLayer();

		/* @PoolingLayer set kernel size
		 * @details set the kernel size
		 *
		 * @param	value		the kernel size(square)
		 */
                void setKernelSize(uint32 value);

		/* @PoolingLayer set kernel H
		 * @details set the kernel H
		 *
		 * @param	value		the kernel H(2D only)
		 */
         //       void setKernelH(uint32 value);

		/* @PoolingLayer set kernel W
		 * @details set the kernel W
		 *
		 * @param	value		the kernel W(2D only)
		 */
         //       void setKernelW(uint32 value);

		/* @PoolingLayer set stride
		 * @details set the stride
		 *
		 * @param	value		the stride(equal in Y, X)
		 */
                void setStride(uint32 value);

		/* @PoolingLayer set stride H
		 * @details set the stride H
		 *
		 * @param	value		the stride H(2D only)
		 */
         //       void setStrideH(uint32 value);

		/* @PoolingLayer set stride W
		 * @details set the stride W
		 *
		 * @param	value		the stride W(2D only)
		 */
         //       void setStrideW(uint32 value);

		/* @PoolingLayer set pad
		 * @details set the padding size
		 * 
		 * @param	value		the padding size(equal in Y, X)
		 */
                void setPad(uint32 value);

		/* @PoolingLayer set pad H
		 * @details set the padding H size
		 * 
		 * @param	value		the padding H size(2D only)
		 */
         //       void setPadH(uint32 value);

		/* @PoolingLayer set pad W
		 * @details set the padding W size
		 * 
		 * @param	value		the padding W size(2D only)
		 */
         //       void setPadW(uint32 value);

		/* @PoolingLayer set pool
		 * @details set the pool type
		 *
		 * @param	method		the method of pool
		 */
		void setPool(PoolMethod method);

		/* @PoolingLayer set engine
		 * @details set the engine type
		 *
		 * @param	type         the type of engine
		 */
		void setEngine(Engine type);

		/* @PoolingLayer set global pooling
		 * @details If global_pooling then it will pool over the size of the bottom by doing
		 *          kernel_h = bottom->height and kernel_w = bottom->width
		 *
		 * @param	state		the state of global pooling
		 */
		void setGlobalPooling(bool state);

		/* @PoolingLayer get engine
		 * @details get engine
		 * 
		 * @return	Engine		the engine 
		 */
		Engine getEngine();

		/* @PoolingLayer get global pooling
		 * @details get global pooling
		 * 
		 * @return	bool		the global pooling
		 */
		bool getGlobalPooling();

		/* @PoolingLayer get kernel size
		 * @details get kernel size
		 * 
		 * @return	int			the kernel size(equal)
		 */
                uint32 getKernelSize();

		/* @PoolingLayer get kernel H
		 * @details get kernel size
		 * 
		 * @return	int			the kernel H(2D only)
		 */
         //       uint32 getKernelH();

		/* @PoolingLayer get kernel W
		 * @details get kernel size
		 * 
		 * @return	int			the kernel W(2D only)
		 */
         //       uint32 getKernelW();

		/* @PoolingLayer get stride
		 * @details get the stride
		 *
		 * @return int			the stride(equal in Y, X)
		 */
                uint32 getStride();

		/* @PoolingLayer get stride H
		 * @details get the stride H
		 *
		 * @return int			the stride H(2D only)
		 */
         //       uint32 getStrideH();

		/* @PoolingLayer get stride W
		 * @details get the stride W
		 *
		 * @return int			the stride W(2D only)
		 */
         //       uint32 getStrideW();

		/* @PoolingLayer get pad
		 * @details get the padding size
		 * 
		 * @return	int			the padding size(equal in Y, X)
		 */
                uint32	getPad();

		/* @PoolingLayer get pad H
		 * @details get the padding H size
		 * 
		 * @return	int			the padding H size(2D only)
		 */
         //       uint32	getPadH();

		/* @PoolingLayer get pad W
		 * @details get the padding W size
		 * 
		 * @return	int			the padding W size(2D only)
		 */
         //       uint32	getPadW();

		/* @PoolingLayer get pool
		 * @details get the pool
		 *
		 * @return string			the pool type
		 */
		PoolMethod getPool();

		string convet2CaffeFormat();
	};
	
	class LAYERLIB_API SPPLayer : public BaseLayer
	{
		public:

			/* @SPPLayer  constructor of SPPLayer
			* @details this class can help user to contruct own Pooling layer
			*/
			SPPLayer(string name);

			SPPLayer();

			/* @SPPLayer deconstructor of SPPLayer
			* @details this class will be deconstruct by user
			*/
			~SPPLayer();

			/* @SPPLayer set Pyramid Height
			 * @details set the Pyramid Height
			 *
			 * @param	value		the Pyramid Height
			 */
                        void setPyramidHeight(uint32 value);

			/* @SPPLayer set pool
			 * @details set the pool type
			 *
			 * @param type          the pool type(Max)
			 */
			void setPool(PoolMethod type);

			/* @SPPLayer set Engine
			 * @details set the Engine type
			 *
			 * @param type          the Engine type(DEFAULT:0,CAFFE:1,CUDNN:2)
			 */
			void setEngine(Engine value);

		   /* @SPPLayer get Pyramid Height
			* @details get the Pyramid Height
			*
			* @return size			the Pyramid Height
			*/
                        uint32 getPyramidHeight();

			/* @SPPLayer get pool
			* @details get the pool
			*
			* @return string			the pool type
			*/
			PoolMethod getPool();

			/* @SPPLayer get engine
			* @details get the engine
			*
			* @return int			the engine type
			*/
			Engine getEngine();

			/* @SPPLayer convert to caffe format
			* @details convert current layer definition to caffe(.prototxt)
			 */
			string convet2CaffeFormat();
	};
	
	class LAYERLIB_API LRNLayer : public BaseLayer
	{
		public:

			/* @LRNLayer  constructor of LRNLayer
			* @details this class can help user to contruct own LRN layer
			*/
			LRNLayer(string name);
			
			LRNLayer();

			/* @LRNLayer deconstructor of LRNLayer
			* @details this class will be deconstruct by user
			*/
			~LRNLayer();

			/* @LRNLayer set localSize
			 * @details set the localSize
			 *
			 * @param	value		the localSize
			 */
                        void setLocalSize(uint32 value);
			
			/* @LRNLayer set alpha
			 * @details set the alpha
			 *
			 * @param	value		the alpha
			 */
			void setAlpha(float value);
			
			/* @LRNLayer set beta
			 * @details set the beta
			 *
			 * @param	value		the beta
			 */
			void setBeta(float value);

			/* @LRNLayer set norm_region
			 * @details set the norm_region type
			 *
			 * @param type          the pool norm_region(ACROSS_CHANNELS)
			 */
			void setNormRegion(NormRegion type);

			/* @LRNLayer set k
			 * @details set the k
			 *
			 * @param	value		the k
			 */
			void setK(float value);

                        /* @LRNLayer set Engine
                         * @details set the Engine type
                         *
                         * @param type          the Engine type(DEFAULT:0,CAFFE:1,CUDNN:2)
                         */
                        void setEngine(Engine value);

			/* @LRNLayer get local_size
			* @details get the local_size
			*
			* @return size			the local_size
			*/
                        uint32 getLocalSize();

			/* @LRNLayer get alpha
			 * @details get the alpha
			* 
			* @return	float			the alpha
			*/
			float getAlpha();

			/* @LRNLayer get beta
			 * @details get the beta
			* 
			* @return	float			the beta
			*/
			float getBeta();

			/* @LRNLayer get norm_region
			* @details get the norm_region
			*
			* @return string			the norm_region type
			*/
			NormRegion getNormRegion();

			/* @LRNLayer get k
			 * @details get the k
			* 
			* @return	float			the k
			*/
			float getK();

                        /* @LRNLayer get engine
                        * @details get the engine
                        *
                        * @return Engine			the engine type
                        */
                        Engine getEngine();

			/* @LRNLayer convert to caffe format
			* @details convert current layer definition to caffe(.prototxt)
			 */
			string convet2CaffeFormat();
	};
}
#endif //VISIONLAYERS
