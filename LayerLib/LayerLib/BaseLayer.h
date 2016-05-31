#ifndef _BASELAYER_H
#define _BASELAYER_H

#ifdef  WIN32
	#ifdef LAYERLIB_EXPORTS
	#define LAYERLIB_API __declspec(dllexport)
	#else
	#define LAYERLIB_API __declspec(dllimport)
	#endif
#else
	#define LAYERLIB_API
#endif

#include <vector>
#include <string>

#include "LayerEnum.h"
#include "DataBlob.h"

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
	/* @class BaseLayer
     * @basic Class for base layer definition
     */
	class LAYERLIB_API BaseLayer
	{
	public:	
		
		BaseLayer();

		~BaseLayer();				

		/* @BaseLayer add top connection
		 * @details add top connection to current layer
		 *
		 * @param	layer		top connection layer
		 */
		void addTopConnection(DataBlob* blob);
		void addTopConnection(DataBlob* blob, string inputName);
		/* @BaseLayer add bottom connection
		 * @details add buttom connection to current layer
		 *
		 * @param	layer		bottom connection layer
		 */
		void addBottomConnection(DataBlob* blob);

		/* @BaseLayer remove top connection
		 * @details remove one of top connection from current layer
		 *
		 * @param	layer		top connection layer
		 */
		void removeTopConnection();
		void removeTopConnection(DataBlob* blob);

		/* @BaseLayer remove bottom connection
		 * @details remove one of bottom connection from current layer
		 *
		 * @param	layer		bottom connection layer
		 */
		void removeBottomConnection(DataBlob* blob);

		/* @BaseLayer clearn top connection
		 * @details clearn all top connection from current layer
		 */
		void clearnTopConnection();

		/* @BaseLayer clearn bottom connection
		 * @details clearn all bottom connection from current layer
		 */
		void clearnBottomConnection();

		/* @BaseLayer get type name
		 * @details get type name of current layer
		 */
		string getLayerType();

		void setLayerName(string value);

		string getLayerName();

		void setLayerPhase(Phase state);

		Phase getLayerPhase();

		virtual string convet2CaffeFormat() = 0;

	protected:		

		/* @BaseLayer type
		 * @details type of current layer
		 */
		LayerType mType;

		/* @BaseLayer name
		 * @details nmae of current layer
		 */
		string mName;

		/* @BaseLayer phase
		 * @details phase of layer
		 */
		Phase mPhase;

		/* @BaseLayer tops
		 * @details linked top connections of current layer
		 */
		vector<string>* mTops;

		/* @BaseLayer bottoms
		 * @details linked bottom connection of current layer
		 */
		vector<string>* mBottoms;

		/* @BaseLayer param
		 * @details parameters about current layer
		 */
		void* mParam;

			
	};

}

#endif 
