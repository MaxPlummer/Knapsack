#include <iostream>
#include <vector>
#include <stack>

int values[100];
int weights[100];
int maximums[100];
int dp[100][100];
std::vector<int> solutions;

int knapsack(int i, int W, int k) {
    for (int n = 0; n <= i; n++) {
        for (int w = 0; w <= W; w++) {
            if (n == 0 || w == 0)
                dp[n][w]=0;
            else if (weights[n] <= w)
                dp[n][w] = std::max(values[n]+dp[n-1][w-weights[n]],dp[n-1][w]);
            else
                dp[n][w] = dp[n-1][w];
        }
    }
    return dp[i][W];
}

void traceback(int i, int k) {
    while (i > 0 && k>0) {
        if (dp[i][k] != dp[i-1][k]) {
            solutions.push_back(i); // Mark the item
            k=k-weights[i];
        }
        i=i-1;
    }
}

int main() {
    std::stack<int> stk; // stack for printing item values
    int i, W, k; // number of items i, maximum weight W, and maximum items k
    std::cout << "Enter the number of items: " << std::endl;
    std::cin >> i;
    std::cout << "Enter the maximum weight: " << std::endl;
    std::cin >> W;
    std::cout << "Enter the maximum items: " << std::endl;
    std::cin >> k;

    for (int n = 1; n <= i; n++) {
        std::cout << "Enter the value of the item: " << std::endl;
        std::cin >> values[n]; // store value of item
        std::cout << "Enter the weight of the item: " << std::endl;
        std::cin >> weights[n]; // store weight of item
    }

    std::cout << "OPT(" << i << ", " << W << ", " << k << ") is: " << std::endl;
    std::cout << knapsack(i, W, k) << std::endl;
    traceback(i, W);
    for (int n : solutions)
        stk.push(n);

    if (stk.empty())
        std::cout << "No items were included!";
    else if (stk.size() == 1)
        std::cout << "The item value included is: ";
    else
        std::cout << "The item values included are: ";

    while(!stk.empty()) {
        std::cout << stk.top() << " ";
        stk.pop();
    }
    std::cout << std::endl;

    return 0;
}
