#include "VisionLayerParam.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	LRNParam::LRNParam()
	{
		mLocalSize = 5;
		mAlpha = 1.0;
		mBeta = 0.75;
		mNormRegion = MMALab::ACROSS_CHANNELS;
		mK = 1.0;
                mEngine = MMALab::DEFAULT;
	}

	LRNParam::~LRNParam()
	{

	}
}
