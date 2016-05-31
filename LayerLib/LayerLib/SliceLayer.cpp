#include "BaseLayer.h"
#include "CommonLayers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	SliceLayer::SliceLayer(string name)
	{
		mName = name;
		mType = MMALab::SLICE;		
		mParam = new SliceParam();
	}

	SliceLayer::SliceLayer()
	{
		mType = MMALab::SLICE;		
		mParam = new SliceParam();
	}

	SliceLayer::~SliceLayer()
	{
		
	}

	void SliceLayer::setAxis(int value)
	{
		((SliceParam*)mParam)->mAxis = value;
	}

        void SliceLayer::setSlicePoint(uint32 value)
	{
		((SliceParam*)mParam)->mSlicePoint = value;
	}

        void SliceLayer::setSliceDim(uint32 value)
	{
		((SliceParam*)mParam)->mSliceDim = value;
	}

	int SliceLayer::getAxis()
	{
		return ((SliceParam*)mParam)->mAxis;
	}

        uint32 SliceLayer::getSlicePoint()
	{
		return ((SliceParam*)mParam)->mSlicePoint;
	}

        uint32 SliceLayer::getSliceDim()
	{
		return ((SliceParam*)mParam)->mSliceDim;
	}

	string SliceLayer::convet2CaffeFormat()
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

		string sliceParamStrStart = "\tslice_param\n\t{\n";
		string sliceParamStrEnd = "\t}\n";

		string axisStrStart = "\t\taxis: ";
		string axisStrEnd = "\n";

		string slicePointStrStart = "\t\tslice_point: ";
		string slicePointStrEnd = "\n";	

		string sliceDimStrStart = "\t\tslice_dim: ";
		string sliceDimStrEnd = "\n";

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
			     sliceParamStrStart ;

		if(((SliceParam*)mParam)->mAxis != 1)
		{
			outStr += axisStrStart + to_string(getAxis()) + axisStrEnd;
		}
		outStr +=  slicePointStrStart + to_string(getSlicePoint()) + slicePointStrEnd;

		if(((SliceParam*)mParam)->mSliceDim != 1)
		{
			outStr +=  sliceDimStrStart + to_string(getSliceDim()) + sliceDimStrEnd;
		}

		outStr += sliceParamStrEnd;

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
