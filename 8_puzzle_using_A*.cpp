#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <utility>
#include <functional>

using namespace std;

map<vector<vector<int> >, bool> visited;
map<vector<vector<int> >, vector<vector<int> > > parent;
map<vector<vector<int> >, int> path;

vector<vector<int> > goal(3, vector<int> (3));
vector<vector<vector<int> > > node;
vector<string> op;

int lm[] = {1, 0, 3, 2};
int dx[] = {0, 0, -1, +1};
int dy[] = {+1, -1, 0, 0};
int steps = 0, explored_nodes = 0, generated_nodes = 0, choice;

string operation[] = {"RIGHT", "LEFT", "UP", "DOWN"};

typedef pair< pair<vector<vector<int> >, int>, int> state;

bool visit(vector<vector<int> > a) {
	if (visited[a]==true)
      return true;
    else return false;
}

int missplaced(vector<vector<int> > a , int c_n) {
    int f_n = c_n;
    for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(a[i][j] != goal[i][j])
				f_n += 1;
		}
	}
    return f_n;
}

int manhattan(vector<vector<int> > a , int c_n) {
	int f_n = c_n;
    for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			for(int k = 0; k < 3; k++) {
				for(int l = 0; l < 3; l++) {
					if(a[i][j] == goal[k][l])
						f_n += abs(i - k) + abs(j - l);
				}
			}
		}
	}
    return f_n;
}

bool isGoal(vector<vector<int> > a) {
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(a[i][j] != goal[i][j])
				return false;
		}
	}
    return true;
}


bool safe(int i,int j) {
	if(i >= 0 && i <= 2 && j >= 0 && j <= 2)
	   return true;
	else
	   return false;
}

vector<pair<vector<vector<int> >, int > > neighbours(pair<vector<vector<int>> , int > a) {
	pair<int, int> pos;
	for(int i = 0;i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(a.first[i][j] == 0) {
				pos.first = i;
				pos.second = j;
				break;
			}
		}
	}
	vector<pair<vector<vector<int>>, int>  >ans;
	for(int k = 3; k >= 0; k--) {
		int cx = pos.first;
		int cy = pos.second;
		vector<vector<int> > n = a.first;
		if(safe(cx + dx[k],cy + dy[k]) && (a.second == -1 || k!= lm[a.second])) {
			swap(n[cx+dx[k]][cy+dy[k]],n[cx][cy]);
			ans.push_back(make_pair(n,k) );
		}
	}
    return ans;
}

struct cmp {
	bool operator() (state &a, state &b) {
        if (choice == 1) {
    		int am = manhattan(a.first.first, a.second);
    		int bm = manhattan(b.first.first, b.second);
            return am > bm;
        } else {
            int cm = missplaced(a.first.first, a.second);
    		int dm = missplaced(b.first.first, b.second);
            return cm > dm;
        }
	}
};

struct cmp2 {
	bool operator() (state &a, state &b) {
		int am = missplaced(a.first.first, a.second);
		int bm = missplaced(b.first.first, b.second);
		return am > bm;
	}
};

void print_path(vector<vector<int> > s) {
  if(parent.count(s)){
      print_path(parent[s]);
  }
   steps += 1;
   op.push_back(operation[path[s]]);
   node.push_back(s);
   return;
}

void solve(vector<vector<int> > a, int c_n) {
    priority_queue<state,vector<state>, cmp> Q;
	Q.push(state(make_pair(a, -1), c_n));
	while(!Q.empty()) {
		pair <vector<vector<int> > , int> s = Q.top().first;
        int moves = Q.top().second;
		Q.pop();
        explored_nodes += 1;
		visited[s.first] = true;
		if(s.first == goal) {
			print_path(s.first);
			break;
		}
		vector<pair < vector<vector<int> > , int > > ns = neighbours(s);
		vector< pair < vector<vector<int> > , int > > :: iterator it;

		for(it = ns.begin(); it != ns.end(); it++) {
			pair < vector<vector<int> > , int >temp = *it;
			if(!visit(temp.first)) {
                path.insert(pair<vector<vector<int> >, int> (temp.first, temp.second));
				parent.insert(pair<vector<vector<int> >, vector<vector<int> > >(temp.first, s.first));
				Q.push(state(make_pair(temp.first, temp.second), moves + 1));
                generated_nodes += 1;
			}
		}
	}
	return;
 }

int main() {
	vector<vector<int> > a(3, vector<int> (3));
    cout << "Enter initial state:\n";
    for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			cin >> a[i][j];
		}
	}
    cout << "Enter goal state:\n";
    for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			cin >> goal[i][j];
		}
	}
    cout << "1. Manhattan Heuristic\n2. Missplaced Heuristic\n";
    cin >> choice;
    cout << "\nNodes\n\n";
	solve(a, 0);
    for (int m = 0; m < node.size(); ++m) {
        vector<vector<int> > temp = node[m];
        if (m)
         cout << "\n" << op[m] << endl;
    	for(int i = 0; i < 3; i++) {
    	 for(int j = 0; j < 3; j++) {
    		printf("%d ", temp[i][j]);
    	 }
    	 cout << endl;
       }
    }
    cout << "Total Steps taken : " << steps - 1 << endl;
    cout << "Generated Nodes   : " << generated_nodes << endl;
    cout << "Explored Nodes    : " << explored_nodes << endl;
    return 0;
}
