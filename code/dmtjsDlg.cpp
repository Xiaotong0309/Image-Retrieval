
// dmtjsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "dmtjs.h"
#include "dmtjsDlg.h"
#include "afxdialogex.h"

//#include "stdafx.h"
//#include "dmt.h"
//#include "dmtDlg.h"
//#include "afxdialogex.h"
#include "stdlib.h "
#include <stdio.h>
#include <gdiplus.h>
#include <string.h>
#include <atlimage.h>
#include <math.h> 

#ifdef _DEBUG
#define new DEBUG_NEW

#endif
Bitmap* pimage;//Image 的派生类对象指针
CRgn m_rgn;//窗口显示区域
CImage ImageBg;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CdmtjsDlg 对话框



CdmtjsDlg::CdmtjsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DMTJS_DIALOG, pParent)
	//, m_GdiPlusToken(0)
	//m_Bg1(L"C:\\Users\\sdwfl\\Desktop\\大作业 要求\\ui界面\\关闭.png")
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CdmtjsDlg::ReSize()
{
	float fsp[2];
	POINT Newp; //获取现在对话框的大小  
	CRect recta;
	GetClientRect(&recta); //取客户区大小    
	Newp.x = recta.right - recta.left;
	Newp.y = recta.bottom - recta.top;
	fsp[0] = (float)Newp.x / old.x;
	fsp[1] = (float)Newp.y / old.y;
	CRect Rect;
	int woc;
	CPoint OldTLPoint, TLPoint; //左上角  
	CPoint OldBRPoint, BRPoint; //右下角  
	HWND hwndChild = ::GetWindow(m_hWnd, GW_CHILD); //列出所有控件    
	while (hwndChild)
	{
		woc = ::GetDlgCtrlID(hwndChild);//取得ID  
		GetDlgItem(woc)->GetWindowRect(Rect);
		ScreenToClient(Rect);
		OldTLPoint  = Rect.TopLeft();
		TLPoint.x  = long(OldTLPoint.x*fsp[0]);
		TLPoint.y  = long(OldTLPoint.y*fsp[1]);
		OldBRPoint  = Rect.BottomRight();
		BRPoint.x  = long(OldBRPoint.x *fsp[0]);
		BRPoint.y  = long(OldBRPoint.y *fsp[1]);
		Rect.SetRect(TLPoint, BRPoint);
		GetDlgItem(woc)->MoveWindow(Rect, TRUE);
		hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
	}
	old = Newp;

}

void CdmtjsDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here  
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		ReSize();
	}
}

void CdmtjsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_IMAGELISTCTRL1, ImageList);
	//  DDX_Control(pDX, IDC_LIST1, ImageList);
	DDX_Control(pDX, IDC_LIST1, m_ImageList);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
	//  DDX_Control(pDX, IDC_BUTTON2, m_Btn1);
	//  DDX_Control(pDX, IDC_BUTTON2, m_Btn1);
}

BEGIN_MESSAGE_MAP(CdmtjsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CdmtjsDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CdmtjsDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CdmtjsDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON6, &CdmtjsDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON5, &CdmtjsDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CdmtjsDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON7, &CdmtjsDlg::OnClickedButton7)
	ON_WM_LBUTTONDOWN()
	ON_STN_CLICKED(IDC_STATIC_PIC, &CdmtjsDlg::OnStnClickedStaticPic)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CdmtjsDlg::OnLvnItemchangedList1)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CdmtjsDlg 消息处理程序

