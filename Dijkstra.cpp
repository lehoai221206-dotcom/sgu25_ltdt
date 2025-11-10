#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1001;       // Giới hạn số đỉnh tối đa
const long long INF = 1e18;  // Giá trị "vô cùng" (coi như không thể tới được)

int n, m, s, t;                         
vector<pair<int, int>> adj[MAXN];        // adj[u] chứa các cặp (v, w): cạnh u → v có trọng số w
vector<long long> d;                     // d[i]: độ dài đường đi ngắn nhất từ s đến i
vector<int> pre;                         // pre[i]: đỉnh liền trước của i trên đường đi ngắn nhất
vector<bool> visited;                    // visited[i]: đánh dấu đỉnh i đã được chọn hay chưa

// Nhập
void nhap() {
    cin >> n >> m >> s >> t;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w}); 
    }
}

// Thuật toán Dijkstra (không dùng hàng đợi ưu tiên)
void dijkstra(int s, int t) {
    d.assign(n + 1, INF);
    pre.assign(n + 1, -1);
    visited.assign(n + 1, false);
    d[s] = 0;

    // Lặp tối đa n lần để chọn dần từng đỉnh có khoảng cách nhỏ nhất
    for (int i = 1; i <= n; i++) {
        int u = -1;
        long long min_d = INF;

        // Chọn đỉnh u chưa thăm có d[u] nhỏ nhất
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && d[j] < min_d) {
                min_d = d[j];
                u = j;
            }
        }

        if (u == -1) break;     // Không còn đỉnh nào có thể đi tới
        visited[u] = true;      // Đánh dấu u đã thăm
        if (u == t) break;      // Dừng sớm nếu đã đến đỉnh đích

        // Cập nhật khoảng cách của các đỉnh kề với u
        for (auto &edge : adj[u]) {
            int v = edge.first; 
            int w = edge.second; 
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w; 
                pre[v] = u;       // lưu lại đỉnh trước để truy vết đường đi
            }
        }
    }

    // Nếu không có đường đi từ s đến t
    if (d[t] == INF) {
        cout << "Khong co duong di tu " << s << " den " << t << endl;
        return;
    }

    // Truy vết lại đường đi từ t ngược về s
    vector<int> path;
    for (int u = t; u != -1; u = pre[u])
        path.push_back(u);
    reverse(path.begin(), path.end());

    cout << path.size() << " " << d[t] << endl;  // số đỉnh đi qua và độ dài ngắn nhất
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i + 1 < path.size()) cout << " ";
    }
    cout << endl;
}

int main() {
    nhap();
    dijkstra(s, t);
    return 0;
}
