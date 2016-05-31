#include "LossLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	ContrastiveLossParam::ContrastiveLossParam()
	{
		mMargin = 1.0;
		mLegacyVersion = false;
	}

	ContrastiveLossParam::~ContrastiveLossParam()
	{

	}

}