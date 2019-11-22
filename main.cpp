#include<iostream>
#include<cstring>//标准C++函数库，主要用于字符串处理
#include<sys/types.h>//基本系统数据类型
#include<sys/stat.h>//文件状态
#include<dirent.h>//文件操作函数
#include<fcntl.h>//文件控制
#include<time.h>//定义关于时间的函数
#include<ftw.h>//文件树漫游
#include<queue>
#include<iomanip>
#include<dirent.h>
#include<stdlib.h>
#include <unistd.h>

using namespace std;


void pwd();    //显示当前所在目录的路径名
void list(string &dirname);    //列出指定目录名中的所有目录及文件
void cd(string &dirname);     //改变当前工作目录
void mkdir(string& dirname); //新建目录
void rmdir(string& dirname); //删除目录
void rename(string &filename1, string &filename2); //重命名一个文件或目录
void find(string& dirname);   //在指定的目录及其子目录中查找指定的文件，并输出查找到的文件的绝对路径。
void copy();   //复制一个已存在的文件

bool startWith(const string& str, const string& head) {
	return str.compare(0, head.size(), head) == 0;
}
int main()
{
	string str;
	string path;
	while (str != "exit") {
		cout << "zhou997:/$ ";
		getline(cin, str);
		if (str == "pwd") {
			pwd();
		}

		if (startWith(str,string("list "))==1) {
			str = str.replace(0, string("list ").length(), "");
			list(str);
		}
		if (str == "list") {
			char res[80];
			getcwd(res, sizeof(res));
			str = res;
			list(str);
		}
		if (str == "cd") {
			string home;
			home = getenv("HOME");
			cd(home);
		}
		if (startWith(str, string("cd ")) == 1) {
			str = str.replace(0, string("cd ").length(), "");
			cd(str);
		}
		if (str == "mkdir") {
			cout << "需要目录名"<<endl;
		}
		if (startWith(str, string("mkdir ")) == 1) {
			str = str.replace(0, string("mkdir ").length(), "");
			mkdir(str);
		}
		if (str == "rmdir") {
			cout << "需要目录名" << endl;
		}
		if (startWith(str, string("rmdir ")) == 1) {
			str = str.replace(0, string("rmdir ").length(), "");
			mkdir(str);
		}
		if (str == "rename") {
			cout << "需要文件名" << endl;
		}
		if (startWith(str, string("rename ")) == 1) {
			str = str.replace(0, string("rename ").length(), "");
			mkdir(str);
		}
		if (str == "copy"){
			//copy();
		}
		if (str == "find") {
			//find();
		}
	}
	return 0;
}

void pwd() {
	char res[80];
	getcwd(res, sizeof(res));
	cout << res << endl;
}

void list(string &dirname){
	DIR * directory;
	struct dirent* dp;
	int count = 0;
	char* dir;
	int len = dirname.length();
	dir = (char*)malloc((len + 1) * sizeof(char));
	strcpy(dir, dirname.c_str());
	directory = opendir(dir);
	if (directory == NULL) {
		cout << "无法打开目录" << endl;
		return;
	}
	while ((dp = readdir(directory)) != NULL)
	{    
		if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {}

		else
			cout <<std::left << setw(20) << dp->d_name ;
		count++;
		if (count % 8 == 0)
			cout << endl;

	}
	cout << endl;

	closedir(directory);

}

void cd(string &path) {
	char *dir;
	int len = path.length();
	dir = (char*)malloc((len + 1) * sizeof(char));
	strcpy(dir, path.c_str());
	if (chdir(dir) == 0)
	{
		return;
	}
	else
	{
		cout << "No such file or directory" << endl;
	}

}

void mkdir(string& path) {
	char *filename;
	int len = path.length();
	filename = (char*)malloc((len + 1) * sizeof(char));
	strcpy(filename, path.c_str());
	if (mkdir(filename, 0777) == 0)
	{}
	else
	{
		cout << filename << "创建失败" << endl;
	}
}

void rmdir(string& path) {
	char* filepath;
	int len = path.length();
	filepath = (char*)malloc((len + 1) * sizeof(char));
	strcpy(filepath, path.c_str());
	if (rmdir(filepath) == 0)
	{
	}
	else
	{
		cout << path << "删除失败" << endl;
	}
}


void rename(string& filename1, string& filename2)
{
	char* file1;
	char* file2;
	int len1 = filename1.length();
	filename1 = (char*)malloc((len1 + 1) * sizeof(char));
	int len2 = filename2.length();
	filename2 = (char*)malloc((len2 + 1) * sizeof(char));
	strcpy(file1, filename1.c_str());
	strcpy(file2, filename2.c_str());

	if (rename(file1, file2) == 0)
	{
	}
	else
		cout << filename1 << " 修改失败 " << filename2 << endl;

}