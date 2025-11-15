#include <iostream>
using namespace std;

int main() {
    long long n;
    // Chương trình chạy liên tục, đọc nhiều giá trị n cho đến khi hết dữ liệu
    while (cin >> n) {
        long long sokhong = 0; // Biến đếm số chữ số 0 tận cùng của n!

        // số 0 tận cùng xuất hiện khi có thừa số 2 * 5,
        // mà số 2 xuất hiện nhiều hơn số 5, 
        // nên chỉ cần đếm số mũ của 5 trong n!
        while (n > 0) {
            n /= 5;          // Đếm xem có bao nhiêu bội số của 5, 25, 125, ...
            sokhong += n;    // Cộng dồn vào tổng số mũ của 5
        }

        // In ra số chữ số 0 tận cùng của n!
        cout << sokhong << endl;
    }
    return 0;
}