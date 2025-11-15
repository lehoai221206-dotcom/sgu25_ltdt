#include <iostream>
#include <vector>
#include <utility>
using namespace std;

// 1. Ma trận kề sang danh sách kề
vector<vector<int>> matrixToAdjList(const vector<vector<int>>& mat, int n) {
    vector<vector<int>> adjList(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (mat[i][j] == 1) {
                adjList[i].push_back(j);
            }
        }
    }
    return adjList;
}

// 2. Ma trận kề sang danh sách cạnh
vector<pair<int, int>> matrixToEdgeList(const vector<vector<int>>& mat, int n) {
    vector<pair<int, int>> edgeList;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            if (mat[i][j] == 1) {
                edgeList.push_back({i, j});
            }
        }
    }
    return edgeList;
}

// 3. Danh sách kề sang ma trận kề
vector<vector<int>> adjListToMatrix(const vector<vector<int>>& adjList, int n) {
    vector<vector<int>> matrix(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j : adjList[i]) {
            matrix[i][j] = 1;
        }
    }
    return matrix;
}

// 4. Danh sách kề sang danh sách cạnh
vector<pair<int, int>> adjListToEdgeList(const vector<vector<int>>& adjList, int n) {
    vector<pair<int, int>> edgeList;
    for (int i = 1; i <= n; i++) {
        for (int neighbor : adjList[i]) {
            if (i <= neighbor) { // Chỉ thêm khi i <= neighbor để tránh trùng lặp
                edgeList.push_back({i, neighbor});
            }
        }
    }
    return edgeList;
}

// 5. Danh sách cạnh sang ma trận kề
vector<vector<int>> edgeListToMatrix(const vector<pair<int, int>>& edgeList, int n) {
    vector<vector<int>> matrix(n + 1, vector<int>(n + 1, 0));
    for (auto edge : edgeList) {
        int u = edge.first;
        int v = edge.second;
        matrix[u][v] = 1;
        if (u != v) {
            matrix[v][u] = 1;
        }
    }
    return matrix;
}

// 6. Danh sách cạnh sang danh sách kề
vector<vector<int>> edgeListToAdjList(const vector<pair<int, int>>& edgeList, int n) {
    vector<vector<int>> adjList(n + 1);
    for (auto edge : edgeList) {
        int u = edge.first;
        int v = edge.second;
        adjList[u].push_back(v);
        if (u != v) {
            adjList[v].push_back(u);
        }
    }
    return adjList;
}

// Hàm in ma trận kề
void printMatrix(const vector<vector<int>>& matrix, int n) {
    cout << "Ma tran ke:\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Hàm in danh sách kề
void printAdjList(const vector<vector<int>>& adjList, int n) {
    cout << "Danh sach ke:\n";
    for (int i = 1; i <= n; i++) {
        cout << i << ": ";
        for (int neighbor : adjList[i]) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
}

// Hàm in danh sách cạnh
void printEdgeList(const vector<pair<int, int>>& edgeList) {
    cout << "Danh sach canh:\n";
    for (auto edge : edgeList) {
        cout << "(" << edge.first << ", " << edge.second << ") ";
    }
    cout << endl;
}

int main() {
    int n = 3;
    
    // Khởi tạo ma trận kề mẫu
    vector<vector<int>> matrix = {
        {0, 0, 0, 0},
        {0, 0, 1, 1},
        {0, 1, 1, 0},
        {0, 1, 0, 1}
    };
    
    cout << " CHUYEN DOI CAC DANG BIEU DIEN DO THI\n\n";
    
    // 1. Ma trận kề -> Danh sách kề
    vector<vector<int>> adjList1 = matrixToAdjList(matrix, n);
    cout << "1. Ma tran ke -> Danh sach ke:\n";
    printAdjList(adjList1, n);
    cout << endl;
    
    // 2. Ma trận kề -> Danh sách cạnh
    vector<pair<int, int>> edgeList1 = matrixToEdgeList(matrix, n);
    cout << "2. Ma tran ke -> Danh sach canh:\n";
    printEdgeList(edgeList1);
    cout << endl;
    
    // 3. Danh sách kề -> Ma trận kề
    vector<vector<int>> matrix2 = adjListToMatrix(adjList1, n);
    cout << "3. Danh sach ke -> Ma tran ke:\n";
    printMatrix(matrix2, n);
    cout << endl;
    
    // 4. Danh sách kề -> Danh sách cạnh
    vector<pair<int, int>> edgeList2 = adjListToEdgeList(adjList1, n);
    cout << "4. Danh sach ke -> Danh sach canh:\n";
    printEdgeList(edgeList2);
    cout << endl;
    
    // 5. Danh sách cạnh -> Ma trận kề
    vector<vector<int>> matrix3 = edgeListToMatrix(edgeList2, n);
    cout << "5. Danh sach canh -> Ma tran ke:\n";
    printMatrix(matrix3, n);
    cout << endl;
    
    // 6. Danh sách cạnh -> Danh sách kề
    vector<vector<int>> adjList2 = edgeListToAdjList(edgeList2, n);
    cout << "6. Danh sach canh -> Danh sach ke:\n";
    printAdjList(adjList2, n);
    
    return 0;
}