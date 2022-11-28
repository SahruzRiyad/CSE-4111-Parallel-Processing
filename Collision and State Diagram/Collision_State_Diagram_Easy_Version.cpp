#include <bits/stdc++.h>
using namespace std;

 void printBinary(int x){
    int len = log2(x) + 1;

    for(int i = len - 1 ; i >= 0 ; i--)
        cout<<(bool)(x & (1<<i));
}

void printSet (set < int >  &x){
    for(auto &i : x)
        cout<<i<<' ';
    cout<<endl;
}

void printCollisionVec(int x){
    int len = log2(x) + 1;

    for(int i = len - 1 ; i >= 0 ; i--)
        cout<<(bool)(x & (1<<i))<<' ';

    cout<<endl;
}

int main(){
    freopen("./input.txt", "r" , stdin);

    int r , c , i , j , k , collisionInt = 0 , ps , ans;
    set < int > forbiddenLat , permissibleLat;
    queue < int > state;
    map < int , bool > vis;

    cin>>r>>c;

    bool table[r+2][c+2];

    //Forbidden Latency
    for(i = 0 ; i < r ; i++){

        for(j = 0 ; j < c ; j++)
            cin>>table[i][j];
        
        for(j = 0 ; j < c ; j++)
            if(table[i][j])
                for(k = j + 1 ; k < c ; k++)
                    if(table[i][k])
                        forbiddenLat.insert(k-j) , collisionInt |= (1 << (k-j-1)); 
    }

    //Permissible Latency
    for (i = 1 ; i <= c ; i++){
        auto has = forbiddenLat.find(i);

        if(has == forbiddenLat.end())
            permissibleLat.insert(i);
    }

    cout<<"Forbidden Latency : ";
    printSet(forbiddenLat);

    cout<<"Perimissible Latency : ";
    printSet(permissibleLat);

    cout<<"Collision Vector : ";
    printCollisionVec(collisionInt);

    //State Diagram:
    state.push(collisionInt);
    int mxLen = 1 << c;
    set < pair < int , int > > nextState[mxLen+1];

    while(!state.empty()){
        ps = state.front();
        vis[ps] = 1;
        state.pop();

        for(i = 0 ; i < c ; i++){

            if(!(ps & (1<<i))){
                int shift = ps >> (i + 1);
                ans = shift | collisionInt;

                nextState[ps].insert({i+1,ans});

                if (vis[ans] == 0)
                    state.push(ans);
            }
        }
    }

    //Display State Diagram:
    cout<<"State Diagram : " << endl;

    for(i = 0 ; i < mxLen ; i++){
        if(!nextState[i].empty()){
            printBinary(i);
            cout<<" : ";

            for(auto &x : nextState[i]){
                cout<<"("<<x.first<<",";
                printBinary(x.second);
                cout<<") ";
            }

            cout<<endl;
        }
    }

    return 0;
}