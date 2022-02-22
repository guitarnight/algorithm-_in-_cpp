#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
class OnedTreeArray{
    int n;
    int* tree = NULL;
    public:
        OnedTreeArray(int n, int *arr){
            this->n = n;
            this->tree = new int[this->n + 1];  //树状数组下标和长度有关，只能从1开始记录
            //memset(tree,sizeof(tree),0); memset居然不准？ 
			for(int i=0; i<=this->n; i++){
				tree[i] = 0;
			}
			for(int i=1; i<=n; i++){
                int length = (-1*i)&i; 
                for (int j=0; j<length; j++){
                	if (i-1-j >= 0){
                		tree[i] += arr[i-1-j];	
					}
                }
            }
        }
        int Sum(int i){
            i++;
            int sum = 0;
            while(i>0){
                sum += tree[i];
                i -= ((-1*i)&i);
            }
            return sum;
        }
        void Update(int i, int x){  //x是变化量
            i++;
            while(i<=this->n){
                tree[i] += x;
                i += ((-i)&i);
            }
        }
        int SectionSum(int x, int y){
            return Sum(y) - Sum(x);
        }
        void Show(){
        	for(int i=1; i<=this->n; i++){
        		cout<<tree[i]<<" ";
			}
			cout<<endl;
		}
};
int main(){
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    OnedTreeArray treearray(10,arr);
    treearray.Show();
    cout<<treearray.Sum(4)<<endl;	//传参是arr的下标，tree需要+1	
    treearray.Update(0,-1);  		//arr[0] = 1 + -1;
    cout<<treearray.Sum(4)<<endl;	//arr[0]+arr[1]+arr[2]+arr[3]+arr[4]
    cout<<treearray.SectionSum(0,9)<<endl;
    return 0;
}