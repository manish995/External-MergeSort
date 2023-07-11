#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


fstream file;

int main(int agrc,char* argv[]){

    file.open(argv[1],ios::in);
    // file2.open("test2",ios::out);
    

    if(!file){
        cout<<"Error in opening file"<<endl;
        return 0;
    }
   
    string tp;
    ll prev=-1;
    int i=0;
    int breaks = 0;
    while(getline(file, tp)){ 
        i++;
        if(stoll(tp)>=prev){
            prev= stoll(tp);
        }
        else{
            cout<<"File is not sorted at: "<<i<<endl;
            breaks++;
            prev=stoll(tp);
        }
        //  cout << tp << "\n"; 
    }
    
    
    

    file.close();

    return 0;
}
