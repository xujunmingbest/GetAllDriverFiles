#include <windows.h>
#include <iostream>
#include <vector>
using namespace std;

bool GetAllFolders(string& Path, vector<string> &AllFolders);
bool  GetAllFiles(string& Path, vector<string> &FData);
bool  DiGuiGetAllFiles(string & Path, vector<string> &AllFiler);
void getDriver(vector<string> &drivers);

void main(int Numbers, char *Str[])
{
	vector<string> drivers;
	getDriver(drivers);
	cout << drivers.size() << endl;

	vector<string> allfiles;
	for (int i = 0; i < drivers.size(); i++) {
		cout << drivers[i].c_str() << endl;
		DiGuiGetAllFiles(drivers[i], allfiles);
		cout << allfiles.size() << endl;
	}
	system("pause");
}




void getDriver(vector<string> &drivers) {
	DWORD Len = GetLogicalDriveStrings(0, 0);//获取盘符的长度
	char *Driver = new char[Len];//字符数组
	GetLogicalDriveStrings(Len, Driver);//获取系统盘字符串
	string out(Driver, Len);

	int pos = 0;
	string temp;
	temp = out.c_str() + pos;
	drivers.push_back(temp);
	while ((pos = out.find('\0', pos)) != out.npos)
	{
		pos++;
		temp = out.c_str() + pos;
		if (temp.length() == 0) continue;
		drivers.push_back(temp);
	}
	delete[] Driver;
	return;
}



bool  GetAllFiles(string& Path, vector<string> &FData)
{
	FData.clear();
	WIN32_FIND_DATA FindData;
	HANDLE hError;
	hError = FindFirstFile((Path + "\\*.*").c_str(), &FindData);
	hError = FindFirstFile(Path.c_str(), &FindData);
	if (hError == INVALID_HANDLE_VALUE)
	{
		printf("搜索失败!");
		return false;
	}
	while (::FindNextFile(hError, &FindData))
	{
		// 过虑.和..
		if (memcmp(FindData.cFileName, ".", 1) == 0
			|| memcmp(FindData.cFileName, "..", 2) == 0)
		{  //
			continue;
		}
		// 构造完整路径
		if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{//判断是否文件夹
			continue;
			//GetAllDirFile(FullPathName);
		}
		// 输出本级的文件
		string Char(FindData.cFileName);
		FData.push_back(Char);
	}
	return true;
}

bool GetAllFolders(string &Path, vector<string> &AllFolders)
{
	AllFolders.clear();
	WIN32_FIND_DATA FindData;
	HANDLE hError;

	hError = FindFirstFile((Path + "\\*.*").c_str(), &FindData);
	if (hError == INVALID_HANDLE_VALUE)
	{
		printf("搜索失败!");
		return false;
	}
	while (::FindNextFile(hError, &FindData))
	{
		// 过虑.和..
		if (memcmp(FindData.cFileName, ".", 1) == 0
			|| memcmp(FindData.cFileName, "..", 2) == 0)
		{  //
			continue;
		}
		// 构造完整路径
		if (FindData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		{//判断是否文件夹
			// 输出本级的文件夹
			string Char(FindData.cFileName);
			AllFolders.push_back(Char);

		}
	}
	return true;
}


bool  DiGuiGetAllFiles(string & Path, vector<string> &AllFiler) {
	WIN32_FIND_DATA FindData;
	HANDLE hError;
	char FilePathName[1000];
	// 构造路径
	hError = FindFirstFile((Path + "\\*.*").c_str(), &FindData);
	if (hError == INVALID_HANDLE_VALUE)
	{
		cout << Path.c_str() << endl;
		printf("搜索失败!");
		return false;
	}
	while (::FindNextFile(hError, &FindData))
	{
		// 过虑.和..
		if (memcmp(FindData.cFileName, ".", 1) == 0
			|| memcmp(FindData.cFileName, "..", 2) == 0)
		{  //
			continue;
		}
		// 构造完整路径
		if (FindData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		{//判断是否文件夹

			DiGuiGetAllFiles((Path + "\\" + FindData.cFileName), AllFiler);
		}
		if (!(FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			AllFiler.push_back((Path + "\\" + FindData.cFileName));
		}
	}
	return true;
}