[SCE CONFIDENTIAL DOCUMENT]
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
                      Copyright (C) 2005 Sony Computer Entertainment Inc.
                                                     All Rights Reserved

A sample program demonstrating use of the sample framework.

< Description of the Sample >
	This is a sample program that uses the sample framework for
	initialization, input handling, text rendering etc.

	The main functions to examine are the application's callback
	functions, TestApp::onInit(), TestApp::onRender(),
	TestApp::onSize() & TestApp::onShutdown().

	TestApp::onInit() is called at startup and lets the application
	allocate any resources it may require. TestApp::onRender() is
	called once per frame and is used for rendering the scene.
	TestApp::onSize() is called if the display resolution changes
	during execution. TestApp::onShutdown() is called on termination
	of the application and allows the application to free any
	resources it had allocated.

< Files >
	TestApp.cpp, TestApp.h

< Activating the Program >
        $ make          : Compiles the program


< Using the Controller >
	A controller can be connected to the USB port and used to move
	the camera. The left stick is used to rotate the camera, and the
	right stick is used to move the camera.

< Displaying status of HID inputs >
	Input of a controller, a keyboard, and a mouse can be monitored
	on the screen. For a keyboard input, only space key is detected.

< Note >
	None
