
// homework_serverDlg.h : ͷ�ļ�
//

#pragma once


// Chomework_serverDlg �Ի���
class Chomework_serverDlg : public CDialogEx
{
// ����
public:
	Chomework_serverDlg(CWnd* pParent = NULL);	// ��׼���캯��
// �Ի�������
	enum { IDD = IDD_HOMEWORK_SERVER_DIALOG };

//�Զ��庯��
	static DWORD WINAPI RecvProc(LPVOID lpParameter);//���տͻ�����Ϣ���̺߳���
	static DWORD WINAPI CreatUser(LPVOID lpParameter);//�����û������տͻ��˵��̺߳���
	static DWORD WINAPI RecvFile(LPVOID lpParameter);//�����ļ����߳�
	UINT   SendMessage_r(CString message);//ѭ���������ݵĺ���         
//�Զ�������
	SOCKET m_sock;
	vector<UserInfo> user_info;
	vector<fileInfo> fileList;
	CStatusBarCtrl *m_StatBar;
	CImageList m_image;
	CString filePath;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	LRESULT afx_msg OnRecvData(WPARAM wParam,LPARAM lParam);//����ͻ�����������ĺ���
	LRESULT afx_msg OnUserExit(WPARAM wParam,LPARAM lParam);//�����û��˳�����ĺ���
	LRESULT afx_msg OnUserEcho(WPARAM wParam,LPARAM lParam);//�����û���������Ϣ�ĺ���
	LRESULT afx_msg OnUserList(WPARAM wParam,LPARAM lParam);//�����û��б�ĺ���
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void Onportset();
	afx_msg void OnBnClickedButton2();
	CListCtrl m_list;
	CListCtrl m_list_ChatContext;
	afx_msg void OnOutputChatcontext();
};
