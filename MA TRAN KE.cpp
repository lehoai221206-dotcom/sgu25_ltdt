#include <fstream>  
using namespace std;
#define FI "MaTranKe.inp"     // File input chứa ma trận kề
#define FO "MaTranKe.out"  // File output chứa kết quả bậc các đỉnh
 
ifstream fi;     // Đối tượng để đọc file input
ofstream fo;  // Đối tượng để ghi file output

int n;                         // Số đỉnh của đồ thị
int a[1001][1001];  // Ma trận kề của đồ thị (tối đa 1000 đỉnh)
int bac[1001];       // Mảng lưu bậc của các đỉnh

void Nhap()
{
    fi.open(FI);  // Mở file input để đọc

    fi >> n;                                         // Đọc số đỉnh của đồ thị (n ≤ 1000)

    for (int i = 0; i < n; i++) {        // Duyệt qua từng hàng (từ đỉnh 0 đến n-1)
        for (int j = 0; j < n; j++) {    // Duyệt qua từng cột (từ đỉnh 0 đến n-1)
            fi >> a[i][j];                     // Đọc giá trị 0 hoặc 1 tại vị trí [i][j]
        }
    }

    fi.close();
}

void XuLy()
{
    // Duyệt qua tất cả các đỉnh của đồ thị
    for (int i = 0; i < n; i++) {
        bac[i] = 0;                              // Khởi tạo bậc của đỉnh i = 0

        // Duyệt qua tất cả các đỉnh kề với đỉnh i
        for (int j = 0; j < n; j++) {
            if (a[i][j] == 1) {              // Nếu có cạnh nối từ đỉnh i đến đỉnh j
                bac[i]++;                     // Tăng bậc của đỉnh i lên 1
            }
        }
    }
}

void Xuat()
{
    fo.open(FO);            // Mở file output để ghi

    fo << n << endl;      // Ghi số đỉnh của đồ thị
    // Ghi bậc của từng đỉnh (từ đỉnh 0 đến n-1)
    for (int i = 0; i < n; i++) {
        fo << bac[i] << endl;
    }

    fo.close();
}

int main()
{
    Nhap();      //  Đọc dữ liệu từ file input
    XuLy();    //  Tính bậc của các đỉnh
    Xuat();    //  Ghi kết quả ra file output
    return 0;
}
