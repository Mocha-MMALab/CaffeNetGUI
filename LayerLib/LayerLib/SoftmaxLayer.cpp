#include "BaseLayer.h"
#include "CommonLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	SoftmaxLayer::SoftmaxLayer(string name)
	{
		mName = name;
		mType = MMALab::SOFTMAX;		
		mParam = new SoftmaxParam();
	}

	SoftmaxLayer::SoftmaxLayer()
	{
		mType = MMALab::SOFTMAX;		
		mParam = new SoftmaxParam();
	}

	SoftmaxLayer::~SoftmaxLayer()
	{
		
	}

	void SoftmaxLayer::setEngine(Engine type)
	{
		((SoftmaxParam*)mParam)->mEngine = type;
	}

	void SoftmaxLayer::setAxis(int value)
	{
		((SoftmaxParam*)mParam)->mAxis = value;
	}
	
	Engine SoftmaxLayer::getEngine()
	{
		return ((SoftmaxParam*)mParam)->mEngine;
	}

	int SoftmaxLayer::getAxis()
	{
		return ((SoftmaxParam*)mParam)->mAxis;
	}

	string SoftmaxLayer::convet2CaffeFormat()
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

		string SoftmaxParamStrStart = "\tsoftmax_param\n\t{\n";
		string SoftmaxParamStrEnd = "\t}\n";

                string engineStrStart = "\t\tengine: ";
		string engineStrEnd = "\n";

		string axisStrStart = "\t\taxis: ";
		string axisStrEnd = "\n";

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

		outStr = outStr + 
			     SoftmaxParamStrStart ;

		if(((SoftmaxParam*)mParam)->mEngine != MMALab::DEFAULT)
		{
			switch (((SoftmaxParam*)mParam)->mEngine)
			{			
			case MMALab::CAFFE:
				outStr += engineStrStart+ "CAFFE" + engineStrEnd;			
				break;
			case MMALab::CUDNN:
				outStr += engineStrStart+ "CUDNN" + engineStrEnd;
			}
		}
                if(((SoftmaxParam*)mParam)->mAxis != 1)
		{
			outStr += axisStrStart + to_string(getAxis()) + axisStrEnd;
		}

		outStr += SoftmaxParamStrEnd;

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
