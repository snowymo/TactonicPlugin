#ifndef _TactonicDLL_H
#define _TactonicDLL_H

#include "../include/DisplayViews.h"

void frameCallback(TactonicFrameEvent* evt);            // TactonicFrame callback registered in the main
void frameCallback1(TactonicFrameEvent* evt);            // TactonicFrame callback registered in the main
void frameCallback2(TactonicFrameEvent* evt);            // TactonicFrame callback registered in the main
void frameCallback3(TactonicFrameEvent* evt);            // TactonicFrame callback registered in the main

const int m_nMatMax = 4;

class TactonicDLL
{
public:
	TactonicDLL(void);
	~TactonicDLL(void);

public:
	static TactonicDLL* getInstance();
	bool getPressDown(int index);
	bool getPressUp(int index);

	TactonicFrame* getFrame();
	TactonicFrame* getFrame1();
	TactonicFrame* getFrame2();
	TactonicFrame* getFrame3();
	bool getFrame(int* frame, int* cnt, int* tot);
	bool getMultiFrame(int* frame, int* nDev, int* nCount, int* nTotal);
	int getDeviceNumber(int * nDev);
	bool getCertainFrame(int* frame, int no, int* nCount, int* nTotal);

private:
	static TactonicDLL* m_pInstance;
	

	// for tactonic
	TactonicDeviceList *m_pDeviceList;                              // Data Structure for retrieving available devices
	TactonicFrame * m_pFrame;
	TactonicFrame * m_pFrame1;
	TactonicFrame * m_pFrames[m_nMatMax];
	//TactonicDevice device0,device1,device2,device3;              // The device that we are monitoring
	TactonicDevice* devices;

private:
	void init();

};

#endif