#include "BaseLayer.h"
#include "CommonLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	MVNLayer::MVNLayer(string name)
	{
		mName = name;
		mType = MMALab::MVN;		
		mParam = new MVNParam();
	}

	MVNLayer::MVNLayer()
	{
		mType = MMALab::MVN;		
		mParam = new MVNParam();
	}

	MVNLayer::~MVNLayer()
	{
		
	}

	void MVNLayer::setNormalizeVariance(bool state)
	{
		((MVNParam*)mParam)->mNormalizeVariance = state;
	}

	void MVNLayer::setAcrossChannels(bool state)
	{
		((MVNParam*)mParam)->mAcrossChannels = state;
	}

	void MVNLayer::setEps(float value)
	{
		((MVNParam*)mParam)->mEps = value;
	}

	bool MVNLayer::getNormalizeVariance()
	{
		return ((MVNParam*)mParam)->mNormalizeVariance;
	}

	bool MVNLayer::getAcrossChannels()
	{
		return ((MVNParam*)mParam)->mAcrossChannels;
	}

	float MVNLayer::getEps()
	{
		return (float)((MVNParam*)mParam)->mEps;
	}

	string MVNLayer::convet2CaffeFormat()
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

		string mvnParamStrStart = "\tmvn_param\n\t{\n";
		string mvnParamStrEnd = "\t}\n";

		string normalizeVarianceStrStart = "\t\tnormalize_variance: ";
		string normalizeVarianceStrEnd = "\n";

		string acrossChannelsStrStart = "\t\tacross_channels: ";
		string acrossChannelsStrEnd = "\n";

		string epsStrStart = "\t\teps: ";
		string epsStrEnd = "\n";

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
			     mvnParamStrStart;          
		if(((MVNParam*)mParam)->mNormalizeVariance != true)
		{
			outStr += normalizeVarianceStrStart + "false" + normalizeVarianceStrEnd;
		}

		if(((MVNParam*)mParam)->mAcrossChannels != false)
		{
			outStr += acrossChannelsStrStart + "true" + acrossChannelsStrEnd;
		}

		if(((MVNParam*)mParam)->mEps != 1e-9)				  
		{
			outStr += epsStrStart + to_string(getEps()) + epsStrEnd;
		}

		outStr +=  mvnParamStrEnd;
		
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