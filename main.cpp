#include "test/TestGenerator.h"
#include "src/SolutionBase.h"
#include "src/KnapsackSolution.h"
#include "src/GreedySolution.h"

int main(int argc, char* argv[]) {
    std::string in = argv[1];
    std::string out = argv[2];
    std::string solution = argv[3];

    KnapsackSolution knapsackSolution;
    GreedySolution greedySolution;

    std::ifstream test_in(in);
    std::ofstream solution_out(out);
    if (solution == "greedy"){
        greedySolution.solve(test_in, solution_out);
    } else{
        knapsackSolution.solve(test_in, solution_out);
    }
    test_in.close();
    solution_out.close();
}
