#include "stdafx.h"
#include "ODB.h"
#include "ODBDlg.h"
#include "afxdialogex.h"
#include <sstream>
//#include <pqxx/pqxx>
#include <odb/database.hxx>
#include <odb/pgsql/database.hxx>
#include <odb/connection.hxx>
#include <odb/session.hxx>
#include <odb/transaction.hxx>
#pragma warning (disable:4068)
#include "DbModels.h"
#include "DbModels-odb.hxx"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CODBDlg::CODBDlg(CWnd* pParent)
	: CDialogEx(IDD_ODB_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CODBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CODBDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()

using namespace db;
using namespace odb;
using namespace odb::core;


BOOL CODBDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	pgsql::database db("dbname = test user = postgres password = 123 hostaddr = 127.0.0.1 port = 5433");
	{
		session s;
		transaction t(db.begin());

		t.tracer(stderr_tracer);

		//auto count = db.erase_query<product>();

		//product hdd("HDD");
		//auto id = db.persist(hdd);

		//product ssd("SSD");
		//id = db.persist(ssd);

		//product mouse("Mouse");
		//id = db.persist(mouse);

		//product keyboard("Keyboard");
		//id = db.persist(keyboard);


		/*for (const order& o : db.query<order>())
		{
			auto d = o.date;
		}*/

		//customer c;
		//if (db.query_one(query<customer>::name.like("T%") + "LIMIT 1", c))
		//{
		//	product mouse = db.query_value<product>("name='HDD'");
		//	order o(c, mouse, 80.39);
		//	db.persist(o);
		//}

		//for (const product& p : db.query<product>())
		//{
		//	std::string s = p.name;
		//}

		for (const customer_order& co : db.query<customer_order>())
		{
			std::string name = co.customer_name;
			std::string product = co.product_name;
			double sum = co.sum;
		}

		t.commit();

		
	}

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

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	return TRUE;
}

void CODBDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		//CAboutDlg dlgAbout;
		//dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CODBDlg::OnPaint()
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
HCURSOR CODBDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

