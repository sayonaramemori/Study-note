#include<string>
#include<iostream>
#include<set>
#include<algorithm>
#include<vector>

using namespace std;

class Solution {
public:
	typedef pair<int,int> poslen;
    int lengthOfLongestSubstring(string s) {
		if(s.empty())return 0;
		if((sz=s.size())==1)return 1;
		dowork(s);
		return res;	
    }
private:
	void cut(const string &s);
	vector<poslen> record;
	set<char> tmp;
	int sz,len,borde;
	int res;
	void init(const string &s);
	void dowork(const string& s);	
	void rangeScan(const poslen&,const string &s);
	void check(const int& pos,const string&s);
};

inline bool mycompare(Solution::poslen &lhs,Solution::poslen &rhs){
	return lhs.second>rhs.second;
}

void Solution::cut(const string &s){
	int pre = 0;
	int index = 1;
	for(int i=0;i<borde;++i,++index){
		if(s[i]==s[index]){
			record.push_back({pre,index-pre});
			pre = index;
		}else continue;
	}
	record.push_back({pre,index-pre});
	sort(record.begin(),record.end(),mycompare);
}

inline void Solution::init(const string &s){
	res = 1;
	borde = sz - 1;
	return;
}

void Solution::rangeScan(const poslen& p,const string &s){
	int times = 0;
	while(times<p.second){
		check(p.first+times,s);
		++times;
	}
}

void Solution::check(const int &pos,const string &s){
	tmp.clear();
	tmp.insert(s[pos]);
	for(int i=pos+1;i<sz;++i)
		if(tmp.insert(s[i]).second==false){
			len = i - pos;
			if(len>res)res = len;
			break;
		}else if(i == borde){
				len = i - pos + 1;
				if(len>res)res = len;
				break;
			}			
	return;
}
			
void Solution::dowork(const string &s){
	init(s);
	cut(s);
	int rsz = record.size();
	int brsz = rsz - 1;
	for(int i=0;i<rsz;++i){
		rangeScan(record[i],s);
		if(i<brsz&&res>=record[i+1].second)break;
	}
	return;
}


int main(int argc,char *argv[]){
	Solution t;
	auto res = t.lengthOfLongestSubstring(argv[1]);
	cout<<"res is:  "<<res<<endl;
	return 0;
}
		
