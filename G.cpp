#include <bits/stdc++.h>

using namespace std;

// 定义n与答案计数器
int n, cnt = 0;
// 定义符号映射表
char op[5] = {' ', '+', '-', '*', '/'};
// 定义符号数组
int posture[6];
// 定义卡牌数组
int card[6];

// 查找主符号，*/优先级大于+-
int find_main_symbol(int l, int r) {
    for (int i = r - 1; i >= l; i--) {
        if (posture[i] == 1 || posture[i] == 2) {
            return i;
        }
    }
    for (int i = r - 1; i >= l; i--) {
        if (posture[i] == 3 || posture[i] == 4) {
            return i;
        }
    }
    return -1;
}
// 计算表达式值的递归函数
int calculate(int l, int r) {
    // 查找主符号的位置
    int pos = find_main_symbol(l, r);
    if (pos == -1) {
        return card[l];
    }
    // 根据主符号位置左右分治递归
    int left = calculate(l, pos);
    int right = calculate(pos + 1, r);
    switch (posture[pos]) {
    case 1:
        return left + right;
    case 2:
        return left - right;
    case 3:
        return left * right;
    case 4:
        return left / right;
    default:
        break;
    }
    return 0;
}

int stack_calculate() {
    // 定义数字栈和符号栈
    int num_stack[6], num_p = -1, op_stack[6], op_p = 0;
    op_stack[0] = -3;
    for (int i = 0; i < n; i++) {
        num_stack[++num_p] = card[i];
        if (i < n - 1)
            // 如果将要入栈的元素优先级小于等于栈顶元素
            if (posture[i] / 3 <= op_stack[op_p] / 3) {
                switch (op_stack[op_p]) {
                case 1:
                    num_stack[num_p - 1] += num_stack[num_p];
                    break;
                case 2:
                    num_stack[num_p - 1] -= num_stack[num_p];
                    break;
                case 3:
                    num_stack[num_p - 1] *= num_stack[num_p];
                    break;
                case 4:
                    num_stack[num_p - 1] /= num_stack[num_p];
                    break;
                default:
                    break;
                }
                num_p--;
                op_stack[op_p] = posture[i];
            } else {
                op_stack[++op_p] = posture[i];
            }
    }
    // 清空符号栈
    while (op_p > 0) {
        switch (op_stack[op_p]) {
        case 1:
            num_stack[num_p - 1] += num_stack[num_p];
            break;
        case 2:
            num_stack[num_p - 1] -= num_stack[num_p];
            break;
        case 3:
            num_stack[num_p - 1] *= num_stack[num_p];
            break;
        case 4:
            num_stack[num_p - 1] /= num_stack[num_p];
            break;
        default:
            break;
        }
        num_p--;
        op_p--;
    }

    return num_stack[0];
}

// 通过递归来填满各个空位的符号
void recurrence(int k) {
    // 如果填满了，使用相应方法验证点数是否为24从而计数输出
    if (k == n - 1) {
        // 使用栈模拟法
        // int ans = stack_calculate();
        // 使用主符号法
        int ans = calculate(0, n);
        if (ans == 24) {
            cnt++;
            for (int i = 0; i < n; i++) {
                cout << card[i];
                if (i < n - 1)
                    cout << op[posture[i]];
            }
            cout << endl;
        }

        return;
    }
    // 否则继续填
    for (int i = 1; i < 5; i++) {
        posture[k] = i;
        recurrence(k + 1);
    }
}

int main() {
    // 输入n张卡牌并进行排序
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> card[i];
    }
    sort(card, card + n);
    // 对卡牌全排列中的每一种情况进行递归
    do {
        recurrence(0);
    } while (next_permutation(card, card + n));
    // 输出答案数
    cout
        << cnt << endl;
    return 0;
}