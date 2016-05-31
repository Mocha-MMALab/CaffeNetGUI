#include "BaseLayer.h"
#include "LossLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
        SigmoidCrossEntropyLossLayer::SigmoidCrossEntropyLossLayer(string name)
        {
                mName = name;
                mType = MMALab::SIGMOID_CROSS_ENTROPY_LOSS;
                mParam = new SigmoidCrossEntropyLossParam();
        }

        SigmoidCrossEntropyLossLayer::SigmoidCrossEntropyLossLayer()
        {
                mType = MMALab::SIGMOID_CROSS_ENTROPY_LOSS;
                mParam = new SigmoidCrossEntropyLossParam();
        }

        SigmoidCrossEntropyLossLayer::~SigmoidCrossEntropyLossLayer()
        {

        }

        string SigmoidCrossEntropyLossLayer::convet2CaffeFormat()
        {
                string layerStrStart = "layer\n{\n";
                string layerStrEnd = "}";

                string nameStrStart = "\tname: \"";
                string nameStrEnd = "\"\n";

                string typeStrStart = "\ttype: \"";
                string typeStrEnd = "\"\n";

                string topStrStart = "\ttop: \"";
                string topStrEnd = "\"\n";

                string bottomStrStart = "\tbottom: \"";
                string bottomStrEnd = "\"\n";

                string phaseStrStart = "\tinclude:\n\t{\n";
                string phaseStrEnd = "\t}\n";

                string phaseStateStrStart = "\t\tphase: ";
                string phaseStateStrEnd = "\n";

                string outStr = layerStrStart +
                                                nameStrStart  + mName         + nameStrEnd +
                                                typeStrStart  + getLayerType() + typeStrEnd;

                for(size_t i = 0; i < mTops->size(); i++)
                {
                        outStr = outStr + topStrStart + (*mTops)[i] + topStrEnd;
                }

                for(size_t i = 0; i < mBottoms->size(); i++)
                {
                        outStr = outStr + bottomStrStart + (*mBottoms)[i] + bottomStrEnd;
                }


                if (mPhase != Phase::BOTH)
                {
                        outStr += phaseStrStart + phaseStateStrStart;

                        if (mPhase == Phase::TRAIN)
                        {
                                outStr += "TRAIN";
                        }
                        else if (mPhase == Phase::TEST)
                        {
                                outStr += "TEST";
                        }

                        outStr += phaseStateStrEnd + phaseStrEnd;
                }

                outStr += layerStrEnd;

                return outStr;
        }
}
