# newDesktop

将窗口嵌入桌面

## 获取要嵌入窗口的句柄
``` c++
//main.cpp
HWND wallpaperHwnd = FindWindow(_T("WMP Skin Host"), _T("Windows Media Player"));
//or
HWND wallpaperHwnd = (HWND)0x002F1B1E;
```
可以使用spy++来获取句柄填进去测试
    
目前我实验的主要对象为firefox浏览器。谷歌浏览器的窗口实现比较奇葩，不建议使用。
