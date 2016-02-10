#include "TactonicDLL.h"
#include <time.h>
#include <iostream>
#include <string>

TactonicDLL* TactonicDLL::m_pInstance = NULL;

TactonicDLL::TactonicDLL(void)
{
	devices = new TactonicDevice[m_nMatMax];
	for(int i = 0; i < m_nMatMax; i++)
		m_pFrames[i] = new TactonicFrame;
}


TactonicDLL::~TactonicDLL(void)
{
	if(m_pInstance)
		delete m_pInstance;
	m_pInstance = NULL;
	if(devices)
		delete [] devices;
	devices = NULL;
	for each (TactonicFrame* frame in m_pFrames){
		if(frame)
			delete frame;
		frame = NULL;
	}
}

TactonicDLL* TactonicDLL::getInstance()
{
	if(m_pInstance == NULL){
		m_pInstance = new TactonicDLL;
		m_pInstance->init();
	}
	
	return m_pInstance;
}


bool TactonicDLL::getFrame(int* frame, int* cnt, int* tot)
{
	// copy from m_pFrame to frame
	if(m_pInstance->m_pDeviceList->numDevices != 0){
		int cols = m_pFrames[0]->cols;
		int rows = m_pFrames[0]->rows;
		//float value = 0;
		for(int i = 0; i < rows; i ++){
			for(int j = 0; j < cols; j++){
				int index = i * cols + j;
				int curValue = m_pFrames[0]->forces[index];
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

TactonicFrame* TactonicDLL::getFrame1()
{
	return m_pFrames[1];
}

TactonicFrame* TactonicDLL::getFrame2()
{
	return m_pFrames[2];
}

TactonicFrame* TactonicDLL::getFrame3()
{
	return m_pFrames[3];
}

bool TactonicDLL::getMultiFrame(int* frame, int* nDev, int* nCount, int* nTotal)
{
	nDev[0] = m_pDeviceList->numDevices;

	// copy from m_pFrame to frame
	for(int devIdx = 0; devIdx < nDev[0]; devIdx++){
		int cols = m_pFrames[0]->cols;
		int rows = m_pFrames[0]->rows;
		//float value = 0;
		for(int i = 0; i < rows; i ++){
			for(int j = 0; j < cols; j++){
				int index = i * cols + j;
				int curValue = m_pFrames[devIdx]->forces[index];
				if(curValue != 0){
					OutputDebugStringA(std::to_string(curValue).c_str());
					++nCount[0];
				}
				frame[devIdx * cols*rows + index] = curValue;
				nTotal[0] += curValue;
			}
			std::cout << "\n";
		}
	}
	return (nTotal[0] > 0);
}


int TactonicDLL::getDeviceNumber(int * nDev)
{
	nDev[0] = m_pDeviceList->numDevices;
	return 0;
}

bool TactonicDLL::getCertainFrame(int* frame, int no, int* nCount, int* nTotal)
{
	// copy from m_pFrame to frame
	//for(int devIdx = 0; devIdx < nDev[0]; devIdx++){
		int cols = m_pFrames[0]->cols;
		int rows = m_pFrames[0]->rows;
		//float value = 0;
		for(int i = 0; i < rows; i ++){
			for(int j = 0; j < cols; j++){
				int index = i * cols + j;
				int curValue = m_pFrames[no]->forces[index];
				if(curValue != 0){
					OutputDebugStringA(std::to_string(curValue).c_str());
					++nCount[0];
				}
				frame[cols*rows + index] = curValue;
				nTotal[0] += curValue;
			}
			std::cout << "\n";
		}
	//}
	return (nTotal[0] > 0);
}

void TactonicDLL::init()
{
	// init tactonic module
	m_pDeviceList = Tactonic_GetDeviceList();                        // Get available devices
	Sleep(1000);

	for(int devIdx = 0; devIdx < m_pDeviceList->numDevices; devIdx++){
		devices[devIdx] = m_pDeviceList->devices[devIdx];                         // Get the device
		m_pFrames[devIdx] = Tactonic_CreateFrame(devices[devIdx]);                   // Create a TactonicFrame for this device
		Tactonic_StartDevice(devices[devIdx]);                           // Start the device
	}

	switch (m_pDeviceList->numDevices)
	{
	case 1:
		// for now we start with one floor
		Tactonic_AddFrameCallback(devices[0], frameCallback);       // Add a TactonicFrame callback method
		break;
	case 2:
		Tactonic_AddFrameCallback(devices[0], frameCallback);       // Add a TactonicFrame callback method
		Tactonic_AddFrameCallback(devices[1], frameCallback1);       // Add a TactonicFrame callback method
		break;
	case 4:
		Tactonic_AddFrameCallback(devices[0], frameCallback);       // Add a TactonicFrame callback method
		Tactonic_AddFrameCallback(devices[1], frameCallback1);       // Add a TactonicFrame callback method
		Tactonic_AddFrameCallback(devices[2], frameCallback2);       // Add a TactonicFrame callback method
		Tactonic_AddFrameCallback(devices[3], frameCallback3);       // Add a TactonicFrame callback method
		break;
	default:
		break;
	}
}

void frameCallback(TactonicFrameEvent* evt){            // TactonicFrame callback registered in the main
	Tactonic_CopyFrame(evt->frame,TactonicDLL::getInstance()->getFrame());               // Copy the callback frame to a local frame
}

void frameCallback1(TactonicFrameEvent* evt){            // TactonicFrame callback registered in the main
	Tactonic_CopyFrame(evt->frame,TactonicDLL::getInstance()->getFrame1());               // Copy the callback frame to a local frame
}

void frameCallback2(TactonicFrameEvent* evt){            // TactonicFrame callback registered in the main
	Tactonic_CopyFrame(evt->frame,TactonicDLL::getInstance()->getFrame2());               // Copy the callback frame to a local frame
}

void frameCallback3(TactonicFrameEvent* evt){            // TactonicFrame callback registered in the main
	Tactonic_CopyFrame(evt->frame,TactonicDLL::getInstance()->getFrame3());               // Copy the callback frame to a local frame
}

