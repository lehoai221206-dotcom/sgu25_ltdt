#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> adj;   // adj[i] lưu danh sách kề của đỉnh i
vector<bool> visited;        // visited[i] = true nếu đỉnh i đã được thăm

void BFS(int start, vector<int>& result) {
    queue<int> q;                 // Hàng đợi để quản lý các đỉnh đang chờ duyệt
    q.push(start);                 // Đưa đỉnh xuất phát vào hàng đợi
    visited[start] = true;     // Đánh dấu đỉnh xuất phát đã được thăm

    while (!q.empty()) {
        int u = q.front();            // Lấy đỉnh đầu tiên trong hàng đợi
        q.pop();                        // Xóa đỉnh đó khỏi hàng đợi
        result.push_back(u);   // Lưu đỉnh u vào kết quả


        for (int v : adj[u]) {
            if (!visited[v]) {           // Nếu v chưa được thăm
                visited[v] = true;    // Đánh dấu đã thăm
                q.push(v);             // Đưa v vào hàng đợi để duyệt sau
            }
        }
    }
}

int main() {
    int n, s;
    cin >> n >> s;                   // Nhập số đỉnh n và đỉnh bắt đầu s
    adj.resize(n + 1);                 // Cấp phát bộ nhớ cho danh sách kề 
    visited.resize(n + 1, false);    // Khởi tạo mảng visited, ban đầu tất cả = false (chưa thăm)


    for (int i = 1; i <= n; i++) {
        int node;
        while (cin >> node) {
            if (node == -1) break;           // gặp -1 thì dừng
            adj[i].push_back(node);      // thêm cạnh i -> node
        }
    }

    vector<int> result;   // Mảng lưu kết quả các đỉnh đã duyệt bằng BFS
    BFS(s, result);       // Gọi BFS từ đỉnh s


    cout << result.size() << "\n";      // Dòng đầu tiên: số lượng đỉnh đã thăm
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];                    // In từng đỉnh
        if (i < result.size() - 1) cout << " "; // Cách nhau ít nhất 1 khoảng trắng
    }
    return 0;
}