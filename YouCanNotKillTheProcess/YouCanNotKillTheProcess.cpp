// YouCanNotKillTheProcess.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <Aclapi.h>
#include <iostream>

/*
������ ������ �ƴ� ȯ�濡�� ���μ����� ������ �� ������ ����ϴ�.
������ 10�� �⺻������ ������ �������� �۾������ڰ� ����ǵ��� ����Ǿ����ϴ�.

�۾������ڰ� ������ �������� ����Ǹ� ȿ���� �����ϴ�.
SeDebugPrivilege �� �׼��� ������ �����ϵ��� ����������ϴ�.
*/
DWORD ProtectProcess(void)
{
	HANDLE hProcess = GetCurrentProcess();
	PACL pEmptyDacl;
	DWORD dwErr;

	pEmptyDacl = (PACL)malloc(sizeof(ACL));

	// �� DACL �� �����, ��� �׼����� �źε˴ϴ�.
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
	std::cout << "���μ��� �׼����� �ź��ϵ��� �����մϴ�..." << std::endl;
	std::cout << ProtectProcess() << std::endl;
	std::cout << "ProtectProcess() �����." << std::endl;

	std::cout << std::endl;
	std::cout << "���μ��� ���Ḧ ����մϴ�." << std::endl;
	std::cin.get();
    return 0;
}
