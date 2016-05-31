#include "DataLayerParam.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	DataParam::DataParam()
	{
		mSource = "";
		mBatchSize = 0;
		mRandSkip = 0;
		mBackend = DB::LEVELDB;
		mScale = 1;
		mMeanfile = "";
		mCropsize = 0;
		mMirror = false;
		mForceEncodedcolor = false;
		mPrefetch = 4;
	}

	DataParam::~DataParam()
	{

	}
}
