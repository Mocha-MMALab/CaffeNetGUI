#include "NeuronLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	ReLUParam::ReLUParam()
	{
		mNegativeSlope = 0;
		mEngine = MMALab::DEFAULT;
	}

	ReLUParam::~ReLUParam()
	{

	}
}