#include <iostream>
#include <vector>
using namespace std;

// Kiểm tra xem đỉnh v có thể thêm vào vị trí pos trong đường đi không
bool isSafe(int v, vector<vector<int>>& graph, vector<int>& path, int pos) {
    // Kiểm tra có cạnh nối từ đỉnh trước đó tới v hay không
    if (graph[path[pos - 1]][v] == 0)
        return false;

    // Kiểm tra đỉnh v đã được dùng trong path chưa
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

// Hàm quay lui tìm chu trình Hamilton
bool hamiltonianCycleUtil(vector<vector<int>>& graph, vector<int>& path, int pos, int n) {
    // Trường hợp cơ sở: đã đi qua tất cả n đỉnh
    if (pos == n) {
        // Kiểm tra có cạnh nối từ đỉnh cuối quay về đỉnh đầu không
        if (graph[path[pos - 1]][path[0]] == 1)
            return true; // Có → là chu trình Hamilton
        return false; // Không → không hợp lệ
    }

    for (int v = 1; v < n; v++) {
        if (isSafe(v, graph, path, pos)) { // Nếu đỉnh v hợp lệ
            path[pos] = v; // Gán v vào vị trí pos

            // Gọi đệ quy để thử thêm đỉnh tiếp theo
            if (hamiltonianCycleUtil(graph, path, pos + 1, n))
                return true; // Nếu tìm được chu trình thì thoát ra luôn

            // Nếu không thành công → quay lui
            path[pos] = -1;
        }
    }

    // Nếu không có đỉnh nào phù hợp → không tìm được chu trình
    return false;
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> graph[i][j];

    // mảng lưu đường đi
    vector<int> path(n, -1); // Khởi tạo toàn -1
    path[0] = 0; // Bắt đầu từ đỉnh 0 (tức đỉnh 1 thực tế)

    // Gọi hàm quay lui và in kết quả
    if (hamiltonianCycleUtil(graph, path, 1, n)) {
        cout << "1\n"; // Có chu trình Hamilton
        for (int i = 0; i < n; i++)
            cout << path[i] + 1 << " "; // In đỉnh 
        cout << path[0] + 1 << "\n"; // Quay lại đỉnh đầu
    }
    else {
        cout << "0\n"; // Không có chu trình Hamilton
    }

    return 0;
}