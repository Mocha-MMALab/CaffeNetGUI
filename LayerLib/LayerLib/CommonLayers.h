#ifndef _COMMONLAYERS_H
#define _COMMONLAYERS_H


#include "LayerEnum.h"
#include "BaseLayer.h"
#include "LayerParam.h"
#include "CommonLayerParam.h"

typedef unsigned int uint32;

using namespace std;

/* @namespace MMALab
 * @MMALab namespace
 */
namespace MMALab
{
	/* @class MVNLayer
	 * @basic class for MVN layer definition
	 */
	class LAYERLIB_API MVNLayer : public BaseLayer
	{
		public:

		/* @MVNLayer constructor of MVNLayer
		 * @details this class can help user to contruct own MVN layer
		 */
		MVNLayer(string name);

		MVNLayer();

		/* @MVNLayer deconstructor of MVNLayer
		 * @details this class will be deconstruct by user
		 */
		~MVNLayer();

		/* @MVNLayer set normalize variance
		 * @details this parameter can be set to false to normalize mean only
		 * 
		 * @param	state		the state of normalize variance 
		 */
		void setNormalizeVariance(bool state);

		/* @MVNLayer set across channels
		 * @details this parameter can be set to true to perform DNN-like MVN
		 *
		 * @prama	state		the state of across channels
		 */
		void setAcrossChannels(bool state);

		/* @MVNLayer set eps
		 * @details epsilon for not dividing by zero while normalizing variance
		 *
		 * @prama	value		the value of epsilon
		 */
		void setEps(float value);

		/* @MVNLayer get normalize variance
		 * @details get the normalize variance
		 *
		 * @return	bool		the state of normalize variance
		 */
		bool getNormalizeVariance();

		/* @MVNLayer get across channels
		 * @details get the across channels
		 *
		 * @return	bool		the state of across channels
		 */
		bool getAcrossChannels();

		/* @MVNLayer get eps
		 * @detail get epsilon
		 *
		 * @return	float		the value of epsilon
		 */
		float getEps();

		/* @MVNLayer convert to caffe format
		 * @details convert current layer definition to caffe(.prototxt)
		 */
		string convet2CaffeFormat();
	};
	
	/* @class ReshapeLayer
	 * @basic class for Reshape layer definition
	 */
	class LAYERLIB_API ReshapeLayer : public BaseLayer
	{
		public:

		/* @ReshapeLayer constructor of ReshapeLayer
		 * @details this class can help user to contruct own Reshape layer
		 */
		ReshapeLayer(string name);

		ReshapeLayer();

		/* @ReshapeLayer deconstructor of ReshapeLayer
		 * @details this class will be deconstruct by user
		 */
		~ReshapeLayer();

		/* @ReshapeLayer set shape
		 * @details Specify the output dimensions. If some of the dimensions are set to 0,
		 *          the corresponding dimension from the bottom layer is used (unchanged).
		 *          Exactly one dimension may be set to -1, in which case its value is
		 *          inferred from the count of the bottom blob and the remaining dimensions.
		 *
		 * @param	value		the value of shape
                 */
                void setShape(BlobShape* shape);

		/* @ReshapeLayer set axis
		 * @details axis may be non-zero to retain some portion of the beginning of the input
		 *          shape (and may be negative to index from the end; e.g., -1 to begin the
		 *          reshape after the last axis, including nothing in the reshape, -2 to 
		 *          include only the last axis, etc.).
		 *
		 * @param	value		the value of axis
		 */
		void setAxis(int value);

		/* @ReshapeLayer get num axes
		 * @details num_axes specifies the extent of the reshape.
		 *          If num_axes >= 0 (and axis >= 0), the reshape will be performed only on
		 *          input axes in the range [axis, axis+num_axes].
		 *          num_axes may also be -1, the default, to include all remaining axes.
		 *
		 * @param	value		the value of num axis
		 */
		void setNumAxis(int value);

		/* @ReshapeLayer get shape
		 * @detail get shpae
		 *
                 * @return	void		the value of shape
                 */
                void* getShape();

