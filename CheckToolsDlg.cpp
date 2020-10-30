// CheckToolsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "wbc.h"
#include "CheckToolsDlg.h"
#include "MySqlUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CheckToolsDlg dialog


CheckToolsDlg::CheckToolsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CheckToolsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CheckToolsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CheckToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CheckToolsDlg)
	DDX_Control(pDX, IDC_COMBO3, shimCbxCtr);
	DDX_Control(pDX, IDC_COMBO2, steelMeshCbxCtr);
	DDX_Control(pDX, IDC_COMBO1, scraperCbxCtr);
	DDX_Control(pDX, IDC_EDIT3, shimEditCtr);
	DDX_Control(pDX, IDC_EDIT2, steelMeshEditCtr);
	DDX_Control(pDX, IDC_EDIT1, scraperEditCtr);
	DDX_Control(pDX, STEELMESH_TEXT, steelMeshTextCtr);
	DDX_Control(pDX, SHIM_TEXT, shimTextCtr);
	DDX_Control(pDX, SCRAPER_TEXT, scraperTextCtr);
	DDX_Control(pDX, CHECK_TOOLS_DLG_WS, waferSourceCtr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CheckToolsDlg, CDialog)
	//{{AFX_MSG_MAP(CheckToolsDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CheckToolsDlg message handlers

//��ʼ������
BOOL CheckToolsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	//��ʼ����ǰwaferSource
	waferSourceCtr.SetWindowText(waferSource);
	selectToolsInfo();
	initAppearanceCheckSelects();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//��дonOk
void CheckToolsDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//��Ӧ�ε�ɨ���ά���¼�
	if(GetDlgItem(IDC_EDIT1)==GetFocus())
	{
		onScanScraper();
		return;
	}

	//��Ӧ����ɨ���ά���¼�
	if(GetDlgItem(IDC_EDIT2)==GetFocus())
	{
		onScanSteelMesh();
		return;
	}

	//��Ӧ��Ƭɨ���ά���¼�
	if(GetDlgItem(IDC_EDIT3)==GetFocus())
	{
		onScanShim();
		return;
	}
}

//��ѯ���й�����Ϣ����䵽3����̬�ı��ؼ�
void CheckToolsDlg::selectToolsInfo(){

	try
	{
		CString msg;
		MySqlUtil mysqlUtil(msg);
		CString sql;
		sql.Format("SELECT description,sn from wbc20_wafer_tool_relation,wbc20_tool WHERE tool_id=wbc20_tool.id AND wafer_source='%s' ORDER BY type",waferSource);
		CStringArray array;
		mysqlUtil.SelectData(sql,msg,array);
		//���ùε���Ϣ
		scraperTextCtr.SetWindowText(array.GetAt(0));
		expectedScraper=array.GetAt(1);
		//���ø�����Ϣ
		steelMeshTextCtr.SetWindowText(array.GetAt(2));
		expectedSteelMesh=array.GetAt(3);
		//���õ�Ƭ��Ϣ
		shimTextCtr.SetWindowText(array.GetAt(4));
		expectedShim=array.GetAt(5);
	}
	catch (const char * info)
	{
		MessageBox(info);
	}

}

//��Ӧ�ε�ɨ���ά��
void CheckToolsDlg::onScanScraper(){
	CString currentScraper;
	scraperEditCtr.GetWindowText(currentScraper);
	if (currentScraper!=expectedScraper)
	{
		MessageBox("ƥ��ε�ʧ��!");
	}else{
		scraperCheck=true;
		scraperCbxCtr.EnableWindow(true);
	}
	scraperEditCtr.SetWindowText("");
}

//��Ӧ����ɨ���ά��
void CheckToolsDlg::onScanSteelMesh(){
	CString currentSteelMesh;
	steelMeshEditCtr.GetWindowText(currentSteelMesh);
	if (currentSteelMesh!=expectedSteelMesh)
	{
		MessageBox("ƥ�����ʧ��!");
	}else{
		steelMeshCheck=true;
	}
	steelMeshEditCtr.SetWindowText("");
}


//��Ӧ��Ƭɨ���ά��
void CheckToolsDlg::onScanShim(){
	CString currentShim;
	shimEditCtr.GetWindowText(currentShim);
	if (currentShim!=expectedShim)
	{
		MessageBox("ƥ���Ƭʧ��!");
	}else{
		shimCheck=true;
	}
	shimEditCtr.SetWindowText("");
}

//��ʼ���������״̬������
void CheckToolsDlg::initAppearanceCheckSelects(){
	scraperCbxCtr.AddString(TEXT("OK"));
	scraperCbxCtr.AddString(TEXT("NG"));
	steelMeshCbxCtr.AddString(TEXT("OK"));
	steelMeshCbxCtr.AddString(TEXT("NG"));
	shimCbxCtr.AddString(TEXT("OK"));
	shimCbxCtr.AddString(TEXT("NG"));
	scraperCbxCtr.EnableWindow(false);
	steelMeshCbxCtr.EnableWindow(false);
	shimCbxCtr.EnableWindow(false);
}
