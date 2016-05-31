#include "BaseLayer.h"
#include "LayerParam.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	BaseLayer::BaseLayer()
	{
		mName = "";
		mTops = new vector<string>();
		mBottoms = new vector<string>();
		mPhase = Phase::BOTH;
	}

	BaseLayer::~BaseLayer()
	{
		delete mTops;
		delete mBottoms;
		delete mParam; 
	}

	void BaseLayer::addTopConnection(DataBlob* blob)
	{
		mTops->push_back(blob->mName);
	}
	void BaseLayer::addTopConnection(DataBlob* blob, string inputName)
	{
		mTops->push_back(inputName);
	} 

	void BaseLayer::addBottomConnection(DataBlob* blob)
	{
		mBottoms->push_back(blob->mName);
	}

	void BaseLayer::removeTopConnection()
	{
		mTops->pop_back();
	}
	void BaseLayer::removeTopConnection(DataBlob* blob)
	{
		int size = (int)mTops->size();
		for(int i = 0; i < size; i++)
		{
			string tempStr = (*mTops)[i];
			if(tempStr.compare(blob->mName) == 0)
			{
				mTops->erase(mTops->begin() + i);
				break;
			}
		}

	}

	void BaseLayer::removeBottomConnection(DataBlob* blob)
	{
		int size = (int)mBottoms->size();
		for(int i = 0; i < size; i++)
		{
			string tempStr = (*mBottoms)[i];
			if(tempStr.compare(blob->mName) == 0)
			{
				mBottoms->erase(mBottoms->begin() + i);
				break;
			}
		}
	}

	void BaseLayer::clearnTopConnection()
	{
		mTops->clear();
	}

	void BaseLayer::clearnBottomConnection()
	{
		mBottoms->clear();
	}

	void BaseLayer::setLayerPhase(Phase state)
	{
		mPhase = state;
	}

	Phase BaseLayer::getLayerPhase()
	{
		return mPhase;
	}

	void BaseLayer::setLayerName(string value)
	{
		mName = value;
	}

	string BaseLayer::getLayerName()
	{
		return mName;
	}

	string BaseLayer::getLayerType()
	{
		string typeName = "";
		switch (mType)
		{
		case MMALab::DATABLOB:
			typeName = "DataBlob";
			break;
		case MMALab::CONVOLUTION:
			typeName = "Convolution";
			break;
		case MMALab::POOLING:
			typeName = "Pooling";
			break;
		case MMALab::SPP:
			typeName = "SPP";
			break;
		case MMALab::LRN:
			typeName = "LRN";
			break;
		case MMALab::CONTRASTIVE_LOSS:
			typeName = "ContrastiveLoss";
			break;
                case MMALab::HINGE_LOSS:
			typeName = "HingeLoss";
			break;
		case MMALab::INFOGAIN_LOSS:
			typeName = "InfogainLoss";
			break;
		case MMALab::EUCLIDEAN_LOSS:
			typeName = "EuclideanLoss";
			break;
		case MMALab::SOFT_MAX_WITH_LOSS:
			typeName = "SoftmaxWithLoss";
			break;
                case MMALab::MULTINOMIAL_LOGISTIC_Loss:
                        typeName = "MultinomialLogisticLoss";
                        break;
                case MMALab::SIGMOID_CROSS_ENTROPY_LOSS:
                        typeName = "SigmoidCrossEntropyLoss";
                        break;
		case MMALab::ACCURACY:
			typeName = "Accuracy";
			break;
		case MMALab::MVN:
			typeName = "MVN";
			break;
		case MMALab::RESHPAE:
			typeName = "Reshape";
			break;
		case MMALab::REDUCTION:
			typeName = "Reduction";
			break;
		case MMALab::SLICE:
			typeName = "Slice";
			break;
		case MMALab::SOFTMAX:
			typeName = "Softmax";
			break;
		case MMALab::INNER_PRODUCT:
			typeName = "InnerProduct";
			break;
		case MMALab::FLATTEN:
			typeName = "Flatten";
			break;
		case MMALab::ELTWISE:
			typeName = "Eltwise";
			break;
		case MMALab::CONCAT:
			typeName = "Concat";
			break;
		case MMALab::ARGMAX:
			typeName = "Argmax";
			break;
		case MMALab::PRELU:
			typeName = "PReLU";
			break;
		case MMALab::THRESHOLD:
			typeName = "Threshold";
			break;
		case MMALab::TANH:
			typeName = "TanH";
			break;
		case MMALab::SIGMOID:
			typeName = "Sigmoid";
			break;
		case MMALab::RELU:
			typeName = "ReLU";
			break;
		case MMALab::POWER:
			typeName = "Power";
			break;
		case MMALab::DROPOUT:
			typeName = "Dropout";
			break;
		case MMALab::EXP:
			typeName = "Exp";
			break;
		case MMALab::LOG:
			typeName = "Log";
			break;
		case MMALab::ABSVAL:
			typeName = "AbsVal";
			break;
		case MMALab::BNLL:
			typeName = "BNLL";
			break;
		case MMALab::DUMMYDATA:
			typeName = "DummyData";
			break;
		case MMALab::HDF5_OUTPUT:
			typeName = "HDF5Output";
			break;
		case MMALab::HDF5_DATA:
			typeName = "HDF5Data";
			break;
		case MMALab::WINDOW_DATA:
			typeName = "WindowData";
			break;
		case MMALab::IMAGE_DATA:
			typeName = "ImageData";
			break;
		case MMALab::DATA:
			typeName = "Data";
			break;
		case MMALab::MEMORY_DATA:
			typeName = "MemoryData";
			break;			
		default:
			break;
		}
		return typeName;
	}

}
