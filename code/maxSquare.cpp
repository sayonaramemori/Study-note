#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;
class Solution {
public:
    int largestrectanglearea(vector<int>& heights) {
		if(heights.empty())return 0;
		dowork(heights);
		return maxSquare;
    }
private:
	void maxThrough(vector<int>& vec,int pos);
	void dowork(vector<int>& vec);
	int sz;
	int maxSquare;
	int curWild;
	int index;
};
void Solution::dowork(vector<int>& vec){
	maxSquare = 0;
	sz = vec.size();
	int tmp;
	for(int i=0;i<sz;++i){
		maxThrough(vec,i);
		if((tmp=vec[i]*curWild)>maxSquare)maxSquare = tmp;
	}
}

void Solution::maxThrough(vector<int>& vec,int pos){
	curWild = 1;
	for(index=pos+1;index<sz;++index){
		if(vec[pos]<=vec[index])++curWild;
		else break;
	}
	for(index=pos-1;index>=0;--index){
		if(vec[pos]<=vec[index])++curWild;
		else break;
	}
	return;
}

	
	
int main(){
Solution r;
vector<int> tmp{1,2,4,5,5};
cout<<r.largestrectanglearea(tmp)<<endl;
return 0;
}


