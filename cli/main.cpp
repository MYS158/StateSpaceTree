#include "console.hpp"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using Entry = std::pair<std::string, std::string>;

static const std::vector<Entry> k_problems = {
    {"nqueens",  "N-Queens"},
    {"8puzzle",  "8-Puzzle"},
    {"tsp",      "TSP (Traveling Salesman)"},
};

static const std::vector<Entry> k_strategies = {
    {"bfs",          "BFS  (Breadth-First Search)"},
    {"dfs",          "DFS  (Depth-First Search)"},
    {"backtracking", "Backtracking"},
    {"ucs",          "UCS  (Uniform-Cost Search)"},
};

static bool is_valid(const std::string& key, const std::vector<Entry>& items) {
    return std::any_of(items.begin(), items.end(),
        [&](const Entry& e){ return e.first == key; });
}

/// Prints a numbered menu and returns the selected key, or empty string on bad input.
static std::string prompt_menu(const char* title, const std::vector<Entry>& items) {
    std::cout << ansi::bold << ansi::cyan << title << ansi::reset << "\n";
    for (std::size_t i = 0; i < items.size(); ++i)
        std::cout << "  " << ansi::yellow << "[" << (i + 1) << "]"
                  << ansi::reset << "  " << items[i].second << "\n";
    std::cout << "\n> ";
    int choice = 0;
    if (!(std::cin >> choice) || choice < 1 || choice > static_cast<int>(items.size()))
        return {};
    return items[static_cast<std::size_t>(choice - 1)].first;
}

/// Stub dispatcher — prints resolved selection; wired to engine in a later sprint.
static void dispatch(const std::string& problem, const std::string& strategy) {
    std::cout << "\n"
              << ansi::bold << "Problem:  " << ansi::reset << problem  << "\n"
              << ansi::bold << "Strategy: " << ansi::reset << strategy << "\n"
              << ansi::yellow << "(engine integration pending)" << ansi::reset << "\n";
}

int main(int argc, char* argv[]) {
    enable_ansi();

    std::string problem_arg, strategy_arg;
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--problem") == 0 && i + 1 < argc)
            problem_arg = argv[++i];
        else if (std::strcmp(argv[i], "--strategy") == 0 && i + 1 < argc)
            strategy_arg = argv[++i];
    }

    if (!problem_arg.empty() && !is_valid(problem_arg, k_problems)) {
        std::cerr << ansi::red << "Unknown problem: " << problem_arg << ansi::reset << "\n";
        problem_arg.clear();
    }
    if (!strategy_arg.empty() && !is_valid(strategy_arg, k_strategies)) {
        std::cerr << ansi::red << "Unknown strategy: " << strategy_arg << ansi::reset << "\n";
        strategy_arg.clear();
    }

    std::cout << ansi::bold << ansi::cyan
              << "╔══════════════════════════════╗\n"
                 "║   State-Space Tree Solver    ║\n"
                 "╚══════════════════════════════╝\n"
              << ansi::reset << "\n";

    if (problem_arg.empty())
        problem_arg = prompt_menu("Select a problem:", k_problems);
    if (strategy_arg.empty())
        strategy_arg = prompt_menu("Select a strategy:", k_strategies);

    if (problem_arg.empty() || strategy_arg.empty()) {
        std::cerr << ansi::red << "Invalid selection.\n" << ansi::reset;
        return 1;
    }

    dispatch(problem_arg, strategy_arg);
    return 0;
}
