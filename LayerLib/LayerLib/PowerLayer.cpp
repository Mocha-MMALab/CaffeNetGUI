#include "BaseLayer.h"
#include "NeuronLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	PowerLayer::PowerLayer(string name)
	{
		mName = name;
		mType = MMALab::POWER;		
		mParam = new PowerParam();
	}

	PowerLayer::PowerLayer()
	{
		mType = MMALab::POWER;		
		mParam = new PowerParam();
	}

	PowerLayer::~PowerLayer()
	{
		
	}

	void PowerLayer::setPower(float value)
	{
		((PowerParam*)mParam)->mPower = value;
	}

	void PowerLayer::setScale(float value)
	{
		((PowerParam*)mParam)->mScale = value;
	}

	void PowerLayer::setShift(float value)
	{
		((PowerParam*)mParam)->mShift = value;
	}

	float PowerLayer::getPower()
	{
		return ((PowerParam*)mParam)->mPower;
	}

	float PowerLayer::getScale()
	{
		return ((PowerParam*)mParam)->mScale;
	}

	float PowerLayer::getShift()
	{
		return ((PowerParam*)mParam)->mShift;
	}

	string PowerLayer::convet2CaffeFormat()
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

		string powerParamStrStart = "\tpower_param\n\t{\n";
		string powerParamStrEnd = "\t}\n";

		string powerStrStart = "\t\tpower: ";
		string powerStrEnd = "\n";

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

		outStr = outStr + powerParamStrStart;

		if (getPower() != 1.0)
		{
			outStr += powerStrStart + to_string(getPower()) + powerStrEnd;
		}

		if (getScale() != 1.0)
		{
			outStr += scaleStrStart + to_string(getScale()) + scaleStrEnd;
		}

		if (getShift() != 0.0)
		{
			outStr += shiftStrStart + to_string(getShift()) + shiftStrEnd;
		}
				 
		outStr += powerParamStrEnd;

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