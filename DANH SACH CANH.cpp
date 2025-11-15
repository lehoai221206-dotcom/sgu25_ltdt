#include <fstream>
#include <vector>
using namespace std;
#define FI "DanhSachCanh.inp"
#define FO "DanhSachCanh.out"

// Cấu trúc cạnh của đồ thị vô hướng
struct Edge {
    int u, v;                  // cạnh nối từ u đến v
    Edge(int a, int b) {
        u = a;
        v = b;
    }
};

ifstream fi;                   // đối tượng để đọc file
ofstream fo;                // đối tượng để ghi file

int n, m;                      // n = số đỉnh, m = số cạnh
vector<Edge> edgeList;       // danh sách cạnh (m phần tử)
int bac[100001];                  // mảng lưu bậc của các đỉnh (giả sử tối đa 100000 đỉnh)

void Nhap() {
    fi.open(FI);            // mở file input
    fi >> n >> m;        // đọc số đỉnh và số cạnh

    // đọc m cạnh và lưu vào edgeList
    for (int i = 0; i < m; i++) {
        int u, v;  
        fi >> u >> v;                                   // đọc 2 đỉnh u và v
        edgeList.push_back(Edge(u, v));  // thêm cạnh (u, v) vào danh sách
    }
    fi.close();       
}

void XuLy() {
    // Khởi tạo tất cả bậc bằng 0
    for (int i = 1; i <= n; i++) {
        bac[i] = 0;
    }

    // Duyệt qua từng cạnh trong danh sách cạnh
    for (int i = 0; i < edgeList.size(); i++) {
        int u = edgeList[i].u;
        int v = edgeList[i].v;

        // Vì đồ thị vô hướng: cạnh (u, v) làm tăng bậc của cả u và v
        bac[u]++;
        bac[v]++;
    }
}
void Xuat() {
    fo.open(FO);

    fo << n << endl; 

    // Ghi bậc của từng đỉnh (từ 1 đến n)
    for (int i = 1; i <= n; i++) {
        fo << bac[i] << endl;
    }

    fo.close();
}


int main() {
    Nhap();       // đọc dữ liệu từ file input
    XuLy();      // tính toán bậc các đỉnh
    Xuat();       // ghi kết quả ra file output
    return 0;
}
