#include <Windows.h>
#include <stdio.h>

int main( int argc, char *argv[]) {

    if (argc != 3) return 0;
    if (strcmp(argv[2], "low_latency")) return 0;
    if (strncmp(argv[1], "COM", 3)) return 0;

    HANDLE hComm;

    hComm = CreateFile(
        (LPCWSTR) argv[1],  
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (hComm == INVALID_HANDLE_VALUE) {
        printf("Failed to open the serial port. Error code: %d\n", GetLastError());
        return 1;
    }

    /*
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hComm, &dcbSerialParams)) {
        printf("Failed to get the serial port state. Error code: %d\n", GetLastError());
        CloseHandle(hComm);
        return 1;
    }

    // Modify the serial port flags to enable low latency mode
    dcbSerialParams.fBinary = TRUE;
    dcbSerialParams.fParity = FALSE;
    dcbSerialParams.fOutxCtsFlow = FALSE;
    dcbSerialParams.fOutxDsrFlow = FALSE;
    dcbSerialParams.fDtrControl = DTR_CONTROL_ENABLE;
    dcbSerialParams.fDsrSensitivity = FALSE;
    dcbSerialParams.fTXContinueOnXoff = TRUE;
    dcbSerialParams.fOutX = FALSE;
    dcbSerialParams.fInX = FALSE;
    dcbSerialParams.fErrorChar = FALSE;
    dcbSerialParams.fNull = FALSE;
    dcbSerialParams.fRtsControl = RTS_CONTROL_ENABLE;
    dcbSerialParams.fAbortOnError = FALSE;
    dcbSerialParams.XonLim = 2048;
    dcbSerialParams.XoffLim = 512;
    dcbSerialParams.XonChar = 17;
    dcbSerialParams.XoffChar = 19;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.Parity = NOPARITY;
    dcbSerialParams.StopBits = ONESTOPBIT;

    if (!SetCommState(hComm, &dcbSerialParams)) {
        printf("Failed to set the serial port state. Error code: %d\n", GetLastError());
        CloseHandle(hComm);
        return 1;
    }
    */

    COMMTIMEOUTS timeouts = { 0 };
    if (!GetCommTimeouts(hComm, &timeouts)) {
        printf("Failed to get the serial port state. Error code: %d\n", GetLastError());
        CloseHandle(hComm);
        return 1;
    }
    timeouts.ReadIntervalTimeout = 10;
    timeouts.ReadTotalTimeoutConstant = 0;
    timeouts.ReadTotalTimeoutMultiplier = 0;
    //timeouts.WriteTotalTimeoutConstant = 100;
    //timeouts.WriteTotalTimeoutMultiplier = 0;
    if (SetCommTimeouts(hComm, &timeouts)) {
        printf("Failed to set the serial port state. Error code: %d\n", GetLastError());
        CloseHandle(hComm);
        return 1;
    }

    CloseHandle(hComm);
    printf("Serial port configuration successful.\n");
    return 0;
}
