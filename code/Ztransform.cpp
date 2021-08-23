#include<string>
#include<iostream>
using namespace std;
class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows==1)return s;
        string res = s;
        int i=0;
        auto sz = s.size();
		int index = -1;
		int row = numRows - 1;
        int wild = 2*row;
		//handle first line
		for(;i<sz;i+=wild)
			res[++index] = s[i];
		int j=0;
		int left;
		int right;
        for(i=1;i<row;++i){
			left = wild - 2*i;
			for(j=i;j<sz;){
				res[++index] = s[j];	
				if((right=j+left)<sz)
					res[++index] = s[right];
				j += wild;
			}
        }
		for(i=row;i<sz;i+=wild)
			res[++index] = s[i];
		return res;
    }
};
int main(){
	Solution t;
	auto res = t.convert(string("PAYPALISHIRING"),3);
	cout<<"res is:"<<res<<endl;
	return 0;
}
