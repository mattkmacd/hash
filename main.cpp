#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <bits/stdc++.h>

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

void segmenter(vector<string> fileNames){
	fstream file;
	string word, fileName, append;
	int fileCount = 0;
	int done = 0;

	append = "../Hash/sm_doc_set/";
	fileName = fileNames[1].c_str();
	append = append + fileName;
	cout << append << endl;
	file.open(append);
	
	if(file.is_open()) {
		cout << fileNames[1].c_str() << endl;
	}
	else{
		cout << "broke" << endl;
	}
	while(file >> word){
		cout << word << endl;
	}
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


int main()
{
    string dir = string("sm_doc_set");
    vector<string> files = vector<string>();

    getdir(dir,files);

    for (unsigned int i = 0;i < files.size();i++) {
        cout << files[i] << endl;
    }
    segmenter(files);
    return 0;
}











