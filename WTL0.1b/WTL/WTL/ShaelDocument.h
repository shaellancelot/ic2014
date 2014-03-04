

#pragma once
#ifndef WTL_DOCUMENT_H_
#define WTL_DOCUMENT_H_

namespace Shael
{

class CDocumentClient;
const TCHAR szUntitledDocument[] = _T("Untitled");
//
// Document
//
class CDocument
{
public:
    // ctor
    CDocument()
    {
        *m_szName = '\0';
		m_bIsModified = false;
    }

    virtual ~CDocument()
    {
        OnDeleted();    // Call first to allow last chance at data
    }

// Overrides
public:
    virtual void DeleteContents();
    virtual const TCHAR* GetFilterString() const;
    virtual const TCHAR* GetDefaultExtension() const;

// Serialize
public:
    virtual bool Save( const TCHAR* szName );
    virtual bool Load( const TCHAR* szName );

// File operations
public:
    virtual bool OnNew();
    virtual bool OnOpen( bool& bFailed );
    virtual bool OnSave( bool& bFailed );
    virtual bool OnSaveAs( bool& bFailed );

// Notifications
public:
    virtual void OnModified() const;
    virtual void OnDeleted() const;
    virtual void OnClientAdded( CDocumentClient* pClient ) const;
    virtual void OnClientRemoved( CDocumentClient* pClient ) const;
    virtual void OnSZNameChanged() const;

// 数据（变量）操作
public:
	// 用户对象操作：m_Clients
    bool AddClient( CDocumentClient* pClient );
    bool RemoveClient( CDocumentClient* pClient );
    int  GetClientCount() const;
    const CSimpleArray<CDocumentClient*>& GetClients() const;						// 获取用户对象
    // 文件修改记录操作：m_bIsModified
    bool IsModified() const;														// 获取文件修改记录								
    void SetModifiedFlag(bool bIsModified = true, bool bNotifyModified = true);		// 设置文件修改记录	
	// 文件路径操作：m_szName
    const TCHAR* GetSZName() const;													// 获取文件路径
    virtual void SetSZName(const TCHAR* szName);									// 设置文件路径

// 变量
private:
    CSimpleArray<CDocumentClient*>	m_Clients;						// 保存用户对象
    bool							m_bIsModified;					// 记录是否被修改过
    TCHAR							m_szName[MAX_PATH+1];			// 文件位置
};

//
// Document client
//
class CDocumentClient
{
public:
    // ctor
    CDocumentClient()
    {
		m_pDoc = NULL;
    }

