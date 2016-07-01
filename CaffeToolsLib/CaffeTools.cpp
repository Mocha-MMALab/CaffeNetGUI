#include "CaffeTools.h"

namespace MMALab
{
    CaffeTools::CaffeTools()
    {
        mNetParam = new NetParameter();
        mSolverParam = new SolverParameter();
    }

    CaffeTools::~CaffeTools()
    {
        delete mNetParam;
        delete mSolverParam;
    }

    void CaffeTools::parseNetProTextFile(string filename)
    {
        ReadProtoFromTextFileOrDie(filename, mNetParam);
    }

    void CaffeTools::parseSolverProTextFile(string filename)
    {
        ReadProtoFromTextFileOrDie(filename, mSolverParam);
    }

    void CaffeTools::saveNetProTextFile(string filename)
    {
        WriteProtoToTextFile(*mNetParam, filename);
    }

    NetParameter CaffeTools::getNetParam()
    {
        return *mNetParam;
    }

	SolverParameter CaffeTools::getSolverParam()
    {
        return *mSolverParam;
    }

   	//use terminal run time train test function
	void CaffeTools::time(string inputCaffeLocal,string inputModel,
		string inputGpu,string inputLogOutputLocal)
    {
        strcpy(tempChar,inputCaffeLocal.c_str());
        strcat(tempChar," time --model=");
        strcat(tempChar,inputModel.c_str());
        strcat(tempChar," --gpu=");
        strcat(tempChar,inputGpu.c_str());
        strcat(tempChar," 2>&1 | tee ");
        strcat(tempChar,inputLogOutputLocal.c_str());

		//add thread to run
        mThread = new thread(&CaffeTools::createThread, this);
    	mThread->detach();
    }

    void CaffeTools::train(string inputCaffeLocal,string inputSolver,
		string inputSnapshot, string inputGpu,string inputLogOutputLocal)
    {
        strcpy(tempChar,inputCaffeLocal.c_str());
        strcat(tempChar," train --solver=");
        strcat(tempChar,inputSolver.c_str());
        strcat(tempChar," --snapshot=");
        strcat(tempChar,inputSnapshot.c_str());
        strcat(tempChar," --gpu=");
        strcat(tempChar,inputGpu.c_str());
        strcat(tempChar," 2>&1 | tee ");
        strcat(tempChar,inputLogOutputLocal.c_str());

        mThread = new thread(&CaffeTools::createThread, this);
    	mThread->detach();
    }

    void CaffeTools::test(string inputCaffeLocal,string inputModel,
		string inputWeights, string inputGpu,string inputLogOutputLocal)
    {
        strcpy(tempChar,inputCaffeLocal.c_str());
        strcat(tempChar," test --model=");
        strcat(tempChar,inputModel.c_str());
        strcat(tempChar," --weights=");
        strcat(tempChar,inputWeights.c_str());
        strcat(tempChar," --gpu=");
        strcat(tempChar,inputGpu.c_str());
        strcat(tempChar," 2>&1 | tee ");
        strcat(tempChar,inputLogOutputLocal.c_str());

        mThread = new thread(&CaffeTools::createThread, this);
    	mThread->detach();
    }

    void CaffeTools::createThread()
    {
		isEnd = false;
        system(tempChar);
		isEnd = true;
    }
	//run at cancel action 
    void CaffeTools::cancelAction(string inputLogFileUrl)
    {
		strcpy(cancelActionChar,"pkill -f '");
		strcat(cancelActionChar,tempChar);
		strcat(cancelActionChar,"'");
		system(cancelActionChar);
	
		strcpy(cancelActionChar,"pkill -f 'tee ");
		strcat(cancelActionChar,inputLogFileUrl.c_str());
		strcat(cancelActionChar,"'");
		system(cancelActionChar);
    }
    bool CaffeTools::getIsEnd()
    {
		return isEnd;
    }
}
