#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main(){
    string str;
    string ans;
    int len;
    int num;
    getline(cin, str);
    len = str.length();

    for(int i=0;i<len;i++){
        num = str[i]-48;
        if(num == 7){
            ans.push_back('1');
            ans.push_back('1');
            ans.push_back('1');
        }
        else if(num == 6){
            ans.push_back('1');
            ans.push_back('1');
            ans.push_back('0');
        }
        else if(num==5){
            ans.push_back('1');
            ans.push_back('0');
            ans.push_back('1');
        }
        else if(num==4){
            ans.push_back('1');
            ans.push_back('0');
            ans.push_back('0');
        }
        else if(num==3){
            ans.push_back('0');
            ans.push_back('1');
            ans.push_back('1');
        }
        else if(num==2){
            ans.push_back('0');
            ans.push_back('1');
            ans.push_back('0');
        }
        else if(num==1){
            ans.push_back('0');
            ans.push_back('0');
            ans.push_back('1');
        }
        else{
            ans.push_back('0');
            ans.push_back('0');
            ans.push_back('0');
        }
    }

    while(1){
        if(ans.front()=='0' && ans.length()>1)
            ans.erase(0,1);
        else
            break;
    }

    cout << ans << endl;

    return 0;
}
