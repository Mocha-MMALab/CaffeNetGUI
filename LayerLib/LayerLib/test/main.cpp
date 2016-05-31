#include <iostream>

#include "../LayerEnum.h"
#include "../Layers.h"
#include "../LossLayers.h"
#include "../CommonLayers.h"
#include "../VisionLayers.h"
#include "../DataLayers.h"

using namespace std;
using namespace MMALab;

int main()
{
	MemoryDataLayer* Layer1 = new MemoryDataLayer();

	DataBlob* Blob1 = new DataBlob("blob");

	Layer1->addTopConnection(Blob1);
	Layer1->setLayerPhase(TEST);

	cout << Layer1->convet2CaffeFormat() << endl;

	return 0;

}
