#include "BaseLayer.h"
#include "CommonLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	EltwiseLayer::EltwiseLayer(string name)
	{
		mName = name;
		mType = MMALab::ELTWISE;		
		mParam = new EltwiseParam();
	}

	EltwiseLayer::EltwiseLayer()
	{
		mType = MMALab::ELTWISE;		
		mParam = new EltwiseParam();
	}

	EltwiseLayer::~EltwiseLayer()
	{
		
	}

	void EltwiseLayer::setOperation(EltwiseOp type)
	{
		((EltwiseParam*)mParam)->mOperation = type;
	}

	void EltwiseLayer::setCoeff(float value)
	{
		((EltwiseParam*)mParam)->mCoeff = value;
	}

	void EltwiseLayer::setStableProdGrad(bool state)
	{
		((EltwiseParam*)mParam)->mStableProdGrad = state;
	}

	EltwiseOp EltwiseLayer::getOperation()
	{
		return ((EltwiseParam*)mParam)->mOperation;
	}

	float EltwiseLayer::getCoeff()
	{
		return ((EltwiseParam*)mParam)->mCoeff;
	}

	bool EltwiseLayer::getStableProdGrad()
	{
		return ((EltwiseParam*)mParam)->mStableProdGrad;
	}

	string EltwiseLayer::convet2CaffeFormat()
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

		string eltwiseParamStrStart = "\teltwise_param\n\t{\n";
		string eltwiseParamStrEnd = "\t}\n";

		string operationStrStart = "\t\toperation: ";
		string operationStrEnd = "\n";

		string coeffStrStart = "\t\tcoeff: ";
		string coeffStrEnd = "\n";

		string stableProdGradStrStart = "\t\tstable_prod_grad: ";
		string stableProdGradStrEnd = "\n";

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
			     eltwiseParamStrStart   ;

                if(((EltwiseParam*)mParam)->mOperation != MMALab::ELTWISEOP_SUM)
		{
			switch (((EltwiseParam*)mParam)->mOperation)
			{
                        case MMALab::ELTWISEOP_PROD:
                                outStr += operationStrStart + "PROD" + operationStrEnd;
				break;
			case MMALab::ELTWISEOP_MAX:
				outStr += operationStrStart + "MAX" + operationStrEnd;
			}
		}
		outStr += coeffStrStart + to_string(getCoeff()) + coeffStrEnd;

		if(((EltwiseParam*)mParam)->mStableProdGrad != true)
		{
			outStr += stableProdGradStrStart + "false" + stableProdGradStrEnd;
		}
		outStr += eltwiseParamStrEnd ;

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
