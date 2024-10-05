
// DSAAppDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "DSAApp.h"
#include "DSAAppDlg.h"
#include "afxdialogex.h"
#include "DSA.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CDSAAppDlg



CDSAAppDlg::CDSAAppDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DSAAPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDSAAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, edtP, m_edtP);
	DDX_Control(pDX, edtQ, m_edtQ);
	DDX_Control(pDX, edtG, m_edtG);
	DDX_Control(pDX, edtMessage, m_edtMessage);
	DDX_Control(pDX, edtPublicKey, m_edtPublicKey);
	DDX_Control(pDX, edtPrivateKey, m_edtPrivateKey);
	DDX_Control(pDX, edtSignature, m_edtSignature);
}

BEGIN_MESSAGE_MAP(CDSAAppDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(btnCreateSignature, &CDSAAppDlg::OnBnClickedbtncreatesignature)
	ON_BN_CLICKED(btnGenerateKeys, &CDSAAppDlg::OnBnClickedbtngeneratekeys)
	ON_BN_CLICKED(btnVerifySignature, &CDSAAppDlg::OnBnClickedbtnverifysignature)
END_MESSAGE_MAP()


// Обработчики сообщений CDSAAppDlg

BOOL CDSAAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CDSAAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CDSAAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

DSAKeys keys;
// создание подписи
void CDSAAppDlg::OnBnClickedbtncreatesignature()
{
	CString str;
	wchar_t signature_s[_MAX_U64TOSTR_BASE10_COUNT];

	m_edtMessage.GetWindowTextW(str);
	pair<BigInt, BigInt> signature = dsa_create_signature(str, keys);

	wcscpy_s(signature_s, signature.first.ToString());
	wcscat_s(signature_s, L" ");
	wcscat_s(signature_s, signature.second.ToString());

	m_edtSignature.SetWindowTextW(signature_s);
}

// генерация ключей
void CDSAAppDlg::OnBnClickedbtngeneratekeys()
{
	CString str;
	wchar_t buffer[_MAX_U64TOSTR_BASE10_COUNT];

	m_edtP.GetWindowTextW(str);
	uint32_t p = _wtol(str);

	m_edtQ.GetWindowTextW(str);
	uint32_t q = _wtol(str);

	m_edtG.GetWindowTextW(str);
	uint32_t g = _wtol(str);

	keys = dsa_generate_keys(q, p, g);

	m_edtPrivateKey.SetWindowTextW(keys.PrivateKey.ToString());
	m_edtPublicKey.SetWindowTextW(keys.PublicKey.ToString());
}

// проверка подписи
void CDSAAppDlg::OnBnClickedbtnverifysignature()
{
	CString message, signature_s;

	m_edtMessage.GetWindowTextW(message);
	m_edtSignature.GetWindowTextW(signature_s);

	int idx = signature_s.Find(' ');
	string str_r = CStringA(signature_s.Left(idx));
	string str_s = CStringA(signature_s.Right(signature_s.GetLength() - idx - 1));

	BigInt r = BigInt(str_r);
	BigInt s = BigInt(str_s);
	
	if (dsa_verify_signature(message, {r, s}, keys))
	{
		MessageBox(L"Подпись верна");
	}
	else
	{
		MessageBox(L"Подпись не верна");
	}
}
