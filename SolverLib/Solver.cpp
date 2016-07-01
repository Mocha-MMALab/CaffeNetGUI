#include "Solver.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
    Solver::Solver(string name)
    {
        mName = name;
        mParam = new SolverParam();
    }

    Solver::Solver()
    {
        mParam = new SolverParam();
    }
	Solver::~Solver()
    {
        
    }

    void Solver::setNet(string value)
    {
        mParam->mNet = value;
    }

    void Solver::setTainNet(string value)
    {
        mParam->mTainNet = value;
    }

    void Solver::setTestNet(string value)
    {
        mParam->mTestNet = value;
    }

    void Solver::setTestIter(int value)
    {
        mParam->mTestIter = value;
    }

    void Solver::setTestInterval(int value)
    {
        mParam->mTestInterval = value;
    }

    void Solver::setTestComputeLoss(bool value)
    {
        mParam->mTestComputeLoss = value;
    }

    void Solver::setTestInitialization(bool value)
    {
        mParam->mTestInitialization = value;
    }

    void Solver::setBaseLr(float value)
    {
        mParam->mBaseLr = value;
    }

    void Solver::setDisplay(int value)
    {
        mParam->mDisplay = value;
    }

    void Solver::setAverageLoss(int value)
    {
        mParam->mAverageLoss = value;
    }

    void Solver::setMaxIter(int value)
    {
        mParam->mMaxIter = value;
    }

    void Solver::setIterSize(int value)
    {
        mParam->mIterSize = value;
    }

    void Solver::setLrPolicy(LrPolicy value)
    {
        mParam->mLrPolicy = value;
    }

    void Solver::setGamma(float value)
    {
        mParam->mGamma = value;
    }

    void Solver::setPower(float value)
    {
        mParam->mPower = value;
    }

    void Solver::setMomentum(float value)
    {
        mParam->mMomentum = value;
    }

    void Solver::setWeightDecay(float value)
    {
        mParam->mWeightDecay = value;
    }

    void Solver::setRegularizationType(RegularizationType value)
    {
        mParam->mRegularizationType = value;
    }

    void Solver::setStepSize(int value)
    {
        mParam->mStepSize = value;
    }

    void Solver::setStepValue(int value)
    {
        mParam->mStepValue.push_back(value);
    }

    void Solver::setClipGradients(float value)
    {
        mParam->mClipGradients = value;
    }

    void Solver::setSnapshot(int value)
    {
        mParam->mSnapshot = value;
    }

    void Solver::setSnapshotPrefix(string value)
    {
        mParam->mSnapshotPrefix = value;
    }

    void Solver::setSnapshotDiff(bool value)
    {
        mParam->mSnapshotDiff = value;
    }

    void Solver::setSnapshotFormat(SnapshotFormat value)
    {
        mParam->mSnapshotFormat = value;
    }

    void Solver::setSolverMode(SolverMode value)
    {
        mParam->mSolverMode = value;
    }

    void Solver::setDeviceId(int value)
    {
        mParam->mDeviceId = value;
    }

    void Solver::setRandomSeed(long value)
    {
        mParam->mRandomSeed = value;
    }

    void Solver::setType(SolverType value)
    {
        mParam->mType = value;
    }

    void Solver::setDelta(float value)
    {
        mParam->mDelta = value;
    }

    void Solver::setMomentum2(float value)
    {
        mParam->mMomentum2 = value;
    }

    void Solver::setRmsDecay(float value)
    {
        mParam->mRmsDecay = value;
    }

    void Solver::setDebugInfo(bool value)
    {
        mParam->mDebugInfo = value;
    }

    void Solver::setSnapshotAfterTrain(bool value)
    {
        mParam->mSnapshotAfterTrain = value;
    }

   string Solver::getNet()
   {
       return mParam->mNet;
   }

   string Solver::getTainNet()
   {
       return mParam->mTainNet;
   }

   string Solver::getTestNet()
   {
       return mParam->mTestNet;
   }

   int Solver::getTestIter()
   {
       return mParam->mTestIter;
   }

   int Solver::getTestInterval()
   {
       return mParam->mTestInterval;
   }

   bool Solver::getTestComputeLoss()
   {
       return mParam->mTestComputeLoss;
   }

   bool Solver::getTestInitialization()
   {
       return mParam->mTestInitialization;
   }

   float Solver::getBaseLr()
   {
       return mParam->mBaseLr;
   }

   int Solver::getDisplay()
   {
       return mParam->mDisplay;
   }

   int Solver::getAverageLoss()
   {
       return mParam->mAverageLoss;
   }

   int Solver::getMaxIter()
   {
       return mParam->mMaxIter;
   }

   int Solver::getIterSize()
   {
       return mParam->mIterSize;
   }

   LrPolicy Solver::getLrPolicy()
   {
       return mParam->mLrPolicy;
   }

   float Solver::getGamma()
   {
       return mParam->mGamma;
   }

   float Solver::getPower()
   {
       return mParam->mPower;
   }

   float Solver::getMomentum()
   {
       return mParam->mMomentum;
   }

   float Solver::getWeightDecay()
   {
       return mParam->mWeightDecay;
   }

   RegularizationType Solver::getRegularizationType()
   {
       return mParam->mRegularizationType;
   }

   int Solver::getStepSize()
   {
       return mParam->mStepSize;
   }

   int Solver::getStepValue(int index)
   {
       return mParam->mStepValue.at(index);
   }

   float Solver::getClipGradients()
   {
       return mParam->mClipGradients;
   }

   int Solver::getSnapshot()
   {
       return mParam->mSnapshot;
   }

   string Solver::getSnapshotPrefix()
   {
       return mParam->mSnapshotPrefix;
   }

   bool Solver::getSnapshotDiff()
   {
       return mParam->mSnapshotDiff;
   }

   SnapshotFormat Solver::getSnapshotFormat()
   {
       return mParam->mSnapshotFormat;
   }

   SolverMode Solver::getSolverMode()
   {
       return mParam->mSolverMode;
   }

   int Solver::getDeviceId()
   {
       return mParam->mDeviceId;
   }

   long Solver::getRandomSeed()
   {
       return mParam->mRandomSeed;
   }

   SolverType Solver::getType()
   {
       return mParam->mType;
   }

   float Solver::getDelta()
   {
       return mParam->mDelta;
   }

   float Solver::getMomentum2()
   {
       return mParam->mMomentum2;
   }

   float Solver::getRmsDecay()
   {
       return mParam->mRmsDecay;
   }

   bool Solver::getDebugInfo()
   {
       return mParam->mDebugInfo;
   }

   bool Solver::getSnapshotAfterTrain()
   {
       return mParam->mSnapshotAfterTrain;
   }

   void Solver::clearStepValue()
   {
       mParam->mStepValue.clear();
   }

   string Solver::convet2CaffeFormat()
   {
       string outStr = "";

       string netStrStart = "net: \"";
       string netStrEnd = "\"\n";

       string trainNetStrStart = "train_net: \"";
       string trainNetStrEnd = "\"\n";

       string testNetStrStart = "test_net: \"";
       string testNetStrEnd = "\"\n";

       string testIterStrStart = "test_iter: ";
       string testIterStrEnd = "\n";

       string testIntervalStrStart = "test_interval: ";
       string testIntervalStrEnd = "\n";

       string baseLrStrStart = "base_lr: ";
       string baseLrStrEnd = "\n";

       string momentumStrStart = "momentum: ";
       string momentumStrEnd = "\n";

       string weightDecayStrStart = "weight_decay: ";
       string weightDecayStrEnd = "\n";

       string lrPolicyStrStart = "lr_policy: \"";
       string lrPolicyStrEnd = "\"\n";

       string stepSizeStrStart = "stepsize: ";
       string stepSizeStrEnd = "\n";

       string gammaStrStart = "gamma: ";
       string gammaStrEnd = "\n";

       string powerStrStart = "power: ";
       string powerStrEnd = "\n";

       string stepValueStrStart = "stepvalue: ";
       string stepValueStrEnd = "\n";

       string displayStrStart = "display: ";
       string displayStrEnd = "\n";

       string maxIterStrStart = "max_iter: ";
       string maxIterStrEnd = "\n";

       string snapshotStrStart = "snapshot: ";
       string snapshotStrEnd = "\n";

       string snapshotPrefixStrStart = "snapshot_prefix: \"";
       string snapshotPrefixStrEnd = "\"\n";

       string typeStrStart = "type: \"";
       string typeStrEnd = "\"\n";

       string solveModeStrStart = "solver_mode: ";
       string solveModeStrEnd= "\n";

       if(getNet() != "")
       {
           outStr += netStrStart + getNet() + netStrEnd;
       }

       if(getTainNet() != "")
       {
           outStr += trainNetStrStart + getTainNet() + trainNetStrEnd;
       }

       if(getTestNet() != "")
       {
           outStr += testNetStrStart + getTestNet() + testNetStrEnd;
       }

       outStr += testIterStrStart + to_string(getTestIter()) + testIterStrEnd +
                        testIntervalStrStart + to_string(getTestInterval()) + testIntervalStrEnd +
                        baseLrStrStart + to_string(getBaseLr()) + baseLrStrEnd +
                        momentumStrStart + to_string(getMomentum()) + momentumStrEnd +
                        weightDecayStrStart + to_string(getWeightDecay()) + weightDecayStrEnd;

       switch(getLrPolicy())
       {
            case LrPolicy::LRPOLICY_FIXED:
            {
                outStr += lrPolicyStrStart + "fixed" + lrPolicyStrEnd;
                break;
            }
            case LrPolicy::LRPOLICY_STEP:
            {
                outStr += lrPolicyStrStart + "step" + lrPolicyStrEnd +
                        stepSizeStrStart + to_string(getStepSize()) + stepSizeStrEnd +
                        gammaStrStart + to_string(getGamma()) + gammaStrEnd;
                break;
            }
            case LrPolicy::LRPOLICY_EXP:
            {
                outStr += lrPolicyStrStart + "exp" + lrPolicyStrEnd +
                        gammaStrStart + to_string(getGamma()) + gammaStrEnd;
                break;
            }
            case LrPolicy::LRPOLICY_INV:
            {
                outStr += lrPolicyStrStart + "inv" + lrPolicyStrEnd +
                        gammaStrStart + to_string(getGamma()) + gammaStrEnd +
                        powerStrStart + to_string(getPower()) + powerStrEnd;
                break;
            }
            case LrPolicy::LRPOLICY_MULTISTEP:
            {
                outStr += lrPolicyStrStart + "multistep" + lrPolicyStrEnd;
                for(int i = 0 ; i < mParam->mStepValue.size(); i++)
                {
                    outStr += stepValueStrStart + to_string(getStepValue(i)) + stepValueStrEnd;
                }
                outStr += gammaStrStart + to_string(getGamma()) + gammaStrEnd;
                break;
            }
            case LrPolicy::LRPOLICY_POLY:
            {
                outStr += lrPolicyStrStart + "poly" + lrPolicyStrEnd +
                        powerStrStart + to_string(getPower()) + powerStrEnd;
                break;
            }
            case LrPolicy::LRPOLICY_SIGMOID:
            {
                outStr += lrPolicyStrStart + "sigmoid" + lrPolicyStrEnd +
                        stepSizeStrStart + to_string(getStepSize()) + stepSizeStrEnd +
                        gammaStrStart + to_string(getGamma()) + gammaStrEnd;
                break;
            }
       }

       outStr += displayStrStart + to_string(getDisplay()) + displayStrEnd +
               maxIterStrStart + to_string(getMaxIter()) + maxIterStrEnd +
               snapshotStrStart + to_string(getSnapshot()) + snapshotStrEnd;

       if(getSnapshotPrefix() != "")
       {
           outStr += snapshotPrefixStrStart + getSnapshotPrefix() + snapshotPrefixStrEnd;
       }

       switch(getType())
       {
            case SolverType::SGD:
            {
                outStr += typeStrStart + "SGD" + typeStrEnd;
                break;
            }
            case SolverType::NESTEROV:
            {
                outStr += typeStrStart + "Nesterov" + typeStrEnd;
                break;
            }
            case SolverType::ADAGRAD:
            {
                outStr += typeStrStart + "AdaGrad" + typeStrEnd;
                break;
            }
            case SolverType::RMSPROP:
            {
                outStr += typeStrStart + "RMSProp" + typeStrEnd;
                break;
            }
            case SolverType::ADADELTA:
            {
                outStr += typeStrStart + "AdaDelta" + typeStrEnd;
                break;
            }
            case SolverType::ADAM:
            {
                outStr += typeStrStart + "Adam" + typeStrEnd;
                break;
            }
       }

       switch(getSolverMode())
       {
            case SolverMode::CPU:
            {
                outStr += solveModeStrStart + "CPU" + solveModeStrEnd;
                break;
            }
            case SolverMode::GPU:
            {
                outStr += solveModeStrStart + "GPU" + solveModeStrEnd;
                break;
            }
       }

       return outStr;

   }
}
