
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
SERVICE_STATUS m_ServiceStatus;//服务状态
SERVICE_STATUS_HANDLE m_ServiceStatusHandle;//服务状态句柄

TCHAR szServiceName[] = TEXT("DemoService02");//服务名字

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

	
	//服务分配表
	SERVICE_TABLE_ENTRY DispatchTable[2];
	//服务名称
	DispatchTable[0].lpServiceName = szServiceName;
	//服务主函数
	DispatchTable[0].lpServiceProc = (LPSERVICE_MAIN_FUNCTION)ServiceMain;

	DispatchTable[1].lpServiceName = NULL;
	DispatchTable[1].lpServiceProc = NULL;

	//注册服务的主函数
	//服务控制分配器 给服务创建一个线程
	StartServiceCtrlDispatcher(DispatchTable);

	system("pause");
	return 0;
}

//服务的主函数实现
VOID WINAPI ServiceMain(DWORD dwNumServicesArgs, LPTSTR *lpServiceArgVectors) {

	MEMORYSTATUS memstatus;//内存信息
	char szMsg[512];
	SIZE_T availmb;

	//服务类型 WIN32
	m_ServiceStatus.dwServiceType = SERVICE_WIN32;
	//服务状态 等待
	m_ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
	//服务控制 关机 服务停止
	m_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_STOP;
	//服务退出
	m_ServiceStatus.dwWin32ExitCode = 0;
	//服务退出
	m_ServiceStatus.dwServiceSpecificExitCode = 0;
	m_ServiceStatus.dwCheckPoint = 0;
	m_ServiceStatus.dwWaitHint = 0;
	//注册服务控制函数
	m_ServiceStatusHandle = RegisterServiceCtrlHandler(szServiceName, ServiceCtrlHandler);
	if (m_ServiceStatusHandle == 0) {
		WriteToLog("RegisterServiceCtrlHandler fail");
	}
	WriteToLog("RegisterServiceCtrlHandler success");

	//服务正在运行了
	m_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
	//报告服务的状态
	SetServiceStatus(m_ServiceStatusHandle, &m_ServiceStatus);

	bRunning = TRUE;

	while (bRunning) {
		//检测电脑当前的内存大小
		GlobalMemoryStatus(&memstatus);
		//将内存换算成MB
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

//服务控制函数
VOID WINAPI ServiceCtrlHandler(DWORD dwControl) {
	switch (dwControl) {
	case SERVICE_CONTROL_STOP://停止
		bRunning = FALSE;
		m_ServiceStatus.dwCurrentState = SERVICE_STOPPED;//停止状态
		break;
	case SERVICE_CONTROL_SHUTDOWN://关机
		bRunning = FALSE;
		m_ServiceStatus.dwCurrentState = SERVICE_STOPPED;//停止状态
		break;
	default:
		break;
	}
	//报告服务状态
	SetServiceStatus(m_ServiceStatusHandle, &m_ServiceStatus);
}

//写日志函数
int WriteToLog(const char *szMsg) {
	FILE* pfile = fopen(FILE_PATH, "a+");
	if (pfile == NULL) {
		return -1;
	}

	fprintf(pfile, "%s\n", szMsg);
	fclose(pfile);
	return 0;
}

//安装服务
BOOL InsCmdService() {
	
	TCHAR szBinaryPathName[MAX_PATH];
	GetModuleFileName(NULL, szBinaryPathName, MAX_PATH);

	//打开服务控制管理器
	SC_HANDLE schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (schSCManager == NULL) {
		printf("OpenSCManager 打开失败\n");
		return FALSE;
	}
	//创建服务
	SC_HANDLE schService = CreateService(schSCManager, 
		"DemoService02", //服务名称
		"ddddd",//描述
		SERVICE_ALL_ACCESS,//服务 所有访问权限
		SERVICE_WIN32_OWN_PROCESS,//WIN32 类型的服务
		SERVICE_AUTO_START,//自动启动
		SERVICE_ERROR_NORMAL,//错误处理 通常的方法
		szBinaryPathName,//服务的程序的路径名
		NULL,//不属于任何用户组
		NULL,//使用已存在的
		NULL,//独立的服务
		NULL,//本地系统账号
		NULL);//本地系统密码
	if (schService == NULL) {
		printf("CreateService 安装失败\n");
		return FALSE;
	}
	CloseServiceHandle(schService);
	CloseServiceHandle(schSCManager);

	printf("安装成功\n");
	return TRUE;
}
//删除服务
VOID DelCmdService() {
	//打开服务控制管理器
	//SC_MANAGER_CREATE_SERVICE 创建
	SC_HANDLE schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	if (schSCManager == NULL) {
		printf("OpenSCManager 失败\n");
		return;
	}
	SC_HANDLE schService = OpenService(schSCManager,
		szServiceName,
		SERVICE_ALL_ACCESS|DELETE);//所有权限|删除
	if (schService == NULL) {
		printf("OpenService 打开服务失败\n");
		return;
	}

	SERVICE_STATUS status;
	//查询服务状态
	BOOL isSuccess = QueryServiceStatus(schService, &status);
	if (isSuccess == FALSE) {//查询失败
		printf("QueryServiceStatus 查询服务失败\n");
		return;
	}
	if (status.dwCurrentState != SERVICE_STOPPED) {
		//如果服务未停止
		isSuccess = ControlService(schService, SERVICE_CONTROL_STOP, &status);
		if (isSuccess == FALSE) {
			printf("ControlService 停止服务失败\n");
			return;
		}
	}
	isSuccess = DeleteService(schService);
	if (isSuccess == FALSE) {
		printf("DeleteService 删除服务失败\n");
		return;
	}
	printf("DeleteService 删除服务成功\n");

	CloseServiceHandle(schService);
	CloseServiceHandle(schSCManager);
}