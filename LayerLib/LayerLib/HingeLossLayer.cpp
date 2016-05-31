#include "BaseLayer.h"
#include "LossLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	HingeLossLayer::HingeLossLayer(string name)
	{
		mName = name;
                mType = MMALab::HINGE_LOSS;
		mParam = new HingeLossParam();
	}

	HingeLossLayer::HingeLossLayer()
	{
                mType = MMALab::HINGE_LOSS;
		mParam = new HingeLossParam();
	}

	HingeLossLayer::~HingeLossLayer()
	{
		
	}

	void HingeLossLayer::setNorm(Norm norm)
	{
		((HingeLossParam*)mParam)->mNorm = norm;
	}

	Norm HingeLossLayer::getNorm()
	{
		return ((HingeLossParam*)mParam)->mNorm;
	}

	string HingeLossLayer::convet2CaffeFormat()
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

                string hingelossParamStrStart = "\thinge_loss_param\n\t{\n";
		string hingelossParamStrEnd = "\t}\n";

		string normStrStart = "\t\tnorm: ";
		string normStrEnd = "\n";

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
			     hingelossParamStrStart;

		if(((HingeLossParam*)mParam)->mNorm != MMALab::L1)
		{
			outStr += normStrStart + "L2" + normStrEnd;			
		}

		outStr += hingelossParamStrEnd;

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
