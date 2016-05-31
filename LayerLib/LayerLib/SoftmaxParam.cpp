#include "CommonLayerParam.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	SoftmaxParam::SoftmaxParam()
	{
		mEngine = MMALab::DEFAULT;
		mAxis = 1;
	}

	SoftmaxParam::~SoftmaxParam()
	{

	}
}
