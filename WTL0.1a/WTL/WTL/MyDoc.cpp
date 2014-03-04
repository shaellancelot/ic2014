#include "StdAfx.h"
#include "MyDoc.h"

#include <fstream>

/*
IMPLEMENT_DYNCREATE(CMyDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyDoc, CDocument)
	// 在此处添加消息
END_MESSAGE_MAP()
*/

CMyDoc::CMyDoc(void)
{
	*m_Text = '\0';
}

CMyDoc::~CMyDoc(void)
{
}

//
// Data access
//
void CMyDoc::SetText( const TCHAR* szText )
{
    strcpy( m_Text, szText );
    SetModifiedFlag();  // Set after change to allow doc clients who
                        // know about this document to fetch the new
                        // data.
}

const TCHAR* CMyDoc::GetText() const
{
    return m_Text;
}

//
// Overrides
//
void CMyDoc::DeleteContents()
{
    *m_Text = '\0';
    CDocument::DeleteContents();
}

const TCHAR* CMyDoc::GetFilterString() const
{
    static const TCHAR szDocumentFilter[] = _T("Text Files (*.txt)\0*.txt\0All Files\0*.*\0");
    return szDocumentFilter;
}

const TCHAR* CMyDoc::GetDefaultExtension() const
{
    static const TCHAR szDefaultExtension[] = _T("txt");
    return szDefaultExtension;
}

bool CMyDoc::Save(const TCHAR* szPathName)
{
    std::ofstream save;
    save.open(szPathName);
    if (!save.is_open())
    {
        return false;
    }

    save << m_Text;

    save.close();
    return CDocument::Save(szPathName);
}

bool CMyDoc::Load(const TCHAR* szPathName)
{
    std::ifstream load;
    load.open(szPathName);
    if (!load.is_open())
    {
        return false;
    }

    DeleteContents();   // Lets assume all will be well

    memset(m_Text, 0, sizeof(m_Text));
    load.read(m_Text, sizeof(m_Text));

    load.close();
    return CDocument::Load(szPathName);
}


//////////////////////////////////////////////////////////////////////////////
// diagnostics(诊断消息)
#ifdef _DEBUG
/*
void CMyDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
*/
#endif //_DEBUG
//////////////////////////////////////////////////////////////////////////////