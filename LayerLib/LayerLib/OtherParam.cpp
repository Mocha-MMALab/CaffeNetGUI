#include "LayerParam.h"
#include<iostream>
using namespace std;
using namespace MMALab;

namespace MMALab
{
	Gaussian::Gaussian()
	{
		mName = "gaussian";
		mStd  = 1.00;
		mMean = 0;
		mSparse = -1;
	}

	Gaussian::~Gaussian()
	{
	
	}

	Constant::Constant()
	{
		mName  = "constant";
		mValue = 0;
                //mSparse = -1;
	}

	Constant::~Constant()
	{
	
	}

	Xavier::Xavier()
	{
		mName = "xavier";
		mStd  = 1.00;
		mVarianceNorm = MMALab::VarianceNorm::FAN_IN;
                //mSparse = -1;
	}

	Xavier::~Xavier()
	{
	
	}

	Uniform::Uniform()
	{
		mName = "uniform";
		mMin = 0;
		mMax = 1;
                //mSparse = -1;
	}

	Uniform::~Uniform()
	{

	}

        Msra::Msra()
        {
                mName = "msra";
                mVarianceNorm = MMALab::VarianceNorm::FAN_IN;
        }

        Msra::~Msra()
        {

        }

	BlobProto::BlobProto()
	{
		mNum = 0;
		mChannels = 0;
		mHeight = 0;
		mWidth = 0;
		mData = 0;
		mDiff = 0;
	}

	BlobProto::~BlobProto()
	{
		
	}

	BlobShape::BlobShape()
        {
                mShape.clear();
	}

	BlobShape::~BlobShape()
	{

	}

}
