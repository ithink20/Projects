#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <utility>
#include <fstream>
#include <sstream>
#include <list>

using namespace std;
typedef long long int lint;

// uncomment line below to enable debugging
// #define ENABLE_DEBUGGING

#if defined(ENABLE_DEBUGGING) || defined(DDD)
#define SOURCE_INFO_COUT "[" << __FUNCTION__ <<  "():" << __LINE__ << "] "
#define debug_print0(...) do { cout << SOURCE_INFO_COUT << #__VA_ARGS__ << endl; } while (0)
#define debug_print1(x) do { cout << SOURCE_INFO_COUT << #x "::" << x << endl; } while (0)
#define debug_print2(x, y) do { cout << SOURCE_INFO_COUT << #x "::" << x << ", " #y "::" << y << endl; } while (0)
#define debug_print3(x, y, z) do { cout << SOURCE_INFO_COUT << #x "::" << x << ", " #y "::" << y << ", " #z "::" << z << endl; } while (0)
#define debug_print4(x, y, z, z1) do { cout << SOURCE_INFO_COUT << #x "::" << x << ", " #y "::" << y << ", " #z "::" << z << ", " #z1 "::" << z1 << endl; } while (0)
#else
#define debug_print0(...)
#define debug_print1(x)
#define debug_print2(x, y)
#define debug_print3(x, y, z)
#define debug_print4(x, y, z, z1)
#endif

struct patch_entry {
    bool keep_old_data;
    string append_data;
    string match_data;
    patch_entry(): keep_old_data(true) {}
};

vector <string> get_data(fstream &file) {
    string linebuffer;
    vector <string> temp;
    while (file && getline(file, linebuffer)) {
        temp.push_back(linebuffer);
    }
    return temp;
}

int get_l_r(string temp) {
    string ans = "";
    for (int i = 0; i < temp.size(); ++i) {
        if (temp[i] == ',') {
            break;
        }
        if (isdigit(temp[i]))
            ans += temp[i];
    }
    int res = 0;
    for (int i = 0; i < ans.length(); ++i) {
        res = res * 10 + (ans[i] - '0');
    }
    return res;
}

int main() {
    fstream input_file, patch_file;
    ofstream output_file("/Users/vikaschaurasiya/Desktop/output.txt");
    input_file.open("/Users/vikaschaurasiya/Desktop/hm", ios::in);
    patch_file.open("/Users/vikaschaurasiya/Desktop/patch.txt", ios::in);
    vector <string> patch_data = get_data(patch_file);
    vector <string> input_data = get_data(input_file);
    vector <patch_entry> A(input_data.size());
    int L;
    for (int i = 2; i < patch_data.size(); ++i) {
        string line = patch_data[i];
        if (line[0] == '@') {
            L = get_l_r(line) - 1;
            continue;
        }
        if (line[0] == ' ') {
            L += 1;
            continue;
        }
        if (line[0] == '-') {
            A[L].keep_old_data = false;
            A[L].match_data = line.substr(1);
            L += 1;
            continue;

        if (line[0] == '+') {
            A[L - 1].append_data.append(line.substr(1) + "\n");
            continue;
        }
    }
    for (int i = 0; i < A.size(); ++i) {
        // cout << A[i].keep_old_data << ";;" << A[i].match_data  << ";;" << A[i].append_data << endl;
        if (A[i].keep_old_data == 0) {
            if (input_data[i] != A[i].match_data) {
                cerr << "Conflicting Error : " << "[" << input_data[i] << "]" << endl;
                return 0;
            }
        }
        if (A[i].keep_old_data == 1) {
            output_file << input_data[i] << endl;
        }
        if (A[i].append_data != "") {
            output_file << A[i].append_data;
        }
    }
    return 0;
}
