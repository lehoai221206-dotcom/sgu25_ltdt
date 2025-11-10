#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void dfs(int u, vector<vector<int>>& graph, vector<bool>& visited, int n) {
    visited[u] = true; // Đánh dấu đỉnh u đã thăm
    for (int v = 0; v < n; v++) {
        if (graph[u][v] == 1 && !visited[v]) {
            dfs(v, graph, visited, n); // Gọi đệ quy sang đỉnh kề v
        }
    }
}
//kiểm tra liên thông
bool isConnected(vector<vector<int>>& graph, int n) {
    vector<bool> visited(n, false);
    int start = -1;
    // Tìm đỉnh có cạnh đầu tiên để bắt đầu DFS
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == 1) {
                start = i;
                break;
            }
        }
        if (start != -1) break;
    }

    if (start == -1) return true; // Đồ thị không có cạnh → xem như liên thông

    dfs(start, graph, visited, n); // Duyệt DFS từ đỉnh start

    // Kiểm tra xem tất cả đỉnh có cạnh đều đã được thăm
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == 1 && !visited[i])
                return false;
        }
    }
    return true;
}
// tìm chu trình Euler 
void findEulerCycle(int u, vector<vector<int>>& graph, vector<int>& cycle, int n) {
    for (int v = 0; v < n; v++) {
        if (graph[u][v] == 1) {       // Nếu còn cạnh giữa u và v
            graph[u][v] = graph[v][u] = 0; // Xóa cạnh đã đi
            findEulerCycle(v, graph, cycle, n); // Đệ quy tìm tiếp từ v
        }
    }
    cycle.push_back(u); // Thêm u vào chu trình sau khi duyệt xong
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }

    // Kiểm tra tính liên thông
    if (!isConnected(graph, n)) {
        cout << "0\n"; // Không liên thông → không có chu trình Euler
        return 0;
    }

    // Kiểm tra bậc chẵn của các đỉnh
    for (int i = 0; i < n; i++) {
        int degree = 0;
        for (int j = 0; j < n; j++) {
            degree += graph[i][j];
        }
        if (degree % 2 != 0) { // Nếu có đỉnh bậc lẻ
            cout << "0\n"; // Không phải đồ thị Euler
            return 0;
        }
    }

    cout << "1\n"; // Đồ thị là Euler

    // Tìm chu trình Euler bắt đầu từ đỉnh 0 (tức là đỉnh 1 thực tế)
    vector<int> cycle;
    findEulerCycle(0, graph, cycle, n);
    reverse(cycle.begin(), cycle.end()); // Đảo ngược để ra thứ tự đúng

    // In chu trình (chuyển từ 0-based → 1-based)
    for (int i = 0; i < cycle.size(); i++) {
        cout << cycle[i] + 1;
        if (i < cycle.size() - 1) cout << " "; // nếu chưa phải đỉnh cuối cùng trong chu trình 
    }                                           // thì in thêm dấu cách      
    cout << "\n";                               

    return 0;
}