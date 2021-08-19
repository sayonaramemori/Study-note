#include<string>
#include<iostream>
#include<algorithm>
#include<map>
using namespace std;

class Solution {
public:
	typedef pair<int,int> prelen;
    string longestPalindrome(string s) {
		init(s);
		return workAtMid(s);
    }
private:
	prelen longestRes;
	int mid,sz,tail;
	int pre,lat,len,times;
	void init(const string &s);
	void settimes(const int &pos,bool type);
	void checkBetter(const int &pre,const int &lat);
	void findByone(const string &s,const int &pos,bool side);
	void findByTwo(const string &s,const int &pos,bool side);
	string workAtMid(const string&s);
};
string Solution::workAtMid(const string&s){
	findByTwo(s,0,true);
	for(int i=1;i<mid;++i){
		findByone(s,i,true);
		findByTwo(s,i,true);
	}
	for(int i=mid;i<tail;++i){
		findByone(s,i,false);
		findByTwo(s,i,false);
	}
	return s.substr(longestRes.first+1,longestRes.second);
}
void Solution::init(const string&s){
    sz = s.size(); 
	tail = sz - 1;
	mid = sz/2;
	longestRes = {-1,1}; 
}

inline void Solution::settimes(const int& pos,bool type){
	if(type)
		times = tail - pos;
	else
		times = tail - pos;
}

void Solution::checkBetter(const int& pre,const int& lat){
	len = lat - pre -1;
	if(len>longestRes.second)
		longestRes = {pre,len};
	return;
}

void Solution::findByone(const string &s,const int &pos,bool side){
	pre = lat = pos;
	if(side){
		for(int i=0;i<pos;++i){
			if(s[--pre]==s[++lat])continue;
			else break;
		}
		if(pre==0&&s[pre]==s[lat]){
			--pre;
			++lat;
		}
	}
	else{
		settimes(pos,true);
		for(int i=0;i<times;++i){
			if(s[--pre]==s[++lat])continue;
			else break;
		}
		if(lat==tail&&s[pre]==s[lat]){
			--pre;
			++lat;
		}
	}
	if(pre+2==lat)return;
	checkBetter(pre,lat);
}

void Solution::findByTwo(const string &s,const int &pos,bool side){
	pre = pos;
	lat = pos + 1;
	if(s[pre]!=s[lat])return;
	if(side){
		for(int i=0;i<pos;++i){
			if(s[--pre]==s[++lat])continue;
			else break;
		}
		if(pre==0&&s[pre]==s[lat]){
			--pre;
			++lat;
		}
	}
	else{
		settimes(pos,false);
		for(int i=0;i<times;++i){
			if(s[--pre]==s[++lat])continue;
			else break;
		}
		if(lat==tail&&s[pre]==s[lat]){
			--pre;
			++lat;
		}
	}
	checkBetter(pre,lat);
}

		
int main(){
	Solution t;
	cout<<"The longest is:  "<<t.longestPalindrome("cbb6")<<endl;
	return 0;
}