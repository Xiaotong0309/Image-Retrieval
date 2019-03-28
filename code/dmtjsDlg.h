
// dmtjsDlg.h : 头文件
//

#pragma once
#include "imagelistctrl1.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "gdiplusheaders.h"




// CdmtjsDlg 对话框
class CdmtjsDlg : public CDialogEx
{
// 构造
public:
	CdmtjsDlg(CWnd* pParent = NULL);	// 标准构造函数

	void ReSize();
	POINT old;
	afx_msg void OnSize(UINT nType, int cx, int cy);
#define PI 3.1415926
#define Qs 4
#define Qv 4
#define Gmin 0
#define Gmax 255
#define pathLen 100

	int TSHEET = 0;//图片库图片张数
	int SHEET;//需要显示的张数
	CString filePath;//被选作基准的图像
	CString fileAll[200];//图像库
	CString filename[200];//图像库图片名字
	TCHAR folder[MAX_PATH];//文件夹路径
	int index = 0;
	double figBase[Gmax + 1];//选作基准的颜色直方图
	double figAll[200][Gmax + 1];//图像库的颜色直方图
	double picComp[200];//选作基准的图片与图片库比较值




	
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DMTJS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	CImagelistctrl1 ImageList;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton6();
	void FindFile(CString Curdir);
	//afx_msg void OnBnClickedButton7();
//	CListCtrl m_ImageList;
//	CImageList ImageList;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnClickedButton7();
	int GetImageCLSID(const WCHAR * format, CLSID * pCLSID);
	WCHAR * ToWChar(LPCCH  str);
//	CImageList ImageList;
	CListCtrl m_ImageList;
	CImageList ImageList;
	
//	ULONG_PTR m_GdiPlusToken;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void myDeleteDirectory(CString directory_path);
	inline BOOL ImageFromIDResource(UINT resourceID, LPCTSTR resourceType, Image*& image);
	afx_msg void OnStnClickedStaticPic();
	CEdit m_Edit;
	void picSeek();
	void pickColor(CString fp, int num);
	int bytesToInt(byte bytes);
	float getCosDistance(double *sur, double *dst);
	float getPSDistance(double *sur, double*dst);
	float getDistance(double *sur, double *dst);


	//HRESULT Load(LPCTSTR pszFileName, bool bPreMultiply);
	void TransparentPNG(CImage *png);
//	BITMAP m_Bn1;
//	Bitmap m_Bg1;
//	CImage img;
//	CButton m_Btn1;
//	CButton m_Btn1;
	BOOL LoadImageFromResource(CImage *pImage, UINT nResID, LPCTSTR lpTyp);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CBrush m_brush;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void CreateRgnByImage(CImage* pImage, CRgn &rgn);
	//bool LoadImageFromResource1(CImage* pImage, UINT nResID, LPCWSTR lpTyp);
	//HRESULT Load(LPCTSTR pszFileName, bool bPreMultiply);
};
