#include "BaseLayer.h"
#include "NeuronLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	SigmoidLayer::SigmoidLayer(string name)
	{
		mName = name;
		mType = MMALab::SIGMOID;		
		mParam = new SigmoidParam();
	}

	SigmoidLayer::SigmoidLayer()
	{
		mType = MMALab::SIGMOID;		
		mParam = new SigmoidParam();
	}

	SigmoidLayer::~SigmoidLayer()
	{
		
	}

	void SigmoidLayer::setEngine(Engine value)
	{
		((SigmoidParam*)mParam)->mEngine = value;
	}	

	Engine SigmoidLayer::getEngine()
	{
		return ((SigmoidParam*)mParam)->mEngine;
	}	

	string SigmoidLayer::convet2CaffeFormat()
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

		string sigmoidParamStrStart = "\tsigmoid_param\n\t{\n";
		string sigmoidParamStrEnd = "\t}\n";

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

		outStr = outStr + sigmoidParamStrStart;

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

		outStr += sigmoidParamStrEnd;

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