#include <bits/stdc++.h>

using namespace std;
// 定义char二维数组存储每一行字符
char s[100][100];

int main() {
    // 定义n并输入n
    int n;
    cin >> n;
    // 定义四个边界以将空白剔除，定义当前行k
    int top_pointer = 100, left_pointer = 100, bottom_pointer = -1, right_pointer = -1, k = 0;
    // 吃掉第一个回车
    cin.get();
    while (k < n) {
        cin.getline(s[k], 100);
        int sk_length = strlen(s[k]);
        // 表明此行是否是纯空白行，并且以下为维护四个边界
        bool space_flag = true;
        for (int i = 0; i < sk_length; i++) {
            if (s[k][i] != ' ') {
                if (space_flag)
                    space_flag = false;
                if (i < left_pointer)
                    left_pointer = i;
                if (i > right_pointer) {
                    right_pointer = i;
                }
            }
        }
        for (int i = sk_length; i < 100; i++)
            s[k][i] = ' ';
        if (!space_flag) {
            if (k < top_pointer)
                top_pointer = k;
            if (k > bottom_pointer)
                bottom_pointer = k;
        }
        k++;
    }
    // 储存好感度
    int ans = 0;
    // 通过计算中点,引入奇偶标识来减少判断次数
    int mid_x = (left_pointer + right_pointer) / 2;
    int mid_y = (top_pointer + bottom_pointer) / 2;
    bool odd_x = (left_pointer + right_pointer) % 2 == 0;
    bool odd_y = (top_pointer + bottom_pointer) % 2 == 0;
    // 分别表明三种对称情况是否有可能成立
    bool x = true,
         y = true, xy = true;
    // 在限定的范围内遍历需要判断的字符
    for (int i = top_pointer; i <= bottom_pointer; i++) {
        for (int j = left_pointer; j <= right_pointer; j++) {
            if (i <= mid_y && y) {
                if (s[i][j] != s[bottom_pointer - i + top_pointer][j] || (odd_y && 2 * i + 1 == bottom_pointer + top_pointer && s[i][j] != ' '))
                    y = false;
            }
            if (j <= mid_x && x) {
                if (s[i][j] != s[i][right_pointer - j + left_pointer] || (odd_x && 2 * j + 1 == right_pointer + left_pointer && s[i][j] != ' '))
                    x = false;
            }
            if (j <= mid_x && xy) {
                if (s[i][j] != s[bottom_pointer - i + top_pointer][right_pointer - j + left_pointer])
                    xy = false;
            }
        }
    }
    // 计算并输出好感度
    if (x)
        ans += 1;
    if (y)
        ans += 2;
    if (xy)
        ans += 3;
    cout << ans << endl;
    return 0;
}