#ifndef POINT_H
#define POINT_H

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
using namespace std; 
// Data points

class Point {
private:
  float* coord; 
public:
  int DIM;
  Point(int dim){
  	DIM=dim;
  	coord=new float[DIM];
  }
  Point(float pnt[] ) {      //构造函数
	  for( int i = 0 ; i < DIM ; i ++ ) 
		  coord[i] = pnt[i]; 
  }; 
  float& operator[] (int i)  { 
	  return coord[i] ; 
  }	; 
  const float& operator[] (int i) const  { 
	  return coord[i] ; 
  }      ;
  Point& operator= (Point& pnt) {   //类赋值
	  for( int i = 0 ; i < DIM ; i ++ ) { 
		  coord[i] = pnt.coord[i] ; 
	  } 
  } ; 
  ~Point(){
     delete[] coord;
  }
}; 

#endif

