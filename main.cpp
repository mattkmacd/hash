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
    int sum = 0;

    for(int i = 0, len = chunk.size(); i < len; i++){
        sum += chunk[i];
    }
    
    return sum;
}


vector<int> segmenter(string fileName){
	vector<int> storage;

	fstream file1;
	
	string word1, word2, append, chunk;
	int fileCount = 0;
	int wordCount;
	int memeCount = 0;
	int done = 0;
	int chunkHash;
	
	while(done == 0){
		wordCount = 0;
		append = "../Hash/sm_doc_set/";
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
			while(file2 >> word2 && wordCount < 5){
				chunk = chunk + word2;
				wordCount++;
			}
			if(wordCount != 5){
				done = 1;
			}
			else{
				chunk = punctRemover(chunk);
				chunkHash = Hashish(chunk);
				//cout << chunk << endl;
				//cout << chunkHash << endl;
				storage.push_back(chunkHash);
			}
			memeCount++;
		}
		//cout << memeCount << endl;
		done = 1;
	}
	return storage;
}

int main()
{
	int wackCheck = 0;
	int wackCount = 0;
	
	//string hash[10000][10];
	string **hash = new string*[10000];
	for(int g = 0; g < 10000; g++){
		hash[g] = new string[1000];
	}
	
	vector<int> temp;
	vector<int> checks;

    string dir = string("sm_doc_set");
    vector<string> files = vector<string>();

    getdir(dir,files);

    for (unsigned int i = 0;i < files.size();i++) {
        cout << files[i] << endl;
    }
    
    for(int j = 0; j < files.size(); j++){
   		temp = segmenter(files[j]);
   		
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
    
    if(hash[2707][0].find(".txt") != string::npos){
    	cout << "FLAM" << endl;
    }
    
    cout << checks.size() << endl;
	
    string searchA, searchB;
    int collisionCount;
    int foundFile = 0;
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
                while(z < 1000 && foundFile < 2){//while both files not found or more elements in second dim of hash table
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

            if(collisionCount > 200){
                printStructs.push_back(collision(searchA,searchB,collisionCount));
            }
        }
    }

    for(int i = 0; i < printStructs.size(); i++){
        cout << printStructs[i].printVals() << endl;
    }
        
    return 0;
}
