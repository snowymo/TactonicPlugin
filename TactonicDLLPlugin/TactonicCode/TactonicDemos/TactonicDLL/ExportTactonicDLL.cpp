#define EXPORTBUILD_TACTONIC

#include "ExportTactonicDLL.h"

extern "C" bool _DLLExport getPressDown(int index)
{
	//return false;
	return TactonicDLL::getInstance()->getPressDown(index);
}

extern "C" bool _DLLExport getPressUp(int index)
{
	return TactonicDLL::getInstance()->getPressUp(index);
}

extern "C" bool _DLLExport getFrame(int* frame, int* nDevice, int* nCount, int* nTotal)
{
	return TactonicDLL::getInstance()->getFrame(frame, nDevice, nCount, nTotal);
}
