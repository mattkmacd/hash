#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <cctype>
#include "collision.h"

using namespace std;

/*function... might want it in some class?*/
int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

string punctRemover(string word){
	//Removes punctuation and spaces from chunks, sets capitalized letters to lower case
	//Prepares chunks to be put through the hash function
    for(int i = 0, len = word.size(); i < len; i++){
        if (ispunct(word[i])) {
            word.erase(i--, 1);
            len = word.size();
        }
        else if(word[i] <= 'Z' && word[i] >= 'A') {
            word[i] = word[i] - ('Z' - 'z');
        }
    }

    return word;

}

int Hashish(string chunk){
	//Sets the hash values to the ASCII sum of the chunks
    int sum = 0;

    for(int i = 0, len = chunk.size(); i < len; i++){
        sum += chunk[i];
    }
      
    return sum;
}


vector<int> segmenter(string fileName, string path, int inChunk){
	vector<int> storage;

	fstream file1;
	
	string word1, word2, append, chunk;
	int fileCount = 0;
	int wordCount;
	int memeCount = 0;
	int done = 0;
	int chunkHash;
	//Runs through the files and finds each of the n word chunks
	//Uses 2 files which iterate seperately to keep track of the first word and add the next n - 1 words to the chunk
	//Returns vector of the hash values for a file
	while(done == 0){
		wordCount = 0;
		//append = "../Hash/sm_doc_set/";
		append = path;
		append = append + fileName.c_str();
		
		file1.open(append);

		while(file1 >> word1 && done == 0){
			fstream file2;
			file2.open(append);
			wordCount = 0;
			chunk = word1;
			while(file2 >> word2 && wordCount < memeCount){
				wordCount++;
			}
			wordCount = 0;
			while(file2 >> word2 && wordCount < inChunk - 1){
				chunk = chunk + word2;
				wordCount++;
			}
			if(wordCount != inChunk - 1){
				done = 1;
			}
			else{
				chunk = punctRemover(chunk);
				chunkHash = Hashish(chunk);
				storage.push_back(chunkHash);
			}
			memeCount++;
		}
		done = 1;
	}
	return storage;
}

void sort(vector<collision> &list){
	//Descending insertion sort
	int i, j;
	collision temp;
	for(i = 0; i < list.size(); i++){
		temp = list[i];
		j = i;
		while(j > 0 && list[j - 1].getNum() < temp.getNum()){
			list[j] = list[j - 1];
			j = j - 1;
			list[j] = temp;
		}
		
	}

}

int main(int argc, char *argv[])
{
	int inChunk;
	int inLimit;
	
	std::string inPath = argv[1];
	inChunk = atoi(argv[2]);
	inLimit = atoi(argv[3]);


	int wackCheck = 0;
	int wackCount = 0;
	
	//Sets up hash table
	string **hash = new string*[10000];
	for(int g = 0; g < 10000; g++){
		hash[g] = new string[1000];
	}
	
	vector<int> temp; //Temporarily stores hash values of each file
	vector<int> checks; //Stores all hash values with 2+ collisions

    string dir = string(inPath);
    vector<string> files = vector<string>();

    getdir(dir,files);
    //Associates file strings with hash values on the hash tables
    for(int j = 0; j < files.size(); j++){
   		temp = segmenter(files[j], inPath, inChunk);
   		
   		for(int i = 0; i < temp.size(); i++){
    		wackCheck = 0;
    		wackCount = 0;
    
    		while(wackCheck == 0){
    			if(hash[temp[i]][wackCount].find(".txt") != string::npos && files[j].compare(hash[temp[i]][wackCount]) != 0){
    				wackCount++;
    			}
    			else{
    				wackCheck = 1;
    			}
    		}
    		if(wackCount == 1){
    			checks.push_back(temp[i]);
    		}
    		hash[temp[i]][wackCount] = files[j];
  		}
  		
    }
	
    string searchA, searchB;
    int collisionCount;
    int foundFile = 0;
    collision tempCol;
    vector <collision> printStructs; //vector w/ all nodes w/ collision greater than 200

	for(int i = 0; i < files.size() - 1; i++){//get filename A
    	searchA = files[i];
        for(int j = 1; j < files.size(); j++){//get filename B
            searchB = files[j];
            collisionCount = 0;

            for(int q = 0; q < checks.size(); q++){//check hash entries for occurance of A and B
                int hashIndex = checks[q];
                int z = 0;

                //check filenames w/ that hash key to see if A and B occur
                //while(z < 1000 && foundFile < 2){//while both files not found or more elements in second dim of hash table
                while(hash[hashIndex][z].find(".txt") != string::npos){
                    if(hash[hashIndex][z] == searchA || hash[hashIndex][z] == searchB){
                        foundFile++;
                    }
                    z++;
                }

                if( foundFile == 2){ //if both fils found w/ that hash key, add to collision count
                    collisionCount++;
                }

                foundFile = 0;
            }
			//If the number of collisions is more than the limit, it is added to the printStructs vector
            if(collisionCount > inLimit){
            	tempCol = collision(searchA, searchB, collisionCount);
            	if(tempCol.repeat(printStructs) == 0){
               		printStructs.push_back(tempCol);
               	}
            }
        }
    }
    //Sorts the collisions in descending order
	sort(printStructs);
    for(int i = 0; i < printStructs.size(); i++){
        cout << printStructs[i].printVals() << endl;
    }
    
    return 0;
}
