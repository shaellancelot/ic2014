// 文档类，继承自定义的CDocument（在ShaelDocument.h中）
#pragma once

#include "ShaelDocument.h"
#include "MyStruct.h"
using namespace Shael;

class CMyDoc : public CDocument
{
public:
	CMyDoc(void);
	virtual ~CMyDoc(void);

// Overrides
public:
    void	DeleteContents();
    const	TCHAR* GetFilterString() const;
    const	TCHAR* GetDefaultExtension() const;

// Serialize
public:
    bool	Save( const TCHAR* szPathName );
    bool	Load( const TCHAR* szPathName );

// Data access
public:
    void	SetText(const TCHAR* szText);
	const	TCHAR*	GetText() const;
	void	SetLine( CPoint a, CPoint b );
	const	CSimpleArray<MyLine>* GetLine() const;
	void	SetEllipse( int left, int top, int right, int bottom );
	const	CSimpleArray<MyEllipse>* GetEllipse() const;

// Data
private:
    TCHAR	m_Text[50];
	CSimpleArray<MyLine>		m_Line;
	CSimpleArray<MyEllipse>		m_Ellipse;
};
