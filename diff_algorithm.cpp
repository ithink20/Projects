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
#include<sstream>

using namespace std;
typedef long long int lint;

struct commonSub {
    string subsequence;
    int index;
    commonSub(): index(-1) {}
};

ostream &operator<< (ostream &os, commonSub const &m) {
    return os << m.subsequence << "::" << m.index;
}

int lcs_helper(vector<vector<int> >&dp, vector<string> &A, vector<string> &B, int m, int n) {
    //Base Case
    if (m == 0 || n == 0) {
        dp[m][n] = 0;
    }
    if (dp[m][n] != -1) {
        return dp[m][n];
    }
    if (A[m - 1] == B[n - 1]) {
        return dp[m][n] = 1 + lcs_helper(dp, A, B, m - 1, n - 1);
    } else {
        return dp[m][n] = max(lcs_helper(dp, A, B, m - 1, n), lcs_helper(dp, A, B, m, n - 1));
    }
}

vector<commonSub> printLcs(vector<vector<int> >&dp, vector<string> &A, vector<string> &B, int m, int n) {
    int last_index = dp[m][n];
    vector<string> matched_string(last_index + 1, "");  //to store matched string
    vector<commonSub> Sub_data(last_index);
    // matched_string[last_index] = '\0';

    for(int i = m, j = n; i > 0 && j > 0; ) {
        if (A[i - 1] == B[j - 1]) {
            matched_string[last_index - 1] = A[i - 1];
            last_index -= 1;
            i -= 1;
            j -= 1;
        }
        else if (dp[i - 1][j] > dp[i][j - 1]) {
            i -= 1;
        } else {
            j -= 1;
        }
    }
    int k = 0, l = 0;
    for (int i = 0; i < A.size(); ++i) {
        // cout << matched_string[i] << endl;
        if (A[i] == matched_string[k]) {
            Sub_data[l].subsequence = matched_string[k];
            Sub_data[l].index = i;
            k += 1; l += 1;
        }
    }
    return Sub_data;
}

vector<commonSub> lcs(vector<string> &A, vector<string> &B) {
    int m = A.size();
    int n = B.size();
    vector <vector<int> >dp(m + 1, vector<int>(n + 1, -1));
    int ans = lcs_helper(dp, A, B, m, n);
    return printLcs(dp, A, B, m, n);
    // return ans;
}

vector <string> get_data(fstream &file) {
    string linebuffer;
    vector <string> temp;
    while (file && getline(file, linebuffer)) {
        temp.push_back(linebuffer);
    }
    return temp;
}

struct PatchEntry {
    bool delete_old;
    vector<string> prepend_lines;
};

template<class T>
void print_vector(std::vector<T> v, string message, string delim = "\n") {
    if (message.size() > 0) {
        cout << message << "\n";
    }
    for (int i = 0; i < v.size(); ++i) {
        cout << "v[" << i  << "]=" << v[i] << delim;
    }
}


int main() {
    fstream input_file, output_file;
    ofstream diff_file("/Users/vikaschaurasiya/Desktop/diff.txt");
    input_file.open("/Users/vikaschaurasiya/Desktop/input.txt", ios::in);
    output_file.open("/Users/vikaschaurasiya/Desktop/output.txt", ios::in);
    vector <string> input_data = get_data(input_file);
    vector <string> output_data = get_data(output_file);
    vector<commonSub> LCS = lcs(input_data, output_data);
    print_vector(input_data, "input_data");
    print_vector(output_data, "output_data");
    print_vector(LCS, "LCS");

    vector<PatchEntry> patch(input_data.size() + 1);
    for (int i = 0, j = 0; i < input_data.size(); i++) {
        if (j < LCS.size() && input_data[i] == LCS[j].subsequence) {
            patch[i].delete_old = false;
            j++;
        } else {
            patch[i].delete_old = true;
        }
    }
    for (int i = 0, j = 0; i < output_data.size(); i++) {
        if (j < LCS.size() && output_data[i] == LCS[j].subsequence) {
            j++;
        } else {
            auto insert_index = j < LCS.size() ? LCS[j].index : patch.size() - 1;
            patch[insert_index].prepend_lines.push_back(output_data[i]);
        }
    }
    cout << "\nPatchEntry\n";
    for (int i = 0; i < patch.size(); ++i) {
        cout << "patch[" << i << "]=" << (patch[i].delete_old ? "delete" : "keep") << "::";
        print_vector(patch[i].prepend_lines, "", ", ");
        cout << "\n";
    }
    cout << "Diff\n";
    int current_line = -1;
    for (int i = 0; i < patch.size(); ++i) {
        if (patch[i].delete_old == true) {
            if (current_line != i) {
                current_line = i;
                cout << "@@ " << current_line + 1 << " @@" << "\n";
            }
            cout << "-" << input_data[i] << "\n";
            current_line += 1;
        }
        auto s = patch[i].prepend_lines;
        for (int j = 0; j < s.size(); j++) {
            cout << "+" << s[j] << "\n";
        }
    }
    return 0;
}
