#include <iostream>
#include <string>
using namespace std;
class Kmp{
    string s;
    int* next;
    public:
        Kmp(string a){
            this->s = a;
            next = new int[a.length()];
            for(int i=0; i<s.length(); i++){
                next[i] = 0;
            }
            next[0] = -1;
            int i=0, j=-1;
            while(i<s.length()){
                if (j==-1 || s[i]==s[j]){
                    i++, j++;
                    if(s[i] == s[j]){
                        next[i] = next[j];
                    }else{
                        next[i] = j;
                    }
                }else{
                    j = next[j];
                }
            }
        }
        int Compare(string a, int pos){
            int slen = s.length();
            int alen = a.length();
            int i=0, j=0;
            while(i<slen && j<alen){
                if (i==-1 || s[i]==a[j]){
                    i++, j++;
                }else{
                    i = next[i];
                }
            }
            if(i >= slen){
                return j-slen;
            }else{
                return -1;
            }
        }
        void Show(){
            cout<<s<<endl;
            for(int i=0; i<s.length(); i++){
                cout<<next[i]<<" ";
            }
            cout<<endl;
        }
};
int main(){
    Kmp kmp("abaabe");
    kmp.Show();
    cout<<kmp.Compare("abaababaaabe",0)<<endl;
    cout<<kmp.Compare("abaababaabe",0)<<endl;
    return 0;
}