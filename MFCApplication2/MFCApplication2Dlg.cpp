
// MFCApplication2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WINDOW_ORIGINAL "Original Image"
#define WINDOW_Rotate	"Rotate Image"

#define WIDTH	500
#define HEIGHT	520

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CMFCApplication2Dlg dialog



CMFCApplication2Dlg::CMFCApplication2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION2_DIALOG, pParent)
	, m_strName(_T(""))
	, m_strPath(_T(""))
	, m_strType(_T(""))
	, m_strShape(_T(""))
	, m_nSIze(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_PATH, m_strPath);
	DDX_Text(pDX, IDC_EDIT_TYPE, m_strType);
	DDX_Text(pDX, IDC_EDIT_SHAPE, m_strShape);
	DDX_Text(pDX, IDC_EDIT_SIZE, m_nSIze);
}

BEGIN_MESSAGE_MAP(CMFCApplication2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplication2Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCApplication2Dlg::OnBnClickedCancel)
//	ON_BN_CLICKED(IDC_BUTTON_BROWSE, &CMFCApplication2Dlg::OnBnClickedButtonBrowse)
	ON_BN_CLICKED(IDC_BUTTON_ROTATE, &CMFCApplication2Dlg::OnBnClickedButtonRotate)
	ON_COMMAND(ID_OPEN_FILE, &CMFCApplication2Dlg::OnOpenFile)
	ON_COMMAND(ID_OPEN_OPENDIRECTORY, &CMFCApplication2Dlg::OnOpenOpendirectory)
	ON_BN_CLICKED(IDC_BUTTON_PREV, &CMFCApplication2Dlg::OnBnClickedButtonPrev)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CMFCApplication2Dlg::OnBnClickedButtonNext)
END_MESSAGE_MAP()


// CMFCApplication2Dlg message handlers

BOOL CMFCApplication2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	m_vFileNames.clear();
	m_strBasePath = "";
	m_nIndex = 0;

	return TRUE;  // return TRUE  unless you set the focus to a control
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication2Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void CMFCApplication2Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


//event handler to 'Rotate' button click event
void CMFCApplication2Dlg::OnBnClickedButtonRotate()
{
	// Load the original image to rotate
	Mat imgOriginal = m_selectedImage;
	//set rotate window name
	const char* pzRotatedImage = "Rotated Image";
	namedWindow(pzRotatedImage);//create window

	int iAngle = 180;
	createTrackbar("Angle", pzRotatedImage, &iAngle, 360); //create trackbar

	int imagaCenterY = imgOriginal.rows / 2;
	int imageCenterX = imgOriginal.cols / 2;	

	while (true)
	{
		//create rotate matrix
		Mat matRotation = getRotationMatrix2D(Point(imageCenterX, imagaCenterY), (iAngle - 180), 1);

		// Rotate the image
		Mat imgRotated;
		warpAffine(imgOriginal, imgRotated, matRotation, imgOriginal.size());

		//show rotated image

		imshow(pzRotatedImage, imgRotated);

		int iRet = waitKey(30);
		if (iRet == 113)  
		{
			destroyWindow(pzRotatedImage);
			break;
		}
	}
	
}


void CMFCApplication2Dlg::OnOpenFile()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpenFile(TRUE);
	dlgOpenFile.GetOFN().Flags |= OFN_ALLOWMULTISELECT;
	if (IDOK == dlgOpenFile.DoModal())
	{
		int counter = 0;
		// get selected files
		POSITION pos = dlgOpenFile.GetStartPosition();
		Mat images[50];
		while (NULL != pos)
		{
			//get filePath
			CString strFilePath = dlgOpenFile.GetNextPathName(pos);
			CT2CA pszConvertedAnsiString(strFilePath);
			cv::String path(pszConvertedAnsiString);
			// ... do something with strFilePath.
			Mat image = imread(path);

			// Check for failure
			if (image.empty())
			{
				return;
			}
			images[counter] = image;
			counter++;
		}
		int index = 0;
		while (true)
		{
			if (index<0 || index>counter - 1) break;
			m_selectedImage = images[index];
			String windowName = "Origional Image:";
			namedWindow(windowName);
			imshow(windowName, m_selectedImage);
			int k = waitKey();
			//when pressed 'whitespace'key
			if (k == 32 && index < counter - 1)
			{
				index++;
				continue;
			}
			//when pressed 'p' key
			if (k == 112 && index > 0)
			{
				index--;
				continue;
			}
			//when pressed 'q' key
			if (k == 113)
			{
				destroyWindow(windowName);
				break;
			}
		}

	}
}


void CMFCApplication2Dlg::OnOpenOpendirectory()
{
	// TODO: Add your command handler code here
	CFolderPickerDialog folderPicker;

	if (folderPicker.DoModal() == IDOK)
	{
		m_strBasePath = folderPicker.GetFolderPath();

		FindAllFiles(m_strBasePath);

		m_nIndex = 0;
		ShowImage();
	}
}


void CMFCApplication2Dlg::OnBnClickedButtonPrev()
{
	// TODO: Add your control notification handler code here
	if (m_nIndex == 0)
	{
		return;
	}

	destroyAllWindows();
	m_nIndex--;
	ShowImage();
}


void CMFCApplication2Dlg::OnBnClickedButtonNext()
{
	// TODO: Add your control notification handler code here
	if (m_nIndex == m_vFileNames.size() - 1)
	{
		return;
	}

	destroyAllWindows();
	m_nIndex++;
	ShowImage();
}



void CMFCApplication2Dlg::FindAllFiles(CString strPath)
{
	// TODO: Add your implementation code here.

	CFileFind finder;
	FILEINFO info;

	bool bOK = false;

	strPath += "\\*.*";
	bOK = finder.FindFile(strPath);

	while (bOK) {
		bOK = finder.FindNextFileW();

		if (finder.IsDots())
			continue;

		if (finder.IsDirectory())
		{
			this->FindAllFiles(finder.GetFilePath());
		}
		else {
			info.strFilePath = finder.GetFilePath();

			CString fileName = finder.GetFileName();
			int index = fileName.ReverseFind('.');

			info.strFileName = fileName.Left(index);
			info.strFileType = fileName.Right(fileName.GetLength() - index - 1);

			m_vFileNames.push_back(info);
		}
	}
}


void CMFCApplication2Dlg::ShowImage()
{
	// TODO: Add your implementation code here.
	String windowName = "Origional Image:";
//	destroyWindow(windowName);

	vector<FILEINFO>::iterator iter;
	iter = m_vFileNames.begin();

	FILEINFO info = *(iter + m_nIndex);

	CT2CA pszConvertedAnsiString(info.strFilePath);
	cv::String path(pszConvertedAnsiString);
	// ... do something with strFilePath.
	m_selectedImage = imread(path);

	// show details...
	m_strName = info.strFileName;
	m_strPath = info.strFilePath;
	m_strType = info.strFileType;

	int nWidth = m_selectedImage.cols;
	int nHeight = m_selectedImage.rows;

	m_strShape.Format(L"%d x %d", nWidth, nHeight);
	m_nSIze = nWidth * nHeight;

	UpdateData(FALSE);

	namedWindow(windowName);
	resize(m_selectedImage, m_selectedImage, Size(WIDTH, HEIGHT));
	imshow(windowName, m_selectedImage);
	int k = waitKey();

	//when pressed 'q' key
	if (k == 113)
	{
		destroyWindow(windowName);
	}

}
