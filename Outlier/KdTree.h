#ifndef KDTREE_H
#define KDTREE_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <string>
#include <sstream>
#include <queue>
#include <functional>
#include "Node.h" 

using namespace std; 
typedef vector<Point*> PVec ;  //定义一个Point类型的vector

// k-d tree class 
class kdtree {
private: 
  Node* head ; 
  Node* build(vector<PVec> vec, int l, int u, int coord, Node* parent) ; 
  int DIM;
public: 
  kdtree(int dim) : head(0) {DIM=dim ;} ; 
  void traverse( Node* n ) const { 
    if(n) {  
       traverse(n->left) ; 
	   traverse(n->right) ; 
    } 
  } ; 
  void BuildTree(vector<Point*> ); 
  Node* getRoot() { return head ; } ; 
  vector<Node*> get_knn(Point& x,int); 
  void knn_traverse(Point& x, Node* top,   priority_queue<DNode, vector<DNode>, LessDNode >* current_best, int K ) ; 
}; 

#endif 

