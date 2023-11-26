#include <iostream>
#include <vector>
#include <stack>

// global variables
int values[100]; // array of item values v
int weights[100]; // array of item weights w
int sizes[100]; // array of subset sizes k
int dp[100][100]; // matrix of solutions for tabulation
std::stack<int> solutions; // stack to store/print items included in solutions

// solves the knapsack problem
int knapsack(int i, int W, int k) {
    for (int n = 0; n <= i; n++) {
        for (int w = 0; w <= W; w++) {
            if (n == 0 || w == 0)
                dp[n][w] = 0;
            else if (weights[n] <= w)
                dp[n][w] = std::max(values[n] + dp[n - 1][w - weights[n]], dp[n - 1][w]);
            else
                dp[n][w] = dp[n - 1][w];
        }
    }
    return dp[i][W];
}

// gets items included in solution
void printHelper(int i, int w, int k) {
    while (i > 0 && w > 0) {
        if (dp[i][w] != dp[i - 1][w]) {
            solutions.push(i); // Mark the item
            w = w - weights[i];
        }
        i = i - 1;
    }

    // print items included from the stack
    if (solutions.empty())
        std::cout << "No items were included!";
    else if (solutions.size() == 1)
        std::cout << "The item value included is: ";
    else
        std::cout << "The item values included are: ";
    while(!solutions.empty()) {
        std::cout << solutions.top() << " ";
        solutions.pop();
    }
    std::cout << std::endl;
}

int main() {
    int i, W, k; // number of items i, maximum weight W, and size of subset k
    std::cout << "Enter the number of items: " << std::endl;
    std::cin >> i;
    std::cout << "Enter the maximum weight: " << std::endl;
    std::cin >> W;
    std::cout << "Enter the size of the subset: " << std::endl;
    std::cin >> k;

    for (int n = 1; n <= i; n++) {
        std::cout << "Enter the value of the item: " << std::endl;
        std::cin >> values[n]; // store value of item
        std::cout << "Enter the weight of the item: " << std::endl;
        std::cin >> weights[n]; // store weight of item
    }

    // call knapsack function to solve OPT(i,W,k)
    std::cout << "OPT(" << i << "," << W << "," << k << ") is: ";
    std::cout << knapsack(i, W, k) << std::endl;

    // get items included in solution
    printHelper(i, W, k);

    // exit
    return 0;
}
