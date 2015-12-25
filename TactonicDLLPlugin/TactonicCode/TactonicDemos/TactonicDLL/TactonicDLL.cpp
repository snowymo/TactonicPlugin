#include "TactonicDLL.h"
#include <time.h>
#include <iostream>
#include <string>

TactonicDLL* TactonicDLL::m_pInstance = NULL;
bool TactonicDLL::m_bInit = false;

TactonicDLL::TactonicDLL(void)
{
	m_pFrame = new TactonicFrame *[8];
	memset(m_pFrame,0,sizeof(TactonicFrame*) * 8);
	m_bInit = false;
}


TactonicDLL::~TactonicDLL(void)
{
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
	if(!m_bInit){
		m_pInstance = new TactonicDLL;
		m_pInstance->init();
	}
	return m_pInstance;
}

bool TactonicDLL::getPressDown(int index)
{
	// everything is stored in frame.force
	// it is a 2D array stored in 1D
	if(m_pInstance->m_pDeviceList->numDevices != 0){
		int cols = m_pFrame[0]->cols;
		int rows = m_pFrame[0]->rows;
		float value = 0;
		for(int i = 0; i < rows; i ++){
			for(int j = 0; j < cols; j++){
				int index = i * cols + j;
				int curValue = m_pFrame[0]->forces[index];
				//std::cout << "force value:\trow:" << i << "\tcol:" << j << "\t:" << curValue << "\t";
				value += curValue;
			}
			//std::cout << "\n";
		}
		return (value > 0);
	}
	else
		return false;
}

bool TactonicDLL::getPressUp(int index)
{
	
	return false;
}

TactonicFrame* TactonicDLL::getFrame(int frameIdx)
{
	return &m_pFrame[frameIdx][0];
}

bool TactonicDLL::getFrame(int* frame, int * deviceCnt, int* cnt, int* tot)
{
	// copy from m_pFrame to frame
	deviceCnt[0] = m_pInstance->m_pDeviceList->numDevices;
	for(int idx = 0; idx < deviceCnt[0]; idx++){
		int cols = m_pFrame[idx]->cols;
		int rows = m_pFrame[idx]->rows;
		//float value = 0;
		for(int i = 0; i < rows; i ++){
			for(int j = 0; j < cols; j++){
				int index = i * cols + j;
				int curValue = m_pFrame[idx]->forces[index];
				if(curValue != 0){
					OutputDebugStringA(std::to_string(curValue).c_str());
					++cnt[0];
				}
				frame[idx * cols * rows + index] = curValue;
				tot[0] += curValue;
			}
			std::cout << "\n";
		}
	}
	return (tot[0] > 0);
	//return false;
}

void TactonicDLL::init()
{
	// init tactonic module
	m_pDeviceList = Tactonic_GetDeviceList();                        // Get available devices
	Sleep(1000);
	
	// Set up the Tactonic Device and register the callback function
	switch (m_pDeviceList->numDevices){
	case 1:
		// for now we start with one floor
		device0 = m_pDeviceList->devices[0];                         // Get the device
		//viewer.init(device0, argc, argv);							// Initialize the View Renderer
		//TactonicTouch_DetectorInitiation(m_pDeviceList->numDevices); 
		//m_pFrame[0] = Tactonic_CreateFrame(device0);                   // Create a TactonicFrame for this device
		m_pFrame0 = Tactonic_CreateFrame(device0);
		//touchFrame = TactonicTouch_CreateFrame(device0);         // Create a TactonicTouchFrame for this device
		//Tactonic_AddFrameCallback(device0, frameCallbackTest);       // Add a TactonicFrame callback method
		Tactonic_AddFrameCallback(device0, frameCallback);       // Add a TactonicFrame callback method
		//TactonicTouch_CreateDetector(device0);                   // Create the touch detector for the device
		//TactonicTouch_AddTouchCallback(device0, touchCallback);  // Add a TactonicTouchFrame callback method
		//TactonicTouch_StartDetector(device0);                    // Start the touch detector
		Tactonic_StartDevice(device0);                           // Start the device
		break;
	case 2:
		//1 Initiation
		device0 = m_pDeviceList->devices[0];                         // Get the device0
		device1 = m_pDeviceList->devices[1];                         // Get the device1

		//device01= device0;//==device1
		//device01.rows= device0.rows+device1.rows;//==device1.cols
		//todo
		//device01.serialNumber= (device0.serialNumber+device1.serialNumber);

		//viewer.init(device01, argc, argv);							// Initialize the View Renderer
		m_pFrame0 = Tactonic_CreateFrame(device0);                   // Create a TactonicFrame for this device
		m_pFrame1 = Tactonic_CreateFrame(device1);                   // Create a TactonicFrame for this device
		//frame  = Tactonic_CreateFrame(device01);                   // Create a TactonicFrame for this device
		//touchFrame0 = TactonicTouch_CreateFrame(device0);         // Create a TactonicTouchFrame for this device
		//touchFrame1 = TactonicTouch_CreateFrame(device1);         
		//touchFrame  = TactonicTouch_CreateFrame(device01);   
		//AllocationTouchFrame0=new TactonicAllocateTouchFrame;
		//AllocationTouchFrame1=new TactonicAllocateTouchFrame;

		//TactonicTouch_DetectorInitiation(deviceList->numDevices);
		//TactonicTouch_CreateDetector(device0);                   // Create the touch detector for the device
		//TactonicTouch_CreateDetector(device1); 
		//2 setup callback functions
		Tactonic_AddFrameCallback(device0, frameCallback0);       // Add a TactonicFrame callback method
		Tactonic_AddFrameCallback(device1, frameCallback1);       // Add a TactonicFrame callback method
		//TactonicTouch_AddTouchCallback(device0, touchCallback0);  // Add a TactonicTouchFrame callback method
		//TactonicTouch_AddTouchCallback(device1, touchCallback1);  // Add a TactonicTouchFrame callback method
		//3 Enable each function
		//TactonicTouch_StartDetector(device0);                    // Start the touch detector
		//TactonicTouch_StartDetector(device1);                    // Start the touch detector
		Tactonic_StartDevice(device0);                           // Start the device
		Tactonic_StartDevice(device1); 
		break;
	case 4:
		break;
	default:
		break;
	}
	m_bInit = true;
	m_pFrame[0] = m_pFrame0;
	m_pFrame[1] = m_pFrame1;
}

void frameCallback(TactonicFrameEvent* evt){            // TactonicFrame callback registered in the main
	Tactonic_CopyFrame(evt->frame,TactonicDLL::getInstance()->m_pFrame0);               // Copy the callback frame to a local frame
}

void frameCallback0(TactonicFrameEvent* evt){            // TactonicFrame callback registered in the main
	Tactonic_CopyFrame(evt->frame,TactonicDLL::getInstance()->m_pFrame0);               // Copy the callback frame to a local frame
}

void frameCallback1(TactonicFrameEvent* evt){            // TactonicFrame callback registered in the main
	Tactonic_CopyFrame(evt->frame,TactonicDLL::getInstance()->m_pFrame1);               // Copy the callback frame to a local frame
}

void frameCallbackTest(TactonicFrameEvent* evt)
{
	Tactonic_CopyFrame(evt->frame,TactonicDLL::getInstance()->m_pTestFrame);               // Copy the callback frame to a local frame
	memcpy_s(TactonicDLL::getInstance()->getFrame(0),sizeof(TactonicFrame),
		TactonicDLL::getInstance()->m_pTestFrame,sizeof(TactonicFrame));
}