		/* @ReshapeLayer get axis
		 * @detail get axis
		 *
		 * @return	int			the value of axis
		 */
		int getAxis();

		/* @ReshapeLayer get num axis
		 * @detail get num axis
		 *
		 * @return	int			the value of num axis
		 */
		int getNumAxis();

		/* @ReshapeLayer convert to caffe format
		 * @details convert current layer definition to caffe(.prototxt)
                 */

		string convet2CaffeFormat();

	};

	/* @class ReductionLayer
	 * @basic class for Reduction layer definition
	 */
	class LAYERLIB_API ReductionLayer : public BaseLayer
	{
	public:

		/* @ReductionLayer constructor of ReductionLayer
		 * @details this class can help user to contruct own Reduction layer
		 */
		ReductionLayer(string name);

		ReductionLayer();

		/* @ReductionLayer deconstructor of ReductionLayer
		 * @details this class will be deconstruct by user
		 */
		~ReductionLayer();

		/* @ReductionLayer  set operation
		 * @details set reduction operation
		 *
		 * @param	value		reduction operation
		 */
		void setOperation(ReductionOp type);

		/* @ReductionLayer  set axis
		 * @details The first axis to reduce to a scalar -- may be negative to index from the
		 *          end (e.g., -1 for the last axis).
		 *
		 * @param	value		the value of axis
		 */
		void setAxis(int value);

		/* @ReductionLayer set coeff
		 * @details set coefficient for output
		 *
		 * @param	value		the value of coefficient
		 */
		void setCoeff(float value);

		/* @ReductionLayer get operation
		 * @details get  operation
		 *
		 * @return	string		the value of operation
		 */
		ReductionOp getOperation();

		/* @ReductionLayer get axis
		 * @details get axis
		 *
		 * @return	int			the value of axis
		 */
		int getAxis();

		/* @ReductionLayer get coeff
		 * @details get coefficient
		 * 
		 * @return	float		the value of coefficient
		 */
		float getCoeff();

		/* @ReductionLayer convert to caffe format
		 * @details convert current layer definition to caffe(.prototxt)
		 */
		string convet2CaffeFormat();

		
	};

	/* @class SliceLayer
	 * @basic class for Slice layer definition
	 */
	class LAYERLIB_API SliceLayer : public BaseLayer
	{

	public:

		/* @SliceLayer constructor of SliceLayer
		 * @details this class can help user to contruct own Slice layer
		 */
		SliceLayer(string name);

		SliceLayer();

		/* @SliceLayer deconstructor of SliceLayer
		 * @details this class will be deconstruct by user
		 */
		~SliceLayer();

		/* @SliceLayer  set axis
		 * @details The axis along which to slice -- may be negative to index from the end
		 *          (e.g., -1 for the last axis).
		 *
		 * @param	value		the value of axis
		 */
		void setAxis(int value);

		/* @SliceLayer  set slice point
		 * @details By default, SliceLayer concatenates blobs along the "channels" axis
		 *
		 * @param	value		the value of slice point
		 */
                void setSlicePoint(uint32 value);

		/* @SliceLayer  set slice dim
		 * @details alias for "axis" -- does not support negative indexing
		 *
		 * @param	value		the value of slice dim
		 */
                void setSliceDim(uint32 value);

		/* @SliceLayer get axis
		 * @details get axis
		 *
		 * @return	int			the value of axis
		 */
		int getAxis();

		/* @SliceLayer get slice point
		 * @details get slice point
		 *
		 * @return	int			the value of slice point
		 */
                uint32 getSlicePoint();

		/* @SliceLayer get slice dim
		 * @details get slice dim
		 *
		 * @return	int			the value of slice dim
		 */
                uint32 getSliceDim();

		/* @SliceLayer convert to caffe format
		 * @details convert current layer definition to caffe(.prototxt)
		 */
		string convet2CaffeFormat();
	};

	/* @class SoftmaxLayer
	 * @basic class for Softmax layer definition
	 */
	class LAYERLIB_API SoftmaxLayer : public BaseLayer
	{

