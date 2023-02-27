#include <bits/stdc++.h>

using namespace std;

// 定义学生pair数组，依次存加权成绩、学分由高到低的科目成绩、学生姓名
pair<double, pair<int, pair<int, pair<int, pair<int, pair<int, string>>>>>> student[10001];
// 定义学分pair数组，依次存学分数目、序号（从0到4）
pair<int, int> point[5];
int main() {
    // 定义输入的学分并计算总学分
    int p, total_p = 0;
    for (int i = 0; i < 5; i++) {
        cin >> p;
        total_p += p;
        point[i] = make_pair(p, i);
    }
    // 对学分pair排序
    sort(point, point + 5);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        // 定义输入的成绩并输入学生姓名与各科成绩
        int g[5], total_g = 0;
        cin >> student[i].second.second.second.second.second.second;
        for (int j = 0; j < 5; j++) {
            cin >> g[j];
        }
        for (int j = 0; j < 5; j++) {
            // 计算总加权成绩
            total_g += g[point[j].second] * point[j].first;
            // 根据当前学分pair的学分数目及序号将成绩放入学生pair的指定位置
            switch (j) {
            case 4:
                student[i].second.first = g[point[j].second];
                break;
            case 3:
                student[i].second.second.first = g[point[j].second];
                break;
            case 2:
                student[i].second.second.second.first = g[point[j].second];
                break;
            case 1:
                student[i].second.second.second.second.first = g[point[j].second];
                break;
            case 0:
                student[i].second.second.second.second.second.first = g[point[j].second];
                break;
            default:
                break;
            }
        }
        // 计算平均加权成绩
        student[i].first = total_g * 1.0 / total_p;
    }
    // 对学生pair排序
    sort(student, student + n);
    // 逆向由大到小输出学生信息
    for (int i = n - 1; i >= 0; i--) {
        cout << student[i].second.second.second.second.second.second << " " << setiosflags(ios::fixed) << setprecision(2) << student[i].first << endl;
    }
    return 0;
}