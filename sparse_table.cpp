#include <iostream>
#include <cmath>
using namespace std;
class SparseTable{
    int n = 0;
    int **table = NULL;
    public:
        SparseTable(int n, int* arr){
            this->n = log(n)/log(2.0);
            table = new int*[n];
            for(int i=0; i<n; i++){
                table[i] = new int[this->n+1];
            }
            for(int i=0; i<n; i++){
            	for(int j=0; j<=this->n; j++){
            		table[i][j] = 0;
				}
			}
            for(int i=0; i<n; i++){
                table[i][0] = arr[i];
			}
            for(int j=1; j<=this->n; j++){	//后行 
                for(int i=0; i<n; i++){	//先列 
                    if(i+(1<<j)-1<n){
                        table[i][j] = table[i][j-1]>table[i+(1<<(j-1))][j-1]?table[i][j-1]:table[i+(1<<(j-1))][j-1];
                    }
                }
            }
        }
        int ST_query(int l, int r){
        	l--;
        	r--;
            int length = log(r-l+1)/log(2.0);
            return table[l][length]>table[r-(1<<(length))+1][length]?table[l][length]:table[r-(1<<(length))+1][length];
        }
        void show(int n){
        	for(int i=0; i<n; i++){
        		for(int j=0; j<=this->n; j++){
        			cout<<table[i][j]<<" ";
				}
				cout<<endl;
			}
		}
};
int main(){
    int arr[10] = {5,3,7,2,12,1,6,4,8,15};
	SparseTable st(10,arr);
    cout<<st.ST_query(3,8)<<endl;
    st.show(10); 
    return 0;
}