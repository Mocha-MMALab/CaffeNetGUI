#include <iostream>
#include "Layers.h"
#include "NNModel.h"

#define TEST_LOSS

using namespace std;
using namespace MMALab;
int main()
{
	NNModel* model = new NNModel("model");

	DataBlob* blob1 = new DataBlob("blob1");
	DataBlob* blob2 = new DataBlob("blob2");
	Gaussian* gaussian = new Gaussian();

#ifdef TEST_VISION	

	ConvolutionLayer* conv = new ConvolutionLayer("conv");	
	conv->addBottomConnection(blob1);
	conv->addTopConnection(blob2);
	conv->setFilterLRDecayMult(1, 0.001);
	conv->setBiasLRDecayMult(1, 0.001);
	conv->setPad(1);
	conv->setGroup(2);
	conv->setStride(2);
	conv->setEngine(Engine::CAFFE);
	conv->setBiasTerm(false);
	conv->setWeightfilter(gaussian);
	conv->setBiasfilter(gaussian);

	PoolingLayer* pool = new PoolingLayer("pool");	
	pool->addBottomConnection(blob1);
	pool->addTopConnection(blob2);
	pool->setPool(PoolMethod::AVE);
	pool->setStride(2);
	pool->setEngine(Engine::CUDNN);
	pool->setGlobalPooling(true);


	SPPLayer* spp = new SPPLayer("spp");
	spp->addBottomConnection(blob1);
	spp->addTopConnection(blob2);
	spp->setPool(PoolMethod::AVE);
	spp->setEngine(Engine::CAFFE);

	LRNLayer* lrn = new LRNLayer("lrn");
	lrn->addBottomConnection(blob1);
	lrn->addTopConnection(blob2);
	lrn->setLocalSize(7);
	lrn->setAlpha(1.2);
	lrn->setBeta(0.9);
	lrn->setNormRegion(NormRegion::WITHIN_CHANNEL);
	lrn->setK(2);

	model->addLayer(conv);
	model->addLayer(pool);
	model->addLayer(spp);
	model->addLayer(lrn);

#endif

#ifdef TEST_LOSS

	AccuracyLayer* accuracy = new AccuracyLayer("accuracy");
	accuracy->addBottomConnection(blob1);
	accuracy->addTopConnection(blob2);
	accuracy->setTopK(1);
	accuracy->setAxis(1);
	accuracy->setIgnoreLabel(0);

	ContrastiveLossLayer* contrastvieloss = new ContrastiveLossLayer("contrastiveloss");
	contrastvieloss->addBottomConnection(blob1);
	contrastvieloss->addTopConnection(blob2);
	contrastvieloss->setMargin(1.0);
	contrastvieloss->setLegacyVersion(false);

	HingeLossLayer* hingeloss = new HingeLossLayer("hingeloss");
	hingeloss->addBottomConnection(blob1);
	hingeloss->addTopConnection(blob2);
	hingeloss->setNorm(L1);

	InfogainLossLayer* infogainloss = new InfogainLossLayer("infogainloss");
	infogainloss->addBottomConnection(blob1);
	infogainloss->addTopConnection(blob2);
	infogainloss->setSource("");

	model->addLayer(accuracy);
	model->addLayer(contrastvieloss);
	model->addLayer(hingeloss);
	model->addLayer(infogainloss);

#endif

#ifdef TEST_COMMON

	ArgMaxLayer* argmax = new ArgMaxLayer("argmax");
	argmax->addBottomConnection(blob1);
	argmax->addTopConnection(blob2);
	argmax->setOutMaxVal(false);
	argmax->setTopK(1);	

	ConcatLayer* concat = new ConcatLayer("concat");
	concat->addBottomConnection(blob1);
	concat->addTopConnection(blob2);
	concat->setAxis(1);
	concat->setConcatDim(-1);

	EltwiseLayer* eltwise = new EltwiseLayer("eltwise");
	eltwise->addBottomConnection(blob1);
	eltwise->addTopConnection(blob2);
	eltwise->setOperation(EltwiseOp::SUM);
	eltwise->setCoeff(0);
	eltwise->setStableProdGrad(true);

	FlattenLayer* flatten = new FlattenLayer("flatten");
	flatten->addBottomConnection(blob1);
	flatten->addTopConnection(blob2);
	flatten->setAxis(1);
	flatten->setEndAxis(-1);

	InnerProductLayer* innerproduct = new InnerProductLayer("innerproduct");
	innerproduct->addBottomConnection(blob1);
	innerproduct->addTopConnection(blob2);
	innerproduct->setNumOutput(0);
	innerproduct->setBiasTerm(true);
	innerproduct->setWeightfilter(gaussian);
	innerproduct->setBiasfilter(gaussian);
	innerproduct->setAxis(1);

	MVNLayer* mvn = new MVNLayer("mvn");
	mvn->addBottomConnection(blob1);
	mvn->addTopConnection(blob2);
	mvn->setNormalizeVariance(true);
	mvn->setAcrossChannels(false);
	mvn->setEps(1e-9);
	
	ReductionLayer* reduction = new ReductionLayer("reduction");
	reduction->addBottomConnection(blob1);
	reduction->addTopConnection(blob2);
	reduction->setOperation(ReductionOp::SUM);
	reduction->setAxis(0);
	reduction->setCoeff(1.0);

	ReshapeLayer* reshape = new ReshapeLayer("reshape");
	reshape->addBottomConnection(blob1);
	reshape->addTopConnection(blob2);
	reshape->setShape("");
	reshape->setAxis(0);
	reshape->setNumAxis(-1);

	SoftMaxLayer* softmax = new SoftMaxLayer("softmax");
	softmax->addBottomConnection(blob1);
	softmax->addTopConnection(blob2);
	softmax->setEngine(Engine::DEFAULT);
	softmax->setAxis(1);
	

	SliceLayer* slice = new SliceLayer("slice");
	slice->addBottomConnection(blob1);
	slice->addTopConnection(blob2);
	slice->setAxis(1);
	slice->setSlicePoint(0);
	slice->setSliceDim(1);

	model->addLayer(argmax);
	model->addLayer(concat);
	model->addLayer(eltwise);
	model->addLayer(flatten);
	model->addLayer(innerproduct);
	model->addLayer(mvn);
	model->addLayer(reduction);
	model->addLayer(reshape);
	model->addLayer(softmax);
	model->addLayer(slice);

#endif

#ifdef TEST_NEURON

	DropoutLayer* dropout = new DropoutLayer("dropout");
	dropout->addBottomConnection(blob1);
	dropout->addTopConnection(blob2);
	dropout->setDropoutRatio(0.6);

	ExpLayer* exp = new ExpLayer("exp");
	exp->addBottomConnection(blob1);
	exp->addTopConnection(blob2);
	exp->setBase(-0.5);
	exp->setScale(1.2);
	exp->setShift(0.5);

	LogLayer* log = new LogLayer("log");
	log->addBottomConnection(blob1);
	log->addTopConnection(blob2);
	log->setBase(-0.5);
	log->setScale(1.2);
	log->setShift(0.5);

	PowerLayer* power = new PowerLayer("power");
	power->addBottomConnection(blob1);
	power->addTopConnection(blob2);
	power->setPower(1.2);
	power->setScale(1.2);
	power->setShift(0.5);

	PReLULayer* prelu = new PReLULayer("prelu");
	prelu->addBottomConnection(blob1);
	prelu->addTopConnection(blob2);
	prelu->setFilter(gaussian);
	prelu->setChannelShared(true);

	ReLULayer* relu = new ReLULayer("relu");
	relu->addBottomConnection(blob1);
	relu->addTopConnection(blob2);
	relu->setNegativeSlope(0.5);
	relu->setEngine(Engine::CUDNN);

	SigmoidLayer* sigmoid = new SigmoidLayer("sigmoid");
	sigmoid->addBottomConnection(blob1);
	sigmoid->addTopConnection(blob2);
	sigmoid->setEngine(Engine::CUDNN);

	TanHLayer* tanh = new TanHLayer("tanh");
	tanh->addBottomConnection(blob1);
	tanh->addTopConnection(blob2);
	tanh->setEngine(Engine::CUDNN);

	ThresholdLayer* threshold = new ThresholdLayer("threshold");
	threshold->addBottomConnection(blob1);
	threshold->addTopConnection(blob2);
	threshold->setThreshold(3.0);

	model->addLayer(dropout);
	model->addLayer(exp);
	model->addLayer(log);
	model->addLayer(power);
	model->addLayer(prelu);
	model->addLayer(relu);
	model->addLayer(sigmoid);
	model->addLayer(tanh);
	model->addLayer(threshold);

#endif
	
#ifdef TEST_DATA

	DataLayer* data = new DataLayer("data");

	DummyDataLayer* dummydata = new DummyDataLayer("dummydata");

	HDF5DataLayer* hdf5data = new HDF5DataLayer("hdf5data");

	HDF5OutputLayer* hdf5output = new HDF5OutputLayer("hdf5output");

	ImageDataLayer* imagedata = new ImageDataLayer("imagedata");

	MemoryDataLayer* memorydata = new MemoryDataLayer("memorydata");

	WindowDataLayer* windowdata = new WindowDataLayer("windowdata");

	model->addLayer(data);
	model->addLayer(dummydata);
	model->addLayer(hdf5data);
	model->addLayer(hdf5output);
	model->addLayer(imagedata);
	model->addLayer(memorydata);
	model->addLayer(windowdata);

#endif
	
	model->convert2CaffeFormat("model");

	return 0;

}
