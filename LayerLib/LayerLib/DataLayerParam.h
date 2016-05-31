#ifndef _DATALAYERPARAM_H
#define _DATALAYERPARAM_H

#include <string>
#include "LayerEnum.h"
#include "LayerParam.h"

typedef unsigned int uint32;

using namespace std;
using namespace MMALab;

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
	/* @class MemoryDataParam
	 * @basic class of Memory parameter definition
	 */
	class LAYERLIB_API MemoryDataParam
	{
	public:

		/* @MemoryDataParam batch size
		 * @details the batch processing of size
		 */
		uint32 mBatchSize;

		/* @MemoryDataParam channels
		 * @details the channels of image
		 */
		uint32 mChannels;

		/* @MemoryDataParam channels
		 * @details the height of image
		 */
		uint32 mHeight;

		/* @MemoryDataParam channels
		 * @details the width of image
		 */
		uint32 mWidth;

		/* @MemoryDataParam constructor of MemoryDataParam
		 * @details this class can help user to define parameter of memorydata layer
		 */
		MemoryDataParam();

		/* @MemoryDataParam deconstructor of memoryDataParam
		 * @details this class will be deconstruct by user
		 */
		~MemoryDataParam();
	};
		
	/* @class DataLayerParam
	 * @basic class of datalayer parameter definition
	 */
	class LAYERLIB_API DataParam
	{
	public:

		/* @DataLayerParam source
		 * @details the data source
		 */
		string mSource;
		
		/* @DataLayerParam batch size
		 * @details the batch processing of size
		 */
		uint32 mBatchSize;

		/* @DataLayerParam rand skip
		 * @details skip up to this number of inputs at the beginning
		 */
		uint32 mRandSkip;

		/* @DataLayerParam backend
		 * @details choose whether to use a LEVELDB or LMDB
		 */
		DB mBackend;

		/* @DataLayerParam scale
		 * @details size conversion of data
		 */
		float  mScale;

		/* @DataLayerParam mean file
		 * @details set the data mean
		 */
		string mMeanfile;

		/* @DataLayerParam crop size
		 * @details randomly crop an image
		 */
		uint32 mCropsize;

		/* @DataLayerParam mirror
		 * @mirror an image
		 */
		bool   mMirror;

		/* @DataLayerParam force encoded color
		 * @details force the encoded image to have 3 color channels
		 */
		bool   mForceEncodedcolor;

                /* @DataLayerParam set Prefetch
                 * @details set Prefetch queue
                 */
                uint32 mPrefetch;

		/* @DataLayerParam constructor of DataLayerParam
		 * @details this class can help user to define parameter of data layer
		 */
		DataParam();

		/* @DataLayerParam deconstructor of DataLayerParam
		 * @details this class will be deconstruct by user
		 */
		~DataParam();
	};

	/* @class ImageDataParam
	 * @basic class of imagedata parameter definition
	 */
	class LAYERLIB_API ImageDataParam
	{
	public:

		/* @ImageDataParam source
		 * @details the imagedata source
		 */
		string mSource;

		/* @ImageDataParam batch size
		 * @details the batch processing of size
		 */
		uint32 mBatchSize;

		/* @ImageDataParam rand skip
		 * @details skip up to this number of inputs at the beginning
		 */
		uint32 mRandSkip;

		/* @ImageDataParam shuffle
		 * @details whether or not shuffle the list of files
		 */
		bool   mShuffle;

		/* @ImageDataParam new height
		 * @details resize all images to this size
		 */
		uint32 mNewHeight;

		/* @ImageDataParam new width
		 * @details resize all images to this size
		 */
		uint32 mNewWidth;

		/* @ImageDataParam is_color
		 * @details images are color or gray
		 */
		bool   mIsColor;

		/* @ImageDataLayerParam scale
		 * @details size conversion of data
		 */
		float  mScale;

		/* @ImageDataLayerParam mean file
		 * @details set the data mean
		 */
		string mMeanFile;

		/* @ImageDataLayerParam crop size
		 * @details randomly crop an image
		 */
		uint32 mCropSize;

		/* @ImageDataLayerParam mirror
		 * @details mirror an image
		 */
		bool   mMirror;

		/* @ImageDataLayerParam root folder
		 * @details the image directory
		 */
		string mRootFolder;

		/* @ImageDataLayerParam constructor of ImageDataLayerParam
		 * @details this class can help user to define parameter of imagedata layer
		 */
		ImageDataParam();

		/* @ImageDataLayerParam deconstructor of ImageDataLayerParam
		 * @details this class will be deconstruct by user
		 */
		~ImageDataParam();
	};

	class LAYERLIB_API WindowDataParam
	{
	public:

		/* @Image1DataParam source
		 * @details the imagedata source
		 */
		string mSource;

		/* @WindowDataLayerParam scale
		 * @details size conversion of data
		 */
		float  mScale;

		/* @WindowDataLayerParam mean file
		 * @details set the data mean
		 */
		string mMeanFile;

		/* @WindowDataParam batch size
		 * @details the batch processing of size
		 */
		uint32 mBatchSize;

		/* @WindowDataLayerParam crop size
		 * @details randomly crop an image
		 */
		uint32 mCropSize;

		/* @WindowDataLayerParam mirror
		 * @details mirror an image
		 */
		bool   mMirror;

		/* @WindowDataLayerParam fg threshold
		 * @details foreground (object) overlap threshold
		 */
		float  mFgThreshold;

		/* @WindowDataLayerParam bg threshold
		 * @details background (non-object) overlap threshold
		 */
		float  mBgThreshold;

		/* @WindowDataLayerParam fg fraction
		 * @details fraction of batch that should be foreground objects
		 */
		float  mFgFraction;

		/* @WindowDataLayerParam contextpad
		 * @details amount of contextual padding to add around a window
		 */
		uint32 mContextPad;

		/* @WindowDataLayerParam cropmode
		 * @details mode for cropping out a detection window
		 */
		CropMode mCropMode;

		/* @WindowDataLayerParam cache images
		 * @details load all images in memory for faster access
		 */
		bool   mCacheImages;

		/* @WindowDataLayerParam root folder
		 * @details the image directory
		 */
		string mRootFolder;


		/* @WindowDataLayerParam constructor of WindowDataLayerParam
		 * @details this class can help user to define parameter of windowdata layer
		 */
		WindowDataParam();

		/* @WindowDataLayerParam deconstructor of WindowDataLayerParam
		 * @details this class will be deconstruct by user
		 */
		~WindowDataParam();
	};

	/* @class HDF5DataParam
	 * @basic class of HDF5 Data parameter definition
	 */
	class LAYERLIB_API HDF5DataParam
	{
	public:

		/* @HDF5DataParam source
		 * @details the imagedata source
		 */
		string mSource;

		/* @HDF5DataParam batch size
		 * @details the batch processing of size
		 */
		uint32 mBatchSize;

		/* @HDF5DataParam shuffle
		 * @details whether or not shuffle the list of files
		 */
		bool   mShuffle;

		/* @HDF5DataParam constructor of HDF5DataParam
		 * @details this class can help user to define parameter of HDF5data layer
		 */
		HDF5DataParam();

		/* @HDF5DataParam deconstructor of HDF5DataParam
		 * @details this class will be deconstruct by user
		 */
		~HDF5DataParam();

	};
	
	/* @class HDF5OutputParam
	 * @basic class of HDF5 Output parameter definition
	 */
	class LAYERLIB_API HDF5OutputParam
	{
	public:

		/* @HDF5OutputParam deconstructor of HDF5OutputParam
		 * @details name of file to write to
		 */
		string mFileName;

		/* @HDF5OutputParam constructor of HDF5OutputParam
		 * @details this class can help user to define parameter of HDF5Output layer
		 */
		HDF5OutputParam();

		/* @HDF5OutputParam deconstructor of HDF5OutputParam
		 * @details this class will be deconstruct by user
		 */
		~HDF5OutputParam();
	};

	/* @class DummyDataParam
	 * @basic class of Dummy Data parameter definition
	 */
	class LAYERLIB_API DummyDataParam
	{
	public:

		/* @DummyDataParam data filler
		 * @details this layer produces N >= 1 top blobs.
		 */
		FillerParameter mDataFiller;

		/* @DummyDataParam shape
		 * @details specifies the shape (dimensions) of a Blob
		 */
		void* mShape;

		/* @DummyDataParam num
		 * @details image number
		 */
		uint32 mNum;

		/* @DummyDataParam channels
		 * @details image channels
		 */
		uint32 mChannels;

		/* @DummyDataParam height
		 * @details image height
		 */
		uint32 mHeight;

		/* @DummyDataParam width
		 * @details image width
		 */
		uint32 mWidth;

		/* @DummyDataParam constructor of HDF5OutputParam
		 * @details this class can help user to define parameter of DummyData layer
		 */
		DummyDataParam();

		/* @DummyDataParam deconstructor of DummyDataParam
		 * @details this class will be deconstruct by user
		 */
		~DummyDataParam();
	};

}
#endif //DATALAYERPARAM
