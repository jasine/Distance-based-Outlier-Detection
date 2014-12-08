#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <string>
#include <sstream>
#include <queue>
#include <ctime>
#include <functional>
#include "KdTree.h"
using namespace std; 

extern float  Distance( const Point& x, const Point& y );
int NItem;
int NAttr;
float fraction;
float radius;
int k;
string dataFileName;
int countOfOutlier=0;
vector<string> outlierResult;
ifstream in;
vector<Point*> data; 
vector<string> ItemIds;
Point* p ;
void optionInput(int argc,char * argv[]){
	//cout<<argc<<endl;
	if(argc==11){
		dataFileName=argv[2];
		NItem=atoi(argv[4]);
		NAttr=atoi(argv[6]);
		fraction=atof(argv[8]);
		radius=atoi(argv[10]);
	}
	else{
		cout<<"The input argument is wrong,Please check the arguments."<<endl;
	}
}

int main(int argc,char * argv[]) 
{ 
  //
	/*dataFileName="Data500.txt";
	cout<<"NumberN:AttNum:Fraction:Radius"<<endl;
	cin>>NItem>>NAttr>>fraction>>radius;*/
  //
  optionInput(argc,argv);
  string ItemId;
  float val; 
  int DIM=NAttr;    //Î¬Êý
  k=(int)NItem*(1-fraction)+1;
  in.open(dataFileName);
  //Read the data from file
  clock_t start, end; 
  start=clock();
  while( !in.eof()) {
    p = new Point(DIM);  
    in>>ItemId;        
	ItemIds.push_back(ItemId);
    for( int i =  0 ; i < DIM ; i ++ ) {
      in>> val ; 
      (*p)[i] = val ; 
    }
    data.push_back(p); 
  }
  // construct k-d tree
  kdtree Tr(DIM) ; 
  Tr.BuildTree(data); 
  Tr.traverse(Tr.getRoot()); 
  bool result;
  for(int i=0;i<NItem;i++){
	  vector<Node*> neighbors=Tr.get_knn(*data[i],k);
	  Point* remotePoint=(neighbors[0])->getPoint();
	  float remoteDistance=Distance(*remotePoint,*data[i]);
	  for(int j=1;j<neighbors.size();j++){
		  remotePoint=(neighbors[j]->getPoint());
		  float d=Distance(*remotePoint,*data[i]);
		  if(d>remoteDistance){
			  remoteDistance=d;
		  }
	  }
	  if(remoteDistance>radius){
		  result=true;
	  }
	  else{
		  result=false;
	  }
	  if(result){
		  outlierResult.push_back(ItemIds[i]);
		  countOfOutlier++;
	  }
  }
  cout<<"Number of outliers:"<<countOfOutlier<<endl;
  cout<<"The IDs of the outliers:"<<endl;
  if(countOfOutlier>0){
    for(int j=0;j<outlierResult.size();j++){
	  cout<<outlierResult[j]<<endl;
    }
  }
  else{
     cout<<"There is no outlier data"<<endl;
  }
  end = clock(); 
  double durationTime=(double)(end - start) / CLK_TCK;
  cout<<"Execution time:"<<durationTime<<"seconds"<<endl;
  in.close();
}

