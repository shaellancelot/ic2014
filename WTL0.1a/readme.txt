1. 添加了绘图功能
   1.1 绘制直线
   1.2 绘制椭圆（包括圆）
   1.3 调用WM_MOUSEMOVE消息实现动态图
2. 已解决问题
   2.1 屏幕闪烁，详见http://www.cnblogs.com/greenerycn/archive/2010/09/02/wtl_doublebuffer.html 
   2.2 修改背景色如下（第二个函数必不可少），
       dc.SetBkColor ( RGB(255,255,255) );
       dc.ExtTextOut ( 0, 0, ETO_OPAQUE, clientRect, "", 0, NULL );  	
3. 待解决问题
   3.1 文档的管理 
   