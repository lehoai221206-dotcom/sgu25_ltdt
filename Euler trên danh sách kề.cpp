#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Hàm tìm chu trình Euler trên danh sách kề 
vector<int> findEulerianCircuit(vector<vector<int>>& adjList, int start) {
    int n = adjList.size();
    vector<int> circuit;        // Lưu chu trình Euler
    stack<int> st;              // Stack mô phỏng đệ quy
    st.push(start);             // Bắt đầu từ đỉnh start

    // Sao chép danh sách kề để giảm cạnh khi đi qua
    vector<vector<int>> tempAdj = adjList;

    // edgeIndex[u] lưu chỉ số cạnh đã đi từ đỉnh u
    vector<int> edgeIndex(n, 0);

    while (!st.empty()) {
        int u = st.top(); // Xem đỉnh hiện tại trên stack

        // Nếu còn cạnh chưa đi từ đỉnh u
        if (edgeIndex[u] < tempAdj[u].size()) {
            int v = tempAdj[u][edgeIndex[u]]; // Lấy đỉnh kề chưa đi
            edgeIndex[u]++;                   // Đánh dấu đã dùng 1 cạnh
            st.push(v);

            // Xóa cạnh ngược v->u (vì đồ thị vô hướng)
            for (int i = edgeIndex[v]; i < tempAdj[v].size(); ++i) {
                if (tempAdj[v][i] == u) {
                    swap(tempAdj[v][i], tempAdj[v].back());
                    tempAdj[v].pop_back();
                    break;
                }
            }
        }
        else {
            // Nếu không còn cạnh đi từ u, pop stack và thêm vào chu trình
            circuit.push_back(u);
            st.pop();
        }
    }

    return circuit; // Lưu theo thứ tự ngược với thứ tự đi thực tế
}

int main() {
    int n;
    cout << "Nhap so dinh: ";
    cin >> n;

    vector<vector<int>> adjList(n);

    cout << "Nhap danh sach ke: \n";
    for (int i = 0; i < n; ++i) {
        int deg, v;
        cout << "So canh cua dinh " << i << ": ";
        cin >> deg;
        cout << "Nhap cac dinh ke: ";
        for (int j = 0; j < deg; ++j) {
            cin >> v;
            adjList[i].push_back(v);
        }
    }

    int start = 0; // Bắt đầu từ đỉnh 0
    vector<int> circuit = findEulerianCircuit(adjList, start);

    cout << "Chu trinh Euler: ";
    // Đảo ngược circuit để ra đúng thứ tự đi
    for (int i = circuit.size() - 1; i >= 0; --i)
        cout << circuit[i] << " ";
    cout << endl;

    return 0;
}