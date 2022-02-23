#include <iostream>
#include <string>
using namespace std;
class TrieTree{
    int deep;           		//当前已用节点数，和单词个数相关 
    int trie[50][26];                   //每个节点26字母，假设最多50节点 
    int *end;                           //一个单词一个end
    public: 
    TrieTree(){
        deep = 1;
        for(int i = 0; i<50; i++){
            for(int j=0; j<26; j++){
                trie[i][j] = 0;
            }
        }
        end = new int[50];
        for(int i=0; i<50; i++){
            end[i] = 0;
        }
    }
    void Push(string s){
        int length = s.length();
        int p = 1;                      //从trie[1][]开始存储
        for(int i=0; i<length; i++){
            int num = s[i] - 'a';
            if (!trie[p][num]){
                trie[p][num] = ++deep;  //分叉，新建节点
            }
            p = trie[p][num];           //到下一个节点
        }
        end[p] = 1;                     //end[当前deep]标记单词结束
    }
    bool Search(string s){
        int length = s.length();
        int p = 1;
        for(int i=0; i<length; i++){
            p = trie[p][s[i] - 'a'];
            if (!p){                    //是否中断
                return false;
            }
        }
        return end[p];                  //是否结尾
    }
};
int main(){
	string s1("bike");
	string s2 = "bin";
	TrieTree tt;
    //没参数别加括号    TrieTree tt();
	tt.Push(s1);
	tt.Push(s2);
	tt.Push("yes");
	cout<<tt.Search("bike")<<endl;
	cout<<tt.Search("bin")<<endl;
	cout<<tt.Search("yes")<<endl;
	
	cout<<tt.Search("fly")<<endl;
	cout<<tt.Search("bing")<<endl;
	cout<<tt.Search("bi")<<endl;
    return 0;
}
