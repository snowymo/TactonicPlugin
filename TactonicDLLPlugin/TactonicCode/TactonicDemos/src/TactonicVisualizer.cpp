// ====================================================================
// Copyright 2010-2012 Tactonics Technologies, LLC. All rights reserved
// PROPRIETARY/CONFIDENTIAL - DO NOT DISTRIBUTE!
// DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
// ====================================================================

#include "Tactonic.h"
//#include "TactonicTouch.h"
#include "DisplayViews.h"

TactonicDevice device0,device1,device2,device3;              // The device that we are monitoring
TactonicDevice device01,device0123; 
TactonicFrame *frame0,*frame1,*frame2,*frame3; 
TactonicFrame *frame;               // An Anti-Aliased Frame of data from the device
//TactonicTouchFrame *touchFrame0,*touchFrame1,*touchFrame2,*touchFrame3;
//TactonicTouchFrame *touchFrame;     // A list of touches that were detected for a given TactonicFrame
//TactonicAllocateTouchFrame* AllocationTouchFrame0;
//TactonicAllocateTouchFrame* AllocationTouchFrame1;
//TactonicAllocateTouchFrame* AllocationTouchFrame2;
//TactonicAllocateTouchFrame* AllocationTouchFrame3;
DisplayViews viewer;                // Renders the Visualizer Views 

void frameCallback(TactonicFrameEvent* evt);
//void touchCallback(TactonicTouchEvent* evt);

void frameCallback0(TactonicFrameEvent* evt);
void frameCallback1(TactonicFrameEvent* evt);
//void touchCallback0(TactonicTouchEvent* evt);
//void touchCallback1(TactonicTouchEvent* evt);

void frameCallback00(TactonicFrameEvent* evt);
void frameCallback11(TactonicFrameEvent* evt);
void frameCallback2(TactonicFrameEvent* evt);
void frameCallback3(TactonicFrameEvent* evt);
//void touchCallback00(TactonicTouchEvent* evt);
//void touchCallback11(TactonicTouchEvent* evt);
//void touchCallback2(TactonicTouchEvent* evt);
//void touchCallback3(TactonicTouchEvent* evt);

void display();
void keyEvent(unsigned char key, int x, int y);
void reshape(GLsizei width, GLsizei height);

bool switch_0_1=true;

