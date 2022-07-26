#include <iostream>
#include "BST.h"
#include <random>
#include <vector>
#include <algorithm>

#define rand_between_inclusive(a, b) rand()%(b-a+1)+a

const int TREE_NODE_COUNT = 100000;

float rand_float()
{
    int temp = rand_between_inclusive(500, 100000);
    int divisor = rand_between_inclusive(1, 1221);
    return (float)temp / divisor;
}

std::vector<float> refill_tree_rand(BST<float>& bst)
{
    bst.delete_tree();
    std::vector<float> result_vec;
    for (int i = 0; i < TREE_NODE_COUNT; i++)
    {
        float temp = rand_float();
        bst.insert(temp);
        if(std::find(result_vec.begin(), result_vec.end(), temp) == result_vec.end())
            result_vec.push_back(temp);
    }

    std::sort(result_vec.begin(), result_vec.end());
    return result_vec;
}

void print_vec(std::vector<float>& vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";
}

#define prnt(a) std::cout << (a) << "\n"

struct BSTTester
{
    static bool compare_to_vec(BST<float>& bst, std::vector<float>& vec)
    {
        auto bst_vec = parseIntoVector(bst);
        int n = bst.get_node_count();

        float flag = true;
        for (int i = 0; i < n; i++)
            if (bst_vec[i] != vec[i])
                flag = false;

        return flag;
    }

    static std::vector<float> parseIntoVector(BST<float>& bst)
    {
        std::vector<float> result;
        parseDFSInOrder(result, bst._root);
        return result;
    }

    static void parseDFSInOrder(std::vector<float>& vec, TreeNode<float>* node)
    {
        if (node->left != NULL)
            parseDFSInOrder(vec, node->left);

        vec.push_back(node->value);

        if (node->right != NULL)
            parseDFSInOrder(vec, node->right);
    }

    friend class BST<float>;
};

int main()
{
    srand(0xdba1098c);
    std::ios_base::sync_with_stdio(false);

    BST<float> bst;

    auto cmp_vector = refill_tree_rand(bst);

    //print_vec(cmp_vector);
    //bst.print_sorted();

    prnt(bst.get_node_count());
    prnt(bst.get_node_count() == cmp_vector.size());
    prnt(bst.get_height());

    prnt(BSTTester::compare_to_vec(bst, cmp_vector));

    // Testing deletion
    for (int i = 0; i < 15000; i++)
    {
        size_t randInd = rand() % bst.get_node_count();
        float value = cmp_vector[randInd];

        bst.delete_value(value);
        cmp_vector.erase(cmp_vector.begin() + randInd);
    }

    prnt(BSTTester::compare_to_vec(bst, cmp_vector));

    std::vector<int> failures;
    bool flag = true;
    // Testing successors
    for (int i = 0; i < bst.get_node_count() - 1; i++)
    {
        //test each existing node and one between them
        float value = cmp_vector[i];
        float expectedValue = cmp_vector[i + 1];
        float resultValue = bst.get_successor(value);

        if (resultValue != expectedValue)
        {
            failures.push_back(i);
            flag = false;
        }
    }

    // for debugging successor failures
    for (auto failureIndex : failures)
    {
        //test each existing node and one between them
        float value = cmp_vector[failureIndex];
        float expectedValue = cmp_vector[failureIndex + 1];
        float resultValue = bst.get_successor(value);
    }

    prnt(flag);

    prnt(bst.is_binary_search_tree());

    cmp_vector = refill_tree_rand(bst); // deleting and refilling tree

    prnt(bst.get_min() == cmp_vector[0]);
    prnt(bst.get_max() == cmp_vector[cmp_vector.size()-1]);
    prnt(bst.is_binary_search_tree());

    system("pause");
}