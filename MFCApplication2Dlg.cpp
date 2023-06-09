
// MFCApplication2Dlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "afxdialogex.h"
#include "opencv2/opencv.hpp"

#if defined _DEBUG
#define CV_EXT "d.lib"
#else
#define CV_EXT ".lib"
#endif

#pragma comment(lib, "opencv_world470" CV_EXT)
#pragma comment(lib, "opencv_world470d" CV_EXT)

// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication2Dlg ダイアログ



CMFCApplication2Dlg::CMFCApplication2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOAD_FILE, &CMFCApplication2Dlg::OnBnClickedLoadFile)
	ON_BN_CLICKED(IDC_MONOTONE, &CMFCApplication2Dlg::OnBnClickedMonotone)
	ON_BN_CLICKED(IDC_ABYNARY, &CMFCApplication2Dlg::OnBnClickedAbynary)
	ON_BN_CLICKED(IDC_FBYNARY, &CMFCApplication2Dlg::OnBnClickedFbynary)
	ON_BN_CLICKED(IDC_LAPLACIAN, &CMFCApplication2Dlg::OnBnClickedLaplacian)
	ON_BN_CLICKED(IDC_SOBEL, &CMFCApplication2Dlg::OnBnClickedSobel)
	ON_BN_CLICKED(IDC_CANNY, &CMFCApplication2Dlg::OnBnClickedCanny)
	ON_BN_CLICKED(IDC_GAUCIAN, &CMFCApplication2Dlg::OnBnClickedGaucian)
	ON_BN_CLICKED(IDOK, &CMFCApplication2Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_PICRESET, &CMFCApplication2Dlg::OnBnClickedPicreset)
END_MESSAGE_MAP()


// CMFCApplication2Dlg メッセージ ハンドラー

BOOL CMFCApplication2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。


	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CMFCApplication2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CMFCApplication2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication2Dlg::OnBnClickedLoadFile()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	
	//画像読み込み
	//CImage tmp; //画像読み込み用変数
	CFileDialog Dlg(TRUE, _T("*.jpg"), NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		_T("画像ファイル(*.jpg)|*.jpg|画像ファイル(*.png)|*.png||")); //画像を設定

	if (Dlg.DoModal() != IDOK)
	{
		return;
	}

	CString filename = Dlg.GetPathName();//画像ファイル名メモリに記入
	cv::String cvfilename = CStringA(filename).GetBuffer();//Mat用画像ファイル名メモリに記入
	mat = cv::imread(cvfilename); //画像読み込み

	cv::Mat img = mat.clone(); //画像データをコピー

	BeginWaitCursor(); //処理中マーク表示指示
	InitPictureContlor();
	cv::resize(img, img, size);
	cv::flip(img, img, 0);

	//Picture Contlorに描画
	BITMAPINFO info = {};
	info.bmiHeader.biBitCount = 24;
	info.bmiHeader.biWidth = size.width;
	info.bmiHeader.biHeight = size.height;
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	info.bmiHeader.biCompression = BI_RGB;

	StretchDIBits(dstDC, 0, 0,
		size.width, size.height, 0, 0,
		size.width, size.height,
		img.data, &info, DIB_RGB_COLORS, SRCCOPY);

	ReleaseDC(dc);
	EndWaitCursor(); //処理中マーク消去指示
}


void CMFCApplication2Dlg::setPictureContlore(HDC dstDC, Mat img, CDC* dc, Size size)
{
	// TODO: ここに実装コードを追加します.
	cv::resize(img, img, size);
	cv::flip(img, img, 0);

	struct MYBITMAPINFO {
		BITMAPINFOHEADER bmiHeader;
		RGBQUAD bmiColors[256];
	};

	MYBITMAPINFO myinfo = {};
	LPBITMAPINFO pInfo = reinterpret_cast<LPBITMAPINFO>(&myinfo);

	pInfo->bmiHeader.biBitCount = 8;
	pInfo->bmiHeader.biWidth = size.width;
	pInfo->bmiHeader.biHeight = size.height;
	pInfo->bmiHeader.biPlanes = 1;
	pInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pInfo->bmiHeader.biCompression = BI_RGB;


	for (int i = 0; i < std::pow(2, 8); i++) {
		pInfo->bmiColors[i].rgbRed = i;
		pInfo->bmiColors[i].rgbGreen = i;
		pInfo->bmiColors[i].rgbBlue = i;
		pInfo->bmiColors[i].rgbReserved = 0;
	}

	StretchDIBits(dstDC, 0, 0,
		size.width, size.height, 0, 0,
		size.width, size.height,
		img.data, pInfo, DIB_RGB_COLORS, SRCCOPY);

	ReleaseDC(dc);
	
}


