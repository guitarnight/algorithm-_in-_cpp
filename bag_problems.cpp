#include <iostream>
#include <string>
using namespace std;
class Bags{
    int* max;           //最大价值数组,长为最大容量
    public:
        int ZeroneBag(int W, int n, int* v, int *w){
            max = new int[W+1];
            for(int j=0; j<=W; j++){
                max[j] = 0;
            }
            //从后向前，后面在前面为选择第i件物品前选择了第i件物品
            for(int i=1; i<=n; i++){
                for(int j=W; j>=0; j--){
                    if(j>=w[i] && max[j-w[i]]+v[i] > max[j]){
                        max[j] = max[j-w[i]]+v[i];
                    }
                }
            }
            return max[W];
        }
        int TotalBag(int W, int n, int* v, int* w){
            max = new int[W+1];
            for(int i=0; i<=W; i++){
                max[i] = 0;
            }
            /*
	    从前到后，前面选择第i件物品，后面还可以继续选，直到装不下
            for(int i=1; i<=n; i++){
                for(int j=0; j<=W; j++){
                    if(j>=w[i] && max[j-w[i]]+v[i]>max[j] ){
                        max[j] = max[j-w[i]] + v[i];
                    }
                }
            }
            */
            for(int i=1; i<=n; i++){
                for(int j=W; j>=0; j--){
                    //从后向前，每个容量从选择1个i物品到选择最多个i物品，实现装最多和价值最大
                    int k = 1;
                    while(j-w[i]*k >= 0){
                        if(max[j-w[i]*k]+v[i]*k > max[j]){
                            max[j] = max[j-w[i]*k]+k*v[i];
                        }
                        k++;
                    }
                }
            }
            return max[W];
        }
        int MultipleBag(int W, int n, int* num, int* v, int* w){
            max = new int[W+1];
            for(int j=0; j<=W; j++){
                max[j] = 0;
            }
            for(int i=1; i<=n; i++){
                for(int j=W; j>=0; j--){
                    int k=1;
                    while(j-k*w[i] >=0 && k<=num[i] && max[j-k*w[i]]+k*v[i] > max[j]){
                        max[j] = max[j-k*w[i]]+k*v[i];
                        k++;
                    }
                }
            }
            return max[W];
        }
        int GroupsBag(int W, int n, int*num, int** v,int** w){
            max = new int[W+1];
            for(int i=0; i<=W; i++){
                max[i] = 0;
            }
            for(int i=1; i<=n; i++){
                for(int j=W; j>=0; j--){
                    for(int k=1; k<=num[i]; k++){
                       if (j>=w[i][k] && max[j-w[i][k]]+v[i][k]>max[j]){
                           max[j] = max[j-w[i][k]]+v[i][k];
                       }
                    }
                }
            }
            return max[W];
        }
        int MixBag(int W, int n, int* num, int* v, int* w){
            max = new int[W+1];
            for(int i=0; i<=W; i++){
                max[i] = 0;
            }
            for(int i=1; i<=n; i++){
                if (num[i] == 1){
                    for(int j=W; j>=0; j--){
                        if(j>=w[i] && max[j-w[i]]+v[i]>max[j]){
                            max[j] = max[j-w[i]]+v[i];
                        }
	                }
                }else if(num[i] == 0){
                    for(int j=0; j<=W; j++){
                        if (j>=w[i] && max[j-w[i]]+v[i]>max[j]){
                            max[j] = max[j-w[i]]+v[i];
                        }
                    }
            	}else{
                    for(int j=W; j>=0; j--){
                        int k=1;
                        while(k<=num[i] && j>=k*w[i] && max[j-k*w[i]]+k*v[i] > max[j]){
                            max[j] = max[j-k*w[i]]+k*v[i];    
                            k++;
                        }
                    }
                }
            }
            return max[W];
        }
};
int main(){
    int W = 10;
	int n = 5;
	int w[6] = {0,2,5,4,2,3};
	int v[6] = {0,6,3,5,4,6};
	int num1[6] = {0,1,1,1,1,1}; 
	int num2[6] = {0,1,2,3,4,5};
	int num3[6] = {0,0,0,0,0,0};
    Bags bag;
    cout<<bag.ZeroneBag(W,n,v,w)<<endl;
    cout<<bag.TotalBag(W,n,v,w)<<endl;
    cout<<bag.MultipleBag(W,n,num1,v,w)<<endl;
    cout<<bag.MultipleBag(W,n,num2,v,w)<<endl;
    cout<<bag.MultipleBag(W,n,num3,v,w)<<endl;			//多重背包中0即是0个 
    cout<<bag.MixBag(W,n,num1,v,w)<<endl;;
    cout<<bag.MixBag(W,n,num2,v,w)<<endl;;
    cout<<bag.MixBag(W,n,num3,v,w)<<endl;;			//混合背包中0表示无限个 
	int **w2 = new int*[n+1];
	for(int i=0; i<=n; i++){
		w2[i] = new int[num2[i]+1];
	}
	for(int i=0; i<=n; i++){
		for(int j=0; j<=num2[i]; j++){
			w2[i][j] = j;
		}
	}	
	int **v2 = new int*[n+1];
	for(int i=0; i<=n; i++){
		v2[i] = new int[num2[i]+1];
	}
	for(int i=0; i<=n; i++){
		for(int j=0; j<=num2[i]; j++){
			v2[i][j] = j;
		}
	}	
	cout<<bag.GroupsBag(W,n,num2,v2,w2)<<endl;
	return 0;
}
