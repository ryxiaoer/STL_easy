//hashtable
#include<iostream>
#include<vector>
#include<memory>
#include<cstring>
using namespace std;


template<class Type>
class HashNode{
	//friend class HashTable<Type,_N>; //这里_N没有，GG，
	HashNode(Type d=Type()):data(d),link(nullptr)
	{}
public:
	Type data;
	HashNode* link;
};
//默认7
template<class Type,size_t _N=7> 
class HashTable{
public:
	HashTable():size(0){
		memset(ht,0,sizeof(HashTable<Type>*)*_N);
	}
	~HashTable() {
		clear();
	}
	void insert(Type &x){
		int index=HashFun(x);//下标计算
		//头插
		HashNode<Type>* s=new HashNode<Type>(x);
		s->link=ht[index];
		ht[index]=s;
		size++;
	}
	//查找并返回节点地址
	HashNode<Type>* Find(const Type &key){
		int index=HashFun(key);
		HashNode<Type>* p=ht[index];
		while(p!=nullptr && p->data!=key){
			p=p->link;
		}
		return p;
	}
	//删除
	void Remove(const Type &key){
		HashNode<Type>* p=Find(key);
		if(p==nullptr) return;
		if(p->link!=nullptr){
			HashNode<Type>* tmp=p->link;
			p->data=p->link->data;
			p->link=p->link->link;
			delete tmp;
			tmp=nullptr;
			size--;
		}
		else {
			//删除尾巴/只有一个节点,从头开始，因为相对来这种情况比较少，可以认为对复杂度影响不大
			int index=HashFun(key);
			HashNode<Type>* tmp=ht[index];
			if(ht[index]==p){
				ht[index]=nullptr;
				delete p;
				p=nullptr;//头
			}
			else{
				while(tmp->link!=p){
					tmp=tmp->link;
				}
				tmp->link=nullptr;
				delete p;
				p=nullptr;
			}
			size--;
		}
	}	
public:
	void PrintHash()const{
		for(int i=0;i<_N;i++){
			cout << "[" << i << "]";
			HashNode<Type>* p=ht[i];
			while(p!=nullptr){
				cout<<p->data<<" ";
				p=p->link;
			}
			cout<<"NULL"<<endl;
		}
	}
	int  lenth()const {
		return size;
	}
	void clear() {
		for (int i = 0; i < _N; ++i) {
			HashNode<Type>* p = ht[i];
			while (p != nullptr) {
				ht[i] = p->link;
				delete p;
				p = ht[i];
			}
		}
	}
	void HashResize(){
		size_t buckSize=_N;
		if(size==buckSize){
			
		}
	}

protected:
	int HashFun(const Type &key){
		return key%_N; //哈希函数 除留余数
	}
private:
	HashNode<Type>*  ht[_N];
	size_t            size;
};
int main(){
	HashTable<int> ht;
	//测试用例
	vector<int> iv={1,2,8,15,20};
	for(auto &e:iv)
		ht.insert(e);
	ht.PrintHash();
	cout << "delete and test>>" << endl;
	ht.Remove(20);
	ht.Remove(5);
	ht.Remove(15);
	ht.Remove(8);
	ht.PrintHash();
	cout << "length=" << ht.lenth() << endl;
	ht.clear();
	ht.PrintHash();
	getchar();
	return 0;
}
