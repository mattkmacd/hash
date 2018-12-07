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
	collision(const collision & src);
	collision(string name1, string name2, int num);
	~collision();
	
	string printVals() const;
	string getFile1() const;
	string getFile2() const;
	int getNum() const;
	int repeat(vector<collision> list) const;
	

private:
	string fileName1;
	string fileName2;
	int numCollisions;
};


//Function implementations:

collision::collision()
{
	fileName1 = "";
	fileName2 = "";
	numCollisions = 0;
}

collision::collision(const collision & src)
{
	fileName1 = src.fileName1;
	fileName2 = src.fileName2;
	numCollisions = src.numCollisions;
}

collision::collision(string name1, string name2, int num){
	fileName1 = name1;
	fileName2 = name2;
	numCollisions = num;
}

collision::~collision(){
}

string collision::printVals() const{
	string temp = std::to_string(numCollisions);
	string result = "Collisions: " + temp + " " + fileName1 + " " + fileName2 + "\n";
	return result;
}

string collision::getFile1() const{
	return fileName1;
}
string collision::getFile2() const{
	return fileName2;
}

int collision::getNum() const{
	return numCollisions;
}

int collision::repeat(vector<collision> list) const{
	for(int i = 0; i < list.size(); i++){
		if(fileName1 == list[i].getFile2() && fileName2 == list[i].getFile1()){
			return 1;
		}
	}
	return 0;
}




#endif
