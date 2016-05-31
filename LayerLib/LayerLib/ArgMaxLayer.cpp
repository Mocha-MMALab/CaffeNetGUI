#include "BaseLayer.h"
#include "CommonLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	ArgMaxLayer::ArgMaxLayer(string name)
	{
		mName = name;
		mType = MMALab::ARGMAX;		
		mParam = new ArgMaxParam();
	}

	ArgMaxLayer::ArgMaxLayer()
	{
		mType = MMALab::ARGMAX;		
		mParam = new ArgMaxParam();
	}

	ArgMaxLayer::~ArgMaxLayer()
	{
		
	}

	void ArgMaxLayer::setOutMaxVal(bool state)
	{
		((ArgMaxParam*)mParam)->mOutMaxVal = state;
	}

        void ArgMaxLayer::setTopK(uint32 value)
	{
		((ArgMaxParam*)mParam)->mTopK = value;
	}	

        void ArgMaxLayer::setAxis(int value)
	{
		((ArgMaxParam*)mParam)->mAxis = value;
	}

	bool ArgMaxLayer::getOutMaxVal()
	{
		return ((ArgMaxParam*)mParam)->mOutMaxVal;
	}

        uint32 ArgMaxLayer::getTopK()
	{
		return ((ArgMaxParam*)mParam)->mTopK;
	}

        int ArgMaxLayer::getAxis()
	{
		return ((ArgMaxParam*)mParam)->mAxis;
	}

	string ArgMaxLayer::convet2CaffeFormat()
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

		string argMaxParamStrStart = "\targmax_param\n\t{\n";
		string argMaxParamStrEnd = "\t}\n";

		string outMaxValStrStart = "\t\tout_max_val: ";
		string outMaxValStrEnd = "\n";

		string topkStrStart = "\t\ttop_k: ";
		string topkStrEnd = "\n";

		string axisStrStart = "\t\taxis: ";
		string axisStrEnd = "\n";		

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
			     argMaxParamStrStart ;

		if(((ArgMaxParam*)mParam)->mOutMaxVal != false)
		{
			outStr +=  outMaxValStrStart + "true" + outMaxValStrEnd;
		}
		if(((ArgMaxParam*)mParam)->mTopK != 1)
		{
			outStr += topkStrStart + to_string(getTopK()) + topkStrEnd; 
		}
		if(((ArgMaxParam*)mParam)->mAxis != 0)
		{
			outStr += axisStrStart + to_string(getAxis()) + axisStrEnd; 
		}
		outStr += argMaxParamStrEnd;

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
