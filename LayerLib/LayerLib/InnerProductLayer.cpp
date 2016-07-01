#include "BaseLayer.h"
#include "CommonLayers.h"
#include <limits>
#include <climits>

using namespace std;
using namespace MMALab;

namespace MMALab
{
	InnerProductLayer::InnerProductLayer(string name)
	{
		mName = name;
		mType = MMALab::INNER_PRODUCT;		
		mParam = new InnerProductParam();

		//learning rate and decay multipliers for the filters
		mFilterLRateMult = 1;
		mFilterDecayMult = 1;

		//learning rate and decay multipliers for the biases
		mBiasLRateMult = 1;
		mBiasDecayMult = 1;
	}

	InnerProductLayer::InnerProductLayer()
	{
		mType = MMALab::INNER_PRODUCT;		
		mParam = new InnerProductParam();

		//learning rate and decay multipliers for the filters
		mFilterLRateMult = 1;
		mFilterDecayMult = 1;

		//learning rate and decay multipliers for the biases
		mBiasLRateMult = 1;
		mBiasDecayMult = 1;
	}

	InnerProductLayer::~InnerProductLayer()
	{
		
	}

	void InnerProductLayer::setNumOutput(uint32 value)
	{
		((InnerProductParam*)mParam)->mNumOutput = value;
	}

	void InnerProductLayer::setBiasTerm(bool state)
	{
		((InnerProductParam*)mParam)->mBiasTerm = state;
	}

	//set learning rate and decay multipliers for the filters
	void InnerProductLayer::setFilterLRDecayMult(float lr, float decay)
	{
		mFilterLRateMult = lr;
		mFilterDecayMult = decay;
	}
	//set learning rate and decay multipliers for the biases
	void InnerProductLayer::setBiasLRDecayMult(float lr, float decay)
	{
		mBiasLRateMult = lr;
		mBiasDecayMult = decay;
	}

	void InnerProductLayer::setWeightfilter(Gaussian* weightfilter)
	{
		((InnerProductParam*)mParam)->mWeightFilterType = MMALab::GAUSSIAN;
		((InnerProductParam*)mParam)->mWeightFilter = (void*)weightfilter;
	}

	void InnerProductLayer::setWeightfilter(Constant* weightfilter)
	{
		((InnerProductParam*)mParam)->mWeightFilterType = MMALab::CONSTANT;
		((InnerProductParam*)mParam)->mWeightFilter = (void*)weightfilter;
	}

	void InnerProductLayer::setWeightfilter(Xavier* weightfilter)
	{
		((InnerProductParam*)mParam)->mWeightFilterType = MMALab::XAVIER;
		((InnerProductParam*)mParam)->mWeightFilter = (void*)weightfilter;
	}

        void InnerProductLayer::setWeightfilter(Uniform* weightfilter)
        {
                ((InnerProductParam*)mParam)->mWeightFilterType = MMALab::UNIFORM;
                ((InnerProductParam*)mParam)->mWeightFilter = (void*)weightfilter;
        }

        void InnerProductLayer::setWeightfilter(Msra* weightfilter)
        {
                ((InnerProductParam*)mParam)->mWeightFilterType = MMALab::MSRA;
                ((InnerProductParam*)mParam)->mWeightFilter = (void*)weightfilter;
        }

	void InnerProductLayer::setBiasfilter(Gaussian* biasfilter)
	{
		((InnerProductParam*)mParam)->mBiasFilterType = MMALab::GAUSSIAN;
		((InnerProductParam*)mParam)->mBiasFilter = (void*)biasfilter;
	}

	void InnerProductLayer::setBiasfilter(Constant* biasfilter)
	{
		((InnerProductParam*)mParam)->mBiasFilterType = MMALab::CONSTANT;
		((InnerProductParam*)mParam)->mBiasFilter = (void*)biasfilter;
	}

	void InnerProductLayer::setBiasfilter(Xavier* biasfilter)
	{
		((InnerProductParam*)mParam)->mBiasFilterType = MMALab::XAVIER;
		((InnerProductParam*)mParam)->mBiasFilter = (void*)biasfilter;
	}

        void InnerProductLayer::setBiasfilter(Uniform* biasfilter)
        {
                ((InnerProductParam*)mParam)->mBiasFilterType = MMALab::UNIFORM;
                ((InnerProductParam*)mParam)->mBiasFilter = (void*)biasfilter;
        }

        void InnerProductLayer::setBiasfilter(Msra* biasfilter)
        {
                ((InnerProductParam*)mParam)->mBiasFilterType = MMALab::MSRA;
                ((InnerProductParam*)mParam)->mBiasFilter = (void*)biasfilter;
        }

	void InnerProductLayer::setAxis(int value)
	{
		((InnerProductParam*)mParam)->mAxis = value;
	}	

