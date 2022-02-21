#include <iostream>
#include <cmath>
class Tree{
    public:
        int l;
        int r;
        int mx;
        Tree():
            l(0),
            r(0),
            mx(0){}
};
class SegmentTree{
    int n = 0;
    Tree* tree = NULL;
    public:
        void init(int i, int l, int r, int *arr){//给定元素个数，线段树已经画好，lr已经确定，求节点mx即可
            tree[i].l = l;
            tree[i].r = r;
            if (l == r){
                tree[i].mx = arr[l];    //arr和tree的0号元素都不存节点
                return;
            }
            init(2*i,l,(r+l)/2,arr);
            init(2*i+1,(l+r)/2+1,r,arr);
            tree[i].mx = tree[2*i].mx > tree[2*i+1].mx ? tree[2*i].mx : tree[2*i+1].mx;
        }
        SegmentTree(int* arr,int n){
            tree = new Tree[2*n];   //满二叉树节点个数，底层n个叶子，总共2*n-1
            init(1,1,n,arr);
        }
        void update(int i, int j, int num){
            if (tree[i].r = tree[i].l && tree[i].l == j){
                tree[i].mx = num;
                return;
            }
            int mid = (tree[i].l+tree[i].r)/2;
            if (i < mid){
                update(2*i,j,num);
            }else{
                update(2*i+1,j,num);
            }
            tree[i].mx = tree[2*i].mx>tree[2*i+1].mx?tree[2*i].mx:tree[2*i+1].mx;
        }
        int query(int l, int r, int k){
            if (tree[k].l <= l && tree[k].r >=r){  //l~r区间分块，各求最值
                return tree[k].mx;  
            }
            int max = INT_MIN;
            int mid = (tree[k].l + tree[k].r)/2;
            if (l <= mid){     //左子树内必有部分区间
                int tmp = query(l,r,2*k);
                max = max > tmp? max: tmp;
            }
            if (r >= mid){      //右子树内必有部分区间
                int tmp = query(l,r,2*k+1);
                max = max>tmp?max:tmp;
            }
            return max;
        }
};
int main(){
    return 0;
}