	public:

		/* @SoftmaxLayer constructor of SoftmaxLayer
		 * @details this class can help user to contruct own Softmax layer
		 */
		SoftmaxLayer(string name);

		SoftmaxLayer();

		/* @SoftmaxLayer deconstructor of SoftmaxLayer
		 * @details this class will be deconstruct by user
		 */
		~SoftmaxLayer();

		/* @SoftmaxLayer set engine
		 * @details set engine
		 *
		 * @param	value		the value of engine
		 */
		void setEngine(Engine type);

		/* @SoftmaxLayer set axis
		 * @details The axis along which to perform the Softmax -- may be negative to index
		 *          from the end (e.g., -1 for the last axis).
		 *          Any other axes will be evaluated as independent Softmaxes.
		 *
		 * @param	value		the value of axis
		 */
		void setAxis(int value);
				
		/* @SoftmaxLayer get engine
		 * @details get engine
		 *
		 * @return	string		the value of engine
		 */
		Engine getEngine();

		/* @SoftmaxLayer get axis
		 * @details get axis
		 *
		 * @return	int			the value of axis
		 */
		int getAxis();

		/* @SoftmaxLayer convert to caffe format
		 * @details convert current layer definition to caffe(.prototxt)
		 */
		string convet2CaffeFormat();
	};

	/* @class InnerProductLayer
	 * @basic class for InnerProduct layer definition
	 */
	class LAYERLIB_API InnerProductLayer : public BaseLayer
	{
	public:

		/* @InnerProductLayer constructor of InnerProductLayer
		 * @details this class can help user to contruct own InnerProduct layer
		 */
		InnerProductLayer(string name);

		InnerProductLayer();

		/* @InnerProductLayer deconstructor of InnerProductLayer
		 * @details this class will be deconstruct by user
		 */
		~InnerProductLayer();

		/* @InnerProductLayer set num output
		 * @details The number of outputs for the layer
		 *
		 * @param	value		the value of sum output
		 */
                void setNumOutput(uint32 value);

		/* @InnerProductLayer set bias term
		 * @details whether to have bias terms
		 *
		 * @param	state		the state of bias term
		 */
		void setBiasTerm(bool state);			
		
		/* @InnerProductLayer set weight filter
		 * @details set the filter for the weight
		 *
		 * @param	weightfilter			the filter for the weight
		 */
		void setWeightfilter(Gaussian* weightfilter);

		/* @InnerProductLayer set weight filter
		 * @details set the filter for the weight
		 *
		 * @param	weightfilter			the filter for the weight
		 */
		void setWeightfilter(Constant* weightfilter);

		/* @InnerProductLayer set weight filter
		 * @details set the filter for the weight
		 *
		 * @param	weightfilter			the filter for the weight
		 */
		void setWeightfilter(Xavier* weightfilter);

                /* @InnerProductLayer set weight filter
                 * @details set the filter for the weight
                 *
                 * @param	weightfilter			the filter for the weight
                 */
                void setWeightfilter(Uniform* weightfilter);

                /* @InnerProductLayer set weight filter
                 * @details set the filter for the weight
                 *
                 * @param	weightfilter			the filter for the weight
                 */
                void setWeightfilter(Msra* weightfilter);

		/* @InnerProductLayer set bias filter
		 * @details set the filter for the bias
		 *
		 * @param	biasfilter			the filter for the weight
		 */
		void setBiasfilter(Gaussian* biasfilter);

                /* @InnerProductLayer set bias filter
                 * @details set the filter for the bias
                 *
                 * @param	biasfilter			the filter for the weight
                 */
                void setBiasfilter(Constant* biasfilter);

                /* @InnerProductLayer set bias filter
                 * @details set the filter for the bias
                 *
                 * @param	biasfilter			the filter for the weight
                 */
                void setBiasfilter(Xavier* biasfilter);

                /* @InnerProductLayer set bias filter
                 * @details set the filter for the bias
                 *
                 * @param	biasfilter			the filter for the weight
                 */
                void setBiasfilter(Uniform* biasfilter);

