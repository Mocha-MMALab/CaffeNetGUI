#ifndef _DATALAYERS_H
#define _DATALAYERS_H

#include "LayerEnum.h"
#include "BaseLayer.h"
#include "LayerParam.h"
#include "DataLayerParam.h"

typedef unsigned int uint32;

using namespace std;

/* @namespace MMALab
 * @MMALab namespace
 */
namespace MMALab
{
	/* @class MemoryDataLayer
	 * @basic class for memorydata layer definition
	 */
	class LAYERLIB_API MemoryDataLayer : public BaseLayer
	{
	public:

		/* @MemoryDataLayer constructor of MemoryDataLayer
		 * @details this class can help user to contruct own memorydata layer
		 */
		MemoryDataLayer(string name);

		MemoryDataLayer();

		/* @MemoryDataLayer deconstructor of MemoryDataLayer
		 * @details this class will be deconstruct by user
		 */
		~MemoryDataLayer();

		/* @MemoryDataParam set batch size
		 * @details set the batch processing of size
		 * 
		 * @param	value		the batch processing of size
		 */
                void setBatchSize(uint32 value);

		/* @MemoryDataParam set channels
		 * @details set the channels of image
		 * 
		 * @param	value		the the channels of image
		 */
                void setChannels(uint32 value);

		/* @MemoryDataParam set height
		 * @details set the height of image
		 * 
		 * @param	value		the height of image
		 */
                void setHeight(uint32 value);

		/* @MemoryDataParam set width
		 * @details set the width of image
		 * 
		 * @param	value		the width of image
		 */
                void setWidth(uint32 value);

		/* @MemoryDataParam get batch size
		 * @details get the batch processing of size
		 * 
		 * @return	int			the batch processing of image
		 */
                uint32 getBatchSize();

		/* @MemoryDataParam get channels
		 * @details get the channels of image
		 * 
		 * @return	int			the channels of image
		 */
                uint32 getChannels();

		/* @MemoryDataParam get height
		 * @details get the height of image
		 * 
		 * @return	int			the height of image
		 */
                uint32 getHeight();

		/* @MemoryDataParam get width
		 * @details get the width of image
		 * 
		 * @return	int			the width of image
		 */
                uint32 getWidth();

		string convet2CaffeFormat();

	};
	
	/* @class DataLayer
	 * @basic class for data layer definition
	 */
	class LAYERLIB_API DataLayer : public BaseLayer
	{
	public:

		/* @DataLayer constructor of DataLayer
		 * @details this class can help user to contruct own data layer
		 */
		DataLayer(string name);

		DataLayer();

		/* @DataLayer deconstructor of DataLayer
		 * @details this class will be deconstruct by user
		 */
		~DataLayer();

		/* @DataLayerParam set source
		 * @details set the data source
		 */
		void setSource(string value);

		/* @DataLayerParam set batch size
		 * @details set the batch processing of size
		 */
                void setBatchSize(uint32 value);

		/* @DataLayerParam set rand skip
		 * @details set this number of inputs at the beginning
		 */
                void setRandSkip(uint32 value);

		/* @DataLayerParam set backend
		 * @details set LEVELDB or LMDB
		 */
		void setBackend(DB type);

		/* @DataLayerParam set scale
		 * @details set size conversion of data
		 */
		void setScale(float value);

		/* @DataLayerParam set mean file
		 * @details set the data mean
		 */
		void setMeanfile(string value);

		/* @DataLayerParam set crop size
		 * @details set randomly crop an image
		 */
                void setCropsize(uint32 value);

		/* @DataLayerParam set mirror
		 * @details set mirror an image
		 */
		void setMirror(bool value);

		/* @DataLayerParam set force encoded color
		 * @details set force the encoded image to have 3 color channels
		 */
		void setForceEncodedcolor(bool value);
		
                /* @DataLayerParam set Prefetch
                 * @details set Prefetch queue
                 */
                void setPrefetch(uint32 value);

		/* @DataLayerParam get source
		 * @details get the data source
		 */
		string getSource();

