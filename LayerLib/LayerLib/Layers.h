#ifndef _LAYERS_H
#define _LAYERS_H

#ifdef  WIN32
	#ifdef LAYERLIB_EXPORTS
	#define LAYERLIB_API __declspec(dllexport)
	#else
	#define LAYERLIB_API __declspec(dllimport)
	#endif
#else
	#define LAYERLIB_API
#endif

#include "LayerEnum.h"

#include "LayerParam.h"
#include "CommonLayerParam.h"
#include "DataLayerParam.h"
#include "LossLayerParam.h"
#include "VisionLayerParam.h"
#include "NeuronLayerParam.h"

#include "BaseLayer.h"
#include "CommonLayers.h"
#include "DataLayers.h"
#include "LossLayers.h"
#include "VisionLayers.h"
#include "NeuronLayers.h"

using namespace std;

/* @namespace MMALab
 * @MMALab namespace
 */
namespace MMALab
{
	
}

#endif 
