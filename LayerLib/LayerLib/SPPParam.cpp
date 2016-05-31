#include "VisionLayerParam.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	SPPParam::SPPParam()
	{
		mPyramidHeight = 0;
		mPool = MMALab::POOLMETHOD_MAX;
		mEngine = MMALab::DEFAULT;
	}
	SPPParam::~SPPParam()
	{

	}
}