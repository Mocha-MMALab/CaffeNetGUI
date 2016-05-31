#include "BaseLayer.h"
#include "CommonLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	ReductionLayer::ReductionLayer(string name)
	{
		mName = name;
		mType = MMALab::REDUCTION;		
		mParam = new ReductionParam();
	}

	ReductionLayer::ReductionLayer()
	{
		mType = MMALab::REDUCTION;		
		mParam = new ReductionParam();
	}

	ReductionLayer::~ReductionLayer()
	{
		 
	}

	void ReductionLayer::setOperation(ReductionOp type)
	{
		((ReductionParam*)mParam)->mOperation = type;
	}

	void ReductionLayer::setAxis(int value)
	{
		((ReductionParam*)mParam)->mAxis = value;
	}

	void ReductionLayer::setCoeff(float value)
	{
		((ReductionParam*)mParam)->mCoeff = value;
	}

	ReductionOp ReductionLayer::getOperation()
	{
		return ((ReductionParam*)mParam)->mOperation;
	}

	int ReductionLayer::getAxis()
	{
		return ((ReductionParam*)mParam)->mAxis;
	}

	float ReductionLayer::getCoeff()
	{
		return ((ReductionParam*)mParam)->mCoeff;
	}

	string ReductionLayer::convet2CaffeFormat()
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

		string reductionParamStrStart = "\treduction_param\n\t{\n";
		string reductionParamStrEnd = "\t}\n";

		string operationStrStart = "\t\toperation: ";
		string operationStrEnd = "\n";

		string axisStrStart = "\t\taxis: ";
		string axisStrEnd = "\n";

		string coeffStrStart = "\t\tcoeff: ";
		string coeffStrEnd = "\n";

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
			     reductionParamStrStart ;

		if(((ReductionParam*)mParam)->mOperation != MMALab::REDUCTIONOP_SUM)
		{
			switch (((ReductionParam*)mParam)->mOperation)
			{
			case MMALab::REDUCTIONOP_ASUM:
				outStr += operationStrStart + "ASUM" + operationStrEnd;
				break;
			case MMALab::REDUCTIONOP_SUMSQ:
				outStr += operationStrStart + "SUMSQ" + operationStrEnd;
				break;
			case MMALab::REDUCTIONOP_MEAN:
				outStr += operationStrStart + "MEAN" + operationStrEnd;
				break;
			}
		}

		if(((ReductionParam*)mParam)->mAxis != 0)
		{
			outStr += axisStrStart + to_string(getAxis()) + axisStrEnd;
		}

		if(((ReductionParam*)mParam)->mCoeff != 1.0)
		{
			outStr +=  coeffStrStart + to_string(getCoeff()) + coeffStrEnd; 
		}
				  
		outStr	+= reductionParamStrEnd;

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
