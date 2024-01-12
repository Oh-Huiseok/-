#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main(){
    string str;
    string ans;
    int len;
    double size;
    double rsize;

    getline(cin, str);
    len = str.length();
    size = ceil(len/3 + 0.5);

    if(len%3==0){
        int add, j=0;
        for(int i=0;i<size-1;i++){
            add = 0;
            add += (str[j]-48) * 4;
            j++;
            add += (str[j]-48) * 2;
            j++;
            add += (str[j]-48) * 1;
            j++;
            ans.push_back(char(add)+48);
        }
    }
    else if(len%3==1){
        int add, j=0;
        add = 0;
        add = (str[j]-48) * 1;
        j++;
        ans.push_back(char(add)+48);

        for(int i=0;i<size-1;i++){
            add = 0;
            add += (str[j]-48) * 4;
            j++;
            add += (str[j]-48) * 2;
            j++;
            add += (str[j]-48) * 1;
            j++;
            ans.push_back(char(add)+48);
        }
    }
    else{
        int add, j=0;
        add = 0;
        add += (str[j]-48) * 2;
        j++;
        add += (str[j]-48) * 1;
        j++;
        ans.push_back(char(add)+48);

        for(int i=0;i<size-1;i++){
            add = 0;
            add += (str[j]-48) * 4;
            j++;
            add += (str[j]-48) * 2;
            j++;
            add += (str[j]-48) * 1;
            j++;
            ans.push_back(char(add)+48);
        }
    }

    cout << ans << endl;

    return 0;
}
