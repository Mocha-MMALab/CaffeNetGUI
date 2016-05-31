#include "CommonLayerParam.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	InnerProductParam::InnerProductParam()
	{
		mNumOutput = 0;

		mBiasTerm = true;		

		mWeightFilterType = MMALab::NONE;
		mWeightFilter = NULL;

		mBiasFilterType = MMALab::NONE;
		mBiasFilter = NULL;

		mAxis = 1;
	}

	InnerProductParam::~InnerProductParam()
	{
	
	}
}