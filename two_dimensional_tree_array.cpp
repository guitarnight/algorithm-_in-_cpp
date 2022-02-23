#include <iostream>
#include <cmath>
using namespace std;
class TwodTreeArray{
    int m;
    int n;
    int** tree = NULL;
    public:
        TwodTreeArray(int m, int n, int (*arr)[4]){
            this->m = m;  //行列号与分块有关，只能从1开始数
            this->n = n;
            tree = new int*[m+1];
            for(int i=0; i<=m; i++){
                tree[i] = new int[n+1];
            }
            for(int i=0; i<=this->m; i++){
            	for(int j=0; j<=this->n; j++){
            		tree[i][j] = 0;
				}
			}
            for(int i=1; i<=m; i++){
                for(int j=1; j<=n; j++){
                    int lengthm = (-i)&i;
                    int lengthn = (-j)&j;
                    for(int l=i; l>i-lengthm; l--){
                        for(int k=j; k>j-lengthn; k--){
                            tree[i][j] += arr[l-1][k-1];
                        }
                    }
                }
            }
        }
        int Sum(int x1, int y1){ 
            int sum = 0;  
            for(int x=x1+1;x>0;x-=(-x)&x){		//5
                for(int y=y1+1;y>0;y-=(-y)&y){	//4
                    sum += tree[x][y];	//10 
                }
            }
            return sum;
        }
        int SectionSum(int x1, int y1, int x2, int y2){
            return Sum(x2,y2) - Sum(x1-1,y2) - Sum(x2,y1-1) + Sum(x1-1,y1-1); 
        }
        void Update(int x, int y, int dif){     //dif是变化量
            x++;
            y++;
            for(x;x<=this->m;x+=(-x)&x){
                for(y;y<=this->n;y+=(-y)&y){
                    tree[x][y] += dif;
                }
            }
        }
        void Show(){
        	for(int i=1; i<=this->m; i++){
        		for(int j=1; j<=this->n; j++){
        			cout<<tree[i][j]<<" ";
				}
				cout<<endl;
			}
		}
};
int main(){
    int arr[5][4] = {{1,2,3,4},
                     {1,2,3,4},
                     {1,2,3,4},
                     {1,2,3,4},
                     {1,2,3,4}};
    TwodTreeArray treearray(5,4,arr);	//二维数组名是一个数组指针，指向第一行 
	treearray.Show();
	cout<<treearray.Sum(4,3)<<endl;
	cout<<treearray.Sum(2,2)<<endl;
	cout<<treearray.SectionSum(2,2,3,3)<<endl;	//矩阵两顶点 
	cout<<treearray.SectionSum(2,2,4,3)<<endl;
    return 0;
}