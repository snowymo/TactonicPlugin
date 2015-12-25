#define EXPORTBUILD_TACTONIC

#include "ExportTactonicDLL.h"

// extern "C" bool _DLLExport getPressDown(int index)
// {
// 	//return false;
// 	return TactonicDLL::getInstance()->getPressDown(index);
// }

// extern "C" bool _DLLExport getPressUp(int index)
// {
// 	return TactonicDLL::getInstance()->getPressUp(index);
// }

extern "C" bool _DLLExport getSingleFrame(int* frame, int* nCount, int* nTotal)
{
	return TactonicDLL::getInstance()->getFrame(frame, nCount, nTotal);
}

extern "C" bool _DLLExport getMultiFrame(int* frame, int* nDev, int* nCount, int* nTotal)
{
	return TactonicDLL::getInstance()->getMultiFrame(frame, nDev, nCount, nTotal);
}
