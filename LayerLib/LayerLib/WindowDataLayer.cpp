#include "BaseLayer.h"
#include "DataLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	WindowDataLayer::WindowDataLayer(string name)
	{
		mName = name;
		mType = MMALab::WINDOW_DATA;		
		mParam = new WindowDataParam();
	}

	WindowDataLayer::WindowDataLayer()
	{
		mType = MMALab::WINDOW_DATA;		
		mParam = new WindowDataParam();
	}

	WindowDataLayer::~WindowDataLayer()
	{
		
	}

	void WindowDataLayer::setSource(string value)
	{
		((WindowDataParam*)mParam)->mSource = value;
	}
		
	void WindowDataLayer::setScale(float value)
	{
		((WindowDataParam*)mParam)->mScale = value;
	}
		
	void WindowDataLayer::setMeanFile(string value)
	{
		((WindowDataParam*)mParam)->mMeanFile = value;
	}
		
        void WindowDataLayer::setBatchSize(uint32 value)
	{
		((WindowDataParam*)mParam)->mBatchSize = value;
	}
		
        void WindowDataLayer::setCropSize(uint32 value)
	{
		((WindowDataParam*)mParam)->mCropSize = value;
	}
		
	void WindowDataLayer::setMirror(bool value)
	{
		((WindowDataParam*)mParam)->mMirror = value;
	}
		
	void WindowDataLayer::setFgThreshold(float value)
	{
		((WindowDataParam*)mParam)->mFgThreshold = value;
	}
		
	void WindowDataLayer::setBgThreshold(float value)
	{
		((WindowDataParam*)mParam)->mBgThreshold = value;
	}
		
	void WindowDataLayer::setFgFraction(float value)
	{
		((WindowDataParam*)mParam)->mFgFraction = value;
	}
		
        void WindowDataLayer::setContextPad(uint32 value)
	{
		((WindowDataParam*)mParam)->mContextPad = value;
	}
		
	void WindowDataLayer::setCropMode(CropMode mode)
	{
		((WindowDataParam*)mParam)->mCropMode = mode;
	}

	void WindowDataLayer::setCacheImages(bool value)
	{
		((WindowDataParam*)mParam)->mCacheImages = value;
	}

	void WindowDataLayer::setRootFolder(string value)
	{
		((WindowDataParam*)mParam)->mRootFolder = value;
	}

	string WindowDataLayer::getSource()
	{
		return ((WindowDataParam*)mParam)->mSource;
	}
	
	float WindowDataLayer::getScale()
	{
		return ((WindowDataParam*)mParam)->mScale;
	}

	string WindowDataLayer::getMeanFile()
	{
		return ((WindowDataParam*)mParam)->mMeanFile;
	}

        uint32 WindowDataLayer::getBatchSize()
	{
		return ((WindowDataParam*)mParam)->mBatchSize;
	}

        uint32 WindowDataLayer::getCropSize()
	{
		return ((WindowDataParam*)mParam)->mCropSize;
	}

	bool WindowDataLayer::getMirror()
	{
		return ((WindowDataParam*)mParam)->mMirror;
	}

	float WindowDataLayer::getFgThreshold()
	{
		return ((WindowDataParam*)mParam)->mFgThreshold;
	}

	float WindowDataLayer::getBgThreshold()
	{
		return ((WindowDataParam*)mParam)->mBgThreshold;
	}

	float WindowDataLayer::getFgFraction()
	{
		return ((WindowDataParam*)mParam)->mFgFraction;
	}

        uint32 WindowDataLayer::getContextPad()
	{
		return ((WindowDataParam*)mParam)->mContextPad;
	}

	CropMode WindowDataLayer::getCropMode()
	{
		return ((WindowDataParam*)mParam)->mCropMode;
	}

	bool WindowDataLayer::getCacheImages()
	{
		return ((WindowDataParam*)mParam)->mCacheImages;
	}

	string WindowDataLayer::getRootFolder()
	{
		return ((WindowDataParam*)mParam)->mRootFolder;
	}

	string WindowDataLayer::convet2CaffeFormat()
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

		string WindowDataParamStrStart = "\twindow_data_param\n\t{\n";
		string WindowDataParamStrEnd = "\t}\n";

		string SourceStrStart = "\t\tsource: ";
		string SourceStrEnd = "\n";

		string ScaleStrStart = "\t\tscale: ";
		string ScaleStrEnd = "\n";

		string MeanFileStrStart = "\t\tmean_file: ";
		string MeanFileStrEnd = "\n";

		string BatchSizeStrStart = "\t\tbatch_size: ";
		string BatchSizeStrEnd = "\n";

		string CropSizeStrStart = "\t\tcrop_size: ";
		string CropSizeStrEnd = "\n";

		string MirrorStrStart = "\t\tmirror: ";
		string MirrorStrEnd = "\n";

		string FgThresholdStrStrat = "\t\tfg_threshold: ";
		string FgThresholdStrEnd = "\n";

		string BgThresholdStrStrat = "\t\tbg_threshold: ";
		string BgThresholdStrEnd = "\n";

		string FgFractionStrStart = "\t\tfg_fraction: ";
		string FgFractionStrEnd = "\n";

		string ContextPadStrStart = "\t\tcontext_pad: "; 
		string ContextPadStrEnd = "\n";

		string CropModeStrStart = "\t\tcrop_mode: ";
		string CropModeStrEnd = "\n";

		string CacheImagesStrStart = "\t\tcache_images: ";
		string CacheImagesStrEnd = "\n";

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

		outStr += WindowDataParamStrStart;

		if (getSource() == "")
		{

		}
		else
		{
			outStr += SourceStrStart + "\"" + getSource() + "\"" + SourceStrEnd;;
		}

		if(((WindowDataParam*)mParam)->mScale != 1)
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

		outStr += BatchSizeStrStart + to_string(getBatchSize()) + BatchSizeStrEnd;

		if(((WindowDataParam*)mParam)->mCropSize != 0)
		{
			outStr += CropSizeStrStart + to_string(getCropSize()) + CropSizeStrEnd;
		}

		if(((WindowDataParam*)mParam)->mMirror != false)
		{
			outStr += MirrorStrStart + "true" + MirrorStrEnd;
		}

		if(((WindowDataParam*)mParam)->mFgThreshold != 0.5)
		{
			outStr += FgThresholdStrStrat + to_string(getFgThreshold()) + FgFractionStrEnd;
		}

		if(((WindowDataParam*)mParam)->mBgThreshold != 0.5)
		{
			outStr += BgThresholdStrStrat + to_string(getBgThreshold()) + BgThresholdStrEnd;
		}

		if(((WindowDataParam*)mParam)->mFgFraction != 0.25)
		{
			outStr += FgFractionStrStart + to_string(getFgFraction()) + FgFractionStrEnd;
		}

		if(((WindowDataParam*)mParam)->mContextPad != 0)
		{
			outStr += ContextPadStrStart + to_string(getContextPad()) + ContextPadStrEnd;
		}

		if(((WindowDataParam*)mParam)->mCropMode != CropMode::WARP)
		{
			outStr += CropModeStrStart + "\"" + "square" + "\"" + CropModeStrEnd;
		}
		
		if(((WindowDataParam*)mParam)->mCacheImages != false)
		{
			outStr +=  CacheImagesStrStart + "true" + CacheImagesStrEnd;
		}

		if(((WindowDataParam*)mParam)->mRootFolder != "")
		{
			outStr +=  RootFolderStrStart + "\"" + getRootFolder() + "\"" + RootFolderStrEnd ;
		}

		outStr += WindowDataParamStrEnd;

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
