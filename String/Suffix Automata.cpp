#include<bits/stdc++.h>
using namespace std;
const int MAXLEN = 400005;

int TotalLen,Size;
int Root,Last;

struct Node{
    int Link,Len;
    int FirstPos,version,baseID;
    int Next[27];
    void Clear(){
        Len = 0; Link = baseID = FirstPos = version = -1;
        memset(Next,0,sizeof(Next));
    }
};

Node St[MAXLEN*2];
bool isValid[MAXLEN*2];
vector<int>CurrList;
vector<int>LastList;

inline void CreateNode(int dep){
    St[Size].Clear();
    St[Size].Len = dep;
    St[Size].FirstPos = dep;
    St[Size].baseID = Size;

    isValid[Size] = true;
}

inline void init(){
    Size = 0;
    Root = Last = TotalLen = 0;
    St[Root].Clear();
    CurrList.clear();
    LastList.clear();
}

inline bool has(int u, int ch){
    int x = St[u].Next[ch];
    return isValid[St[x].baseID];
}

inline void SAM(int ch){
    TotalLen++;
    int Curr = ++Size;
    CreateNode(St[Last].Len + 1);

    int p = Last;
    while(p !=-1 && !has(p,ch)){
        St[p].Next[ch] = Curr;
        p = St[p].Link;
    }

    if(p == -1) St[Curr].Link = Root;
    else{
        int q = St[p].Next[ch];
        if(St[q].Len == St[p].Len + 1) St[Curr].Link = q;
        else{
            int Clone = ++Size;
            CreateNode(St[p].Len + 1);

            St[Clone].FirstPos = St[q].FirstPos;
            memcpy(St[Clone].Next,St[q].Next,sizeof(St[q].Next));
            St[Clone].Link = St[q].Link;
            St[Clone].baseID = St[q].baseID;
            St[q].Link = St[Curr].Link = Clone;

            while(p != -1 && St[p].Next[ch] == q) St[p].Next[ch] = Clone, p = St[p].Link;
        }
    }
    CurrList.push_back(Curr);
    LastList.push_back(Last);
    Last = Curr;
}

inline void del(int len){
    if(!len) return;

    for(int i = 0; i < len; i++){
        isValid[St[CurrList.back()].baseID] = false;
        CurrList.pop_back();
        Last = LastList.back();
        LastList.pop_back();
        TotalLen--;
    }
}

inline void MarkTerminal(int u,int v){
    while(u != -1) St[u].version = v,  u = St[u].Link;
}

int FindSmallest(int len,int idx){
    MarkTerminal(Last,idx);

    int cur = Root;
    for(int i= 0; i< len; i++){
        if(cur > Root && St[cur].version == idx) return TotalLen - i + 1;
        for(int ch = 0; ch < 26; ch++){
            if(!has(cur, ch )) continue;
            cur = St[cur].Next[ch];
            break;
        }
    }
    return St[cur].FirstPos - len + 1;
}
///Returns longest common substring of 2 strings
int LCS(char * s1, char * s2)
{
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    init();
    for(int i = 0; i < len1; i++) SAM(s1[i] - 'a' + 1);
    int curNode = 0, curLen = 0;
    int ans = 0;
    for(int i = 0; i < len2; i++){
        while(curNode > -1 && St[curNode].Next[s2[i] - 'a' + 1] == 0) curNode = St[curNode].Link, curLen = St[curNode].Len;
        if(curNode == -1) curNode = 0;
        if(St[curNode].Next[s2[i] - 'a' + 1]) curNode = St[curNode].Next[s2[i] - 'a' + 1], curLen++;
        ans = max(ans, curLen);
    }
    return ans;
}

