#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;




#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x<<" "; _print(x); cerr << endl;
#else
#define debug(x)
#endif



void _print(ll t) {cerr << t;}
void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(lld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}
void _print(bool t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.first); cerr << ","; _print(p.second); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(unordered_map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}








const int key =1720050378;
vector<int> key_bit(32,0);




vector<int> convert_string_int(string w){
    // reverse(w.begin(),w.end());
    int a = w[0];
    int b = w[1];
    a <<= 8;
    a += b;
    vector<int> str(16);
    for(int i = 0;i<16;i++){
        if(a&(1<<i)){
            str[i] = 1;
        }
        else{
            str[i] = 0;
        }
    }
    
    return str;
}



string convert_int_string(vector<int> &w_ans){
    string ans;
    vector<int> first;
    int a = 0;
    for(int i = 0;i<8;i++){
        if(w_ans[i]){
            a += (1<<i);
        }
    }
    ans.push_back((char)a);
    a= 0;
    for(int i = 8;i<16;i++){
        if(w_ans[i]){
            a += (1<<(i-8));
        }
    }
    ans.push_back((char)a);
    reverse(ans.begin(),ans.end());
    return ans;

}

vector<vector<int>> key_mixing(vector<int> &subkey,vector<int> &w_num){
    
    vector<int> xor_(16);
    for(int i = 0;i<16;i++){
        xor_[i] = subkey[i] ^ w_num[i];
    }
    debug(subkey)
    debug(w_num)
    debug(xor_)
    vector<vector<int>> sbox(4,vector<int>());

    
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++)
            sbox[i].push_back(xor_[4*i + j]);
    }

    debug(sbox);
    return sbox;

}


vector<int> key_permutation(vector<vector<int>> sbox){
    vector<int> permute;


    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            permute.push_back(sbox[j][i]);
        }
    }
    debug(permute)

    return permute;


}




vector<int> func(int round,vector<int> w_num){
     
    if(round == 1){
        vector<int> subkey;
        for(int i = 0;i<16;i++){
            subkey.push_back(key_bit[i]);
        }
        debug(subkey)
        vector<vector<int>> sbox = key_mixing(subkey,w_num);
        vector<int> permut = key_permutation(sbox);
        return permut;
    }
    else if(round == 2){
        vector<int> subkey;
        for(int i = 4;i<20;i++){
            subkey.push_back(key_bit[i]);
        }
        vector<vector<int>> sbox = key_mixing(subkey,w_num);
        vector<int> permut = key_permutation(sbox);
        return permut;
    }
    else if(round == 3){
        vector<int> subkey;
        for(int i = 8;i<24;i++){
            subkey.push_back(key_bit[i]);
        }
        vector<vector<int>> sbox = key_mixing(subkey,w_num);
        vector<int> permut = key_permutation(sbox);
        return permut;
    }
}
int main(){

    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);

    

    freopen("error.txt","w",stderr);

#endif


    string w = "ab";
    
    for(int i = 0;i<32;i++){
        if(key&(1<<i)){
            key_bit[i] = 1;
        }
        
    }
    debug(key_bit)


    //convert string to bits array
    vector<int> w_num = convert_string_int(w);
    debug(w_num)
    //doing the ciphering
    for(int i = 1;i<=3;i++){
        w_num = func(i,w_num);
        debug(w_num)
    }


    //final layer without permutation
    vector<int> subkey;
    for(int i = 16;i<32;i++){
        subkey.push_back(key_bit[i]);
    }

    vector<vector<int>> finalbox = key_mixing(subkey,w_num);
    debug(finalbox)
    //final bit of encrypted cipher
    vector<int> w_ans;
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            w_ans.push_back(finalbox[i][j]);
        }
    }





    debug(w_ans)
    //convert the bits to string;


    //check here
    string ret = convert_int_string(w_ans);

    vector<int> check = convert_string_int(ret);
    debug(check)
    cout<<ret<<endl;

    // reverse(ret.begin(),ret.end());
    cout<<ret<<endl;


    return 0;
}