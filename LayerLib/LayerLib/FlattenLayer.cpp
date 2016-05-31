#include "BaseLayer.h"
#include "CommonLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	FlattenLayer::FlattenLayer(string name)
	{
		mName = name;
		mType = MMALab::FLATTEN;		
		mParam = new FlattenParam();
	}

	FlattenLayer::FlattenLayer()
	{
		mType = MMALab::FLATTEN;		
		mParam = new FlattenParam();
	}

	FlattenLayer::~FlattenLayer()
	{
		
	}

	void FlattenLayer::setAxis(int value)
	{
		((FlattenParam*)mParam)->mAxis = value;
	}

	void FlattenLayer::setEndAxis(int value)
	{
		((FlattenParam*)mParam)->mEndAxis = value;
	}

	int FlattenLayer::getAxis()
	{
		return ((FlattenParam*)mParam)->mAxis;
	}

	int FlattenLayer::getEndAxis()
	{
		return ((FlattenParam*)mParam)->mEndAxis;
	}

	string FlattenLayer::convet2CaffeFormat()
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

		string flattenParamStrStart = "\tflatten_param\n\t{\n";
		string flattenParamStrEnd = "\t}\n";

		string axisStrStart = "\t\taxis: ";
		string axisStrEnd = "\n";

		string endAxisStrStart = "\t\tend_axis: ";
		string endAxisStrEnd = "\n";		

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
			     flattenParamStrStart ;
		if(((FlattenParam*)mParam)->mAxis != 1)
		{
			outStr += axisStrStart + to_string(getAxis())    + axisStrEnd;
		}

		if(((FlattenParam*)mParam)->mEndAxis != -1)
		{
			outStr += endAxisStrStart + to_string(getEndAxis()) + endAxisStrEnd;
		}
		outStr += flattenParamStrEnd;

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
