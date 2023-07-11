#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


fstream file;
fstream file2;
int main(){

    file.open("test",ios::out);
    // file2.open("test2",ios::out);
    

    if(!file){
        cout<<"Error in opening file"<<endl;
        return 0;
    }
    ll n;
    cin >> n;
    // vector<ll> arr;
    for(int i=0;i<n;i++){
        ll temp = rand()%100000;
        // arr.push_back(temp);
        file<<temp<<"\n";
    }
    // sort(arr.begin(),arr.end());
    // for(int i=0;i<n;i++){
    //     file2<<arr[i]<<"\n";
    // }

    // file2.close();

    file.close();

    return 0;
}
