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
	int index;
	int moreMat(int,int,const string&,const string&);
	bool flag = false;
	int p1;
	size_t sz1;
	int p2;
	size_t sz2;
	int p3;
	size_t sz3;
};
int Solution::moreMat(int p1,int p2,const string &s1,const string &s2){
	index = 0;
	while(p1<s1.size()&&s1[p1]==s2[p2]){
		++index;
		++p1;
		++p2;
	}
	return index;
}
bool Solution::check(const string&s1,const string&s2,const string&s3){
	int res;
	int tmp;
	while(1){
		if(p1==sz1||p2==sz2){
			if((p1+p2)==sz3){
				flag=true;
				return true;
			}
			else{
				if(p1==sz1){
					res = moreMat(p2,p3,s2,s3);
					p2 += res;
					p3 += res;
				}else{
					res = moreMat(p1,p3,s2,s3);
					p1 += res;
					p3 += res;
				}
				flag = true;
				if((p1+p2)==p3)return true;
				else return false;
			}
		}
		if(s2[p2]==s3[p3]||s1[p1]==s3[p3]){
			if(s2[p2]==s3[p3]&&s3[p3]==s1[p1]){
				res = moreMat(p1,p3,s1,s3);
				tmp = moreMat(p2,p3,s2,s3);
				if(res>tmp){
					p1+=res;
					p3+=res;
				}else{
					p2+=tmp;
					p2+=tmp;
				}
			}else{
				if(s2[p2]==s3[p3]){
					res = moreMat(p2,p3,s2,s3);
					p2 += res;
					p3 += res;
				}else{
					res = moreMat(p1,p3,s1,s3);
					p1 += res;
					p3 += res;
				}
			}
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
