@ECHO OFF
set JoyAngVel=1
set JoyTransVel=1
REM Select the Language in the next line 1=English  2=French  3=Spanish  4=German
set Language=1
VirtualHouse.exe default.txt /TESTMODE /LANGUAGE %Language% /JOYTRANSVEL %JoyTransVel% /JOYANGVEL %JoyAngVel%
