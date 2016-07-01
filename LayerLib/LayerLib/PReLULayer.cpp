#include "BaseLayer.h"
#include "NeuronLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	PReLULayer::PReLULayer(string name)
	{
		mName = name;
		mType = MMALab::PRELU;		
		mParam = new PReLUParam();
	}


	PReLULayer::PReLULayer()
	{
		mType = MMALab::PRELU;		
		mParam = new PReLUParam();
	}

	PReLULayer::~PReLULayer()
	{
		 
	}

	void PReLULayer::setFilter(Gaussian* filter)
	{
		((PReLUParam*)mParam)->mFilterType = MMALab::GAUSSIAN;
		((PReLUParam*)mParam)->mFilter = (void*)filter;
	}

	void PReLULayer::setFilter(Constant* filter)
	{
		((PReLUParam*)mParam)->mFilterType = MMALab::CONSTANT;
		((PReLUParam*)mParam)->mFilter = (void*)filter;
	}

	void PReLULayer::setFilter(Xavier* filter)
	{
		((PReLUParam*)mParam)->mFilterType = MMALab::XAVIER;
		((PReLUParam*)mParam)->mFilter = (void*)filter;
	}

        void PReLULayer::setFilter(Uniform* filter)
        {
                ((PReLUParam*)mParam)->mFilterType = MMALab::UNIFORM;
                ((PReLUParam*)mParam)->mFilter = (void*)filter;
        }

        void PReLULayer::setFilter(Msra* filter)
        {
                ((PReLUParam*)mParam)->mFilterType = MMALab::MSRA;
                ((PReLUParam*)mParam)->mFilter = (void*)filter;
        }

	void PReLULayer::setChannelShared(bool state)
	{
		((PReLUParam*)mParam)->mChannelShared = state;
	}
	
	void* PReLULayer::getFilter()
	{
		return ((PReLUParam*)mParam)->mFilter;
	}

	bool PReLULayer::getChannelShared()
	{
		return ((PReLUParam*)mParam)->mChannelShared;
	}

	FilterType PReLULayer::getFilterType()
	{
		return ((PReLUParam*)mParam)->mFilterType;
	}

	void PReLULayer::setFilterToNone()
	{
		((PReLUParam*)mParam)->mFilterType = FilterType::NONE;
		((PReLUParam*)mParam)->mFilter = NULL;
	}

	string PReLULayer::convet2CaffeFormat()
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

		string PReLUParamStrStart = "\tprelu_param\n\t{\n";
		string PReLUParamStrEnd = "\t}\n";

		string fillerStrStart = "\t\tfiller\n\t\t{\n\t\t\ttype:\"";
		string fillerStrEnd = "\n\t\t}\n";

		string channelSharedStrStart = "\t\tchannel_shared: ";
		string channelSharedStrEnd = "\n";

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

		outStr = outStr + PReLUParamStrStart;
		
		switch (((PReLUParam*)mParam)->mFilterType)
		{

		case MMALab::GAUSSIAN:
		{
			string temp1 = "\"\n\t\t\tstd: ";
			string temp2 = "\n\t\t\tmean: ";
                        string temp3 = "\n\t\t\tsparse: ";
			Gaussian* filter = (Gaussian*)getFilter();
			outStr = outStr + fillerStrStart + filter->mName 
							+ temp1 + to_string(filter->mStd) 
                                                        + temp2 + to_string(filter->mMean)
                                                        + temp3 + to_string(filter->mSparse)
							+ fillerStrEnd;
			break;
		}

		case MMALab::CONSTANT:
		{
			string temp1 = "\"\n\t\t\tvalue: ";
                        //string temp2 = "\n\t\t\tsparse: ";
			Constant* filter = (Constant*)getFilter();
			outStr = outStr + fillerStrStart + filter->mName 
                                                        + temp1 + to_string(filter->mValue)
                                                        //+ temp2 + to_string(filter->mSparse)
							+ fillerStrEnd;
			break;
		}
		break;

		case MMALab::XAVIER:
		{
                        //string temp1 = "\"\n\t\t\tsparse: ";
			string temp2 = "\"\n\t\t\tstd: ";
                        string temp3 = "\n\t\t\tvariance_norm: ";
			Xavier* filter = (Xavier*)getFilter();
			outStr = outStr + fillerStrStart + filter->mName 
                                                        //+ temp1 + to_string(filter->mSparse)
                                                        + temp2 + to_string(filter->mStd);

                        if(filter->mVarianceNorm!=MMALab::FAN_IN)
                        {
                            switch(filter->mVarianceNorm)
                            {
                                case MMALab::FAN_OUT: outStr = outStr + temp3 + "FAN_OUT";break;
                                case MMALab::AVERAGE: outStr = outStr + temp3 + "AVERAGE";break;
                            }
                        }
                        outStr = outStr + fillerStrEnd;
			break;
		}
		break;

                case MMALab::UNIFORM:
                {
                        string temp1 = "\"\n\t\t\tmin: ";
                        string temp2 = "\n\t\t\tmax: ";
                        //string temp3 = "\n\t\t\tsparse: ";
                        Uniform* filter = (Uniform*)getFilter();
                        outStr = outStr + fillerStrStart + filter->mName
                                                        + temp1 + to_string(filter->mMin)
                                                        + temp2 + to_string(filter->mMax)
                                                        //+ temp3 + to_string(filter->mSparse)
                                                        + fillerStrEnd;
                        break;
                }
                break;

                case MMALab::MSRA:
                {
                    string temp1 = "\n\t\t\tvariance_norm: ";
                    Msra* filter = (Msra*)getFilter();

                    outStr = outStr + fillerStrStart + filter->mName + "\"";
                    if(filter->mVarianceNorm!=MMALab::FAN_IN)
                    {
                        switch(filter->mVarianceNorm)
                        {
                            case MMALab::FAN_OUT: outStr = outStr + temp1 + "FAN_OUT";break;
                            case MMALab::AVERAGE: outStr = outStr + temp1 + "AVERAGE";break;
                        }
                    }
                    outStr = outStr + fillerStrEnd;
                    break;
                }
                    break;

		default:
			break;

		}

		if (getChannelShared() != false)
		{
			outStr += channelSharedStrStart + "true" + channelSharedStrEnd;
		}				 	
				 
		outStr += PReLUParamStrEnd;

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
