// test dll in main
// by Zhenyi

//#include "../TactonicDemos -send out version/TactonicDLL/ExportTactonicDLL.h"
#include "ExportTactonicDLL.h"

void testTactonicFrame()
{
	// test dll export function
	getPressDown(0);
	return;
}

int main()
{
	testTactonicFrame();
	return 0;
}