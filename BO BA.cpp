#include <iostream>
#include <string>
#include <map> 
using namespace std;

int main() {
    int T;
    cin >> T; // Nhập số lượng test

    while (T--) {
        string s;
        cin >> s;             // Nhập chuỗi
        int n = s.length();   // Độ dài chuỗi

        map<string, int> counter; // Map để đếm số lần xuất hiện của từng bộ ba ký tự

        // Duyệt chuỗi, cắt ra từng đoạn con dài 3 ký tự
        for (int i = 0; i + 2 < n; i++) {
            string triplet = s.substr(i, 3); // Lấy chuỗi con từ vị trí i, độ dài 3
            counter[triplet]++;              // Tăng số lần xuất hiện trong map
        }

        // Tìm số lần xuất hiện lớn nhất
        int maxCount = 0;
        for (auto p : counter) {
            if (p.second > maxCount) {
                maxCount = p.second; // Cập nhật tần suất lớn nhất
            }
        }

        // In ra kết quả cho chuỗi hiện tại
        cout << maxCount << "\n";
    }
    return 0;
}