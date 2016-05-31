#include "BaseLayer.h"
#include "DataLayers.h"
#include <iostream>
using namespace std;
using namespace MMALab;

namespace MMALab
{
	DummyDataLayer::DummyDataLayer(string name)
	{
		mName = name;
		mType = MMALab::DUMMYDATA;	
		mParam = new DummyDataParam();
	}

	DummyDataLayer::DummyDataLayer()
	{
		mType = MMALab::DUMMYDATA;		
		mParam = new DummyDataParam();
	}

	DummyDataLayer::~DummyDataLayer()
	{
		
	}

	void DummyDataLayer::setDataFiller(FillerParameter type)
	{
		((DummyDataParam*)mParam)->mDataFiller = type;
	}

        void DummyDataLayer::setShape(BlobShape* shape)
	{
		((DummyDataParam*)mParam)->mShape = shape;
	}

        void DummyDataLayer::setNum(uint32 value)
	{
		((DummyDataParam*)mParam)->mNum  = value;
	}

        void DummyDataLayer::setChannels(uint32 value)
	{
		((DummyDataParam*)mParam)->mChannels = value;
	}

        void DummyDataLayer::setHeight(uint32 value)
	{
		((DummyDataParam*)mParam)->mHeight = value;
	}

        void DummyDataLayer::setWidth(uint32 value)
	{
		((DummyDataParam*)mParam)->mWidth = value;
	}

	FillerParameter DummyDataLayer::getDataFiller()
	{
		return ((DummyDataParam*)mParam)->mDataFiller;
	}

	void* DummyDataLayer::getShape()
	{
		return ((DummyDataParam*)mParam)->mShape;
	}

        uint32 DummyDataLayer::getNum()
	{
		return ((DummyDataParam*)mParam)->mNum;
	}

        uint32 DummyDataLayer::getChannels()
	{
		return ((DummyDataParam*)mParam)->mChannels;
	}

        uint32 DummyDataLayer::getHeigth()
	{
		return ((DummyDataParam*)mParam)->mHeight;
	}

        uint32 DummyDataLayer::getWidth()
	{
		return ((DummyDataParam*)mParam)->mWidth;
	}

	string DummyDataLayer::convet2CaffeFormat()
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

                string dummyDataParamStrStart = "\tdummy_data_param\n\t{\n";
                string dummyDataParamStrEnd = "\t}\n";

                string dataFillerParamStrStart = "\t\tdata_filler\n\t\t{\n";
                string dataFillerParamStrEnd = "\t\t}\n";

                string shapeParamStrStart = "\t\tshape: {";
                string shapeParamStrEnd = " }\n";

                string numParamStrStart = "\t\tnum: ";
                string numParamStrEnd = "\n";

                string channelsParamStrStart = "\t\tchannels: ";
                string channelsParamStrEnd = "\n";

                string heightParamStrStart = "\t\theight: ";
                string heightParamStrEnd = "\n";

                string widthParamStrStart = "\t\twidth: ";
                string widthParamStrEnd = "\n";

		string phaseStrStart = "\tinclude:\n\t{\n";		
		string phaseStrEnd = "\t}\n";

		string phaseStateStrStart = "\t\tphase: ";
		string phaseStateStrEnd = "\n";


		string outStr =  layerStrStart + 
						 nameStrStart + getLayerName() + nameStrEnd + 
						 typeStrStart + getLayerType() + typeStrEnd;

		for(size_t i = 0; i < mTops->size(); i++)
		{
			outStr = outStr + topStrStart + (*mTops)[i] + topStrEnd;
		}

		for(size_t i = 0; i < mBottoms->size(); i++)
		{
			outStr = outStr + bottomStrStart + (*mBottoms)[i] +bottomStrEnd;
		}

                outStr += dummyDataParamStrStart;

		switch (((DummyDataParam*)mParam)->mDataFiller)
		{
		case MMALab::CONSTANTFILLER:
                        outStr += dataFillerParamStrStart;
			outStr += "\t\t\ttype: \"CONSTANT\"\n";
			outStr += "\t\t\tvalue: 0\n";
                        outStr += dataFillerParamStrEnd;
			break;
		
		case MMALab::UNIFORMFILLER:
                        outStr += dataFillerParamStrStart;
			outStr += "\t\t\ttype: \"UNIFORM\"\n";
			outStr += "\t\t\tmin: 0\n";
			outStr += "\t\t\tmax: 1\n";
                        outStr += dataFillerParamStrEnd;
			break;

		case MMALab::GAUSSIANFILLER:
                        outStr += dataFillerParamStrStart;
			outStr += "\t\t\ttype: \"GAUSSIAN\"\n";
			outStr += "\t\t\tmean: 0\n";
			outStr += "\t\t\tstd: 1\n";
			outStr += "\t\t\sparse: -1\n";
			break;
			
		case MMALab::POSITIVEUNITBALLFILLER:
                        outStr += dataFillerParamStrStart + "\t\t\ttype: \"POSITIVEUNITBALL\"\n" + dataFillerParamStrEnd;
			break;

		case MMALab::XAVIERFILLER:
                        outStr += dataFillerParamStrStart + "\t\t\ttype: \"XAVIER\"\n" + dataFillerParamStrEnd;
			break;

		default:
                        outStr += dataFillerParamStrStart + dataFillerParamStrEnd;
		}
		
                if(((DummyDataParam*)mParam)->mShape != NULL)
                {
                    BlobShape* shape = (BlobShape*)getShape();
                    cout << "shape->mShape.size()  is" <<endl;
                    for(int i = 0; i < shape->mShape.size(); i++)
                    {
                        outStr = outStr + shapeParamStrStart;
                        for(int j = 0; j < shape->mShape.at(i).size(); j++)
                        {
                            outStr = outStr +  " dim: " + to_string(shape->mShape.at(i).at(j));
                        }
                        outStr = outStr + shapeParamStrEnd;
                    }
                }

                outStr += /*numParamStrStart + to_string(getNum()) + numParamStrEnd +
                                  channelsParamStrStart + to_string(getChannels()) + channelsParamStrEnd +
                                  heightParamStrStart + to_string(getHeigth()) + heightParamStrEnd +
                                  widthParamStrStart + to_string(getWidth()) + widthParamStrEnd +*/
                                  dummyDataParamStrEnd;

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
