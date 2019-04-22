# Project-Judger
这是一个用于信息学竞赛的小型评测工具。

构建的二进制文件在Binary\Release\Judger.exe。

**下载后请自行按照个人配置修改源代码。（使用CodeBlocks环境）**

**其中example.zip是一个评测示例。**

默认输出为64位。

主程序main.cpp，头文件auto.hpp/compile.hpp/execute.hpp/functions.hpp，图标MainIcon.ico，链接库libpsapi.a(即为psapi.lib)

使用方法同Lemon评测机差不多。

评测时**默认使用TDM-GCC，路径D:\TDM-GCC\bin\g++.exe，请自行修改。**

main()的参数列表：
argv[1]工作目录，argv[2]配置文件，argv[3]待评测的源程序，argv[4]输出文件，argv[5]题目名称。

配置文件(argv[2])书写格式：包含若干行，每行两个整数(%d %d)，表示时间限制(ms)和空间限制(KB)。
**有多少个测试点就写多少行。**
每次评测一道题目、一个程序。

输出文件/评测结果(argv[4])包含若干行，每行开头有一个字符串表示评测状态(AC/WA/TLE/MLE/CE/OLE/UKE/RE)，如果是AC，后面还会有两个量，分别表示用时(ms)和内存使用量(KB)。

待评测的程序需要加文件读入输出。输入文件名为**题目名称+".in"**，输出文件名为**题目名称+".out"**。

测试数据应放在工作目录(argv[1])中。 **不得包含多余文件夹。** 输入、输出文件名应分别以.in/.out结尾，并在文件名中包含一些数字。例如，程序默认test1.in与test1.out对应为一组输入输出。无法识别如test(没有扩展名)或test.ans(扩展名错误)等。若输入与输出自动匹配失败，评测将出现异常。

**在匹配数据之后，评测机会按照文件名中的数字进行排序，而不是按照字典序。** 如，有test1.in,test2.in,test10.in，排序后应为test1.in,test2.in,test10.in，**而不是test1.in,test10.in,test2.in**。

**全程静默评测，正常运行时只会弹出一个控制台窗口，不会显示内容，并会自行关闭。** 请使用cmd脚本或进程创建函数来调用，**直接点击将会由于缺少运行参数而自动关闭。**

compile.hpp中的compile函数，即调用编译器对**待评测程序**进行编译。默认编译时限10s。有三个参数：s为编译器文件名（完整），dir为编译器**路径**，cmd为编译参数。如s="D:\TDM-GCC\bin\g++.exe"，dir="D:\TDM-GCC\bin"，cmd=" test.cpp -o test.exe -lm"。您也可以调用别的编译器，以支持其他语言。

execute.hpp中的execute函数，即在评测时运行**待评测程序**。若待评测程序运行超过时间限制，**待评测程序**将立即被强制关闭。

**其中example.zip是一个评测示例。**

**该程序遵守GPL v3.0条约。**

允许对程序进行修改、编译、复制等，**禁止用于商业用途。**

**更新于2019.3.31**
