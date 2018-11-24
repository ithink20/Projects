#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <sstream>
#include <cstdlib>

using namespace std;

vector<vector<string> > vector_object(const char *file_name) {
    ifstream fileName;
    fileName.open(file_name);
    string d;
    vector <string> myVec;
    vector<vector<string> > data;
    int i = 0;
    while (!fileName.eof()) {
       fileName >> d;
       stringstream ss(d);
       vector <string> myVec;
       string token;
       while (getline(ss, token, ',')) {
            myVec.push_back(token);
       }
       data.push_back(myVec);
       i += 1;
    }
    data.erase(data.end() - 1);
    return data;
}
int main() {
    char file_name[10];
    cout << "Enter the file name (without .csv)\n";
    cin >> file_name;
    strcat(file_name,".csv");
    vector <vector <string> > data = vector_object(file_name);
            cout << "Data present in " << file_name <<" are : \n";
            string op;
            for (int i = 0; i < data.size(); ++i) {
                    for(int j=0;j < data[0].size(); ++j){
                        cout << data[i][j] <<" ";
                    }
                    cout << endl;
            }

    return 0;
}
