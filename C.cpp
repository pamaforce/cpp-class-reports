#include <bits/stdc++.h>

using namespace std;

// 定义一年中每个月的天数（2月默认28天，用到时动态修改）
int day_in_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
// 定义每个月的缩写
string month_in_eng[13] = {"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sept", "Oct", "Nov", "Dec"};
// 题目要求的mfc_time()函数，new_val为结果，old_val和t为输入
void mfc_time(long long int old_val[], long long int t, long long int new_val[]) {
    // 将秒数累加到原时间的秒上，然后超出的部分加到更高一阶的时间上，直至不超出
    new_val[5] = old_val[5] + t;
    new_val[4] = old_val[4];
    new_val[3] = old_val[3];
    new_val[2] = old_val[2];
    new_val[1] = old_val[1];
    new_val[0] = old_val[0];
    while (new_val[5] > 59) {
        new_val[5] -= 60;
        new_val[4]++;
        if (new_val[4] > 59) {
            new_val[4] -= 60;
            new_val[3]++;
            if (new_val[3] > 23) {
                new_val[3] -= 24;
                new_val[2]++;
                day_in_month[2] = (new_val[0] % 400 == 0 || (new_val[0] % 4 == 0 && new_val[0] % 100 != 0)) ? 29 : 28;
                if (new_val[2] > day_in_month[new_val[1]]) {
                    new_val[2] -= day_in_month[new_val[1]];
                    new_val[1]++;
                    if (new_val[1] > 12) {
                        new_val[1] -= 12;
                        new_val[0]++;
                    }
                }
            }
        }
    }
    // 可以处理当t为负数时的情况
    while (new_val[5] < 0) {
        new_val[5] += 60;
        new_val[4]--;
        if (new_val[4] < 0) {
            new_val[4] += 60;
            new_val[3]--;
            if (new_val[3] < 0) {
                new_val[3] += 24;
                new_val[2]--;
                day_in_month[2] = (new_val[0] % 400 == 0 || (new_val[0] % 4 == 0 && new_val[0] % 100 != 0)) ? 29 : 28;
                if (new_val[2] < 1) {
                    new_val[1]--;
                    if (new_val[1] < 1) {
                        new_val[1] += 12;
                        new_val[0]--;
                    }
                    new_val[2] += day_in_month[new_val[1]];
                }
            }
        }
    }
}
// 当位数不足两位时补0
string pad0(long long int s) {
    stringstream ss;
    if (s < 10) {
        ss << 0;
    }
    ss << s;
    return ss.str();
}

int main() {
    // 定义并输入n
    int n;
    cin >> n;
    while (n--) {
        // 定义当前时间和t并输入
        long long int time[6], t;
        cin >> time[0] >> time[1] >> time[2] >> time[3] >> time[4] >> time[5] >> t;
        long long int new_time[6];
        // 得到转换后的时间
        mfc_time(time, t, new_time);
        // 将转换后的时间按格式输出
        cout << month_in_eng[new_time[1]] << " " << new_time[2] << (new_time[2] == 1 || new_time[2] == 21 || new_time[2] == 31 ? "st " : new_time[2] == 2 || new_time[2] == 22 ? "nd "
                                                                                                                                     : new_time[2] == 3 || new_time[2] == 23   ? "rd "
                                                                                                                                                                               : "th ")
             << pad0(new_time[3]) << ":" << pad0(new_time[4]) << ":" << pad0(new_time[5]) << " " << new_time[0] << endl;
    }
    return 0;
}