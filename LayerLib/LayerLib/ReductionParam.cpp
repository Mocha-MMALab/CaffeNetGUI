#include "CommonLayerParam.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	ReductionParam::ReductionParam()
	{
		mOperation = MMALab::REDUCTIONOP_SUM;
		mAxis = 0;
		mCoeff = 1.0;
	}

	ReductionParam::~ReductionParam()
	{

	}
}