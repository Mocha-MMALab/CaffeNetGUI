#include "BaseLayer.h"
#include "NeuronLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	DropoutLayer::DropoutLayer(string name)
	{
		mName = name;
		mType = MMALab::DROPOUT;		
		mParam = new DropoutParam();
	}

	DropoutLayer::DropoutLayer()
	{
		mType = MMALab::DROPOUT;		
		mParam = new DropoutParam();
	}

	DropoutLayer::~DropoutLayer()
	{
		
	}

	void DropoutLayer::setDropoutRatio(float value)
	{
		((DropoutParam*)mParam)->mDropoutRatio = value;
	}	

	float DropoutLayer::getDropoutRatio()
	{
		return ((DropoutParam*)mParam)->mDropoutRatio;
	}	

	string DropoutLayer::convet2CaffeFormat()
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

		string dropoutParamStrStart = "\tdropout_param\n\t{\n";
		string dropoutParamStrEnd = "\t}\n";

		string dropoutRatioStrStart = "\t\tdropout_ratio: ";
		string dropoutRatioStrEnd = "\n";

		string phaseStrStart = "\tinclude:\n\t{\n";		
		string phaseStrEnd = "\t}\n";

		string phaseStateStrStart = "\t\tphase: ";
		string phaseStateStrEnd = "\n";


		string outStr = layerStrStart + 
						nameStrStart  + getLayerName() + nameStrEnd + 
						typeStrStart  + getLayerType() + typeStrEnd;

		for(size_t i = 0; i < mTops->size(); i++)
		{
			outStr = outStr + topStrStart + (*mTops)[i] + topStrEnd;
		}

		for(size_t i = 0; i < mBottoms->size(); i++)
		{
			outStr = outStr + bottomStrStart + (*mBottoms)[i] + bottomStrEnd;
		}

		outStr = outStr + dropoutParamStrStart;

		if (getDropoutRatio() != 0.5)
		{
			outStr += dropoutRatioStrStart + to_string(getDropoutRatio()) + dropoutRatioStrEnd;
		}				 

		outStr += dropoutParamStrEnd;

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