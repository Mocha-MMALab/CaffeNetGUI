#include "BaseLayer.h"
#include "DataLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	DataLayer::DataLayer(string name)
	{
		mName = name;
		mType = MMALab::DATA;		
		mParam = new DataParam();
	}

	DataLayer::DataLayer()
	{
		mType = MMALab::DATA;		
		mParam = new DataParam();
	}

	DataLayer::~DataLayer()
	{
		
	}

	void DataLayer::setSource(string value)
	{
		((DataParam*)mParam)->mSource = value;
	}

        void DataLayer::setBatchSize(uint32 value)
	{
		((DataParam*)mParam)->mBatchSize = value;
	}

        void DataLayer::setRandSkip(uint32 value)
	{
		((DataParam*)mParam)->mRandSkip = value;
	}

	void DataLayer::setBackend(DB type)
	{
		((DataParam*)mParam)->mBackend = type;
	}

	void DataLayer::setScale(float value)
	{
		((DataParam*)mParam)->mScale = value;
	}

	void DataLayer::setMeanfile(string value)
	{
		((DataParam*)mParam)->mMeanfile = value;
	}

        void DataLayer::setCropsize(uint32 value)
	{
		((DataParam*)mParam)->mCropsize = value;
	}

	void DataLayer::setMirror(bool value)
	{
		((DataParam*)mParam)->mMirror = value;
	}

	void DataLayer::setForceEncodedcolor(bool value)
	{
		((DataParam*)mParam)->mForceEncodedcolor = value;
	}

        void DataLayer::setPrefetch(uint32 value)
        {
                ((DataParam*)mParam)->mPrefetch = value;
        }

	string DataLayer::getSource()
	{
		return ((DataParam*)mParam)->mSource;
	}

        uint32 DataLayer::getBatchSize()
	{
		return ((DataParam*)mParam)->mBatchSize;
	}

        uint32 DataLayer::getRandSkip()
	{
		return ((DataParam*)mParam)->mRandSkip;
	}

	DB DataLayer::getBackend()
	{
		return ((DataParam*)mParam)->mBackend;
	}

	float DataLayer::getScale()
	{
		return ((DataParam*)mParam)->mScale;
	}

	string DataLayer::getMeanfile()
	{
		return ((DataParam*)mParam)->mMeanfile;
	}

        uint32 DataLayer::getCropsize()
	{
		return ((DataParam*)mParam)->mCropsize;
	}

	bool DataLayer::getMirror()
	{
		return ((DataParam*)mParam)->mMirror;
	}
	
	bool DataLayer::getForceEncodedcolor()
	{
		return ((DataParam*)mParam)->mForceEncodedcolor;
	}

        uint32 DataLayer::getPrefetch()
        {
                return ((DataParam*)mParam)->mPrefetch;
        }

	string DataLayer::convet2CaffeFormat()
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

		string dataParamStrStart = "\tdata_param\n\t{\n";
		string dataParamStrEnd ="\t}\n";

		string SourceStrStart = "\t\tsource: ";
		string SourceStrEnd = "\n";

		string batchSizeStrStart = "\t\tbatch_size: ";
		string batchSizeStrEnd = "\n";

		string randSkipStrStart = "\t\trand_skip: ";
		string randSkipStrEnd = "\n";

		string backendStrStart = "\t\tbackend: ";
		string backendStrEnd = "\n";

		string ScaleStrStart = "\t\tscale: ";
		string ScaleStrEnd = "\n";

		string MeanFileStrStart = "\t\tmean_file: ";
		string MeanFileStrEnd = "\n";

		string CropSizeStrStart = "\t\tcrop_size: ";
		string CropSizeStrEnd = "\n";

		string MirrorStrStart = "\t\tmirror: ";
		string MirrorStrEnd = "\n";

		string ForceEncodeColorStrStart = "\t\tforce_encoded_color: ";
		string ForceEncodeColorStrEnd = "\n";

                string PrefetchStrStart =  "\t\tprefetch: ";
                string PrefetchStrEnd = "\n";

		string phaseStrStart = "\tinclude:\n\t{\n";		
		string phaseStrEnd = "\t}\n";

		string phaseStateStrStart = "\t\tphase: ";
		string phaseStateStrEnd = "\n";

		string outStr =  layerStrStart + 
						 nameStrStart + getLayerName() + nameStrEnd + 
						 typeStrStart + getLayerType() + typeStrEnd;

		for(size_t i = 0; i < mTops->size(); i++)
		{
			outStr = outStr + topStrStart + (*mTops)[i] + topStrEnd;
		}

		for(size_t i = 0; i < mBottoms->size(); i++)
		{
			outStr = outStr + bottomStrStart + (*mBottoms)[i] +bottomStrEnd;
		}

		outStr += dataParamStrStart;

		if (getSource() == "")
		{

		}
		else
		{
			outStr += SourceStrStart + "\"" + getSource() + "\"" + SourceStrEnd;
		}

		outStr +=batchSizeStrStart + to_string(getBatchSize()) + batchSizeStrEnd;

		if(((DataParam*)mParam)->mRandSkip != 0)
		{
			outStr += randSkipStrStart + to_string(getRandSkip()) + randSkipStrEnd;
		}

		if(((DataParam*)mParam)->mBackend != DB::LEVELDB)
		{
			switch (((DataParam*)mParam)->mBackend)
			{
			case DB::LEVELDB:
					outStr += backendStrStart + "LEVELDB" + backendStrEnd;
					break;

			case DB::LMDB:
					outStr += backendStrStart + "LMDB" + backendStrEnd;
					break;
			}
		}

		if(((DataParam*)mParam)->mScale != 1)
		{
			outStr += ScaleStrStart + to_string(getScale()) + ScaleStrEnd;
		}

		if (getMeanfile() == "")
		{

		}
		else
		{
			outStr += MeanFileStrStart + "\"" + getMeanfile() + "\"" + MeanFileStrEnd;
		}		

		if(((DataParam*)mParam)->mCropsize != 0)
		{
			outStr += CropSizeStrStart + to_string(getCropsize()) + CropSizeStrEnd;
		}

		if(((DataParam*)mParam)->mMirror != false)
		{
			outStr += MirrorStrStart + "true" + MirrorStrEnd;
		}

		if(((DataParam*)mParam)->mForceEncodedcolor != false)
		{
			outStr += ForceEncodeColorStrStart + "true" + ForceEncodeColorStrEnd;
		}

                if(((DataParam*)mParam)->mPrefetch != 4)
                {
                        outStr += PrefetchStrStart + to_string(getPrefetch())  + PrefetchStrEnd;
                }

		outStr += dataParamStrEnd;

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
