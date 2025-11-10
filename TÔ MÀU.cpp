#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Hàm tô màu đồ thị theo thuật toán Welsh–Powell
vector<int> welshPowellColoring(int n, vector<vector<int>>& adj) {
    vector<pair<int, int>> degrees; // Lưu (bậc, đỉnh)

    // Tính bậc của từng đỉnh
    for (int i = 1; i <= n; i++) {
        degrees.push_back({adj[i].size(), i});
    }

    // Sắp xếp đỉnh theo bậc giảm dần
    sort(degrees.begin(), degrees.end(), [](pair<int,int> a, pair<int,int> b) {
        if (a.first != b.first) return a.first > b.first; // Bậc lớn hơn đứng trước
        return a.second < b.second; // Nếu bằng bậc, đỉnh nhỏ hơn đứng trước
    });

    vector<int> color(n + 1, 0);        // Lưu màu mỗi đỉnh (0 = chưa tô)
    vector<bool> colored(n + 1, false); // Đánh dấu đỉnh đã tô hay chưa
    vector<int> order;                  // Thứ tự đỉnh theo bậc giảm dần

    for (auto &p : degrees) order.push_back(p.second);

    int currentColor = 0;   // Màu hiện tại
    int coloredCount = 0;   // Số đỉnh đã tô

    while (coloredCount < n) {
        currentColor++; // Bắt đầu màu mới

        // Tìm đỉnh chưa tô đầu tiên
        int firstUncolored = -1;
        for (int u : order) {
            if (!colored[u]) {
                firstUncolored = u;
                break;
            }
        }
        if (firstUncolored == -1) break;

        // Tô màu cho đỉnh đầu tiên chưa tô
        color[firstUncolored] = currentColor;
        colored[firstUncolored] = true;
        coloredCount++;

        // Tô màu cho các đỉnh khác không kề với màu hiện tại
        for (int u : order) {
            if (colored[u]) continue; // Bỏ qua đỉnh đã tô

            bool canColor = true; 

            // Kiểm tra các đỉnh kề
            for (int neighbor : adj[u]) {
                if (color[neighbor] == currentColor) {
                    canColor = false; // Nếu kề với màu hiện tại, không tô
                    break;
                }
            }

            // Nếu không kề, tô màu
            if (canColor) {
                color[u] = currentColor;
                colored[u] = true;
                coloredCount++;
            }
        }
    }

    return color; 
}

int main() {
    int n, m;
    cin >> n >> m; 

    vector<vector<int>> adj(n + 1); // Danh sách kề

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v); // Thêm cạnh u-v
        adj[v].push_back(u); // Thêm cạnh v-u vì đồ thị vô hướng
    }

    vector<int> color = welshPowellColoring(n, adj); // Gọi Welsh–Powell

    int maxColor = *max_element(color.begin(), color.end()); // Tìm số màu sử dụng

    // Gom các đỉnh theo màu
    vector<vector<int>> colorGroups(maxColor + 1);
    for (int i = 1; i <= n; i++) colorGroups[color[i]].push_back(i);

    cout << maxColor << "\n"; 

    for (int c = 1; c <= maxColor; c++) {
        for (int city : colorGroups[c]) cout << city << " ";
        cout << "\n";
    }

    return 0;
}
