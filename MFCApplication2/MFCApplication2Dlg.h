
// MFCApplication2Dlg.h : header file
//

#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

typedef struct _FILEINFO {
	CString strFileName;
	CString strFilePath;
	CString strFileType;
}FILEINFO;

// CMFCApplication2Dlg dialog
class CMFCApplication2Dlg : public CDialogEx
{
// Construction
public:
	CMFCApplication2Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	Mat m_selectedImage;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
//	afx_msg void OnBnClickedButtonBrowse();
	afx_msg void OnBnClickedButtonRotate();
	afx_msg void OnOpenFile();
	afx_msg void OnOpenOpendirectory();
	afx_msg void OnBnClickedButtonPrev();
	afx_msg void OnBnClickedButtonNext();

private:
	// Image Name
	CString m_strName;
	// Image Path
	CString m_strPath;
	// Image Type
	CString m_strType;
	// Image Shape
	CString m_strShape;
	// Image Size
	int m_nSIze;

	vector<FILEINFO> m_vFileNames;
	CString m_strBasePath;
	int m_nIndex;
public:
	void FindAllFiles(CString strPath);
	void ShowImage();
};
