#include <bits/stdc++.h>
using namespace std;

vector < string > inVec[100] , outVec[100] , pVec;
map < string , vector < pair < string , string > > > dependecy; 

bool checkConditions(vector<string>&x , vector<string>&y){
    for(auto &i : x)
        for(auto &j: y)
            if(i == j)
                return false;
    return true;
}

vector < pair < string , string > > parallel_pair(int n){
    int i , j;
    bool flow_dp , anti_dp , output_dp;
    vector < pair < string , string > > result;

    for(i = 0 ; i < n ; i++){
        for(j = i + 1; j < n; j++){
            anti_dp = checkConditions(inVec[i],outVec[j]);
            flow_dp = checkConditions(inVec[j],outVec[i]);
            output_dp = checkConditions(outVec[i],outVec[j]);
            
            if(anti_dp + flow_dp + output_dp == 3){
                result.push_back({pVec[i],pVec[j]});
                dependecy[pVec[i]].push_back({" no_dp ",pVec[j]});
            } 
            else{
                if(!flow_dp)
                    dependecy[pVec[i]].push_back({" ———> ",pVec[j]});
                if(!anti_dp)
                    dependecy[pVec[i]].push_back({" ——।—> ",pVec[j]});
                if(!output_dp)
                    dependecy[pVec[i]].push_back({" ——o—> ",pVec[j]});
            }   
        }
    }
    return result;
}
int main(){
    freopen("berInput.txt","r",stdin);
    string s , pName , inpString , tmp , outString;
    int n = 0 , i , j , len , pInd , x = 0 , y = 0;
    vector < pair < string , string > > result;

    while(cin>>s){
        len = s.size();
        for(i = 0 ; i < len ; i++){

            if(s[i] == ':')
                pName = s.substr(0,i) , pInd = i , pVec.push_back(pName);

            else if(s[i] == '='){

                inpString = s.substr(i+1,len) + '/';
                outString = s.substr(pInd+1,i-pInd-1);
                outVec[x].push_back(outString);

                for(j = 0 ; j < inpString.size() ; j++){
                    if(inpString[j] >= 'A' && inpString[j] <= 'Z')
                        tmp += inpString[j];
                    else 
                        inVec[x].push_back(tmp) , tmp = "";
                }
            }
        }
        x++;  
    }
   
    result = parallel_pair(x);
    cout<<result.size()<<" pairs execute in parallel: ";
    for(auto &itr : result)
        cout<<"("<<itr.first<<"||"<<itr.second<<") ";
    cout<<endl;

    cout<<"Dependency Graph:\n";
    for(auto &itr : pVec){
        i = 0;
        cout<<itr<<": ";
        for(auto &itr2 : dependecy[itr]){
            cout<<itr<<itr2.first<<itr2.second;
            if(i != dependecy[itr].size() - 1)
                cout<<", ";
            i++;
        }
        cout<<endl;
    }

    return 0;
}