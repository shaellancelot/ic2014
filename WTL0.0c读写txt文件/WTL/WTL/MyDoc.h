// 文档类，继承自定义的CDocument（在ShaelDocument.h中）
#pragma once

#include "ShaelDocument.h"
using namespace Shael;

struct circle
{
	int			nRadius;
	int			nCentreX;
	int			nCentreY;
	COLORREF	color;
};

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
    bool	Save(const TCHAR* szPathName);
    bool	Load(const TCHAR* szPathName);

// Data access
public:
    void	SetText(const TCHAR* szText);
    const	TCHAR* GetText() const;

// Data
private:
    TCHAR	m_Text[50];
};
