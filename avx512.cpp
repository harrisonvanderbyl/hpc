#include <iostream>
#include <chrono>
#include <immintrin.h>

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
        auto temp = _mm512_setzero_ps();

        // do eight at a time
        for(int index = 0; index < size; index += 16){
            temp = _mm512_fmadd_ps(_mm512_loadu_ps(VectorA + index), _mm512_loadu_ps(VectorB + index), temp);
        }

        // add the lanes together
        output = temp[0] + temp[1] + temp[2] + temp[3] + temp[4] + temp[5] + temp[6] + temp[7];
    }
    
    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration<double>(endTime - startTime);
    std::cout << "It took " << duration.count() << " seconds.\n";


}