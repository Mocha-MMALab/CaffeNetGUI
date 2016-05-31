#include "CommonLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	EltwiseParam::EltwiseParam()
	{
		mOperation = MMALab::ELTWISEOP_SUM;
		mCoeff = 0;
		mStableProdGrad = true;
	}

	EltwiseParam::~EltwiseParam()
	{

	}
}
