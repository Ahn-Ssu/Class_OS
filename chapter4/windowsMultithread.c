#include <windows.h>
#include <stdio.h>

DWORD Sum;

DWORD WINAPI Summation(LPVOID param){
    DWORD Upper = *(DWORD*)Param;

    for (DWORD i = 0 ; i <= Upper; i ++)
        Sum += i;
    
    return 0;
}
//  환경이 맥, 리눅스여서 이거 안돌아 가는거 같음.. 헤더가 없다고 뜨네
int main(int argc, char *argv[]){
    DWORD ThreadId;
    HANDLE ThreadHandle; 
    int Param;

    if (argc != 2){
        fprintf(stderr, "An interger parameter is required\n");
        return -1;
    }

    Param = atoi(argv[1]);

    if (Param < 0){
        fprintf(stderr, "An integer >= 0 is required\n");
        return -1;
    }

    ThreadHandle = CreateThread(NULL,
                                0,
                                Summation,
                                &Param,
                                0
                                &ThreadId);

    if ( ThreadHandle != NULL){
        WaitForSingleObject(ThreadHandle, INFINITE);

        CloseHandle(ThreadHandle);

        printf("Sum = %d\n", Sum);
    }
}