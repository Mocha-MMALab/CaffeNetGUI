#include "NeuronLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	ExpParam::ExpParam()
	{
		mBase  = -1.0;
		mScale =  1.0;
		mShift =  0.0;
	}

	ExpParam::~ExpParam()
	{

	}
}