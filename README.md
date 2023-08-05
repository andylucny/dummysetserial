# dummysetserial
Dummy setserial for MS Windows

At the moment, it can perform only the command:

setserial COM7 low_latency

that decreases the timeout for reception on the com port. 
It helps speed up communication on the RS485 bus.

Copy setserial.exe into c:\windows or c:\cygwin64\bin
