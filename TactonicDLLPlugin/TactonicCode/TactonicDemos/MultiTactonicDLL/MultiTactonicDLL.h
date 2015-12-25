#ifndef _MULTI_TACTONIC_H
#define _MULTI_TACTONIC_H

#include "../include/DisplayViews.h"

void multiFrameCallback(TactonicFrameEvent* evt);            // TactonicFrame callback registered in the main

class MultiTactonicDLL
{
public:
	MultiTactonicDLL(void);
	~MultiTactonicDLL(void);

public:
	static MultiTactonicDLL* getInstance();

	bool getFrame(int* frame, int* devCnt, int* cnt, int* tot);

	TactonicFrame * m_pFrame0;
	TactonicFrame * m_pFrame1;

private:
	static MultiTactonicDLL* m_pInstance;

	// for tactonic
	TactonicDeviceList *m_pDeviceList;                              // Data Structure for retrieving available devices
	
	TactonicDevice device0,device1,device2,device3;              // The device that we are monitoring

	void init();
};

#endif