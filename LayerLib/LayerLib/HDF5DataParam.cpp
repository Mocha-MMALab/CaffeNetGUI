#include "DataLayerParam.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	HDF5DataParam::HDF5DataParam()
	{
		mSource = "";
		mBatchSize = 0;
		mShuffle = false;
	}

	HDF5DataParam::~HDF5DataParam()
	{

	}
}