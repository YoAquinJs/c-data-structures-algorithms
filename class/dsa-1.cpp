#include <cassert>
#include <vector>
#include <iostream>
#include <chrono>
#include <functional>

int sum_loop(const int n){
    int sum = 0;
    for (int i=1; i <= n; i++)
        sum += i;
    return sum;
}

int sum_recursive(const int n){
    if (n <= 0) return 0;
    return n+sum_recursive(n-1);
}

int sum_math(const int n){
    if (n <= 0) return 0;
    return n*(n+1)/2;
}

int64_t benchmark(int (*func)(int), const int& arg, int& result);
void tests(std::vector<std::pair<int, int>> test_cases);

// g++ dsa-1.cpp -o main; ./main
int main(){
    tests({
        {0, 0},
        {1, 1},
        {2, 3},
        {4, 10},
        {10, 55},
        {100, 5050},
        {-1000, 0},
    });

    int n, sum;
    int64_t duration;

    std::cout << "enter n: ";
    std::cin >> n;
    duration = benchmark(sum_loop, n, sum);
    std::cout << "loop: " << sum << " : Took " << duration << "ns\n";
    duration = benchmark(sum_recursive, n, sum);
    std::cout << "recursive: " << sum << " : Took " << duration << "ns\n";
    duration = benchmark(sum_math, n, sum);
    std::cout << "math: " << sum << " : Took " << duration << "ns\n";

    return 0;
}

void tests(std::vector<std::pair<int, int>> test_cases) {
    for (const auto& test_case : test_cases){
        assert(sum_loop(test_case.first) == test_case.second);
        assert(sum_recursive(test_case.first) == test_case.second);
        assert(sum_math(test_case.first) == test_case.second);
    }
}

int64_t benchmark(int (*func)(int), const int& arg, int& result) {
    auto start = std::chrono::high_resolution_clock::now();

    result = func(arg);

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}
