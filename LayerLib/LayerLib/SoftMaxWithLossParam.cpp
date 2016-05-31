#include "LossLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
        SoftmaxWithLossParam::SoftmaxWithLossParam()
        {
                mNormalize = true;
                mEngine = MMALab::DEFAULT;
                mAxis = 1;
                mIgnoreLabel = 0;
        }

        SoftmaxWithLossParam::~SoftmaxWithLossParam()
        {

        }
}
