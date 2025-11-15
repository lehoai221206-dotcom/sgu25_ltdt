#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#define FI "DanhSachKe.inp"  
#define FO "DanhSachKe.out"  
ifstream fi;                // Đối tượng để đọc file input
ofstream fo;              // Đối tượng để ghi file output

vector<int> danhSachKe[100001];  // Mảng các vector lưu danh sách kề của từng đỉnh
int bac[100001];                               // Mảng lưu bậc của các đỉnh
int n;                                                // Số đỉnh của đồ thị

void Nhap() {
    fi.open(FI);                // Mở file input để đọc

    fi >> n;                       // Đọc số đỉnh n của đồ thị

    // Đọc danh sách kề cho từng đỉnh (từ đỉnh 1 đến n)
    for (int i = 1; i <= n; i++) {
        int dinhKe;            // Biến lưu đỉnh kề đọc được từ file

        // Đọc lần lượt các đỉnh kề cho đến khi gặp số -1
        while (fi >> dinhKe && dinhKe != -1) {
            danhSachKe[i].push_back(dinhKe);      // Thêm đỉnh kề vào danh sách của đỉnh i
        }
    }

    fi.close();
}
void XuLy() {

    for (int i = 1; i <= n; i++) {
         // Bậc của đỉnh i = số lượng đỉnh kề trong danh sách kề của nó
        bac[i] = danhSachKe[i].size();
    }
}
void Xuat() {
    fo.open(FO);          // Mở file output để ghi

    fo << n << endl;   // Ghi số đỉnh của đồ thị

    // Ghi bậc của từng đỉnh (từ đỉnh 1 đến n)
    for (int i = 1; i <= n; i++) {
        fo << bac[i] << endl;
    }

    fo.close();
}
int main() {
    Nhap();     //  Đọc dữ liệu từ file input
    XuLy();    // Tính bậc của các đỉnh
    Xuat();    //  Ghi kết quả ra file output

    return 0;
}
