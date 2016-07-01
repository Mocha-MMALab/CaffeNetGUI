#include "BaseLayer.h"
#include "VisionLayers.h"
#include <limits>
#include <climits>
#include <iostream>
using namespace std;
using namespace MMALab;

namespace MMALab
{
	ConvolutionLayer::ConvolutionLayer(string name)
	{
		mName = name;
		mType = MMALab::CONVOLUTION;		
		mParam = new ConvolutionParam();

		//learning rate and decay multipliers for the filters
		mFilterLRateMult = 1;
		mFilterDecayMult = 1;

		//learning rate and decay multipliers for the biases
		mBiasLRateMult = 1;
		mBiasDecayMult = 1;
	}
	ConvolutionLayer::ConvolutionLayer()
	{
		mType = MMALab::CONVOLUTION;		
		mParam = new ConvolutionParam();

		//learning rate and decay multipliers for the filters
		mFilterLRateMult = 1;
		mFilterDecayMult = 1;

		//learning rate and decay multipliers for the biases
		mBiasLRateMult = 1;
		mBiasDecayMult = 1;
	}


	ConvolutionLayer::~ConvolutionLayer()
	{
	
	}

        void ConvolutionLayer::setNumOutput(uint32 value)
	{
		((ConvolutionParam*)mParam)->mNumOutput = value;	
	}

        void ConvolutionLayer::setKernelSize(uint32 value)
	{
		((ConvolutionParam*)mParam)->mKernelSize = value;
	}

	void ConvolutionLayer::setWeightfilter(Gaussian* weightfilter)
	{
		((ConvolutionParam*)mParam)->mWeightfilterType = MMALab::GAUSSIAN;
		((ConvolutionParam*)mParam)->mWeightfilter = (void*)weightfilter;
	}

	void ConvolutionLayer::setWeightfilter(Constant* weightfilter)
	{
		((ConvolutionParam*)mParam)->mWeightfilterType = MMALab::CONSTANT;
		((ConvolutionParam*)mParam)->mWeightfilter = (void*)weightfilter;
	}

	void ConvolutionLayer::setWeightfilter(Xavier* weightfilter)
	{
		((ConvolutionParam*)mParam)->mWeightfilterType = MMALab::XAVIER;
		((ConvolutionParam*)mParam)->mWeightfilter = (void*)weightfilter;
	}

        void ConvolutionLayer::setWeightfilter(Uniform* weightfilter)
        {
                ((ConvolutionParam*)mParam)->mWeightfilterType = MMALab::UNIFORM;
                ((ConvolutionParam*)mParam)->mWeightfilter = (void*)weightfilter;
        }

        void ConvolutionLayer::setWeightfilter(Msra* weightfilter)
        {
                ((ConvolutionParam*)mParam)->mWeightfilterType = MMALab::MSRA;
                ((ConvolutionParam*)mParam)->mWeightfilter = (void*)weightfilter;
        }

	void ConvolutionLayer::setBiasfilter(Gaussian* biasfilter)
	{
		((ConvolutionParam*)mParam)->mBiasfilterType = MMALab::GAUSSIAN;
		((ConvolutionParam*)mParam)->mBiasfilter = (void*)biasfilter;
	}

        void ConvolutionLayer::setBiasfilter(Constant* biasfilter)
        {
                ((ConvolutionParam*)mParam)->mBiasfilterType = MMALab::CONSTANT;
                ((ConvolutionParam*)mParam)->mBiasfilter = (void*)biasfilter;
        }

        void ConvolutionLayer::setBiasfilter(Xavier* biasfilter)
        {
                ((ConvolutionParam*)mParam)->mBiasfilterType = MMALab::XAVIER;
                ((ConvolutionParam*)mParam)->mBiasfilter = (void*)biasfilter;
        }

        void ConvolutionLayer::setBiasfilter(Uniform* biasfilter)
        {
                ((ConvolutionParam*)mParam)->mBiasfilterType = MMALab::UNIFORM;
                ((ConvolutionParam*)mParam)->mBiasfilter = (void*)biasfilter;
        }

