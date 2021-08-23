#include<vector>
#include<iostream>
#include<map>

using namespace std;


class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
		init(nums);
		dowork(target);
		return res;
    }
private:
	size_t sz;
	map<int,int> temp;
	vector<int> res;
	void dowork(int target);
	void init(const vector<int>& nums);
};
void Solution::init(const vector<int>& nums){
	sz = nums.size();
	res.resize(2,0);
	for(int i=0;i<sz;++i)
		temp[nums[i]] = i;
}
void Solution::dowork(int target){
	int tmp;
	auto end = temp.end();
	for(auto &v:temp){
		tmp = target - v.first;
		if(temp.find(tmp)!=end){
			res[0] = temp[tmp];
			res[1] = v.second;
			return;
		}
	}
}

int main(){
	vector<int> tmp{1,2,3,4,5};
	Solution t;
	auto res = t.twoSum(tmp,3);
	cout<<"res:[ "<<res[0]<<","<<res[1]<<"]"<<endl;	
	return 0;
}