		/* @DataLayerParam get batch size
		 * @details get the batch processing of size
		 */
                uint32 getBatchSize();

		/* @DataLayerParam get rand skip
		 * @details get this number of inputs at the beginning
		 */
                uint32 getRandSkip();

		/* @DataLayerParam get backend
		 * @details get LEVELDB or LMDB
		 */
		DB getBackend();

		/* @DataLayerParam get scale
		 * @details get size conversion of data
		 */
		float getScale();

		/* @DataLayerParam set mean file
		 * @details set the data mean
		 */
		string getMeanfile();

		/* @DataLayerParam get crop size
		 * @details get randomly crop an image
		 */
                uint32 getCropsize();

		/* @DataLayerParam get mirror
		 * @details get mirror an image
		 */
		bool getMirror();

		/* @DataLayerParam get force encoded color
		 * @details get force the encoded image to have 3 color channels
		 */
		bool getForceEncodedcolor();

                /* @DataLayerParam get Prefetch
                 * @details get Prefetch queue
                 */
                uint32 getPrefetch();

		string convet2CaffeFormat();
	};
	
	/* @class ImageDataLayer
	 * @basic class for imagedata layer definition
	 */
	class LAYERLIB_API ImageDataLayer : public BaseLayer
	{
	public:

		/* @ImageDataLayer constructor of ImageDataLayer
		 * @details this class can help user to contruct own imagedata layer
		 */
		ImageDataLayer(string name);

		ImageDataLayer();

		/* @ImageDataLayer deconstructor of ImageDataLayer
		 * @details this class will be deconstruct by user
		 */
		~ImageDataLayer();

		/* @ImageDataLayer set source
		 * @details set the data source
		 */
		void setSource(string value);

		/* @ImageDataLayer set batch size
		 * @details set the batch processing of size
		 */
                void setBatchSize(uint32 value);

		/* @ImageDataLayer set rand skip
		 * @details set this number of inputs at the beginning
		 */
                void setRandSkip(uint32 value);

		/* @ImageDataParam set shuffle
		 * @details set whether or not shuffle the list of files
		 */
		void setShuffle(bool value);

		/* @ImageDataLayer set new height
		 * @details set resize all images to this size
		 */
                void setNewHeight(uint32 value);

		/* @ImageDataLayer set new width
		 * @details set resize all images to this size
		 */
                void setNewWidth(uint32 value);

		/* @ImageDataLayer set is_color
		 * @details set images are color or gray
		 */
		void setIsColor(bool value);

		/* @ImageDataLayer set scale
		 * @details set size conversion of data
		 */
		void setScale(float value);

		/* @ImageDataLayer set mean file
		 * @details set the data mean
		 */
		void setMeanFile(string value);

		/* @ImageDataLayer set crop size
		 * @details set randomly crop an image
		 */
                void setCropSize(uint32 value);

		/* @ImageDataLayer set mirror
		 * @details set mirror an image
		 */
		void setMirror(bool value);

		/* @ImageDataLayer set root folder
		 * @details set the image directory
		 */
		void setRootFolder(string value);

		/* @ImageDataLayer get source
		 * @details get the data source
		 */
		string getSource();

		/* @ImageDataLayer get batch size
		 * @details get the batch processing of size
		 */
                uint32 getBatchSize();

		/* @ImageDataLayer get rand skip
		 * @details get this number of inputs at the beginning
		 */
                uint32 getRandSkip();

		/* @ImageDataParam get shuffle
		 * @details get whether or not shuffle the list of files
		 */
		bool getShuffle();

		/* @ImageDataLayer get new height
		 * @details get resize all images to this size
		 */
                uint32 getNewHeight();

		/* @ImageDataLayer get new width
		 * @details get resize all images to this size
		 */
                uint32 getNewWidth();

		/* @ImageDataLayer get is_color
		 * @details get images are color or gray
		 */
		bool getIsColor();

		/* @ImageDataLayer get scale
		 * @details get size conversion of data
		 */
		float getScale();

		/* @ImageDataLayer get mean file
		 * @details get the data mean
		 */
		string getMeanFile();

