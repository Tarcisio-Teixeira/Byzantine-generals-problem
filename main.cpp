#include "general.cpp"
#include "function.cpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <future>

// writing on a text file
// #include <iostream>
// #include <fstream>

int main(){
    // std::ofstream myfile ("example.txt");
    // int numberOfGenerals = 10;
    // for(int numberOfTraitors=1;numberOfTraitors<7;numberOfTraitors++){
    srand(time(NULL));
    int numberOfIterations=100, numberOfLoyals=numberOfGenerals-numberOfTraitors-1;
    int numberOfTraitors=5;
    bool isCommanderTraitor=false;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    double res_a = 0, res_r = 0;
    int failureCounter = 0;
    std::vector<std::future<std::map<char,int>>> VF;

    for (int j = 0; j < numberOfIterations; j++) {
        // // the commander can be randomly chosen as a traitor
        // double tmp = ((double) rand() / (RAND_MAX));
        // if (tmp > double(i + 1) / double(i + numberOfTraitors + 1)) {
        //     // the probability that the commander is a traitor
        //     isCommanderTraitor = true;
        //     numberOfTraitors = 4;
        //     numberOfLoyals = i + 1;
        // } else {
        //     isCommanderTraitor = false;
        //     numberOfTraitors = 5;
        //     numberOfLoyals = i;
        //     if (isCommanderTraitor) res_a++; // If the commander is loyal, he will also attack
        // }
        VF.push_back(std::async(&simulate, 1, numberOfLoyals, numberOfTraitors, isCommanderTraitor));
    }
    for (int j = 0; j < numberOfIterations; j++) {
        auto results = VF[j].get();
        res_a += results['a'];
        res_r += results['r'];
        failureCounter += results['f'];
    }

    
    

    std::cout << "The loyals failed in "<< failureCounter << (failureCounter<=1 ? " time." :" times." )<< std::endl;
    std::cout << "Loyals that attacked: " << res_a/numberOfIterations <<std::endl;
    std::cout << "Loyals that retreated: " << res_r/numberOfIterations<<std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << std::endl;

    // if (myfile.is_open())
    // {
    //     myfile << std::to_string(numberOfTraitors) << ","<< std::to_string(numberOfGenerals)<< "," << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    //     myfile << "\n";
    // }
    // else std::cout << "Unable to open file";
    // }
    // myfile.close();
    return 0;
}
