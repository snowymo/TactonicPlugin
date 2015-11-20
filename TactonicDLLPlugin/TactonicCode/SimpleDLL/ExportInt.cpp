#define EXPORTBUILD_INT

#include "ExportInt.h"

extern "C" int _DLLExport getInt()
{
	MYINT myInt;
	return myInt.getInt(1,2);
}

extern "C" bool _DLLExport getPressDown(int index)
{
	//return false;
	return TactonicDLL::getInstance()->getPressDown(index);
}