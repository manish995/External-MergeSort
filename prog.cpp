#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


fstream infile;
ll m,k,n,b;
ll key_in_one_blk;
ll total_num_blocks;

fstream outfile;
fstream outfile1;
fstream outfile2;



ll num_seeks_sort_pass = 0;
ll num_blk_transfer_sort_pass = 0;
ll num_seeks_merge_pass =0;
ll num_blk_transfer_merge_pass = 0;
ll overall_num_seeks = 0;
ll overall_num_blk_transfers = 0;
ll total_num_of_pass=0;
ll seeks_in_one_pass=0;
ll transfers_in_one_pass=0;


vector<ll> in_vec;
ll in_blk_ptr=0;
vector<ll> out_vec;
ll out_blk_ptr=0;


// file containing the keys (each line contains a single key),
// size of available memory, m, in number of blocks,
// size of each key, k, in bytes,
// total number of keys, n, and
// disk block size, b, in bytes.


void print_vec(vector<ll> vec){
    for(ll i=0;i<vec.size();i++){
        cout<<vec[i]<<" ";
    }
    cout<<endl;
}

void read_comp_file(vector<ll> &vec, fstream &file){
    if(file){
        ll i=0;
        while(!file.eof() && i<n){
            ll temp;
            file>>vec[i];
            i++;
        }
    }
    else{
         cout<<"File ptr is null"<<endl;
    }
    print_vec(vec);
    // cout<<vec.size()<<endl;
}


void write_comp_file(vector<ll> vec, fstream &file){

    if(file){
        for(ll i=0;i<vec.size();i++){
            file<<vec[i]<<"\n";
        }
    }
    else{
        cout<<"File ptr is null"<<endl;
    }
}


ll read_in_memory(vector<ll> &memory){
    cout<<"read in memory start"<<endl;
    num_seeks_sort_pass++;
    overall_num_seeks++;

    ll temp=in_blk_ptr; 
    for(ll i=0;i<m*key_in_one_blk && in_blk_ptr < n;i++){
        memory[i] = in_vec[in_blk_ptr];
        in_blk_ptr++;
        cout<<memory[i]<<" ";
    }
    cout<<endl;
    cout<<"read in memory end"<<endl;
    return in_blk_ptr-temp;
}

void write_to_memory(vector<ll> &memory){
    cout<<"write to memory start"<<endl;
    num_seeks_sort_pass++;
    overall_num_seeks++;
    for(ll i=0;i<m*key_in_one_blk && out_blk_ptr < n;i++){
        out_vec[out_blk_ptr] = memory[i];
        out_blk_ptr++;
        cout<<memory[i]<<" ";
    }
    cout<<endl;
    cout<<"write to memory end"<<endl;
}

ll read_block_from_vec(vector<ll> &block,ll start){

    num_blk_transfer_merge_pass+=2;
    num_seeks_merge_pass+=2;
    overall_num_blk_transfers+=2;
    overall_num_seeks+=2;
    for(ll i=0;i<block.size();i++){
        if(start+i > n){
            cout<<"returned from here"<<endl;
            return i-start;
            }
        block[i] = in_vec[start+i];
    }
    return block.size();
    
}

void write_block_to_vec(vector<ll> &block){
    num_blk_transfer_merge_pass++;
    num_seeks_merge_pass++;
    overall_num_blk_transfers++;
    overall_num_seeks+=2;
    for(ll i=0;i<block.size();i++){
        out_vec[out_blk_ptr] = block[i];
        out_blk_ptr++;
    }
}


void sort_the_memory(vector<ll> &memory, ll num){
    sort(memory.begin(),memory.end()-m*key_in_one_blk+num);
}


void sort_blocks(vector<ll> & memory){
    cout<<"sort_blocks_start"<<endl;
    cout<<"Ceil "<<ceil(((float)n)/(m*key_in_one_blk))<<endl;
    for(ll i=0;i<ceil(((float)n)/(m*key_in_one_blk));i++){
        // prll("Hello");
        
        ll ret = read_in_memory(memory);
        cout<<"Return value from read: "<<ret<<endl;
        sort_the_memory(memory,ret);
        write_to_memory(memory);
    }
    cout<<"sort_blocks_end"<<endl;

}


