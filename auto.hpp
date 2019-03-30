// (C)2019 Bits.

//×Ô¶¯»¯

using namespace std;

void getdata(string path, vector<string> &files, string format){
	long hFile = 0;
	struct _finddata_t fileinfo;
	string p;
	if((hFile = _findfirst(p.assign(path).append("\\*" + format).c_str(), &fileinfo)) != -1){
		do{
			if(!(fileinfo.attrib & _A_SUBDIR))
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
		}
		while(_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}
