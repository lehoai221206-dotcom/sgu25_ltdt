#include <iostream>           
#include <vector>             
#include <queue>              
#include <cstring>            
using namespace std;

const int MAXN = 100005;     // Số đỉnh tối đa của đồ thị

vector<int> adj[MAXN];        // Danh sách kề
bool visited[MAXN];             // Mảng đánh dấu các đỉnh đã được thăm
int n, x, y, z;

// Hàm BFS không đi qua cạnh (u, v)
int BFS_bo_canh(int start, int u, int v) {
    memset(visited, false, sizeof(visited));     // Khởi tạo tất cả đỉnh chưa thăm
    queue<int> q;
    q.push(start);                                // Thêm đỉnh bắt đầu vào hàng đợi
    visited[start] = true;                    // Đánh dấu đỉnh bắt đầu đã thăm
    int count = 0;                            // Biến đếm số đỉnh đã thăm

    while (!q.empty()) {
        int current = q.front();             // Lấy đỉnh đầu hàng đợi
        q.pop();                                   // Xóa đỉnh khỏi hàng đợi
        count++;                                // Tăng số đỉnh đã thăm

        // Duyệt các đỉnh kề của current
        for (int ke : adj[current]) {
            // Kiểm tra nếu đây là cạnh cần tránh
            if ((current == u && ke == v) || (current == v && ke == u)) {
                continue;                       // Bỏ qua cạnh này
            }
            if (!visited[ke]) {                 // Nếu đỉnh kề chưa thăm
                visited[ke] = true;          // Đánh dấu đã thăm
                q.push(ke);                  // Thêm vào hàng đợi
            }
        }
    }
    return count;
}

// Hàm BFS không đi qua đỉnh skip
int BFS_bo_dinh(int start, int skip) {
    memset(visited, false, sizeof(visited));    // Khởi tạo tất cả đỉnh chưa thăm
    queue<int> q;
    q.push(start);                                // Thêm đỉnh bắt đầu vào hàng đợi
    visited[start] = true;                   // Đánh dấu đỉnh bắt đầu đã thăm
    visited[skip] = true;                  // Đánh dấu đỉnh skip là đã thăm (không đi qua)
    int count = 0;                           // Biến đếm số đỉnh đã thăm


    while (!q.empty()) {
        int current = q.front();             // Lấy đỉnh đầu hàng đợi
        q.pop();                                  // Xóa đỉnh khỏi hàng đợi
        count++;                             // Tăng số đỉnh đã thăm

        // Duyệt các đỉnh kề của current
        for (int ke : adj[current]) {
            if (!visited[ke]) {                 // Nếu đỉnh kề chưa thăm
                visited[ke] = true;          // Đánh dấu đã thăm
                q.push(ke);                  // Thêm vào hàng đợi
            }
        }
    }
    return count;  
}

int main() {
cin >> n >> x >> y >> z;

    for (int i = 1; i <= n; i++) {
        int j;
        while (cin >> j && j != -1)   // Đọc đến khi gặp -1
 {
            adj[i].push_back(j);  // Thêm đỉnh j vào danh sách kề của i
        }
    }

    // Kiểm tra cạnh (x,y) có phải là cạnh cầu không
    int tp_1 = BFS_bo_canh(x, x, y);     // BFS từ x không qua cạnh (x,y)
    bool lacanhcau = (tp_1 < n);           // Nếu số đỉnh thăm được < n => cạnh cầu

    if (lacanhcau) {
        cout << "canh cau\n";
    }
    else {
        cout << "khong la canh cau\n";
    }

    // Tìm một đỉnh kề với z để làm điểm bắt đầu BFS
    int start = -1;
    for (int ke : adj[z]) {
        if (ke != z) {      // Tránh khuyên 
            start = ke;
            break;
        }
    }

    // Kiểm tra đỉnh z có phải là đỉnh khớp không
    // Trường hợp đặc biệt: z là đỉnh cô lập hoặc chỉ có khuyên
    if (start == -1 || adj[z].empty()) {
        cout << "khong la dinh khop\n";
    }
    else {
        int tp_2 = BFS_bo_dinh(start, z);    // BFS không qua đỉnh z
        bool ladinhkhop = (tp_2 < n - 1);    // Nếu số đỉnh thăm được < n-1 => đỉnh khớp

        if (ladinhkhop) {
            cout << "dinh khop\n";
        }
        else {
            cout << "khong la dinh khop\n";
        }
    }

    return 0; 
}