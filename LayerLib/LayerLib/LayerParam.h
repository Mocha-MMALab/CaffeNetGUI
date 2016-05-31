#ifndef _LAYERPARAM_H
#define _LAYERPARAM_H


#include <string>
#include <vector>
#include <map>

#include "LayerEnum.h"

#ifdef  WIN32
	#ifdef LAYERLIB_EXPORTS
	#define LAYERLIB_API __declspec(dllexport)
	#else
	#define LAYERLIB_API __declspec(dllimport)
	#endif
#else
	#define LAYERLIB_API
#endif

using namespace std;

typedef map<int, int> MapSmall;
typedef map<int, MapSmall> MapBig;
/* @namespace MMALab
 * @MMALab namespace
 */
namespace MMALab
{
#ifdef  WIN32
	//delete warning C4251 
	//template class LAYERLIB_API std::allocator<char>;
	//template class LAYERLIB_API std::basic_string<char>;
#endif

	class LAYERLIB_API Gaussian
	{
	public:
		Gaussian();
		~Gaussian();
		string mName;
		float mStd;
		float mMean;
		int mSparse;
	};

	class LAYERLIB_API Constant
	{
	public:
		Constant();
		~Constant();
		string mName;
		float mValue;
		//int mSparse;
	};

	class LAYERLIB_API Xavier
	{
	public:
		Xavier();
		~Xavier();
		string mName;
		float mStd;
		VarianceNorm mVarianceNorm;
		//int mSparse;
	};

	class LAYERLIB_API Uniform
	{
	public:
		Uniform();
		~Uniform();
		string mName;
		float mMin;
		float mMax;
		//int mSparse;
	};

        class LAYERLIB_API Msra
        {
        public:
                Msra();
                ~Msra();
                string mName;
                VarianceNorm mVarianceNorm;
        };

	class LAYERLIB_API BlobProto
	{
	public:
		BlobProto();
		~BlobProto();
		int mNum;
		int mChannels;
		int mHeight;
		int mWidth;
		float mData;
		float mDiff;
	};

        class LAYERLIB_API BlobShape
	{
	public:
                BlobShape();
                ~BlobShape();
                MapBig mShape;
	};
}

#endif 
