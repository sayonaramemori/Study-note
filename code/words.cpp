#include<string>
#include<map>
#include<set>
#include<vector>
using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
		init(s,words);
		if(record.size()<sz)return {};

    }
private:
	void init(const string &s,const vector<string>&words);
	void dowork(const string &s,vector<string> &words);
	int check(map<int,int>::iterator it);
	vector<int> res;
	map<int,int> startype;
	vector<int> sz;
	int size;
};
void Solution::dowork(const string &s,vector<string> &words){
	int num = 1 + startype.size() - size;
	set<int> tmp;
	bool flag = true;
	auto begin=startype.begin();
	for(int i=0;i<num;++i){
		tmp.clear();
		for(int j=i;j<size;++j){
			if(tmp.insert((begin+j)->second).second==false){
				flag = false;
				break;
			}
		}
		if(flag)check(begin+i);
		else flag = true;
	}
}
void Solution::init(const string &s,const vector<string> &words){
	size = words.size();
	int pos;
	for(int i=0;i<size;++i){
		sz.push_back(words[i].size());
		while((pos = s.find(words[i]))!=string::npos)startype[pos] = i;
	}
}
