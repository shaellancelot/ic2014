1. ��ʵ�ֹ���
   1.1 ����ֱ�ߡ���Բ
       ����nEditType���û�ͼ���ܣ�
       0��������
       1������ֱ��
       2��������Բ
       3�����ƾ��Σ���ʵ�֣�
   1.2 ���ʺͱ�ˢ������
   1.3 �ĵ��Ļ�������
       ShaelDocument->CDocument->CMyDoc(������CSimpleArray���͵�MyLine��MyEllipse����)
       ShaelDocument->CDocumentClient->WTLView
2. �ѽ������
   2.1 ��Ļ��˸�����http://www.cnblogs.com/greenerycn/archive/2010/09/02/wtl_doublebuffer.html 
   2.2 �޸ı���ɫ���£��ڶ��������ز����٣���
       dc.SetBkColor ( RGB(255,255,255) );
       dc.ExtTextOut ( 0, 0, ETO_OPAQUE, clientRect, "", 0, NULL );  	
3. ���������
   3.1 �ĵ��ļ��غͱ���
   3.2 ���洰�������ʵ�� 
4. ����
   4.1 �Ҽ�ֱ���˳�����
   4.2 ���������״
    BOOL OnSetCursor(CWindow wnd, UINT nHitTest, UINT message)  
    {  
        static CCursor cursor = AtlLoadCursor(IDC_CURSOR1);  //��������Դ��ʮ ����״  
        ::SetCursor(cursor);  
        return TRUE;  
    }
   