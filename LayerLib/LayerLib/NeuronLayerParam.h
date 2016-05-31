#ifndef _NEURONLAYERPARAM_H
#define _NEURONLAYERPARAM_H


#include <string>
#include "LayerEnum.h"
#include "LayerParam.h"

using namespace std;
using namespace MMALab;

/* @namespace MMALab
 * @MMALab namespace
 */
namespace MMALab
{

	/* @class PReLUParam
	 * @basic class of PReLU parameter definition
	 */
	class LAYERLIB_API PReLUParam
	{
	public:

		/* @PReLUParam filter
		 * @details the filter
		 */
		void* mFilter;

		/* @PReLUParam filter
		 * @details Initial value of a_i. Default is a_i=0.25 for all i.
		 */
		FilterType mFilterType;

		/* @PReLUParam channel shared
		 * @details Whether or not slope paramters are shared across channels.
		 */
		bool mChannelShared;

		/* @PReLUParam constructor of PReLUParam
		 * @details this class can help user to define parameter of PReLU layer
		 */
		PReLUParam();

		/* @PReLUParam deconsturctor of PReLUParam
		 * @details this class will be deconstruct by user
		 */
		~PReLUParam();
	};

	/* @class ThresholdParam
	 * @basic class of Threshold parameter definition
	 */
	class LAYERLIB_API ThresholdParam
	{
	public:

		/* @ThresholdParam threshold
		 * @details Strictly positive values
		 */
		float mThreshold;

		/* @ThresholdParam constructor of ThresholdParam
		 * @details this class can help user to define parameter of Threshold layer
		 */
		ThresholdParam();

		/* @ThresholdParam deconsturctor of ThresholdParam
		 * @details this class will be deconstruct by user
		 */
		~ThresholdParam();

	};

	/* @class TanHParam
	 * @basic class of TanH parameter definition
	 */
	class LAYERLIB_API TanHParam
	{
	public:

		/* @TanHParam engine
		 * @details engine
		 */
		Engine mEngine;

		/* @TanHParam constructor of TanHParam
		 * @details this class can help user to define parameter of TanH layer
		 */
		TanHParam();

		/* @TanHParam deconsturctor of TanHParam
		 * @details this class will be deconstruct by user
		 */
		~TanHParam();
	};

	/* @class SigmoidParam
	 * @basic class of Sigmoid definition
	 */
	class LAYERLIB_API SigmoidParam
	{
	public:

		/* @SigmoidParam engine
		 * @details engine
		 */
		Engine mEngine;

		/* @SigmoidParam constructor of SigmoidParam
		 * @details this class can help user to define parameter of Sigmoid layer
		 */
		SigmoidParam();

		/* @SigmoidParam deconsturctor of SigmoidParam
		 * @details this class will be deconstruct by user
		 */
		~SigmoidParam();
	};

	/* @class ReLUParam
	 * @basic class of ReLU definition
	 */
	class LAYERLIB_API ReLUParam
	{
	public:

		/* @ReLUParam negative slope
		 * @details Allow non-zero slope for negative inputs to speed up optimization
		 */
		float mNegativeSlope;

		/* @ReLUParam engine
		 * @details engine
		 */
		Engine mEngine;

		/* @ReLUParam constructor of ReLUParam
		 * @details this class can help user to define parameter of ReLU layer
		 */
		ReLUParam();

		/* @ReLUParam deconsturctor of ReLUParam
		 * @details this class will be deconstruct by user
		 */
		~ReLUParam();
	};

	/* @class PowerParam
	 * @basic class of ReLU definition
	 */
	class LAYERLIB_API PowerParam
	{
	public:

		/* @PowerParam power
		 * @details outputs y = (shift + scale * x) ^ power
		 */
		float mPower;

		/* @PowerParam scale
		 * @details outputs y = (shift + scale * x) ^ power
		 */
		float mScale;

		/* @PowerParam shift
		 * @details outputs y = (shift + scale * x) ^ power
		 */
		float mShift;

