// �ĵ��࣬�̳��Զ����CDocument����ShaelDocument.h�У�
#pragma once

#include "ShaelDocument.h"
using namespace Shael;

struct Line
{
	int			nBeginX;
	int			nBeginY;
	int			nEndX;
	int			nEndY;
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
public:
	Line	m_Line;
};
