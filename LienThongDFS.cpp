#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<vector<int>> adj;      // adj[i] lưu danh sách kề của đỉnh i
vector<bool> visited;        // visited[i] = true nếu đỉnh i đã được thăm

void DFS(int start, vector<int>& result) {
    stack<int> st;                   // Ngăn xếp để quản lý các đỉnh đang chờ duyệt
    st.push(start);                 // Đưa đỉnh xuất phát vào ngăn xếp
    visited[start] = true;         // Đánh dấu đỉnh xuất phát đã được thăm

    while (!st.empty()) {
        int u = st.top();                 // Lấy đỉnh trên cùng của ngăn xếp
        st.pop();                        // Xóa đỉnh đó khỏi ngăn xếp
        result.push_back(u);            // Lưu đỉnh u vào kết quả

        for (int v : adj[u]) {
            if (!visited[v]) {            // Nếu v chưa được thăm
                visited[v] = true;       // Đánh dấu đã thăm
                st.push(v);             // Đưa v vào ngăn xếp để duyệt sau
            }
        }
    }
}

int main() {
    int n, s;
    cin >> n >> s;                    // Nhập số đỉnh n và đỉnh bắt đầu s
    adj.resize(n + 1);               // Cấp phát bộ nhớ cho danh sách kề (đỉnh đánh số từ 1..n)
    visited.resize(n + 1, false);   // Khởi tạo mảng visited, ban đầu tất cả = false (chưa thăm)

    for (int i = 1; i <= n; i++) {
        int node;
        while (cin >> node) {
            if (node == -1) break;           // gặp -1 thì dừng
            adj[i].push_back(node);        // thêm cạnh i -> node
        }
    }

    vector<int> result;    // Mảng lưu kết quả các đỉnh đã duyệt bằng DFS
    DFS(s, result);       // Gọi DFS từ đỉnh s

    cout << result.size() << "\n";      // Dòng đầu tiên: số lượng đỉnh đã thăm
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];                    // In từng đỉnh
        if (i < result.size() - 1) cout << " "; // Cách nhau ít nhất 1 khoảng trắng
    }
    return 0;
}