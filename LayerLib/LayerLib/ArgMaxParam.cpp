#include "CommonLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	ArgMaxParam::ArgMaxParam()
	{
		mOutMaxVal = false;
		mTopK = 1;
		mAxis = 0;
	}

	ArgMaxParam::~ArgMaxParam()
	{

	}
}
