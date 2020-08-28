#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//模拟vector的实现
namespace my{
	template<class T>
	class vector{
		public:
			typedef T* iterator;
		public:
			vector():_start(nullptr),_finish(nullptr),_end_of_storage(nullptr){
				
			}	
			vector(initializer_list<T> il):_start(nullptr),_finish(nullptr),_end_of_storage(nullptr){
				reserve(il.size());
				for(auto &e:il)
					push_back(e);
				cout<<"initializer Over!"<<endl;
			}
			~vector(){
				delete []_start;//delete nullptr是可以的
				_start=_finish=_end_of_storage=nullptr;
			}
		public:
			size_t size()const{
				return _finish-_start;
			}
			size_t capacity()const{
				return _end_of_storage-_start;
			}
			bool empty(){
				return _start==_finish;
			}
			//扩容:开辟新空间-》将老空间的数据复制过来
		public: 
			void reserve(size_t n){
				if(n>capacity()){
					T* new_start=new T[n];
					//memcpy或for
					size_t old_size=size();
					for(int i=0;i<old_size;i++){
						new_start[i]=_start[i];
					}
					delete []_start;
					_start=new_start;
					_finish=_start+old_size;
					_end_of_storage=_start+n;
				}
			}
		public:
			iterator begin()const{
				return _start;
			}
			iterator end()const{
				return _finish;
			}
		public:
		//插入 删除
			iterator insert(iterator pos,const T &x){
				if(size()>=capacity()){
					//扩容
					size_t offset=pos-_start;//偏移量计算
					size_t new_capacity;
					if(capacity()==0) new_capacity=1;
					else new_capacity=capacity()*2;
					reserve(new_capacity);
					//注意：此时pos还指向原空间 因此要对pos迭代器更新
					pos=_start+offset;
				}
				iterator it_end=_finish;
				while(it_end>pos){//移动数据
					*it_end=*(it_end-1);
					it_end--;
				}
				*it_end=x;
				_finish++;
				return it_end;
			}
			void push_back(const T &x){
				insert(end(),x);
			}
			iterator erase(iterator pos){
				iterator p=pos;
				while(p!=end()){
					*p=*(p+1);
					p++;
				}
				_finish--;
				return pos;
			}
			//交换
		public:
			void swap(vector<T>  &v){
				cout<<"swap:"<<endl;
				std::swap(_start,v._start);
				std::swap(_finish,v._finish);
				std::swap(_end_of_storage,v._end_of_storage);
			}
		private:
			iterator _start; //迭代器可以看作是指针
			iterator _finish;
			iterator _end_of_storage;
	};
};
int main(){
	my::vector<int> v1={1,2,3};
	my::vector<int> v2={1,2,3,4};
	v1.swap(v2);
	for(const auto &e:v1)
		cout<<e<<" ";
	cout<<endl;
}
/*
int main(){
	my::vector<int> iv;
	cout<<iv.size()<<" "<<iv.capacity()<<endl;
	iv.reserve(10);
	cout<<iv.size()<<" "<<iv.capacity()<<endl;
	iv.insert(iv.begin(),1);
	iv.insert(iv.begin(),2);
	iv.insert(iv.begin(),3);
	iv.insert(iv.begin(),4);
	iv.push_back(5);
	for(const auto &e:iv)
		cout<<e<<" ";
	cout<<endl;
	iv.erase(iv.begin());
	iv.erase(iv.end());
	for(const auto &e:iv)
		cout<<e<<" ";
	cout<<endl;
	return 0;
}



////////////////////应用/////////////////////
/*
int main()
{
    vector<int> iv;
    cout << iv.capacity() << endl;
    for (int i = 0; i<6; ++i)
    {
        iv.push_back(i);
        cout << "size: " << iv.size() << endl;
        cout << "capacity: " << iv.capacity() << endl;//kuo rong *2
	}
	for(const auto  &e:iv)
		cout<<e<<" "<<endl;
	cout<<endl;
	auto pos=find(iv.begin(),iv.end(),6);
	if(pos!=iv.end())
		cout<<"*pos="<<*pos<<endl;
	else
		cout<<"NO DATA"<<endl;
	//iv.push_back(100);
	//cout<<"new *pos="<<*pos<<endl;//迭代器失效 程序可能崩溃（底层扩容）
	//判断迭代器失效 指向位置是否合法 
	//删除 直接iv.erase(it)会导致迭代器失效
	//应该是it=iv.erase(it)；更新迭代器所指向的地址
    return 0;
}
*/
