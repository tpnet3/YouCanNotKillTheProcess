// YouCanNotKillTheProcess.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <Aclapi.h>
#include <iostream>

DWORD ProtectProcess(void)
{
	HANDLE hProcess = GetCurrentProcess();
	PACL pEmptyDacl;
	DWORD dwErr;

	// using malloc guarantees proper alignment
	pEmptyDacl = (PACL)malloc(sizeof(ACL));

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
	int value;
	std::cout << ProtectProcess() << std::endl;
	std::cin >> value;
    return 0;
}
