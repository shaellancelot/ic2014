1. 已实现功能
   1.1 绘制直线、椭圆。
       根据nEditType设置绘图功能：
       0：鼠标操作
       1：绘制直线
       2：绘制椭圆
       3：绘制矩形（待实现）
   1.2 画笔和笔刷的配置。
   1.3 文档的基本机制。
       ShaelDocument->CDocument->CMyDoc(定义了CSimpleArray类型的MyLine和MyEllipse数组)
       ShaelDocument->CDocumentClient->WTLView
   1.4 存储当前画面为图片，位置为"d:\B.jpg"。
	HDC hDC = ::GetDC( m_hWnd );									//获取DC 
        HDC hDCMem = ::CreateCompatibleDC( hDC );							//创建兼容DC      
	HBITMAP hBitMap = ::CreateCompatibleBitmap( hDC, clientRect.Width(), clientRect.Height() );	//创建兼容位图      
	HBITMAP hOldMap = (HBITMAP)::SelectObject( hDCMem, hBitMap );					//将位图选入DC，并保存返回值        
        ::BitBlt( hDCMem, 0, 0, clientRect.Width(), clientRect.Height(), hDC, 0, 0, SRCCOPY );		//将屏幕DC的图象复制到内存DC中      
        CImage image;     
        image.Attach( hBitMap );     
        image.Save( _T("d:\B.jpg") );    
        image.Detach();  
        // 选入上次的返回值  
	::SelectObject( hDCMem, hOldMap );       
        //释放      
        ::DeleteObject(hBitMap);     
        ::DeleteDC(hDCMem);     
        ::DeleteDC(hDC);  


2. 已解决问题
   2.1 屏幕闪烁。详见http://www.cnblogs.com/greenerycn/archive/2010/09/02/wtl_doublebuffer.html 
   2.2 修改背景色如下（第二个函数必不可少）。
       dc.SetBkColor ( RGB(255,255,255) );
       dc.ExtTextOut ( 0, 0, ETO_OPAQUE, clientRect, "", 0, NULL );  

	
3. 待解决问题
   3.1 文档的加载和保存，自定义一种工程文件。
   3.2 自定义工具栏和菜单栏 。
   3.3 分割窗口。
   3.4 反馈音效。
   3.5 生成线路代码。
   3.6 对准矫正功能。
   3.7 设置鼠标形状。
        BOOL OnSetCursor(CWindow wnd, UINT nHitTest, UINT message)  
        {  
            static CCursor cursor = AtlLoadCursor(IDC_CURSOR1);  //载入光标资源：十字形状  
            ::SetCursor(cursor);  
            return TRUE;  
        }


4. 其他
   4.1 右键直接退出程序。

   