# Project-Judger
这是一个用于信息学竞赛的小型评测工具。

构建的二进制文件在Binary\Release\Judger.exe。

下载后请自行按照个人配置修改源代码。（使用CodeBlocks环境）

默认输出为64位。

主程序main.cpp，头文件auto.hpp/compile.hpp/execute.hpp/functions.hpp，图标MainIcon.ico，链接库libpsapi.a(即为psapi.lib)

使用方法同Lemon评测机差不多。

评测时默认使用TDM-GCC，路径D:\TDM-GCC\bin\g++.exe，请自行修改。

main()的参数列表：
argv[1]工作目录，argv[2]配置文件，argv[3]待评测的源程序，argv[4]输出文件，argv[5]题目名称。