void merge_n(){
    
    cout<<"merge_n function start"<<endl;


    for (ll pass=0;;pass++){
        cout<<"MERGE PASS: "<<pass+1<<endl;
        total_num_of_pass++;

        in_blk_ptr=0;
        out_blk_ptr=0;


        fstream inputfile;
        fstream outputfile;

        inputfile.open("outfile"+to_string(pass+1),ios::in | ios::out);
        outputfile.open("outfile"+to_string(pass+2),ios::out);

        // inputfile.close();
        outputfile.close();

        // inputfile.open("outfile"+to_string(pass+1),ios::in | ios::out);
        outputfile.open("outfile"+to_string(pass+2),ios::in | ios::out);
        cout<<"MERGE PASS INPUT "<<endl;
        read_comp_file(in_vec,inputfile);

        ll runs = ceil(((float)n)/(m*key_in_one_blk*(ll)(pow(m-1,pass))));

        // cout<<"Runs: "<<runs<<endl;

        vector<vector<ll>> memory(m,vector<ll>(key_in_one_blk));
        vector<ll> start_of_every_run(runs);
        vector<ll> start_of_every_run_copy(runs);


        for(ll i=0;i<runs;i++){
            start_of_every_run[i] = i*m*key_in_one_blk*((ll)(pow(m-1,pass)));
            start_of_every_run_copy[i] = i*m*key_in_one_blk*((ll)(pow(m-1,pass)));
            // cout<<start_of_every_run[i]<<" ";
        }
        // cout<<endl;

        // runs is overall number of groups
        // num_runs is number of groups of runs
        // num_blocks is number of block in one group 
        ll flag =0;
        if(runs<=m-1){

            cout<<"Last Merge Pass"<<endl;
            // break;

            flag =1 ;

            
        }
        if(1){
            ll num_runs = ceil(((float)runs)/(m-1));

            // cout<<"Num runs: "<<num_runs<<endl;
            
            for(ll i=0;i<num_runs;i++){
                ll num_blocks = min(m-1,runs-i*(m-1));
                // cout<<"Num blocks: "<<num_blocks<<endl;

                vector<ll> start_of_every_block(num_blocks,0);
                for(ll j=0;j<num_blocks;j++){
                    ll ret = read_block_from_vec(memory[j],start_of_every_run[i*(m-1)+j]);
                    // cout<<"Ret: "<<ret<<endl;
                }

                ll k=0;
                while(k<num_blocks*m*key_in_one_blk*((ll)pow(m-1,pass))){
                    ll min_index = -1;
                    ll min_val = LONG_LONG_MAX;
                    for(ll j=0;j<num_blocks;j++){
                        if(start_of_every_block[j]!=-1 && memory[j][start_of_every_block[j]]<min_val){
                            min_val = memory[j][start_of_every_block[j]];
                            min_index = j;
                        }
                    }
                    if(min_index==-1){
                        // cout<<"some error"<<endl;
                        break;
                    }
                    else{
                        cout<<"Min Index: "<<min_index<<endl;
                        cout<<"Min val: "<<min_val<<endl;
                        
                    }
                    out_vec[out_blk_ptr] = min_val;
                    out_blk_ptr++;
                    start_of_every_block[min_index]++;
                    // cout<<"min index: " << min_index << "Num blocks: "<<num_blocks<<endl;
                    // cout<<" cond 2:"<<(start_of_every_run[i*(m-1)+min_index]-start_of_every_run_copy[i*(m-1)+min_index])/key_in_one_blk<<total_num_blocks % (m*(ll)pow(m-1,pass))-1<<endl;
                    // cout<<" cond 3:"<<(start_of_every_block[min_index]==(n%key_in_one_blk))<<endl;
                    // cout<<" cond 4:"<<(start_of_every_block[min_index] == key_in_one_blk)<<endl;
                    if((min_index==(num_blocks-1)) && (i==num_runs-1) && (start_of_every_run[i*(m-1)+min_index]-start_of_every_run_copy[i*(m-1)+min_index])/key_in_one_blk== total_num_blocks % (m*(ll)pow(m-1,pass))-1 && ((start_of_every_block[min_index]==(n%key_in_one_blk)) ||  (start_of_every_block[min_index] == key_in_one_blk))){
                        start_of_every_block[min_index] = -1;
                        // cout<<"condition check"<<endl;
                    }
                    else if(start_of_every_block[min_index]==key_in_one_blk){
                        start_of_every_block[min_index] = 0;
                        start_of_every_run[i*(m-1)+min_index]+=key_in_one_blk;
                        if(start_of_every_run[i*(m-1)+min_index]==start_of_every_run_copy[i*(m-1)+min_index]+m*key_in_one_blk*((ll)pow(m-1,pass))){
                            start_of_every_block[min_index] = -1;
                            // cout<<"condition check"<<endl;
                        }
                        else{
                            read_block_from_vec(memory[min_index],start_of_every_run[i*(m-1)+min_index]);
                        }
                    }
                    k++;
                }

            }

        }

    cout<<"MERGE PASS OUTPUT"<<endl;
    print_vec(out_vec);
    cout<<endl<<endl;
    write_comp_file(out_vec,outputfile);
    inputfile.close();
    outputfile.close();
    if(flag==1){
            break;
        }
    }
    
    cout<<"merge_n function end"<<endl;

}


