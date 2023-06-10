/*  
    Homework 4 - Dynamic Programming
    This C++ program calculates the minimum number of operations needed to obtain the number n 
    using multiplication by 2 or 3, or addition by 1.
*/

#include <iostream>
#include <vector>
#include <fstream>

int minOperations(int n) {
    std::vector<int> dp(n + 1, 0);
    std::vector<int> sequence;

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + 1;
        if (i % 2 == 0)
            dp[i] = std::min(dp[i], dp[i / 2] + 1);
        if (i % 3 == 0)
            dp[i] = std::min(dp[i], dp[i / 3] + 1);
    }

    int i = n;
    while (i >= 1) {
        sequence.push_back(i);
        if (i == 1)
            break;
        if (dp[i - 1] + 1 == dp[i])
            i = i - 1;
        else if (i % 2 == 0 && dp[i / 2] + 1 == dp[i])
            i = i / 2;
        else if (i % 3 == 0 && dp[i / 3] + 1 == dp[i])
            i = i / 3;
    }
    int dim = sequence.size();
    for (int j = dim - 1; j >= 0; j--)
        std::cout << sequence[j] << " ";
    std::cout << std::endl;

    return dp[n];
}

int main() {
    std::ifstream fin("input.txt");
    int n;
    fin >> n;
    int minOps = minOperations(n);
    std::cout << "Minimum number of operations: " << minOps << std::endl;
    fin.close();
    return 0;
}