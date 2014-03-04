1. 已实现功能
   1.1 绘制直线、椭圆
       根据nEditType设置绘图功能：
       0：鼠标操作
       1：绘制直线
       2：绘制椭圆
       3：绘制矩形（待实现）
   1.2 画笔和笔刷的配置
   1.3 文档的基本机制
       ShaelDocument->CDocument->CMyDoc(定义了CSimpleArray类型的MyLine和MyEllipse数组)
       ShaelDocument->CDocumentClient->WTLView
2. 已解决问题
   2.1 屏幕闪烁，详见http://www.cnblogs.com/greenerycn/archive/2010/09/02/wtl_doublebuffer.html 
   2.2 修改背景色如下（第二个函数必不可少），
       dc.SetBkColor ( RGB(255,255,255) );
       dc.ExtTextOut ( 0, 0, ETO_OPAQUE, clientRect, "", 0, NULL );  	
3. 待解决问题
   3.1 文档的加载和保存
   3.2 界面窗口设计与实现 
4. 其他
   4.1 右键直接退出程序
   4.2 设置鼠标形状
    BOOL OnSetCursor(CWindow wnd, UINT nHitTest, UINT message)  
    {  
        static CCursor cursor = AtlLoadCursor(IDC_CURSOR1);  //载入光标资源：十 字形状  
        ::SetCursor(cursor);  
        return TRUE;  
    }
   