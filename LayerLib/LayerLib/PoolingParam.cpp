#include "VisionLayerParam.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	PoolingParam::PoolingParam()
	{
		mKernelSize = 0;
		//mKernelH = 0;
		//mKernelW = 0;
		mPad = 0;
		//mPadH = 0;
		//mPadW = 0;
		mStride = 1;
		//mStrideH = 0;
		//mStrideW = 0;
		mPool = MMALab::POOLMETHOD_MAX;
		mEngine = MMALab::DEFAULT;
		mGlobalPooling = false;
		
	}
	PoolingParam::~PoolingParam()
	{

	}
}
