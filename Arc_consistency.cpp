#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <utility>

using namespace std;
typedef long long int lint;


int cons[50][50];

int rel[]={0,1,2,3};

int fun (char ch){
    if (ch == '>')
        return 1;
    if (ch == '<')
        return 2;
    if (ch == '=')
        return 3;
    if (ch == '!')
        return 4;

}

bool check(int x, int y, int a, int b) {
    if (cons[x][y] == 1) {
        return (a > b);
    }
    if (cons[x][y] == 2) {
        return (b < a);
    }
    if (cons[x][y] == 3) {
        return (a == b);
    }
    if (cons[x][y] == 4) {
        return (a != b);
    }
    return false;
}

bool Revise(vector <vector <int> >&Dom, int x, int y) {
    bool change = false;
    cout << endl << "[ " << x << "--" << y << "]";
    for(int i = 0; i < Dom[x].size(); ++i) {
        int flag = 0;
        for (int j = 0; j < Dom[y].size(); ++j) {
            if (!(Dom[x][i] == -1 || Dom[y][j] == -1) && check(x, y, Dom[x][i], Dom[y][j])) {
                cout << "     " << Dom[x][i] << "," << Dom[y][j] << endl;
                flag = 1;
                break;
            }
        }
        if (flag == 0 && Dom[x][i] != -1) {
            change = true;
            cout << "|" << Dom[x][i] << "|" << endl;
            Dom[x][i] = -1;
        }
    }
    return change;
}

int main() {
    int N, M;
    cin >> N >> M;
    vector <vector<int> >G(N);
    pair<int, int> P;
    set <pair<int, int> >Q;
    set <pair<int, int> >Arc;
    int u, v;
    for (int i = 0; i < M; ++i) {

        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for (int i = 0; i < N; ++i) {
        //cout << i << " : ";
        for (int j = 0; j < G[i].size(); ++j) {
            //cout << G[i][j] << " ";
            P = make_pair(i, G[i][j]);
            Q.insert(P);
            Arc.insert(P);
        }
    }


    for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                 cons[i][j] = 0 ;
        }
    }
    cout <<"\nEnter the constraints for edges "<<endl;
    char choice;
    for (int i = 0; i < G.size(); ++i) {
            for (int j = 0; j < G[i].size(); ++j) {
                cout << "\n" << i <<"--"<<G[i][j]<<"  : ";
                cin >> choice ;
                cons[i][G[i][j]] = fun(choice);
        }
    }
    vector <vector <int> >Dom(N);
    int x;
    char ch;
    for (int i = 0; i < N; ++i) {
        cout << "enter domain_size for " << i << " node \n";
        int size; cin >> size;
        while (size--) {
            cin >> x;
            Dom[i].push_back(x);
        }
    }
    while (Q.size() != 0) {
        set<pair<int,int> > :: iterator pt = Q.begin();
        set<pair<int,int> > :: iterator it = Q.begin();
        while (pt != Q.end()) {
            cout << "(" << (*pt).first << " " << (*pt).second << "), ";
            ++pt;
        }
        cout << endl;
        int x = (*it).first;
        int y = (*it).second;
        Q.erase(it);
        if (Revise(Dom, x, y)) {
            set<pair<int, int> > :: iterator itr = Arc.begin();
            while (itr != Arc.end()) {
                if ((*itr).first != y && (*itr).second == x) {
                    Q.insert(make_pair((*itr).first, (*itr).second));
                }
                ++itr;
            }
        }
    }
    cout << endl;
    for (int i = 0; i < Dom.size(); ++i) {
        for (int j = 0; j < Dom[i].size(); ++j) {
            if (Dom[i][j] != -1)
                cout << Dom[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
