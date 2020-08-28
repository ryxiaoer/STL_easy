#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//ģ��vector��ʵ��
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
				delete []_start;//delete nullptr�ǿ��Ե�
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
			//����:�����¿ռ�-�����Ͽռ�����ݸ��ƹ���
		public: 
			void reserve(size_t n){
				if(n>capacity()){
					T* new_start=new T[n];
					//memcpy��for
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
		//���� ɾ��
			iterator insert(iterator pos,const T &x){
				if(size()>=capacity()){
					//����
					size_t offset=pos-_start;//ƫ��������
					size_t new_capacity;
					if(capacity()==0) new_capacity=1;
					else new_capacity=capacity()*2;
					reserve(new_capacity);
					//ע�⣺��ʱpos��ָ��ԭ�ռ� ���Ҫ��pos����������
					pos=_start+offset;
				}
				iterator it_end=_finish;
				while(it_end>pos){//�ƶ�����
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
			//����
		public:
			void swap(vector<T>  &v){
				cout<<"swap:"<<endl;
				std::swap(_start,v._start);
				std::swap(_finish,v._finish);
				std::swap(_end_of_storage,v._end_of_storage);
			}
		private:
			iterator _start; //���������Կ�����ָ��
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



////////////////////Ӧ��/////////////////////
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
	//cout<<"new *pos="<<*pos<<endl;//������ʧЧ ������ܱ������ײ����ݣ�
	//�жϵ�����ʧЧ ָ��λ���Ƿ�Ϸ� 
	//ɾ�� ֱ��iv.erase(it)�ᵼ�µ�����ʧЧ
	//Ӧ����it=iv.erase(it)�����µ�������ָ��ĵ�ַ
    return 0;
}
*/