	uint32 InnerProductLayer::getNumOutput()
	{
		return ((InnerProductParam*)mParam)->mNumOutput;
	}

	bool InnerProductLayer::getBiasTerm()
	{
		return ((InnerProductParam*)mParam)->mBiasTerm;
	}

	void* InnerProductLayer::getWeightfilter()
	{
		return ((InnerProductParam*)mParam)->mWeightFilter;
	}

	void* InnerProductLayer::getBiasfilter()
	{
		return ((InnerProductParam*)mParam)->mBiasFilter;
	}	

	int InnerProductLayer::getAxis()
	{
		return ((InnerProductParam*)mParam)->mAxis;
	}

	FilterType InnerProductLayer::getWeightfilterType()
	{
		return ((InnerProductParam*)mParam)->mWeightFilterType;
	}

	FilterType InnerProductLayer::getBiasfilterType()
	{
		return ((InnerProductParam*)mParam)->mBiasFilterType;
	}

	void InnerProductLayer::setWeightfilterToNone()
	{
		((InnerProductParam*)mParam)->mWeightFilterType = FilterType::NONE;
		((InnerProductParam*)mParam)->mWeightFilter = NULL;
	}

	void InnerProductLayer::setBiasfilterToNone()
	{
		((InnerProductParam*)mParam)->mBiasFilterType = FilterType::NONE;
		((InnerProductParam*)mParam)->mBiasFilter = NULL;
	}

	string InnerProductLayer::convet2CaffeFormat()
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

		string filterLRDecayMultStrStart = "\tparam {";
		string filterLRDecayMultStrEnd  = " }\n";

		string biasLRDecayMultStrStart = "\tparam {";
		string biaseLRDecayMultStrEnd  = " }\n";
		
                string InnerProductParamStrStart = "\tinner_product_param\n\t{\n";
		string InnerProductParamStrEnd = "\t}\n";

		string numOutputStrStart = "\t\tnum_output: ";
		string numOutputStrEnd = "\n";		

		string weightFillerStrStart = "\t\tweight_filler\n\t\t{\n\t\t\ttype:\"";
		string weightFillerStrEnd = "\n\t\t}\n";

		string biasFillerStrStart = "\t\tbias_filler\n\t\t{\n\t\t\ttype:\"";
		string biasFillerStrEnd = "\n\t\t}\n";

                string biasTermStrStart = "\t\tbias_term: ";
		string biasTermStrEnd = "\n";		

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

		if((mFilterLRateMult != -INT_MAX) && (mFilterDecayMult != -INT_MAX))
		{
			string temp1 = " lr_mult: ";
			string temp2 = " decay_mult: ";

			outStr = outStr + filterLRDecayMultStrStart + temp1 + to_string(mFilterLRateMult) 
														+ temp2 + to_string(mFilterDecayMult) + filterLRDecayMultStrEnd;
		}

		if((mBiasLRateMult != -INT_MAX) && (mBiasDecayMult != -INT_MAX))
		{
			string temp1 = " lr_mult: ";
			string temp2 = " decay_mult: ";

			outStr = outStr + biasLRDecayMultStrStart + temp1 + to_string(mBiasLRateMult) 
												      + temp2 + to_string(mBiasDecayMult) + biaseLRDecayMultStrEnd;
		}

		outStr = outStr +
				 InnerProductParamStrStart +
				 numOutputStrStart         + to_string(getNumOutput()) + numOutputStrEnd;

		if(getBiasTerm() != true)
		{
			outStr = outStr + biasTermStrStart + "false" + biasTermStrEnd;
		}
		
