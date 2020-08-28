//list���ʵ��
#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
using namespace std;

//ģ��ʵ��list
namespace my{
template<class T>
class myiterator;

template<class T>
class ListNode{
	friend class myiterator<T>;
	public:
		ListNode(T data=T()):_value(data),next(nullptr),prev(nullptr){}
		~ListNode(){}
	private:
		T _value;
		ListNode* next;
		ListNode* prev;
};
template<class T>
class myiterator{
	public:
		typedef ListNode<T>* PNode;
		typedef myiterator<T> Iterator;
	public:
		myiterator(PNode _P):_Ptr(_P){}
		~myiterator(){}
	private:
		PNode _Ptr;
};
template<class T>
class myList{
	public:
		typedef ListNode<T>* PNode;
	public:
		myList(){
			CreateHead();
		}
		~myList(){
			clear();
			delete _pHead;
			_pHead=nullptr;
		}
	public:
		Iterator begin(){
			return Iterator(_pHead->next);
		}
		Iterator end(){//˫ѭ������
			return Iterator(_pHead);
		}
		Iterator insert(Iterator pos,const T &x){
			PNode s=new ListNode<T>(x);
			
		}
	protected:
		void CreateHead(){
			_pHead=new PNode;
			_pHead->next=_pHead;
			_pHead->prev=_pHead;
		}
	private:
		PNode _pHead;
};
};
int main(){
	cout<<" "; 
	my::myList<int> mylist;
	cout<<" "; 
	return 0;
}



///////////////list�����÷�///////////////
/*
int main(){
	list<int> lt1{1,2,3,4};
	auto pos = find(lt1.begin(), lt1.end(), 3);
	cout<<*pos<<endl;
	lt1.insert(pos,88);//����Ӧλ�ò���
	list<char> lt2(10,'a');//���10��a
	for(const auto &l:lt2)//���ʷ���1��for���� ������begin(),end(),it++��
		cout<<l<<"->";
	cout <<"Over."<<endl;
	//��������
	list<char> lt3=lt2;
	for(const auto &l:lt3)
		cout<<l<<"->";
	cout <<"Over."<<endl;
	list<char> lt4(lt3.begin(),lt3.end());
	for(const auto &l:lt4)
		cout<<l<<"->";
	cout <<"Over."<<endl;
	//���ʷ���2 �Զ������������
	list<char>::iterator it=lt2.begin();
	while(it!=lt2.end()){
		cout<<*it++<<"->";
		//++it;
	}
	cout<<"over."<<endl;
	//�������1
	list<int>::iterator it1=lt1.end();
	//end���ص������һ���ڵ����һ��λ�� �ǷǷ����ݣ����Ҫ--
	cout<<"������ʣ�"<<endl; 
	while(it1!=lt1.begin()){
		--it1;//����
		cout<<*it1<<"->";
	}
	cout<<"over."<<endl;
	//�������2
	list<int>::reverse_iterator rit=lt1.rbegin();//������ʼ
	while(rit!=lt1.rend())
		cout<<*rit++<<"->";//����++
	cout<<"over."<<endl;
	cout<<"lt1��С��"<<lt1.size()<<endl;//Ԫ�ظ���
	cout<<"Lt1�ĵ�һ��Ԫ�غ����һ��Ԫ��"<<lt1.front()<<" "<<lt1.back()<<endl;
	

	lt2.swap(lt3);//����
	//������ʧЧ
	list<int>::iterator it2=lt1.begin();
	auto po=find(lt1.begin(),lt1.end(), 88);
	lt1.erase(po);
	while(it2!=lt1.end()){
		if(it2==po){
			it2=lt1.erase(po);
		} 
		cout<<*it2<<" ";
		++it2;
	}
	return 0;
} 
*/




