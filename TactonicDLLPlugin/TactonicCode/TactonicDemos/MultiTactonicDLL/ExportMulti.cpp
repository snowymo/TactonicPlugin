#define EXPORTBUILD_TACTONIC

#include "ExportMulti.h"

extern "C" bool _DLLExport getMultiFrame(int* frame, int* devCnt, int* nCount, int* nTotal)
{
	return MultiTactonicDLL::getInstance()->getFrame(frame, devCnt, nCount, nTotal);
}
