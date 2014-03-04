#include "StdAfx.h"
#include "MyDoc.h"

#include <fstream>

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
    SetModifiedFlag();  
}

const TCHAR* CMyDoc::GetText() const
{
    return m_Text;
}

void CMyDoc::SetLine( WTL::CPoint a, WTL::CPoint b )
{
	MyLine line;
	line.startPoint = a;
	line.endPoint = b;
	m_Line.Add( line );
    SetModifiedFlag();  
}

const CSimpleArray<MyLine>* CMyDoc::GetLine() const
{
	return &m_Line;
}

void CMyDoc::SetEllipse( int left, int top, int right, int bottom )
{
	MyEllipse ellipse;
	ellipse.left = left;
	ellipse.top = top;
	ellipse.right = right;
	ellipse.bottom = bottom;
	m_Ellipse.Add( ellipse );
    SetModifiedFlag();  
}

const CSimpleArray<MyEllipse>* CMyDoc::GetEllipse() const
{
	return &m_Ellipse;
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
    save.open( szPathName );
    if( !save.is_open() )
    {
        return false;
    }
	

    save << m_Text;

    save.close();
    return CDocument::Save( szPathName );
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

