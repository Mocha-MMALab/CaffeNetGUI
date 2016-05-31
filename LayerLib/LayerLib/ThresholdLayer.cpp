#include "BaseLayer.h"
#include "NeuronLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	ThresholdLayer::ThresholdLayer(string name)
	{
		mName = name;
		mType = MMALab::THRESHOLD;		
		mParam = new ThresholdParam();
	}

	ThresholdLayer::ThresholdLayer()
	{
		mType = MMALab::THRESHOLD;		
		mParam = new ThresholdParam();
	}

	ThresholdLayer::~ThresholdLayer()
	{
		
	}

	void ThresholdLayer::setThreshold(float value)
	{
		((ThresholdParam*)mParam)->mThreshold = value;
	}	

	float ThresholdLayer::getThreshold()
	{
		return ((ThresholdParam*)mParam)->mThreshold;
	}	

	string ThresholdLayer::convet2CaffeFormat()
	{
		string layerStrStart = "layer\n{\n";
		string layerStrEnd = "}";

		string nameStrStart = "\tname: \"";
		string nameStrEnd = "\"\n";

		string typeStrStart = "\ttype: \"";
		string typeStrEnd = "\"\n";

		string topStrStart = "\ttop: \"";
		string topStrEnd = "\"\n";

		string bottomStrStart = "\tbottom: \"";
		string bottomStrEnd = "\"\n";

		string thresholdParamStrStart = "\tthreshold_param\n\t{\n";
		string thresholdParamStrEnd = "\t}\n";

		string thresholdStrStart = "\t\tthreshold: ";
		string thresholdStrEnd = "\n";

		string phaseStrStart = "\tinclude:\n\t{\n";		
		string phaseStrEnd = "\t}\n";

		string phaseStateStrStart = "\t\tphase: ";
		string phaseStateStrEnd = "\n";

		string outStr = layerStrStart + 
						nameStrStart  + mName         + nameStrEnd + 
						typeStrStart  + getLayerType() + typeStrEnd;

		for(size_t i = 0; i < mTops->size(); i++)
		{
			outStr = outStr + topStrStart + (*mTops)[i] + topStrEnd;
		}

		for(size_t i = 0; i < mBottoms->size(); i++)
		{
			outStr = outStr + bottomStrStart + (*mBottoms)[i] + bottomStrEnd;
		}

		outStr = outStr + thresholdParamStrStart;

		if (getThreshold() != 0)
		{
			outStr += thresholdStrStart + to_string(getThreshold()) + thresholdStrEnd;
		}

		outStr += thresholdParamStrEnd;

		if (mPhase != Phase::BOTH)
		{
			outStr += phaseStrStart + phaseStateStrStart;

			if (mPhase == Phase::TRAIN)
			{
				outStr += "TRAIN";
			}
			else if (mPhase == Phase::TEST)
			{
				outStr += "TEST";
			}

			outStr += phaseStateStrEnd + phaseStrEnd;
		}
		
		outStr += layerStrEnd;

		return outStr;
	}
}