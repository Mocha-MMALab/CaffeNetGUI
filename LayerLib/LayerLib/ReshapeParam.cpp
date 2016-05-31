#include "CommonLayerParam.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	ReshapeParam::ReshapeParam()
	{
		mShape = NULL;
		mAxis = 0;
		mNumAxis = -1;
	}

	ReshapeParam::~ReshapeParam()
	{

	}
}
