/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>
#include <time.h>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(first[curDim]<second[curDim])
      return true;
    
    if(first[curDim]==second[curDim]){
      if(first<second) 
        return true;
    }
    return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double current = 0;
    for(int i = 0; i<Dim; i++){ // loops through and gets the distance from target to currentBest
      current+= pow( (target[i] - currentBest[i]), 2);
    }
    //current = sqrt(current);

    double newLength = 0;
    for(int i = 0; i<Dim; i++){// loops through and gets the distance from target to potential
      newLength+= pow( (target[i] - potential[i]), 2);
    }
    //newLength = sqrt(newLength);

    if(newLength<current)// if the potential is less 
      return true;
    if(newLength==current){
      if(potential<currentBest)
        return true;
    }

     return false;
}

template <int Dim>
void KDTree<Dim>::quickSelect(vector<Point<Dim>>& newPoints, int left, int right, int index, int dim){
  
  if(left==right)// if the vector is pointing to the same then we are done sorting
    return;

  srand(time(NULL));
  int PointIndex = left + (rand() % (right-left)); // chooses a random value between the left and right values
  PointIndex = partition(newPoints, left, right, PointIndex, dim);

  if(index==PointIndex){ // if the point index is the middle then return
    return;
  } else if(index<PointIndex){
    return quickSelect(newPoints, left, PointIndex-1, index, dim);
  }else{
    return quickSelect(newPoints, PointIndex+1, right, index, dim);
  }


}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& newPoints, int left, int right, int index, int dim){


  Point<Dim> pivotPoint = newPoints[index];// gets the pivot value
  typename std::vector<Point<Dim>>::iterator itRight = newPoints.begin() + right; // creates an iterator that points to the right
  typename std::vector<Point<Dim>>::iterator itPivot = newPoints.begin()+ index; // creates an iterator that points to the pivot
  typename std::vector<Point<Dim>>::iterator itLeft = newPoints.begin()+ left; // creates an iterator that points to the left
  int counter = left; // counter for the return value

   std::iter_swap(itPivot, itRight); // swaps the right and Pivot 

  for(typename std::vector<Point<Dim>>::iterator it = (newPoints.begin()+ left) ; it != (itRight); ++it){// loops through from left to the right swapping if larger than the pivot
    if((*it)[dim] < pivotPoint[dim]){// if the current value is less than the pivot value at the given dimension
       std::iter_swap(it, itLeft); // swaps the current and left position 
        itLeft++;
        counter++;
    }
    else if((*it)[dim] == pivotPoint[dim]){ // if the current value at the given dimension is equal then we do the Point<
      if(*it < pivotPoint){// swap if it matches the point tie breaker
       std::iter_swap(it, itLeft); // swaps the current and left position 
        itLeft++;
        counter++;
      }
    }
  }

   std::iter_swap(itRight, itLeft); // swaps the right and Pivot back into the original place
  return counter;
}

