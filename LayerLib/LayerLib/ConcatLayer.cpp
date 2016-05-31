#include "BaseLayer.h"
#include "CommonLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	ConcatLayer::ConcatLayer(string name)
	{
		mName = name;
		mType = MMALab::CONCAT;		
		mParam = new ConcatParam();
	}

	ConcatLayer::ConcatLayer()
	{
		mType = MMALab::CONCAT;		
		mParam = new ConcatParam();
	}

	ConcatLayer::~ConcatLayer()
	{
		
	}

	void ConcatLayer::setAxis(int value)
	{
		((ConcatParam*)mParam)->mAxis = value;
	}

        void ConcatLayer::setConcatDim(uint32 value)
	{
		((ConcatParam*)mParam)->mConcatDim = value;
	}

	int ConcatLayer::getAxis()
	{
		return ((ConcatParam*)mParam)->mAxis;
	}

        uint32 ConcatLayer::getConcatDim()
	{
		return ((ConcatParam*)mParam)->mConcatDim;
	}

	string ConcatLayer::convet2CaffeFormat()
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

		string concatParamStrStart = "\tconcat_param\n\t{\n";
		string concatParamStrEnd = "\t}\n";

		string axisStrStart = "\t\taxis: ";
		string axisStrEnd = "\n";

		string concatDimStrStart = "\t\tconcat_dim: ";
		string concatDimStrEnd = "\n";

		string ignorelabelStrStart = "\t\tignore_label: ";
		string ignorelabelStrEnd = "\n";

		string phaseStrStart = "\tinclude:\n\t{\n";		
		string phaseStrEnd = "\t}\n";

		string phaseStateStrStart = "\t\tphase: ";
		string phaseStateStrEnd = "\n";

		string outStr = layerStrStart + 
						nameStrStart  + getLayerName()    + nameStrEnd + 
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
			     concatParamStrStart ;
		if(((ConcatParam*)mParam)->mAxis != 1)
		{
			outStr +=  axisStrStart + to_string(getAxis()) + axisStrEnd;
		}

		if(((ConcatParam*)mParam)->mConcatDim != -1)
		{
			outStr += concatDimStrStart + to_string(getConcatDim()) + concatDimStrEnd;
		}				 
		outStr += concatParamStrEnd;

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
