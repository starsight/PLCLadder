#pragma once


// CFindText 对话框

class CFindText : public CDialogEx
{
	DECLARE_DYNAMIC(CFindText)

public:
	CFindText(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFindText();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
