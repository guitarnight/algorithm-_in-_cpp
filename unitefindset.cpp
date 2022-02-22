#include <iostream>
using namespace std;
class BlockStack{
    int n;
    int* root = NULL;
    int* count = NULL;
    int* below = NULL;
    public:
        BlockStack(int num){
            this->n = num;
            root = new int[num];
            for(int i=0; i<this->n; i++){
                root[i] = i;
            }
            count = new int[num];
            for(int i=0; i<this->n; i++){
                count[i] = 1;
            }
            below = new int[num];
            for(int i=0; i<this->n; i++){
                below[i] = 0;
            }
        }
        int find(int x){
            if (root[x] == x){  //后来未移动根则直接结束，不改below
                return x;
            }
            root[x] = find(root[x]);  //中间方块也都改动完成
            below[x] += below[root[x]];
            return root[x];     //每一层都要有返回，才能归
        }
        void unite(int x, int y){
            int rootx = find(x);
            int rooty = find(y);
            below[rootx] += count[rooty];
            count[rooty] += count[rootx];
            root[rootx] = rooty;
        }
        int Cbelow(int x){
            return below[x];
        }
};
int main(){
    int m = 0, n = 0;
    while(cin>>m && m){
        BlockStack bs(m);
        cin>>n;
        for(int i=0; i<n; i++){
            char order = 'M';
            cin >> order;
            if (order == 'M' || order == 'm'){
                int p = 0, q= 0;
                cin>>p;
                cin>>q;
                bs.unite(p-1,q-1);
            }else{
                int p = 0;
                cin >> p;
                bs.find(p-1);
                cout<<bs.Cbelow(p-1)<<endl;
            }
        }
    }
}