#include "BaseLayer.h"
#include "NeuronLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	ExpLayer::ExpLayer(string name)
	{
		mName = name;
		mType = MMALab::EXP;		
		mParam = new ExpParam();
	}

	ExpLayer::ExpLayer()
	{
		mType = MMALab::EXP;		
		mParam = new ExpParam();
	}

	ExpLayer::~ExpLayer()
	{
		
	}

	void ExpLayer::setBase(float value)
	{
		((ExpParam*)mParam)->mBase = value;
	}

	void ExpLayer::setScale(float value)
	{
		((ExpParam*)mParam)->mScale = value;
	}

	void ExpLayer::setShift(float value)
	{
		((ExpParam*)mParam)->mShift = value;
	}

	float ExpLayer::getBase()
	{
		return ((ExpParam*)mParam)->mBase;
	}

	float ExpLayer::getScale()
	{
		return ((ExpParam*)mParam)->mScale;
	}

	float ExpLayer::getShift()
	{
		return ((ExpParam*)mParam)->mShift;
	}

	string ExpLayer::convet2CaffeFormat()
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

		string expParamStrStart = "\texp_param\n\t{\n";
		string expParamStrEnd = "\t}\n";

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

		outStr = outStr + expParamStrStart;

		if (getBase() != -1.0)
		{
			outStr += baseStrStart + to_string(getBase()) + baseStrEnd;
		}

		if (getScale() != 1.0)
		{
			outStr += scaleStrStart + to_string(getScale()) + scaleStrEnd;
		}

		if (getShift() != 0.0)
		{
			outStr += shiftStrStart + to_string(getShift()) + shiftStrEnd;
		}
				 
		outStr += expParamStrEnd;

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