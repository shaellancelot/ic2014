1. ��ʵ�ֹ���
   1.1 ����ֱ�ߡ���Բ��
       ����nEditType���û�ͼ���ܣ�
       0��������
       1������ֱ��
       2��������Բ
       3�����ƾ��Σ���ʵ�֣�
   1.2 ���ʺͱ�ˢ�����á�
   1.3 �ĵ��Ļ������ơ�
       ShaelDocument->CDocument->CMyDoc(������CSimpleArray���͵�MyLine��MyEllipse����)
       ShaelDocument->CDocumentClient->WTLView
   1.4 �洢��ǰ����ΪͼƬ��λ��Ϊ"d:\B.jpg"��
	HDC hDC = ::GetDC( m_hWnd );									//��ȡDC 
        HDC hDCMem = ::CreateCompatibleDC( hDC );							//��������DC      
	HBITMAP hBitMap = ::CreateCompatibleBitmap( hDC, clientRect.Width(), clientRect.Height() );	//��������λͼ      
	HBITMAP hOldMap = (HBITMAP)::SelectObject( hDCMem, hBitMap );					//��λͼѡ��DC�������淵��ֵ        
        ::BitBlt( hDCMem, 0, 0, clientRect.Width(), clientRect.Height(), hDC, 0, 0, SRCCOPY );		//����ĻDC��ͼ���Ƶ��ڴ�DC��      
        CImage image;     
        image.Attach( hBitMap );     
        image.Save( _T("d:\B.jpg") );    
        image.Detach();  
        // ѡ���ϴεķ���ֵ  
	::SelectObject( hDCMem, hOldMap );       
        //�ͷ�      
        ::DeleteObject(hBitMap);     
        ::DeleteDC(hDCMem);     
        ::DeleteDC(hDC);  


2. �ѽ������
   2.1 ��Ļ��˸�����http://www.cnblogs.com/greenerycn/archive/2010/09/02/wtl_doublebuffer.html 
   2.2 �޸ı���ɫ���£��ڶ��������ز����٣���
       dc.SetBkColor ( RGB(255,255,255) );
       dc.ExtTextOut ( 0, 0, ETO_OPAQUE, clientRect, "", 0, NULL );  

	
3. ���������
   3.1 �ĵ��ļ��غͱ��棬�Զ���һ�ֹ����ļ���
   3.2 �Զ��幤�����Ͳ˵��� ��
   3.3 �ָ�ڡ�
   3.4 ������Ч��
   3.5 ������·���롣
   3.6 ��׼�������ܡ�
   3.7 ���������״��
        BOOL OnSetCursor(CWindow wnd, UINT nHitTest, UINT message)  
        {  
            static CCursor cursor = AtlLoadCursor(IDC_CURSOR1);  //��������Դ��ʮ����״  
            ::SetCursor(cursor);  
            return TRUE;  
        }


4. ����
   4.1 �Ҽ�ֱ���˳�����

   