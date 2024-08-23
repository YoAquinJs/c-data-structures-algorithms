#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <iostream>

void alloc_vector(std::vector<int>& nums, int n) {
    nums = std::vector<int>(n);
    for (int i=0; i < n; i++)
        nums[i] == std::rand();
}

void bigo_1(std::vector<int>& nums){
    int len = nums.capacity();
}
void bigo_n(std::vector<int>& nums){
    for (int n : nums);
}
void bigo_n_squared(std::vector<int>& nums){
    for (int n : nums)
        for (int n : nums);
}
void bigo_n_cubed(std::vector<int>& nums){
    for (int n : nums)
        for (int n : nums)
            for (int n : nums);
}
void bigo_n2_plus_n2(std::vector<int>& nums){
    for (int n : nums)
        for (int n : nums);

    for (int n : nums)
        for (int n : nums);
}
int count_perm(int n) {
    if (n <= 0)
        return 0;
    else if (n == 1)
        return 1;
    int perms = 0;
    for (int i=0; i < n; i++)
        perms += count_perm(n-1);
    return perms;
}
void bigo_n_fact(std::vector<int>& nums){
    count_perm(nums.size());
}

int64_t benchmark(void (*func)(std::vector<int>&), std::vector<int>& arg);

// g++ dsa-2.cpp -o main; ./main
int main(){
    std::srand(std::time(0));

    std::vector<int> nums;
    int sizes[] = {10, 100, 1000, 10000, 100000, 1000000};
    for (int n : sizes){
        alloc_vector(nums, n);
        std::cout << "O(1): " << benchmark(bigo_1, nums) << "ms with n " << n << "\n";
        std::cout << "O(n): " << benchmark(bigo_n, nums) << "ms with n " << n << "\n";
        std::cout << "O(n2): " << benchmark(bigo_n_squared, nums) << "ms with n " << n << "\n";
        std::cout << "O(n3): " << benchmark(bigo_n_cubed, nums) << "ms with n " << n << "\n";
        std::cout << "O(n2+n2): " << benchmark(bigo_n2_plus_n2, nums) << "ms with n " << n << "\n";
        std::cout << "O(n!): " << benchmark(bigo_n_fact, nums) << "ms with n " << n << "\n";
    }

    return 0;
}

int64_t benchmark(void (*func)(std::vector<int>&), std::vector<int>& nums) {
    auto start = std::chrono::high_resolution_clock::now();

    func(nums);

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}
