Distance-based-Outlier-Detection
================================

A realization of Distance-based-Outlier-Detection in data mining

##Input parameters:
-r <Input file>
-n <Number of items in the file>
-a <Number of attributes of each item> -c <A fraction of total items>
-d <Neighborhood radius>

##Example:
./Outlier -r xxx.txt 每n 100000 每a 5 每c 0.9988 每d 2.5

##Input data format:
itemID attr1 attr2 attr3 attr4 ... 
itemID attr1 attr2 attr3 attr4 ... 
...

##Output:
Number of outliers
The IDs of the outliers Execution time