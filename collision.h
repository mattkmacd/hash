#ifndef collision_H
#define collison_H

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <cctype>

using namespace std;

class collision {
public:
	collision();
	collision(string name1, string name2, int num);
	~collision();
	
	string printVals() const;
	

private:
	string fileName1;
	string fileName2;
	int numCollisions;
};


//Function implementations:

collision::collision()
{
}

collision::collision(string name1, string name2, int num){
	fileName1 = name1;
	fileName2 = name2;
	numCollisions = num;
}

collision::~collision(){
	delete &fileName1;
	delete &fileName2;
	delete &numCollisions;
}

string collision::printVals() const{
	string temp = std::to_string(numCollisions);
	string result = "Collisions: " + temp + " " + fileName1 + " " + fileName2 + "\n";
	return result;
}


#endif
