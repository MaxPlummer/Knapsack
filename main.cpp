#include <iostream>
#include <vector>
#include <stack>

// global variables
int values[100]; // array of item values v
int weights[100]; // array of item weights w
int dp[100][100][100]; // 3-D matrix of solutions for tabulation
std::stack<int> itemsUsed; // stack to store/print items included in solutions

// solves the knapsack problem
int knapsack(int i, int w, int k) {
    int inf = INT_MAX; // INT_MAX represents infinity
    // iterate through the 3-D matrix
    for (int l = 0; l <= i; l++) {
        for (int m = 0; m <= w; m++) {
            for (int n = 0; n <= k; n++) {
                // implement recursive function
                if (l < n)
                    dp[l][m][n] = -inf;
                else if (m > 0 && n == 0)
                    dp[l][m][n] = -inf;
                else if (m == 0 && n > 0)
                    dp[l][m][n] = -inf;
                else if (m == 0 && n == 0)
                    dp[l][m][n] = 0;
                else if (weights[l] > m)
                    dp[l][m][n] = dp[l - 1][m][n];
                else
                    dp[l][m][n] = std::max(dp[l - 1][m][n], values[l] + dp[l - 1][m - weights[l]][n - 1]);
            }
        }
    }
    return dp[i][w][k]; // return the last value of the matrix within the bounds of the problem
}

// gets items included in solution
void traceback(int i, int w, int k) {
    while (i > 0 && w > 0) {
        // iterate through the 3-D matrix and check for items used in OPT(i,w,k)
        if (dp[i][w][k] != dp[i - 1][w][k]) {
            // if the element above the current element differs, it is included in the solution
            itemsUsed.push(i); // place the item in the stack
            w = w - weights[i]; // next valid column of w
        }
        i = i - 1; // next row of i
    }
}

int main() {
    int i, w, k; // number of items i, maximum weight W, and size of subset k
    std::cout << "Enter the number of items: " << std::endl;
    std::cin >> i;
    std::cout << "Enter the maximum weight: " << std::endl;
    std::cin >> w;
    std::cout << "Enter the size of the subset: " << std::endl;
    std::cin >> k;

    for (int n = 1; n <= i; n++) {
        std::cout << "Enter the value of the item: " << std::endl;
        std::cin >> values[n]; // store value of item
        std::cout << "Enter the weight of the item: " << std::endl;
        std::cin >> weights[n]; // store weight of item
    }

    // call knapsack function to solve OPT(i,W,k)
    int res = knapsack(i, w, k);
    // get items included in solution
    traceback(i, w, k);
    // print items included from the stack
    if (itemsUsed.empty() || res <= 0) // if the stack is empty or the result is 0 or less, there is no solution
        std::cout << "OPT(" << i << "," << w << "," << k << ") has no solution!" << std::endl;
    else { // otherwise, the solution is printed
        std::cout << "OPT(" << i << "," << w << "," << k << ") is: " << res << std::endl;
        if (itemsUsed.size() == 1)
            std::cout << "The item value included is: ";
        else
            std::cout << "The item values included are: ";
        // print items included in the solution
        while (!itemsUsed.empty()) {
            std::cout << itemsUsed.top() << " ";
            itemsUsed.pop();
        }
        std::cout << std::endl;
    }

    // exit
    return 0;
}
