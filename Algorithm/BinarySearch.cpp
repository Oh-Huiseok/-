#include <iostream>
#include <vector>
using namespace std;
void binsearch(int n, vector<int> &S, int x, int& loc){
    int low, high, mid;
    low = 1; high = n;
    loc = 0;
    while(low<=high && loc==0){
        mid = (low+high)/2;
        if(x==S[mid]){
            loc = mid;
            break;
        }
        else if(x<S[mid])
            high = mid-1;
        else
            low = mid+1;
    }
}
int main(){
    int n; cin>>n;
    vector<int>S(n+1);
    for(int i=1;i<=n;i++){
        cin>>S[i];
    }
    int x; cin>>x;
    int loc;

    binsearch(n, S, x, loc);

    cout << loc;
}