                /* @InnerProductLayer set bias filter
                 * @details set the filter for the bias
                 *
                 * @param	biasfilter			the filter for the weight
                 */
                void setBiasfilter(Msra* biasfilter);

		/* @InnerProductLayer set axis
		 * @details The first axis to be lumped into a single inner product computation;
		 *          all preceding axes are retained in the output.
		 *          May be negative to index from the end (e.g., -1 for the last axis).
		 *
		 * @param	value		the value of axis
		 */
		void setAxis(int value);

		/* @InnerProductLayer get num output
		 * @details get num output
		 *
		 * @return	int			the value of num output
		 */
                uint32 getNumOutput();

		/* @InnerProductLayer get bias term
		 * @details	get bias term
		 *
		 * @return	bool		the state of bias term		
		 */
		bool getBiasTerm();
				
		/* @InnerProductLayer get weight filter
		 * @details get the filter for the weight
		 *
		 * @return	string		the filter for the weight
		 */
		void* getWeightfilter();

		/* @InnerProductLayer get bias filter
		 * @details get the filter for the bias
		 *
		 * @return	string		the filter for the bias
		 */
		void* getBiasfilter();

		/* @InnerProductLayer get axis
		 * @details get axis
		 *
		 * @return	int			the value of axis
		 */
		int getAxis();

		/* @InnerProductLayer convert to caffe format
		 * @details convert current layer definition to caffe(.prototxt)
		 */
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

	/* @class FlattenLayer
	 * @basic class for Flatten layer definition
	 */
	class LAYERLIB_API FlattenLayer : public BaseLayer
	{
	public:

		/* @FlattenLayer constructor of FlattenLayer
		 * @details this class can help user to contruct own Flatten layer
		 */
		FlattenLayer(string name);

		FlattenLayer();

		/* @FlattenLayer deconstructor of FlattenLayer
		 * @details this class will be deconstruct by user
		 */
		~FlattenLayer();

		/* @FlattenLayer set axis
		 * @details The first axis to flatten: all preceding axes are retained in the output.
		 *          May be negative to index from the end (e.g., -1 for the last axis).
		 *
		 * @param	value		the value of axis
		 */
		void setAxis(int value);

		/* @FlattenLayer set end axis
		 * @details The last axis to flatten: all following axes are retained in the output.
		 *          May be negative to index from the end (e.g., the default -1 for the 
		 *          last axis).
		 *
		 * @param	value		the value of end axis
		 */
		void setEndAxis(int value);

		/* @FlattenLayer get axis
		 * @details get axis
		 *
		 * @return	int			the value of axis			
		 */
		int getAxis();

		/* @FlattenLayer get end axis
		 * @details get end axis
		 *
		 * @return	int			the value of end axis		
		 */
		int getEndAxis();

		/* @FlattenLayer convert to caffe format
		 * @details convert current layer definition to caffe(.prototxt)
		 */
		string convet2CaffeFormat();
	};

	/* @class EltwiseLayer
	 * @basic class for Eltwise layer definition
	 */
	class LAYERLIB_API EltwiseLayer : public BaseLayer
	{
	public:

		/* @EltwiseLayer constructor of EltwiseLayer
		 * @details this class can help user to contruct own Eltwise layer
		 */
		EltwiseLayer(string name);

		EltwiseLayer();

		/* @EltwiseLayer deconstructor of FlattenLayer
		 * @details this class will be deconstruct by user
		 */
		~EltwiseLayer();

		/* @EltwiseLayer set operation
		 * @details set element-wise operation
		 *
		 * @param	value			the value of operation
		 */
		void setOperation(EltwiseOp value);

		/* @EltwiseLayer set coeff
		 * @details set blob-wise coefficient for SUM operation
		 *
		 * @param	value			the value of coeff
		 */
		void setCoeff(float value);

