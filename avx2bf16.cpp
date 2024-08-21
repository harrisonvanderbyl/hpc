#include <iostream>
#include <chrono>
#include <immintrin.h>

int main(){
    
    // initialize size
    int size = 1024*1024;
    
    // initialize tensors
    __bfloat16* VectorA = new __bfloat16[size];
    __bfloat16* VectorB = new __bfloat16[size];

    // result buffer
    float output;

    // how many repeats
    int repeats = 2048;

    // start the clock
    auto startTime = std::chrono::steady_clock::now();
    
    for(int i = 0; i < repeats; i++){
        // reset
        auto temp = _mm256_setzero_ps();

        // do eight at a time
        for(int index = 0; index < size; index +=16){
            temp = _mm256_dpbf16_ps(temp,(__m256bh)_mm256_loadu_si256((__m256i_u *)(VectorA + index)),(__m256bh)_mm256_loadu_si256((__m256i_u *)(VectorB + index)));
        }

        // add the lanes together
        output = temp[0] + temp[1] + temp[2] + temp[3] + temp[4] + temp[5] + temp[6] + temp[7];
    }
    
    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration<double>(endTime - startTime);
    std::cout << "It took " << duration.count() << " seconds.\n";


}