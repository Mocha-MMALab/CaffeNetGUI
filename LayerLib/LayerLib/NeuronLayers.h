#ifndef _NEURONLAYERS_H
#define _NEURONLAYERS_H

#include <string>
#include "LayerEnum.h"
#include "BaseLayer.h"
#include "LayerParam.h"
#include "NeuronLayerParam.h"

using namespace std;
using namespace MMALab;

/* @namespace MMALab
 * @MMALab namespace
 */
namespace MMALab
{

	/* @class PReLULayer
	 * @basic class for PReLU layer definition
	 */
	class LAYERLIB_API PReLULayer : public BaseLayer
	{
	public:

		/* @PReLULayer constructor of PReLULayer
		 * @details this class can help user to contruct own PReLU layer
		 */
		PReLULayer(string name);

		PReLULayer();

		/* @PReLULayer deconstructor of PReLULayer
		 * @details this class will be deconstruct by user
		 */
		~PReLULayer();
		
		/* @PReLULayer set filter
		 * @details Initial value of a_i. Default is a_i=0.25 for all i.
		 *
		 * @param	value		the value of filter
		 */
		void setFilter(Gaussian* filter);
		void setFilter(Constant* filter);
                void setFilter(Xavier* filter);
                void setFilter(Uniform* filter);
                void setFilter(Msra* filter);

		/* @PReLULayer set channel shared
		 * @details Whether or not slope paramters are shared across channels.
		 *
		 * @param	state		the value of channel shared
		 */
		void setChannelShared(bool state);

		/* @PReLULayer get filter
		 * @details get filter
		 *
		 * @return	string		the value of filter
		 */
		void* getFilter();

		/* @PReLULayer get channel shared
		 * @details get channel shared
		 *
		 * @return	bool		the state of channel shared
		 */
		FilterType getFilterType();

		void setFilterToNone();

		bool getChannelShared();

		/* @PReLULayer convert to caffe format
		 * @details convert current layer definition to caffe(.prototxt)
		 */
		string convet2CaffeFormat();
	};

	/* @class ThresholdLayer
	 * @basic class for Threshold layer definition
	 */
	class LAYERLIB_API ThresholdLayer : public BaseLayer
	{
	public:

		/* @ThresholdLayer constructor of ThresholdLayer
		 * @details this class can help user to contruct own Threshold layer
		 */
		ThresholdLayer(string name);

		ThresholdLayer();

		/* @ThresholdLayer deconstructor of ThresholdLayer
		 * @details this class will be deconstruct by user
		 */
		~ThresholdLayer();
		
		/* @ThresholdLayer set threshold
		 * @details Strictly positive values.
		 *
		 * @param	value		the value of threshold
		 */
		void setThreshold(float value);
				
		/* @ThresholdLayer get threshold
		 * @details get threshold
		 *
		 * @return	float		the value of threshold
		 */
		float getThreshold();			

		/* @ThresholdLayer convert to caffe format
		 * @details convert current layer definition to caffe(.prototxt)
		 */
		string convet2CaffeFormat();
	};

	/* @class TanHLayer
	 * @basic class for TanH layer definition
	 */
	class LAYERLIB_API TanHLayer : public BaseLayer
	{
	public:

		/* @TanHLayer constructor of TanHLayer
		 * @details this class can help user to contruct own TanH layer
		 */
		TanHLayer(string name);

		TanHLayer();

		/* @TanHLayer deconstructor of TanHLayer
		 * @details this class will be deconstruct by user
		 */
		~TanHLayer();
		
		/* @TanHLayer set engine
		 * @details set engine
		 *
		 * @param	value		the value of engine
		 */
		void setEngine(Engine value);
				
		/* @TanHLayer get engine
		 * @details get engine
		 *
		 * @return	string		the value of engine
		 */
		Engine getEngine();			

		/* @TanHLayer convert to caffe format
		 * @details convert current layer definition to caffe(.prototxt)
		 */
		string convet2CaffeFormat();
	};

	/* @class SigmoidLayer
	 * @basic class for Sigmoid layer definition
	 */
	class LAYERLIB_API SigmoidLayer : public BaseLayer
	{
	public:

		/* @SigmoidLayer constructor of SigmoidLayer
		 * @details this class can help user to contruct own Sigmoid layer
		 */
		SigmoidLayer(string name);


		SigmoidLayer();

		/* @SigmoidLayer deconstructor of SigmoidLayer
		 * @details this class will be deconstruct by user
		 */
		~SigmoidLayer();
		
		/* @SigmoidLayer set engine
		 * @details set engine
		 *
		 * @param	value		the value of engine
		 */
		void setEngine(Engine value);
				
