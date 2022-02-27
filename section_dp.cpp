#include <iostream>
#include <string>
#include <string.h>
using namespace std;
int main(){
    int n=0, m=0;
    cin>>n>>m;
    string s;
    cin>>s;
    int add = 0, del = 0;
    int* cost = new int[n];
    for(int i=0; i<n; i++){
        char num = 'a';
        cin>>num>>add>>del;
        cost[num-'a'] = add < del ? add :del;
    }
    int **dp = new int*[s.length()];
    for(int i=0; i<s.length(); i++){
        dp[i] = new int[s.length()];
    }
    //memset(dp,0,sizeof(dp)); 数组是连续空间，指针是分散空间
    for(int i=0; i<s.length(); i++){
        for(int j=0; j<s.length(); j++){
            dp[i][j] = 0;
        }
    }
    for(int i=s.length()-1; i>=0; i--){             //起点
        for(int j=i+1; j<s.length(); j++){          //终点
            if(s[i] == s[j]){                       //与起点终点联系密切的区间递推关系
                dp[i][j] = dp[i+1][j-1];            
            }else{
                dp[i][j] = min(dp[i+1][j]+cost[s[i]-'a'],dp[i][j-1]+cost[s[j]-'a']);
            }
        }
    }
    cout<<dp[0][s.length()-1]<<endl;
    return 0;
}
/*
for (int len = 1; len <= n; ++len) {                //长度，与区间长度联系密切的递推关系
    for (int l = 1; l + len - 1 <= n; ++l) {        //起点
        int r = l + len - 1;                        //终点
        if (len == 1 || len == 2) {                 //ij无过度点
            f[l][r] = 0;                
            continue;
        }
        f[l][r] = 1e9;                              //ij有过度点，求f[l][r]min则初始化为inf为max
        for (int k = l + 1; k < r; ++k) {           //起点到终点之间短到长二分
            int v = f[l][k] + f[k][r] + a[l] * a[k] * a[r];
            f[l][r] = min(f[l][r], v); 
        }
    }
}
*/
