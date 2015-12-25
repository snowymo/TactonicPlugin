#ifndef _TactonicDLL_H
#define _TactonicDLL_H

#include "../include/DisplayViews.h"

void frameCallback(TactonicFrameEvent* evt);            // TactonicFrame callback registered in the main
void frameCallback0(TactonicFrameEvent* evt);            // TactonicFrame callback registered in the main
void frameCallback1(TactonicFrameEvent* evt);            // TactonicFrame callback registered in the main

class TactonicDLL
{
public:
	TactonicDLL(void);
	~TactonicDLL(void);

	//TactonicFrame* getFrame()  { return m_pFrame; }
	TactonicFrame* getFrame0()  { return m_pFrame0; }
	//void setFrame0(TactonicFrame* val) { m_pFrame0 = val; }
	TactonicFrame* getFrame1()  { return m_pFrame1; }
	//void setFrame1(TactonicFrame* val) { m_pFrame1 = val; }
public:
	static TactonicDLL* getInstance();
	//bool getPressDown(int index);
	//bool getPressUp(int index);

	TactonicFrame* getFrame(int i);
	TactonicFrame* getFrame();
	bool getFrame(int* frame, int* cnt, int* tot);
	bool getMultiFrame(int* frame, int* devCnt, int* cnt, int* tot);

	

	TactonicFrame** m_pp;

private:
	static TactonicDLL* m_pInstance;

	// for tactonic
	TactonicDeviceList *m_pDeviceList;                              // Data Structure for retrieving available devices
	TactonicFrame * m_pFrame;
	TactonicDevice device0,device1,device2,device3;              // The device that we are monitoring

	TactonicFrame* m_pFrame0;
	TactonicFrame* m_pFrame1;
	TactonicFrame* m_pFrame2;
	TactonicFrame* m_pFrame3;
private:
	void init();

};

#endif