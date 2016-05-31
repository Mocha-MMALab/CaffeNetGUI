#include "DataLayerParam.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	ImageDataParam::ImageDataParam()
	{
		mSource = "";
		mBatchSize = 1;
		mRandSkip = 0;
		mShuffle = false;
		mNewHeight = 0;
		mNewWidth = 0;
		mIsColor = true;
		mScale = 1;
		mMeanFile = "";
		mCropSize = 0;
		mMirror = false;
		mRootFolder = "";
	}

	ImageDataParam::~ImageDataParam()
	{

	}
}
