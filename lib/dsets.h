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
        void addelements(int num) {
            elems_.insert(elems_.end(), num, -1);
        }

        /**
         * @brief Find root of uptree / find label of bucket
         * 
         * @param elem - element to query
         * @return int - ID of root/label
         * 
         * @throws std::out_of_range if elem is out of bounds
         */
        int find(int elem)  {
            if(elem < 0 || (unsigned) elem >= elems_.size()) {
                throw std::out_of_range("DisjointSets:find: out of bounds index " + std::to_string(elem));
            }

            if(elems_[elem] < 0) {
                return elem;
            }

            // Path compression
            int root = find(elems_[elem]);
            elems_[elem] = root;
            return root;
        }

        /**
         * @brief unions two sets together
         * 
         * @param a - ID of a node in set 1
         * @param b - ID of a node in set 2
         */
        void setunion(int a, int b) {
            // Union by rank
            a = find(a);
            b = find(b);

            // If in same set do nothing
            if(a == b) {
                return;
            }

            // Else merger smaller tree into bigger tree
            if(elems_[b] < elems_[a]) {
                elems_[b] += elems_[a];
                elems_[a] = b;
            } else {
                // equal tie break left arg
                elems_[a] += elems_[b];
                elems_[b] = a;
            }
        }

        /**
         * @brief return number of elements in a bucket
         * 
         * @param elem - ID to elem in the bucket
         * @return int - size of that bucket
         * 
         */
        int size(int elem) {
            return -1*elems_[find(elem)];
        }
    private:
        std::vector<int> elems_;  
};