BOOL CdmtjsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//::SetWindowPos(this->m_hWnd, HWND_BOTTOM, 20, 0, 1000, 600, SWP_NOZORDER);
	//计算原始对话框大小
	CRect rect;
	GetClientRect(&rect); //取客户区大小    
	old.x = rect.right - rect.left;
	old.y = rect.bottom - rect.top;
	//GdiplusStartupInput gdiplusStartupInput;
	//GdiplusStartup(&m_GdiPlusToken, &gdiplusStartupInput, NULL);//其中，m_GdiPlusToken是ULONG_PTR类型的成员变量。
	
	//CImage Image;
	//CDC *pDC  = GetDC();
	//LoadImageFromResource(&ImageBg, IDB_PNG11, _T("PNG"));
	//HRESULT result = Image.Load(_T("背景.png"));
	//TransparentPNG(&ImageBg);
	//ImageBg.Draw(pDC->m_hDC, 0, 0, rect.Width(), rect.Height());
	CRgn rgn;
	//CreateRgnByImage(&ImageBg, rgn);
	
	//MoveWindow(&rect);
	rgn.CreateRoundRectRgn(rect.left, rect.top, rect.right, rect.bottom, 100, 100);
	SetWindowRgn(rgn, TRUE);
	

	//创建CImageList
	if (ImageList.GetSafeHandle() == NULL)
	{
		ImageList.Create(80, 80, ILC_MASK | ILC_COLOR32, 0, 0);
		//ImageList.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));
		m_ImageList.SetImageList(&ImageList, LVSIL_NORMAL);
	}

	//按钮图片
	//CDC *pDC  = m_Btn1.GetWindowDC()->m_hDC;
	//列表框
	//GetDlgItem(IDC_LIST1)->ModifyStyle(0, SS_GRAYFRAME/*灰色背景*/, 0);
	m_ImageList.SetBkColor(RGB(192, 192, 192));

	//delete image;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CdmtjsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CdmtjsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;


		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		CRect rect;
		GetClientRect(&rect);
		
		
		/*
		Graphics graphics(dc.m_hDC);

		//if (!img.IsNull()) img.Destroy();
		//img.Load(_T("背景.png")); //load载入，否则不显示  
		//TransparentPNG(&img); //调用透明化处理函数  
		//if (!img.IsNull()) img.Draw(dc.m_hDC, 0, 0); //以左上角为原点，按原始大小，在(80,20)处贴图  


		//Image bg(L"G:\\Test\\ui\\background.png"); //载入背景图 
		Image* bg;//(L"..\\res\\start.png");  
		if (ImageFromIDResource(IDB_PNG11, L"PNG", bg) == false)
		{
		//TRACE("ImageFromIDResource failed.");
		}
		else
		{
		//TRACE("ImageFromIDResource success.");
		graphics.DrawImage(bg,rect.left,rect.top,rect.Width(),rect.Height());
		delete bg;
		}
		Image *bg1;
		Graphics graphics1(GetDlgItem(IDC_BUTTON2)->GetDC()->GetSafeHdc());
		GetDlgItem(IDC_BUTTON2)->GetWindowRect(rect);
		ScreenToClient(rect);
		ImageFromIDResource(IDB_PNG3, L"PNG", bg1);
		//Image image(L"按键-关闭.png", TRUE); //图片的路径，我把imgaresed文件夹图片放在res中
		graphics1.DrawImage(bg1, 0, 0, rect.Width(), rect.Height());
		delete bg1;
		*/

		CImage Image;
		LoadImageFromResource(&Image, IDB_PNG11, _T("PNG"));
		Image.Draw(dc.m_hDC, rect.left, rect.top, rect.Width(), rect.Height());
		
		CDC *pDC = GetDlgItem(IDC_BUTTON2)->GetDC();	
		
		//关闭
		GetDlgItem(IDC_BUTTON2)->GetWindowRect(rect);
		LoadImageFromResource(&Image, IDB_PNG3, _T("PNG"));
		if (Image.IsNull())
		{
			MessageBox(_T("没加载成功"));
			return ;
		}
		if (Image.GetBPP() == 32) //确认该图像包含Alpha通道  
		{
			int i;
			int j;
			for (i = 0; i<Image.GetWidth(); i++)
			{
				for (j = 0; j<Image.GetHeight(); j++)
				{
					byte *pByte = (byte *)Image.GetPixelAddress(i, j);
					pByte[0] = pByte[0] * pByte[3] / 255;
					pByte[1] = pByte[1] * pByte[3] / 255;
					pByte[2] = pByte[2] * pByte[3] / 255;
				}
			}
		}
		Image.Draw(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height());
		//最小化
		pDC = GetDlgItem(IDC_BUTTON1)->GetDC();
		GetDlgItem(IDC_BUTTON1)->GetWindowRect(rect);
		LoadImageFromResource(&Image, IDB_PNG5, _T("PNG"));
		if (Image.IsNull())
		{
			MessageBox(_T("没加载成功"));
			return;
		}
		if (Image.GetBPP() == 32) //确认该图像包含Alpha通道  
		{
			int i;
			int j;
			for (i = 0; i<Image.GetWidth(); i++)
			{
				for (j = 0; j<Image.GetHeight(); j++)
				{
					byte *pByte = (byte *)Image.GetPixelAddress(i, j);
					pByte[0] = pByte[0] * pByte[3] / 255;
					pByte[1] = pByte[1] * pByte[3] / 255;
					pByte[2] = pByte[2] * pByte[3] / 255;
				}
			}
		}
		Image.Draw(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height());

		//最大化
		pDC = GetDlgItem(IDC_BUTTON3)->GetDC();
		GetDlgItem(IDC_BUTTON3)->GetWindowRect(rect);
		LoadImageFromResource(&Image, IDB_PNG4, _T("PNG"));
		if (Image.IsNull())
		{
			MessageBox(_T("没加载成功"));
			return;
		}
		if (Image.GetBPP() == 32) //确认该图像包含Alpha通道  
		{
			int i;
			int j;
			for (i = 0; i<Image.GetWidth(); i++)
			{
				for (j = 0; j<Image.GetHeight(); j++)
				{
					byte *pByte = (byte *)Image.GetPixelAddress(i, j);
					pByte[0] = pByte[0] * pByte[3] / 255;
					pByte[1] = pByte[1] * pByte[3] / 255;
					pByte[2] = pByte[2] * pByte[3] / 255;
				}
			}
		}
		Image.Draw(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height());

		//搜索
		pDC = GetDlgItem(IDC_BUTTON4)->GetDC();
		GetDlgItem(IDC_BUTTON4)->GetWindowRect(rect);
		LoadImageFromResource(&Image, IDB_PNG6, _T("PNG"));
		if (Image.IsNull())
		{
			MessageBox(_T("没加载成功"));
			return;
		}
		if (Image.GetBPP() == 32) //确认该图像包含Alpha通道  
		{
			int i;
			int j;
			for (i = 0; i<Image.GetWidth(); i++)
			{
				for (j = 0; j<Image.GetHeight(); j++)
				{
					byte *pByte = (byte *)Image.GetPixelAddress(i, j);
					pByte[0] = pByte[0] * pByte[3] / 255;
					pByte[1] = pByte[1] * pByte[3] / 255;
					pByte[2] = pByte[2] * pByte[3] / 255;
				}
			}
		}
		Image.Draw(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height());

		//文件夹
		pDC = GetDlgItem(IDC_BUTTON6)->GetDC();
		GetDlgItem(IDC_BUTTON6)->GetWindowRect(rect);
		LoadImageFromResource(&Image, IDB_PNG7, _T("PNG"));
		if (Image.IsNull())
		{
			MessageBox(_T("没加载成功"));
			return;
		}
		if (Image.GetBPP() == 32) //确认该图像包含Alpha通道  
		{
			int i;
			int j;
			for (i = 0; i<Image.GetWidth(); i++)
			{
				for (j = 0; j<Image.GetHeight(); j++)
				{
					byte *pByte = (byte *)Image.GetPixelAddress(i, j);
					pByte[0] = pByte[0] * pByte[3] / 255;
					pByte[1] = pByte[1] * pByte[3] / 255;
					pByte[2] = pByte[2] * pByte[3] / 255;
				}
			}
		}
		Image.Draw(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height());

		//选择图片
		pDC = GetDlgItem(IDC_BUTTON5)->GetDC();
		GetDlgItem(IDC_BUTTON5)->GetWindowRect(rect);
		LoadImageFromResource(&Image, IDB_PNG8, _T("PNG"));
		if (Image.IsNull())
		{
			MessageBox(_T("没加载成功"));
			return;
		}
		if (Image.GetBPP() == 32) //确认该图像包含Alpha通道  
		{
			int i;
			int j;
			for (i = 0; i<Image.GetWidth(); i++)
			{
				for (j = 0; j<Image.GetHeight(); j++)
				{
					byte *pByte = (byte *)Image.GetPixelAddress(i, j);
					pByte[0] = pByte[0] * pByte[3] / 255;
					pByte[1] = pByte[1] * pByte[3] / 255;
					pByte[2] = pByte[2] * pByte[3] / 255;
				}
			}
		}
		Image.Draw(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height());

		//载入图片
		pDC = GetDlgItem(IDC_BUTTON7)->GetDC();
		GetDlgItem(IDC_BUTTON7)->GetWindowRect(rect);
		LoadImageFromResource(&Image, IDB_PNG9, _T("PNG"));
		if (Image.IsNull())
		{
			MessageBox(_T("没加载成功"));
			return;
		}
		if (Image.GetBPP() == 32) //确认该图像包含Alpha通道  
		{
			int i;
			int j;
			for (i = 0; i<Image.GetWidth(); i++)
			{
				for (j = 0; j<Image.GetHeight(); j++)
				{
					byte *pByte = (byte *)Image.GetPixelAddress(i, j);
					pByte[0] = pByte[0] * pByte[3] / 255;
					pByte[1] = pByte[1] * pByte[3] / 255;
					pByte[2] = pByte[2] * pByte[3] / 255;
				}
			}
		}
		Image.Draw(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height());

		Image.Destroy();
		ReleaseDC(pDC);
		
		//CDialog::OnPaint();
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CdmtjsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CdmtjsDlg::OnBnClickedButton2()//关闭
{
	// TODO: 在此添加控件通知处理程序代码
	CString strFileSave = folder;
	strFileSave += ("\\temp");
	myDeleteDirectory(strFileSave);
	ImageBg.Destroy();
	PostQuitMessage(1);
}


void CdmtjsDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_SHOWMINIMIZED);
}


void CdmtjsDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IsZoomed()) {		
		ShowWindow(SW_SHOWNORMAL);
		CRect rect;
		GetClientRect(&rect);
		CRgn rgn;
		rgn.CreateRoundRectRgn(rect.left, rect.top, rect.right, rect.bottom, 100, 100);
		SetWindowRgn(rgn, TRUE);
		ReSize();
		this->Invalidate();
	}		
	else {
		ShowWindow(SW_SHOWMAXIMIZED);
		CRect rect;
		GetClientRect(&rect);
		CRgn rgn;
		rgn.CreateRoundRectRgn(rect.left, rect.top, rect.right, rect.bottom, 100, 100);
		SetWindowRgn(rgn, TRUE);
		ReSize();
		this->Invalidate();

	}
		 
}


void CdmtjsDlg::OnBnClickedButton6()//文件夹
{
	// TODO: 在此添加控件通知处理程序代码
	ZeroMemory(folder, sizeof(folder));

	BROWSEINFO bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = folder;
	bi.lpszTitle = _T("请选择图片库：");
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	//弹出选择目录对话框
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);

	if (lp && SHGetPathFromIDList(lp, folder))
	{
		//str.Format(_T("选择的目录为 %s"), folder);
		//AfxMessageBox(str);
		SetDlgItemText(IDC_TXT_PATH, folder);

	}
	//else
		//AfxMessageBox(_T("无效的目录，请重新选择"));

	//新建文件夹temp 用于存储位图图片
	CString   strFolderPath = folder;
	strFolderPath += "\\temp";
	if (!PathIsDirectory(strFolderPath))
	{
		CreateDirectory(strFolderPath, NULL);
	}
	
}

