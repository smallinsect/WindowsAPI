
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>

#define SLEEP_TIME 1000
#define FILE_PATH "c:/log.txt"

VOID WINAPI ServiceMain(DWORD dwNumServicesArgs, LPTSTR *lpServiceArgVectors);
VOID WINAPI ServiceCtrlHandler(DWORD dwControl);
int WriteToLog(const char *szMsg);

BOOL bRunning = TRUE;
SERVICE_STATUS m_ServiceStatus;//����״̬
SERVICE_STATUS_HANDLE m_ServiceStatusHandle;//����״̬���

TCHAR szServiceName[] = TEXT("DemoService");//��������

int main(int argc, char *argv[]) {

	//��������
	SERVICE_TABLE_ENTRY DispatchTable[2];
	//��������
	DispatchTable[0].lpServiceName = szServiceName;
	//����������
	DispatchTable[0].lpServiceProc = (LPSERVICE_MAIN_FUNCTION)ServiceMain;
	
	DispatchTable[1].lpServiceName = NULL;
	DispatchTable[1].lpServiceProc = NULL;

	//ע������������
	//������Ʒ����� �����񴴽�һ���߳�
	StartServiceCtrlDispatcher(DispatchTable);

	system("pause");
	return 0;
}

//�����������ʵ��
VOID WINAPI ServiceMain(DWORD dwNumServicesArgs, LPTSTR *lpServiceArgVectors) {

	MEMORYSTATUS memstatus;//�ڴ���Ϣ
	char szMsg[512];
	SIZE_T availmb;

	//�������� WIN32
	m_ServiceStatus.dwServiceType = SERVICE_WIN32;
	//����״̬ �ȴ�
	m_ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
	//������� �ػ� ����ֹͣ
	m_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_STOP;
	//�����˳�
	m_ServiceStatus.dwWin32ExitCode = 0;
	//�����˳�
	m_ServiceStatus.dwServiceSpecificExitCode = 0;
	m_ServiceStatus.dwCheckPoint = 0;
	m_ServiceStatus.dwWaitHint = 0;
	//ע�������ƺ���
	m_ServiceStatusHandle = RegisterServiceCtrlHandler(szServiceName, ServiceCtrlHandler);
	if (m_ServiceStatusHandle == 0) {
		WriteToLog("RegisterServiceCtrlHandler fail");
	}
	WriteToLog("RegisterServiceCtrlHandler success");

	//��������������
	m_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
	//��������״̬
	SetServiceStatus(m_ServiceStatusHandle, &m_ServiceStatus);

	bRunning = TRUE;

	while (bRunning) {
		//�����Ե�ǰ���ڴ��С
		GlobalMemoryStatus(&memstatus);
		//���ڴ滻���MB
		availmb = memstatus.dwAvailPhys / 1024 / 1024;
#ifdef _WIN64
		sprintf(szMsg, "available memory is %lld MB", availmb);
#else
		sprintf(szMsg, "available memory is %ld MB", availmb);
#endif
		WriteToLog(szMsg);
		Sleep(SLEEP_TIME);
	}
	WriteToLog("service stop");
}

//������ƺ���
VOID WINAPI ServiceCtrlHandler(DWORD dwControl) {
	switch (dwControl) {
	case SERVICE_CONTROL_STOP://ֹͣ
		bRunning = FALSE;
		m_ServiceStatus.dwCurrentState = SERVICE_STOPPED;//ֹͣ״̬
		break;
	case SERVICE_CONTROL_SHUTDOWN://�ػ�
		bRunning = FALSE;
		m_ServiceStatus.dwCurrentState = SERVICE_STOPPED;//ֹͣ״̬
		break;
	default:
		break;
	}
	//�������״̬
	SetServiceStatus(m_ServiceStatusHandle, &m_ServiceStatus);
}

//д��־����
int WriteToLog(const char *szMsg) {
	FILE* pfile = fopen(FILE_PATH, "a+");
	if (pfile == NULL) {
		return -1;
	}

	fprintf(pfile, "%s\n", szMsg);
	fclose(pfile);
	return 0;
}