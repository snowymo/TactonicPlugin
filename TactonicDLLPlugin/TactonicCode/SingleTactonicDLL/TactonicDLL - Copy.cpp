#include "TactonicDLL.h"
#include <time.h>
#include <iostream>
#include <string>

TactonicDLL* TactonicDLL::m_pInstance = NULL;

TactonicDLL::TactonicDLL(void)
{
}


TactonicDLL::~TactonicDLL(void)
{
	if(m_pp)
		delete [] m_pp;
	m_pp = NULL;
	if(m_pInstance)
		delete m_pInstance;
	m_pInstance = NULL;
}

TactonicDLL* TactonicDLL::getInstance()
{
	if(m_pInstance == NULL){
		m_pInstance = new TactonicDLL;
		m_pInstance->init();
	}
	return m_pInstance;
}

// bool TactonicDLL::getPressDown(int index)
// {
// 	// everything is stored in frame.force
// 	// it is a 2D array stored in 1D
// 	if(m_pInstance->m_pDeviceList->numDevices != 0){
// 		int cols = m_pFrame->cols;
// 		int rows = m_pFrame->rows;
// 		float value = 0;
// 		for(int i = 0; i < rows; i ++){
// 			for(int j = 0; j < cols; j++){
// 				int index = i * cols + j;
// 				int curValue = m_pFrame->forces[index];
// 				//std::cout << "force value:\trow:" << i << "\tcol:" << j << "\t:" << curValue << "\t";
// 				value += curValue;
// 			}
// 			//std::cout << "\n";
// 		}
// 		return (value > 0);
// 	}
// 	else
// 		return false;
// }

// bool TactonicDLL::getPressUp(int index)
// {
// 	
// 	return false;
// }

TactonicFrame* TactonicDLL::getFrame(int i)
{
	TactonicFrame* test = m_pFrame + i * sizeof(TactonicFrame);
	return test;
}

TactonicFrame* TactonicDLL::getFrame()
{
	return m_pFrame;
}

bool TactonicDLL::getFrame(int* frame, int* cnt, int* tot)
{
	// copy from m_pFrame to frame
	if(m_pInstance->m_pDeviceList->numDevices != 0){
		int cols = m_pFrame->cols;
		int rows = m_pFrame->rows;
		//float value = 0;
		for(int i = 0; i < rows; i ++){
			for(int j = 0; j < cols; j++){
				int index = i * cols + j;
				int curValue = m_pFrame->forces[index];
				if(curValue != 0){
					OutputDebugStringA(std::to_string(curValue).c_str());
					++cnt[0];
				}
				frame[index] = curValue;
				tot[0] += curValue;
			}
			std::cout << "\n";
		}
		return (tot[0] > 0);
	}
	return false;
}


bool TactonicDLL::getMultiFrame(int* frame, int* devCnt, int* cnt, int* tot)
{
	// copy from m_pFrame to frame
	devCnt[0] = m_pInstance->m_pDeviceList->numDevices;
	for(int devIdx = 0; devIdx < devCnt[0]; devIdx++){
		int cols = m_pp[devIdx]->cols;
		int rows = m_pp[devIdx]->rows;
		//float value = 0;
		for(int i = 0; i < rows; i ++){
			for(int j = 0; j < cols; j++){
				int index = i * cols + j;
				int curValue = m_pp[devIdx]->forces[index];
				if(curValue != 0){
					OutputDebugStringA(std::to_string(curValue).c_str());
					++cnt[0];
				}
				frame[devIdx*cols*rows + index] = curValue;
				tot[0] += curValue;
			}			
		}
	}
	return (tot[0] > 0);
}

void TactonicDLL::init()
{
	// init tactonic module
	m_pDeviceList = Tactonic_GetDeviceList();                        // Get available devices
	m_pp = new TactonicFrame*[m_pDeviceList->numDevices];
	Sleep(1000);
	// for now we start with one floor
	switch(m_pDeviceList->numDevices){                              // Set up the Tactonic Device and register the callback function
	case 1:
		device0 = m_pDeviceList->devices[0];                         // Get the device
		//viewer.init(device0, argc, argv);							// Initialize the View Renderer
		//TactonicTouch_DetectorInitiation(m_pDeviceList->numDevices); 
		//m_pFrame0 = Tactonic_CreateFrame(device0);                   // Create a TactonicFrame for this device
		m_pFrame = Tactonic_CreateFrame(device0);                   // Create a TactonicFrame for this device
		//touchFrame = TactonicTouch_CreateFrame(device0);         // Create a TactonicTouchFrame for this device
		Tactonic_AddFrameCallback(device0, frameCallback);       // Add a TactonicFrame callback method
		//TactonicTouch_CreateDetector(device0);                   // Create the touch detector for the device
		//TactonicTouch_AddTouchCallback(device0, touchCallback);  // Add a TactonicTouchFrame callback method
		//TactonicTouch_StartDetector(device0);                    // Start the touch detector
		Tactonic_StartDevice(device0);                           // Start the device
		m_pp[0] = m_pFrame0;
		break;
	case 2:
		break;
	default:
		break;
	}
}

void frameCallback(TactonicFrameEvent* evt){            // TactonicFrame callback registered in the main
	Tactonic_CopyFrame(evt->frame,TactonicDLL::getInstance()->getFrame());               // Copy the callback frame to a local frame
}

void frameCallback0(TactonicFrameEvent* evt){            // TactonicFrame callback registered in the main
	Tactonic_CopyFrame(evt->frame,TactonicDLL::getInstance()->getFrame(0));               // Copy the callback frame to a local frame
}

void frameCallback1(TactonicFrameEvent* evt){            // TactonicFrame callback registered in the main
	Tactonic_CopyFrame(evt->frame,TactonicDLL::getInstance()->getFrame(1));               // Copy the callback frame to a local frame
}