		/* @EltwiseLayer set stable prod grad
		 * @details Whether to use an asymptotically slower (for >2 inputs) but stabler 
		 *          method of computing the gradient for the PROD operation. 
		 *          (No effect for SUM op.)
		 *
		 * @param	state			the state of stable prod grad
		 */
		void setStableProdGrad(bool state);

		/* @EltwiseLayer get operation
		 * @details get operation
		 *
		 * @return	string			the value of operation
		 */
		EltwiseOp getOperation();

		/* @EltwiseLayer get coeff
		 * @details get coeff
		 *
		 * @return	float			the value of operation
		 */
		float getCoeff();

		/* @EltwiseLayer get stable prod grad
		 * @details get stable prod grad
		 *
		 * @return	bool			the value of stable prod grad
		 */
		bool getStableProdGrad();

		/* @EltwiseLayer convert to caffe format
		 * @details convert current layer definition to caffe(.prototxt)
		 */
		string convet2CaffeFormat();

	};

	/* @class ConcatLayer
	 * @basic class for Concat layer definition
	 */
	class LAYERLIB_API ConcatLayer : public BaseLayer
	{
	public:

		/* @ConcatLayer constructor of ConcatLayer
		 * @details this class can help user to contruct own Concat layer
		 */
		ConcatLayer(string name);

		ConcatLayer();

		/* @ConcatLayer deconstructor of ConcatLayer
		 * @details this class will be deconstruct by user
		 */
		~ConcatLayer();

		/* @ConcatLayer set axis
		 * @details The axis along which to concatenate -- may be negative to index 
		 *          from the end (e.g., -1 for the last axis).  
		 *          Other axes must have the same dimension for all the bottom blobs.
		 *
		 * @param	value			the value of axis
		 */
		void setAxis(int value);

		/* @ConcatLayer set concat dim
		 * @details alias for "axis" -- does not support negative indexing.
		 *
		 * @param	value			the value of concat dim
		 */
                void setConcatDim(uint32 value);

		/* @ConcatLayer get axis
		 * @details get axis
		 *
		 * @return	int				the value of axis
		 */
		int getAxis();

		/* @ConcatLayer get concat dim
		 * @details get concat dim
		 *
		 * @return	int				the value of concat dim
		 */
                uint32 getConcatDim();

		/* @ConcatLayer convert to caffe format
		 * @details convert current layer definition to caffe(.prototxt)
		 */
		string convet2CaffeFormat();

	};

	/* @class ArgMaxLayer
	 * @basic class for ArgMax layer definition
	 */
	class LAYERLIB_API ArgMaxLayer : public BaseLayer
	{
	public:

		/* @ArgMaxLayer constructor of ArgMaxLayer
		 * @details this class can help user to contruct own ArgMax layer
		 */
		ArgMaxLayer(string name);

		ArgMaxLayer();

		/* @ArgMaxLayer deconstructor of ArgMaxLayer
		 * @details this class will be deconstruct by user
		 */
		~ArgMaxLayer();

		/* @ArgMaxLayer set out max val
		 * @details If true produce pairs (argmax, maxval)
		 *
		 * @param	value			the state of out max val
		 */
		void setOutMaxVal(bool state);

		/* @ArgMaxLayer set top k
		 * @details set top k
		 *
		 * @param	value			the value of top k
		 */
                void setTopK(uint32 value);

		/* @ArgMaxLayer set axis
		 * @details set axis
		 *
		 * @param	value			the value of axis
		 */
                void setAxis(int value);

		/* @ArgMaxLayer get out max val
		 * @details get out max val
		 *
		 * @return	bool			the value of out max val
		 */
		bool getOutMaxVal();

		/* @ArgMaxLayer get top k
		 * @details get top k
		 *
		 * @return	uint				the value of top k
		 */
                uint32 getTopK();

		/* @ArgMaxLayer get axis
		 * @details get axis
		 *
		 * @return	uint				the value of axis
		 */
                int getAxis();

		/* @ArgMaxLayer convert to caffe format
		 * @details convert current layer definition to caffe(.prototxt)
		 */
		string convet2CaffeFormat();

	};

}
#endif // COMMONLAYERS
