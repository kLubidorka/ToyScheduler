#include "KnapsackSolver.h"

void KnapsackSolver::solve(const KnapsackSolver::WeightType &W, const std::vector<WeightType> &w,
                           const std::vector<CostType> &c, std::vector<std::size_t> &res) {
    const std::size_t n = w.size();
    if (n != c.size() || n == 0) {
        return;
    }
    std::vector<std::vector<CostType>> dp(n);

    // loading dp base
    dp[0] = std::vector<CostType>(W + 1, 0);
    for (std::size_t i = w[0]; i <= W; ++i) {
        dp[0][i] = c[0];
    }

    // dp steps
    for (std::size_t i = 1; i < n; ++i) {
        dp[i] = dp[i - 1];
        for (WeightType weight = w[i]; weight <= W; ++weight) {
            dp[i][weight] = std::max(dp[i][weight], dp[i - 1][weight - w[i]] + c[i]);
        }
    }

    // calculating steps
    res.clear();
    WeightType weight = W;
    for (std::size_t i = n - 1; i > 0; --i) {
        if (dp[i - 1][weight] != dp[i][weight]) {
            weight -= w[i];
            res.push_back(i);
        }
    }
    if (dp[0][weight] != 0) {
        res.push_back(0);
    }
    std::reverse(res.begin(), res.end());
}
