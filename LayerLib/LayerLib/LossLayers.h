#ifndef _LOSSLAYERS_H
#define _LOSSLAYERS_H


#include "LayerEnum.h"
#include "BaseLayer.h"
#include "LayerParam.h"
#include "LossLayerParam.h"

typedef unsigned int uint32;

using namespace std;

/* @namespace MMALab
 * @MMALab namespace
 */
namespace MMALab
{

	/* @class ContrastiveLossLayer
	 * @basic class for contrastiveLoss layer definition
	 */
	class LAYERLIB_API ContrastiveLossLayer : public BaseLayer
	{

	public:

		/* @ContrastiveLossLayer constructor of ContrastiveLossLayer
		 * @details this class can help user to contruct own ContrastiveLoss layer
		 */
		ContrastiveLossLayer(string name);

		ContrastiveLossLayer();

		/* @ContrastiveLossLayer deconstructor of ContrastiveLossLayer
		 * @details this class will be deconstruct by user
		 */
		~ContrastiveLossLayer();

		/* @ContrastiveLossLayer set margin
		 * @details set marin for dissimilar pair
		 *
		 * @param	value		margin for dissimilar pair
		 */
                void setMargin(float value);

		/* @ContrastiveLossLayer set legacy version
		 * @details set false uses (margin - d)^2
		 * @        set true  uses (margin - d^2)
		 * 
		 * @param	state		the implementation of this cost function
		 */
		void setLegacyVersion(bool state);

		/* @ContrastiveLossLayer get margin
		 * @details get margin for dissimilar pair
		 *
		 * @return	double		the margin for dissimilar pair
		 */
                float getMargin();

		/* @ContrastiveLossLayer get legacy version
		 * @details get the implementation of this cost function
		 * 
		 * @return	bool		the implementation of this cost function
		 */
		bool getLegacyVersion();

		/* @ContrastiveLossLayer convert to caffe format
		 * @details convert current layer definition to caffe(.prototxt)
		 */
		string convet2CaffeFormat();
	};

	/* @class HingeLossLayer
	 * @basic class for higeLoss layer definition
	 */
	class LAYERLIB_API HingeLossLayer : public BaseLayer
	{

	public:
		/* @HingeLossLayer constructor of HingeLossLayer
		 * @details this class can help user to contruct own hingeLoss layer
		 */
		HingeLossLayer(string name);

		HingeLossLayer();

		/* @HingeLossLayer deconstructor of HingeLossLayer
		 * @details this class will be deconstruct by user
		 */
		~HingeLossLayer();

		/* @HingeLossLayer set norm
		 * @details set norm to use L1 or L2
		 *
		 * @param	value		specify the norm to use L1 or L2
		 */
		void setNorm(Norm norm);

		/* @HingeLossLayer get norm
		 * @details get norm to use L1 or L2
		 *
		 * @return	string		the norm to use L1 or L2
		 */
		Norm getNorm();

		/* @HingeLossLayer convert to caffe format
		 * @details convert current layer definition to caffe(.prototxt)
		 */
		string convet2CaffeFormat();
	};
	
	/* @class InfogainLossLayer
	 * @basic class for InfogainLoss layer definition
	 */
	class LAYERLIB_API InfogainLossLayer : public BaseLayer
	{
	public:

		/* @InfogainLossLayer constructor of InfogainLossLayer
		 * @details this class can help user to contruct own InfogainLoss layer
		 */
		InfogainLossLayer(string name);

		InfogainLossLayer();

		/* @InfogainLossLayer deconstructor of InfogainLossLayer
		 * @details this class will be deconstruct by user
		 */
		~InfogainLossLayer();
		
		/* @InfogainLossLayer set source
		 * @details set the infogain matrix source
		 *
		 * @param	value		specify the infogain matrix source
		 */
		void setSource(string value);

		/* @InfogainLossLayer get source
		 * @details get the infogain matrix source
		 *
		 * @return	string		the infogain matrix source
		 */
		string getSource();

		/* @InfogainLossLayer convert to caffe format
		 * @details convert current layer definition to caffe(.prototxt)
		 */
		string convet2CaffeFormat();
	};

        /* @class MultinomialLogisticLossLayer
         * @basic class for MultinomialLogisticLoss layer definition
         */
        class LAYERLIB_API MultinomialLogisticLossLayer : public BaseLayer
        {
        public:

                /* @MultinomialLogisticLossLayer constructor of MultinomialLogisticLossLayer
                 * @details this class can help user to contruct own MultinomialLogisticLoss layer
                 */
                MultinomialLogisticLossLayer(string name);

                MultinomialLogisticLossLayer();

                /* @MultinomialLogisticLossLayer deconstructor of MultinomialLogisticLossLayer
                 * @details this class will be deconstruct by user
                 */
                ~MultinomialLogisticLossLayer();

                /* @MultinomialLogisticLossLayer convert to caffe format
                 * @details convert current layer definition to caffe(.prototxt)
                 */
                string convet2CaffeFormat();
        };

	/* @class AccuracyLayer
	 * @basic class for Accuracy layer definition
	 */
	class LAYERLIB_API AccuracyLayer : public BaseLayer
	{
	public:

		/* @AccuracyLayer constructor of AccuracyLayer
		 * @details this class can help user to contruct own Accuracy layer
		 */
		AccuracyLayer(string name);

		AccuracyLayer();

		/* @AccuracyLayer deconstructor of AccuracyLayer
		 * @details this class will be deconstruct by user
		 */
		~AccuracyLayer();

		/* @AccuracyLayer set top k
		 * @details when computing Accuracy, count as correct by comparing 
		 *          the true label to the top k scoring classes. 
		 *          By default, only compare to the top scoring class (i.e. argmax).
		 *
		 * @param	value		the top scoring class
		 */
                void setTopK(uint32 value);

