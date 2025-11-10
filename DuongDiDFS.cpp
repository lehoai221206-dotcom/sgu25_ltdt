#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

vector<vector<int>> adj;       // adj[i] lưu danh sách kề của đỉnh i
vector<bool> visited;          // visited[i] = true nếu đỉnh i đã được thăm
vector<int> parent;            // parent[v] lưu cha của đỉnh v để truy vết đường đi
bool found = false;            // cờ báo hiệu đã tìm thấy y

void DFS(int start, int end) {
    stack<int> st;
    st.push(start);               // bắt đầu từ đỉnh start
    visited[start] = true;        // đánh dấu đã thăm start
    parent[start] = -1;           // đỉnh bắt đầu không có cha

    while (!st.empty() && !found) {
        int u = st.top();         // lấy đỉnh trên cùng ngăn xếp
        st.pop();

        for (int v : adj[u]) {
            if (!visited[v]) {        // nếu v chưa được thăm
                visited[v] = true;    // đánh dấu đã thăm
                parent[v] = u;        // lưu cha của v là u
                st.push(v);           // cho v vào ngăn xếp

                if (v == end) {       // nếu tìm thấy đỉnh đích
                    found = true;
                    return;           // dừng hàm ngay lập tức
                }
            }
        }
    }
}

int main() {
    int n, x, y;
    cin >> n >> x >> y;

    adj.resize(n + 1);                  // cấp phát danh sách kề
    visited.resize(n + 1, false);       // khởi tạo tất cả các đỉnh chưa thăm
    parent.resize(n + 1, -1);           // khởi tạo cha = -1

    for (int i = 1; i <= n; i++) {
        int node;
        while (cin >> node) {
            if (node == -1) break;      // kết thúc danh sách kề bằng -1
            adj[i].push_back(node);     // thêm cạnh i -> node
        }
    }

    // Chạy DFS từ x đến y
    DFS(x, y);

    // Truy vết đường đi từ y ngược về x bằng mảng parent
    vector<int> path;
    if (visited[y]) {
        for (int v = y; v != -1; v = parent[v]) {
            path.push_back(v);          // thêm từng đỉnh vào đường đi
        }
        reverse(path.begin(), path.end()); // đảo ngược để có đường đi từ x -> y

        cout << path.size() << "\n";         // số lượng đỉnh trong đường đi
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i < path.size() - 1) cout << " ";
        }
    }
    else {
        cout << "0\n";    // không tìm thấy đường đi
    }

    return 0;
}