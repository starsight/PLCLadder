; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPointSet
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MUL.h"
LastPage=0

ClassCount=16
Class1=CMULApp
Class2=CMULDoc
Class3=CMULView
Class4=CMainFrame

ResourceCount=10
Resource1=IDR_DRAWTYPE
Resource2=IDD_SYNTAX
Resource3=IDR_ITEMMENU
Class5=CChildFrame
Class6=CAboutDlg
Resource4=IDR_LADDER
Resource5=IDD_POINTSET
Resource6=IDR_MAINFRAME
Class7=CLADDoc
Class8=CLADView
Resource7=IDR_ACCELERATOR1
Resource8=IDD_ABOUTBOX
Resource9=IDR_MULTYPE
Class9=CPointSet
Class10=CSyntax
Class11=CAreSet
Class12=CSplashWnd
Class13=CSettingComDlg
Class14=CCommunicationDlg
Class15=COpenComDlg
Class16=CCompileDlg
Resource10=IDD_WORKARESET

[CLS:CMULApp]
Type=0
HeaderFile=MUL.h
ImplementationFile=MUL.cpp
Filter=N
LastObject=CMULApp

[CLS:CMULDoc]
Type=0
HeaderFile=MULDoc.h
ImplementationFile=MULDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CMULDoc

[CLS:CMULView]
Type=0
HeaderFile=MULView.h
ImplementationFile=MULView.cpp
Filter=C
LastObject=CMULView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_FILE_NEW
BaseClass=CMDIFrameWnd
VirtualFilter=fWC


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
LastObject=CChildFrame


[CLS:CAboutDlg]
Type=0
HeaderFile=MUL.cpp
ImplementationFile=MUL.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_VIEW_LADDER
Command8=ID_VIEW_INSTRU
Command9=ID_VIEW_ADDRESS
Command10=ID_OPTION_WORKARE
Command11=ID_OPTION_FONT
Command12=ID_COMPILE_LAD
Command13=ID_COMPILE_INSTR
Command14=ID_APP_ABOUT
CommandCount=14

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_APP_ABOUT
CommandCount=7

[MNU:IDR_MULTYPE]
Type=1
Class=CMULView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_VIEW_TOOLBAR
Command13=ID_VIEW_STATUS_BAR
Command14=ID_COMPILE_INSTR
Command15=ID_WINDOW_NEW
Command16=ID_WINDOW_CASCADE
Command17=ID_WINDOW_TILE_HORZ
Command18=ID_WINDOW_ARRANGE
Command19=ID_APP_ABOUT
CommandCount=19

[TB:IDR_DRAWTYPE]
Type=1
Class=?
Command1=ID_DRAW_FREE
Command2=ID_DRAW_LD
Command3=ID_DRAW_LDI
Command4=ID_DRAW_OR
Command5=ID_DRAW_ORI
Command6=ID_DRAW_LINE
Command7=ID_DRAW_OUT
Command8=ID_DRAW_ADDITION
Command9=ID_DRAW_ERASE
CommandCount=9

[MNU:IDR_LADDER]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_VIEW_TOOLBAR
Command13=ID_VIEW_STATUS_BAR
Command14=ID_VIEW_LADDER
Command15=ID_VIEW_INSTRU
Command16=ID_VIEW_ADDRESS
Command17=ID_DRAW_LD
Command18=ID_DRAW_LDI
Command19=ID_DRAW_OR
Command20=ID_DRAW_ORI
Command21=ID_DRAW_LINE
Command22=ID_DRAW_OUT
Command23=ID_DRAW_ADDITION
Command24=ID_OPTION_WORKARE
Command25=ID_OPTION_SETADDR
Command26=ID_OPTION_FONT
Command27=ID_COMPILE_LAD
Command28=ID_WINDOW_NEW
Command29=ID_WINDOW_CASCADE
Command30=ID_WINDOW_TILE_HORZ
Command31=ID_WINDOW_ARRANGE
Command32=ID_APP_ABOUT
CommandCount=32