int main(int argc, char *argv[]) {

	glutInit(&argc,argv);                                       // Set up OpenGL for rendering the Visualization
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);                // Standard OpenGL Initialization
	glutInitWindowSize(WIDTH, HEIGHT);                          // Standard OpenGL Initialization
	glutInitWindowPosition(0,0);
	glutCreateWindow("Tactonic Technologies");                  // Standard OpenGL Initialization
	glutKeyboardFunc(keyEvent);                                 // Register OpenGL Key Handler		
	glutDisplayFunc(display);                                   // Register OpenGL Rendering Handler
	glutIdleFunc(display);                                      // Register OpenGL Idle Handler
	glutReshapeFunc(reshape);                                   // Register OpenGL Reshape Handler
	TactonicDeviceList *deviceList;                              // Data Structure for retrieving available devices
	deviceList = Tactonic_GetDeviceList();                        // Get available devices

	Sleep(1000);
	if(deviceList->numDevices > 0 && deviceList->numDevices < 2 ){                              // Set up the Tactonic Device and register the callback function
		device0 = deviceList->devices[0];                         // Get the device
		viewer.init(device0, argc, argv);							// Initialize the View Renderer
		//TactonicTouch_DetectorInitiation(deviceList->numDevices); 
		frame = Tactonic_CreateFrame(device0);                   // Create a TactonicFrame for this device
		//touchFrame = TactonicTouch_CreateFrame(device0);         // Create a TactonicTouchFrame for this device
		Tactonic_AddFrameCallback(device0, frameCallback);       // Add a TactonicFrame callback method
		//TactonicTouch_CreateDetector(device0);                   // Create the touch detector for the device
		//TactonicTouch_AddTouchCallback(device0, touchCallback);  // Add a TactonicTouchFrame callback method
		//TactonicTouch_StartDetector(device0);                    // Start the touch detector
		Tactonic_StartDevice(device0);                           // Start the device
		glutMainLoop();                                         // Start the GLUT display loop
	}
	if(deviceList->numDevices > 0 && deviceList->numDevices ==2 ){                              // Set up the Tactonic Device and register the callback function
		//1 Initiation
		device0 = deviceList->devices[0];                         // Get the device0
		device1 = deviceList->devices[1];                         // Get the device1

		device01= device0;//==device1
		device01.rows= device0.rows+device1.rows;//==device1.cols
		device01.serialNumber= (device0.serialNumber+device1.serialNumber);

		viewer.init(device01, argc, argv);							// Initialize the View Renderer
		frame0 = Tactonic_CreateFrame(device0);                   // Create a TactonicFrame for this device
		frame1 = Tactonic_CreateFrame(device1);                   // Create a TactonicFrame for this device
		frame  = Tactonic_CreateFrame(device01);                   // Create a TactonicFrame for this device
		//touchFrame0 = TactonicTouch_CreateFrame(device0);         // Create a TactonicTouchFrame for this device
		//touchFrame1 = TactonicTouch_CreateFrame(device1);         
		//touchFrame  = TactonicTouch_CreateFrame(device01);   
		//AllocationTouchFrame0=new TactonicAllocateTouchFrame;
		//AllocationTouchFrame1=new TactonicAllocateTouchFrame;

		/*TactonicTouch_DetectorInitiation(deviceList->numDevices);
		TactonicTouch_CreateDetector(device0);                   // Create the touch detector for the device
		TactonicTouch_CreateDetector(device1); */
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

		glutMainLoop();                                         // Start the GLUT display loop
	}
	else if(deviceList->numDevices > 0 && deviceList->numDevices ==4 ){                              // Set up the Tactonic Device and register the callback function
		//1 Initiation
		device0 = deviceList->devices[0];                         // Get the device0
		device1 = deviceList->devices[1];                         // Get the device1
		device2 = deviceList->devices[2];                         // Get the device2
		device3 = deviceList->devices[3];                         // Get the device3

		device0123= device0;//==device1
		device0123.rows= device0.rows+device1.rows;//==device1.cols
		device0123.cols= device0.cols+device1.cols;//==device1.cols
		device0123.serialNumber= (device0.serialNumber+device1.serialNumber+device2.serialNumber+device3.serialNumber);

		viewer.init(device0123, argc, argv);							// Initialize the View Renderer
		frame0 = Tactonic_CreateFrame(device0);                   // Create a TactonicFrame for this device
		frame1 = Tactonic_CreateFrame(device1);                   // Create a TactonicFrame for this device
		frame2 = Tactonic_CreateFrame(device2);                   // Create a TactonicFrame for this device
		frame3 = Tactonic_CreateFrame(device3);                   // Create a TactonicFrame for this device
		frame  = Tactonic_CreateFrame(device0123);                   // Create a TactonicFrame for this device
		/*
		touchFrame0 = TactonicTouch_CreateFrame(device0);         // Create a TactonicTouchFrame for this device
		touchFrame1 = TactonicTouch_CreateFrame(device1); 
		touchFrame2 = TactonicTouch_CreateFrame(device2);         // Create a TactonicTouchFrame for this device
		touchFrame3 = TactonicTouch_CreateFrame(device3); 
		touchFrame  = TactonicTouch_CreateFrame(device0123);   
		
		AllocationTouchFrame0=new TactonicAllocateTouchFrame;
		AllocationTouchFrame1=new TactonicAllocateTouchFrame;
		AllocationTouchFrame2=new TactonicAllocateTouchFrame;
		AllocationTouchFrame3=new TactonicAllocateTouchFrame;

		TactonicTouch_DetectorInitiation(deviceList->numDevices);
		TactonicTouch_CreateDetector(device0);                   // Create the touch detector for the device
		TactonicTouch_CreateDetector(device1);
		TactonicTouch_CreateDetector(device2);                   // Create the touch detector for the device
		TactonicTouch_CreateDetector(device3);
		*/
		//2 setup callback functions
		Tactonic_AddFrameCallback(device0, frameCallback00);       // Add a TactonicFrame callback method
		Tactonic_AddFrameCallback(device1, frameCallback11);       // Add a TactonicFrame callback method
		Tactonic_AddFrameCallback(device2, frameCallback2);       // Add a TactonicFrame callback method
		Tactonic_AddFrameCallback(device3, frameCallback3);       // Add a TactonicFrame callback method
		//TactonicTouch_AddTouchCallback(device0, touchCallback00);  // Add a TactonicTouchFrame callback method
		//TactonicTouch_AddTouchCallback(device1, touchCallback11);  // Add a TactonicTouchFrame callback method
		//TactonicTouch_AddTouchCallback(device2, touchCallback2);  // Add a TactonicTouchFrame callback method
		//TactonicTouch_AddTouchCallback(device3, touchCallback3);  // Add a TactonicTouchFrame callback method
		//3 Enable each function
		/*TactonicTouch_StartDetector(device0);                    // Start the touch detector
		TactonicTouch_StartDetector(device1);                    // Start the touch detector
		TactonicTouch_StartDetector(device2);                    // Start the touch detector
		TactonicTouch_StartDetector(device3);                    // Start the touch detector
		*/
		Tactonic_StartDevice(device0);                           // Start the device
		Tactonic_StartDevice(device1); 
		Tactonic_StartDevice(device2);                           // Start the device
		Tactonic_StartDevice(device3); 

		glutMainLoop();                                         // Start the GLUT display loop
	}
	else{                                                       // If no devices, close the program
		printf("No devices available.");
		Sleep(1000);
	}
	return 0;
}


