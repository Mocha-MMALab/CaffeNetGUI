#include "BaseLayer.h"
#include "DataLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	MemoryDataLayer::MemoryDataLayer(string name)
	{
		mName = name;
		mType = MMALab::MEMORY_DATA;		
		mParam = new MemoryDataParam();
	}

	MemoryDataLayer::MemoryDataLayer()
	{
		mType = MMALab::MEMORY_DATA;		
		mParam = new MemoryDataParam();
	}

	MemoryDataLayer::~MemoryDataLayer()
	{
		
	}

        void MemoryDataLayer::setBatchSize(uint32 value)
	{
		((MemoryDataParam*)mParam)->mBatchSize = value;
	}

        void MemoryDataLayer::setChannels(uint32 value)
	{
		((MemoryDataParam*)mParam)->mChannels = value;
	}

        void MemoryDataLayer::setHeight(uint32 value)
	{
		((MemoryDataParam*)mParam)->mHeight = value;
	}

        void MemoryDataLayer::setWidth(uint32 value)
	{
		((MemoryDataParam*)mParam)->mWidth = value;
	}

        uint32 MemoryDataLayer::getBatchSize()
	{
		return ((MemoryDataParam*)mParam)->mBatchSize;
	}

        uint32 MemoryDataLayer::getChannels()
	{
		return ((MemoryDataParam*)mParam)->mChannels;
	}

        uint32 MemoryDataLayer::getHeight()
	{
		return ((MemoryDataParam*)mParam)->mHeight;
	}

        uint32 MemoryDataLayer::getWidth()
	{
		return ((MemoryDataParam*)mParam)->mWidth;
	}

	string MemoryDataLayer::convet2CaffeFormat()
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

		string memoryDataParamStrStart = "\tmemory_data_param\n\t{\n";
		string memoryDataParamStrEnd = "\t}\n";

		string batchSizeStrStart = "\t\tbatch_size: ";
		string batchSizeEnd = "\n";

		string channelsStrStart = "\t\tchannels: ";
		string channelsEnd = "\n";

		string heightStrStart = "\t\theight: ";
		string heightEnd = "\n";

		string widthStrStart = "\t\twidth: ";
		string widthEnd = "\n";

		string phaseStrStart = "\tinclude:\n\t{\n";		
		string phaseStrEnd = "\t}\n";

		string phaseStateStrStart = "\t\tphase: ";
		string phaseStateStrEnd = "\n";

		string outStr = layerStrStart + 
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

		outStr = outStr + 
				 memoryDataParamStrStart + 
				 batchSizeStrStart + to_string(getBatchSize()) + batchSizeEnd +
				 channelsStrStart + to_string(getChannels()) + channelsEnd +
				 heightStrStart + to_string(getHeight()) + heightEnd +
				 widthStrStart + to_string(getWidth()) + widthEnd +
				 memoryDataParamStrEnd;

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
