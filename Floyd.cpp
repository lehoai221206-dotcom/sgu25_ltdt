#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1001;
const long long INF = 1e18;

int n, m;
long long dist[MAXN][MAXN];  // Ma trận lưu khoảng cách giữa các đỉnh


void Nhap() {
    cin >> n >> m;
    //dist[i][i] = 0 (khoảng cách từ i đến chính nó)
    //dist[i][j] = INF (giả sử ban đầu không có đường nối)
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) dist[i][j] = 0;
            else dist[i][j] = INF;
        }
    }

    // Nhập m cạnh
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        // Nếu có nhiều cạnh giữa hai đỉnh, chỉ giữ cạnh nhỏ nhất
        dist[u][v] = min(dist[u][v], (long long)w);
        dist[v][u] = min(dist[v][u], (long long)w);
    }
}

//️Thuật toán Floyd-Warshall
void floydWarshall() {
    // k là đỉnh trung gian
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                // Nếu tồn tại đường i -> k -> j ngắn hơn i -> j hiện tại thì cập nhật
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

void xuat() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << dist[i][j];
            if (j < n) cout << " ";
        }
        cout << endl;
    }
}

int main() {
    Nhap();          
    floydWarshall();   // Tính đường đi ngắn nhất giữa mọi cặp đỉnh
    xuat();     

    return 0;
}