        void ConvolutionLayer::setBiasfilter(Msra* biasfilter)
        {
                ((ConvolutionParam*)mParam)->mBiasfilterType = MMALab::MSRA;
                ((ConvolutionParam*)mParam)->mBiasfilter = (void*)biasfilter;
        }

	void ConvolutionLayer::setBiasTerm(bool biasTerm)
	{
		((ConvolutionParam*)mParam)->mBiasTerm = biasTerm;
	}

        void ConvolutionLayer::setPad(uint32 value)
	{
		((ConvolutionParam*)mParam)->mPad = value;
	}

        void ConvolutionLayer::setGroup(uint32 value)
	{
		((ConvolutionParam*)mParam)->mGroup = value;
	}

	void ConvolutionLayer::setEngine(Engine type)
	{
		((ConvolutionParam*)mParam)->mEngine = type;
	}

        void ConvolutionLayer::setStride(uint32 value)
	{
		((ConvolutionParam*)mParam)->mStride = value;
	}

        uint32 ConvolutionLayer::getNumOutput()
	{
		return ((ConvolutionParam*)mParam)->mNumOutput;
	}

        uint32 ConvolutionLayer::getKernelSize()
	{
		return ((ConvolutionParam*)mParam)->mKernelSize;
	}

	void* ConvolutionLayer::getWeightfilter()
	{
		return ((ConvolutionParam*)mParam)->mWeightfilter;
	}

	void* ConvolutionLayer::getBiasfilter()
	{
		return ((ConvolutionParam*)mParam)->mBiasfilter;
	}

	bool ConvolutionLayer::getBiasTerm()
	{
		return ((ConvolutionParam*)mParam)->mBiasTerm;
	}

        uint32 ConvolutionLayer::getPad()
	{
		return ((ConvolutionParam*)mParam)->mPad;
	}

        uint32 ConvolutionLayer::getGroup()
	{
		return ((ConvolutionParam*)mParam)->mGroup;
	}

	Engine ConvolutionLayer::getEngine()
	{
		return ((ConvolutionParam*)mParam)->mEngine;
	}

        uint32 ConvolutionLayer::getStride()
	{
		return ((ConvolutionParam*)mParam)->mStride;
	}

	//set learning rate and decay multipliers for the filters
	void ConvolutionLayer::setFilterLRDecayMult(float lr, float decay)
	{
		mFilterLRateMult = lr;
		mFilterDecayMult = decay;
	}
	//set learning rate and decay multipliers for the biases
	void ConvolutionLayer::setBiasLRDecayMult(float lr, float decay)
	{
		mBiasLRateMult = lr;
		mBiasDecayMult = decay;
	}

	FilterType ConvolutionLayer::getWeightfilterType()
	{
		return ((ConvolutionParam*)mParam)->mWeightfilterType;
	}

	FilterType ConvolutionLayer::getBiasfilterType()
	{
		return ((ConvolutionParam*)mParam)->mBiasfilterType;
	}

	void ConvolutionLayer::setWeightfilterToNone()
	{
		((ConvolutionParam*)mParam)->mWeightfilterType = FilterType::NONE;
		((ConvolutionParam*)mParam)->mWeightfilter = NULL;
	}

	void ConvolutionLayer::setBiasfilterToNone()
	{
		((ConvolutionParam*)mParam)->mBiasfilterType = FilterType::NONE;
		((ConvolutionParam*)mParam)->mBiasfilter = NULL;
	}

	string ConvolutionLayer::convet2CaffeFormat()
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
		
		string ConvolutionParamStrStart = "\tconvolution_param\n\t{\n";
		string ConvolutionParamStrEnd = "\t}\n";

		string numOutputStrStart = "\t\tnum_output: ";
		string numOutputStrEnd = "\n";

		string padStrStart = "\t\tpad: ";
		string padStrEnd  = "\n";

		string kernelSizeStrStart = "\t\tkernel_size: ";
		string kernelSizeStrEnd = "\n";

		string strideStrStart = "\t\tstride: ";
		string strideStrEnd = "\n";

		string biasTermStrStart = "\t\tbias_term: ";
		string biasTermStrEnd = "\n";

		string groupStrStart = "\t\tgroup: ";
		string groupStrEnd = "\n";

