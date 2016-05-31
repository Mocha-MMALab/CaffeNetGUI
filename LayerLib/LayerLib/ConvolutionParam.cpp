#include "VisionLayerParam.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	ConvolutionParam::ConvolutionParam()
	{
		mNumOutput = 0;
		mKernelSize = 0;
		mWeightfilterType = MMALab::NONE;
		mWeightfilter = NULL;
		mBiasfilterType = MMALab::NONE;
		mBiasfilter = NULL;
		mBiasTerm = true;
		mPad = 0;
		mStride = 1;
		mEngine = MMALab::DEFAULT;
		mGroup = 1;
	}

	ConvolutionParam::~ConvolutionParam()
	{
	
	}




}