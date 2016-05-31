#include "NeuronLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	
	PReLUParam::PReLUParam()
	{
		mFilterType = MMALab::NONE;
		mFilter = NULL;
		mChannelShared = false;
	}

	PReLUParam::~PReLUParam()
	{

	}
}