		/* @PowerParam constructor of PowerParam
		 * @details this class can help user to define parameter of Power layer
		 */
		PowerParam();

		/* @PowerParam deconsturctor of PowerParam
		 * @details this class will be deconstruct by user
		 */
		~PowerParam();

	};

	/* @class DropoutParam
	 * @basic class of Dropout definition
	 */
	class LAYERLIB_API DropoutParam
	{
	public:

		/* @DropoutParam dropout ratio
		 * @details dropout ratio
		 */
		float mDropoutRatio;

		/* @DropoutParam constructor of DropoutParam
		 * @details this class can help user to define parameter of Dropout layer
		 */
		DropoutParam();

		/* @DropoutParam deconsturctor of DropoutParam
		 * @details this class will be deconstruct by user
		 */
		~DropoutParam();

	};

	/* @class ExpParam
	 * @basic class of Exp definition
	 */
	class LAYERLIB_API ExpParam
	{
	public:

		/* @ExpParam base
		 * @details y = base ^ (shift + scale * x), for base > 0.
		 *          Or if base is set to the default (-1), base is set to e,
		 *          so y = exp(shift + scale * x).
		 */
		float mBase;

		/* @ExpParam scale
		 * @details y = base ^ (shift + scale * x), for base > 0.
		 *          Or if base is set to the default (-1), base is set to e,
		 *          so y = exp(shift + scale * x).
		 */
		float mScale;

		/* @ExpParam shift
		 * @details y = base ^ (shift + scale * x), for base > 0.
		 *          Or if base is set to the default (-1), base is set to e,
		 *          so y = exp(shift + scale * x).
		 */
		float mShift;

		/* @ExpParam constructor of ExpParam
		 * @details this class can help user to define parameter of Exp layer
		 */
		ExpParam();

		/* @ExpParam deconsturctor of ExpParam
		 * @details this class will be deconstruct by user
		 */
		~ExpParam();

	};

	/* @class LogParam
	 * @basic class of Log definition
	 */
	class LAYERLIB_API LogParam
	{
	public:

		/* @LogParam base
		 * @details y = base ^ (shift + scale * x), for base > 0.
		 *          Or if base is set to the default (-1), base is set to e,
		 *          so y = ln(shift + scale * x) = log_e(shift + scale * x)
		 */
		float mBase;

		/* @LogParam scale
		 * @details y = base ^ (shift + scale * x), for base > 0.
		 *          Or if base is set to the default (-1), base is set to e,
		 *          so y = ln(shift + scale * x) = log_e(shift + scale * x)
		 */
		float mScale;

		/* @LogParam shift
		 * @details y = base ^ (shift + scale * x), for base > 0.
		 *          Or if base is set to the default (-1), base is set to e,
		 *          so y = ln(shift + scale * x) = log_e(shift + scale * x)
		 */
		float mShift;

		/* @LogParam constructor of LogParam
		 * @details this class can help user to define parameter of Log layer
		 */
		LogParam();

		/* @LogParam deconsturctor of ExpParam
		 * @details this class will be deconstruct by user
		 */
		~LogParam();

	};

        /* @class AbsValParam
         * @basic class of Log definition
         */
        class LAYERLIB_API AbsValParam
        {
        public:

                /* @AbsValParam constructor of AbsValParam
                 * @details this class can help user to define parameter of AbsVal layer
                 */
                AbsValParam();

                /* @AbsValParam deconsturctor of AbsValParam
                 * @details this class will be deconstruct by user
                 */
                ~AbsValParam();

        };

        /* @class BNLLParam
         * @basic class of Log definition
         */
        class LAYERLIB_API BNLLParam
        {
        public:

                /* @BNLLParam constructor of BNLLParam
                 * @details this class can help user to define parameter of BNLL layer
                 */
                BNLLParam();

                /* @BNLLParam deconsturctor of BNLLParam
                 * @details this class will be deconstruct by user
                 */
                ~BNLLParam();

        };
}

#endif //NEURONLAYERPARAM