		/* @SigmoidLayer get engine
		 * @details get engine
		 *
		 * @return	string		the value of engine
		 */
		Engine getEngine();			

		/* @SigmoidLayer convert to caffe format
		 * @details convert current layer definition to caffe(.prototxt)
		 */
		string convet2CaffeFormat();
	};

	/* @class ReLULayer
	 * @basic class for ReLU layer definition
	 */
	class LAYERLIB_API ReLULayer : public BaseLayer
	{
	public:

		/* @ReLULayer constructor of ReLULayer
		 * @details this class can help user to contruct own ReLU layer
		 */
		ReLULayer(string name);

		ReLULayer();

		/* @ReLULayer deconstructor of ReLULayer
		 * @details this class will be deconstruct by user
		 */
		~ReLULayer();
		
		/* @ReLULayer set negative slope
		 * @details Allow non-zero slope for negative inputs to speed up optimization
		 *
		 * @param	value		the value of negative slope
		 */
		void setNegativeSlope(float value);

		/* @ReLULayer set engine
		 * @details set engine
		 *
		 * @param	value		the value of engine
		 */
		void setEngine(Engine value);
				
		/* @ReLULayer get negative slope
		 * @details get negative slope
		 *
		 * @return	float		the value of negative slope
		 */
		float getNegativeSlope();

		/* @ReLULayer get engine
		 * @details get engine
		 *
		 * @return	string		the value of engine
		 */
		Engine getEngine();			

		/* @ReLULayer convert to caffe format
		 * @details convert current layer definition to caffe(.prototxt)
		 */
		string convet2CaffeFormat();
	};

	/* @class PowerLayer
	 * @basic class for Power layer definition
	 */
	class LAYERLIB_API PowerLayer : public BaseLayer
	{
	public:

		/* @PowerLayer constructor of PowerLayer
		 * @details this class can help user to contruct own Power layer
		 */
		PowerLayer(string name);
		
		PowerLayer();

		/* @PowerLayer deconstructor of PowerLayer
		 * @details this class will be deconstruct by user
		 */
		~PowerLayer();
		
		/* @PowerLayer set power
		 * @details outputs y = (shift + scale * x) ^ power
		 *
		 * @param	value		the value of power
		 */
		void setPower(float value);

		/* @PowerLayer set scale
		 * @details outputs y = (shift + scale * x) ^ power
		 *
		 * @param	value		the value of scale
		 */
		void setScale(float value);

		/* @PowerLayer set shift
		 * @details outputs y = (shift + scale * x) ^ power
		 *
		 * @param	value		the value of shift
		 */
		void setShift(float value);
				
		/* @PowerLayer get power
		 * @details get power
		 *
		 * @return	float		the value of power
		 */
		float getPower();

		/* @PowerLayer get scale
		 * @details get scale
		 *
		 * @return	float		the value of scale
		 */
		float getScale();

		/* @PowerLayer get shift
		 * @details get shift
		 *
		 * @return	float		the value of shift
		 */
		float getShift();

		/* @PowerLayer convert to caffe format
		 * @details convert current layer definition to caffe(.prototxt)
		 */
		string convet2CaffeFormat();
	};

	/* @class DropoutLayer
	 * @basic class for Dropout layer definition
	 */
	class LAYERLIB_API DropoutLayer : public BaseLayer
	{
	public:

		/* @DropoutLayer constructor of DropoutLayer
		 * @details this class can help user to contruct own Dropout layer
		 */
		DropoutLayer(string name);

		DropoutLayer();

		/* @DropoutLayer deconstructor of DropoutLayer
		 * @details this class will be deconstruct by user
		 */
		~DropoutLayer();
		
		/* @DropoutLayer set droupout ratio
		 * @details droupout ratio
		 *
		 * @param	value		the value of droupout ratio
		 */
		void setDropoutRatio(float value);
								
		/* @DropoutLayer get droupout ratio
		 * @details get droupout ratio
		 *
		 * @return	float		the value of droupout ratio
		 */
		float getDropoutRatio();

		/* @DropoutLayer convert to caffe format
		 * @details convert current layer definition to caffe(.prototxt)
		 */
		string convet2CaffeFormat();
	};

	/* @class ExpLayer
	 * @basic class for Exp layer definition
	 */
	class LAYERLIB_API ExpLayer : public BaseLayer
	{
	public:

		/* @ExpLayer constructor of ExpLayer
		 * @details this class can help user to contruct own Exp layer
		 */
		ExpLayer(string name);

		ExpLayer();