void frameCallback0(TactonicFrameEvent* evt){            // TactonicFrame callback registered in the main
	Tactonic_CopyFrame(evt->frame,frame0);               // Copy the callback frame to a local frame
	frame->frameNumber=frame0->frameNumber*4;
	for (int i=0;i<frame->numForces/2;i++)
	{
		frame->forces[i]=frame0->forces[i];
	}
}
void frameCallback1(TactonicFrameEvent* evt){            // TactonicFrame callback registered in the main
	Tactonic_CopyFrame(evt->frame,frame1);               // Copy the callback frame to a local frame
	for (int i=0;i<frame->numForces/2;i++)
	{
		frame->forces[i+(frame->rows*frame->cols/2)]=frame1->forces[i];
	}
}

//0 Left bottom 1 Left top 2 Right bottom 3 Right top
void frameCallback00(TactonicFrameEvent* evt){            // TactonicFrame callback registered in the main
	Tactonic_CopyFrame(evt->frame,frame0);               // Copy the callback frame to a local frame
	frame->frameNumber=frame0->frameNumber*4;
	int step_col=frame->cols/2;//80
    int step_row=frame->rows/2;
	int end_point=step_row*step_col-1;
	for (int i=0;i<frame->numForces/4;i++)
	{
		frame->forces[i+(i/step_col)*step_col]=frame0->forces[end_point-i];
	}
}
void frameCallback11(TactonicFrameEvent* evt){            // TactonicFrame callback registered in the main
	Tactonic_CopyFrame(evt->frame,frame1);               // Copy the callback frame to a local frame
	int step_col=frame->cols/2;
	int step_row=frame->rows/2;
	int end_point=step_row*step_col-1;
	for (int i=0;i<frame->numForces/4;i++)
	{
		frame->forces[ (i+(i/step_col)*step_col+step_row*frame->cols)]=frame1->forces[end_point-i];
	}
}
void frameCallback2(TactonicFrameEvent* evt){            // TactonicFrame callback registered in the main
	Tactonic_CopyFrame(evt->frame,frame2);               // Copy the callback frame to a local frame
	int step_col=frame->cols/2;
	int step_row=frame->rows/2;
	for (int i=0;i<frame->numForces/4;i++)
	{
		frame->forces[i+((i/step_col)+1)*step_col]=frame2->forces[i];
	}
}
void frameCallback3(TactonicFrameEvent* evt){            // TactonicFrame callback registered in the main
	Tactonic_CopyFrame(evt->frame,frame3);               // Copy the callback frame to a local frame
	int step_col=frame->cols/2;
	int step_row=frame->rows/2;
	for (int i=0;i<frame->numForces/4;i++)
	{
			frame->forces[i+((i/step_col)+1)*step_col+step_row*frame->cols]=frame3->forces[i];
	}
}





//void touchCallback0(TactonicTouchEvent* evt){            // TactonicTouchFrame callback registered in the main
//	TactonicTouch_CopyFrame(evt->frame, touchFrame);    // Copy the callback touch frame to a local frame
//	viewer.registerTouches(touchFrame);                 // Register the touch frame in the display views
//}

