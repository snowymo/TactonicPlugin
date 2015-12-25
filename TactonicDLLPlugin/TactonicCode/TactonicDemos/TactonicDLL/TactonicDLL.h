#ifndef _TactonicDLL_H
#define _TactonicDLL_H

#include "../include/DisplayViews.h"
//#include <vector>

void frameCallback(TactonicFrameEvent* evt);            // TactonicFrame callback registered in the main
void frameCallbackTest(TactonicFrameEvent* evt);            // TactonicFrame callback registered in the main
void frameCallback0(TactonicFrameEvent* evt);            // TactonicFrame callback registered in the main
void frameCallback1(TactonicFrameEvent* evt);            // TactonicFrame callback registered in the main

class TactonicDLL
{
public:
	TactonicDLL(void);
	~TactonicDLL(void);

public:
	static TactonicDLL* getInstance();
	bool getPressDown(int index);
	bool getPressUp(int index);

	TactonicFrame* getFrame(int frameIdx);
	bool getFrame(int* frame, int * deviceCnt, int* cnt, int* tot);

	TactonicFrame * m_pTestFrame;

	TactonicFrame* m_pFrame0;
	TactonicFrame* m_pFrame1;

private:
	static TactonicDLL* m_pInstance;

	// for tactonic
	TactonicDeviceList *m_pDeviceList;                              // Data Structure for retrieving available devices
	TactonicFrame ** m_pFrame;										// frame data of mat
	
	
	TactonicDevice device0,device1,device2,device3;					// The device that we are monitoring

private:
	void init();
	static bool m_bInit;

};

#endif