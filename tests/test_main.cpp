#include <cassert>
#include <memory>
#include <optional>
#include <string>
#include "node.hpp"
#include "tree.hpp"
#include "problem.hpp"
#include "search_strategy.hpp"
#include "strategies/bfs.hpp"
#include "strategies/dfs.hpp"
#include "strategies/backtracking.hpp"
#include "strategies/ucs.hpp"

// ── Node tests ────────────────────────────────────────────────────────────────

static void test_node_root() {
    Node<int> root(42);
    assert(root.state() == 42);
    assert(root.parent() == nullptr);
    assert(root.depth() == 0);
    assert(!root.cost().has_value());
    assert(root.children().empty());
}

static void test_node_child() {
    Node<int> root(1);
    Node<int>* child = root.add_child(
        std::make_unique<Node<int>>(2, &root, std::optional<double>{1.5})
    );
    assert(child->state() == 2);
    assert(child->parent() == &root);
    assert(child->depth() == 1);
    assert(child->cost().has_value());
    assert(*child->cost() == 1.5);
}

static void test_node_depth_chain() {
    Node<int> root(0);
    Node<int>* a = root.add_child(std::make_unique<Node<int>>(1, &root));
    Node<int>* b = a->add_child(std::make_unique<Node<int>>(2, a));
    assert(a->depth() == 1);
    assert(b->depth() == 2);
}

static void test_node_multiple_children() {
    Node<int> root(0);
    root.add_child(std::make_unique<Node<int>>(1, &root));
    root.add_child(std::make_unique<Node<int>>(2, &root));
    root.add_child(std::make_unique<Node<int>>(3, &root));
    assert(root.children().size() == 3);
}

static void test_node_string_state() {
    Node<std::string> root("start");
    Node<std::string>* child = root.add_child(
        std::make_unique<Node<std::string>>("goal", &root, std::optional<double>{3.0})
    );
    assert(child->state() == "goal");
    assert(child->depth() == 1);
}

// ── Tree tests ────────────────────────────────────────────────────────────────

static void test_tree_root() {
    Tree<int> tree(42);
    assert(tree.root()->state() == 42);
    assert(tree.root()->parent() == nullptr);
}

static void test_tree_expand() {
    Tree<int> tree(0);
    auto children = tree.expand(tree.root(), {
        {1, std::nullopt},
        {2, std::nullopt},
        {3, std::nullopt}
    });
    assert(children.size() == 3);
    assert(children[0]->state() == 1);
    assert(children[1]->state() == 2);
    assert(children[2]->state() == 3);
    assert(tree.root()->children().size() == 3);
}

static void test_tree_path_to() {
    Tree<int> tree(0);
    auto lvl1 = tree.expand(tree.root(), {{1, std::nullopt}});
    auto lvl2 = tree.expand(lvl1[0], {{2, std::nullopt}});

    auto path = tree.path_to(lvl2[0]);
    assert(path.size() == 3);
    assert(path[0]->state() == 0);
    assert(path[1]->state() == 1);
    assert(path[2]->state() == 2);
}

static void test_tree_path_to_root() {
    Tree<int> tree(7);
    auto path = tree.path_to(tree.root());
    assert(path.size() == 1);
    assert(path[0]->state() == 7);
}

static void test_tree_cost_to_weighted() {
    Tree<int> tree(0);
    auto lvl1 = tree.expand(tree.root(), {{1, std::optional<double>{2.0}}});
    auto lvl2 = tree.expand(lvl1[0],    {{2, std::optional<double>{3.5}}});

    auto cost = tree.cost_to(lvl2[0]);
    assert(cost.has_value());
    assert(*cost == 5.5);
}

static void test_tree_cost_to_missing_edge() {
    Tree<int> tree(0);
    auto lvl1 = tree.expand(tree.root(), {{1, std::nullopt}});
    auto lvl2 = tree.expand(lvl1[0],    {{2, std::optional<double>{1.0}}});

    assert(!tree.cost_to(lvl2[0]).has_value());
}

static void test_tree_cost_to_root() {
    Tree<int> tree(0);
    auto cost = tree.cost_to(tree.root());
    assert(cost.has_value());
    assert(*cost == 0.0);
}

// ── SearchStrategy / Problem interface tests ──────────────────────────────────

// Minimal concrete Problem: single-node graph where root is the goal.
struct TrivialProblem : Problem<int> {
    int initial_state() const override { return 42; }
    bool is_goal(const int& s) const override { return s == 42; }
    std::vector<std::pair<int, std::optional<double>>>
    successors(const int&) const override { return {}; }
};

// Custom strategy that checks the root and returns it if it's the goal.
struct RootGoalStrategy : SearchStrategy<int> {
    std::optional<std::vector<Node<int>*>>
    solve(Tree<int>& tree, const Problem<int>& problem) override {
        if (problem.is_goal(tree.root()->state()))
            return tree.path_to(tree.root());
        return std::nullopt;
    }
};

static void test_strategy_interface_extensible() {
    TrivialProblem prob;
    Tree<int> tree(prob.initial_state());
    RootGoalStrategy strategy;
    auto result = strategy.solve(tree, prob);
    assert(result.has_value());
    assert(result->size() == 1);
    assert((*result)[0]->state() == 42);
}

static void test_strategy_stubs_return_nullopt() {
    TrivialProblem prob;
    Tree<int> bfs_tree(prob.initial_state());
    Tree<int> dfs_tree(prob.initial_state());
    Tree<int> bt_tree(prob.initial_state());
    Tree<int> ucs_tree(prob.initial_state());

    assert(!BFS<int>{}.solve(bfs_tree, prob).has_value());
    assert(!DFS<int>{}.solve(dfs_tree, prob).has_value());
    assert(!Backtracking<int>{}.solve(bt_tree, prob).has_value());
    assert(!UCS<int>{}.solve(ucs_tree, prob).has_value());
}

int main() {
    test_node_root();
    test_node_child();
    test_node_depth_chain();
    test_node_multiple_children();
    test_node_string_state();

    test_tree_root();
    test_tree_expand();
    test_tree_path_to();
    test_tree_path_to_root();
    test_tree_cost_to_weighted();
    test_tree_cost_to_missing_edge();
    test_tree_cost_to_root();

    test_strategy_interface_extensible();
    test_strategy_stubs_return_nullopt();

    return 0;
}