[MNU:IDR_ITEMMENU]
Type=1
Class=?
Command1=ID_SELECT_SET
Command2=ID_SELECT_RST
Command3=ID_SELECT_S
Command4=ID_SELECT_R
Command5=ID_SELECT_MC
Command6=ID_SELECT_MCR
Command7=ID_SELECT_K
Command8=ID_SELECT_F
Command9=ID_SELECT_CJP
Command10=ID_SELECT_EJP
Command11=ID_SELECT_PLS
Command12=ID_SELECT_END
CommandCount=12

[ACL:IDR_ACCELERATOR1]
Type=1
Class=?
Command1=ID_SELECT_SET
Command2=ID_SELECT_RST
Command3=ID_SELECT_S
Command4=ID_SELECT_R
Command5=ID_SELECT_MC
Command6=ID_SELECT_MCR
Command7=ID_SELECT_K
Command8=ID_SELECT_F
Command9=ID_SELECT_CJP
Command10=ID_SELECT_EJP
Command11=ID_SELECT_PLS
Command12=ID_SELECT_END
CommandCount=12

[CLS:CLADDoc]
Type=0
HeaderFile=LADDoc.h
ImplementationFile=LADDoc.cpp
BaseClass=CDocument
Filter=N
VirtualFilter=DC
LastObject=CLADDoc

[CLS:CLADView]
Type=0
HeaderFile=LADView.h
ImplementationFile=LADView.cpp
BaseClass=CScrollView
Filter=C
LastObject=CLADView
VirtualFilter=VWC

[DLG:IDD_POINTSET]
Type=1
Class=CPointSet
ControlCount=8
Control1=IDC_CAPTION,static,1342308866
Control2=IDC_ADDR,edit,1350631560
Control3=IDC_STATIC,static,1342308866
Control4=IDC_NAME,edit,1350631552
Control5=IDC_STATIC,static,1342308354
Control6=IDC_NOTE,edit,1350631552
Control7=IDOK,button,1342242816
Control8=IDCANCEL,button,1342242816

[DLG:IDD_SYNTAX]
Type=1
Class=CSyntax
ControlCount=1
Control1=IDC_COMPILE,edit,1352734852

[DLG:IDD_WORKARESET]
Type=1
Class=CAreSet
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308864
Control4=IDC_WORKARE_WIDTH,edit,1350639744
Control5=IDC_STATIC,static,1342308876
Control6=IDC_WORKARE_HIGH,edit,1350631552
Control7=IDC_PAGEWIDTH,static,1342308864
Control8=IDC_PAGEHIGH,static,1342308864

[CLS:CPointSet]
Type=0
HeaderFile=PointSet.h
ImplementationFile=PointSet.cpp
BaseClass=CDialog
Filter=D
LastObject=CPointSet
VirtualFilter=dWC

[CLS:CSyntax]
Type=0
HeaderFile=Syntax.h
ImplementationFile=Syntax.cpp
BaseClass=CDialog
Filter=D
LastObject=CSyntax
VirtualFilter=dWC

[CLS:CAreSet]
Type=0
HeaderFile=AreSet.h
ImplementationFile=AreSet.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CAreSet

[CLS:CSplashWnd]
Type=0
HeaderFile=Splash.h
ImplementationFile=Splash.cpp
BaseClass=CWnd
LastObject=CSplashWnd

[CLS:COpenComDlg]
Type=0
HeaderFile=OpenComDlg.h
ImplementationFile=OpenComDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_BTN_SETTINGCOM1
VirtualFilter=dWC

[CLS:CSettingComDlg]
Type=0
HeaderFile=SettingComDlg.h
ImplementationFile=SettingComDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_COMBO_BAUD

[CLS:CCommunicationDlg]
Type=0
HeaderFile=CommunicationDlg.h
ImplementationFile=CommunicationDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CCommunicationDlg
VirtualFilter=dWC

[CLS:CCompileDlg]
Type=0
HeaderFile=CompileDlg.h
ImplementationFile=CompileDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CCompileDlg

