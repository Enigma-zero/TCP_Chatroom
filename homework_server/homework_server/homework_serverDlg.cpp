
// homework_serverDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "homework_server.h"
#include "homework_serverDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//����ȫ�ֱ���
vector<SOCKET> UserSocket;
UINT m_userNum;
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
public:
	afx_msg void Onportset();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	
	ON_COMMAND(ID_port_set, &CAboutDlg::Onportset)
END_MESSAGE_MAP()


// Chomework_serverDlg �Ի���




Chomework_serverDlg::Chomework_serverDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Chomework_serverDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Chomework_serverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_LIST2, m_list_ChatContext);
}

BEGIN_MESSAGE_MAP(Chomework_serverDlg, CDialogEx)
	ON_MESSAGE(WM_RECVDATA,OnRecvData)
	ON_MESSAGE(WM_USER_EXIT,OnUserExit)
	ON_MESSAGE(WM_USER_SENDMSG,OnUserEcho)
	ON_MESSAGE(WM_USER_LIST,OnUserList)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_port_set, &Chomework_serverDlg::Onportset)
	ON_COMMAND(ID_OUTPUT_CHATCONTEXT, &Chomework_serverDlg::OnOutputChatcontext)
END_MESSAGE_MAP()


// Chomework_serverDlg ��Ϣ�������


BOOL Chomework_serverDlg::OnInitDialog()
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
	m_userNum = 0;
	m_StatBar=new CStatusBarCtrl;
	RECT m_Rect;
	GetClientRect(&m_Rect); //��ȡ�Ի���ľ�������
	m_Rect.top=m_Rect.bottom-20; //����״̬���ľ�������
	m_StatBar->Create(WS_BORDER|WS_VISIBLE|CBRS_BOTTOM,m_Rect,this,3);
	int nParts[2]= {300, 500}; //�ָ�ߴ�
	m_StatBar->SetParts(2, nParts); //�ָ�״̬��
	m_StatBar->SetText("��ǰ������Ϊ��0",0,0); //��һ����������"���ǵ�һ��ָʾ��"
	m_StatBar->SetText("��ǰδ����������",1,0); //��������

	filePath = ".\\Recv\\";
	//listcontrol�ؼ���ʼ��

	LONG lStyle;
	lStyle = GetWindowLong(m_list.m_hWnd, GWL_STYLE);// ��ȡ��ǰ����style
	lStyle &= ~LVS_TYPEMASK; // �����ʾ��ʽλ
	lStyle |= LVS_REPORT; // ����style
	SetWindowLong(m_list.m_hWnd, GWL_STYLE, lStyle);// ����style
	DWORD dwStyle = m_list.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;// ѡ��ĳ��ʹ���и�����ֻ������report ����listctrl ��
	dwStyle |= LVS_EX_GRIDLINES;// �����ߣ�ֻ������report ����listctrl ��
	m_list.SetExtendedStyle(dwStyle); // ������չ��� 
	m_list.InsertColumn( 0, "�����û�", LVCFMT_LEFT, 176 );// ������

	LONG lStyle1;
	lStyle1 = GetWindowLong(m_list_ChatContext.m_hWnd, GWL_STYLE);// ��ȡ��ǰ����style
	lStyle1 &= ~LVS_TYPEMASK; // �����ʾ��ʽλ
	lStyle1 |= LVS_REPORT; // ����style
	SetWindowLong(m_list_ChatContext.m_hWnd, GWL_STYLE, lStyle1);// ����style
	DWORD dwStyle1 = m_list_ChatContext.GetExtendedStyle();
	dwStyle1 |= LVS_EX_FULLROWSELECT;// ѡ��ĳ��ʹ���и�����ֻ������report ����listctrl ��
	//dwStyle |= LVS_EX_GRIDLINES;// �����ߣ�ֻ������report ����listctrl ��
	m_list_ChatContext.SetExtendedStyle(dwStyle1); // ������չ��� 
	m_list_ChatContext.InsertColumn( 0, "�����¼", LVCFMT_LEFT, 449 );// ������
	//�²����������
	
	m_image.Create(16,16, TRUE|ILC_COLOR24, 3, 1);
    m_list.SetImageList(&m_image,LVSIL_SMALL);
	HICON hicon=(HICON)LoadImage(
        NULL,    //handle of the instance that contains //the image
        "1.ico",//name or identifier of image
        IMAGE_ICON,//type of image-can also be IMAGE_CURSOR or MAGE_ICON
        0,0,//desired width and height
        LR_LOADFROMFILE);//load flags
	m_image.Add(hicon);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Chomework_serverDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Chomework_serverDlg::OnPaint()
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
HCURSOR Chomework_serverDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//�˵����󶨵ĺ���
void CAboutDlg::Onportset(void)
{}

