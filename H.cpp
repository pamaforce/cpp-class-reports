#include <bits/stdc++.h>

using namespace std;

// 储存原始点的信息依次分别为x坐标原始值、y坐标大小排名、y坐标原始值、x坐标大小排名、点的序号
pair<pair<pair<int, int>, pair<int, int>>, int> raw_point[5001];
// 储存点的二维前缀和
int point[5001][5001];
// 储存答案
int ans[100001][4];

// 自定义比较函数，用来给y坐标排序
int cmp(pair<pair<pair<int, int>, pair<int, int>>, int> a, pair<pair<pair<int, int>, pair<int, int>>, int> b) {
    if (a.first.second != b.first.second)
        return a.first.second < b.first.second;
    else
        return a.first.first > b.first.first;
}

int main() {
    std::ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        // 输入点的坐标，并带上序号存储
        cin >> raw_point[i].first.first.first >> raw_point[i].first.second.first;
        raw_point[i].second = i;
    }
    // 按照y坐标优先进行排序
    sort(raw_point, raw_point + n, cmp);
    int ty = 0;
    for (int i = 0; i < n; i++) {
        // 特别处理一下坐标相等的情况，并将y坐标排名存储起来
        if (i > 0 && raw_point[i].first.second.first == raw_point[i - 1].first.second.first) {
            raw_point[i].first.first.second = raw_point[i - 1].first.first.second;
        } else
            raw_point[i].first.first.second = ty++;
    }
    // 按照x坐标优先进行排序
    sort(raw_point, raw_point + n);
    int tx = 0;
    for (int i = 1; i <= n; i++) {
        // 特别处理一下坐标相等的情况，并将x坐标排名存储起来
        if (i > 1 && raw_point[i - 1].first.first.first == raw_point[i - 2].first.first.first) {
            raw_point[i - 1].first.second.second = raw_point[i - 2].first.second.second;
        } else {
            raw_point[i - 1].first.second.second = tx++;
        }
        // 将点离散化存储到密集的点数组中
        point[raw_point[i - 1].first.second.second + 1][raw_point[i - 1].first.first.second + 1]++;
    }
    for (int i = 1; i <= tx; i++) {
        for (int j = 1; j <= ty; j++) {
            // 将点数组构造为二维前缀和数组
            point[i][j] = point[i][j] + point[i - 1][j] + point[i][j - 1] - point[i - 1][j - 1];
        }
    }
    int x, y;
    for (int i = 1; i <= m; i++) {
        cin >> x >> y;
        // 找到对应点的坐标排名
        int posX1 = 0, posY1 = 0, posX2 = 0, posY2 = 0;
        for (int j = 0; j < n; j++) {
            if (posX1 == 0 && raw_point[j].second == x) {
                posX1 = raw_point[j].first.second.second + 1;
                posY1 = raw_point[j].first.first.second + 1;
            }
            if (posX2 == 0 && raw_point[j].second == y) {
                posX2 = raw_point[j].first.second.second + 1;
                posY2 = raw_point[j].first.first.second + 1;
            }
            if (posX1 != 0 && posX2 != 0)
                break;
        }
        // 统一转换为右下角到左上角，否则答案算出来是错的，不满足公式
        if (posX1 > posX2) {
            ans[i][0] = posX1;
            ans[i][2] = posX2;
        } else {
            ans[i][0] = posX2;
            ans[i][2] = posX1;
        }
        if (posY1 > posY2) {
            ans[i][1] = posY1;
            ans[i][3] = posY2;
        } else {
            ans[i][1] = posY2;
            ans[i][3] = posY1;
        }
    }
    for (int i = 1; i <= m; i++) {
        // 通过二维前缀和求解
        cout << point[ans[i][0]][ans[i][1]] - point[ans[i][0]][ans[i][3] - 1] - point[ans[i][2] - 1][ans[i][1]] + point[ans[i][2] - 1][ans[i][3] - 1] << "\n";
    }
    return 0;
}