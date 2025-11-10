#include <iostream>            
#include <vector>              
#include <stack>               
using namespace std;

vector<vector<int>> danhSachKe;   // danh sách kề

vector<int> mau;                   // mau[i] lưu màu của đỉnh i

// Trả về true nếu phần thành phần liên thông đó có thể tô 2 màu, ngược lại false
bool KiemTraPhanDoi(int start) {
    stack<int> st;
    st.push(start);                    // đưa đỉnh bắt đầu vào stack
    mau[start] = 0;                 // tô đỉnh bắt đầu màu 0

    while (!st.empty()) {
        int u = st.top();     // lấy đỉnh ở đỉnh stack 
        st.pop();               // loại bỏ đỉnh đó khỏi stack

        for (int v : danhSachKe[u]) {
            // nếu v chưa được tô màu, tô nó màu đối diện với u
            if (mau[v] == -1) {
                mau[v] = 1 - mau[u];           // 1 - mau[u] cho màu đối lập (0<->1)
                st.push(v);   
            }
            // nếu v đã tô và cùng màu với u -> phát hiện không phân đôi
            else if (mau[v] == mau[u]) {
                return false;       // trả về false ngay lập tức
            }
        }
    }
    return true;
}

int main() {
    int n;
    cin >> n;

    // cấp phát kích thước cho danh sách kề 
    danhSachKe.resize(n + 1);
    // khởi tạo mảng màu, tất cả đặt = -1 (chưa tô)
    mau.assign(n + 1, -1);


    for (int i = 1; i <= n; i++) {
        int dinhKe;
        while (cin >> dinhKe) {
            if (dinhKe == -1) break;                      // gặp -1 -> kết thúc danh sách kề cho đỉnh i
            danhSachKe[i].push_back(dinhKe);   // thêm đỉnh kề vào danhSachKe[i]
        }
    }

    bool ketQua = true;            // biến lưu kết quả chung 

    for (int i = 1; i <= n; i++) {
        if (mau[i] == -1) {         // nếu đỉnh i chưa được tô màu
            // gọi hàm kiểm tra bắt đầu từ i, nếu false -> không phân đôi
            if (!KiemTraPhanDoi(i)) {
                ketQua = false;    // cập nhật kết quả
                break;             // có thể dừng ngay vì đã biết không phân đôi
            }
        }
    }

    if (ketQua) cout << "Do thi phan doi\n";
    else cout << "Do thi khong phan doi\n";

    return 0;
}