#include <bits/stdc++.h>
using namespace std;
#define MAX 2005
#define ll long long int

ll Base[2] = {773,709};
ll Mod[2] = {281559881,693329647};
ll InvBase[2][2];

ll Pow[MAX][2][2];
ll PowCell[MAX][MAX][2];

ll Inv[MAX][2][2];
ll InvCell[MAX][MAX][2];

ll A[MAX][MAX];
ll B[MAX][MAX];
ll cA[MAX][MAX][2];
ll cB[MAX][MAX][2];

ll bigMod(ll n,ll r,ll mod){
    if(r==0) return 1;
    ll ret = bigMod(n, r/2, mod);
    ret = (ret*ret) % mod;
    if(r&1) ret = (ret*n)% mod;
    return ret;
}
ll invMod(ll n,ll mod) {return bigMod(n,mod-2,mod);}

ll cMod(ll x,ll mod){
    while(x>=mod) x-=mod;
    while(x<0)    x+=mod;
    return x;
}

void Preprocess(){
    for(int b=0;b<2;b++) for(int m=0;m<2;m++)                          Pow[0][b][m]     = Inv[0][b][m] = 1;
    for(int b=0;b<2;b++) for(int m=0;m<2;m++)   for(int i=1;i<MAX;i++) Pow[i][b][m]     = (Pow[i-1][b][m]*Base[b]) % Mod[m];
    for(int m=0;m<2;m++) for(int i=0;i<MAX;i++) for(int j=0;j<MAX;j++) PowCell[i][j][m] = (Pow[i][0][m]*Pow[j][1][m]) % Mod[m];

    for(int b=0;b<2;b++) for(int m=0;m<2;m++)                          InvBase[b][m]    = invMod(Base[b],Mod[m]);
    for(int b=0;b<2;b++) for(int m=0;m<2;m++)   for(int i=1;i<MAX;i++) Inv[i][b][m]     = (Inv[i-1][b][m]*InvBase[b][m]) % Mod[m];
    for(int m=0;m<2;m++) for(int i=0;i<MAX;i++) for(int j=0;j<MAX;j++) InvCell[i][j][m] = (Inv[i][0][m]*Inv[j][1][m])%Mod[m];
}

void Generate(ll M[MAX][MAX],ll cM[MAX][MAX][2],int r,int c){
    for(int m=0;m<2;m++){
        for(int i=1;i<=r;i++){
            for(int j=1;j<=c;j++){
                ll Now=(M[i][j]*PowCell[i][j][m])%Mod[m];
                cM[i][j][m]=cM[i-1][j][m]+cM[i][j-1][m]-cM[i-1][j-1][m]+Now;
                cM[i][j][m] = cMod(cM[i][j][m], Mod[m]);
            }
        }
    }
}

pair<ll,ll> Query(ll cM[MAX][MAX][2],int x1,int y1,int x2,int y2){
    ll Sum[2];
    for(int m=0;m<2;m++){
        Sum[m] = cB[x2][y2][m]-cB[x2][y1-1][m]-cB[x1-1][y2][m]+cB[x1-1][y1-1][m];
        Sum[m] = cMod(Sum[m],Mod[m]);
        Sum[m] = (InvCell[x1-1][y1-1][m] * Sum[m]) % Mod[m];
    }
    return {Sum[0],Sum[1]};
}
