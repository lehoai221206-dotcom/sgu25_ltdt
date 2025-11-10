#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void dfs(int u, vector<vector<int>>& graph, vector<bool>& visited, int n) {
    visited[u] = true; // Đánh dấu đỉnh u đã được thăm

    // Duyệt tất cả các đỉnh kề với u
    for (int v = 0; v < n; v++) {
        // Nếu tồn tại cạnh (u, v) và v chưa được thăm thì đi tiếp
        if (graph[u][v] == 1 && !visited[v])
            dfs(v, graph, visited, n); // Gọi đệ quy sang v
    }
}


bool isConnected(vector<vector<int>>& graph, int n) {
    vector<bool> visited(n, false);
    int start = -1;

    // Tìm một đỉnh có ít nhất 1 cạnh để bắt đầu DFS
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == 1) { // Nếu có cạnh nối i với j
                start = i;          // chọn i làm đỉnh bắt đầu
                break;
            }
        }
        if (start != -1) break;
    }

    if (start == -1) return true; // Không có cạnh nào → xem như liên thông

    // Duyệt toàn bộ đồ thị bắt đầu từ đỉnh start
    dfs(start, graph, visited, n);

    // Kiểm tra xem tất cả các đỉnh có cạnh đều đã được thăm chưa
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Nếu đỉnh i có cạnh nhưng chưa thăm → đồ thị không liên thông
            if (graph[i][j] == 1 && !visited[i])
                return false;
        }
    }
    return true;
}

// hàm đệ quy tìm đường đi Euler 
void findEulerPath(int u, vector<vector<int>>& graph, vector<int>& path, int n) {
    // Duyệt qua tất cả các đỉnh v kề với u
    for (int v = 0; v < n; v++) {
        if (graph[u][v] == 1) {           // Nếu tồn tại cạnh (u, v)
            graph[u][v] = graph[v][u] = 0; // Xóa cạnh u-v (để không đi lại)
            findEulerPath(v, graph, path, n); // Gọi đệ quy từ đỉnh v
        }
    }

    // Sau khi duyệt hết các cạnh từ u, thêm u vào danh sách đường đi
    path.push_back(u);
    // (Thêm vào cuối — để khi đảo ngược lại ta có thứ tự đi đúng)
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> graph[i][j];

    if (!isConnected(graph, n)) {
        cout << "0\n"; // Không liên thông → không thể có đường đi Euler
        return 0;
    }

    vector<int> oddVertices;
    for (int i = 0; i < n; i++) {
        int degree = 0;
        for (int j = 0; j < n; j++)
            degree += graph[i][j]; // Đếm số cạnh nối với i (bậc của đỉnh i)
        if (degree % 2 != 0)
            oddVertices.push_back(i); // Nếu bậc lẻ, thêm vào danh sách
    }

    if (oddVertices.size() != 2) {
        cout << "0\n"; // Không phải đồ thị nửa Euler
        return 0;
    }

    cout << "1\n"; // Là đồ thị nửa Euler

    int start = oddVertices[0]; // bắt đầu từ 1 trong 2 đỉnh bậc lẻ

    vector<int> path;
    findEulerPath(start, graph, path, n); // Gọi hàm đệ quy tìm đường đi
    reverse(path.begin(), path.end());    // Đảo ngược để ra thứ tự đúng

    for (int i = 0; i < path.size(); i++) {
        cout << path[i] + 1;
        if (i < path.size() - 1)
            cout << " ";
    }
    cout << "\n";

    return 0;
}