		/* @ImageDataLayer get crop size
		 * @details get randomly crop an image
		 */
                uint32 getCropSize();

		/* @ImageDataLayer get mirror
		 * @details get mirror an image
		 */
		bool getMirror();

		/* @ImageDataLayer get root folder
		 * @details get the image directory
		 */
		string getRootFolder();

		string convet2CaffeFormat();

	};

	/* @class WindowDataLayer
	 * @basic class for windowdata layer definition
	 */
	class LAYERLIB_API WindowDataLayer : public BaseLayer
	{
	public:

		/* @WindowDataLayer constructor of WindowDataLayer
		 * @details this class can help user to contruct own windowdata layer
		 */
		WindowDataLayer(string name);

		WindowDataLayer();

		/* @WindowDataLayer deconstructor of WindowDataLayer
		 * @details this class will be deconstruct by user
		 */
		~WindowDataLayer();

		/* @WindowDataLayer set source
		 * @details set the data source
		 */
		void setSource(string value);

		/* @WindowDataLayer set scale
		 * @details set size conversion of data
		 */
		void setScale(float value);

		/* @WindowDataLayer set mean file
		 * @details set the data mean
		 */
		void setMeanFile(string value);

		/* @WindowDataLayer set batch size
		 * @details set the batch processing of size
		 */
                void setBatchSize(uint32 value);

		/* @WindowDataLayer set crop size
		 * @details set randomly crop an image
		 */
                void setCropSize(uint32 value);

		/* @WindowDataLayer set mirror
		 * @details set mirror an image
		 */
		void setMirror(bool value);

		/* @WindowDataLayer set fg threshold
		 * @details set foreground (object) overlap threshold
		 */
		void setFgThreshold(float value);

		/* @WindowDataLayer set bg threshold
		 * @details set background (non-object) overlap threshold
		 */
		void setBgThreshold(float value);

		/* @WindowDataLayer set fg fraction
		 * @details set fraction of batch
		 */
		void setFgFraction(float value);

		/* @WindowDataLayer set context pad
		 * @details set amount of contextual padding to add around a window
		 */
                void setContextPad(uint32 value);

		/* @WindowDataLayer set crop mode
		 * @details set mode for cropping out a detection window
		 */
		void setCropMode(CropMode mode);

		/* @WindowDataLayer set cache images
		 * @details set load all images in memory for faster access
		 */
		void setCacheImages(bool value);

		/* @WindowDataLayer set root folder
		 * @details set the image directory
		 */
		void setRootFolder(string value);

		/* @WindowDataLayer get source
		 * @details get the data source
		 */
		string getSource();

		/* @WindowDataLayer get scale
		 * @details get size conversion of data
		 */
		float getScale();

		/* @WindowDataLayer get mean file
		 * @details get the data mean
		 */
		string getMeanFile();

		/* @WindowDataLayer get batch size
		 * @details get the batch processing of size
		 */
                uint32 getBatchSize();

		/* @WindowDataLayer get crop size
		 * @details get randomly crop an image
		 */
                uint32 getCropSize();

		/* @WindowDataLayer get mirror
		 * @details get mirror an image
		 */
		bool getMirror();

		/* @WindowDataLayer get fg threshold
		 * @details get foreground (object) overlap threshold
		 */
		float getFgThreshold();

		/* @WindowDataLayer get bg threshold
		 * @details get background (non-object) overlap threshold
		 */
		float getBgThreshold();

		/* @WindowDataLayer get fg fraction
		 * @details get fraction of batch
		 */
		float getFgFraction();

		/* @WindowDataLayer get context pad
		 * @details get amount of contextual padding to add around a window
		 */
                uint32 getContextPad();

		/* @WindowDataLayer get crop mode
		 * @details get mode for cropping out a detection window
		 */
		CropMode getCropMode();

		/* @WindowDataLayer get cache images
		 * @details get load all images in memory for faster access
		 */
		bool getCacheImages();

		/* @WindowDataLayer get root folder
		 * @details get the image directory
		 */
		string getRootFolder();

		string convet2CaffeFormat();
	};

