#include <iostream>
#include <cmath>
using namespace std;
class SeparateBlock{
    int n;      //n块
    int length; //块长
    int* pos;   //块序列
    int* left;  //块左端点
    int* right; //块右端点
    int* sum;   //块内和，可改为最值等
    int* lazy;  //懒标记，用于记录改动内容，不真实改动，等到要用改后数据时，从这里查看改动
    public:
        SeparateBlock(int n, int *arr){
            this->length = sqrt(n*1.0);
            this->n = this->length;
            if (n%this->length){
                this->n++;
            }
            left = new int[this->n];
            right = new int[this->n];
            for(int i=0; i<this->n; i++){
                left[i] = i*length;
                right[i] = (i+1)*length-1;
            }
            pos = new int[n];
            sum = new int[this->n];
            for(int i=0; i<this->n; i++){
                sum[i] = 0;
            }
            for(int i=0; i<this->n; i++){
                    for(int j=left[i]; j<=right[i]; j++){
                    pos[j] = i;
                    sum[i] += arr[j];
                }
            }
            lazy = new int[this->n];
            for(int i=0; i<this->n; i++){
                lazy[i] = 0;    //初始不发生改动
            }
        }
        void Update(int l, int r, int x, int *arr){   //x是变化量
            int posl = pos[l];
            int posr = pos[r];
            if (posl == posr){
                for(int i=l; i<=r; i++){
                    sum[posl] += x;
                    arr[l] += x;
                }
                return;
            }
            for(int i=posl; i<=posr; i++){
                if (i==posl){
                    for(int j=l; j<=right[i]; j++){
                        arr[j] += x;
                        sum[i] += x;
                    }
                    continue;
                }
                if (i==posr){
                    for(int j=left[i]; j<=r; j++){
                        arr[j] += x;
                        sum[i] += x;
                    }
                    continue;
                }
                /*真实改动就和直接改动复杂度一样了
                for(int j=left[i]; j<=right[i]; j++){
                    arr[j] += x;
                    sum[i] += x;
                }
                */
               lazy[i] += x;    //优化在改动
            }
        }
        int Sum(int l, int r, int *arr){
            int returnsum = 0;
            int posl = pos[l];
            int posr = pos[r];
            if (posl == posr){
                for(int i=l; i<=r; i++){
                    returnsum += arr[i];
                }
                return returnsum;
            } 
            for(int i=posl; i<=posr; i++){
                if (i==posl){
                    for(int j=l; j<=right[i]; j++){
                        returnsum += arr[j];
                    }
                    continue;
                }
                if (i==posr){
                    for(int j=left[i]; j<=r; j++){
                        returnsum += arr[j];
                    }
                    continue;
                }
                returnsum += sum[i] + lazy[i]*(right[i] - left[i] +1);
            }
            return returnsum;
        }
};
int main(){
    int arr[6] = {1,2,3,4,5,6};
    SeparateBlock sb(6,arr);
    cout<<sb.Sum(0,3,arr)<<endl;
    sb.Update(0,3,-1,arr);
    cout<<sb.Sum(0,3,arr)<<endl;
    cout<<sb.Sum(3,3,arr)<<endl;
    return 0;
}