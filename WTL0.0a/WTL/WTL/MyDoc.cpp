#include "StdAfx.h"
#include "MyDoc.h"


IMPLEMENT_DYNCREATE(CMyDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyDoc, CDocument)
	// �ڴ˴������Ϣ
END_MESSAGE_MAP()

CMyDoc::CMyDoc(void)
{
	NcircleNum = 0;
	m_bLButtonDown = FALSE;
}

CMyDoc::~CMyDoc(void)
{
}

BOOL CMyDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

void CMyDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

//////////////////////////////////////////////////////////////////////////////
// diagnostics(�����Ϣ)
#ifdef _DEBUG
void CMyDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG
//////////////////////////////////////////////////////////////////////////////