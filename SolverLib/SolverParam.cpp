#include "SolverParam.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
    SolverParam::SolverParam()
    {
        mNet = "";
        mTainNet = "";
        mTestNet = "";
        mTestIter = 0;
        mTestInterval = 0;
        mTestComputeLoss = false;
        mTestInitialization = true;
        mBaseLr = 0;
        mDisplay = 0;
        mAverageLoss = 1;
        mMaxIter = 0;
        mIterSize = 1;
        mLrPolicy = LrPolicy::LRPOLICY_FIXED;
        mGamma = 0;
        mPower = 0;
        mMomentum = 0;
        mWeightDecay = 0;
        mRegularizationType = RegularizationType::RegularizationType_L2;
        mStepSize = 0;
        mStepValue.clear();
        mClipGradients = -1;
        mSnapshot = 0;
        mSnapshotPrefix = "";
        mSnapshotDiff = false;
        mSnapshotFormat = SnapshotFormat::BINARYPROTO;
         mSolverMode = SolverMode::GPU;
        mDeviceId = 0;
        mRandomSeed = -1;
        mType = SolverType::SGD;
        mDelta = 1e-8;
        mMomentum2 = 0.999;
        mRmsDecay = 0;
        mDebugInfo = false;
        mSnapshotAfterTrain = true;
    }

    SolverParam::~SolverParam()
    {

    }
}

