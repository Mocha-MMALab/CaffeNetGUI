#include "BaseLayer.h"
#include "NeuronLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	ReLULayer::ReLULayer(string name)
	{
		mName = name;
		mType = MMALab::RELU;		
		mParam = new ReLUParam();
	}

	ReLULayer::ReLULayer()
	{
		mType = MMALab::RELU;		
		mParam = new ReLUParam();
	}

	ReLULayer::~ReLULayer()
	{
		
	}

	void ReLULayer::setNegativeSlope(float value)
	{
		((ReLUParam*)mParam)->mNegativeSlope = value;
	}

	void ReLULayer::setEngine(Engine value)
	{
		((ReLUParam*)mParam)->mEngine = value;
	}	

	float ReLULayer::getNegativeSlope()
	{
		return ((ReLUParam*)mParam)->mNegativeSlope;
	}

	Engine ReLULayer::getEngine()
	{
		return ((ReLUParam*)mParam)->mEngine;
	}	

	string ReLULayer::convet2CaffeFormat()
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

		string ReLUParamStrStart = "\trelu_param\n\t{\n";
		string ReLUParamStrEnd = "\t}\n";

		string negativeSlopeStrStart = "\t\tnegative_slope: ";
		string negativeSlopeStrEnd = "\n";

		string engineStrStart = "\t\tengine: ";
		string engineStrEnd = "\n";

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

		outStr = outStr + ReLUParamStrStart;

		if (getNegativeSlope() != 0)
		{
			outStr += negativeSlopeStrStart + to_string(getNegativeSlope()) + negativeSlopeStrEnd;
		}

		if (getEngine() != MMALab::DEFAULT)
		{
			switch (getEngine())
			{
			case MMALab::CAFFE:
				outStr += engineStrStart + "CAFFE" + engineStrEnd;
				break;

			case MMALab::CUDNN:
				outStr += engineStrStart + "CUDNN" + engineStrEnd;
				break;
			}			
		}	 

		outStr += ReLUParamStrEnd;

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