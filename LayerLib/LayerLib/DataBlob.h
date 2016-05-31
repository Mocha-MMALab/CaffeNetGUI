#ifndef _DATABLOB_H
#define _DATABLOB_H

#ifdef  WIN32
	#ifdef LAYERLIB_EXPORTS
	#define LAYERLIB_API __declspec(dllexport)
	#else
	#define LAYERLIB_API __declspec(dllimport)
	#endif
#else
	#define LAYERLIB_API
#endif

#include <string>

using namespace std;

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
	/* @class DataBlob
     * @basic Class for data blob definition
     */
	class LAYERLIB_API DataBlob
	{

	public: 

		/* @DataBlob constructor of DataBlob
		 * @details this class can help user to contruct own data blob
		 */
		DataBlob(string name);

		/* @DataBlob deconstructor of DataBlob
		 * @details this class will be deconstruct by user
		 */
		~DataBlob();

		/* @DataBloc name
		 * @details name of current data blob
		 */
		string mName;
	};
}

#endif // DATABLOB
