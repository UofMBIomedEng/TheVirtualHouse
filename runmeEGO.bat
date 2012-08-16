@ECHO OFF
set JoyAngVel=1
set JoyTransVel=1
REM Select the Language in the next line 1=English  2=French  3=Spanish  4=German
set Language=1
For /f "tokens=2-4 delims=/ " %%a in ('date /t') do (set mydate=%%c-%%a-%%b)
color 2
title Virtual House test
ECHO Welcome to the Virtual House test (Egocentric Mode)
set /p patientname=Please enter the subject name:

md %patientname%%mydate%_EGO

VirtualHouse.exe %patientname%%mydate%_EGO\%patientname%%mydate%_1.txt /LANGUAGE %Language% /JOYTRANSVEL %JoyTransVel% /JOYANGVEL %JoyAngVel% /NOINFO /AUTOEXIT /USEJOYSTICK /TRIAL 1 /LOGTOTAL %patientname%%mydate%_EGO\%patientname%%mydate%_EGO.txt
VirtualHouse.exe %patientname%%mydate%_EGO\%patientname%%mydate%_2.txt /LANGUAGE %Language% /JOYTRANSVEL %JoyTransVel% /JOYANGVEL %JoyAngVel% /NOINFO /AUTOEXIT /USEJOYSTICK /TRIAL 2 /LOGTOTAL %patientname%%mydate%_EGO\%patientname%%mydate%_EGO.txt
VirtualHouse.exe %patientname%%mydate%_EGO\%patientname%%mydate%_3.txt /LANGUAGE %Language% /JOYTRANSVEL %JoyTransVel% /JOYANGVEL %JoyAngVel% /NOINFO /AUTOEXIT /USEJOYSTICK /TRIAL 3 /LOGTOTAL %patientname%%mydate%_EGO\%patientname%%mydate%_EGO.txt
VirtualHouse.exe %patientname%%mydate%_EGO\%patientname%%mydate%_4.txt /LANGUAGE %Language% /JOYTRANSVEL %JoyTransVel% /JOYANGVEL %JoyAngVel% /NOINFO /AUTOEXIT /USEJOYSTICK /TRIAL 4 /LOGTOTAL %patientname%%mydate%_EGO\%patientname%%mydate%_EGO.txt
VirtualHouse.exe %patientname%%mydate%_EGO\%patientname%%mydate%_5.txt /LANGUAGE %Language% /JOYTRANSVEL %JoyTransVel% /JOYANGVEL %JoyAngVel% /NOINFO /AUTOEXIT /USEJOYSTICK /TRIAL 5 /LOGTOTAL %patientname%%mydate%_EGO\%patientname%%mydate%_EGO.txt
VirtualHouse.exe %patientname%%mydate%_EGO\%patientname%%mydate%_6.txt /LANGUAGE %Language% /JOYTRANSVEL %JoyTransVel% /JOYANGVEL %JoyAngVel% /NOINFO /AUTOEXIT /USEJOYSTICK /TRIAL 6 /LOGTOTAL %patientname%%mydate%_EGO\%patientname%%mydate%_EGO.txt
VirtualHouse.exe %patientname%%mydate%_EGO\%patientname%%mydate%_7.txt /LANGUAGE %Language% /JOYTRANSVEL %JoyTransVel% /JOYANGVEL %JoyAngVel% /NOINFO /AUTOEXIT /USEJOYSTICK /TRIAL 7 /LOGTOTAL %patientname%%mydate%_EGO\%patientname%%mydate%_EGO.txt
VirtualHouse.exe %patientname%%mydate%_EGO\%patientname%%mydate%_8.txt /LANGUAGE %Language% /JOYTRANSVEL %JoyTransVel% /JOYANGVEL %JoyAngVel% /NOINFO /AUTOEXIT /USEJOYSTICK /TRIAL 8 /LOGTOTAL %patientname%%mydate%_EGO\%patientname%%mydate%_EGO.txt
