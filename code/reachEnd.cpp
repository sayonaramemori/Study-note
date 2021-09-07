#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;


class Solution{
public:
    bool canJump(const vector<int> &nums){
        curIndex = nums.size()-1;
        return findIndex(nums);
    }
private:
    bool findIndex(const vector<int> &nums);
    vector<int> tmp;
    int curIndex;
};


bool Solution::findIndex(const vector<int> &nums){
    int temp;
    for(int i=0;i<curIndex;++i){
        temp = i+nums[i];
        tmp.push_back(temp);
        if(temp>=curIndex){
            if(i==0){
                return true;
            }else{
                curIndex = i;
                tmp.clear();
                return findIndex(nums);
            }
        }
    }
    return false;
}

int main(){
    Solution t;
    if(t.canJump({3,2,1,1,4}))cout<<"true"<<endl;
    else cout<<"false"<<endl;
    return 0;
}