/*
void touchCallback0(TactonicTouchEvent* evt){            // TactonicTouchFrame callback registered in the main
	TactonicTouch_CopyFrame(evt->frame, touchFrame0);    // Copy the callback touch frame to a local frame
	touchFrame->time=touchFrame0->time;

	AllocationTouchFrame0->srcFrame=touchFrame0;
	AllocationTouchFrame0->dstFrame=touchFrame;
	AllocationTouchFrame0->pos_x=0;
	AllocationTouchFrame0->pos_y=0;
	AllocationTouchFrame0->dstFrame->numTouches=touchFrame0->numTouches+touchFrame1->numTouches;
	AllocationTouchFrame0->numTouches=0;
	AllocationTouchFrame0->dstFrame->frameNumber=0;
	AllocationTouchFrame0->dstFrame->time=touchFrame0->time;
	TactonicTouch_AllocateTouchFrame( AllocationTouchFrame0); 

}
*/
/*
void touchCallback1(TactonicTouchEvent* evt){            // TactonicTouchFrame callback registered in the main
	TactonicTouch_CopyFrame(evt->frame, touchFrame1);    // Copy the callback touch frame to a local frame
	AllocationTouchFrame1->srcFrame=touchFrame1;
	AllocationTouchFrame1->dstFrame=touchFrame;
	AllocationTouchFrame1->pos_x=0;
	AllocationTouchFrame1->pos_y=309.5;//205.5
	AllocationTouchFrame1->dstFrame->numTouches=touchFrame0->numTouches+touchFrame1->numTouches;
	AllocationTouchFrame1->numTouches=touchFrame0->numTouches;
	AllocationTouchFrame1->dstFrame->frameNumber=0;
	AllocationTouchFrame1->dstFrame->time=touchFrame1->time;
	TactonicTouch_AllocateTouchFrame( AllocationTouchFrame1);
	//touchFrame->time=touchFrame1->time;
	//touchFrame->frameNumber=touchFrame1->frameNumber;

	//touchFrame->frameNumber=0;
	//touchFrame->numTouches=touchFrame0->numTouches+touchFrame1->numTouches;

	//for (int i=0;i<touchFrame1->numTouches;i++)
	//{
	//	touchFrame->touches[i+touchFrame0->numTouches].x=touchFrame1->touches[i].x;
	//	touchFrame->touches[i+touchFrame0->numTouches].y=touchFrame1->touches[i].y+205.5;//2*device0.rows;
	//	touchFrame->touches[i+touchFrame0->numTouches].force=touchFrame1->touches[i].force;
	//	touchFrame->touches[i+touchFrame0->numTouches].dx=touchFrame1->touches[i].dx;
	//	touchFrame->touches[i+touchFrame0->numTouches].dy=touchFrame1->touches[i].dy;
	//	touchFrame->touches[i+touchFrame0->numTouches].dForce=touchFrame1->touches[i].dForce;
	//	touchFrame->touches[i+touchFrame0->numTouches].id=touchFrame1->touches[i].id+touchFrame0->numTouches;
	//	touchFrame->touches[i+touchFrame0->numTouches].touchState=touchFrame1->touches[i].touchState;
	//}
	viewer.registerTouches(touchFrame);                 // Register the touch frame in the display views
}
*/


