#pragma once
#include "general.cpp"
#include <vector>
#include <iostream>

char majority(std::vector<char> res, int rowIndex, int n){
    int counterD=0,counterA=0,counterN=0,counterR=0,max;
    char c;

    for (int i=0; i< n; ++i){
        c = res[rowIndex*n + i];
        if (c=='d') counterD++;
        else if (c=='a') counterA++;
        else if (c=='n') counterN++;
        else if (c=='r') counterR++;
    }
    max = std::max(counterA,std::max(counterD,std::max(counterR,counterN)));
    if (max==counterR) return 'r';
    else if (max==counterA) return 'a';
    else if (max==counterN) return 'n';
    else  return 'd';

};
std::vector<General*> removeGeneralI(int i, std::vector<General*> generals){
    std::vector<General*> res;
    for(int j=0; j<generals.size();++j){
        if (j!=i) res.push_back(generals[j]);
    }
    return res;
};
std::vector<char> OMAux(int m, General* commander, std::vector<General*> generals, char _received) {
    int n = generals.size();
    char received;
    std::vector<char> initialMessages = commander->generateMessages(n,_received);
    std::vector<char> resI, result;
    if (m==0){
        // for (int i=0; i<n; ++i){
        //     initialMessages[i] = generals[i]->decideMessage(initialMessages[i]);
        // }
        return initialMessages;
    }
    else {
        std::vector<char> res(n*n, 'd');
        for (int i=0; i<n; ++i){
            received = initialMessages[i]; //generals[i]->decideMessage(initialMessages[i]);
            resI = OMAux(m-1,generals[i],removeGeneralI(i,generals), received);
            for (int j=0; j<n-1;++j){
                if (j>=i) res[(j+1)*n + i]=resI[j];
                else res[j*n + i]=resI[j];
            }
            res[i*n + i]=received;
        }
        for (int k=0; k<n; ++k){
            result.push_back(majority(res,k,n));
        }
        // for (int k=0; k<n; ++k){
        //     for (int l=0; l<n; ++l){
        //         std::cout << res[k*n+l] << " ";
        //     }
        //     std::cout<<std::endl;
            
        // }
        return result;
    }

};
std::vector<char> OM(int m, General* commander, std::vector<General*> generals){
    return OMAux(m,commander,generals, 'a');
};
std::map<char,int> simulate(int numberOfIterations, int numberOfLoyals, int numberOfTraitors, bool isCommanderTraitor ){
    std::vector<General*> generals;
    General* commander = new General(0,isCommanderTraitor);
    std::map<char,int> results;
    int failureCounter=0,tmpA,tmpR;
    int m = isCommanderTraitor ? 1 : 0;
    m+=numberOfTraitors;
    results.insert(std::pair<char,int>('r',0));
    results.insert(std::pair<char,int>('a',0));
    results.insert(std::pair<char,int>('d',0));
    results.insert(std::pair<char,int>('n',0));
    
    for (int i=1; i<numberOfLoyals+1; ++i){
        General* g = new General(i,false);
        generals.push_back(g);
    }
    for (int i=numberOfLoyals+1; i<numberOfLoyals+numberOfTraitors+1; ++i){
        General* g = new General(i,true);
        generals.push_back(g);
    }
    for(int it=0;it<numberOfIterations;++it){
        std::vector<char> decisions = OM(m, commander, generals);
        tmpA = results['a'];
        tmpR = results['r'];
        for (int i = 0;  i<numberOfLoyals+numberOfTraitors; ++i){
            if (!(generals[i]->getIsTraitor())) {
                results[decisions[i]]++;
            }
        }
        if (results['a']-tmpA != numberOfLoyals && results['r']-tmpR != numberOfLoyals){
            // std::cout << results['a']-tmpA << "," <<results['r']-tmpR << std::endl;
            failureCounter++;
        }else if ( !isCommanderTraitor && results['a']-tmpA != numberOfLoyals ){
            failureCounter++;
        }
    }
    results['f'] = failureCounter;
    return results;

}