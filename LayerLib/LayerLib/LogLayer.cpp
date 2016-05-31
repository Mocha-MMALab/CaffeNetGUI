#include "BaseLayer.h"
#include "NeuronLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	LogLayer::LogLayer(string name)
	{
		mName = name;
		mType = MMALab::LOG;		
		mParam = new LogParam();
	}

	LogLayer::LogLayer()
	{
		mType = MMALab::LOG;		
		mParam = new LogParam();
	}

	LogLayer::~LogLayer()
	{
		 
	}

	void LogLayer::setBase(float value)
	{
		((LogParam*)mParam)->mBase = value;
	}

	void LogLayer::setScale(float value)
	{
		((LogParam*)mParam)->mScale = value;
	}

	void LogLayer::setShift(float value)
	{
		((LogParam*)mParam)->mShift = value;
	}

	float LogLayer::getBase()
	{
		return ((LogParam*)mParam)->mBase;
	}

	float LogLayer::getScale()
	{
		return ((LogParam*)mParam)->mScale;
	}

	float LogLayer::getShift()
	{
		return ((LogParam*)mParam)->mShift;
	}

	string LogLayer::convet2CaffeFormat()
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

		string LogParamStrStart = "\tlog_param\n\t{\n";
		string LogParamStrEnd = "\t}\n";

		string baseStrStart = "\t\tbase: ";
		string baseStrEnd = "\n";

		string scaleStrStart = "\t\tscale: ";
		string scaleStrEnd = "\n";

		string shiftStrStart = "\t\tshift: ";
		string shiftStrEnd = "\n";

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

		outStr = outStr + LogParamStrStart;

		if (getBase() != -1.0)
		{
			outStr += baseStrStart + to_string(getBase())  + baseStrEnd;
		}

		if (getScale() != 1.0)
		{
			outStr += scaleStrStart + to_string(getScale()) + scaleStrEnd;
		}

		if (getShift() != 0.0)
		{
			outStr += shiftStrStart + to_string(getShift()) + shiftStrEnd;
		}

		outStr += LogParamStrEnd;

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