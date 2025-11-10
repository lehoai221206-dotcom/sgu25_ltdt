#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1001;          // giới hạn n <= 1000
const long long INF = 1e18;     // biểu diễn "vô cùng

int n, m, s, t;                           // số đỉnh, số cạnh, đỉnh bắt đầu s, đỉnh đích t
vector<pair<int, int>> adj[MAXN];        // danh sách kề: adj[u] chứa các cặp (v, w)
vector<long long> d;                     // d[i] = khoảng cách ngắn nhất từ s tới i
vector<int> pre;                         // pre[i] = đỉnh trước của i trong đường đi ngắn nhất

void nhap() {
    cin >> n >> m >> s >> t;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        // Vì đồ thị có hướng, chỉ thêm 1 chiều u -> v
        adj[u].push_back({v, w});
    }
}

// Hàm Dijkstra 
void dijkstra(int s, int t) {
    // khoảng cách ban đầu là INF, pre = -1 (chưa có cha)
    d.assign(n + 1, INF);
    pre.assign(n + 1, -1);
    d[s] = 0; // khoảng cách từ s tới chính nó là 0

    // hàng đợi ưu tiên lưu cặp (khoảng cách, đỉnh)
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, s}); 

    while (!pq.empty()) {
        long long kc = pq.top().first; // kc = khoảng cách tạm thời lấy ra từ hàng đợi
        int u = pq.top().second;       // u = đỉnh đang xét
        pq.pop();

        // Nếu kc khác với d[u], nghĩa là đây là một bản ghi cũ trong hàng đợi -> bỏ qua
        if (kc != d[u]) continue;

        // nếu đã lấy đúng đỉnh đích t thì có thể dừng sớm
        if (u == t) break;

        for (size_t i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first;    // đỉnh kề
            int w = adj[u][i].second;   // trọng số cạnh u -> v

            // Nếu đi qua u giúp rút ngắn khoảng cách tới v
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;    // cập nhật khoảng cách ngắn hơn
                pre[v] = u;         // lưu đỉnh trước của v là u để truy vết sau này
                pq.push({d[v], v}); // đưa bản ghi mới vào hàng đợi
            }
        }
    }

    // kiểm tra xem có đường đi tới t không
    if (d[t] == INF) {
        cout << "Khong co duong di tu " << s << " den " << t << endl;
        return;
    }

    // Truy vết đường đi ngược từ t về s bằng mảng pre[]
    vector<int> path;
    for (int u = t; u != -1; u = pre[u]) {
        path.push_back(u);
    }
    reverse(path.begin(), path.end()); // đảo ngược để được thứ tự s -> t

    cout << path.size() << " " << d[t] << endl;
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
