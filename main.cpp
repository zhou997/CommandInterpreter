#include<iostream>
#include<cstring>
#include<sys/types.h>//基本系统数据类型
#include<sys/stat.h>//文件状态
#include<dirent.h>//文件操作函数
#include<fcntl.h>//文件控制
#include<ftw.h>//文件夹便利
#include<queue>
#include<iomanip>
#include<dirent.h>
#include <sys/utsname.h>
#include<stdlib.h>
#include <unistd.h>

using namespace std;
struct utsname uts;

void pwd();    //显示当前所在目录的路径名
void list(string &dirname);    //列出指定目录名中的所有目录及文件
void cd(string &dirname);     //改变当前工作目录
void mkdir(string& dirname); //新建目录
void rmdir(string& dirname); //删除目录
void rename(string &filename1, string &filename2); //重命名一个文件或目录
void find(string &variable1, string &variable2, string &varaible3);  
void copy(string& path, string& name);   //复制一个已存在的文件
void scanDir(const char* path);

void version();
int i = 0;
string name;
string path1;
char* stringToChar(string& str) {
	char* ch;
	int len = str.length();
	ch = (char*)malloc((len + 1) * sizeof(char));
	strcpy(ch, str.c_str());
}

int main()
{
	string command;
	string variable1, variable2, variable3;
	while (command != "exit") {
		command.clear();
		variable1.clear();
		variable2.clear();
		variable3.clear();

		cout << "zhou997:/$ ";
		while (true) {
			cin >> command;
			char c = getchar();
			if (c == '\n') break;
			cin >> variable1;
			c = getchar();
			if (c == '\n') break;
			cin >> variable2;
			c = getchar();
			if (c == '\n') break;
			cin >> variable3;
			c = getchar();
			if (c == '\n') break;
		}
		if (command == "pwd") {
			pwd();
		}

		if (command == "list") {
			if (variable1.empty()) {
				char res[80];
				getcwd(res, sizeof(res));
				variable1 = res;
				list(variable1);
			}
			else {
				list(variable1);
			}

		}
		if (command == "cd") {
			if (variable1.empty()) {
				string home;
				home = getenv("HOME");
				cd(home);
			}
			else {
				cd(variable1);
			}
		}

		if (command == "mkdir") {
			if (variable1.empty()) {
				cout << "需要目录名" << endl;

			}
			else { 
				mkdir(variable1); 
			}
		}

		if (command == "rmdir") {
			if (variable1.empty()) {
				cout << "需要目录名" << endl;
			}
			else {
			rmdir(variable1);
			}
		}
		if (command == "rename") {
			if (variable1.empty()) {
				cout << "需要原名称" << endl;
			}
			if (variable2.empty()) {
				cout << "需要目标名称" << endl;
			}
			else {
				rename(variable1, variable2);
			}
		}
		if (command == "version") {
			version();
		}

		if (command == "copy") {
			if (variable1.empty()) {
				cout << "需要文件名" << endl;
			}
			else {
				copy(variable1, variable2);

			}
		}
		if (command == "find") {
			if (variable1.empty()) {
				cout << "需要路径" << endl;
			}
			else {
				find(variable1, variable2, variable3);
			}
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
	dir = stringToChar(dirname);
	directory = opendir(dir);
	if (directory == NULL) {
		cout << "无法打开目录" << endl;
		return;
	}
	while ((dp = readdir(directory)) != NULL)
	{    
		if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {}

		else
			cout <<std::left << setw(25) << dp->d_name;
		count++;
		if (count % 5 == 0)
			cout << endl;

	}
	cout << endl;

	closedir(directory);

}

void cd(string &path) {
	char *dir;
	dir = stringToChar(path);
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
	filename = stringToChar(path);
	if (mkdir(filename, 0777) == 0)
	{}
	else
	{
		cout << filename << "创建失败" << endl;
	}
}

void rmdir(string& path) {
	char* filepath;
	filepath = stringToChar(path);
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
	file1 = stringToChar(filename1);
	file2 = stringToChar(filename2);
	if (rename(file1, file2) == 0)
	{
	}
	else
		cout << filename1 << " 修改失败 " << filename2 << endl;

}

static int filter(const struct dirent* dir_ent)
{
	char* str = "/";
	char* fpath = stringToChar(path1);
	fpath = strcat(fpath, str);

	if (!strcmp(dir_ent->d_name, ".") || !strcmp(dir_ent->d_name, "..")) return 0;
	std::string fname = dir_ent->d_name;

	if (dir_ent->d_type == DT_DIR) {
		char* name = stringToChar(fname);
		fpath= strcat(fpath, name);
		scanDir(fpath);
	}
	if (fname.find(name) == std::string::npos) {
		return 0;
	}
	return 1;
}
void scanDir(const char* path) {
	struct dirent** namelist;
	int n = scandir(path, &namelist, filter, alphasort);
	for (int i = 0; i < n; i++) {
		std::string fname = namelist[i]->d_name;
		cout <<fname<<"	"<< path << endl;
	}
}
void find(string& varaible1, string& varaible2, string& varaible3) {
	char* path;
	char* option;
	char* fname;
	path = stringToChar(varaible1);
	option = stringToChar(varaible2);
	fname = stringToChar(varaible3);
	name = fname;
	path1 = path;
	scanDir(path);
}

void copy(string& para1, string& para2) {
	char* name;
	char* path;
	char* str = "/";
	path = stringToChar(para2);
	path = strcat(path, str);
	name = stringToChar(para1);
	FILE* fp1;
	fp1 = fopen(name, "r");
	FILE* fp2;
	fp2 = fopen(strcat(path, name), "w");

	char buff[1024] = { '\0' };
	int count = 0;
	while ((count = fread(buff, 1, 1024, fp1)) != 0)
	{
		fwrite(buff, 1, count, fp2);
	}

	fclose(fp1);
	fclose(fp2);
}

void version() {
	if (uname(&uts) >= 0) {
		cout << "The Kernel version is " << uts.release << endl;
		cout << "The System is " << uts.sysname <<" " <<uts.nodename << endl;
		cout << "The Architecture is " << uts.machine << endl;
	}
}