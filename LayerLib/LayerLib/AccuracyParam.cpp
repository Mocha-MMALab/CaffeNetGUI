#include "LossLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	AccuracyParam::AccuracyParam()
	{
		mTopk = 1;
		mAxis = 1;
		mIgnoreLabel = 0;
	}

	AccuracyParam::~AccuracyParam()
	{

	}
}