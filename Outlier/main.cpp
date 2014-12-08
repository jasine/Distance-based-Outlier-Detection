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
#include "getopt.h"
using namespace std;

extern float  Distance(const Point& x, const Point& y);
int NItem;
int NAttr;
float fraction;
float radius;
int k;
string dataFileName;
int countOfOutlier = 0;
vector<string> outlierResult;
ifstream in;
vector<Point*> data;
vector<string> ItemIds;
Point* p;

bool optionInput(int argc, char ** argv)
{
	int flag = 1;//1:参数正确 0:参数为帮助 -1:参数错误
	if (argc == 2)
	{
		if ('h' == (getopt(argc, argv, ":h")) )
		{
			cout <<
				"Description:"<<endl<<
				"Distance-based Outlier Detection"<<endl<<endl<<
				"Input parameters : "<<endl<<
				"- r <Input file>"<<endl<<
				"- n <Number of items in the file>"<<endl<<
				"- a <Number of attributes of each item> "<<endl<<
				"- c <A fraction of total items>"<<endl<<
				"- d <Neighborhood radius>"<<endl<<endl<<
				"Example : "<<endl<<
				"./Outlier - r xxx.txt –n 100000 –a 5 –c 0.9988 –d 2.5"<<endl<<endl<<
				"Input data format : "<<endl<<
				"itemID attr1 attr2 attr3 attr4 ... "<<endl<<
				"itemID attr1 attr2 attr3 attr4 ... "<<endl<<
				"..."<<endl<<endl<<
				"Output : "<<endl<<
				"Number of outliers"<<endl<<
				"The IDs of the outliers Execution time"<<endl<<endl<<
				"Author : "<<endl<<
				"HappyShadowWalker  dongbo jasine  "<<endl;
			flag=0;
		}
		else
		{
			flag = -1;
		}
	}
	else if (argc == 11)
	{
		int oc;                     /*选项字符 */
		while ((oc = getopt(argc, argv, ":r:n:a:c:d:")) != -1)
		{
			switch (oc)
			{
				case 'r':
				{
					dataFileName = optarg;
					ifstream in(dataFileName);
					if (!in)
					{
						cerr << "Input file does not exist"<<endl;
						flag = -1;
					}
				}
				break;
				case 'n':
				{
					NItem = atoi(optarg);
					if (NItem < 1)
					{
						cerr << "Number of items in the file must more than 0"<< endl;
						flag= -1;
					}
				}
				break;
				case 'a':
				{
					NAttr = atoi(optarg);
					if (NAttr < 1)
					{
						cerr << "Number of attributes of each item must more than 0"<<endl;
						flag= -1;
					}
				}
				break;
				case 'c':
				{
					fraction = atof(optarg);
					if (fraction >1||fraction<0 )
					{
						cerr << "A fraction of total items must between 0 and 1"<<endl;
						flag= -1;
					}
				}
				break;
				case 'd':
				{
					radius = atof(optarg);//change atoi() to atof() by jasine 2014.12.8
					if (radius <=0)
					{
						cerr << "Neighborhood radius must more than 0"<<endl;
						flag= -1;
					}
				}
				break;
				case 0:
				{
					flag= -1;
				}
				break;
			}
		}
	}
	else
	{
		cout << "require more arguments" << endl;
		flag= -1;
	}
	if (flag <= 0)
	{
		if (flag == -1)
		{
			cout << "Input -h to get more help and information" << endl;
		}
		exit(-1);
	}
	cout << "Processing, please wait.." << endl;	
}

int main(int argc, char ** argv)
{		
	
	optionInput(argc, argv);//Deal with arguments

	string ItemId;
	float val;
	int DIM = NAttr;
	k = (int)NItem*(1 - fraction) + 1;
	in.open(dataFileName);
	//Read the data from file
	clock_t start, end;
	start = clock();
	while (!in.eof()) {
		p = new Point(DIM);
		in >> ItemId;
		ItemIds.push_back(ItemId);
		for (int i = 0; i < DIM; i++) {
			in >> val;
			(*p)[i] = val;
		}
		data.push_back(p);
	}
	// construct k-d tree
	kdtree Tr(DIM);
	Tr.BuildTree(data);
	Tr.traverse(Tr.getRoot());
	bool result;
	for (int i = 0; i < NItem; i++) {
		vector<Node*> neighbors = Tr.get_knn(*data[i], k);
		Point* remotePoint = (neighbors[0])->getPoint();
		float remoteDistance = Distance(*remotePoint, *data[i]);
		for (int j = 1; j < neighbors.size(); j++) {
			remotePoint = (neighbors[j]->getPoint());
			float d = Distance(*remotePoint, *data[i]);
			if (d > remoteDistance) {
				remoteDistance = d;
			}
		}
		if (remoteDistance > radius) {
			result = true;
		}
		else {
			result = false;
		}
		if (result) {
			outlierResult.push_back(ItemIds[i]);
			countOfOutlier++;
		}
	}
	cout << "Number of outliers:" << countOfOutlier << endl;
	cout << "The IDs of the outliers:" << endl;
	if (countOfOutlier > 0) {
		for (int j = 0; j < outlierResult.size(); j++) {
			cout << outlierResult[j] << endl;
		}
	}
	else {
		cout << "There is no outlier data" << endl;
	}
	end = clock();
	double durationTime = (double)(end - start) / CLK_TCK;
	cout << "Execution time:" << durationTime << "seconds" << endl;
	in.close();
}