void Chomework_serverDlg::Onportset()
{
	// TODO: �ڴ���������������
	m_StatBar->SetText("��ǰ�ѿ���������",1,0); //��������
	RECVPARAM *pRecvParam = new RECVPARAM;
	pRecvParam->sock = m_sock;
	pRecvParam->hwnd = m_hWnd;
	HANDLE hThread=CreateThread(NULL,0,RecvProc,(LPVOID)pRecvParam,0,NULL);
	
}
//���������źŰ󶨵ĺ���
LRESULT Chomework_serverDlg::OnRecvData(WPARAM wParam,LPARAM lParam)

{   
	//��ȡ�յ����ַ���
	char* temp = (char*)lParam;
	//�ָ��ַ�����ȡ����Ĳ���
	CString strSource,ch;
	vector <CString> vecString;
	int iPos = 0;
	CString strTmp;
	strSource.Format("%s",temp);
	ch = ":";
	strTmp = strSource.Tokenize(ch,iPos);
	while(strTmp.Trim() != _T(""))
	{
		vecString.push_back(strTmp);
		strTmp = strSource.Tokenize(ch,iPos);
	}
	if(vecString[0] == "Login")
	{
		CString str;
		str.Format("�û���%s  �������ӷ�������",vecString[1]);
		if(IDYES==AfxMessageBox(str,MB_YESNO|MB_ICONQUESTION))
		{
			m_userNum++;
			MessageBox("����������");

			//�����µ��û���Ϣ��

			UserInfo newUserInfo;
			newUserInfo.UserId = m_userNum;
			newUserInfo.time = CTime::GetCurrentTime();
			newUserInfo.UserName = vecString[1];
			newUserInfo.UserIp = vecString[2];
			newUserInfo.port = atoi(vecString[3]);
			newUserInfo.m_socket = UserSocket[m_userNum-1];
			Exint * tempInt = new Exint;
			tempInt->number = m_userNum;
			tempInt->hwnd = m_hWnd;
			newUserInfo.ThreadId = CreateThread(NULL,0,CreatUser,(LPVOID)(tempInt),0,NULL);//�������߳̽���ͨ��
			user_info.push_back(newUserInfo);


			//���������ÿؼ�����

			//����״̬����Ϣ
			CString temp;
			temp.Format("��ǰ������Ϊ��%d",m_userNum);
			m_StatBar->SetText(temp,0,0);
			//�����Ƕ�listcontrol�ĸ���
			int nIndex = m_list.GetItemCount();  
			LV_ITEM   lvitemAdd = {0};  
			lvitemAdd.mask = LVIF_TEXT|LVIF_IMAGE;  
			lvitemAdd.iItem = nIndex ;  
			lvitemAdd.iSubItem = 0;  
			lvitemAdd.pszText = newUserInfo.UserName.GetBuffer();
			newUserInfo.UserName.ReleaseBuffer();
			lvitemAdd.iImage = 0;  //(ĳ�����ڵĴ��ھ��)  
			m_list.InsertItem(&lvitemAdd);
            /*
			int nIndex1 = m_list_ChatContext.GetItemCount();  
			LV_ITEM   lvitemAdd1 = {0};  
			lvitemAdd1.mask = LVIF_TEXT;  
			lvitemAdd1.iItem = nIndex1 ;  
			lvitemAdd1.iSubItem = 0;  
			temp.Format("%s:����������",newUserInfo.UserName);
			lvitemAdd1.pszText = temp.GetBuffer();
			temp.ReleaseBuffer();
			m_list_ChatContext.InsertItem(&lvitemAdd1);
			*/

			//�����û���Ϣ
			char sendBuf[] = "y";
	        send(UserSocket[m_userNum-1], sendBuf, 100, 0);


			Sleep(1000);

			CString strList = "LOGIN," + newUserInfo.UserName;
			SendMessage_r(strList);

		}
		else
		{

			MessageBox("�Ѿܾ����ӣ�");
		}
	}
	else if(vecString[0] == "File")
	{
		SOCKET socket = UserSocket[UserSocket.size() -1];
		UserSocket.pop_back();
		CString str;
		int iFileSize = atoi(vecString[3]); 
		str.Format("�û���%s  �������ļ��� \n �ļ�����%s \n ��С;%d",vecString[1],vecString[2],iFileSize);
		if(IDYES==AfxMessageBox(str,MB_YESNO|MB_ICONQUESTION))
		{
		fileInfo* newFile = new fileInfo;
		newFile->m_From = vecString[1];
		newFile->m_fileName = vecString[2];
		newFile->m_filePatch = filePath;
		newFile->hwnd = m_hWnd;
		newFile->m_fileSocket = socket;
		if(!CreateThread(NULL,0,RecvFile,(LPVOID)(newFile),0,NULL))
		{

		}
		}
	}
	return true;
}
//�����̺߳���
DWORD WINAPI Chomework_serverDlg::RecvProc(LPVOID lpParameter)        //��̬���Ա����(ʵ��)

