#pragma once
#include <vector>
#include <utility>      // std::pair, std::make_pair
#include <string>       // std::string
#include <iostream>     // std::cout

class KDTree
{
    private:


        struct KDTreeNode
        {

        };


    public:
        /**
         * @brief Construct a new KDTree object
         * 
         * @param allPoints, takes in a vector of Pair of points with an x/y to sort and create a tree
         */
        KDTree(const std::vector<std::pair<double,double>>& allPoints);
        
        KDTree();
    private:
        KDTreeNode *root;
        size_t size;
};