
// HomeworkDlg.h : ͷ�ļ�
//

#pragma once


// CHomeworkDlg �Ի���
class CHomeworkDlg : public CDialogEx
{
// ����
public:
	CHomeworkDlg(CWnd* pParent = NULL);	// ��׼���캯��
	static DWORD WINAPI RecvProc(LPVOID lpParameter);
// �Ի�������
	enum { IDD = IDD_HOMEWORK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnIpnFieldchangedIpaddress2(NMHDR *pNMHDR, LRESULT *pResult);
	CIPAddressCtrl m_ServerAddress;
//	CEdit m_Name;
	UINT m_Port;
	CString m_Name;
	afx_msg void OnBnClickedButtonlogin();
};
