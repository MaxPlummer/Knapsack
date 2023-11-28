#include <iostream>
#include <vector>
#include <stack>

// global variables
int values[100]; // array of item values v
int weights[100]; // array of item weights w
int sizes[100]; // array of subset sizes k
int DP[100][100]; // matrix of solutions for tabulation
std::stack<int> solutions; // stack to store/print items included in solutions

// solves the knapsack problem
int knapsack(int i, int W, int k) {
    for (int l = 0; l <= i; l++) {
        for (int m = 0; m <= W; m++) {
            if (l == 0 || m == 0)
                DP[l][m] = 0;
            else if (weights[l] <= m)
                DP[l][m] = std::max(values[l] + DP[l - 1][m - weights[l]], DP[l - 1][m]);
            else
                DP[l][m] = DP[l - 1][m];
        }
    }
    return DP[i][W];
}

// gets items included in solution
void traceback(int i, int w, int k) {
    while (i > 0 && w > 0) {
        if (DP[i][w] != DP[i - 1][w]) {
            solutions.push(i); // Mark the item
            w = w - weights[i];
        }
        i = i - 1;
    }
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
    int res = knapsack(i, W, k);
    // get items included in solution
    traceback(i, W, k);

    if (solutions.size() == k) {
        std::cout << "OPT(" << i << "," << W << "," << k << ") is: ";
        std::cout << res << std::endl;

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
    else
        std::cout << "OPT(" << i << "," << W << "," << k << ") has no solution." << std::endl;

    // exit
    return 0;
}
