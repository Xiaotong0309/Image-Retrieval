
// dmtjsDlg.h : ͷ�ļ�
//

#pragma once
#include "imagelistctrl1.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "gdiplusheaders.h"




// CdmtjsDlg �Ի���
class CdmtjsDlg : public CDialogEx
{
// ����
public:
	CdmtjsDlg(CWnd* pParent = NULL);	// ��׼���캯��

	void ReSize();
	POINT old;
	afx_msg void OnSize(UINT nType, int cx, int cy);
#define PI 3.1415926
#define Qs 4
#define Qv 4
#define Gmin 0
#define Gmax 255
#define pathLen 100

	int TSHEET = 0;//ͼƬ��ͼƬ����
	int SHEET;//��Ҫ��ʾ������
	CString filePath;//��ѡ����׼��ͼ��
	CString fileAll[200];//ͼ���
	CString filename[200];//ͼ���ͼƬ����
	TCHAR folder[MAX_PATH];//�ļ���·��
	int index = 0;
	double figBase[Gmax + 1];//ѡ����׼����ɫֱ��ͼ
	double figAll[200][Gmax + 1];//ͼ������ɫֱ��ͼ
	double picComp[200];//ѡ����׼��ͼƬ��ͼƬ��Ƚ�ֵ




	
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DMTJS_DIALOG };
#endif

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
