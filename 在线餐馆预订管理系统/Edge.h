#include <iostream>
#include <string>

using namespace std;
const int maxn = 1e6 + 10;
const int inf = 0x3f3f3f3f;

struct edge
{
    string to, next;
    float w;
} e[maxn];

struct node
{
    int w, now;
    bool operator<(const node x) const
    { //大根堆，大的在前
        return w > x.w;
    }
};

int getGBKindex(string s) {

    return (int)((unsigned char)s[0] - 129) * 190 + ((unsigned char)s[3] - 129) +
        ((unsigned char)s[2] - 64) - (unsigned char)s[1] / 128;
}

priority_queue<node> q;       //定义一个大根堆


