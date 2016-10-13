
// HomeworkDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Homework.h"
#include "HomeworkDlg.h"
#include "afxdialogex.h"
#include "Cmain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHomeworkDlg �Ի���




CHomeworkDlg::CHomeworkDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHomeworkDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Port = 0;
	m_Name = _T("");
}

void CHomeworkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS2, m_ServerAddress);
	//  DDX_Control(pDX, IDC_EDIT_name, m_Name);
	DDX_Text(pDX, IDC_EDIT_Port, m_Port);
	DDV_MinMaxUInt(pDX, m_Port, 0, 100000);
	DDX_Text(pDX, IDC_EDIT_name, m_Name);
	DDV_MaxChars(pDX, m_Name, 20);
}

BEGIN_MESSAGE_MAP(CHomeworkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS2, &CHomeworkDlg::OnIpnFieldchangedIpaddress2)
	ON_BN_CLICKED(IDC_BUTTON_login, &CHomeworkDlg::OnBnClickedButtonlogin)
END_MESSAGE_MAP()


// CHomeworkDlg ��Ϣ�������

BOOL CHomeworkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_ServerAddress.SetAddress( htonl(inet_addr("127.0.0.1")));
	m_Port=6000;
	UpdateData(false);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CHomeworkDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHomeworkDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CHomeworkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHomeworkDlg::OnIpnFieldchangedIpaddress2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CHomeworkDlg::OnBnClickedButtonlogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//�����ǻ�ȡ�ؼ�����
	UpdateData(true);
	BYTE f0,f1,f2,f3;
	CString ip;
	m_ServerAddress.GetAddress(f0,f1,f2,f3);
	ip.Format( _T("%d.%d.%d.%d"), f0, f1, f2, f3);

	//�������������������������
	SOCKET sockClient;
	sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(INVALID_SOCKET == WSAGetLastError())
		MessageBox("Create Socket failed!");

	//2.�������������������
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr(ip);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(m_Port);
	connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	//3.�ͷ���������ͨ�ţ����ջ��Ƿ�������

	CString data;
	data.Format("Login:%s:%s:%d",m_Name,ip,m_Port);
	char * temp = data.GetBuffer(0);
	char sendBuf[30];
	data.ReleaseBuffer();
	strcpy(sendBuf,temp);
	send(sockClient, sendBuf, sizeof(sendBuf) + 1, 0);
	if(SOCKET_ERROR == WSAGetLastError())
		MessageBox("Server send data failed!");
	char recvBuf[100];
    recv(sockClient, recvBuf, 100, 0);
	if(strcmp(recvBuf,"y") == 0)
	{	
		CDialog::OnCancel();
		Cmain temp1;
		temp1.m_sock = sockClient;
		temp1.m_name = m_Name;
		//temp1.SetWindowTextA(m_Name);
		temp1.DoModal();
	
	}
	else
	{
		closesocket(sockClient);
	}
}


//�ú���û���õ�
DWORD WINAPI CHomeworkDlg::RecvProc(LPVOID lpParameter)        //��̬���Ա����(ʵ��)

{
	AfxMessageBox("���߳�����!");
	SOCKET sock=((RECVPARAM*)lpParameter)->sock;
    HWND hwnd=((RECVPARAM*)lpParameter)->hwnd;
	char tempBuf[300];
	//1.�����׽���
       sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
       if(INVALID_SOCKET == WSAGetLastError())
              AfxMessageBox("Create Socket failed!");
 
       //2.���׽��ֵ�һ���˿ں�
       SOCKADDR_IN addrSrv;
       memset(&addrSrv, 0, sizeof(addrSrv));
       addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
       addrSrv.sin_family = AF_INET;
       addrSrv.sin_port = htons(6000);
       bind(sock, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
 
       //3.�����׽���Ϊ����ģʽ
       listen(sock,5);
 
       //4.�ȴ��û������ӵ���
       SOCKADDR_IN addrClient;
       int sockLen = sizeof(SOCKADDR);
       while(1)
       {
		      AfxMessageBox("�����Ѿ�����!");
              SOCKET sockConn = accept(sock, (SOCKADDR*)&addrClient, &sockLen);
              if(INVALID_SOCKET == WSAGetLastError())
                     AfxMessageBox("Connect client failed!");
 
              //5.�÷��ص��׽��ֺ��û�ͨ�ţ��������ݻ��ǽ�������
              char recvBuf[100];
              recv(sockConn, recvBuf, 100, 0);
              if(SOCKET_ERROR == WSAGetLastError())
                     AfxMessageBox("Server recieve data failed!");

              AfxMessageBox(recvBuf);
	   }
}