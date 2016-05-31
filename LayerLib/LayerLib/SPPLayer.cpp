#include "BaseLayer.h"
#include "VisionLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	SPPLayer::SPPLayer(string name)
	{
		mName = name;
		mType = MMALab::SPP;		
		mParam = new SPPParam();
	}

	SPPLayer::SPPLayer()
	{
		mType = MMALab::SPP;		
		mParam = new SPPParam();
	}

	SPPLayer::~SPPLayer()
	{
		
	}

        void SPPLayer::setPyramidHeight(uint32 value)
	{
		((SPPParam*)mParam)->mPyramidHeight = value;
	}

	void SPPLayer::setPool(PoolMethod type)
	{
		((SPPParam*)mParam)->mPool = type;
	}

	void SPPLayer::setEngine(Engine value)
	{
		((SPPParam*)mParam)->mEngine = value;
	}

        uint32 SPPLayer::getPyramidHeight()
	{
		return ((SPPParam*)mParam)->mPyramidHeight;
	}

	PoolMethod SPPLayer::getPool()
	{
		return ((SPPParam*)mParam)->mPool;
	}

	Engine SPPLayer::getEngine()
	{
		return ((SPPParam*)mParam)->mEngine;
	}

	string SPPLayer::convet2CaffeFormat()
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

		string SPPParamStrStart = "\tspp_param\n\t{\n";
		string SPPParamEnd = "\t}\n";

		string pyramidHeightStrStart = "\t\tpyramid_height:";
		string pyramidHeightStrEnd = "\n";

		string poolStrStart = "\t\tpool:";
		string poolStrEnd = "\n";

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

		outStr += SPPParamStrStart + 
			pyramidHeightStrStart + to_string(getPyramidHeight()) + pyramidHeightStrEnd;

		if (getPool() != MMALab::POOLMETHOD_MAX)
		{
			switch (getPool())
			{
			case MMALab::POOLMETHOD_AVE:
				outStr += poolStrStart + "AVE" + poolStrEnd;
				break;

			case MMALab::POOLMETHOD_STOCHASTIC:
				outStr += poolStrStart + "STOCHASTIC" + poolStrEnd;
				break;			
			}
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

		outStr += SPPParamEnd;
		
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
