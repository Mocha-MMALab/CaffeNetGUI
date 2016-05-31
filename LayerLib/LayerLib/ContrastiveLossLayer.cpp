#include "BaseLayer.h"
#include "LossLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	ContrastiveLossLayer::ContrastiveLossLayer(string name)
	{
		mName = name;
		mType = MMALab::CONTRASTIVE_LOSS;		
		mParam = new ContrastiveLossParam();
	}

	ContrastiveLossLayer::ContrastiveLossLayer()
	{
		mType = MMALab::CONTRASTIVE_LOSS;		
		mParam = new ContrastiveLossParam();
	}

	ContrastiveLossLayer::~ContrastiveLossLayer()
	{
		
	}

        void ContrastiveLossLayer::setMargin(float value)
	{
		((ContrastiveLossParam*)mParam)->mMargin = value;
	}

	void ContrastiveLossLayer::setLegacyVersion(bool state)
	{
		((ContrastiveLossParam*)mParam)->mLegacyVersion = state;
	}

        float ContrastiveLossLayer::getMargin()
	{
		return ((ContrastiveLossParam*)mParam)->mMargin;
	}

	bool ContrastiveLossLayer::getLegacyVersion()
	{
		return ((ContrastiveLossParam*)mParam)->mLegacyVersion;
	}

	string ContrastiveLossLayer::convet2CaffeFormat()
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

                string contrastivelossParamStrStart = "\tcontrastive_loss_param\n\t{\n";
		string contrastivelossParamStrEnd = "\t}\n";

		string marginStrStart = "\t\tmargin: ";
		string marginStrEnd = "\n";

		string legacyVersionStrStart = "\t\tlegacy_version: ";
		string legacyVersionStrEnd = "\n";

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
			     contrastivelossParamStrStart ;


		if(((ContrastiveLossParam*)mParam)->mMargin != 1)
		{
			outStr += marginStrStart + to_string(getMargin()) + marginStrEnd;
		}

		if(((ContrastiveLossParam*)mParam)->mLegacyVersion != false)
		{
			outStr += legacyVersionStrStart + "true" + legacyVersionStrEnd;
		}
		
		outStr += contrastivelossParamStrEnd;

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
