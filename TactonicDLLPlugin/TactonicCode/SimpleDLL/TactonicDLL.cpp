#include "TactonicDLL.h"
#include <time.h>
#include <iostream>

TactonicDLL::TactonicDLL(void)
{
}


TactonicDLL::~TactonicDLL(void)
{
	if(m_pInstance)
		delete m_pInstance;
	m_pInstance = NULL;
}

TactonicDLL* TactonicDLL::getInstance()
{
	if(!m_pInstance){
		m_pInstance = new TactonicDLL;
		//m_pInstance->init();
	}
	return m_pInstance;
}

bool TactonicDLL::getPressDown(int index)
{
	// everything is stored in frame.force
	// it is a 2D array stored in 1D
// 	int cols = m_pFrame->cols;
// 	int rows = m_pFrame->rows;
// 	float value;
// 	for(int i = 0; i < rows; i ++){
// 		for(int j = 0; j < cols; j++){
// 			int index = i * cols + j;
// 			value = m_pFrame->forces[index];
// 			std::cout << "force value:\trow:" << i << "\tcol:" << j << "\t:" << value << "\t";
// 		}
// 		std::cout << "\n";
// 	}
	return false;
}

bool TactonicDLL::getPressUp(int index)
{
	
	return false;
}

TactonicFrame* TactonicDLL::getFrame()
{
	return m_pFrame;
}

TactonicDLL* TactonicDLL::m_pInstance = NULL;

void TactonicDLL::init()
{
	// init tactonic module
	m_pDeviceList = Tactonic_GetDeviceList();                        // Get available devices
	// for now we start with one floor
	if(m_pDeviceList->numDevices > 0 && m_pDeviceList->numDevices == 1 ){                              // Set up the Tactonic Device and register the callback function
		device0 = m_pDeviceList->devices[0];                         // Get the device
		//viewer.init(device0, argc, argv);							// Initialize the View Renderer
		//TactonicTouch_DetectorInitiation(m_pDeviceList->numDevices); 
		m_pFrame = Tactonic_CreateFrame(device0);                   // Create a TactonicFrame for this device
		//touchFrame = TactonicTouch_CreateFrame(device0);         // Create a TactonicTouchFrame for this device
		Tactonic_AddFrameCallback(device0, frameCallback);       // Add a TactonicFrame callback method
		//TactonicTouch_CreateDetector(device0);                   // Create the touch detector for the device
		//TactonicTouch_AddTouchCallback(device0, touchCallback);  // Add a TactonicTouchFrame callback method
		//TactonicTouch_StartDetector(device0);                    // Start the touch detector
		Tactonic_StartDevice(device0);                           // Start the device
	}
}

void frameCallback(TactonicFrameEvent* evt){            // TactonicFrame callback registered in the main
	Tactonic_CopyFrame(evt->frame,TactonicDLL::getInstance()->getFrame());               // Copy the callback frame to a local frame
}