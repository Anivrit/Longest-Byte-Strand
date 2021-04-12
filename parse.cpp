//MUST BE RUN IN C++ 11 OR BETTER
/*
parse through the bytes.

Now, we loop through every single permutation of two files.

STD Search will give iterator to where sequence starts. Subtract from begin to get the offset

*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;



vector<string> fileNames;

vector<int> readFile(string filename){
    fstream file(filename,ios::in | ios::out | ios::binary);
    vector<int> v;
    char temp;
     while(!file.eof()){
        file.read(&temp, 1);
        v.push_back(static_cast<int>(temp));
    }
    return v;
}


vector<int> longestStrandTwoFiles(vector<int> X, vector<int> Y)
{
    int l1 = X.size();
    int l2 = Y.size();
    int lfinal = 0;
    int endIndX;
    int longest[2][l2];
    int curRow = 0;

    for (int i = 0; i <= l1; i++) {
        for (int j = 0; j <= l2; j++) {
            if (i == 0 || j == 0) {
                longest[curRow][j] = 0;
            }
            else if (X[i - 1] == Y[j - 1]) {
                longest[curRow][j] = longest[1 - curRow][j - 1] + 1;
                if (longest[curRow][j] > lfinal) {
                    lfinal = longest[curRow][j];
                    endIndX = i - 1;
                }
            }
            else {
                longest[curRow][j] = 0;
            }
        }
        curRow = 1 - curRow;
    }
 
    if (lfinal == 0) {
        return vector<int>();
    }
 
    else{
        vector<int>::const_iterator first = X.begin() + endIndX-lfinal+1;
        vector<int>::const_iterator last = X.begin() + endIndX+1;
        vector<int> newVec(first, last);
        return newVec;
    }
}

vector<vector<int>> parseDir(){
    vector<vector<int>> files;
    string path = std::__fs::filesystem::current_path().string() + "/Data";
    for (const auto & file : std::__fs::filesystem::directory_iterator(path)){
        string filepath = file.path().string();
        fileNames.push_back(filepath);
        files.push_back(readFile(filepath));
    }
    return files;
}

vector<int> maxStrandNFiles(vector<vector<int>> files){
    vector<int> temp;
    vector<int> longest = vector<int>();
    for(int i = 0; i<files.size(); i++){
        for(int j = i;j<files.size(); j++){

            temp = longestStrandTwoFiles(files[i],files[j]);
            if(temp.size() > longest.size()){
                longest = temp;
            }
        }
    }
    return longest;
}

void findMatches(vector<vector<int>> files, vector<int> longest){
    int length = longest.size();
    cout << "Length: " << length << endl;
    for(int i = 0; i<files.size(); i++){
        auto it = search(files[i].begin(),files[i].end(),longest.begin(),longest.end());
        if(it != files[i].end()){
            cout << "File : " << fileNames[i] << " , ";
            cout << "Offset : " << (it - files[i].begin()) << endl;
        }
    }
    
}
 
int main(){
    vector<vector<int>> parsedFiles = parseDir();
    vector<int> longestStrand = maxStrandNFiles(parsedFiles);
    
    findMatches(parsedFiles,longestStrand);
}