		/* @ExpLayer deconstructor of ExpLayer
		 * @details this class will be deconstruct by user
		 */
		~ExpLayer();
		
		/* @ExpLayer set base
		 * @details y = base ^ (shift + scale * x), for base > 0.
		 *          Or if base is set to the default (-1), base is set to e,
		 *          so y = exp(shift + scale * x).
		 *
		 * @param	value		the value of base
		 */
		void setBase(float value);

		/* @ExpLayer set scale
		 * @details y = base ^ (shift + scale * x), for base > 0.
		 *          Or if base is set to the default (-1), base is set to e,
		 *          so y = exp(shift + scale * x).
		 *
		 * @param	value		the value of scale
		 */
		void setScale(float value);

		/* @ExpLayer set shift
		 * @details y = base ^ (shift + scale * x), for base > 0.
		 *          Or if base is set to the default (-1), base is set to e,
		 *          so y = exp(shift + scale * x).
		 *
		 * @param	value		the value of shift
		 */
		void setShift(float value);
				
		/* @ExpLayer get base
		 * @details get base
		 *
		 * @return	float		the value of base
		 */
		float getBase();

		/* @ExpLayer get scale
		 * @details get scale
		 *
		 * @return	float		the value of scale
		 */
		float getScale();

		/* @ExpLayer get shift
		 * @details get shift
		 *
		 * @return	float		the value of shift
		 */
		float getShift();

		/* @ExpLayer convert to caffe format
		 * @details convert current layer definition to caffe(.prototxt)
		 */
		string convet2CaffeFormat();
	};

	/* @class LogLayer
	 * @basic class for Log layer definition
	 */
	class LAYERLIB_API LogLayer : public BaseLayer
	{
	public:

		/* @LogLayer constructor of LogLayer
		 * @details this class can help user to contruct own Log layer
		 */
		LogLayer(string name);

		LogLayer();

		/* @LogLayer deconstructor of LogLayer
		 * @details this class will be deconstruct by user
		 */
		~LogLayer();
		
		/* @LogLayer set base
		 * @details y = base ^ (shift + scale * x), for base > 0.
		 *          Or if base is set to the default (-1), base is set to e,
		 *          so y = ln(shift + scale * x) = log_e(shift + scale * x)
		 *
		 * @param	value		the value of base
		 */
		void setBase(float value);

		/* @LogLayer set scale
		 * @details y = base ^ (shift + scale * x), for base > 0.
		 *          Or if base is set to the default (-1), base is set to e,
		 *          so y = ln(shift + scale * x) = log_e(shift + scale * x)
		 *
		 * @param	value		the value of scale
		 */
		void setScale(float value);

		/* @LogLayer set shift
		 * @details y = base ^ (shift + scale * x), for base > 0.
		 *          Or if base is set to the default (-1), base is set to e,
		 *          so y = ln(shift + scale * x) = log_e(shift + scale * x)
		 *
		 * @param	value		the value of shift
		 */
		void setShift(float value);
				
		/* @LogLayer get base
		 * @details get base
		 *
		 * @return	float		the value of base
		 */
		float getBase();

		/* @LogLayer get scale
		 * @details get scale
		 *
		 * @return	float		the value of scale
		 */
		float getScale();

		/* @LogLayer get shift
		 * @details get shift
		 *
		 * @return	float		the value of shift
		 */
		float getShift();

		/* @LogLayer convert to caffe format
		 * @details convert current layer definition to caffe(.prototxt)
		 */
		string convet2CaffeFormat();
	};

        /* @class AbsValLayer
         * @basic class for AbsVal layer definition
         */
        class LAYERLIB_API AbsValLayer : public BaseLayer
        {
        public:

                /* @AbsValLayer constructor of AbsValLayer
                 * @details this class can help user to contruct own AbsVal layer
                 */
                AbsValLayer(string name);

                AbsValLayer();

                ~AbsValLayer();

                /* @AbsValLayer convert to caffe format
                 * @details convert current layer definition to caffe(.prototxt)
                 */
                string convet2CaffeFormat();
        };

        /* @class BNLLLayer
         * @basic class for BNLL layer definition
         */
        class LAYERLIB_API BNLLLayer : public BaseLayer
        {
        public:

                /* @BNLLLayer constructor of BNLLLayer
                 * @details this class can help user to contruct own AbsVal layer
                 */
                BNLLLayer(string name);

                BNLLLayer();

                ~BNLLLayer();

                /* @BNLLLayer convert to caffe format
                 * @details convert current layer definition to caffe(.prototxt)
                 */
                string convet2CaffeFormat();
        };
}

#endif //NEURONLAYERS