template <int Dim>
void KDTree<Dim>::dimensionSort(vector<Point<Dim>>& newPoints, int left, int right, int index, int dim){ // will sort the vector by its length and dimension count
  /*INVESTIGATE IN MAKING IT ITERATIVE/TAKE LESS STACK SPACE 
    (use while loop and then 3 sets of local vars?) / (make sub vectors for each fn call to make it shorter?)*/

  if(left>=right) // if we have gone past our bounds or have hit the same number return
    return;
  if(dim>=Dim) // if our dimension is too large then rest back to 0
    dim=0;

  quickSelect(newPoints, left, right, index, dim); // this will sort the inital vector by the given dimension
  dim++;
  dimensionSort(newPoints, left, index-1, (left+index-1)/2, dim); // recurse through the left and right subvectors to organize
  dimensionSort(newPoints, index+1, right, (right+index+1)/2, dim);


}
template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{

    vector<Point<Dim>> temp = newPoints; // creates a new temp vector/ and gets it median index
    int index = (temp.size()-1)/2;
    size = temp.size();
    if(!temp.empty()){ // if the vector is not empty then organize it and create the tree
      dimensionSort(temp, 0, temp.size()-1, index, 0); // sort our vector
      root = createNode(temp, 0, temp.size()-1); // creates a kd tree and sets the root to it,.
    }

    
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::createNode(vector<Point<Dim>>& newPoints, int left, int right){

  if(left>right)// if left is greater than right then we have gone past the smallest "sub vector"
    return NULL;

  if(left==right){ // if left == right then we are at a leaf node
    int index = (left+right)/2;
    KDTreeNode* leaf = new KDTreeNode(newPoints[index]);
    return leaf;
  }

  int index = (left+right)/2;
  KDTreeNode* parent = new KDTreeNode(newPoints[index]); // creates a new leaf node based on the given index
  
  parent->left = createNode(newPoints, left, index-1); // recursively creates the left and right subtrees
  parent->right = createNode(newPoints, index+1, right);
  return parent;

}


template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
    root = copyTree(other.root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if(this != &rhs){ // if there is previous data clear it
    destroyTree(root);
    root = copyTree(rhs.root);
  }
  
  return *this;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copyTree(KDTreeNode* subtree) {
  if(subtree==NULL)// if the current node is null return null
    return NULL;

  KDTreeNode* parent = new KDTreeNode(subtree->point); // creates a new leaf node based on the given index
  
  parent->left = copyTree(subtree->left); // recursively creates the left and right subtrees
  parent->right = copyTree(subtree->right);
  return parent; // returns the current node when completed

}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   destroyTree(root);
}

template <int Dim>
void KDTree<Dim>::destroyTree(KDTreeNode* subtree){
    if(subtree==NULL)// if the subtree is NULL simply return
      return;
  
    destroyTree(subtree->left); // recurse trhough the whole tree left and right and then delete
    destroyTree(subtree->right);
    delete subtree;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return findSmallest(root, query, 0);

    //return Point<Dim>();
}

template <int Dim>
Point<Dim> KDTree<Dim>::findSmallest(KDTreeNode* subtree, const Point<Dim>& query, int dimen) const
{
  if(dimen>=Dim){dimen=0;} // if the given dimension is out of bounds then rest to 0
  if(subtree->left==NULL && subtree->right==NULL){// if the current node is a leaf node, then this is our guess
    Point<Dim> foundValue = subtree->point;
    return foundValue;
  }

  Point<Dim> firstGuess;
  Point<Dim> secondGuess;
  int tempDim = dimen+1; // a temp variable to increment the current dimension
  
  if(smallerDimVal(query,subtree->point, dimen)){ // if the current subtree is smaller than  our query in the given dimension then go down else go right and increas our dimension
    if(subtree->left !=NULL){// if the left subtree is not null then recurse down it or we have our firstGuess
      firstGuess = findSmallest(subtree->left, query, tempDim);
    }else{
      firstGuess = subtree->point;
    }

    if(shouldReplace(query, firstGuess, subtree->point)){// if true then replaced it with the new guess and check the second guess
        firstGuess = subtree->point;
    }
    if(checkHyperRect(query, firstGuess, subtree->point, dimen)){ // if our hyper circles crosses any hyper rectangles then recurse down the right tree
      if(subtree->right!=NULL){
        secondGuess = findSmallest(subtree->right, query, tempDim);
        if(shouldReplace(query, firstGuess, secondGuess)){ // if the second guess is closer then replace the first guess
          firstGuess = secondGuess;
        }
      }
    }

  }else if(query == subtree->point){ // if we are an exact match, then return the sutbree
    return subtree->point;
  }else{
    if(subtree->right!=NULL){
      firstGuess = findSmallest(subtree->right, query, tempDim);
    }else{
      firstGuess = subtree->point;
    }

    if(shouldReplace(query, firstGuess, subtree->point)){// if true then replaced it with the new guess and check the second guess
        firstGuess = subtree->point;
    }
    if(checkHyperRect(query, firstGuess, subtree->point, dimen)){ // if our hyper circles crosses any hyper rectangles then recurse down the right tree
      if(subtree->left!=NULL){
        secondGuess = findSmallest(subtree->left, query, tempDim);
        if(shouldReplace(query, firstGuess, secondGuess)){ // if the second guess is closer then replace the first guess
          firstGuess = secondGuess;
        }
      }
    }
  }


  return firstGuess;

}

template <int Dim>
bool KDTree<Dim>::checkHyperRect(const Point<Dim>& target, Point<Dim>& currentBest, Point<Dim>& split, int dimen) const
{
  double current = 0; // this portion calcualtes the radius of our hyper circle
    for(int i = 0; i<Dim; i++){ // loops through and gets the distance from target to currentBest
      current+= pow( (target[i] - currentBest[i]), 2);
    }
    

    double distance = (split[dimen] - target[dimen]);
    distance = distance*distance;
    if( distance <= current ){ // if the distance between the split and the target is less than the calcualted distance
      return true;
    }

    return false;
}



