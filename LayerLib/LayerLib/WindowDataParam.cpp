#include "DataLayerParam.h"
using namespace std;
using namespace MMALab;

namespace MMALab
{
	WindowDataParam::WindowDataParam()
	{
		mSource = "";
		mScale = 1;
		mMeanFile = "";
		mBatchSize = 0;
		mCropSize = 0;
		mMirror = false;
		mFgThreshold = 0.5;
		mBgThreshold = 0.5;
		mFgFraction = 0.25;
		mContextPad = 0;
		mCropMode =	CropMode::WARP;
		mCacheImages = false;
		mRootFolder = "";
	}

	WindowDataParam::~WindowDataParam()
	{

	}
}