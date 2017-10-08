// YouCanNotKillTheProcess.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <Aclapi.h>
#include <iostream>

/*
관리자 권한이 아닌 환경에서 프로세스를 종료할 수 없도록 만듭니다.
윈도우 10은 기본적으로 관리자 권한으로 작업관리자가 실행되도록 설계되었습니다.

작업관리자가 관리자 권한으로 실행되면 효과가 없습니다.
SeDebugPrivilege 는 액세스 설정을 무시하도록 만들어졌습니다.
*/
DWORD ProtectProcess(void)
{
	HANDLE hProcess = GetCurrentProcess();
	PACL pEmptyDacl;
	DWORD dwErr;

	pEmptyDacl = (PACL)malloc(sizeof(ACL));

	// 빈 DACL 을 만들면, 모든 액세스가 거부됩니다.
	if (!InitializeAcl(pEmptyDacl, sizeof(ACL), ACL_REVISION))
	{
		dwErr = GetLastError();
	}
	else
	{
		dwErr = SetSecurityInfo(hProcess, SE_KERNEL_OBJECT,
			DACL_SECURITY_INFORMATION, NULL, NULL, pEmptyDacl, NULL);
	}

	free(pEmptyDacl);
	return dwErr;
}

int main()
{
	std::cout << "프로세스 액세스를 거부하도록 설정합니다..." << std::endl;
	std::cout << ProtectProcess() << std::endl;
	std::cout << "ProtectProcess() 실행됨." << std::endl;

	std::cout << std::endl;
	std::cout << "프로세스 종료를 대기합니다." << std::endl;
	std::cin.get();
    return 0;
}
