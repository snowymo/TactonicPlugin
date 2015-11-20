#ifndef _TactonicDLL_H
#define _TactonicDLL_H

#include "DisplayViews.h"

void frameCallback(TactonicFrameEvent* evt);            // TactonicFrame callback registered in the main

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

private:
	static TactonicDLL* m_pInstance;

	// for tactonic
	TactonicDeviceList *m_pDeviceList;                              // Data Structure for retrieving available devices
	TactonicFrame * m_pFrame;
	TactonicDevice device0,device1,device2,device3;              // The device that we are monitoring

private:
	void init();

};

#endif