#include "BaseLayer.h"
#include "CommonLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	ReshapeLayer::ReshapeLayer(string name)
	{
		mName = name;
		mType = MMALab::RESHPAE;		
		mParam = new ReshapeParam();
	}

	ReshapeLayer::ReshapeLayer()
	{
		mType = MMALab::RESHPAE;		
		mParam = new ReshapeParam();
	}

	ReshapeLayer::~ReshapeLayer()
	{
		 
        }

        void ReshapeLayer::setShape(BlobShape* shape)
        {
            ((ReshapeParam*)mParam)->mShape = (void*)shape;
        }

	void ReshapeLayer::setAxis(int value)
	{
		((ReshapeParam*)mParam)->mAxis = value;
	}

	void ReshapeLayer::setNumAxis(int value)
	{
		((ReshapeParam*)mParam)->mNumAxis = value;
	}

        void* ReshapeLayer::getShape()
	{
		return ((ReshapeParam*)mParam)->mShape;
	}

	int ReshapeLayer::getAxis()
	{
		return ((ReshapeParam*)mParam)->mAxis;
	}

	int ReshapeLayer::getNumAxis()
	{
		return ((ReshapeParam*)mParam)->mNumAxis;
        }

	string ReshapeLayer::convet2CaffeFormat()
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

		string reshapeParamStrStart = "\treshape_param\n\t{\n";
		string reshapeParamStrEnd = "\t}\n";

                string shapeStrStart = "\t\tshape: {";
                string shapeStrEnd = " }\n";

		string axisStrStart = "\t\taxis: ";
		string axisStrEnd = "\n";

		string numAxisStrStart = "\t\tnum_axis: ";
		string numAxisStrEnd = "\n";

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

		outStr = outStr + 
			     reshapeParamStrStart ;
                                 //shapeStrStart + getShape() + shapeStrEnd ;

                if(((ReshapeParam*)mParam)->mShape != NULL)
                {
                    BlobShape* shape = (BlobShape*)getShape();
                    for(int i = 0; i < shape->mShape.size(); i++)
                    {
                        outStr = outStr + shapeStrStart;
                        for(int j = 0; j < shape->mShape.at(i).size(); j++)
                        {
                            outStr = outStr +  " dim: " + to_string(shape->mShape.at(i).at(j));
                        }
                        outStr = outStr + shapeStrEnd;
                    }
                }

		if(((ReshapeParam*)mParam)->mAxis != 0)
		{
			 outStr += axisStrStart + to_string(getAxis()) + axisStrEnd;
		}
		
		if(((ReshapeParam*)mParam)->mNumAxis != -1)
		{
			outStr += numAxisStrStart + to_string(getNumAxis()) + numAxisStrEnd;
		}

		outStr += reshapeParamStrEnd;
				 
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
