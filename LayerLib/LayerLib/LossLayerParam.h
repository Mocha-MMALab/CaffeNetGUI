#ifndef _LOSSLAYERPARAM_H
#define _LOSSLAYERPARAM_H


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
	
	/* @class ContrastiveLossParam
	 * @basic class of ContrastiveLoss parameter definition
	 */
	class LAYERLIB_API ContrastiveLossParam
	{

	public:

		/* @ContrastiveLossParam margin
		 * @details the margin for dissimilar pair
		 */
                float mMargin;

		/* @ContrastiveLossParam legacy version
		 * @details the legacy version = false uses (margin - d)^2
		 * @        the legacy version = true  uses (margin - d^2)
		 */
		bool   mLegacyVersion;

		/* @ContrastiveLossParam constructor of ContrastiveLossParam
		 * @details this class can help user to define parameter of contrastiveLoss layer
		 */
		ContrastiveLossParam();

		/* @ContrastiveLossParam deconstructor of ContrastiveLossParam
		 * @details this class will be deconstruct by user
		 */
		~ContrastiveLossParam();
	};

	/* @class HingeLossParam
	 * @basic class of HingeLoss parameter definition
	 */
	class LAYERLIB_API HingeLossParam
	{
		
	public:

		/* @HingeLossParam norm
		 * @details the specify the norm to use L1 or L2
		 */
		Norm mNorm;

		/* @HingeLossParam constructor of HingeLossParam
		 * @details this class can help user to define parameter of HingeLoss layer
		 */
		HingeLossParam();

		/* @HingeLossParam deconsturctor of HingeLossParam
		 * @details this class will be deconstruct by user
		 */
		~HingeLossParam();
	};
	
        /* @class InfogainLossParam
	 * @basic class of InfogainLoss parameter definition
	 */
	class LAYERLIB_API InfogainLossParam
	{
	public:

		/* @InfogainLossParam source
		 * @details specify the infogain matrix source
		 */
		string mSource;

		/* @InfogainLossParam constructor of InfogainLossParam
		 * @details this class can help user to define parameter of InfogainLoss layer
		 */
		InfogainLossParam();

		/* @InfogainLossParam deconsturctor of InfogainLossParam
		 * @details this class will be deconstruct by user
		 */
		~InfogainLossParam();
	};

        /* @class MultinomialLogisticLossParam
         * @basic class of MultinomialLogisticLoss parameter definition
         */
        class LAYERLIB_API MultinomialLogisticLossParam
        {
        public:

                /* @MultinomialLogisticLossParam constructor of MultinomialLogisticLossParam
                 * @details this class can help user to define parameter of MultinomialLogisticLoss layer
                 */
                MultinomialLogisticLossParam();

                /* @MultinomialLogisticLossParam deconsturctor of MultinomialLogisticLossParam
                 * @details this class will be deconstruct by user
                 */
                ~MultinomialLogisticLossParam();
        };

	/* @class AccuracyParam
	 * @basic class of Accuracy parameter definition
	 */
	class LAYERLIB_API AccuracyParam
	{
	public:
		/* @AccuracyParam top k
		 * @details when computing accuracy, count as correct by comparing the true label
		 * @        to the top k socing classes.
		 * @        By default, only compare to the top scoring class (i.e. argmax).
		 */
                uint32 mTopk;

		/* @AccuracyParam axis
		 * @detals the "label" axis of the prediction blob, whose argmax corresponds to 
		 * @       the predicted label -- may be negative to index from the end 
		 * @       (e.g., -1 for the last axis).  For example, if axis == 1 and the 
		 * @       predictions are (N x C x H x W), the label blob is expected to 
		 * @       contain N*H*W ground truth labels with integer values in 
		 * @       {0, 1, ..., C-1}.
		 */
		int mAxis;

		/* @AccuracyParam ignore label
		 * @details if specified, ignore instances with the given label.
		 */
                int mIgnoreLabel;

		/* @AccuracyParam constructor of AccuracyParam
		 * @details this class can help user to define parameter of Accuracy layer
		 */
		AccuracyParam();

		/* @AccuracyParam deconsturctor of AccuracyParam
		 * @details this class will be deconstruct by user
		 */
		~AccuracyParam();
        };

        /* @class SigmoidCrossEntropyLossParam
         * @basic class of SigmoidCrossEntropyLoss parameter definition
         */
        class LAYERLIB_API SigmoidCrossEntropyLossParam
        {
        public:

                /* @SigmoidCrossEntropyLossParam constructor of SigmoidCrossEntropyLossParam
                 * @details this class can help user to define parameter of SigmoidCrossEntropyLoss layer
                 */
                SigmoidCrossEntropyLossParam();

                /* @SigmoidCrossEntropyLossParam deconsturctor of SigmoidCrossEntropyLossParam
                 * @details this class will be deconstruct by user
                 */
                ~SigmoidCrossEntropyLossParam();
        };

        /* @class SigmoidCrossEntropyLossParam
         * @basic class of SigmoidCrossEntropyLoss parameter definition
         */
        class LAYERLIB_API EuclideanLossParam
        {
        public:

                /* @EuclideanLossParam constructor of EuclideanLossParam
                 * @details this class can help user to define parameter of EuclideanLoss layer
                 */
                EuclideanLossParam();

                /* @EuclideanLossParam deconsturctor of EuclideanLossParam
                 * @details this class will be deconstruct by user
                 */
                ~EuclideanLossParam();
        };

        /* @class SoftmaxWithLossParam
         * @basic class of SoftmaxWithLoss parameter definition
         */
        class LAYERLIB_API SoftmaxWithLossParam
        {

        public:

                /* @SoftmaxWithLossParam ignore label
                * @details if specified, ignore instances with the given label.
                */
                int mIgnoreLabel;

                /* @SoftmaxWithLossParam normalize
                 * @details this parameter can be set to false to normalize mean only
                 */
                bool mNormalize;

                /* @SoftmaxWithLossParam engine
                 * @details engine
                 */
                Engine mEngine;

                /* @SoftmaxWithLossParam axis
                 * @details The axis along which to perform the softmax -- may be negative to index
                 *          from the end (e.g., -1 for the last axis).
                 *          Any other axes will be evaluated as independent softmaxes.
                 */
                int mAxis;

                /* @SoftmaxWithLossParam constructor of SoftmaxWithLossParam
                 * @details this class can help user to define parameter of SoftmaxWithLoss layer
                 */
                SoftmaxWithLossParam();

                /* @SoftmaxWithLossParam deconstructor of SoftmaxWithLossParam
                 * @details this class will be deconstruct by user
                 */
                ~SoftmaxWithLossParam();
        };

}

#endif //LOSSLAYERPARAM
