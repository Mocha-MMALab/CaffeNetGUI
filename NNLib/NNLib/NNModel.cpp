#include "NNModel.h"
#include <iostream>
#include <fstream>

using namespace std;

namespace MMALab
{
	NNModel::NNModel()
	{
		mName = "Net";
		mLinkedLayers = new vector<BaseLayer*>();
	}

	NNModel::NNModel(string name)
	{
		mName = name;
		mLinkedLayers = new vector<BaseLayer*>();
	}

	NNModel::~NNModel()
	{
		delete mLinkedLayers;
	}

	void NNModel::addLayer(BaseLayer* layer)
	{
		mLinkedLayers->push_back((BaseLayer*)layer);
	}

	void NNModel::removeLayer(BaseLayer* layer)
	{
		int size = mLinkedLayers->size();

		for (int i=0; i<size; ++i)
		{
			if (mLinkedLayers->at(i)->getLayerName() == layer->getLayerName())
			{
				mLinkedLayers->erase(mLinkedLayers->begin() + i);
				break;
			}
		}
	}

	void NNModel::clearnLayer()
	{
		mLinkedLayers->clear();
	}

	//layer transform to caffe format
	void NNModel::convert2CaffeFormat(string modelName)
	{
		int size = mLinkedLayers->size();

		string exportName = modelName;
		string extension  = ".prototxt";

		exportName += extension;
		ofstream file(exportName, ios::out);		

		for (int i=0; i<size; ++i)
		{
			file << mLinkedLayers->at(i)->convet2CaffeFormat() << endl << endl;
		}

		file.close();
	}

	//set model name
	void NNModel::setName(string name)
	{
		mName = name;
	}

	string NNModel::getName()
	{
		return mName;
	}

	void NNModel::showLinkedLayers()
	{
		int size = mLinkedLayers->size();

		cout << "Showing all of linked layers: " << endl;
		cout << "------------------------------" << endl;

		for (int i=size-1; i>=0; --i)
		{
			cout << "\t" << mLinkedLayers->at(i)->getLayerName() << endl;

			if (i!=0)
			{
				cout << "\t    ^" << endl;
			}
		}

		cout << "------------------------------" << endl;
	}
}
