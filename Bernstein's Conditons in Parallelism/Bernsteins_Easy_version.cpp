#include <bits/stdc++.h>
using namespace std;

bool checkEmptySet(vector < char > &x , vector < char > &y){
    for (auto &i : x)
        for(auto &j : y)
            if(i == j)
                return false;
    return true;
}


int main(){

    vector < string > processName;
    vector < char > inputVec[100] , outputVec[100];
    string s;
    int len = 0, i , j , p;
    bool anti_dp , flow_dp , output_dp;


    freopen("./berInput.txt", "r" , stdin);

    while(cin>>s){

        processName.push_back(s.substr(0,2));

        outputVec[len].push_back(s[3]);

        inputVec[len].push_back(s[5]);
        inputVec[len].push_back(s[7]);

        len++;
    }

    for(i = 0 ; i < len ; i++){

        cout<<processName[i]<<" : ";

        for(j = i + 1 ; j < len ; j++){
            anti_dp = checkEmptySet(inputVec[i] , outputVec[j]);
            flow_dp = checkEmptySet(inputVec[j] , outputVec[i]);
            output_dp = checkEmptySet(outputVec[i] , outputVec[j]);
            p = anti_dp + flow_dp + output_dp;

            if(p == 3)
                cout << processName[i]<< " || " << processName[j];

            else {
                if(!anti_dp){
                    cout << processName[i]<<" −−।−−> " << processName[j];
                    (p < 2)? cout<<", ",p++ : p;
                }
                
                if(!flow_dp){
                    cout << processName[i] << " −−−−−> " << processName[j];
                    (p < 1)? cout<<", ",p++ : p;
                }

                if(!output_dp){
                    cout << processName[i]<<" −−o−−> " << processName[j];
                }

            }

            if(j != len - 1)
                cout<<", ";

        }
        cout<<endl;
    }

    return 0;
}