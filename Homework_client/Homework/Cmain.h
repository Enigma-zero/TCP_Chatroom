#pragma once


// Cmain �Ի���

class Cmain : public CDialogEx
{
	DECLARE_DYNAMIC(Cmain)

public:
	Cmain(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Cmain();
	SOCKET m_sock;
	CString m_name;
	CImageList m_image;
	static DWORD WINAPI RecvProc(LPVOID lpParameter);
// �Ի�������
	enum { IDD = IDD_DIALOG_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	LRESULT afx_msg OnRecvData(WPARAM wParam,LPARAM lParam);
	afx_msg void OnBnClickedButtonSend();
	CString m_SendMessage;
	virtual BOOL OnInitDialog();
	CListCtrl m_list;
	CListCtrl m_list_ChatContext;
	afx_msg void OnOnrecord();
	afx_msg void On32771();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void Ontransfile();
};
