#include <bits/stdc++.h>

using namespace std;
class MyInteger {
private:
    // 用vector容器来管理内存空间
    vector<int> num;

public:
    MyInteger() : MyInteger("0") {}
    MyInteger(vector<int> n) {
        // 去除前导0
        while (n.back() == 0)
            n.pop_back();
        if (n.empty())
            n.push_back(0);
        num = n;
    }
    MyInteger(string n) {
        // 去除前导0
        int nl = n.length(), i = 0;
        while (i < nl && n[i] == '0')
            i++;
        string x = n.substr(i);
        if (x.empty())
            x = "0";
        int xl = x.length();
        for (int i = xl - 1; i >= 0; i--) {
            num.push_back(x[i] - '0');
        }
    }
    MyInteger(const char *n) : MyInteger((string)n) {}
    MyInteger(int num) : MyInteger(to_string(num)) {}
    ~MyInteger() {}
    string getnum() {
        string ans = "";
        // 由于是逆向存储，输出时使用反向迭代器遍历
        for (vector<int>::reverse_iterator it = num.rbegin(); it != num.rend(); it++) {
            ans += to_string(*it);
        }
        return ans;
    }
    // 由于num为私有变量，提供这个函数来供重载运算符获取容器长度
    int getsize() const {
        return num.size();
    }
    // 由于num为私有变量，提供这个函数来供重载运算符获取容器元素
    int getpos(int pos) const {
        return num.at(pos);
    }
    // 重载+运算符
    MyInteger operator+(const MyInteger &bint2) {
        // c为进位，以下为模拟加法运算
        int c = 0, l = 0;
        vector<int> temp;
        while (c || l < num.size() || l < bint2.getsize()) {
            if (l < num.size())
                c += num.at(l);
            if (l < bint2.getsize())
                c += bint2.getpos(l);
            temp.push_back(c % 10);
            c /= 10;
            l++;
        }
        MyInteger res(temp);
        return res;
    }
    // 重载-运算符
    MyInteger operator-(const MyInteger &bint2) {
        // b为借位，以下为模拟减法运算，由题意不考虑负数
        int b = 0, l = 0;
        vector<int> temp;
        while (l < num.size()) {
            int t = num.at(l) - b + 10;
            if (l < bint2.getsize())
                t -= bint2.getpos(l);
            temp.push_back(t % 10);
            b = 1 - t / 10;
            l++;
        }
        MyInteger res(temp);
        return res;
    }
    // 重载*运算符
    MyInteger operator*(const MyInteger &bint2) {
        // c为进位，以下为模拟乘法运算
        int c = 0, l = 1;
        vector<int> temp;
        temp.push_back(0);
        for (int i = 0; i < num.size(); i++) {
            c = 0;
            for (int j = 0; j < bint2.getsize(); j++) {
                if (i + j >= l) {
                    temp.push_back(0);
                    l++;
                }
                int p = temp.at(i + j);
                p += num.at(i) * bint2.getpos(j) + c;
                c = p / 10;
                p %= 10;
                temp.at(i + j) = p;
            }
            temp.push_back(c);
            l++;
        }
        MyInteger res(temp);
        return res;
    }
};

int main() {
    return 0;
}