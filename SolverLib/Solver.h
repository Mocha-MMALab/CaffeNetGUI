#ifndef SOLVER_H
#define SOLVER_H

#include <string>
#include "SolverParam.h"

using namespace std;

/* @namespace MMALab
 * @MMALab namespace
 */
namespace MMALab
{
    class SOLVERLIB_API Solver
    {
    public:
        Solver(string name);
        Solver();
        ~Solver();
        void setNet(string value);
        void setTainNet(string value);
        void setTestNet(string value);
        void setTestIter(int value);
        void setTestInterval(int value);
        void setTestComputeLoss(bool value);
        void setTestInitialization(bool value);
        void setBaseLr(float value);
        void setDisplay(int value);
        void setAverageLoss(int value);
        void setMaxIter(int value);
        void setIterSize(int value);
        void setLrPolicy(LrPolicy value);
        void setGamma(float value);
        void setPower(float value);
        void setMomentum(float value);
        void setWeightDecay(float value);
        void setRegularizationType(RegularizationType value);
        void setStepSize(int value);
        void setStepValue(int value);
        void setClipGradients(float value);
        void setSnapshot(int value);
        void setSnapshotPrefix(string value);
        void setSnapshotDiff(bool value);
        void setSnapshotFormat(SnapshotFormat value);
        void setSolverMode(SolverMode value);
        void setDeviceId(int value);
        void setRandomSeed(long value);
        void setType(SolverType value);
        void setDelta(float value);
        void setMomentum2(float value);
        void setRmsDecay(float value);
        void setDebugInfo(bool value);
        void setSnapshotAfterTrain(bool value);

       string getNet();
       string getTainNet();
       string getTestNet();
       int getTestIter();
       int getTestInterval();
       bool getTestComputeLoss();
       bool getTestInitialization();
       float getBaseLr();
       int getDisplay();
       int getAverageLoss();
       int getMaxIter();
       int getIterSize();
       LrPolicy getLrPolicy();
       float getGamma();
       float getPower();
       float getMomentum();
       float getWeightDecay();
       RegularizationType getRegularizationType();
       int getStepSize();
       int getStepValue(int index);
       float getClipGradients();
       int getSnapshot();
       string getSnapshotPrefix();
       bool getSnapshotDiff();
       SnapshotFormat getSnapshotFormat();
       SolverMode getSolverMode();
       int getDeviceId();
       long getRandomSeed();
       SolverType getType();
       float getDelta();
       float getMomentum2();
       float getRmsDecay();
       bool getDebugInfo();
       bool getSnapshotAfterTrain();

       void clearStepValue();
       string convet2CaffeFormat();

    protected:
        string mName;
        SolverParam* mParam;
    };
}
#endif // SOLVER_H
