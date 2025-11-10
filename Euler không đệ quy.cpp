#include <iostream>
#include <vector>
#include <stack>
using namespace std;
// Hàm kiểm tra có cạnh nào còn đi được từ đỉnh u
bool hasUnusedEdge(const vector<vector<int>>& graph, int u, int n) {
    for (int v = 0; v < n; ++v) {
        if (graph[u][v] > 0) return true;
    }
    return false;
}

// Hàm tìm chu trình Euler (không đệ quy) từ ma trận kề
vector<int> findEulerianCircuit(vector<vector<int>> graph, int start) {
    int n = graph.size();
    stack<int> st;
    vector<int> circuit;

    st.push(start);

    while (!st.empty()) {
        int u = st.top();
        bool found = false;

        // Tìm cạnh còn đi được từ u
        for (int v = 0; v < n; ++v) {
            if (graph[u][v] > 0) {
                // Đi qua cạnh u-v
                st.push(v);
                graph[u][v]--;
                graph[v][u]--; // vì đồ thị vô hướng
                found = true;
                break;
            }
        }

        if (!found) {
            // Không còn cạnh đi được từ u -> thêm vào chu trình
            circuit.push_back(u);
            st.pop();
        }
    }

    return circuit; // lưu chu trình ngược, cần đảo nếu muốn thứ tự đi
}

int main() {
    int n;
    cout << "Nhap so dinh: ";
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));
    cout << "Nhap ma tran ke:\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> graph[i][j];

    int start = 0; // Bắt đầu từ đỉnh 0
    vector<int> circuit = findEulerianCircuit(graph, start);

    cout << "Chu trinh Euler: ";
    for (int i = circuit.size() - 1; i >= 0; --i) // đảo ngược để ra đúng thứ tự
        cout << circuit[i] << " ";
    cout << endl;

    return 0;
}