    virtual ~CDocumentClient()
    {
#ifdef _DEBUG
        // Try to avoid data loss in applications by notifying
        // of the possibility in debug builds. 
        if (IsDocumentVolatile())
        {
            ATLTRACE(_T("WARNING: Possible undesired data loss occured.\n"));
        }
#endif

        bool bSuccess = DetachDocument();
        _ASSERTE( bSuccess );
    }

// Utilities
public:
    CDocument* GetDocument() const;					// 获取m_pDoc
    bool AttachDocument( CDocument* pDoc );			// 对m_pDoc赋值，并将本对象添加到m_Clients中
    bool DetachDocument();							// 将本用户从m_Clients中移除，并重置m_pDoc

// Overrides
public:
    virtual bool IsDocumentVolatile() const;
    virtual bool IsDocumentSave( const HWND hWnd = NULL, const TCHAR* szCaption = NULL ) const;

// Notifications from the document
    virtual void OnDocumentModified();
    virtual void OnDocumentDeleted();
    virtual void OnDocumentClientAdded( CDocumentClient* pClient );
    virtual void OnDocumentClientRemoved( CDocumentClient* pClient );
    virtual void OnDocumentSZNameChanged( const TCHAR* szName );

// 变量
private:
    CDocument*  m_pDoc;					// 一个用户对应一个文件
};

//
// CDocument inlines
//
inline void CDocument::OnModified() const
{
    for( int i = 0; i < m_Clients.GetSize(); ++i )
    {
        CDocumentClient* pClient = m_Clients[i];
        _ASSERTE( pClient != NULL );
        pClient->OnDocumentModified();
    }
}

inline void CDocument::OnDeleted() const
{
    for( int i = 0; i < m_Clients.GetSize(); ++i )
    {
        CDocumentClient* pClient = m_Clients[i];
        _ASSERTE( pClient != NULL );
        pClient->OnDocumentDeleted();
    }
}

inline void CDocument::OnClientAdded( CDocumentClient* pClient ) const
{
    for( int i = 0; i < m_Clients.GetSize(); ++i )
    {
        CDocumentClient* pDocClient = m_Clients[i];
        _ASSERTE( pDocClient != NULL );
        pDocClient->OnDocumentClientAdded( pClient );
    }
}

inline void CDocument::OnClientRemoved( CDocumentClient* pClient ) const
{
    for( int i = 0; i < m_Clients.GetSize(); ++i )
    {
        CDocumentClient* pDocClient = m_Clients[i];
        _ASSERTE( pDocClient != NULL );
        pDocClient->OnDocumentClientRemoved(pClient);
    }
}

inline void CDocument::OnSZNameChanged() const
{
    for( int i = 0; i < m_Clients.GetSize(); ++i )
    {
        CDocumentClient* pDocClient = m_Clients[i];
        _ASSERTE(pDocClient != NULL);
        pDocClient->OnDocumentSZNameChanged( m_szName );
    }
}

inline bool CDocument::AddClient( CDocumentClient* pClient )
{
    _ASSERTE( pClient != NULL );
    bool bSuccess = m_Clients.Add( pClient );
    if ( bSuccess )
    {
        OnClientAdded( pClient );
    }
    return bSuccess;
}

inline bool CDocument::RemoveClient( CDocumentClient* pClient )
{
    _ASSERTE( pClient != NULL );
    bool bSuccess = m_Clients.Remove( pClient );
    if( bSuccess )
    {
        OnClientRemoved( pClient );
    }
    return bSuccess;
}

inline int CDocument::GetClientCount() const
{
    return m_Clients.GetSize();
}

inline const CSimpleArray<CDocumentClient*>& CDocument::GetClients() const
{
    return m_Clients;
}

inline bool CDocument::IsModified() const
{
    return m_bIsModified;
}

inline void CDocument::SetModifiedFlag( bool bIsModified, bool bNotifyModified ) 
{
    m_bIsModified = bIsModified;
    if( bNotifyModified )
    {
        OnModified();
    }
}

inline const TCHAR* CDocument::GetSZName() const
{
    if( *m_szName == '\0' )
    {
        return szUntitledDocument;
    }
    return m_szName;
}

inline void CDocument::SetSZName(const TCHAR* szName)
{
    _ASSERTE(szName != NULL);
    _tcscpy(m_szName, szName);

    OnSZNameChanged();
}

inline void CDocument::DeleteContents()
{
    SetModifiedFlag( false );
}

inline bool CDocument::OnNew()
{
    DeleteContents();
    *m_szName = '\0';
    return true;
}

inline bool CDocument::OnOpen( bool& bFailed )
{
    bFailed = false;
    CFileDialog dlg( TRUE, GetDefaultExtension() );
    if( dlg.DoModal() == IDOK )
    {
        if( Load(dlg.m_szFileName) )
        {
            SetSZName( dlg.m_szFileName );
            return true;
        }else{
            bFailed = true;
        }
    }
    return false;
}

inline bool CDocument::OnSave( bool& bFailed )
{
    bFailed = false;
	// 查看m_szName是否为空或者"Untitled"
    if( *m_szName == '\0' || _tcscmp(m_szName, szUntitledDocument) == 0 )
    {
        return OnSaveAs( bFailed );
    }
    // No need to save if it is not dirty
    if( !IsModified() )
    {
        return true;
    }
    bool bSaved = Save( m_szName );
    if ( !bSaved )
    {
        bFailed = true;
    }
    return bSaved;
}

inline bool CDocument::OnSaveAs( bool& bFailed )
{
    bFailed = false;
    const TCHAR* szInitialFile;
    szInitialFile = (*m_szName != '\0') ? m_szName : szUntitledDocument;
	CFileDialog dlg(FALSE,GetDefaultExtension());
    
    if( dlg.DoModal() == IDOK )
    {
        if( Save(dlg.m_szFileName) )
        {
            SetSZName( dlg.m_szFileName );
            return true;
        }else{
            bFailed = true;
        }
    }
    return false;
}

inline bool CDocument::Save( const TCHAR* szName )
{
    SetModifiedFlag( false, false );
    return true;
}

inline bool CDocument::Load(const TCHAR* szName)
{
    SetModifiedFlag( false );
    return true;
}

inline const TCHAR* CDocument::GetFilterString() const
{
    static const TCHAR szDocumentFilter[] = _T("All Files\0*.*\0");
    return szDocumentFilter;
}

inline const TCHAR* CDocument::GetDefaultExtension() const
{
    return NULL;
}

//
// CDocumentClient inlines
//
inline CDocument* CDocumentClient::GetDocument() const
{
    _ASSERTE(m_pDoc != NULL);
    return m_pDoc;
}

inline bool CDocumentClient::AttachDocument( CDocument* pDoc )
{
    _ASSERTE( pDoc != NULL );
    m_pDoc = pDoc;
    return m_pDoc->AddClient( this );
}

inline bool CDocumentClient::DetachDocument()
{
    bool bSuccess = true;
    if ( m_pDoc != NULL )
    {
        bSuccess = m_pDoc->RemoveClient(this);
    }
    m_pDoc = NULL;
    return bSuccess;
}

inline void CDocumentClient::OnDocumentModified()
{
}

inline void CDocumentClient::OnDocumentDeleted()
{
#ifdef _DEBUG
    // Try to avoid data loss in applications by notifying
    // of the possibility in debug builds. 
    if (IsDocumentVolatile())
    {
        ATLTRACE(_T("WARNING: Possible undesired data loss occured.\n"));
    }
#endif

    DetachDocument();
}

inline void CDocumentClient::OnDocumentClientAdded(CDocumentClient* pClient)
{
}

inline void CDocumentClient::OnDocumentClientRemoved(CDocumentClient* pClient)
{
}

inline void CDocumentClient::OnDocumentSZNameChanged( const TCHAR* szName )
{
}

inline bool CDocumentClient::IsDocumentVolatile() const
{
    if( m_pDoc != NULL && m_pDoc->IsModified() && m_pDoc->GetClientCount() == 1 )
    {
        _ASSERTE( m_pDoc->GetClients()[0] == this );
        return true;
    }

    return false;
}

inline bool CDocumentClient::IsDocumentSave( const HWND hWnd, const TCHAR* szCaption ) const
{
    if( IsDocumentVolatile() )
    {
        TCHAR szText[256];
        const TCHAR* szName = GetDocument()->GetSZName();
        wsprintf( szText, _T("Save changes to %s?"), szName );
        int bRet = MessageBox( hWnd, szText, szCaption, MB_YESNOCANCEL | MB_ICONEXCLAMATION );
        if( bRet == IDYES )
        {
            bool bFailed;
            if( !m_pDoc->OnSave(bFailed) )
            {
                return false; 
            }
        }else if( bRet == IDNO ){
            // just pass through
        }else if ( bRet == IDCANCEL ){
            return false;
        }else
        {
            _ASSERTE(0);
        }
    }
    return true;
}

}; //namespace

#endif  