		/* @AccuracyLayer set axis
		 * @details the "label" axis of the prediction blob, whose argmax corresponds 
		 *          to the predicted label -- may be negative to index from the end 
		 *          (e.g., -1 for the last axis).  
		 *          For example, if axis == 1 and the predictions are (N x C x H x W), 
		 *          the label blob is expected to contain N*H*W ground truth labels 
		 *          with integer values in {0, 1, ..., C-1}.
		 *
		 * @param	value		the axis of the prediction blob
		*/
		void setAxis(int value);

		/* @AccuracyLayer set ignore label
		 * @details if specified, ignore instances with the given label.
		 *
		 * @param	value		specidied label
		 */
		void setIgnoreLabel(int value);

		/* @AccuracyLayer get ignore label
		 * @details get the specified  label.
		 *
		 * @param	value		specidied label
		 */
		int getIgnoreLabel();

		/* @AccuracyLayer get axis
		 * @details get the axis of the prediction blob
		 *
		 * @return	int			the axis of the prediction blob
		 */
		int getAxis();

		/* @AccuracyLayer get top k
		 * @details get the top scoring class (i.e. argmax).
		 *
		 * @return	int			the top scoring class
		 */
                uint32 getTopK();

		/* @AccuracyLayer convert to caffe format
		 * @details convert current layer definition to caffe(.prototxt)
		 */
		string convet2CaffeFormat();
	};

        /* @class SigmoidCrossEntropyLossLayer
         * @basic class for SigmoidCrossEntropyLoss layer definition
         */
        class LAYERLIB_API SigmoidCrossEntropyLossLayer : public BaseLayer
        {
        public:

                /* @SigmoidCrossEntropyLossLayer constructor of SigmoidCrossEntropyLossLayer
                 * @details this class can help user to contruct own SigmoidCrossEntropyLoss layer
                 */
                SigmoidCrossEntropyLossLayer(string name);

                SigmoidCrossEntropyLossLayer();

                /* @SigmoidCrossEntropyLossLayer deconstructor of SigmoidCrossEntropyLossLayer
                 * @details this class will be deconstruct by user
                 */
                ~SigmoidCrossEntropyLossLayer();

                /* @AccuracyLayer convert to caffe format
                 * @details convert current layer definition to caffe(.prototxt)
                 */
                string convet2CaffeFormat();
        };

        /* @class EuclideanLossLayer
         * @basic class for EuclideanLoss layer definition
         */
        class LAYERLIB_API EuclideanLossLayer : public BaseLayer
        {
        public:

                /* @EuclideanLossLayer constructor of EuclideanLossLayer
                 * @details this class can help user to contruct own EuclideanLoss layer
                 */
                EuclideanLossLayer(string name);

                EuclideanLossLayer();

                /* @EuclideanLossLayer deconstructor of EuclideanLossLayer
                 * @details this class will be deconstruct by user
                 */
                ~EuclideanLossLayer();

                /* @EuclideanLossLayer convert to caffe format
                 * @details convert current layer definition to caffe(.prototxt)
                 */
                string convet2CaffeFormat();
        };

        class LAYERLIB_API SoftmaxWithLossLayer : public BaseLayer
        {
        public:

                /* @SoftmaxWithLossLayer constructor of SoftmaxWithLossLayer
                 * @details this class can help user to contruct own SoftmaxWithLoss layer
                 */
                SoftmaxWithLossLayer(string name);

                SoftmaxWithLossLayer();

                /* @SoftmaxWithLossLayer deconstructor of SoftmaxWithLossLayer
                 * @details this class will be deconstruct by user
                 */
                ~SoftmaxWithLossLayer();

                /* @SoftmaxWithLossLayer set ignore label
                 * @details if specified, ignore instances with the given label.
                 *
                 * @param	value		specidied label
                 */
                void setIgnoreLabel(int value);

                /* @SoftmaxWithLossLayer set normalize
                 * @details this parameter can be set to false to normalize mean only
                 *
                 * @param	state		the state of normalize
                 */
                void setNormalize(bool state);

                /* @SoftmaxWithLossLayer set engine
                 * @details set engine
                 *
                 * @param	value		the value of engine
                 */
                void setEngine(Engine type);

                /* @SoftmaxWithLossLayer set axis
                 * @details the "label" axis of the prediction blob, whose argmax corresponds
                 *          to the predicted label -- may be negative to index from the end
                 *          (e.g., -1 for the last axis).
                 *          For example, if axis == 1 and the predictions are (N x C x H x W),
                 *          the label blob is expected to contain N*H*W ground truth labels
                 *          with integer values in {0, 1, ..., C-1}.
                 *
                 * @param	value		the axis of the prediction blob
                */
                void setAxis(int value);

                /* @SoftmaxWithLossLayer get ignore label
                 * @details get the specified  label.
                 *
                 * @param	value		specidied label
                 */
                int getIgnoreLabel();

                /* @SoftmaxWithLossLayer get normalize
                 * @details get the normalize variance
                 *
                 * @return	bool		the state of normalize
                 */
                bool getNormalize();

                /* @SoftmaxWithLossLayer get engine
                 * @details get engine
                 *
                 * @return	string		the value of engine
                 */
                Engine getEngine();

                /* @SoftmaxWithLossLayer get axis
                 * @details get the axis of the prediction blob
                 *
                 * @return	int			the axis of the prediction blob
                 */
                int getAxis();

                /* @SoftmaxWithLossLayer convert to caffe format
                 * @details convert current layer definition to caffe(.prototxt)
                 */
                string convet2CaffeFormat();
        };


}

#endif //LOSSLAYERS
