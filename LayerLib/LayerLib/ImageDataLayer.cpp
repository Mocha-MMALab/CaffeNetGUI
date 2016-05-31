#include "BaseLayer.h"
#include "DataLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	ImageDataLayer::ImageDataLayer(string name)
	{
		mName = name;
		mType = MMALab::IMAGE_DATA;		
		mParam = new ImageDataParam();
	}

	ImageDataLayer::ImageDataLayer()
	{
		mType = MMALab::IMAGE_DATA;		
		mParam = new ImageDataParam();
	}

	ImageDataLayer::~ImageDataLayer()
	{
		
	}

	void ImageDataLayer::setSource(string value)
	{
		((ImageDataParam*)mParam)->mSource = value;
	}

        void ImageDataLayer::setBatchSize(uint32 value)
	{
		((ImageDataParam*)mParam)->mBatchSize = value;
	}

        void ImageDataLayer::setRandSkip(uint32 value)
	{
		((ImageDataParam*)mParam)->mRandSkip = value;
	}

	void ImageDataLayer::setShuffle(bool value)
	{
                ((ImageDataParam*)mParam)->mShuffle = value;
	}

        void ImageDataLayer::setNewHeight(uint32 value)
	{
		((ImageDataParam*)mParam)->mNewHeight = value;
	}

        void ImageDataLayer::setNewWidth(uint32 value)
	{
		((ImageDataParam*)mParam)->mNewWidth = value;
	}

	void ImageDataLayer::setIsColor(bool value)
	{
		((ImageDataParam*)mParam)->mIsColor = value;
	}

	void ImageDataLayer::setScale(float value)
	{
		((ImageDataParam*)mParam)->mScale = value;
	}

	void ImageDataLayer::setMeanFile(string value)
	{
		((ImageDataParam*)mParam)->mMeanFile = value;
	}

        void ImageDataLayer::setCropSize(uint32 value)
	{
		((ImageDataParam*)mParam)->mCropSize = value;
	}

	void ImageDataLayer::setMirror(bool value)
	{
		((ImageDataParam*)mParam)->mMirror = value;
	}

	void ImageDataLayer::setRootFolder(string value)
	{
		((ImageDataParam*)mParam)->mRootFolder = value;
	}

	string ImageDataLayer::getSource()
	{
		return ((ImageDataParam*)mParam)->mSource;
	}

        uint32 ImageDataLayer::getBatchSize()
	{
		return ((ImageDataParam*)mParam)->mBatchSize;
	}

        uint32 ImageDataLayer::getRandSkip()
	{
		return ((ImageDataParam*)mParam)->mRandSkip;
	}

        bool ImageDataLayer::getShuffle()
	{
		return ((ImageDataParam*)mParam)->mShuffle;
	}

        uint32 ImageDataLayer::getNewHeight()
	{
		return ((ImageDataParam*)mParam)->mNewHeight;
	}

        uint32 ImageDataLayer::getNewWidth()
	{
		return ((ImageDataParam*)mParam)->mNewWidth;
	}

	bool ImageDataLayer::getIsColor()
	{
		return ((ImageDataParam*)mParam)->mIsColor;
	}

	float ImageDataLayer::getScale()
	{
		return ((ImageDataParam*)mParam)->mScale;
	}

	string ImageDataLayer::getMeanFile()
	{
		return ((ImageDataParam*)mParam)->mMeanFile;
	}

        uint32 ImageDataLayer::getCropSize()
	{
		return ((ImageDataParam*)mParam)->mCropSize;
	}

	bool ImageDataLayer::getMirror()
	{
		return ((ImageDataParam*)mParam)->mMirror;
	}

	string ImageDataLayer::getRootFolder()
	{
		return ((ImageDataParam*)mParam)->mRootFolder;
	}

	string ImageDataLayer::convet2CaffeFormat()
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

		string ImagedataParamStrStart = "\timage_data_param\n\t{\n";
		string ImagedataParamStrEnd ="\t}\n";

		string SourceSrtStart = "\t\tsource: ";
		string SourceSrtEnd = "\n";

		string batchSizeStrStart = "\t\tbatch_size: ";
		string batchSizeStrEnd = "\n";

		string randSkipStrStart = "\t\trand_skip: ";
		string randSkipStrEnd = "\n";

		string ShuffleStrStart = "\t\tshuffle: ";
		string ShuffleStrEnd = "\n";

		string NewHeightStrStart = "\t\tnew_height: ";
		string NewHeightStrEnd = "\n";

		string NewWidthStrStart = "\t\tnew_width: ";
		string NewWidthStrEnd = "\n";

		string IsColorStrStart = "\t\tis_color: ";
		string IsColorStrEnd = "\n";

		string ScaleStrStart = "\t\tscale: ";
		string ScaleStrEnd = "\n";

		string MeanFileStrStart = "\t\tmean_file: ";
		string MeanFileStrEnd = "\n";

		string CropSizeStrStart = "\t\tcrop_size: ";
		string CropSizeStrEnd = "\n";

		string MirrorStrStart = "\t\tmirror: ";
		string MirrorStrEnd = "\n";

		string RootFolderStrStart = "\t\troot_folder: ";
		string RootFolderStrEnd = "\n";

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

		outStr += ImagedataParamStrStart;

		if (getSource() == "")
		{

		}
		else
		{
			outStr += SourceSrtStart + "\"" + getSource() + "\"" + SourceSrtEnd;
		}

		outStr += batchSizeStrStart + to_string(getBatchSize()) + batchSizeStrEnd;

		if(((ImageDataParam*)mParam)->mRandSkip != 0)
		{
			outStr += randSkipStrStart + to_string(getRandSkip()) + randSkipStrEnd;
		}

		if(((ImageDataParam*)mParam)->mShuffle != false)
		{
			outStr += ShuffleStrStart + "true" + ShuffleStrEnd;
		}

		if(((ImageDataParam*)mParam)->mNewHeight != 0)
		{
			outStr += NewHeightStrStart + to_string(getNewHeight()) + NewHeightStrEnd;
		}

		if(((ImageDataParam*)mParam)->mNewWidth != 0)
		{
			outStr += NewWidthStrStart + to_string(getNewWidth()) + NewWidthStrEnd;
		}

		if(((ImageDataParam*)mParam)->mIsColor != true)
		{
			outStr += IsColorStrStart + "false" + IsColorStrEnd;
		}

		if(((ImageDataParam*)mParam)->mScale != 1)
		{
			outStr += ScaleStrStart + to_string(getScale()) + ScaleStrEnd;
		}

		if (getMeanFile() == "")
		{

		}
		else
		{
			outStr += MeanFileStrStart + "\"" + getMeanFile() + "\"" + MeanFileStrEnd;
		}		

		if(((ImageDataParam*)mParam)->mCropSize != 0)
		{
			outStr += CropSizeStrStart + to_string(getCropSize()) + CropSizeStrEnd;
		}

		if(((ImageDataParam*)mParam)->mMirror != false)
		{
			outStr += MirrorStrStart + "true" + MirrorStrEnd;
		}

		if(((ImageDataParam*)mParam)->mRootFolder != "")
		{
			outStr += RootFolderStrStart + "\"" + getRootFolder() + "\"" + RootFolderStrEnd;
		}

		outStr += ImagedataParamStrEnd;

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
