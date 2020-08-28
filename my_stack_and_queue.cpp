//stack��queue�Լ����ȼ����ж����������� ��������������û�е�����
#include<iostream>
#include<queue>
#include<deque>
#include<stack>
#include<vector>
#include<functional>
using namespace std;

namespace my{
	template<class T,class Cont=vector<T>,class Comper=less<T>>//�ṩ���͡��������ȽϷ�����Ĭ�ϴ�ѣ�
	class priority_queue{
		public:
			priority_queue()
			{}
			template<class InputIterator>
			priority_queue(InputIterator first,InputIterator last):c(first,last){
				//�ֶ�������
				int n=c.size();
				int start=n/2-1; //�ҵ������������һ����֧
				while(start>=0){
					_AdjustDown(start,n);
					start--;
				}
			}
		public:
			void show_heap()const{
				for(int i=0;i<c.size();i++)
					cout<<c[i]<<" ";
				cout<<endl;
			}
			void push(const T &x){
				c.push_back(x);
				_AdjustUp(c.size()-1);
			}
			void pop(){
				std::swap(c[0],c[c.size()-1]);
				c.pop_back();
				_AdjustDown(0,c.size());
			}
		protected:
			//���µ���
			void _AdjustDown(int start,int n){
				int i=start;
				int j=2*i+1;//������
				while(j<n){
					if(j+1<n && c[j]<c[j+1]) //�ҵ������������ֵ
					//if(comp(c[i],c[j]))
						j++;
					if(c[j]>c[i]){ 
						T tmp=c[i];
						c[i]=c[j];
						c[j]=tmp;
						//����׷��
						i=j;
						j=2*i+1;
					}//����
					else break;
				}
			}
			//���ϵ���
			void _AdjustUp(int start){
				int j=start;//��
				int i=(j-1)/2;//��
				while(i>=0){
					if(c[j]>c[i]){
						T tmp=c[i];
						c[i]=c[j];
						c[j]=tmp;
						
						j=i;
						i=(j-1)/2;
					}
					else break;
				}
			}
			
		private:
			Cont c;  //����
			Comper comp; //�ȽϷº���
	};
};
int main(){
	vector<int> v{3,2,7,60,4,1,9,8,5};
	my::priority_queue<int> pq(v.begin(),v.end());
	//my::priority_queue<int,vector<int>,generate<int>> pq(v.begin(),v.end());//С��
	pq.show_heap();
	pq.push(15);
	pq.pop();
	pq.show_heap();
	return 0;
}

/*
namespace my{
	template<class T,class Cont=vector<T>,class Comper=less<T>>//�ṩ���͡��������ȽϷ�����Ĭ�ϴ�ѣ�
	class priority_queue{
		public:
			priority_queue():c(){
				
			}
			template<class InputIterator>
			priority_queue(InputIterator first,InputIterator last):c(first,last){
				make_heap(c.begin(),c.end(),comp); //������
			}
		public:
			bool empty(){
				return 0==c.size();
			}
			size_t size(){
				return c.size();
			}
		public:
			void push(const T &x){
				c.push_back(x);
				push_heap(c.begin(),c.end(),comp);//������
			}
			void pop(){
				pop_heap(c.begin(),c.end(),comp);
				c.pop_back();
			}
			T top(){
				return c.front();
			}
		private:
			Cont c;  //����
			Comper comp; //�ȽϷº���
	};
};
int main(){
	vector<int> v{3,2,7,60,4,1,9,8,5};
	my::priority_queue<int> pq(v.begin(),v.end());

	cout<<endl;
	pq.push(100);
	pq.push(200);
	cout<<pq.top();
	pq.pop();
	cout<<pq.top();
	return 0;
}
/*
//�º���
namespace my{
	template <class InputIterator, class T>
	ptrdiff_t count(InputIterator first, InputIterator last, const T& value){
		ptrdiff_t ret = 0;
		while (first != last){
			if (*first++ == value) 
				++ret;
		}
		return ret;
	}
	// ͳ������pred������Ԫ����[first, last)�еĸ���
	template <class InputIterator, class Predicate>
	ptrdiff_t count_if(InputIterator first, InputIterator last, Predicate pred){ //pred��һ��ģ�����
		ptrdiff_t ret = 0;
		while (first != last) {
			if (pred(*first++))
				++ret;
		}
		return ret;
	}
};
struct IsOdd{
	bool operator()(int i){ 
		return ((i % 2) == 1);
	}
};
int main(){
	// ͳ��10��v1�г��ֵĴ���
	vector<int> v1{ 10, 20, 30, 10,30, 20, 10, 10, 20 };
	cout <<my::count(v1.begin(), v1.end(), 10) << endl;
	
	vector<int> v2{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ,13};
	cout << my::count_if(v2.begin(), v2.end(), IsOdd()) << endl;//��������isodd�����ĵ�ַ������pred�в�������ȷ������ָ��
	return 0;
}
//�º��� ʹ�÷������� ��ʵ���Ƕ���Ҳ�к������� ������������ŵ�����
/*
namespace my{
	template<class _Ty>
	struct plus{
		_Ty operator()(const _Ty& _Left,const _Ty& _Right){
			return (_Left+_Right);
		}
	};
};
int main(){
	my::plus<int> pl;
	minus<int> mu;
	cout<<pl(10,20)<<endl;
	//�ȼ��ڣ�
	cout<<pl.operator()(10,20)<<endl;
	
	cout<<mu(100,30)<<endl;
	return 0;
}


/*
//������
int main(){
	vector<int> iv={3,2,7,6,0,4,1,9,8,5};
	make_heap(iv.begin(),iv.end());
	auto it=iv.end();
	while(it!=iv.begin()){
		pop_heap(iv.begin(),it);
		it--;
	}
	for(const auto &e:iv)
		cout<<e<<" ";
	cout<<endl;
	return 0;
}
/*
//���ȼ�����

int main(){
	vector<int> iv={3,2,7,6,0,4,1,9,8,5};
	//priority_queue<int> pq;//�ײ��Ƕ� Ĭ���Ǵ��
	priority_queue<int,vector<int>,greater<int>> pq;
	for(const auto &e:iv){
		pq.push(e);
	}
	cout<<pq.top()<<endl;
	while(!pq.empty()){
		auto val=pq.top();
		pq.pop();
		cout<<val<<" ";
	}
	cout<<endl;
	return 0;
}

/*
int main(){
	queue<char> Q;
	Q.push('A');
	Q.push('1');
	Q.push('2');
	cout<<"size="<<Q.size()<<endl;
	cout<<"front="<<Q.front()<<endl;
	cout<<"back="<<Q.back()<<endl;
	return 0;
}
/*
int main(){
	stack<char> st;
	st.push('A');
	st.push('B');
	st.push('C');
	
	cout<<"st.size="<<st.size()<<endl;
	while(!st.empty()){
		char val=st.top();
		st.pop();
		cout<<val<<" ��ջ";
	}
	cout<<endl;
	return 0;
}
*/
