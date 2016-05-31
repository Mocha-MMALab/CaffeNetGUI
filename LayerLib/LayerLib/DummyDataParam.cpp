#include "DataLayerParam.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	DummyDataParam::DummyDataParam()
	{
		mDataFiller = MMALab::CONSTANTFILLER;
		mShape = NULL;
		mNum = 0;
		mChannels = 0;
		mHeight = 0;
		mWidth = 0;
	}

	DummyDataParam::~DummyDataParam()
	{

	}
}