/*
void touchCallback00(TactonicTouchEvent* evt){            // TactonicTouchFrame callback registered in the main
	TactonicTouch_CopyFrame(evt->frame, touchFrame0);    // Copy the callback touch frame to a local frame
	//printf("TouchCallback0 %d\n",touchFrame0->numTouches);
	touchFrame->time=touchFrame0->time;
	//touchFrame->frameNumber=touchFrame0->frameNumber;
	AllocationTouchFrame0->srcFrame=touchFrame0;
	AllocationTouchFrame0->dstFrame=touchFrame;
	AllocationTouchFrame0->pos_x=0;
	AllocationTouchFrame0->pos_y=0;
	AllocationTouchFrame0->dstFrame->numTouches=touchFrame0->numTouches+touchFrame1->numTouches+touchFrame2->numTouches+touchFrame3->numTouches;
	AllocationTouchFrame0->numTouches=0;
	AllocationTouchFrame0->dstFrame->frameNumber=0;
	AllocationTouchFrame0->dstFrame->time=touchFrame0->time;
	TactonicTouch_AllocateTouchFrame( AllocationTouchFrame0); 
}
void touchCallback11(TactonicTouchEvent* evt){            // TactonicTouchFrame callback registered in the main
	TactonicTouch_CopyFrame(evt->frame, touchFrame1);    // Copy the callback touch frame to a local frame
	//printf("TouchCallback1 %d \n",touchFrame1->numTouches);
	AllocationTouchFrame1->srcFrame=touchFrame1;
	AllocationTouchFrame1->dstFrame=touchFrame;
	AllocationTouchFrame1->pos_y=205.5;
	AllocationTouchFrame1->dstFrame->numTouches=touchFrame0->numTouches+touchFrame1->numTouches+touchFrame2->numTouches+touchFrame3->numTouches;
	AllocationTouchFrame1->numTouches=touchFrame0->numTouches;
	AllocationTouchFrame1->dstFrame->frameNumber=0;
	AllocationTouchFrame1->dstFrame->time=touchFrame1->time;
	TactonicTouch_AllocateTouchFrame( AllocationTouchFrame1);
}



void touchCallback2(TactonicTouchEvent* evt){            // TactonicTouchFrame callback registered in the main
	TactonicTouch_CopyFrame(evt->frame, touchFrame1);    // Copy the callback touch frame to a local frame
	//printf("TouchCallback1 %d \n",touchFrame1->numTouches);
	AllocationTouchFrame2->srcFrame=touchFrame2;
	AllocationTouchFrame2->dstFrame=touchFrame;
	AllocationTouchFrame2->pos_x=280;
	AllocationTouchFrame2->pos_y=0;
	AllocationTouchFrame2->dstFrame->numTouches=touchFrame0->numTouches+touchFrame1->numTouches+touchFrame2->numTouches+touchFrame3->numTouches;
	AllocationTouchFrame2->numTouches=touchFrame0->numTouches;
	AllocationTouchFrame2->dstFrame->frameNumber=0;
	AllocationTouchFrame2->dstFrame->time=touchFrame2->time;
	TactonicTouch_AllocateTouchFrame( AllocationTouchFrame2);
	//viewer.registerTouches(touchFrame);                 // Register the touch frame in the display views 
}
void touchCallback3(TactonicTouchEvent* evt){            // TactonicTouchFrame callback registered in the main
	TactonicTouch_CopyFrame(evt->frame, touchFrame1);    // Copy the callback touch frame to a local frame
	//printf("TouchCallback1 %d \n",touchFrame1->numTouches);
	AllocationTouchFrame3->srcFrame=touchFrame3;
	AllocationTouchFrame3->dstFrame=touchFrame;
	AllocationTouchFrame2->pos_x=280;
	AllocationTouchFrame3->pos_y=205.5;
	AllocationTouchFrame3->dstFrame->numTouches=touchFrame0->numTouches+touchFrame1->numTouches+touchFrame2->numTouches+touchFrame3->numTouches;
	AllocationTouchFrame3->numTouches=touchFrame0->numTouches;
	AllocationTouchFrame3->dstFrame->frameNumber=0;
	AllocationTouchFrame3->dstFrame->time=touchFrame3->time;
	TactonicTouch_AllocateTouchFrame( AllocationTouchFrame3);
	viewer.registerTouches(touchFrame);                 // Register the touch frame in the display views
}
*/

void frameCallback(TactonicFrameEvent* evt){            // TactonicFrame callback registered in the main
	Tactonic_CopyFrame(evt->frame,frame);               // Copy the callback frame to a local frame
}
/*
void touchCallback(TactonicTouchEvent* evt){            // TactonicTouchFrame callback registered in the main
	TactonicTouch_CopyFrame(evt->frame, touchFrame);    // Copy the callback touch frame to a local frame
	viewer.registerTouches(touchFrame);                 // Register the touch frame in the display views
}
*/
void display(){											// Glut display loop
	viewer.display(frame);                  // Render the current frame
}

void keyEvent(unsigned char key, int x, int y){			// Glut key event
	viewer.keyEvent(key);								// Send the key event to the visualizer so it may change modes
}

void reshape(GLsizei width, GLsizei height){			// Glut window resized
	viewer.reshape(width,height);						// Window was resized, send new shape to renderer
}