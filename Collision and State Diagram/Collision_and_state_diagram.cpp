#include <bits/stdc++.h>
using namespace std;

int collisionVal = 0 , mxForbidden = -1;
vector < int > table[50];

void printSet(set<int> &x){
    for(auto itr = x.begin() ; itr != x.end() ; itr++)
        cout<<*itr<<' ';
    cout<<endl;
}

void printVector(vector < int > &x){
    for(auto &itr : x)
        cout<<itr<<' ';
    cout<<endl;
}

set < int > findForbiddenLatency(int stage , int t){
    int prev;
    set < int > forbidden;
    for(int i = 0 ; i < stage ; i++){
        prev = -1;
        for(int j = 0 ; j < t ; j++){
            if(prev != -1){
                for(int k = prev + 1; k < t ; k++){
                    if(table[i][k])
                        forbidden.insert(k-prev);
                        mxForbidden = max(mxForbidden,(k-prev));
                }
                prev = -1;
            }
            if(table[i][j])
                prev = j;
        }
    }
    return forbidden;
}

set < int > findPermissibleLatency(int t , set < int > &forbidden){
    set < int > permissible;

    for(int i = 1 ; i <= t ; i++){
        auto has = forbidden.find(i);
        if(has == forbidden.end()){
            permissible.insert(i);
        }
    }
    return permissible;
}

vector < int > findCollisionVector(set < int > &forbidden){

    auto last = forbidden.end();
    last--;
    vector < int > collisionVector;

    for(int i = 1 ; i <= *last ; i++){
        auto has = forbidden.find(i);
        if(has == forbidden.end())
            collisionVector.push_back(0);
        else{
            collisionVector.push_back(1);
            collisionVal |= (1<<(i-1));
        }
        
    }
    reverse(collisionVector.begin() , collisionVector.end());
    
    return collisionVector;
    
}

set < pair <int , int > > findCollisionPoint(int stage , int t , int newStage , int newT , set < int > &forbidden){

    set < int > newTaskForbidden;
    set < pair < int , int >  > collisionPoint;
    bool foribddenFlag = 0;

    for(int i = 0 ; i < newT ; i++){
        if(table[newStage][i]){
            auto itr = forbidden.find(abs(newT - i));
            if(itr != forbidden.end())
                foribddenFlag = 1;
            newTaskForbidden.insert(abs(newT - i));
        }
    }

    if(foribddenFlag){
        for(int i = 0 ; i < stage ; i++){
            for(int j = newT ; j < t ; j++){
                if(table[i][j]){
                    for(auto &itr : newTaskForbidden)
                        if( j - itr >= 0 && table[i][j-itr] == 1)
                            collisionPoint.insert({i+1,j+1});
                }
            }
        }
    }
    return collisionPoint;
}

void findStageDiagram(int t){
    int icv = collisionVal , ps ,shift , ans , x , maxLen = (1<<t) + 1;
    queue < int > state;
    set < pair < int , int > > stateLat[maxLen];
    map < int , bool > vis;
    state.push(icv);

    while(!state.empty()){
        ps = state.front();
        vis[ps] = 1;
        state.pop();
        for(int i = 0 ; i < t ; i++){
            if(!(ps & (1<<i))){
                shift = ps >> (i + 1);
                ans = shift | icv;
                
                stateLat[ps].insert({ans,(i+1)});

                if(!vis[ans])
                    state.push(ans);
            }
        }
    }
    printf("State Diagram:\n");
    for(int i = 1 ; i < maxLen ; i++){
        if(!stateLat[i].empty()){
            for(int j = mxForbidden - 1 ; j >= 0 ; j--){
                x = (bool)(i & (1<<j));
                cout<<x;
            }
            cout<<"-> ";
            for(auto &itr : stateLat[i]){
                cout<<'(';
                for(int j = mxForbidden - 1 ; j >= 0 ; j--){
                    x = (bool)(itr.first & (1<<j));
                    cout<<x;
                }
                cout<<','<<itr.second<<") ";
            }
            cout<<endl;
        }
    }

}

int main(){
    FILE *fp = freopen("input.txt","r",stdin);
    int stage , t , newStage , newT , x , ps;
    cin>>stage>>t;

    vector < int > collisionVector;
    set < int > forbidden , permissible;
    set < pair < int , int >  > collisionPoint;

    for(int i = 0 ; i < stage ; i++)
        for(int j = 0 ; j < t ; j++)
            cin>>x,table[i].push_back(x);

    forbidden = findForbiddenLatency(stage , t);
    permissible = findPermissibleLatency(t , forbidden);
    collisionVector = findCollisionVector(forbidden);

    cout<<"Forbidden Set: ";
    printSet(forbidden);

    cout<<"Permissible Set: ";
    printSet(permissible);

    cout<<"Collision Vector: ";
    printVector(collisionVector);

    cin>>newStage>>newT;
    newStage--,newT--;

    collisionPoint = findCollisionPoint(stage , t , newStage , newT ,forbidden);

    if(!collisionPoint.empty()){
        printf("Collision Occurs in points: ");
        for(auto &itr : collisionPoint)
            cout<<'('<<itr.first<<','<<itr.second<<") ";
        cout<<endl;
    }
    else
        printf("No Collision occurs\n");
    
    findStageDiagram(t);

    fclose(fp);
    return 0;
}