{
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
              SOCKET sockConn = accept(sock, (SOCKADDR*)&addrClient, &sockLen);
              if(INVALID_SOCKET == WSAGetLastError())
                     AfxMessageBox("Connect client failed!");
 
              //5.�÷��ص��׽��ֺ��û�ͨ�ţ��������ݻ��ǽ�������
              char recvBuf[128];
              recv(sockConn, recvBuf, 128, 0);
              if(SOCKET_ERROR == WSAGetLastError())
                     AfxMessageBox("Server recieve data failed!");

              ::PostMessage(hwnd,WM_RECVDATA,0,(LPARAM)recvBuf);
			  UserSocket.push_back(sockConn);
       }
	 
	return 0;
}
//�����û���Ϣ����
DWORD WINAPI Chomework_serverDlg::CreatUser(LPVOID lpParameter)
{
	UINT num = ((Exint *)lpParameter)->number;
	HWND m_hwnd = ((Exint *)lpParameter)->hwnd;
	SOCKET clientSocket = UserSocket[num-1];
	while(1)
	{
		char recvBuf[128];
        int Irecv = recv(clientSocket, recvBuf, 128, 0);
		//AfxMessageBox(recvBuf);
		if(Irecv <= 0)
		{
			closesocket(clientSocket);
			std::vector<SOCKET>::iterator it = UserSocket.begin();
			for(it = UserSocket.begin();it != UserSocket.end();it++)
			{
				if((*it) == clientSocket)
				{
					UserSocket.erase(it);
					break;
				}
			}
			int * Pnum = new int;
			*Pnum = num;
			::PostMessage(m_hwnd,WM_USER_EXIT,0,(LPARAM)Pnum);
			m_userNum--;
			break;
		}
		else if(strcmp(recvBuf,"EXIT") == 0)
		{
			closesocket(clientSocket);
			std::vector<SOCKET>::iterator it = UserSocket.begin() + num - 1;
			for(it = UserSocket.begin();it != UserSocket.end();it++)
			{
				if( (*it) == clientSocket )
				{
						UserSocket.erase(it);
						break;
				}
			}
			int * Pnum = new int;
			*Pnum = num;
			::PostMessage(m_hwnd,WM_USER_EXIT,0,(LPARAM)Pnum);
			m_userNum--;
			break;
		}
		else if(strcmp(recvBuf,"USERLIST") == 0)
		{
			int * Pnum = new int;
			*Pnum = num;
			::PostMessage(m_hwnd,WM_USER_LIST,0,(LPARAM)Pnum);

		}
		else
		{
			::PostMessage(m_hwnd,WM_USER_SENDMSG,0,(LPARAM)recvBuf);
		}
	}
	return 0;
}
//�û��˳��ĺ���
LRESULT Chomework_serverDlg::OnUserExit(WPARAM wParam,LPARAM lParam)
{


    int User_num = *(int *)lParam;
	int ii = 0,Iindex = 0;	
    CString str,temp;
	for(ii = 0; ii < user_info.size();ii++)
	{
		if(user_info[ii].UserId == User_num)
			break;
	}
	vector<UserInfo>::iterator it = user_info.begin() + ii ;
	//���û���¼���д����־������
    CString Fpatch = ".\\log\\Userinfo.txt";
	CTime tempTime = CTime::GetCurrentTime();
	CTimeSpan span = tempTime - user_info[ii].time;

	CString str1 = "�û�:"+ user_info[ii].UserName + "\n";
	CString str2 = "IP��ַΪ: " + user_info[ii].UserIp + "\n";
	CString str3 = "��¼ʱ��Ϊ��" + user_info[ii].time.Format("%Y-%m-%d %H:%M:%S %W-%A") + "\n";
    CString str4 = "�˳�ʱ��Ϊ: " + tempTime.Format("%Y-%m-%d %H:%M:%S %W-%A") + "\n";
	CString str5 = "����ʱ��Ϊ��" + span.Format("%D��-%HСʱ-%M����-%S��") + "\n" + "\n";
	CString WriteStr = str1 + str2 + str3 + str4 + str5;

	CStdioFile Flog(Fpatch,CFile::typeText|CFile::modeNoTruncate|CFile::modeCreate|CFile::modeReadWrite);
	Flog.SeekToEnd();
	Flog.WriteString(WriteStr);
	Flog.Close();

	//���ÿؼ�����

	str.Format("��ǰ������Ϊ��%d",m_userNum);
	m_StatBar->SetText(str,0,0);
	//����listcontrol������
	int nIndex1 = m_list_ChatContext.GetItemCount();  
	LV_ITEM   lvitemAdd1 = {0};  
	lvitemAdd1.mask = LVIF_TEXT;  
	lvitemAdd1.iItem = nIndex1 ;  
	lvitemAdd1.iSubItem = 0;  
	temp.Format("%s:�뿪������",user_info[ii].UserName);
	lvitemAdd1.pszText = temp.GetBuffer();
	temp.ReleaseBuffer();
	m_list_ChatContext.InsertItem(&lvitemAdd1);

	//��ͻ��˷�������
	CString strTemp = "MSG," + temp;
	SendMessage_r(strTemp);

	Sleep(1000);
	CString strList;
	strList = "LOGOUT," + user_info[ii].UserName;
	SendMessage_r(strList);

	//ɾ��m_list�ж�Ӧ���û�

	for(Iindex = 0; Iindex < m_list.GetItemCount(); Iindex++)
	{
		str = m_list.GetItemText(Iindex,0);
		if(str == user_info[ii].UserName)
		{
			m_list.DeleteItem(Iindex);
			break;
		}
	}
	user_info.erase(it);
	return 0;
}
//ѭ���������ݺ����������͸��ͻ��˷�������
UINT Chomework_serverDlg::SendMessage_r(CString message)
{
	if(message.GetLength() > 128)
		return 0;
	int ii = 0;
	char* sendBuf = (LPSTR)(LPCTSTR)message;
	char Buff[128];
	strcpy(Buff,sendBuf);
	for(ii = 0; ii < UserSocket.size(); ii++)
	{
		send(UserSocket[ii], Buff,128, 0);
	}
	return 1;
}
//����Կͻ��˷�������Ϣ�㲥��ȥ
LRESULT Chomework_serverDlg::OnUserEcho(WPARAM wParam,LPARAM lParam)
{
	char* temp = (char* ) lParam;
	CString str;
	str.Format("MSG,%s",temp);
	CString strmsg;
	strmsg.Format("%s",temp);
	SendMessage_r(str);
	int nIndex1 = m_list_ChatContext.GetItemCount();  
	LV_ITEM   lvitemAdd1 = {0};  
	lvitemAdd1.mask = LVIF_TEXT;  
	lvitemAdd1.iItem = nIndex1 ;  
	lvitemAdd1.iSubItem = 0;  
	lvitemAdd1.pszText = strmsg.GetBuffer();
	strmsg.ReleaseBuffer();
	m_list_ChatContext.InsertItem(&lvitemAdd1);
	
    return 0;
}
//��¼�����¼�ĳ���
void Chomework_serverDlg::OnOutputChatcontext()
{
	// TODO: �ڴ���������������

	CTime tm = CTime::GetCurrentTime();
	CString str = tm.Format("%Y%m%d%H%M%S%W%A");
	CString Fpatch = ".\\log\\" + str + ".txt";
	CStdioFile Flog(Fpatch,CFile::typeText|CFile::modeCreate|CFile::modeReadWrite);
	int iIndex = m_list_ChatContext.GetItemCount();
	for(int i = 0;i < iIndex; i++)
	{
	CString s = m_list_ChatContext.GetItemText(i,0);
	s += "\n";
	Flog.WriteString(s);
	}
	Flog.Close();
}
//�����û������б�ĺ���
LRESULT Chomework_serverDlg::OnUserList(WPARAM wParam,LPARAM lParam)
{
	int number = *(int *)lParam;
	int Iindex = m_list.GetItemCount();
	SOCKET clientSocket;
	for(int i = 0;i < user_info.size();i++)
	{
		if(user_info[i].UserId == number)
		{
			clientSocket = user_info[i].m_socket;
			break;
		}
	}
	for(int ii = 0;ii < Iindex; ii++)
	{
		CString message = "LOGIN," + m_list.GetItemText(ii,0);
		char* sendBuf = (LPSTR)(LPCTSTR)message;
	    char Buff[128];
	    strcpy(Buff,sendBuf);
		Sleep(20);
		send(clientSocket, Buff,128, 0);
	}

	for(int i = 0;i < m_list_ChatContext.GetItemCount();i++)
	{
		CString message = "MSG," + m_list_ChatContext.GetItemText(i,0);
		char* sendBuf = (LPSTR)(LPCTSTR)message;
	    char Buff[128];
	    strcpy(Buff,sendBuf);
		Sleep(20);
		send(clientSocket, Buff,128, 0);
	}
	return 0;
}
//���������ļ��߳�
DWORD WINAPI Chomework_serverDlg::RecvFile(LPVOID lpParameter)
{
	fileInfo newFileInfo = *(fileInfo*) lpParameter;
	CFile newFile;
	char recvBuf[1024];
	newFile.Open(newFileInfo.m_fileName,CFile::modeCreate|CFile::modeWrite);
	while(1)
	{
		int Irecv = recv(newFileInfo.m_fileSocket, recvBuf, 1024, 0);
		if(Irecv>0)
		{
			    newFile.Write(recvBuf,Irecv);
				char buff[128] = "y";
				send(newFileInfo.m_fileSocket,buff,128,0);

		}
		else
		{
			break;
		}

	}
	newFile.Close();
	return 0;
}