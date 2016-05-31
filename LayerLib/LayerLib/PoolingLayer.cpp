#include "BaseLayer.h"
#include "VisionLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	PoolingLayer::PoolingLayer(string name)
	{
		mName = name;
		mType = MMALab::POOLING;		
		mParam = new PoolingParam();
	}

	PoolingLayer::PoolingLayer()
	{
		mType = MMALab::POOLING;		
		mParam = new PoolingParam();
	}

	PoolingLayer::~PoolingLayer()
	{
		
	}

	void PoolingLayer::setKernelSize(uint32 value)
	{
		((PoolingParam*)mParam)->mKernelSize = value;
	}
	/*void PoolingLayer::setKernelH(uint32 value)
	{
		((PoolingParam*)mParam)->mKernelH = value;
	}
	void PoolingLayer::setKernelW(uint32 value)
	{
		((PoolingParam*)mParam)->mKernelW = value;
	}*/

	void PoolingLayer::setPad(uint32 value)
	{
		((PoolingParam*)mParam)->mPad = value;
	}
	/*void PoolingLayer::setPadH(uint32 value)
	{
		((PoolingParam*)mParam)->mPadH = value;
	}
	void PoolingLayer::setPadW(uint32 value)
	{
		((PoolingParam*)mParam)->mPadW = value;
	}*/

	void PoolingLayer::setStride(uint32 value)
	{
		((PoolingParam*)mParam)->mStride = value;
	}
	/*void PoolingLayer::setStrideH(uint32 value)
	{
		((PoolingParam*)mParam)->mStrideH = value;
	}
	void PoolingLayer::setStrideW(uint32 value)
	{
		((PoolingParam*)mParam)->mStrideW = value;
	}*/

	void PoolingLayer::setPool(PoolMethod method)
	{
		((PoolingParam*)mParam)->mPool = method;
	}

	void PoolingLayer::setEngine(Engine type)
	{
		((PoolingParam*)mParam)->mEngine = type;
	}

	void PoolingLayer::setGlobalPooling(bool state)
	{
		((PoolingParam*)mParam)->mGlobalPooling = state;
	}


	PoolMethod PoolingLayer::getPool()
	{
		return ((PoolingParam*)mParam)->mPool;
	}	

	bool PoolingLayer::getGlobalPooling()
	{
		return ((PoolingParam*)mParam)->mGlobalPooling;
	}	

	Engine PoolingLayer::getEngine()
	{
		return ((PoolingParam*)mParam)->mEngine;
	}


	uint32 PoolingLayer::getKernelSize()
	{
		return ((PoolingParam*)mParam)->mKernelSize;
	}
	/*uint32 PoolingLayer::getKernelH()
	{
		return ((PoolingParam*)mParam)->mKernelH;
	}
	uint32 PoolingLayer::getKernelW()
	{
		return ((PoolingParam*)mParam)->mKernelW;
	}*/
	
	uint32 PoolingLayer::getPad()
	{
		return ((PoolingParam*)mParam)->mPad;
	}
	/*uint32 PoolingLayer::getPadH()
	{
		return ((PoolingParam*)mParam)->mPadH;
	}
	uint32 PoolingLayer::getPadW()
	{
		return ((PoolingParam*)mParam)->mPadW;
	}*/

	uint32 PoolingLayer::getStride()
	{
		return ((PoolingParam*)mParam)->mStride; 
	}
	/*uint32 PoolingLayer::getStrideH()
	{
		return ((PoolingParam*)mParam)->mStrideH; 
	}
	uint32 PoolingLayer::getStrideW()
	{
		return ((PoolingParam*)mParam)->mStrideW; 
	}*/

	string PoolingLayer::convet2CaffeFormat()
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

		string poolingParamStrStart = "\tpooling_param\n\t{\n";
		string poolingParamStrEnd = "\t}\n";

		string kernelSizeStrStart = "\t\tkernel_size: ";
		string kernelSizeStrEnd = "\n";

		/*string kernelHStrStart = "\t\tkernel_h: ";
		string kernelHStrEnd = "\n";

		string kernelWStrStart = "\t\tkernel_w: ";
		string kernelWStrEnd = "\n";*/

		string strideStrStart = "\t\tstride: ";
		string strideStrEnd = "\n";
		/*string strideHStrStart = "\t\tstride_h: ";
		string strideHStrEnd = "\n";
		string strideWStrStart = "\t\tstride_w: ";
		string strideWStrEnd = "\n";*/

		string padStrStart = "\t\tpad: ";
		string padStrEnd = "\n";
		/*string padHStrStart = "\t\tpad_h: ";
		string padHStrEnd = "\n";
		string padWStrStart = "\t\tpad_w: ";
		string padWStrEnd = "\n";*/

		string poolStrStart = "\t\tpool: ";
		string poolStrEnd = "\n";

		string engineStrStart = "\t\tengine: ";
		string engineStrEnd = "\n";

		string globalPoolingStrStart = "\t\tglobal_pooling: ";
		string globalPoolingStrEnd = "\n";

		string phaseStrStart = "\tinclude:\n\t{\n";		
		string phaseStrEnd = "\t}\n";

		string phaseStateStrStart = "\t\tphase: ";
		string phaseStateStrEnd = "\n";

		string outStr = layerStrStart+
						nameStrStart + mName + nameStrEnd + 
						typeStrStart + getLayerType() + typeStrEnd;

		for(size_t i = 0; i < mTops->size(); i++)
		{
			outStr = outStr + topStrStart + (*mTops)[i] + topStrEnd;
		}

		for(size_t i = 0; i < mBottoms->size(); i++)
		{
			outStr = outStr + bottomStrStart + (*mBottoms)[i] + bottomStrEnd;
		}

		outStr += poolingParamStrStart;	



		if (((PoolingParam*)mParam)->mPool != MMALab::POOLMETHOD_MAX)

		{
			switch (((PoolingParam*)mParam)->mPool)
			{
			case MMALab::POOLMETHOD_AVE:
				outStr += poolStrStart + "AVE" + poolStrEnd;
				break;
			case MMALab::POOLMETHOD_STOCHASTIC:
				outStr += poolStrStart + "STOCHASTIC" + poolStrEnd;
				break;
			}
		}

		if (((PoolingParam*)mParam)->mPad != 0)
		{
			outStr += padStrStart + to_string(getPad()) + padStrEnd;
		}
		/*if (((PoolingParam*)mParam)->mPadH != 0)
		{
			outStr += padHStrStart + to_string(getPadH()) + padHStrEnd;
		}
		if (((PoolingParam*)mParam)->mPadW != 0)
		{
			outStr += padWStrStart + to_string(getPadW()) + padWStrEnd;
		}*/

		outStr += kernelSizeStrStart   + to_string(getKernelSize()) + kernelSizeStrEnd;
		/*outStr += kernelHStrStart   + to_string(getKernelH()) + kernelHStrEnd;
		outStr += kernelWStrStart   + to_string(getKernelW()) + kernelWStrEnd;*/

		if (((PoolingParam*)mParam)->mStride != 1)
		{
			outStr += strideStrStart + to_string(getStride()) + strideStrEnd;
		}
		/*if (((PoolingParam*)mParam)->mStrideH != 1)
		{
			outStr += strideHStrStart + to_string(getStrideH()) + strideHStrEnd;
		}
		if (((PoolingParam*)mParam)->mStrideW != 1)
		{
			outStr += strideWStrStart + to_string(getStrideW()) + strideWStrEnd;
		}*/

		if (((PoolingParam*)mParam)->mEngine != MMALab::DEFAULT)
		{
			switch (((PoolingParam*)mParam)->mEngine)
			{
			case MMALab::CAFFE:
				outStr += engineStrStart + "CAFFE" + engineStrEnd;
				break;

			case MMALab::CUDNN:
				outStr += engineStrStart + "CUDNN" + engineStrEnd;
				break;
			}
		}

		if (((PoolingParam*)mParam)->mGlobalPooling != false)
		{
			outStr += globalPoolingStrStart + "true" + globalPoolingStrEnd;
		}

		outStr += poolingParamStrEnd;		
				
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
