#include <iostream>
#include <chrono>

int main(){
    
    // initialize size
    int size = 1024*1024;
    
    // initialize tensors
    float* VectorA = new float[size];
    float* VectorB = new float[size];

    // result buffer
    float output;

    // how many repeats
    int repeats = 2048;

    // start the clock
    auto startTime = std::chrono::steady_clock::now();
    
    for(int i = 0; i < repeats; i++){
        // reset
        output = 0;

        // do one at a time
        for(int index = 0; index < size; index ++){
            output = VectorA[index] * VectorB[index] + output;
        }
    }
    
    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration<double>(endTime - startTime);
    std::cout << "It took " << duration.count() << " seconds.\n";


}