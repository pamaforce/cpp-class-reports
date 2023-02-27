#include <bits/stdc++.h>

using namespace std;

// 因为每组字符串的长度不超过500，可知后缀自动机状态总数不会超过2*500-1=999，这里取2000保险
#define MAXSIZE 2000

int main() {
    // 定义并输入数据组数
    int n;
    cin >> n;
    while (n--) {
        // 定义并输入字符串
        string s;
        cin >> s;
        int s_length = s.length();
        // 定义并初始化要用到的数组
        int len[MAXSIZE], lnk[MAXSIZE], cnt[MAXSIZE], nxt[MAXSIZE][26], sub[MAXSIZE], c[MAXSIZE];
        memset(c, 0, sizeof c);
        memset(len, 0, sizeof len);
        memset(lnk, 0, sizeof lnk);
        memset(cnt, 0, sizeof cnt);
        memset(nxt, 0, sizeof nxt);
        // 定义并初始化答案，当前状态指针，last指针
        int answer = 0, index = 1, last = 1;
        // 遍历拓展字符串以等效字符串环
        for (int i = 0; i < 2 * s_length - 1; i++) {
            // 构造后缀自动机并记录各种状态，ch为当前要插入的字符
            int x = ++index, ch = s[i % s_length] - 'a';
            len[x] = len[last] + 1;
            sub[x] = 1;
            int p;
            for (p = last; p && !nxt[p][ch]; p = lnk[p])
                nxt[p][ch] = x;
            if (!p)
                lnk[x] = 1, cnt[1]++;
            else {
                int q = nxt[p][ch];
                if (len[p] + 1 == len[q])
                    lnk[x] = q, cnt[q]++;
                else {
                    int nq = ++index;
                    len[nq] = len[p] + 1;
                    lnk[nq] = lnk[q];
                    memcpy(nxt[nq], nxt[q], sizeof nxt[q]);
                    for (; p && nxt[p][ch] == q; p = lnk[p])
                        nxt[p][ch] = nq;
                    lnk[q] = lnk[x] = nq;
                    cnt[nq] += 2;
                }
            }
            last = x;
        }
        // 更新各个节点状态
        for (int i = 2; i <= index; i++) {
            c[len[lnk[i]] + 1]++;
            c[len[i] + 1]--;
        }
        // 累加长度为1到s_length的本质不同的子串数目
        for (int i = 1; i <= s_length; i++) {
            c[i] += c[i - 1];
            answer += c[i];
        }
        // 输出答案
        cout << answer << endl;
    }
}