void print_stats(){
    cout<<"PRINTING STATS"<<endl;
    cout<<"seeks in sorted pass: "<<num_seeks_sort_pass<<endl;
    cout<<"blk transfers in sorted pass: "<<num_blk_transfer_sort_pass<<endl;

    cout<<"Total number of merge passes: "<<total_num_of_pass<<endl;
    cout<<"Seek in one merge pass: "<<seeks_in_one_pass<<endl;
    cout<<"Blk transfers in one merge pass: "<<transfers_in_one_pass<<endl;
    cout<<"seeks in all merge pass: "<<num_seeks_merge_pass<<endl;
    cout<<"blk transfers in all merge pass: "<<num_blk_transfer_merge_pass<<endl;
    cout<<"Overall seeks: "<<overall_num_seeks<<endl;
    cout<<"Overall blk transfers: "<<overall_num_blk_transfers<<endl;
}


int main(int argc, char**argv){

    if(argc!=6){
        cout<<"Wrong input format"<<endl;
        exit(-1);
    }

    infile.open(argv[1],ios::in);
    // outfile.open("out",ios::out);
    outfile1.open("outfile1",ios::out);
    // outfile2.open("out2",ios::in | ios::out);

    m = stoll(argv[2]);
    k = stoll(argv[3]);
    n = stoll(argv[4]);
    b = stoll(argv[5]);

    key_in_one_blk = b/k;
    total_num_blocks = ceil(((float)n)/key_in_one_blk);

    cout<<"Input: m="<<m<<" k="<<k<<" n="<<n<<" b="<<b<<endl;
    cout<<"Keys_in_one_blk: "<<key_in_one_blk<<endl;

    vector<ll> memory_blocks(m*key_in_one_blk);

    in_vec.resize(n);
    out_vec.resize(n);


    read_comp_file(in_vec,infile);
    cout<<endl<<endl;
    cout<<"SORT PHASE START"<<endl;
    sort_blocks(memory_blocks);
    cout<<"SORT PHASE END"<<endl<<endl;
    num_blk_transfer_sort_pass = 2*ceil((float)n/(key_in_one_blk));
    overall_num_blk_transfers += 2*ceil((float)n/(key_in_one_blk));
    
    cout<<"OUTPUT OF SORT PHASE"<<endl;
    print_vec(out_vec);
    write_comp_file(out_vec,outfile1);
    in_blk_ptr=0;
    out_blk_ptr=0;
    outfile1.close();
    if(n<=m*key_in_one_blk){
        cout<<"No merge pass required"<<endl;
        cout<<endl<<endl;
        print_stats();

        infile.close();
        return 0;
    }

    cout<<endl<<endl;
    cout<<"MERGE PHASE START"<<endl;
    merge_n();
    cout<<"MERGE PHASE END"<<endl<<endl;
    seeks_in_one_pass = num_blk_transfer_merge_pass/total_num_of_pass;
    transfers_in_one_pass = num_blk_transfer_merge_pass/total_num_of_pass;

    cout<<endl<<endl;
    print_stats();

    infile.close();

    return 0;
}