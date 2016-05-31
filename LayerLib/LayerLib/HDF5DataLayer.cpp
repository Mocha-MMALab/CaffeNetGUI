#include "BaseLayer.h"
#include "DataLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	HDF5DataLayer::HDF5DataLayer(string name)
	{
		mName = name;
		mType = MMALab::HDF5_DATA;
		
		mParam = new HDF5DataParam();
	}

	HDF5DataLayer::HDF5DataLayer()
	{
		mType = MMALab::HDF5_DATA;
		
		mParam = new HDF5DataParam();
	}

	HDF5DataLayer::~HDF5DataLayer()
	{
		
	}

	void HDF5DataLayer::setSource(string value)
	{
		((HDF5DataParam*)mParam)->mSource = value;
	}

        void HDF5DataLayer::setBatchSize(uint32 value)
	{
		((HDF5DataParam*)mParam)->mBatchSize = value;
	}

	void HDF5DataLayer::setShuffle(bool value)
	{
		((HDF5DataParam*)mParam)->mShuffle = value;
	}

	string HDF5DataLayer::getSource()
	{
		return ((HDF5DataParam*)mParam)->mSource;
	}

        uint32 HDF5DataLayer::getBatchSize()
	{
		return ((HDF5DataParam*)mParam)->mBatchSize;
	}

	bool HDF5DataLayer::getShuffle()
	{
		return ((HDF5DataParam*)mParam)->mShuffle;
	}

	string HDF5DataLayer::convet2CaffeFormat()
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

		string HDF5DataParamStrStart = "\thdf5_data_param\n\t{\n";
		string HDF5DataParamStrEnd = "\t}\n";

		string SourceStrStart = "\t\tsource: ";
		string SourceStrEnd = "\n";

		string BatchSizeStrStart = "\t\tbatch_size: ";
		string BatchSizeStrEnd = "\n";

		string ShuffleStrStart = "\t\tshuffle: ";
		string ShuffleStrEnd = "\n";

		string phaseStrStart = "\tinclude:\n\t{\n";		
		string phaseStrEnd = "\t}\n";

		string phaseStateStrStart = "\t\tphase: ";
		string phaseStateStrEnd = "\n";

		string outStr =  layerStrStart + 
						 nameStrStart + mName + nameStrEnd + 
						 typeStrStart + getLayerType() + typeStrEnd;

		for(size_t i = 0; i < mTops->size(); i++)
		{
			outStr = outStr + topStrStart + (*mTops)[i] + topStrEnd;
		}

		for(size_t i = 0; i < mBottoms->size(); i++)
		{
			outStr = outStr + bottomStrStart + (*mBottoms)[i] +bottomStrEnd;
		}

		outStr += HDF5DataParamStrStart;

		if (getSource() == "")
		{

		}
		else
		{
			outStr += SourceStrStart + "\"" + getSource() + "\"" + SourceStrEnd;
		}

		outStr += BatchSizeStrStart + to_string(getBatchSize()) + BatchSizeStrEnd;

		if(((HDF5DataParam*)mParam)->mShuffle != false)
		{
			outStr += ShuffleStrStart + "true" + ShuffleStrEnd;
		}

		outStr += HDF5DataParamStrEnd;

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
