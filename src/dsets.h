/* Binh-Minh's (bmn4) code for CS225 mp_mazes, pseudo code from lecture slides */
#pragma once
#include <vector>

class DisjointSets {
    public:
        /**
         * @brief Inserts num buckets to the end
         * 
         * @param num - number of buckets to insert
         */
        void addelements(int num);

        /**
         * @brief Find root of uptree / find label of bucket
         * 
         * @param elem - element to query
         * @return int - ID of root/label
         * 
         * @throws std::out_of_range if elem is out of bounds
         */
        int find(int elem);

        /**
         * @brief unions two sets together
         * 
         * @param a - ID of a node in set 1
         * @param b - ID of a node in set 2
         */
        void setunion(int a, int b);

        /**
         * @brief return number of elements in a bucket
         * 
         * @param elem - ID to elem in the bucket
         * @return int - size of that bucket
         * 
         */
        int size(int elem);
    private:
        std::vector<int> elems_;  
};