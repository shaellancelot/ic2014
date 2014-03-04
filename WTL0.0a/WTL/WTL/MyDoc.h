#pragma once

struct circle
{
	int			nRadius;
	int			nCentreX;
	int			nCentreY;
	COLORREF	color;
};

class CMyDoc : public CDocument
{
protected:
	CMyDoc(void);
	DECLARE_DYNCREATE(CMyDoc)
	DECLARE_MESSAGE_MAP()
public:
	virtual ~CMyDoc(void);
	
	// ���ؿ⺯��
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

	// ����
	struct	circle ACircle[200];
	int		NcircleNum;
	BOOL	m_bLButtonDown;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};
