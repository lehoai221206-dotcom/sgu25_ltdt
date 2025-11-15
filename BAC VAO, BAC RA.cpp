#include <fstream>  
using namespace std;
#define FI "BacVaoBacRa.inp"     // File input chứa ma trận kề
#define FO "BacVaoBacRa.out"  // File output chứa kết quả bậc vào/ra

ifstream fi;                                    // Đối tượng để đọc file input
ofstream fo;                                 // Đối tượng để ghi file output


int n;                          // Số đỉnh của đồ thị
int a[1001][1001];    // Ma trận kề của đồ thị (tối đa 1000 đỉnh)
int bacVao[1001];    // Mảng lưu bậc vào 
int bacRa[1001];     // Mảng lưu bậc ra 


void Nhap()
{
    fi.open(FI);        // Mở file input để đọc

    fi >> n;             // Đọc số đỉnh của đồ thị (n ≤ 1000)


    for (int i = 0; i < n; i++) {        // Duyệt qua từng hàng (từ đỉnh 0 đến n-1)
        for (int j = 0; j < n; j++) {    // Duyệt qua từng cột (từ đỉnh 0 đến n-1)
            fi >> a[i][j];                     // Đọc giá trị 0 hoặc 1 tại vị trí [i][j]
        }
    }

    fi.close();
}


void XuLy()
{
    for (int i = 0; i < n; i++) {
        bacVao[i] = 0;    // Khởi tạo bậc vào của đỉnh i = 0
        bacRa[i] = 0;     // Khởi tạo bậc ra của đỉnh i = 0
    }
 
    for (int i = 0; i < n; i++) {         // Duyệt qua từng đỉnh i
        for (int j = 0; j < n; j++) {     // Duyệt qua từng đỉnh j
            if (a[i][j] == 1) {              // Nếu có cung từ đỉnh i đến đỉnh j
                bacRa[i]++;                 // Tăng bậc ra của đỉnh i lên 1
                bacVao[j]++;              // Tăng bậc vào của đỉnh j lên 1
            }
        }
    }
}


void Xuat()
{
    fo.open(FO);         // Mở file output để ghi

    fo << n << endl;  // Ghi số đỉnh của đồ thị

    for (int i = 0; i < n; i++) {
        fo << bacVao[i] << " " << bacRa[i] << endl;
    }

    fo.close();
}

int main()
{
    Nhap();      //  Đọc dữ liệu từ file input
    XuLy();    //  Tính bậc vào và bậc ra của các đỉnh
    Xuat();    //  Ghi kết quả ra file output
    return 0;
}