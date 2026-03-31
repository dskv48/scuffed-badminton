#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int g;
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

void dfs_visit(int i, int j) {
    cout << i << ' ' << j << '\n';
    visited[i][j] = true;
    if (j == 8999) {
        return;
    } else if (i == 1 && j == 1) {
        if (!visited[1][2]) {
            dfs_visit(1, 2);
        }
    } else {
        g = gcd(i + 1, j);
        if (!visited[(i + 1) / g][j / g]) {
            dfs_visit((i + 1) / g, j / g);
        }

        g = gcd(i, j + 1);
        if (!visited[i / g][(j + 1) / g]) {
            dfs_visit(i / g, (j + 1) / g);
        }
    }
}

int main() {
    for (int i = 0; i < 9000; i++) {
        for (int j = 0; j < 9000; j++) {
            visited[i][j] = false;
        }
    }

    dfs_visit(2, 11);
}
