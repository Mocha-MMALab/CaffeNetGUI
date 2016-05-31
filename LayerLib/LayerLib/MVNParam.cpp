#include "CommonLayerParam.h"
using namespace std;
using namespace MMALab;

namespace MMALab
{
	MVNParam::MVNParam()
	{
		mNormalizeVariance = true;

		mAcrossChannels = false;

		mEps = 1e-9;
	}

	MVNParam::~MVNParam()
	{

	}
}