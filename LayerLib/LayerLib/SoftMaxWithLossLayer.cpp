#include "BaseLayer.h"
#include "LossLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
        SoftmaxWithLossLayer::SoftmaxWithLossLayer(string name)
        {
                mName = name;
                mType = MMALab::SOFT_MAX_WITH_LOSS;
                mParam = new SoftmaxWithLossParam();
        }

        SoftmaxWithLossLayer::SoftmaxWithLossLayer()
        {
                mType = MMALab::SOFT_MAX_WITH_LOSS;
                mParam = new SoftmaxWithLossParam();
        }

        SoftmaxWithLossLayer::~SoftmaxWithLossLayer()
        {

        }

        void SoftmaxWithLossLayer::setNormalize(bool state)
        {
                ((SoftmaxWithLossParam*)mParam)->mNormalize = state;
        }

        void SoftmaxWithLossLayer::setEngine(Engine type)
        {
                ((SoftmaxWithLossParam*)mParam)->mEngine = type;
        }

        void SoftmaxWithLossLayer::setAxis(int value)
        {
                ((SoftmaxWithLossParam*)mParam)->mAxis = value;
        }

        void SoftmaxWithLossLayer::setIgnoreLabel(int value)
        {
                ((SoftmaxWithLossParam*)mParam)->mIgnoreLabel = value;
        }

        bool SoftmaxWithLossLayer::getNormalize()
        {
                return ((SoftmaxWithLossParam*)mParam)->mNormalize;
        }

        Engine SoftmaxWithLossLayer::getEngine()
        {
                return ((SoftmaxWithLossParam*)mParam)->mEngine;
        }

        int SoftmaxWithLossLayer::getAxis()
        {
                return ((SoftmaxWithLossParam*)mParam)->mAxis;
        }

        int SoftmaxWithLossLayer::getIgnoreLabel()
        {
                return ((SoftmaxWithLossParam*)mParam)->mIgnoreLabel;
        }

        string SoftmaxWithLossLayer::convet2CaffeFormat()
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

                string softMaxWithLossParamStrStart = "\tloss_param\n\t{\n";
                string softMaxWithLossParamStrEnd = "\t}\n";

                string axisStrStart = "\t\taxis: ";
                string axisStrEnd = "\n";

                string ignorelabelStrStart = "\t\tignore_label: ";
                string ignorelabelStrEnd = "\n";

                string engineStrStart = "\t\tengine: ";
                string engineStrEnd = "\n";

                string normalizeStrStart = "\t\tnormalize: ";
                string normalizeStrEnd = "\n";

                string phaseStrStart = "\tinclude:\n\t{\n";
                string phaseStrEnd = "\t}\n";

                string phaseStateStrStart = "\t\tphase: ";
                string phaseStateStrEnd = "\n";

                string outStr = layerStrStart +
                                                nameStrStart  + getLayerName() + nameStrEnd +
                                                typeStrStart  + getLayerType() + typeStrEnd;

                for(size_t i = 0; i < mTops->size(); i++)
                {
                        outStr = outStr + topStrStart + (*mTops)[i] + topStrEnd;
                }

                for(size_t i = 0; i < mBottoms->size(); i++)
                {
                        outStr = outStr + bottomStrStart + (*mBottoms)[i] + bottomStrEnd;
                }

                outStr = outStr +
                             softMaxWithLossParamStrStart ;

                if(((SoftmaxWithLossParam*)mParam)->mEngine != MMALab::DEFAULT)
                {
                        switch (((SoftmaxWithLossParam*)mParam)->mEngine)
                        {
                        case MMALab::CAFFE:
                                outStr += engineStrStart+ "CAFFE" + engineStrEnd;
                                break;
                        case MMALab::CUDNN:
                                outStr += engineStrStart+ "CUDNN" + engineStrEnd;
                        }
                }

                if(((SoftmaxWithLossParam*)mParam)->mAxis != 1)
                {
                        outStr += axisStrStart + to_string(getAxis()) + axisStrEnd;
                }

                if(((SoftmaxWithLossParam*)mParam)->mNormalize != true)
                {
                        outStr += normalizeStrStart + "false" + normalizeStrEnd;
                }

                outStr += ignorelabelStrStart + to_string(getIgnoreLabel()) + ignorelabelStrEnd +
                                  softMaxWithLossParamStrEnd;

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
