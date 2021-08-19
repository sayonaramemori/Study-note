#include<string>
#include<iostream>
#include<set>

using namespace std;

class Solution {
public:
	typedef pair<int,int> stalen;
    int lengthOfLongestSubstring(string s) {
		dowork(s);
		return res;	
    }
private:
	set<char> tmp;
	int sz,len;
	int res;
	void init(const string &s);
	void dowork(const string& s);	
	void check(const int& pos,const string&s);
};

void Solution::init(const string &s){
	sz = s.size();
	res = 1;
	return;
}


void Solution::check(const int &pos,const string &s){
	tmp.clear();
	tmp.insert(s[pos]);
	for(int i=pos+1;i<sz;++i)
		if(tmp.insert(s[i]).second==false){
			len = i - pos;
			if(len>res)res = len;
			break;
		}
	return;
}
			

void Solution::dowork(const string &s){
	init(s);
	for(int i=0;i<sz;++i){
		check(i,s);
	}
	return;
}


int main(int argc,char *argv[]){
	Solution t;
	auto res = t.lengthOfLongestSubstring(argv[1]);
	cout<<"res is:  "<<res<<endl;
	return 0;
}
		
