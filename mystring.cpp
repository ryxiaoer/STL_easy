//string
#include <iostream>
//#include <string>
#include <iterator>
#include <algorithm>
using namespace std;
//��ǳ��������
//���������ַ��� �¿��ٿռ���ߴ���һ�����Խ�������ʱ����
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
				//�����ķ�������ɾ������str,һ�����벻�ɹ�Ԫ���ݻ��ܱ���
				string tmp_str(s);    //��ʱ����
				swap(_str, tmp_str._str);
				
				//char *tmp_str=newchar[strlen(s)+1];
				//delete []_str;
				//_str=new char[strlen(s)+1]��
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
//////////////////////////string�Ļ���Ӧ��///////////////////////
//oj ��д�ַ���ת����

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
	else {cout<<"��������"<<endl;}
	
	
	//char* str="-216452a";
	//int value=atoi(str);//�ַ���ת������ϵͳ�Դ���
	//cout<<atoi(str.c_str());
	//cout<<"value="<<value<<endl;
	return 0;
}
///////////////////////////////////////////////////////////////////
/*
//�ַ����Ľ�ȡ
int main(){
	string str("http://cplusplus.com/reference/string/string/?kw=string");
	//string tmp_str=str.substr();//Ĭ�ϲ���ȡ
	size_t start=str.find("cplusplus");
	size_t end=str.find(".com");
	string tmp_str=str.substr(start,end-start+4);//��һ��Ӧ�����ַ����Ľ�ȡ����,������ҿ�
	cout<<tmp_str<<endl;
	//�ַ���������
	string str_in;
	//    ������ �������
	getline(cin,str_in);//cin<<��ʧȥ�ո������� getline����һ��  
	cout<<"str_in="<<str_in<<endl; 
	//�����ض�λ��
	cout<<"str[10]="<<str[10]<<endl;
	cout<<"str.at(10)="<<str.at(10)<<endl;//��������ķ���λ����һ���ģ�����at���Խ����ʽ��м�飬��[]�Ƿ������Դ��� �������
	cout<<"�Ƿ�����str[-1]"<<str.at(-1)<<endl;
	cout<<"�Ƿ�����str[100]"<<str.at(100)<<endl;
	return 0;
}
/*
//find + npos ���Ҷ�λ��
int main(){
	string str("http://cplusplus.com/reference/string/string/?kw=string");
	//npos ���һ��λ��
	auto pos0=str.find('/');//pos���±� Ĭ�ϴ�0С�꿪ʼ����
	if(pos0==string::npos)
		cout<<"��"<<endl;
	else cout<<"pos0="<<pos0<<endl;
	auto pos10=str.find("kw=string",10);//��5��ʼ����
	if(pos10==string::npos)
		cout<<"��"<<endl;
	else cout<<"pos10="<<pos10<<endl;
	
	return 0;
}
/*
//c_str ���ַ���תΪc��ʽ�ַ���
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
	cout<<"str���ȣ�"<<my_strlen(str.c_str())<<endl;
	
	return 0;
}
/*
//����ÿ����ǰһ�ε�2�� 1 2 4 4 8 8 8 8 16 16
void fun(int n){
	string str;
	int x='a';
	for(int i=0;i<n;i++){
		str.push_back((char)(x++));
		cout<<"str.capacity="<<str.capacity()<<endl;
	}	
	cout<<"push_back����  str="<<str<<endl;
}
void re_fun(int n){
	string str;
	str.reserve(20);//Ԥ���Ļ��ڲ�����Ԥ���ռ������²����ݣ��ܼ������ݵĿ�������
	int x='a';
	for(int i=0;i<n;i++){
		str.push_back((char)(x++));
		cout<<"str.capacity="<<str.capacity()<<endl;
	}	
	cout<<"push_back����  str="<<str<<endl;
}
int main(){
	fun(10);
	cout<<"Ԥ���㹻�ռ��"<<endl;
	re_fun(10);
	return 0;
}
/*
int main(){
	string str1("qazs");
	str1.clear();//���
	cout<<"str1.size()="<<str1.size()<<"  str1.length()="<<str1.length()
		<<"  str1.capacity()="<<str1.capacity()<<endl;//size��lenggth������һ���ģ�����length��ֻ���string��
		//capacity�ǿռ��ܴ�С�����ǰ��һ��
	cout<<"str1="<<str1<<endl;;
	string str2="wsx";
	cout<<"str2="<<str2<<endl;
	string str3(3,'@');
	cout<<"str3="<<str3<<endl;
	//����
	str1.resize(10);//���µ���Ԫ�صĸ�����n ������resize(10,'a')ָ���ַ�����Ĭ���ǡ�0��
	str1.resize(2);//С��ʵ�ʳ���/Ĭ�ϳ��ȣ�size��length=1������������ 10
	cout<<"str1.size()="<<str1.size()<<"  str1.length()="<<str1.length()
		<<"  str1.capacity()="<<str1.capacity()<<endl;
	//Ԥ���ռ�
	str1.reserve(1);//Ҫ��ʵ�ʴ� ����2
	cout<<"str1.size()="<<str1.size()<<"  str1.length()="<<str1.length()
		<<"  str1.capacity()="<<str1.capacity()<<endl;
	return 0; 
}
*/
