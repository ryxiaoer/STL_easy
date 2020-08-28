#include <iostream>
#include <cstring>
#include <typeinfo>
#include <stdlib.h>
#include <assert.h>
//#include <list>
//#include <stack>
#include <iterator>
//迭代器
//迭代：依序访问且只访问一次的过程 迭代器就是迭代的工具
//空间配置器
using namespace std;
//链表实现
namespace my{
	template<class _Ty>
	_Ty* _Allocate(size_t _N, _Ty*){//申请
		if (_N < 0)
			_N = 0;
		return ((_Ty *)operator new((size_t)_N * sizeof (_Ty))); 
	}
	//构造
	template<class _T1, class _T2>
	void _Construct(_T1* _P, const _T2& _V){
		new ((void*)_P) _T1(_V);   //定位new
	}
	//析构
	template<class _Ty>
	void _Destroy(_Ty* _P){
		_P->~_Ty();
	}

	//空间配置器
	template<class _Ty>
	class myallocator{
	public:
		typedef size_t size_type;
		typedef size_t difference_type;
		typedef _Ty*   pointer;
		typedef const _Ty* const_pointer;
		typedef _Ty&       reference;
		typedef const _Ty& const_reference;
		typedef _Ty value_type;
		//申请空间
		pointer allocate(size_type _N, const void *){
			return (_Allocate((difference_type)_N, (pointer)0));
		}
		//以字符大小申请空间
		char* _Charalloc(size_type _N){
			return (_Allocate((difference_type)_N,(char*)0));
		}
		//释放空间
		void deallocate(void* _P, size_type){
			operator delete(_P); //  free
		}
		//构造对象
		void construct(pointer _P, const _Ty& _V){
			_Construct(_P, _V);
		}
		//析构对象
		void destroy(pointer _P){
			_Destroy(_P);
		}
	};
	//======================链表和迭代器的实现======================//
	template<class _Ty,class _A=myallocator<_Ty>>
	//stl中是带头双向循环链表
	class list{
		public:
		//类型的萃取
			typedef _Ty          value_type;//定义值类型
			typedef _Ty*         pointer_type;//指针类型
			typedef _Ty&         reference_value;//引用类型
			typedef const _Ty*   const_pointer_type;//常指针类型
			typedef const _Ty&   const_reference_value;//常引用类型
			typedef size_t       size_type;
		public:
			struct _Node;//节点声明
			typedef _Node* _Nodeptr;
			struct _Node{
				_Ty        _Value;
				_Nodeptr   _Next;
				_Nodeptr   _Prev;
			}; 
		public:
		//迭代器类 内部类
			class iterator{//使用对象中的ptr指向一个节点
				public:
				iterator(_Nodeptr _P):_Ptr(_P){
					
				}
				bool operator!=(const iterator &it){
					return !(it._Ptr==_Ptr);
				}
				bool operator==(const iterator &it){
					return (it._Ptr==_Ptr);
				}
				_Ty& operator*(){
					return (_Ptr->_Value);
				}
				/*
				_Nodeptr operator++(){
				_Ptr=_Ptr->_Next;
					return _Ptr;
				} 
				*/
				iterator& operator++(){
					_Ptr=_Ptr->_Next;
					return  *this;
				}
				iterator operator++(int){
					iterator tmp=*this;
					_Ptr=_Ptr->_Next;
					return tmp;
				}
				_Nodeptr _Mynode(){
					return _Ptr;
				}
				private:
				_Nodeptr _Ptr;
			};
		public:
		//构造对象
			//list():_Head(nullptr),_Size(0){}//_head为空，但实际要求头指针不为空，所以要调用bynode申请一个节点
			list():_Head(_Buynode()),_Size(0)
			{}
		public:
			iterator begin(){//第一个真实的节点
				return iterator(_Head->_Next);
			}
			iterator end(){//迭代器默认左闭右开 即要返回最后一个节点的下一个位置（头）不同的容器要做不同的判断
				return iterator(_Head);
			}
		public:
			void push_back(const _Ty &x){
//				_Nodeptr _S=(_Nodeptr)malloc(sizeof(_Node));
//				assert(_S!=nullptr);
				
//				_S->_Value=x;				
//				_S->_Prev=_Head->_Prev;
//				_Head->_Prev->_Next=_S;
//				_S->_Next=_Head;
//				_Head->_Prev=_S;
				_Nodeptr _S=_Buynode(_Head,_Head->_Prev);
				_S->_Value=x;	
				_Head->_Prev->_Next=_S;
				_Head->_Prev=_S;
				_Size++;
			}
			void push_front(const _Ty &x){
				_Nodeptr _S=_Buynode(_Head->_Next,_Head);
				_S->_Value=x;
				_Head->_Next->_Prev=_S;
				_Head->_Next=_S;
				_Size++;
			}
			void push_front_0(const _Ty &x){
				insert(begin(),x);
			}
			void PrintList(){
				_Nodeptr p=_Head->_Next;
				while(p!=_Head){
					cout<<p->_Value<<"->";
					p=p->_Next;
				}
				cout<<"Over"<<endl;
			}
			iterator insert(iterator _P,const _Ty& _X=_Ty()){//默认零值
				_Nodeptr _S=_P._Mynode();//s指向p所在的节点
				_S->_Prev=_Buynode(_S,_S->_Prev);//申请一个节点 前驱是s思的前驱，后继是s
				_S=_S->_Prev;
				_S->_Prev->_Next=_S;
				//_S->_Value=_X;
				allocator.construct(&(_S->_Value),_X);
				++_Size;
				return (iterator(_S));
			}
			
		protected:
		                              //_Next arg     _Prev arg(前一个，下一个参数)
			_Nodeptr _Buynode(_Nodeptr _Narg=0,_Nodeptr _Parg=0){//0->nullptr
				//_Nodeptr _S=(_Nodeptr)malloc(sizeof(_Node));
				_Nodeptr _S=(_Nodeptr)allocator._Charalloc(sizeof(_Node));
				assert(_S!=nullptr);
				_S->_Value=0;
				//_S->_Next=_S;
				//_S->_Prev=_S;
				_S->_Next=_Narg!=0?_Narg:_S;
				_S->_Prev=_Parg!=0?_Parg:_S;
				return _S;
			}
		private:
		//_内部类型或函数
			_Nodeptr  _Head;
			size_type _Size;//记录真实节点个数
			_A        allocator;//空间配置对象 空间配置器
	};
};
int main(){
	my::list<int> mylist;
	mylist.push_back(1);
	mylist.push_front_0(0);
	auto pos=mylist.begin();
	mylist.insert(pos,2);
	
	my::list<int>::iterator it=mylist.begin();
	while(it!=mylist.end()){
		cout<<*it<<"->";
		//it++;
		++it;
	}
	cout<<"Over."<<endl;
	
	return 0;
}
/*
int main(){
	my::list<int> mylist;
	
	mylist.push_back(1);
	mylist.push_back(2);
	mylist.push_back(3);
	mylist.push_front_0(8);
	mylist.push_front(88);
	//mylist.PrintList();
	
	auto pos=mylist.begin();
	mylist.insert(pos,3);
	
	my::list<int>::iterator it=mylist.begin();
	while(it!=mylist.end()){
		cout<<*it<<"->";
		//it++;
		++it;
	}
	cout<<"Over."<<endl;
	
	
	return 0;
}
*/
