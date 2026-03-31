#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

double ev[9000];
vector< pair<int, int> > markov_chain[9000][9000];
int g;
double progress[9000];
double ans;
bool visited[9000][9000];

int gcd(int a, int b) {
    if (a == b) {
        return a;
    } else if (a == 0) {
        return b;
    } else if (b == 0) {
        return a;
    } else if (a > b) {
        return gcd(a % b, b);
    } else {
        return gcd(a, b % a);
    }
}

void construct_chain() {
    for (int i = 1; i < 8999; i++) {
        for (int j = i; j < 8999; j++) {
            g = gcd(i + 1, j);
            markov_chain[i][j].emplace_back((i + 1) / g, j / g);

            g = gcd(i, j + 1);
            markov_chain[i][j].emplace_back(i / g, (j + 1) / g);
        }
    }
}

double dist_to_parent(int i, int j, int parent) {
    if (i == 1) {
        ans = 0;
        while (j < parent) {
            ans += progress[j];
            j++;
        }
        return ans;
    } else {
        return 1 + dist_to_parent((markov_chain[i][j])[0].first, (markov_chain[i][j])[0].second, parent) / 2 + dist_to_parent((markov_chain[i][j])[1].first, (markov_chain[i][j])[1].second, parent) / 2;
    }
}

void visit(int i, int j) {
    double ratio = (j * 1.0) / (i * 1.0);
    if (ratio >= 2) {
        cout << ratio << '\n';
    }
    int a = (markov_chain[i][j])[0].first;
    int b = (markov_chain[i][j])[0].second;
    int c = (markov_chain[i][j])[1].first;
    int d = (markov_chain[i][j])[1].second;

    visited[i][j] = true;
    if (b >= 11 && !visited[a][b]) {
        visit(a, b);
    }

    if (d >= 11 && !visited[c][d]) {
        visit(c, d);
    }
}

int main() {
    for (int i = 0; i < 9000; i++) {
        for (int j = 0; j < 9000; j++) {
            visited[i][j] = false;
        }
    }
    ev[1] = 0;
    ev[2] = 1;
    progress[1] = 1;

    construct_chain();
    
    for (int j = 2; j <= 10; j++) {
        progress[j] = dist_to_parent((markov_chain[1][j])[0].first, (markov_chain[1][j])[0].second, j) + 2;
        ev[j + 1] = ev[j] + progress[j];
    }

    for (int j = 1; j <= 11; j++) {
        cout << "E_" << j << ": " << fixed << setprecision(8) << ev[j] << '\n';
    }

    visit(2, 11);
}