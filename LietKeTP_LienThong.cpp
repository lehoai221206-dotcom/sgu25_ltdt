#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> danh_sach_ke;   // danh_sach_ke[i] chứa các đỉnh kề với đỉnh i
vector<bool> da_tham;                       // da_tham[i] = true nếu đỉnh i đã được duyệt

vector<int> BFS(int bat_dau) {
    vector<int> thanh_phan;      // chứa các đỉnh trong thành phần liên thông
    queue<int> q;

    q.push(bat_dau);                  // đưa đỉnh vào hàng đợi và đánh dấu đã thăm
    da_tham[bat_dau] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        thanh_phan.push_back(u);      // thêm u vào thành phần

        for (int v : danh_sach_ke[u]) {
            if (!da_tham[v]) {
                da_tham[v] = true;  // nếu v chưa thăm thì đánh dấu
                q.push(v);               // đưa vào hàng đợi
            }
        }
    }
    return thanh_phan;
}

int main() {
    int n;
    cin >> n; // số đỉnh

    // khởi tạo danh sách kề và mảng đã thăm 
    danh_sach_ke.resize(n + 1);
    da_tham.assign(n + 1, false); // ban đầu tất cả chưa thăm 

    // Nhập danh sách kề
    for (int i = 1; i <= n; i++) {
        int x;
        while (cin >> x) {              // nhập các đỉnh kề của i 
            if (x == -1) break;          // kết thúc bằng -1
            danh_sach_ke[i].push_back(x);
        }
    }

    vector<vector<int>> cac_thanh_phan; // lưu các thành phần liên thông

    for (int i = 1; i <= n; i++) {
        if (!da_tham[i]) {                                // nếu i chưa được thăm
            vector<int> tp = BFS(i);                  // tìm thành phần liên thông chứa i
            cac_thanh_phan.push_back(tp);    // lưu vào danh sách các thành phần 
        }
    }

    cout << cac_thanh_phan.size() << "\n";   // in số thành phần liên thông
    for (auto& tp : cac_thanh_phan) {          // in từng thành phần 
        for (int v : tp) cout << v << " ";
        cout << "\n";
    }

    return 0;
}