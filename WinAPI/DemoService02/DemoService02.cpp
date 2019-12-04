
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <windows.h>

#define SLEEP_TIME 1000
#define FILE_PATH "c:/log.txt"

VOID WINAPI ServiceMain(DWORD dwNumServicesArgs, LPTSTR *lpServiceArgVectors);
VOID WINAPI ServiceCtrlHandler(DWORD dwControl);
int WriteToLog(const char *szMsg);

BOOL InsCmdService();
VOID DelCmdService();

BOOL bRunning = TRUE;
SERVICE_STATUS m_ServiceStatus;//����״̬
SERVICE_STATUS_HANDLE m_ServiceStatusHandle;//����״̬���

TCHAR szServiceName[] = TEXT("DemoService02");//��������

int main(int argc, char *argv[]) {
	if (argc == 2) {
		if (!strcmp(argv[1], "-i")) {
			InsCmdService();
		}
		else if (!strcmp(argv[1], "-d")) {
			DelCmdService();
		}
		return 0;
	}

	
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

//��װ����
BOOL InsCmdService() {
	
	TCHAR szBinaryPathName[MAX_PATH];
	GetModuleFileName(NULL, szBinaryPathName, MAX_PATH);

	//�򿪷�����ƹ�����
	SC_HANDLE schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (schSCManager == NULL) {
		printf("OpenSCManager ��ʧ��\n");
		return FALSE;
	}
	//��������
	SC_HANDLE schService = CreateService(schSCManager, 
		"DemoService02", //��������
		"ddddd",//����
		SERVICE_ALL_ACCESS,//���� ���з���Ȩ��
		SERVICE_WIN32_OWN_PROCESS,//WIN32 ���͵ķ���
		SERVICE_AUTO_START,//�Զ�����
		SERVICE_ERROR_NORMAL,//������ ͨ���ķ���
		szBinaryPathName,//����ĳ����·����
		NULL,//�������κ��û���
		NULL,//ʹ���Ѵ��ڵ�
		NULL,//�����ķ���
		NULL,//����ϵͳ�˺�
		NULL);//����ϵͳ����
	if (schService == NULL) {
		printf("CreateService ��װʧ��\n");
		return FALSE;
	}
	CloseServiceHandle(schService);
	CloseServiceHandle(schSCManager);

	printf("��װ�ɹ�\n");
	return TRUE;
}
//ɾ������
VOID DelCmdService() {
	//�򿪷�����ƹ�����
	//SC_MANAGER_CREATE_SERVICE ����
	SC_HANDLE schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	if (schSCManager == NULL) {
		printf("OpenSCManager ʧ��\n");
		return;
	}
	SC_HANDLE schService = OpenService(schSCManager,
		szServiceName,
		SERVICE_ALL_ACCESS|DELETE);//����Ȩ��|ɾ��
	if (schService == NULL) {
		printf("OpenService �򿪷���ʧ��\n");
		return;
	}

	SERVICE_STATUS status;
	//��ѯ����״̬
	BOOL isSuccess = QueryServiceStatus(schService, &status);
	if (isSuccess == FALSE) {//��ѯʧ��
		printf("QueryServiceStatus ��ѯ����ʧ��\n");
		return;
	}
	if (status.dwCurrentState != SERVICE_STOPPED) {
		//�������δֹͣ
		isSuccess = ControlService(schService, SERVICE_CONTROL_STOP, &status);
		if (isSuccess == FALSE) {
			printf("ControlService ֹͣ����ʧ��\n");
			return;
		}
	}
	isSuccess = DeleteService(schService);
	if (isSuccess == FALSE) {
		printf("DeleteService ɾ������ʧ��\n");
		return;
	}
	printf("DeleteService ɾ������ɹ�\n");

	CloseServiceHandle(schService);
	CloseServiceHandle(schSCManager);
}