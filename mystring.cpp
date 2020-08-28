//string
#include <iostream>
//#include <string>
#include <iterator>
#include <algorithm>
using namespace std;
//深浅拷贝问题
//拷贝的两种方法 新开辟空间或者创建一个可以交换的临时对象
namespace bit
{
	class string
	{
	public:
		string(const char* str = "")
		{
			if (nullptr == str)
				_str = new char[1]{'\0'};
			else
			{
				_str = new char[strlen(str) + 1];
				strcpy(_str, str);
			}
		}
		string(const string &s)
		{
			_str = new char[strlen(s._str)+1];
			strcpy(_str, s._str);
		}
		string& operator=(const string &s)
		{
			if(this != &s)
			{
				//这样的方法不用删除——str,一旦申请不成功元数据还能保留
				string tmp_str(s);    //临时对象
				swap(_str, tmp_str._str);
				
				//char *tmp_str=newchar[strlen(s)+1];
				//delete []_str;
				//_str=new char[strlen(s)+1]；
				//strcpy(_str,s._str);
			}
			return *this;
		}
		~string()
		{
			if (_str)
			{
				delete[] _str;
				_str = nullptr;
			}
		}
	private:
		char* _str;
	};
};
void main()
{
	bit::string str(nullptr);
	bit::string str1("abc");
	bit::string str2("xyz");
	str2 = str1;
}
/*
//////////////////////////string的基础应用///////////////////////
//oj 编写字符串转整数

int main(){
	string str("123a4");
	string tmp;
	int sz=0;
	if((str[0]>='0'&&str[0]<='9')||str[0]=='+'||str[0]=='-'){
		if(str[0]!='0'&&str[0]!='+') 
		tmp.push_back(str[0]);
		for(int i=1;i<str.size();i++){
			if(str[i]>'9'||str[i]<'0') break;
			tmp.push_back(str[i]);
		}
	//	cout<<tmp<<endl;
		for(auto &c:tmp){
	        sz=((int)c)+sz*10;
	        cout<<sz<<endl;
	    }

	}
	else {cout<<"输入有误"<<endl;}
	
	
	//char* str="-216452a";
	//int value=atoi(str);//字符串转整数（系统自带）
	//cout<<atoi(str.c_str());
	//cout<<"value="<<value<<endl;
	return 0;
}
///////////////////////////////////////////////////////////////////
/*
//字符串的截取
int main(){
	string str("http://cplusplus.com/reference/string/string/?kw=string");
	//string tmp_str=str.substr();//默认不截取
	size_t start=str.find("cplusplus");
	size_t end=str.find(".com");
	string tmp_str=str.substr(start,end-start+4);//后一个应该是字符串的截取长度,且左闭右开
	cout<<tmp_str<<endl;
	//字符串的输入
	string str_in;
	//    输入流 输入对象
	getline(cin,str_in);//cin<<会失去空格后的内容 getline保留一行  
	cout<<"str_in="<<str_in<<endl; 
	//访问特定位置
	cout<<"str[10]="<<str[10]<<endl;
	cout<<"str.at(10)="<<str.at(10)<<endl;//这个两个的访问位置是一样的，但是at会对越界访问进行检查，而[]是发生断言错误 程序崩溃
	cout<<"非法访问str[-1]"<<str.at(-1)<<endl;
	cout<<"非法访问str[100]"<<str.at(100)<<endl;
	return 0;
}
/*
//find + npos 查找定位、
int main(){
	string str("http://cplusplus.com/reference/string/string/?kw=string");
	//npos 最后一个位置
	auto pos0=str.find('/');//pos是下标 默认从0小标开始查找
	if(pos0==string::npos)
		cout<<"无"<<endl;
	else cout<<"pos0="<<pos0<<endl;
	auto pos10=str.find("kw=string",10);//从5开始查找
	if(pos10==string::npos)
		cout<<"无"<<endl;
	else cout<<"pos10="<<pos10<<endl;
	
	return 0;
}
/*
//c_str 将字符串转为c格式字符串
int my_strlen(const char *str){
	int count=0;
	while(*str++!='\0')
		count++;
	return count;
}
int main(){
	//int len=mystrlen("qazwsxedc");
	//cout<<len<<endl;
	string str("qazwsxedc");
	cout<<str<<endl;
	cout<<"str长度："<<my_strlen(str.c_str())<<endl;
	
	return 0;
}
/*
//扩容每次是前一次的2倍 1 2 4 4 8 8 8 8 16 16
void fun(int n){
	string str;
	int x='a';
	for(int i=0;i<n;i++){
		str.push_back((char)(x++));
		cout<<"str.capacity="<<str.capacity()<<endl;
	}	
	cout<<"push_back结束  str="<<str<<endl;
}
void re_fun(int n){
	string str;
	str.reserve(20);//预留的话在不超出预留空间的情况下不扩容，能减少数据的拷贝次数
	int x='a';
	for(int i=0;i<n;i++){
		str.push_back((char)(x++));
		cout<<"str.capacity="<<str.capacity()<<endl;
	}	
	cout<<"push_back结束  str="<<str<<endl;
}
int main(){
	fun(10);
	cout<<"预留足够空间后："<<endl;
	re_fun(10);
	return 0;
}
/*
int main(){
	string str1("qazs");
	str1.clear();//清除
	cout<<"str1.size()="<<str1.size()<<"  str1.length()="<<str1.length()
		<<"  str1.capacity()="<<str1.capacity()<<endl;//size和lenggth本质是一样的，但是length是只针对string的
		//capacity是空间总大小，清楚前后一致
	cout<<"str1="<<str1<<endl;;
	string str2="wsx";
	cout<<"str2="<<str2<<endl;
	string str3(3,'@');
	cout<<"str3="<<str3<<endl;
	//扩容
	str1.resize(10);//重新调整元素的个数至n ，可以resize(10,'a')指定字符补充默认是‘0’
	str1.resize(2);//小于实际长度/默认长度，size和length=1，但容量不变 10
	cout<<"str1.size()="<<str1.size()<<"  str1.length()="<<str1.length()
		<<"  str1.capacity()="<<str1.capacity()<<endl;
	//预留空间
	str1.reserve(1);//要比实际大 大于2
	cout<<"str1.size()="<<str1.size()<<"  str1.length()="<<str1.length()
		<<"  str1.capacity()="<<str1.capacity()<<endl;
	return 0; 
}
*/
