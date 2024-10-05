
// DSAAppDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CDSAAppDlg
class CDSAAppDlg : public CDialogEx
{
// Создание
public:
	CDSAAppDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DSAAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedbtncreatesignature();
	afx_msg void OnBnClickedbtngeneratekeys();
	CEdit m_edtP;
	CEdit m_edtQ;
	CEdit m_edtG;
	CEdit m_edtMessage;
	CEdit m_edtPublicKey;
	CEdit m_edtPrivateKey;
	CEdit m_edtSignature;
	afx_msg void OnBnClickedbtnverifysignature();
};