		string engineStrStart = "\t\tengine: ";
		string engineStrEnd = "\n";

		string weightFillerStrStart = "\t\tweight_filler\n\t\t{\n\t\t\ttype:\"";
		string weightFillerStrEnd = "\n\t\t}\n";

		string biasFillerStrStart = "\t\tbias_filler\n\t\t{\n\t\t\ttype:\"";
		string biasFillerStrEnd = "\n\t\t}\n";

		string phaseStrStart = "\tinclude:\n\t{\n";		
		string phaseStrEnd = "\t}\n";

		string phaseStateStrStart = "\t\tphase: ";
		string phaseStateStrEnd = "\n";

		string outStr = layerStrStart +
						nameStrStart + getLayerName() + nameStrEnd +
						typeStrStart + getLayerType() + typeStrEnd;
		
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
				 ConvolutionParamStrStart +
				 numOutputStrStart  + to_string(getNumOutput())  + numOutputStrEnd;

		if (getBiasTerm() == false)
		{
			outStr = outStr + biasTermStrStart + "false" + biasTermStrEnd;
		}

		if (getPad() != 0)
		{
			outStr += padStrStart + to_string(getPad()) + padStrEnd;
		}

		outStr += kernelSizeStrStart + to_string(getKernelSize()) + strideStrEnd;
				 
		if (getGroup() != 1)
		{
			outStr += groupStrStart + to_string(getGroup()) + groupStrEnd;
		}

		if (getStride() != 1)
		{
			outStr += strideStrStart + to_string(getStride()) + kernelSizeStrEnd;
		}

		
		
		switch (((ConvolutionParam*)mParam)->mWeightfilterType)
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

                                if(filter->mVarianceNorm!=MMALab::VarianceNorm::FAN_IN)
                                {
                                    switch(filter->mVarianceNorm)
                                    {
                                        case MMALab::VarianceNorm::FAN_OUT: outStr = outStr + temp3 + "FAN_OUT";break;
                                        case MMALab::VarianceNorm::AVERAGE: outStr = outStr + temp3 + "AVERAGE";break;
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
                            if(filter->mVarianceNorm!=MMALab::VarianceNorm::FAN_IN)
                            {
                                switch(filter->mVarianceNorm)
                                {
                                    case MMALab::VarianceNorm::FAN_OUT: outStr = outStr + temp1 + "FAN_OUT";break;
                                    case MMALab::VarianceNorm::AVERAGE: outStr = outStr + temp1 + "AVERAGE";break;
                                }
                            }
                            outStr = outStr + biasFillerStrEnd;
                            break;
                        }
                        break;
		default:
			break;
		}

		switch (((ConvolutionParam*)mParam)->mBiasfilterType)
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

                                if(filter->mVarianceNorm!=MMALab::VarianceNorm::FAN_IN)
                                {
                                    switch(filter->mVarianceNorm)
                                    {
                                        case MMALab::VarianceNorm::FAN_OUT: outStr = outStr + temp3 + "FAN_OUT";break;
                                    case MMALab::VarianceNorm::AVERAGE: outStr = outStr + temp3 + "AVERAGE";break;
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
                            if(filter->mVarianceNorm!=MMALab::VarianceNorm::FAN_IN)
                            {
                                switch(filter->mVarianceNorm)
                                {
                                    case MMALab::VarianceNorm::FAN_OUT: outStr = outStr + temp1 + "FAN_OUT";break;
                                    case MMALab::VarianceNorm::AVERAGE: outStr = outStr + temp1 + "AVERAGE";break;
                                }
                            }
                            outStr = outStr + biasFillerStrEnd;
                            break;
                        }
                        break;
		default:
			break;
		}

		if (getEngine() != MMALab::DEFAULT)
		{
			switch (getEngine())
			{
			case MMALab::CAFFE:
					outStr += engineStrStart + "CAFFE" + engineStrEnd;
					break;
			case MMALab::CUDNN:
					outStr += engineStrStart + "CUDNN" + engineStrEnd;
					break;
			}
		}

		outStr = outStr + ConvolutionParamStrEnd;

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
