#include "BaseLayer.h"
#include "LossLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	AccuracyLayer::AccuracyLayer(string name) 
	{
		mName = name;
		mType = MMALab::ACCURACY;		
		mParam = new AccuracyParam();
	}

	AccuracyLayer::AccuracyLayer()
	{
		mType = MMALab::ACCURACY;
		mParam = new AccuracyParam();
	}

	AccuracyLayer::~AccuracyLayer()
	{
		
	}

        void AccuracyLayer::setTopK(uint32 value)
	{
		((AccuracyParam*)mParam)->mTopk = value;
	}

	void AccuracyLayer::setAxis(int value)
	{
		((AccuracyParam*)mParam)->mAxis = value;
	}

	void AccuracyLayer::setIgnoreLabel(int value)
	{
		((AccuracyParam*)mParam)->mIgnoreLabel = value;
	}

        uint32 AccuracyLayer::getTopK()
	{
		return ((AccuracyParam*)mParam)->mTopk;
	}

	int AccuracyLayer::getAxis()
	{
		return ((AccuracyParam*)mParam)->mAxis;
	}

	int AccuracyLayer::getIgnoreLabel()
	{
		return ((AccuracyParam*)mParam)->mIgnoreLabel;
	}

	string AccuracyLayer::convet2CaffeFormat()
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

		string accuracyParamStrStart = "\taccuracy_param\n\t{\n";
		string accuracyParamStrEnd = "\t}\n";

		string topkStrStart = "\t\ttop_k: ";
		string topkStrEnd = "\n";

		string axisStrStart = "\t\taxis: ";
		string axisStrEnd = "\n";

		string ignorelabelStrStart = "\t\tignore_label: ";
		string ignorelabelStrEnd = "\n";

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

		outStr = outStr + 
			     accuracyParamStrStart ;
		if(((AccuracyParam*)mParam)->mTopk != 1)
		{
			outStr += topkStrStart + to_string(getTopK()) + topkStrEnd;
		}
				  
		if(((AccuracyParam*)mParam)->mAxis != 1)
		{
			outStr += axisStrStart + to_string(getAxis()) + axisStrEnd;
		}		

		outStr += ignorelabelStrStart + to_string(getIgnoreLabel()) + ignorelabelStrEnd +
				  accuracyParamStrEnd; 
		
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
