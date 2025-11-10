#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1001;       // số đỉnh tối đa
const long long INF = 1e18;  // giá trị vô cùng 

int n, m, s, t, x;                       
vector<pair<int, int>> adj[MAXN];        // adj[u] chứa danh sách (v, w) — cung từ u -> v có trọng số w
vector<long long> d;                     // d[i] là khoảng cách ngắn nhất từ 1 đỉnh đến i
vector<int> pre;                         // pre[i] là đỉnh trước của i trong đường đi ngắn nhất
vector<bool> visited;                    // đánh dấu các đỉnh đã chọn

//Hàm Dijkstra 
void dijkstra(int start, vector<long long> &dist, vector<int> &prev) {
    dist.assign(n + 1, INF);     // ban đầu tất cả các đỉnh đều có khoảng cách "vô cùng"
    prev.assign(n + 1, -1);      // chưa có đỉnh trước nào
    visited.assign(n + 1, false);// tất cả các đỉnh đều chưa được chọn
    dist[start] = 0;             

    // Lặp n lần để chọn từng đỉnh có khoảng cách nhỏ nhất
    for (int i = 1; i <= n; i++) {
        int u = -1;
        long long min_d = INF;

        // Tìm đỉnh u chưa thăm có dist[u] nhỏ nhất
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < min_d) {
                min_d = dist[j];
                u = j;
            }
        }

        if (u == -1) break;  // không còn đỉnh nào có thể đi tới
        visited[u] = true;   // đánh dấu u đã được chọn

        // Cập nhật các đỉnh kề của u
        for (size_t k = 0; k < adj[u].size(); k++) {
            int v = adj[u][k].first;   
            int w = adj[u][k].second;  
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w; 
                prev[v] = u;           // lưu lại đỉnh trước của v
            }
        }
    }
}

// Hàm truy vết đường đi từ s -> t 
vector<int> truyVet(int s, int t, vector<int> &prev) {
    vector<int> path;
    for (int u = t; u != -1; u = prev[u]) path.push_back(u);
    reverse(path.begin(), path.end());
    if (path.empty() || path[0] != s) path.clear(); // nếu không thể tới đích
    return path;
}

int main() {
    cin >> n >> m >> s >> t >> x; 

    // Nhập danh sách 
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(make_pair(v, w));
    }

    //chạy Dijkstra từ s để có khoảng cách s -> x
    vector<long long> d1;
    vector<int> pre1;
    dijkstra(s, d1, pre1);

    //chạy Dijkstra từ x để có khoảng cách x -> t
    vector<long long> d2;
    vector<int> pre2;
    dijkstra(x, d2, pre2);

    // Kiểm tra có đường đi hợp lệ không
    if (d1[x] == INF || d2[t] == INF) {
        cout << "Khong co duong di tu " << s << " den " << t << " qua " << x << endl;
        return 0;
    }

    long long tong = d1[x] + d2[t]; // tổng khoảng cách s -> x -> t

    // Truy vết 2 đoạn đường
    vector<int> path1 = truyVet(s, x, pre1); // đường s -> x
    vector<int> path2 = truyVet(x, t, pre2); // đường x -> t

    // Ghép lại, bỏ trùng đỉnh x
    for (size_t i = 1; i < path2.size(); i++)
        path1.push_back(path2[i]);

    cout << path1.size() << " " << tong << endl;
    for (size_t i = 0; i < path1.size(); i++) {
        cout << path1[i];
        if (i + 1 < path1.size()) cout << " ";
    }
    cout << endl;

    return 0;
}
