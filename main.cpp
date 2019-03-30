// (C)2019 Bits.

//主程序

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <vector>

#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <io.h>

#include "execute.hpp"
#include "compile.hpp"
#include "auto.hpp"
#include "functions.hpp"

using namespace std;

vector<result> res;
vector<limit> lit;

bool StdStrCmp(string x, string y){
    if(x.length() != y.length())
        return x.length() < y.length();
    return x < y;
}

bool judge(string content, string code, string exam){
    // content: 测试数据目录
    // code: 源代码文件名
    // exam: 题目名
    vector<string> input, output;
    res.clear();
    input.clear();
    output.clear();
    string *a, *b, enter = "\n";
    a = new string[100000];
    b = new string[100000];
    if(a ==  NULL || b == NULL){
        delete[] a;
        delete[] b;
        return 1;
    }
    getdata(content, input, ".in");
    getdata(content, output, ".out");
    sort(input.begin(), input.end(), StdStrCmp);
    sort(output.begin(), output.end(), StdStrCmp);
    int rtval, total = lit.size();
    rtval = system("md E:\\check");
    if(rtval)
        return 1;
    rtval = compile("D:\\TDM-GCC\\bin\\g++.exe", "D:\\TDM-GCC\\bin",
                    " -o E:\\check\\test.exe " + code + " -lm");
    if(rtval){
        for(int i = 0; i < total; i++)
            res.push_back((result){-1, 0, 0});
        system("rd /s /q E:\\check");
        return 0;
    }
    for(int i = 0; i < total; i++){
        copyf(input[i], "E:\\check\\" + exam + ".in");
        res.push_back(execute("E:\\check\\test.exe", "E:\\check", lit[i]));
        if(res[i].flag == -2){
            ifstream finx(("E:\\check\\" + exam + ".out").c_str());
            ifstream finy(output[i].c_str());
            int x=0, y=0;
            while(x < 100000 && getline(finx, a[x]))
                x++;
            while(y < 100000 && getline(finy, b[y]))
                y++;
            finx.close();
            finy.close();
            if(x == 100000 || y == 100000)
                res[i].flag = 4;
            else{
                x--, y--;
                if(x > 0){
                    while((a[x] == enter || a[x].size() == 0) && x > 0)
                        x--;
                }
                if(y > 0){
                    while((b[y] == enter || b[y].size() == 0) && y > 0)
                        y--;
                }
                if(x != y)
                    res[i].flag = 1;
                else{
                    bool p = true;
                    for(int j = 0; j < x; j++){
                        if(!StrComp(a[j], b[j])){
                            p = false;
                            break;
                        }
                    }
                    if(p)
                        res[i].flag = 0;
                    else
                        res[i].flag = 1;
                }
            }
        }
        remove(("E:\\check\\" + exam + ".in").c_str());
        remove(("E:\\check\\" + exam + ".out").c_str());
    }
    delete[] a;
    delete[] b;
    input.clear();
    output.clear();
    getdata("E:\\check", output, "");
    rtval = output.size();
    for(int i = 0; i < rtval; i++)
        remove(output[i].c_str());
    while(checkfolder("E:\\check")){
        system("rd /s /q E:\\check");
        Sleep(50);
    }
    output.clear();
    return 0;
}

/*
argv[1]: 数据文件夹
argv[2]: 配置文件
argv[3]: 代码文件
argv[4]: 导出文件
argv[5]: 题目名称
*/
int main(int argc, char *argv[]){
    if(argc != 6)
        return 1;
    string content = argv[1], config = argv[2],
           source = argv[3], output = argv[4], exam = argv[5];
    int errors = !checkfolder(content) + !checkfile(config);
    if(errors)
        return errors;
    ifstream fin(config.c_str());
    int x, y;
    while(fin >> x >> y)
        lit.push_back((limit){x, y});
    fin.close();
    if(!lit.size())
        return 1;
    int rtval = judge(content, source, exam);
    ofstream fout(output.c_str());
    x = res.size();
    for(int i = 0; i < x; i++){
        switch(res[i].flag){
            case -1:{
                fout << "CE";
                break;
            }
            case 0:{
                fout << "AC " << res[i].utime << ' ' << res[i].umemory;
                break;
            }
            case 1:{
                fout << "WA";
                break;
            }
            case 2:{
                fout << "TLE";
                break;
            }
            case 3:{
                fout << "MLE";
                break;
            }
            case 4:{
                fout << "OLE";
                break;
            }
            case 5:{
                fout << "RE";
                break;
            }
            case 6:{
                fout << "UKE";
                break;
            }
            default:{
                return 1;
                break;
            }
        }
        fout << endl;
    }
    fout.close();
    lit.clear();
    res.clear();
    _fcloseall();
    return rtval;
}
