#ifndef SOLVERPARAM_H
#define SOLVERPARAM_H
#ifdef WIN32
        #ifdef NNLIB_EXPORTS
        #define SOLVERLIB_API __declspec(dllexport)
        #else
        #define SOLVERLIB_API __declspec(dllimport)
        #endif
#else
        #define SOLVERLIB_API
#endif

#include <string>
#include "SolverEnum.h"
#include <vector>
using namespace std;
using namespace MMALab;

/* @namespace MMALab
 * @MMALab namespace
 */
namespace MMALab
{
    class SOLVERLIB_API SolverParam
    {
    public:
        string mNet;
        //NetParameter net_param
        string mTainNet;
        //NetParameter train_net_param
        string mTestNet;
        //NetParameter test_net_param
        //NetState train_state
        //NetState test_state
        int mTestIter;//repeated
        int mTestInterval;//default = 0
        bool mTestComputeLoss;//default = false
        bool mTestInitialization;//default = true
        float mBaseLr;
        int mDisplay;
        int mAverageLoss;//default = 1
        int mMaxIter;
        int mIterSize;//default = 1
        LrPolicy mLrPolicy;
        float mGamma;
        float  mPower;
        float mMomentum;
        float mWeightDecay;
        RegularizationType mRegularizationType;//default = "L2"   L1,L2
        int mStepSize;
        vector<int> mStepValue;//repeated
        float mClipGradients;//default = -1
        int mSnapshot;//default = 0
        string mSnapshotPrefix;
        bool mSnapshotDiff;//default = false
        SnapshotFormat mSnapshotFormat;//default = BINARYPROTO
        SolverMode mSolverMode;//default = GPU
        int mDeviceId;//default = 0
        long mRandomSeed;//default = -1
        SolverType mType;//default = SGD
        float mDelta;//default = 1e-8
        float mMomentum2;//default = 0.999
        float mRmsDecay;
        bool mDebugInfo;//default = false
        bool mSnapshotAfterTrain;//default = true


        SolverParam();
        ~SolverParam();
    };

}


#endif // SOLVERPARAM_H