		switch (((InnerProductParam*)mParam)->mWeightFilterType)
		{
			case MMALab::GAUSSIAN:
			{
				string temp1 = "\"\n\t\t\tstd: ";
				string temp2 = "\n\t\t\tmean: ";
                                string temp3 = "\n\t\t\tsparse: ";
				Gaussian* filter = (Gaussian*)getWeightfilter();

				outStr = outStr + weightFillerStrStart + filter->mName 
								+ temp1 + to_string(filter->mStd) 
                                                                + temp2 + to_string(filter->mMean)
                                                                + temp3 + to_string(filter->mSparse)
								+ weightFillerStrEnd;
				break;
			}

			case MMALab::CONSTANT:
			{
				string temp1 = "\"\n\t\t\tvalue: ";
                                //string temp2 = "\n\t\t\tsparse: ";
				Constant* filter = (Constant*)getWeightfilter();

				outStr = outStr + weightFillerStrStart + filter->mName 
                                                                + temp1 + to_string(filter->mValue)
                                                                //+ temp2 + to_string(filter->mSparse)
								+ weightFillerStrEnd;
				break;
			}
				break;

			case MMALab::XAVIER:
			{
                                //string temp1 = "\"\n\t\t\tsparse: ";
                                string temp2 = "\"\n\t\t\tstd: ";
                                string temp3 = "\n\t\t\tvariance_norm: ";
				Xavier* filter = (Xavier*)getWeightfilter();

				outStr = outStr + weightFillerStrStart + filter->mName 
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
                                outStr = outStr + weightFillerStrEnd;
				break;
			}
				break;

                        case MMALab::UNIFORM:
                        {
                            string temp1 = "\"\n\t\t\tmin: ";
                            string temp2 = "\n\t\t\tmax: ";
                            //string temp3 = "\n\t\t\tsparse: ";
                            Uniform* filter = (Uniform*)getWeightfilter();

                            outStr = outStr + weightFillerStrStart + filter->mName
                                                    + temp1 + to_string(filter->mMin)
                                                    + temp2 + to_string(filter->mMax)
                                                    //+ temp3 + to_string(filter->mSparse)
                                                    + weightFillerStrEnd;
                            break;
                        }
                            break;

                        case MMALab::MSRA:
                        {
                             string temp1 = "\n\t\t\tvariance_norm: ";
                             Msra* filter = (Msra*)getWeightfilter();

                             outStr = outStr + weightFillerStrStart + filter->mName + "\"";
                             if(filter->mVarianceNorm!=MMALab::FAN_IN)
                             {
                                 switch(filter->mVarianceNorm)
                                 {
                                     case MMALab::FAN_OUT: outStr = outStr + temp1 + "FAN_OUT";break;
                                     case MMALab::AVERAGE: outStr = outStr + temp1 + "AVERAGE";break;
                                 }
                             }
                             outStr = outStr + biasFillerStrEnd;
                             break;
                        }
                            break;

			default:
				break;
		}


		switch (((InnerProductParam*)mParam)->mBiasFilterType)
		{
			case MMALab::GAUSSIAN:
			{
				string temp1 = "\"\n\t\t\tstd: ";
				string temp2 = "\n\t\t\tmean: ";
                                string temp3 = "\n\t\t\tsparse: ";
				Gaussian* filter = (Gaussian*)getBiasfilter();

				outStr = outStr + biasFillerStrStart + filter->mName 
								+ temp1 + to_string(filter->mStd) 
                                                                + temp2 + to_string(filter->mMean)
                                                                + temp3 + to_string(filter->mSparse)
								+ biasFillerStrEnd;
				break;
			}

			case MMALab::CONSTANT:
			{
				string temp1 = "\"\n\t\t\tvalue: ";
                                //string temp2 = "\n\t\t\tsparse: ";
				Constant* filter = (Constant*)getBiasfilter();

				outStr = outStr + biasFillerStrStart + filter->mName 
								+ temp1 + to_string(filter->mValue) 
                                                                //+ temp2 + to_string(filter->mSparse)
								+ biasFillerStrEnd;
				break;
			}
				break;

			case MMALab::XAVIER:
			{
                                //string temp1 = "\"\n\t\t\tsparse: ";
                                string temp2 = "\"\n\t\t\tstd: ";
                                string temp3 = "\n\t\t\tvariance_norm: ";
				Xavier* filter = (Xavier*)getBiasfilter();

				outStr = outStr + biasFillerStrStart + filter->mName 
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
                                outStr = outStr + biasFillerStrEnd;
				break;
			}
				break;

                        case MMALab::UNIFORM:
                        {
                            string temp1 = "\"\n\t\t\tmin: ";
                            string temp2 = "\n\t\t\tmax: ";
                            //string temp3 = "\n\t\t\tsparse: ";
                            Uniform* filter = (Uniform*)getBiasfilter();

                            outStr = outStr + biasFillerStrStart + filter->mName
                                            + temp1 + to_string(filter->mMin)
                                            + temp2 + to_string(filter->mMax)
                                            //+ temp3 + to_string(filter->mSparse)
                                            + biasFillerStrEnd;
                            break;
                        }
                            break;
                        case MMALab::MSRA:
                        {
                            string temp1 = "\n\t\t\tvariance_norm: ";
                            Msra* filter = (Msra*)getBiasfilter();

                            outStr = outStr + biasFillerStrStart + filter->mName + "\"";
                            if(filter->mVarianceNorm!=MMALab::FAN_IN)
                            {
                                switch(filter->mVarianceNorm)
                                {
                                    case MMALab::FAN_OUT: outStr = outStr + temp1 + "FAN_OUT";break;
                                    case MMALab::AVERAGE: outStr = outStr + temp1 + "AVERAGE";break;
                                }
                            }
                            outStr = outStr + biasFillerStrEnd;
                            break;
                        }
                            break;

			default:
				break;
		}

		outStr = outStr + InnerProductParamStrEnd;

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
