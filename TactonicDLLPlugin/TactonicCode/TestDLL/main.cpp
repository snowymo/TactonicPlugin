// test dll in main
// by Zhenyi

//#include "../TactonicDemos -send out version/TactonicDLL/ExportTactonicDLL.h"
#include "ExportTactonicDLL.h"

void testTactonicFrame()
{
	// test dll export function
	getPressDown(0);

	int * frame = new int[48*60];
	int * cnt = new int[1];
	cnt[0] = 0;
	int * tot = new int[1];
	tot[0] = 0;
	int * dvn = new int[1];
	getFrame(frame, dvn, cnt, tot);
	return;
}

int main()
{
	testTactonicFrame();
	return 0;
}