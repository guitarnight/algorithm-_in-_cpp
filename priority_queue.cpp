#include <iostream>

using namespace std;
class Priority_queue{
        int *tree = NULL;
        int n;
    public:
        Priority_queue(int num, int* &arr){
            this->n = num;
            //tree = new int[this->n+1];
            tree = new int[100];
            tree[0] = num;
            for(int i=1; i<=this->n; i++){
                tree[i] = arr[i];
            }
        }
        int Sink(){
            int i = 1;
            while(2*i<=n){  //最后一个节点可能是左也可能是右
                int j = 2*i;
                if (j<n && tree[j] < tree[j+1]){
                    j = j+1;
                }
                if (tree[i] >= tree[j]){
                    break;
                }else{
                    tree[i] = tree[i] ^ tree[j];
                    tree[j] = tree[i] ^ tree[j];
                    tree[i] = tree[i] ^ tree[j];
                    i = j;
                }
            }
            return i;
        }
        int pop(){
            int tmp = tree[1];
            tree[1] = tree[this->n];
            this->n--;
            int order = Sink();
            return tmp;
        }
        int Swim(int num){
            while(num >1 && tree[num] > tree[num/2]){
                tree[num] = tree[num] ^ tree[num/2];
                tree[num/2] = tree[num] ^ tree[num/2];
                tree[num] = tree[num] ^ tree[num/2];
                num /= 2;
            }
            return num;
        }
        int push(int x){
            this->n++;
            tree[this->n] = x;
            return Swim(this->n);
        }
        void show(){
            for(int i=1; i<=this->n; i++){
                cout<<this->tree[i]<<" ";
            }
            cout<<endl;
        }
};
int main(){
    return 0;
}