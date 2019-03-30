// (C)2019 Bits.

//º¯Êý

using namespace std;

string GetNowPath(){
    char path[256];
    getcwd(path, 256);
    return path;
}

void copyf(string src, string tar){
    FILE *p1, *p2;
    register char c;
    p1 = fopen(src.c_str(), "r");
    p2 = fopen(tar.c_str(), "w");
    while((c = fgetc(p1)) != EOF)
        fputc(c, p2);
    fclose(p1);
    fclose(p2);
}

inline bool StrComp(string &a, string &b){
	int len1 = a.size() - 1,
        len2 = b.size() - 1;
	while(len1 >= 0 && a[len1] == ' ')
        len1--;
    while(len2 >= 0 && b[len2] == ' ')
        len2--;
    a.erase(len1 + 1, a.size() - len1 - 1);
    b.erase(len2 + 1, b.size() - len2 - 1);
	return a == b;
}

bool checkfolder(const string &strPath){
    WIN32_FIND_DATA wfd;
    bool rValue = false;
    HANDLE hFind = FindFirstFile(strPath.c_str(), &wfd);
    if((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        rValue = true;
    FindClose(hFind);
    return rValue;
}

bool checkfile(string path){
    FILE *p;
    p = fopen(path.c_str(), "r");
    if(p == NULL){
        fclose(p);
        return false;
    }
    fclose(p);
    return true;
}