void CdmtjsDlg::FindFile(CString Curdir)
{
	HANDLE hfile;//查找文件句柄
	WIN32_FIND_DATA wfdata;//文件信息结构
	BOOL IsOver = false;//查找过程结束标志
	CString strname;//文件名
	CString strfull;//全路径
	CString first = Curdir + _T("\\") + _T("\\*.*");
	hfile = FindFirstFile((LPCTSTR)(first), &wfdata);//查找第一个文件
	if (hfile == INVALID_HANDLE_VALUE)
		IsOver = true;//查找过程结束
	while (!IsOver)
	{
		strname.Format(_T("%s"), wfdata.cFileName);//获取找到的文件名
		strfull = Curdir + "\\" + strname;//全路径
		if ((wfdata.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) && (wfdata.cFileName[0] != _TEXT('.')))//
		{
			SetCurrentDirectory(wfdata.cFileName);
			FindFile(strfull);//递归调用
			SetCurrentDirectory(_T(".."));//返回当前目录
		}
		else if (wfdata.cFileName[0] != _TEXT('.'))
		{
			fileAll[TSHEET] = strfull;
			filename[TSHEET] = wfdata.cFileName;
			//AfxMessageBox(fileAll[TSHEET]);
			TSHEET++;
		}

		IsOver = !FindNextFile(hfile, &wfdata);//查找下一个文件
	}
	FindClose(hfile);//关闭句柄
}


