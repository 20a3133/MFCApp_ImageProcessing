
// MFCApplication2Dlg.h : ヘッダー ファイル
//

#pragma once

#include <opencv2/opencv.hpp>
using namespace cv;


// CMFCApplication2Dlg ダイアログ
class CMFCApplication2Dlg : public CDialogEx
{
// コンストラクション
public:
	CMFCApplication2Dlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


protected:
	Mat mat;
	CDC* dc;
	HDC dstDC;
	Size size;

// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLoadFile();
private:
	void setPictureContlore(HDC dsrDC, Mat img, CDC* dc, Size size);
public:
	afx_msg void OnBnClickedMonotone();
	afx_msg void OnBnClickedAbynary();
	afx_msg void OnBnClickedFbynary();
	afx_msg void OnBnClickedLaplacian();
	afx_msg void OnBnClickedSobel();
	afx_msg void OnBnClickedCanny();
	afx_msg void OnBnClickedGaucian();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedReset();
	afx_msg void OnBnClickedClear();
private:
	void InitPictureContlor();
};
