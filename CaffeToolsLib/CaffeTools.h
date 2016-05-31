#ifndef CAFFETOOLS_H
#define CAFFETOOLS_H

#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <thread>

#include "hdf5.h"

#include "caffe/common.hpp"
#include "caffe/layer.hpp"
#include "caffe/net.hpp"
#include "caffe/parallel.hpp"
#include "caffe/proto/caffe.pb.h"
#include "caffe/util/hdf5.hpp"
#include "caffe/util/insert_splits.hpp"
#include "caffe/util/math_functions.hpp"
#include "caffe/util/upgrade_proto.hpp"
#include "caffe/util/io.hpp"

#include "caffe/util/benchmark.hpp"
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include "caffe/util/signal_handler.h"

using namespace std;
using namespace caffe;

namespace MMALab
{

    class CaffeTools
    {
    public:
        CaffeTools();
        virtual ~CaffeTools();

        void parseNetProTextFile(string filename);
        void parseSolverProTextFile(string filename);
        void saveNetProTextFile(string filename);

        NetParameter getNetParam();

		void time(string inputCaffeLocal,string inputModel,
			string inputGpu,string inputLogOutputLocal);

		void train(string inputCaffeLocal, string inputSolver,
			string inputSnapshot, string inputGpu, string inputLogOutputLocal);

    	void test(string inputCaffeLocal, string inputModel,
			string inputWeights, string inputGpu, string inputLogOutputLocal);

		void createThread();
		void cancelAction(string inputLogFileUrl);
		bool getIsEnd();
    private:
		bool isEnd = false;
        char tempChar[2048];
		char cancelActionChar[2048];
        NetParameter*		mNetParam;
        SolverParameter*	mSolverParam;
		std::thread* mThread;
    };

}

#endif // CAFFETOOLS_H
