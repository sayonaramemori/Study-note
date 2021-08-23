#include<string>
#include<iostream>
#include<algorithm>
using namespace std;
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
		sz1 = s1.size();
		sz2 = s2.size();
		sz3 = s3.size();
		if(sz1+sz2!=sz3)return false;
		p1 = p2 = p3 = 0;
		bool res;
		while(res = check(s1,s2,s3))if(flag)break;
		return res;
    }
private:
	bool check(const string&s1,const string&s2,const string&s3);
	int moreMat(bool isOne,int&,int&,const string&,const string&);
	bool flag = false;
	int p1;
	size_t sz1;
	int p2;
	size_t sz2;
	int p3;
	size_t sz3;
};
void Solution::moreMat(bool isOne,int &m,int &s,const string& ms,const string &s3){
	++m;
	++s;
	if(isOne){
		if(m!=sz1&&s!=sz3)
			if(ms[m]==s3[s])moreMat(true,m,s,ms,s3);
	}else{
		if(m!=sz2&&s!=sz3)
			if(ms[m]==s3[s])moreMat(false,m,s,ms,s3);
	}
	return;
}
bool Solution::check(const string&s1,const string&s2,const string&s3){
	while(1){
		if(p1==sz1||p2==sz2||p3==sz3){
			if(p1==sz1&&p2==sz2&&p3==sz3&&(p1+p2)==p3){
				flag=true;
				return true;
			}
			else{
				if(p1==sz1){
					moreMat(true,p2,p3,s2,s3);
					continue;
				}else{
					moreMat(false,p1,p3,s2,s3);
					continue;
				}
			}
		}
		if(s1[p1]==s3[p3]){
			moreMat(true,p1,p3,s1,s3);
			continue;
		}
		if(s2[p2]==s3[p3]){
			moreMat(false,p2,p3,s2,s3);
			continue;
		}
		return false;
	}
	return false;
}


int main(){
	string s1 = "aabcc";
	string s2 = "dbbca";
	string s3 = "aadbbcbcac";
	Solution t;
	auto res = t.isInterleave(s1,s2,s3);
	if(res)cout<<"res:true"<<endl;
	else cout<<"res:false"<<endl;
	return 0;
}
