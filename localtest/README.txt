一、LogLib VS2017工程文件夹 需c++控制台应用以及MFC支持
LogLib.exe 从LogLib提取出的 生成data.txt
main.py 读取并删除data.txt HTTP POST至远程服务器

二、VS2017工程设置： 配置属性-常规-项目默认值-MFC的使用：在共享DLL中使用MFC
配置属性-C/C++-预编译头：不使用预编译头
配置属性-常规-项目默认值-字符集：未设置     ，注：c++字符太混乱，这里我关了

编译出现_WIN32_WINNT not defined. Defaulting to _WIN32_WINNT_MAXVER (see WinSDKVer.h) 不要紧
此为限制程序/工程对windows平台版本的要求？ 我没改


c++中 LogLib.cpp为程序入口
TaskInfo.cpp/h提供MFC获取应用程序的TaskInfo类
Log.cpp/h提供Log日志类

三、c++生成的data.txt格式：
每个时间点以==============\n开头
每组数据有7行，详情：例子请查看data.txt，在\web_project\localtest\LogLib\LogLib中
ClassName:ConsoleWindowClass
WindowText:D:\PC_git_library\web_project\localtest\LogLib\x64\Debug\LogLib.exe
ProcessName:VsDebugConsole.exe
type:common                                               //topWindow or common
StartTime:Sun Mar 31 05:40:11 2019          // is a timestr
RunningTime:Thu Jan  1 00:00:00 1970      //PresentTime-StartTime,我错误地暂时保存成timestr了this is bug, need fix 
PresentTime:Sun Mar 31 05:40:11 2019     // is a timestr