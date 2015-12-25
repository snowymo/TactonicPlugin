#include "MultiTactonicDLL.h"

#include <time.h>
#include <string>
#include <iostream>

MultiTactonicDLL* MultiTactonicDLL::m_pInstance = NULL;

void MultiTactonicDLL::init()
{
	// init tactonic module
	m_pDeviceList = Tactonic_GetDeviceList();                        // Get available devices
	Sleep(1000);
	// for now we start with one floor
	switch(m_pDeviceList->numDevices){                              // Set up the Tactonic Device and register the callback function
	case 1:
		device0 = m_pDeviceList->devices[0];                         // Get the device
		//viewer.init(device0, argc, argv);							// Initialize the View Renderer
		//TactonicTouch_DetectorInitiation(m_pDeviceList->numDevices); 
		m_pFrame0 = Tactonic_CreateFrame(device0);                   // Create a TactonicFrame for this device
		//touchFrame = TactonicTouch_CreateFrame(device0);         // Create a TactonicTouchFrame for this device
		Tactonic_AddFrameCallback(device0, multiFrameCallback);       // Add a TactonicFrame callback method
		//TactonicTouch_CreateDetector(device0);                   // Create the touch detector for the device
		//TactonicTouch_AddTouchCallback(device0, touchCallback);  // Add a TactonicTouchFrame callback method
		//TactonicTouch_StartDetector(device0);                    // Start the touch detector
		Tactonic_StartDevice(device0);                           // Start the device
		break;
	case 2:
		break;
	default:
		break;
	}
}

MultiTactonicDLL::MultiTactonicDLL(void)
{
}


MultiTactonicDLL::~MultiTactonicDLL(void)
{
	if(m_pInstance)
		delete m_pInstance;
	m_pInstance = NULL;
}

MultiTactonicDLL* MultiTactonicDLL::getInstance()
{
	if(m_pInstance == NULL){
		m_pInstance = new MultiTactonicDLL;
		m_pInstance->init();
	}
	return m_pInstance;
}

bool MultiTactonicDLL::getFrame(int* frame, int* devCnt, int* cnt, int* tot)
{
	// copy from m_pFrame to frame
	devCnt[0] = m_pInstance->m_pDeviceList->numDevices;
	TactonicFrame ** pp = new TactonicFrame *[4];
	pp[0] = m_pFrame0;
	pp[1] = m_pFrame1;

	for(int devIdx = 0; devIdx < devCnt[0]; devIdx++){
		int cols = pp[devIdx]->cols;
		int rows = pp[devIdx]->rows;
		//float value = 0;
		for(int i = 0; i < rows; i ++){
			for(int j = 0; j < cols; j++){
				int index = i * cols + j;
				int curValue = pp[devIdx]->forces[index];
				if(curValue != 0){
					OutputDebugStringA(std::to_string(curValue).c_str());
					++cnt[0];
				}
				frame[devIdx*cols*rows + index] = curValue;
				tot[0] += curValue;
			}
			std::cout << "\n";
		}
		return (tot[0] > 0);
	}
	return false;
}


void multiFrameCallback(TactonicFrameEvent* evt)
{
	Tactonic_CopyFrame(evt->frame,MultiTactonicDLL::getInstance()->m_pFrame0);               // Copy the callback frame to a local frame
}
