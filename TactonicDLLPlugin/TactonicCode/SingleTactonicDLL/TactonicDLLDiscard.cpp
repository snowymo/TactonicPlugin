#include "TactonicDLL.h"
#include <time.h>
#include <iostream>
#include <string>


TactonicFrame* TactonicDLL::getFrame()
{
	return m_pFrames[0];
}


bool TactonicDLL::getPressDown(int index)
{
	// everything is stored in frame.force
	// it is a 2D array stored in 1D
	if (m_pInstance->m_pDeviceList->numDevices != 0) {
		int cols = m_pFrame->cols;
		int rows = m_pFrame->rows;
		float value = 0;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				int index = i * cols + j;
				int curValue = m_pFrame->forces[index];
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