void CMFCApplication2Dlg::OnBnClickedMonotone()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	BeginWaitCursor(); //処理中マーク表示指示
	InitPictureContlor();
	cv::Mat img = mat.clone();
	cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
	
	setPictureContlore(dstDC, img, dc, size);//Picture Contlorに描画
	EndWaitCursor(); //処理中マーク消去指示
}


void CMFCApplication2Dlg::OnBnClickedAbynary()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	BeginWaitCursor(); //処理中マーク表示指示
	InitPictureContlor();
	cv::Mat img = mat.clone();
	cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
	//cv::threshold(img, img, 127, 255, cv::THRESH_BINARY);
	cv::adaptiveThreshold(img, img, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 9, 12);

	setPictureContlore(dstDC, img, dc, size);//Picture Contlorに描画
	EndWaitCursor(); //処理中マーク消去指示
}


void CMFCApplication2Dlg::OnBnClickedFbynary()
{
	BeginWaitCursor(); //処理中マーク表示指示
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	InitPictureContlor();
	cv::Mat img = mat.clone();
	cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
	cv::threshold(img, img, 127, 255, cv::THRESH_BINARY);

	setPictureContlore(dstDC, img, dc, size);//Picture Contlorに描画
	EndWaitCursor(); //処理中マーク消去指示
}


void CMFCApplication2Dlg::OnBnClickedLaplacian()
{
	BeginWaitCursor(); //処理中マーク表示指示
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	InitPictureContlor();
	cv::Mat img = mat.clone();
	cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
	cv::Laplacian(img, img, CV_8UC1, 1, 5);

	setPictureContlore(dstDC, img, dc, size);//Picture Contlorに描画
	EndWaitCursor(); //処理中マーク消去指示
}


void CMFCApplication2Dlg::OnBnClickedSobel()
{
	BeginWaitCursor(); //処理中マーク表示指示
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	InitPictureContlor();
	cv::Mat img = mat.clone();
	cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
	cv::Sobel(img, img, CV_8UC1, 1, 1, 1, 3);
	
	setPictureContlore(dstDC, img, dc, size);//Picture Contlorに描画
	EndWaitCursor(); //処理中マーク消去指示
}


void CMFCApplication2Dlg::OnBnClickedCanny()
{
	BeginWaitCursor(); //処理中マーク表示指示
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	InitPictureContlor();
	cv::Mat img = mat.clone();
	cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
	Canny(img, img, 125, 255);

	setPictureContlore(dstDC, img, dc, size);//Picture Contlorに描画
	EndWaitCursor(); //処理中マーク消去指示
}


void CMFCApplication2Dlg::OnBnClickedGaucian()
{
	BeginWaitCursor(); //処理中マーク表示指示
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	InitPictureContlor();
	cv::Mat img = mat.clone();
	cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
	cv::GaussianBlur(img, img, cv::Size(7, 7), 0);

	setPictureContlore(dstDC, img, dc, size);//Picture Contlorに描画
	EndWaitCursor(); //処理中マーク消去指示
}


void CMFCApplication2Dlg::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CDialogEx::OnOK();
}


void CMFCApplication2Dlg::InitPictureContlor()
{
	// TODO: ここに実装コードを追加します.
	//Picture Contlorerの設定
	dc = GetDlgItem(IDC_IMAGE)->GetDC();
	dstDC = dc->GetSafeHdc();

	CRect rc;
	GetDlgItem(IDC_IMAGE)->GetClientRect(&rc);

	size = cv::Size(rc.Width() & ~0x03, rc.Height() & ~0x03);
}


void CMFCApplication2Dlg::OnBnClickedPicreset()
{
	BeginWaitCursor(); //処理中マーク表示指示
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	InitPictureContlor();
	cv::Mat img = mat.clone();

	InitPictureContlor();
	Invalidate();
	UpdateWindow();
	cv::resize(img, img, size);
	cv::flip(img, img, 0);

	//Picture Contlorに描画
	BITMAPINFO info = {};
	info.bmiHeader.biBitCount = 24;
	info.bmiHeader.biWidth = size.width;
	info.bmiHeader.biHeight = size.height;
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	info.bmiHeader.biCompression = BI_RGB;

	StretchDIBits(dstDC, 0, 0,
		size.width, size.height, 0, 0,
		size.width, size.height,
		img.data, &info, DIB_RGB_COLORS, SRCCOPY);

	ReleaseDC(dc);
	EndWaitCursor(); //処理中マーク消去指示
}
