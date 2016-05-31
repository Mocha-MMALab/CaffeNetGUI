#include "BaseLayer.h"
#include "DataLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	HDF5OutputLayer::HDF5OutputLayer(string name)
	{
		mName = name;
		mType = MMALab::HDF5_OUTPUT;		
		mParam = new HDF5OutputParam();
	}

	HDF5OutputLayer::HDF5OutputLayer()
	{
		mType = MMALab::HDF5_OUTPUT;		
		mParam = new HDF5OutputParam();
	}

	HDF5OutputLayer::~HDF5OutputLayer()
	{
		
	}

	void HDF5OutputLayer::setFileName(string value)
	{
		((HDF5OutputParam*)mParam)->mFileName = value;
	}

	string HDF5OutputLayer::getFileName()
	{
		return ((HDF5OutputParam*)mParam)->mFileName;
	}

	string HDF5OutputLayer::convet2CaffeFormat()
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

		string HDF5OutputParamStrStart = "\thdf5_output_param\n\t{\n";
		string HDF5OutputParamStrEnd = "\t}\n";

		string FileNameStrStart = "\t\tfile_name:";
		string FileNameStrEnd = "\n";

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

		outStr = outStr + HDF5OutputParamStrStart;

		if (getFileName() == "")
		{

		}
		else
		{
			outStr = outStr + FileNameStrStart + "\"" + getFileName() + "\"" + FileNameStrEnd;
		}

		outStr = outStr + HDF5OutputParamStrEnd;

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

	
