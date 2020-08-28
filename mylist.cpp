//list类的实现
#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
using namespace std;

//模拟实现list
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
		Iterator end(){//双循环链表
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



///////////////list基本用法///////////////
/*
int main(){
	list<int> lt1{1,2,3,4};
	auto pos = find(lt1.begin(), lt1.end(), 3);
	cout<<*pos<<endl;
	lt1.insert(pos,88);//在相应位置插入
	list<char> lt2(10,'a');//输出10个a
	for(const auto &l:lt2)//访问方法1：for访问 （带有begin(),end(),it++）
		cout<<l<<"->";
	cout <<"Over."<<endl;
	//拷贝构造
	list<char> lt3=lt2;
	for(const auto &l:lt3)
		cout<<l<<"->";
	cout <<"Over."<<endl;
	list<char> lt4(lt3.begin(),lt3.end());
	for(const auto &l:lt4)
		cout<<l<<"->";
	cout <<"Over."<<endl;
	//访问方法2 自定义迭代器访问
	list<char>::iterator it=lt2.begin();
	while(it!=lt2.end()){
		cout<<*it++<<"->";
		//++it;
	}
	cout<<"over."<<endl;
	//反向访问1
	list<int>::iterator it1=lt1.end();
	//end返回的是最后一个节点的下一个位置 是非法数据，因此要--
	cout<<"反向访问："<<endl; 
	while(it1!=lt1.begin()){
		--it1;//反向
		cout<<*it1<<"->";
	}
	cout<<"over."<<endl;
	//反向访问2
	list<int>::reverse_iterator rit=lt1.rbegin();//反向起始
	while(rit!=lt1.rend())
		cout<<*rit++<<"->";//反向++
	cout<<"over."<<endl;
	cout<<"lt1大小："<<lt1.size()<<endl;//元素个数
	cout<<"Lt1的第一个元素和最后一个元素"<<lt1.front()<<" "<<lt1.back()<<endl;
	

	lt2.swap(lt3);//交换
	//迭代器失效
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