void CdmtjsDlg::OnBnClickedButton5()//选择图片
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog  dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T(" BMP(*.BMP)|| GIF(*.gif)|| PNG(*.png)||  JPEG(*.jpg)|| ICO(*.ico)||PNM(*.pnm)||PCX(*.pcx)||TIFF(*.tif)||All Files (*.*)|*.*||"), NULL);
	dlgFile.m_ofn.lpstrInitialDir = folder;

	if (dlgFile.DoModal()==IDOK)
	{
		filePath = dlgFile.GetPathName();
		//显示图片
		//((CStatic*)GetDlgItem(IDC_STATIC_PIC))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
		CWnd *pWnd = GetDlgItem(IDC_STATIC_PIC);
		CDC  *pDC = NULL;
		pDC = pWnd->GetDC();
		//ShowJpgGif(pDC,dlg.GetPathName(),0,0);  
		CImage image1;//image是CImage类的一个对象，用来加载图像的
		image1.Load(filePath);
		::SetStretchBltMode(*pDC, HALFTONE);
		::SetBrushOrgEx(*pDC, 0, 0, NULL);
		CRect rect;
		pWnd->GetClientRect(&rect);
		image1.Draw(*pDC, rect);
		ReleaseDC(pDC);
	}
}


	void CdmtjsDlg::OnBnClickedButton4()//搜索
	{
		// TODO: 在此添加控件通知处理程序代码
		//获取张数
		UpdateData(TRUE);
		CString wstr;
		char str[20] = { 0 };
		m_Edit.GetWindowText(wstr);
		wcstombs(str, wstr, wcslen(wstr));
		//int m;
		SHEET = atof(str);
		//FindFile(folder);
		picSeek();
		CString strOpenFileName;
		//m_ImageList.SetImageList(&ImageList, LVSIL_NORMAL);
		m_ImageList.DeleteAllItems();
		for (int i = 0; i<SHEET && filename[i] != ""; i++)
		{
			SHFILEINFO info;
			SHGetFileInfo(fileAll[i], 0, &info, sizeof(&info), SHGFI_DISPLAYNAME | SHGFI_ICON);
			int j = ImageList.Add(info.hIcon);
			//转换为位图
			//设置编码方式
			strOpenFileName = fileAll[i];
			// 建立图形对象  
			Graphics graphics(GetDC()->m_hDC);

			// 装入当前已经打开的图像文件  
			Image image(strOpenFileName);

			CString strFileSave = folder;
			strFileSave += ("\\temp\\i.bmp");


			CLSID clsid;
			if (GetImageCLSID(L"image/bmp", &clsid))
			{
				int a = image.Save(strFileSave, &clsid, NULL);
				// 将保存后的图像进行显示  
				strOpenFileName = strFileSave;
			}

			HBITMAP hBitmap;
			CBitmap *pBitmap;
			pBitmap = new CBitmap;
			hBitmap = (HBITMAP)LoadImage(NULL, strOpenFileName, IMAGE_BITMAP, 80, 80, LR_LOADFROMFILE);
			//LoadImage（所需要图片的实例的句柄,图片所在路径及文件名,加载图片类型IMAGE_BITMAP为装载位图,图片宽度，图片高度）
			pBitmap->Attach(hBitmap);
			j = ImageList.Add(pBitmap, RGB(0, 0, 0));
			m_ImageList.InsertItem(j, info.szDisplayName, j);

		}
		DeleteFile(strOpenFileName);
	}


	void CdmtjsDlg::OnClickedButton7()//载入图片
	{
		// TODO: 在此添加控件通知处理程序代码
		FindFile(folder);
		CString strOpenFileName;
		//m_ImageList.SetImageList(&ImageList, LVSIL_NORMAL);
		m_ImageList.DeleteAllItems();
		for (int i = 0; filename[i] != ""; i++)
		{
			SHFILEINFO info;
			SHGetFileInfo(fileAll[i], 0, &info, sizeof(&info), SHGFI_DISPLAYNAME | SHGFI_ICON);
			int j = ImageList.Add(info.hIcon);
			//转换为位图
			//设置编码方式
			strOpenFileName = fileAll[i];
			// 建立图形对象  
			Graphics graphics(GetDC()->m_hDC);

			// 装入当前已经打开的图像文件  
			Image image(strOpenFileName);

			CString strFileSave= folder;
			strFileSave += ("\\temp\\i.bmp");


			CLSID clsid;
			if (GetImageCLSID(L"image/bmp", &clsid))
			{
				int a=image.Save(strFileSave, &clsid, NULL);
				
				// 将保存后的图像进行显示  
				strOpenFileName = strFileSave;
			}

			HBITMAP hBitmap;
			CBitmap *pBitmap;
			pBitmap = new CBitmap;
			hBitmap = (HBITMAP)LoadImage(NULL, strOpenFileName, IMAGE_BITMAP, 80, 80, LR_LOADFROMFILE);
			//LoadImage（所需要图片的实例的句柄,图片所在路径及文件名,加载图片类型IMAGE_BITMAP为装载位图,图片宽度，图片高度）
			pBitmap->Attach (hBitmap);
			j=ImageList.Add (pBitmap, RGB(0, 0, 0));
			m_ImageList.InsertItem(j, info.szDisplayName, j);

		}
		DeleteFile(strOpenFileName);
	}

	int CdmtjsDlg::GetImageCLSID(const WCHAR *format, CLSID *pCLSID)
	{
		UINT num = 0;
		UINT size = 0;
		ImageCodecInfo* pImageCodecInfo = NULL;
		GetImageEncodersSize(&num, &size);
		if (size == 0)
			return FALSE; // 编码信息不可用  
						  // 分配内存  
		pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
		if (pImageCodecInfo == NULL)
			return FALSE; // 分配失败  
						  // 获得系统中可用的编码方式的所有信息  
		GetImageEncoders(num, size, pImageCodecInfo);
		// 在可用编码信息中查找 format 格式是否被支持  

		for (UINT i = 0; i<num; ++i)
		{
			//MimeType: 编码方式的具体描述  
			if (wcscmp(pImageCodecInfo[i].MimeType, format) == 0)
			{
				*pCLSID = pImageCodecInfo[i].Clsid;
				free(pImageCodecInfo);
				return TRUE;
			}
		}
		free(pImageCodecInfo);
		return FALSE;
	}

	WCHAR* CdmtjsDlg::ToWChar(LPCCH str)
	{
		//在 GDI＋中，有关字符的参数类型全部都是 WCHAR 类型的  
		//该函数是将传统字符串进行转换  
		static WCHAR buffer[1024];
		wcsset(buffer, 0);
		MultiByteToWideChar(CP_ACP, 0, str, strlen(str), buffer, 1024);
		return buffer;
	}

   //点击客户区可移动位置
	void CdmtjsDlg::OnLButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值

		CDialogEx::OnLButtonDown(nFlags, point);
		CDialogEx::OnLButtonDown(nFlags, point);
		if (!IsZoomed()) {
            PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
		}
		
	}

	//删除temp文件夹
	void CdmtjsDlg::myDeleteDirectory(CString directory_path)
	{
		CFileFind finder;
		CString path;
		path.Format(_T("%s/*.*"), directory_path);
		BOOL bWorking = finder.FindFile(path);
		while (bWorking) {
			bWorking = finder.FindNextFile();
			if (finder.IsDirectory() && !finder.IsDots()) {//处理文件夹  
				myDeleteDirectory(finder.GetFilePath()); //递归删除文件夹  
				RemoveDirectory(finder.GetFilePath());
			}
			else {//处理文件  
				DeleteFile(finder.GetFilePath());
			}
		}
	}

	//让资源中的png图片变成GDI+中的Image对象即可进行绘画  
	inline BOOL CdmtjsDlg::ImageFromIDResource(UINT resourceID, LPCTSTR resourceType, Image *& image)
	{
		HINSTANCE hInst = AfxGetResourceHandle();
		HRSRC hRsrc = ::FindResource(hInst, MAKEINTRESOURCE(resourceID), resourceType);
		if (hRsrc == NULL)
			return FALSE;
		// load resource into memory  
		DWORD len = SizeofResource(hInst, hRsrc);
		BYTE* lpRsrc = (BYTE*)LoadResource(hInst, hRsrc);
		if (lpRsrc == NULL)
			return FALSE;
		// Allocate global memory on which to create stream  
		HGLOBAL m_hMem = GlobalAlloc(GMEM_FIXED, len);
		BYTE* pmem = (BYTE*)GlobalLock(m_hMem);
		memcpy(pmem, lpRsrc, len);
		IStream* pstm;
		CreateStreamOnHGlobal(m_hMem, FALSE, &pstm);
		// load from stream  
		image = Gdiplus::Image::FromStream(pstm);
		// free/release stuff  
		GlobalUnlock(m_hMem);
		GlobalFree(m_hMem);
		pstm->Release();
		FreeResource(lpRsrc);
		return TRUE;
	}


	void CdmtjsDlg::OnStnClickedStaticPic()
	{
		// TODO: 在此添加控件通知处理程序代码
		RECT rect;
		CDC* pDC = GetDlgItem(IDC_STATIC_PIC)->GetDC();
		GetDlgItem(IDC_STATIC_PIC)->GetWindowRect(&rect);
		//CRgn rgn;
		//rgn.CreateRoundRectRgn(rect.left, rect.top, rect.right, rect.bottom, 100, 100);
		//SetWindowRgn(rgn, TRUE);
	}


	void CdmtjsDlg::picSeek()
	{
		int i, j;
		double k;
		CString temp;

		//初始化
		
		for (i = 0; i <= Gmax; i++)
			figBase[i] = 0;
		for (i = 0; i < TSHEET; i++)
			for (j = 0; j <= Gmax; j++)
				figAll[i][j] = 0;
		
		//提取选择图片的hsv像素
		pickColor(filePath, -1);
		//提取库图片hsv像素
		for (i = 0; i < TSHEET; i++)
			pickColor(fileAll[i], i);

		//计算距离
		for (i = 0; i < TSHEET; i++) {
			//picComp[i] = getDistance(figAll[i], figBase);//欧氏距离
			//picComp[i] = getCosDistance(figAll[i], figBase);//马氏距离
			picComp[i] = getPSDistance(figAll[i], figBase);//巴氏距离
		}
		
		//排序
		for (i = 0; i < TSHEET - 1; i++)
			for (j = i + 1; j < TSHEET; j++) {
				if (picComp[i] < picComp[j]) {
					k = picComp[i];
					picComp[i] = picComp[j];
					picComp[j] = k;

					temp = fileAll[i];
					fileAll[i] = fileAll[j];
					fileAll[j] = temp;

					temp = filename[i];
					filename[i] = filename[j];
					filename[j] = temp;

				}
			}

	}
	
	void CdmtjsDlg::pickColor(CString fp, int num)
	{
		CImage Img;
		int i, j, k;
		double tr, tg, tb, cmax, cmin, delta;
		byte *pRData = NULL;
		int tG;
		double th, ts, tv;
		int pit, nWidth, nHeight, bpp;
		RGBQUAD ColorTabs[256];
		int nColorTableEntries;
		if (S_OK == Img.Load((LPCTSTR)fp)) {
			nWidth = Img.GetWidth();//获取图像宽度
			nHeight = Img.GetHeight();//获取图像高度
			bpp = Img.GetBPP();//每个像素的位数
			pit = Img.GetPitch();//每行字节数
			pRData = (byte *)Img.GetBits();//图片首地址，可能在左上，也可能在左下，根据pit的正负确定
			if (bpp == 8) {//伪彩色，得到调色板
				nColorTableEntries = Img.GetMaxColorTableEntries();
				Img.GetColorTable(0, nColorTableEntries, ColorTabs);
			}
			for (j = 0; j < nHeight; j++)
				for (i = 0; i < nWidth; i++)
				{
					if (bpp == 8) {//伪彩色，要根据调色板找到对应rgb
						k = bytesToInt(*(pRData + pit*(nHeight - j - 1) + i));
						tr = ColorTabs[k].rgbBlue;
						tg = ColorTabs[k].rgbGreen;
						tb = ColorTabs[k].rgbRed;
					}
					else {
						tr = (double)bytesToInt(*(pRData + pit*(nHeight - j - 1) + i * 3 + 2));
						tg = (double)bytesToInt(*(pRData + pit*(nHeight - j - 1) + i * 3 + 1));
						tb = (double)bytesToInt(*(pRData + pit*(nHeight - j - 1) + i * 3));
					}
					
					//转化成HSV	
					
					cmax = max(max(tr, tg), tb);
					cmin = min(min(tr, tg), tb);
					delta = cmax - cmin;
					if (delta == 0)
						th = 0;
					else if (cmax == tr)
						th = 60*((tg - tb) / delta) ;
					else if (cmax == tg)
						th = 60*((tb - tr) / delta + 2);
					else if (cmax == tb)
						th = 60*((tr - tg) / delta + 4);
					if (th < 0)
						th += 360;
					tv = cmax / 255.0;
					if (cmax == 0)
						ts = 0;
					else ts = delta / cmax;
					//获得直方图
					//对HSV的量化

					if (th > 15 && th <= 25)
						th = 1;
					else if (th > 25 && th <= 45)
						th = 2;
					else if (th > 45 && th <= 55)
						th = 3;
					else if (th > 55 && th <= 80)
						th = 4;
					else if (th > 80 && th <= 108)
						th = 5;
					else if (th > 108 && th <= 140)
						th = 6;
					else if (th > 140 && th <= 165)
						th = 7;
					else if (th > 165 && th <= 190)
						th = 8;
					else if (th > 190 && th <= 220)
						th = 9;
					else if (th > 220 && th <= 255)
						th = 10;
					else if (th > 255 && th <= 275)
						th = 11;
					else if (th > 275 && th <= 290)
						th = 12;
					else if (th > 290 && th <= 316)
						th = 13;
					else if (th > 316 && th <= 330)
						th = 14;
					else if (th > 330 && th <= 345)
						th = 15;
					else th = 0;
					
					if (ts >= 0 && ts <= 0.15)
						ts = 0;
					else if (ts > 0.15&&ts <= 0.4)
						ts = 1;
					else if (ts > 0.4&&ts <= 0.75)
						ts = 2;
					else ts = 3
						;
					if (tv >= 0 && tv <= 0.15)
						tv = 0;
					else if (tv > 0.15 && tv <= 0.4)
						tv = 1;
					else if (tv > 0.4 && tv <= 0.75)
						tv = 2;
					else tv = 3;
					
					//构造一维特征矢量
					tG = th*Qs*Qv + ts*Qv + tv;
				
					if (num == -1) {//被选中的基准图片
						figBase[(int)tG]++;
					}
					else {//全体图片库图片
						figAll[num][(int)tG]++;
					}

				}	
			//标准化
			  for (i = 0; i <= Gmax; i++) {
					if (num == -1) {//被选中的基准图片
						figBase[i] = figBase[i]/(nWidth*nHeight);
					}
					else {//全体图片库图片
						figAll[num][i] = figAll[num][i]/(nWidth*nHeight);
					}
				}
			
			
		}
		else {
			printf("image loading error!\n");
		}
		Img.Destroy();
		

	}

	int CdmtjsDlg::bytesToInt(byte bytes)
	{
		int addr = bytes & 0xFF;
		return addr;
	}

	float CdmtjsDlg::getCosDistance(double * sur, double * dst)
	{
		float surSum = 0, dstSum = 0, sum  = 0;
		for (int i = 0; i <= Gmax; i++) {
			surSum += pow(sur[i] + 0.0, 2);
			dstSum += pow(dst[i] + 0.0, 2);
			sum += sur[i] * dst[i];
		}
		surSum = sqrt(surSum);
		dstSum = sqrt(dstSum);
		return sum / (surSum*dstSum);
	}

	float CdmtjsDlg::getPSDistance(double * sur, double * dst)
	{
		float sum = 0;
		for (int i = 0; i <= Gmax; i++) {
			sum += sqrt(sur[i] * dst[i]);
		}
		return sum;
	}

	float CdmtjsDlg::getDistance(double * sur, double * dst)
	{
		float sum = 0;
		for (int i = 0; i <= Gmax; i++) {
			sum += pow(sur[i] - dst[i], 4);
		}
		return sqrt(sum);
	}

	void CdmtjsDlg::TransparentPNG(CImage * png)
	{
		for (int i = 0; i <png->GetWidth(); i++) //遍历像素处理  
		{
			for (int j = 0; j < png->GetHeight(); j++)
			{
				unsigned char* pucColor = reinterpret_cast<unsigned char*>(png->GetPixelAddress(i, j));
				pucColor[0] = pucColor[0] * pucColor[3] / 255;
				pucColor[1] = pucColor[1] * pucColor[3] / 255;
				pucColor[2] = pucColor[2] * pucColor[3] / 255;
			}
		}
	}

	BOOL CdmtjsDlg::LoadImageFromResource(CImage * pImage, UINT nResID, LPCTSTR lpTyp)
	{
		if (pImage  == NULL)
			return false;
		pImage->Destroy();
		// 查找资源  
		HRSRC hRsrc  = ::FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(nResID), lpTyp);
		if (hRsrc  == NULL)
			return false;
		// 加载资源  
		HGLOBAL hImgData  = ::LoadResource(AfxGetResourceHandle(), hRsrc);
		if (hImgData  == NULL)
		{
			::FreeResource(hImgData);
			return false;
		}
		// 锁定内存中的指定资源  
		LPVOID lpVoid  = ::LockResource(hImgData);
		LPSTREAM pStream  = NULL;
		DWORD dwSize  = ::SizeofResource(AfxGetResourceHandle(), hRsrc);
		HGLOBAL hNew  = ::GlobalAlloc(GHND, dwSize);
		LPBYTE lpByte  = (LPBYTE)::GlobalLock(hNew);
		::memcpy(lpByte, lpVoid, dwSize);
		// 解除内存中的指定资源  
		::GlobalUnlock(hNew);
		// 从指定内存创建流对象  
		HRESULT ht  = ::CreateStreamOnHGlobal(hNew, TRUE, &pStream);
		if (ht  != S_OK )
		{
			GlobalFree(hNew);
		}
		else 
		{
			// 加载图片  
			pImage->Load(pStream);
		GlobalFree(hNew);
		}
			// 释放资源  
		::FreeResource(hImgData);
		return true;
	}



	HBRUSH CdmtjsDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
	{
		HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

		// TODO:  在此更改 DC 的任何特性
		if (nCtlColor == CTLCOLOR_STATIC)//如果当前控件属于静态文本
		{
			//pDC->SetTextColor(RGB(255, 0, 0)); //字体颜色
			//pDC->SetBkMode(TRANSPARENT); //设置字体背景为透明
			//pDC->SetBkColor(RGB(192, 192, 192));
			
		}
		if (nCtlColor == CTLCOLOR_EDIT) //文本编辑框颜色  
		{
			//pDC->SetTextColor(RGB(0, 0, 255));
			//pDC->SetBkColor(RGB(192, 192, 192)); //静态控件的背景颜色设置
			//return (HBRUSH)::GetStockObject(HOLLOW_BRUSH);

			//pDC->SetBkMode(TRANSPARENT);
		}
		if (nCtlColor == CTLCOLOR_SCROLLBAR) //滑动条颜色  
		{
			//pDC->SetTextColor(RGB(0, 0, 255));
			pDC->SetBkColor(RGB(192, 192, 192)); //静态控件的背景颜色设置  
												 //pDC->SetBkMode(TRANSPARENT);
		}
		
		// TODO: Return a different brush if the default is not desired

		// TODO:  如果默认的不是所需画笔，则返回另一个画笔
		return hbr;
	}


	void CdmtjsDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
	{
		LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
		// TODO: 在此添加控件通知处理程序代码
		m_ImageList.SetRedraw(FALSE);
		//更新内容
		m_ImageList.SetRedraw(TRUE);
		m_ImageList.Invalidate();
		m_ImageList.UpdateWindow();
		*pResult = 0;
	}


	BOOL CdmtjsDlg::OnEraseBkgnd(CDC* pDC)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		//ImageBg.AlphaBlend(pDC->GetSafeHdc(), 0, 0);
		pDC->SetBkMode(TRANSPARENT);
		return CDialogEx::OnEraseBkgnd(pDC);
	}

	void CdmtjsDlg::CreateRgnByImage(CImage * pImage, CRgn & rgn)
	{
		rgn.CreateRectRgn(0, 0, 0, 0);
		CRgn tempRgn;
		for (UINT h = 0; h < (UINT)pImage->GetHeight(); ++h)
		{
			UINT w = 0;
			while (w < (UINT)ImageBg.GetWidth())
			{
				UINT leftX = w;
				while (w < (UINT)ImageBg.GetWidth())
				{
					UCHAR* cr = (UCHAR*)pImage->GetPixelAddress(w, h);
					if (cr[3] != 0)
						break;
					leftX = w;
					w++;
				}
				while (w < (UINT)ImageBg.GetWidth())
				{
					UCHAR* cr = (UCHAR*)pImage->GetPixelAddress(w, h);
					if (cr[3] == 0)
						break;
					w++;
				}
				tempRgn.CreateRectRgn(leftX, h, w - 1, h + 1);
				rgn.CombineRgn(&rgn, &tempRgn, RGN_OR);
				tempRgn.DeleteObject();
			}
		}
	}

	