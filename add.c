
#include<stdio.h>
#include<windows.h>
#include<string.h>
#include <TlHelp32.h>
#include<stdlib.h>
#include<Psapi.h>
#pragma comment(lib, "Psapi.lib")

LPWSTR GetProcessPath( DWORD idProcess )
{
    // ��ȡ����·��
    wchar_t sPath[100] = L"\0";
    // �򿪽��̾��
	
    HANDLE hProcess = OpenProcess(PROCESS_VM_READ, FALSE, idProcess );
	printf("jinl");
	if(hProcess == NULL){
		printf("\n%d\n",GetLastError());
	}
    if( NULL != hProcess )
    {
        HMODULE hMod;
        DWORD cbNeeded;
        // ��ȡ·��
		printf("dddddfadfadd");
        if( EnumProcessModules( hProcess, &hMod, sizeof( hMod ), &cbNeeded ) )
        {
            DWORD dw = GetModuleFileNameEx( hProcess, hMod, (LPWSTR)sPath,sizeof(sPath) );
			printf("dddddfadfadd");

            }
        CloseHandle( hProcess );
        }
	printf("dddd%s",sPath);
	wprintf(L"%s",sPath);
    return( sPath );
}

int getProcessInfo(){
    HANDLE shot;
    HANDLE process;
    PROCESSENTRY32 pe32;
    char proinfo[5000] = "\0";

    shot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(shot == INVALID_HANDLE_VALUE){
        printf("CreateToolhelp32Snapshot fail\n");
        return -1;
    }
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if(!Process32First(shot, &pe32)){
        printf("Process32First fail");
        CloseHandle(shot);
        return -1;
    }
    //printf("������\t����ID\t������\t�߳���\t���ȼ�\n"); // �������ȼ�


    //printf("%s\t%u\t%u\t%d\t%d\n", pe32.szExeFile, pe32.th32ProcessID, pe32.th32ParentProcessID, pe32.cntThreads, pe32.pcPriClassBase);


    sprintf(proinfo,"%s$%u$%d$%d$%u\n",pe32.szExeFile,pe32.th32ParentProcessID,pe32.cntThreads,pe32.pcPriClassBase,pe32.th32ProcessID);

	GetProcessPath(pe32.th32ProcessID);
    while(Process32Next(shot, &pe32)){
        sprintf(proinfo+strlen(proinfo),"%s$%u$%d$%d$%u\n",pe32.szExeFile,pe32.th32ParentProcessID,pe32.cntThreads,pe32.pcPriClassBase,pe32.th32ProcessID);
    }
    strcat(proinfo,"\0");
    printf("%s",proinfo);

    //send(sock,proinfo,strlen(proinfo)+1,0);
    CloseHandle(shot);   //�رվ��
    return 0;
}

main(){
	getProcessInfo();
	
	system("pause");
}






