@ECHO OFF
set JoyAngVel=1
set JoyTransVel=1
REM Select the Language in the next line 1=English  2=French  3=Spanish  4=German
set Language=1
For /f "tokens=2-4 delims=/ " %%a in ('date /t') do (set mydate=%%c-%%a-%%b)
color 2
title Virtual House test
ECHO Welcome to the Virtual House test (Allocentric Mode)
set /p patientname=Please enter the subject name:

md %patientname%%date:~10,4%-%date:~4,2%-%date:~7,2%_ALLO

VirtualHouse.exe %patientname%%mydate%_ALLO\%patientname%%mydate%_1.txt /LANGUAGE %Language% /JOYTRANSVEL %JoyTransVel% /JOYANGVEL %JoyAngVel% /ALLOCENTRIC /NOINFO /AUTOEXIT /USEJOYSTICK /TRIAL 1 /LOGTOTAL %patientname%%mydate%_ALLO\%patientname%%mydate%_ALLO.txt
VirtualHouse.exe %patientname%%mydate%_ALLO\%patientname%%mydate%_2.txt /LANGUAGE %Language% /JOYTRANSVEL %JoyTransVel% /JOYANGVEL %JoyAngVel% /ALLOCENTRIC /NOINFO /AUTOEXIT /USEJOYSTICK /TRIAL 2 /LOGTOTAL %patientname%%mydate%_ALLO\%patientname%%mydate%_ALLO.txt
VirtualHouse.exe %patientname%%mydate%_ALLO\%patientname%%mydate%_3.txt /LANGUAGE %Language% /JOYTRANSVEL %JoyTransVel% /JOYANGVEL %JoyAngVel% /ALLOCENTRIC /NOINFO /AUTOEXIT /USEJOYSTICK /TRIAL 3 /LOGTOTAL %patientname%%mydate%_ALLO\%patientname%%mydate%_ALLO.txt
VirtualHouse.exe %patientname%%mydate%_ALLO\%patientname%%mydate%_4.txt /LANGUAGE %Language% /JOYTRANSVEL %JoyTransVel% /JOYANGVEL %JoyAngVel% /ALLOCENTRIC /NOINFO /AUTOEXIT /USEJOYSTICK /TRIAL 4 /LOGTOTAL %patientname%%mydate%_ALLO\%patientname%%mydate%_ALLO.txt
VirtualHouse.exe %patientname%%mydate%_ALLO\%patientname%%mydate%_5.txt /LANGUAGE %Language% /JOYTRANSVEL %JoyTransVel% /JOYANGVEL %JoyAngVel% /ALLOCENTRIC /NOINFO /AUTOEXIT /USEJOYSTICK /TRIAL 5 /LOGTOTAL %patientname%%mydate%_ALLO\%patientname%%mydate%_ALLO.txt
VirtualHouse.exe %patientname%%mydate%_ALLO\%patientname%%mydate%_6.txt /LANGUAGE %Language% /JOYTRANSVEL %JoyTransVel% /JOYANGVEL %JoyAngVel% /ALLOCENTRIC /NOINFO /AUTOEXIT /USEJOYSTICK /TRIAL 6 /LOGTOTAL %patientname%%mydate%_ALLO\%patientname%%mydate%_ALLO.txt
VirtualHouse.exe %patientname%%mydate%_ALLO\%patientname%%mydate%_7.txt /LANGUAGE %Language% /JOYTRANSVEL %JoyTransVel% /JOYANGVEL %JoyAngVel% /ALLOCENTRIC /NOINFO /AUTOEXIT /USEJOYSTICK /TRIAL 7 /LOGTOTAL %patientname%%mydate%_ALLO\%patientname%%mydate%_ALLO.txt
VirtualHouse.exe %patientname%%mydate%_ALLO\%patientname%%mydate%_8.txt /LANGUAGE %Language% /JOYTRANSVEL %JoyTransVel% /JOYANGVEL %JoyAngVel% /ALLOCENTRIC /NOINFO /AUTOEXIT /USEJOYSTICK /TRIAL 8 /LOGTOTAL %patientname%%mydate%_ALLO\%patientname%%mydate%_ALLO.txt
VirtualHouse.exe %patientname%%mydate%_ALLO\%patientname%%mydate%_9.txt /LANGUAGE %Language% /JOYTRANSVEL %JoyTransVel% /JOYANGVEL %JoyAngVel% /ALLOCENTRIC /NOINFO /AUTOEXIT /USEJOYSTICK /TRIAL 9 /LOGTOTAL %patientname%%mydate%_ALLO\%patientname%%mydate%_ALLO.txt

