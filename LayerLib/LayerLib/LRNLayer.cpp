#include "BaseLayer.h"
#include "VisionLayers.h"
#include <limits>

using namespace std;
using namespace MMALab;

namespace MMALab
{
	LRNLayer::LRNLayer(string name)
	{
		mName = name;
		mType = MMALab::LRN;		
		mParam = new LRNParam(); 
	}
	LRNLayer::LRNLayer()
	{
		mType = MMALab::LRN;		
		mParam = new LRNParam(); 
	}

	LRNLayer::~LRNLayer()
	{
		
	}
	
        void LRNLayer::setLocalSize(uint32 value)
	{
		((LRNParam*)mParam)->mLocalSize = value;
	}

	void LRNLayer::setAlpha(float value)
	{
		((LRNParam*)mParam)->mAlpha = value;
	}

	void LRNLayer::setBeta(float value)
	{
		((LRNParam*)mParam)->mBeta = value;
	}

	void LRNLayer::setNormRegion(NormRegion type)
	{
		((LRNParam*)mParam)->mNormRegion = type;
	}

	void LRNLayer::setK(float value)
	{
		((LRNParam*)mParam)->mK = value;
	}

        void LRNLayer::setEngine(Engine value)
        {
                ((LRNParam*)mParam)->mEngine = value;
        }

        uint32 LRNLayer::getLocalSize()
	{
		return ((LRNParam*)mParam)->mLocalSize;
	}

	float LRNLayer::getAlpha()
	{
		return ((LRNParam*)mParam)->mAlpha;
	}

	float LRNLayer::getBeta()
	{
		return ((LRNParam*)mParam)->mBeta;
	}

	NormRegion LRNLayer::getNormRegion()
	{
		return ((LRNParam*)mParam)->mNormRegion;
	}

	float LRNLayer::getK()
	{
		return ((LRNParam*)mParam)->mK;
	}

	Engine LRNLayer::getEngine()
	{
		return ((LRNParam*)mParam)->mEngine;
	}

	string LRNLayer::convet2CaffeFormat()
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

		string LRNParamStrStart = "\tlrn_param\n\t{\n";
		string LRNParamStrEnd = "\t}\n";

		string localSizeStrStart = "\t\tlocal_size: ";
		string localSizeStrEnd = "\n";

		string alphaStrStart = "\t\talpha: ";
		string alphaStrEnd = "\n";

		string betaStrStart = "\t\tbeta: ";
		string betaStrEnd = "\n";
		
		string normRegionStrStart = "\t\tnorm_region: ";
		string normRegionStrEnd = "\n";

		string kStrStart = "\t\tk: ";
		string kStrEnd = "\n";

                string engineStrStart = "\t\tengine:";
                string engineStrEnd = "\n";

		string phaseStrStart = "\tinclude:\n\t{\n";		
		string phaseStrEnd = "\t}\n";

		string phaseStateStrStart = "\t\tphase: ";
		string phaseStateStrEnd = "\n";

		string outStr = layerStrStart+
						nameStrStart + mName + nameStrEnd + 
						typeStrStart + getLayerType() + typeStrEnd;

		for(size_t i = 0; i < mTops->size(); i++)
		{
			outStr = outStr + topStrStart + (*mTops)[i] + topStrEnd;
		}

		for(size_t i = 0; i < mBottoms->size(); i++)
		{
			outStr = outStr + bottomStrStart + (*mBottoms)[i] + bottomStrEnd;
		}

		outStr += LRNParamStrStart;

		if (getLocalSize() != 5)
		{
			outStr += localSizeStrStart + to_string(getLocalSize()) + localSizeStrEnd;
		}

		if (getAlpha() != 1.0)
		{
			outStr += alphaStrStart + to_string(getAlpha()) + alphaStrEnd;
		}

		if (getBeta() != 0.75)
		{
			outStr += betaStrStart + to_string(getBeta()) + betaStrEnd;
		}

		if (getNormRegion() != MMALab::ACROSS_CHANNELS)
		{
			outStr += normRegionStrStart + "WITHIN_CHANNEL" + normRegionStrEnd;
		}

		if (getK() != 1.0)
		{
			outStr += kStrStart + to_string(getK()) + kStrEnd;
		}

                if (getEngine() != MMALab::DEFAULT)
                {
                        switch (getEngine())
                        {
                        case MMALab::CAFFE:
                                outStr += engineStrStart + "CAFFE" + engineStrEnd;
                                break;

                        case MMALab::CUDNN:
                                outStr += engineStrStart + "CUDNN" + engineStrEnd;
                                break;
                        }
                }

		outStr += LRNParamStrEnd;

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
