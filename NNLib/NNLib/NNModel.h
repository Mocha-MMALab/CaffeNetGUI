#ifndef _NNMODEL_H
#define _NNMODEL_H
#ifdef WIN32
	#ifdef NNLIB_EXPORTS
	#define NNLIB_API __declspec(dllexport)
	#else
	#define NNLIB_API __declspec(dllimport)
	#endif
#else
	#define NNLIB_API
#endif

#include <string>
#include "BaseLayer.h"
#include "Layers.h"

using namespace std;
using namespace MMALab;

namespace MMALab
{
	class NNLIB_API NNModel
	{
	public:

		/* @NNModel constructor of NNModel
		 * @details this class can help user to contruct own network model
		 */
		NNModel();

		/* @NNModel constructor of NNModel
		 * @details this class can help user to contruct own network model
		 *
		 * @param	name		the name of network model
		 */
		NNModel(string name);

		/* @NNModel deconstructor of NNModel
		 * @details this class will be deconstruct by user
		 */
		~NNModel();

		/* @NNModel add layer
		 * @detalis add layer to current network model
		 *
		 * @param	layer			the layer of prepare added to current network model
		 */
		void addLayer(BaseLayer* layer);

		/* @NNModel remove layer
		 * @details remove specific layer from current network model
		 *
		 * @param	layer			the layer of prepare removed from current network model
		 */
		void removeLayer(BaseLayer* layer);

		/* @NNModel clearn layer
		 * @details remove all layer from current network model
		 */
		void clearnLayer();

		/* @NNModel convert to caffe format
		 * @details convert current network model to caffe format(.prototxt)
		 *
		 * @param	exportPath		the name of exported .prototxt file
		 */
		void convert2CaffeFormat(string modelName); 

		/* @NNModel set the NN name
		 * @details set the NN name
		 *
		 * @param	name		the name of NN
		 */
		void setName(string name);

		/* @NNModel get the NN name
		 * @details get the NN name
		 *
		 * @return	string		the name of NN
		 */
		string getName();		

		/* @NNModel show the linked layers
		 * @details show all linked layers of current model
		 */
		void showLinkedLayers();

	private:

		/* @NNModel linked layers
		 * @details all linked layers of current network model
		 */
		vector<BaseLayer*>* mLinkedLayers;

		string mName;
	};
}

#endif // NNMODEL