	/* @class HDF5DataLayer
	 * @basic class for hdf5data layer definition
	 */
	class LAYERLIB_API HDF5DataLayer : public BaseLayer
	{
	public:

		/* @HDF5DataLayer constructor of HDF5DataLayer
		 * @details this class can help user to contruct own HDF5data layer
		 */
		HDF5DataLayer(string name);

		HDF5DataLayer();

		/* @HDF5DataLayer deconstructor of HDF5DataLayer
		 * @details this class will be deconstruct by user
		 */
		~HDF5DataLayer();

		/* @HDF5DataLayer set source
		 * @details set the imagedata source
		 */
		void setSource(string value);

		/* @HDF5DataLayer set batch size
		 * @details set the batch processing of size
		 */
                void setBatchSize(uint32 value);

		/* @HDF5DataLayer set shuffle
		 * @details set whether or not shuffle the list of files
		 */
		void setShuffle(bool value);

		/* @HDF5DataLayer get source
		 * @details get the imagedata source
		 */
		string getSource();

		/* @HDF5DataLayer get batch size
		 * @details get the batch processing of size
		 */
                uint32 getBatchSize();

		/* @HDF5DataLayer get shuffle
		 * @details get whether or not shuffle the list of files
		 */
		bool getShuffle();

		string convet2CaffeFormat();
	};

	/* @class HDF5OutputLayer
	 * @basic class for hdf5output layer definition
	 */
	class LAYERLIB_API HDF5OutputLayer : public BaseLayer
	{
	public:

		/* @HDF5OutputLayer constructor of HDF5OutputLayer
		 * @details this class can help user to contruct own HDF5output layer
		 */
		HDF5OutputLayer(string name);

		HDF5OutputLayer();

		/* @HDF5OutputLayer deconstructor of HDF5OutputLayer
		 * @details this class will be deconstruct by user
		 */
		~HDF5OutputLayer();

		/* @HDF5OutputLayer set file name
		 * @details set the name of file to write to
		 */
		void setFileName(string value);

		/* @HDF5OutputLayer get file name
		 * @details get the name of file to write to
		 */
		string getFileName();
		
		string convet2CaffeFormat();
	};

	class LAYERLIB_API DummyDataLayer : public BaseLayer
	{
	public:

		/* @DummyDataLayer constructor of DummyDataLayer
		 * @details this class can help user to contruct own DummyData layer
		 */
		DummyDataLayer(string name);

		DummyDataLayer();

		/* @DummyDataLayer deconstructor of DummyDataLayer
		 * @details this class will be deconstruct by user
		 */
		~DummyDataLayer();

		/* @DummyDataLayer set data filler
		 * @details set this layer produces N >= 1 top blobs.
		 */
		void setDataFiller(FillerParameter type);

		/* @DummyDataLayer set shape
		 * @details set specifies the shape (dimensions) of a Blob
		 */
                void setShape(BlobShape* shape);

		/* @DummyDataLayer set num
		 * @details set image number
		 */
                void setNum(uint32 value);

		/* @DummyDataLayer set channels
		 * @details set image channels
		 */
                void setChannels(uint32 value);

		/* @DummyDataLayer set height
		 * @details set image height
		 */
                void setHeight(uint32 value);

		/* @DummyDataLayer set width
		 * @details set image width
		 */
                void setWidth(uint32 value);

		/* @DummyDataLayer get data filler
		 * @details get this layer produces N >= 1 top blobs.
		 */
		FillerParameter getDataFiller();

		/* @DummyDataLayer get shape
		 * @details get specifies the shape (dimensions) of a Blob
		 */
		void* getShape();

		/* @DummyDataLayer get num
		 * @details get image number
		 */
                uint32 getNum();

		/* @DummyDataLayer get channels
		 * @details get image channels
		 */
                uint32 getChannels();

		/* @DummyDataLayer get height
		 * @details get image height
		 */
                uint32 getHeigth();

		/* @DummyDataLayer get width
		 * @details get image width
		 */
                uint32 getWidth();

		string convet2CaffeFormat();
	};
}
#endif //DATALAYERS
