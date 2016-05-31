#include "DataLayerParam.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	MemoryDataParam::MemoryDataParam()
	{
		mBatchSize = 0;
		mChannels = 0;
		mHeight = 0;
		mWidth = 0;
	}

	MemoryDataParam::~MemoryDataParam()
	{

	}
}