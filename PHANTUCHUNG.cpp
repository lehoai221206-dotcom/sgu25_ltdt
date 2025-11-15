#include <iostream>
#include <algorithm> 
using namespace std;

int main() {
    int nx, ny, nz;

    // Nhập dãy x
    cin >> nx;
    int x[1001];               // vì nx ≤ 1000
    for (int i = 0; i < nx; i++) cin >> x[i];

    // Nhập dãy y
    cin >> ny;
    int y[1001];
    for (int i = 0; i < ny; i++) cin >> y[i];

    // Nhập dãy z
    cin >> nz;
    int z[1001];
    for (int i = 0; i < nz; i++) cin >> z[i];

    //  Sắp xếp 3 dãy để dễ so sánh
    sort(x, x + nx);
    sort(y, y + ny);
    sort(z, z + nz);

    int i = 0, j = 0, k = 0;

    int chung[1001];       // Lưu kết quả
    int dem = 0;             // Đếm số phần tử chung
    int truoc = -1;         // Dùng để tránh lưu trùng lặp

    while (i < nx && j < ny && k < nz) {
        if (x[i] == y[j] && y[j] == z[k]) {
            if (x[i] != truoc) {          // Kiểm tra tránh trùng lặp
                chung[dem++] = x[i];
                truoc = x[i];              // Cập nhật phần tử vừa lưu
            }
            i++; j++; k++;            // Tăng cả 3 chỉ số
        }
        else if (x[i] < y[j]) i++;         // Nếu x nhỏ nhất thì tăng i
        else if (y[j] < z[k]) j++;       // Nếu y nhỏ nhất thì tăng j
        else k++;                            // Ngược lại tăng k
    }

    cout << dem << endl;       // In số lượng phần tử chung
    for (int t = 0; t < dem; t++) {
        cout << chung[t] << " ";
    }
    return 0;
}