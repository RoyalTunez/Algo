//Polygon stabbing problem solved in (O(n^2 + nm)) where is n size of polygon and m is lines amount

#include <utility>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <math.h>
#include <algorithm>
#include <string>
#include <iomanip>
#include <stdio.h>
#include <queue>
#include <cmath>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ld, ld> point;
#define x first
#define y second
const long double e = (ld)1e-9;

int n, m;
ld x, y;
vector<point> in;
set<pair<point, point>> edges;

struct triangl {
    point a, b, c;

    triangl(point in_a, point in_b, point in_c) : a(std::move(in_a)), b(std::move(in_b)), c(std::move(in_c)) {}
};

struct line {
    ld a, b, c;

    explicit line(pair<point, point> in_line) {
        a = in_line.x.y - in_line.y.y;
        b = in_line.y.x - in_line.x.x;
        c = -a * in_line.x.x - b * in_line.x.y;
    }

    line(point a, point b) : line(make_pair(a, b)) {
    }
};

bool equal(ld a, ld b) {
    return abs(a - b) < e;
}

bool equal(point a, point b) {
    return equal(a.x, b.x) && equal(a.y, b.y);
}

ld triangle_area(point a, point b, point c) {
    return a.x * b.y + b.x * c.y + c.x * a.y - a.y * b.x - b.y * c.x - c.y * a.x;
}

ld area(point a, point b, point c) {
    return abs(a.x * b.y + b.x * c.y + c.x * a.y - a.y * b.x - b.y * c.x - c.y * a.x) / 2.0;
}

bool clockwise(point a, point b, point c) {
    return triangle_area(a, b, c) < 0;
}

bool inside_triangle(point a, triangl c) {
    return equal(area(a, c.a, c.b) + area(a, c.b, c.c) + area(a, c.c, c.a), area(c.a, c.b, c.c));
}

ld det(ld a, ld b, ld c, ld d) {
    return a * d - b * c;
}

bool intersect(line fir, line sec, point &res) {
    ld zn = det(fir.a, fir.b, sec.a, sec.b);
    if (abs(zn) < e)
        return false;
    res.x = -det(fir.c, fir.b, sec.c, sec.b) / zn;
    res.y = -det(fir.a, fir.c, sec.a, sec.c) / zn;
    return true;
}

bool on_line(point pt, line l) {
    return equal(pt.x * l.a + pt.y * l.b + l.c, (ld) 0.0);
}

ld dist(point a, point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}


bool on_edge(point a, point b, point c) {
    return equal(dist(a, b) + dist(a, c), dist(b, c));
}


ld dist(line a, line b, line c, point b1, point b2, point c1, point c2) {
    point fir, sec;
    if (!intersect(a, b, fir)) {
        return (ld) 0.0;
    }
    if (!intersect(a, c, sec)) {
        return (ld) 0.0;
    }
    if (on_edge(fir, b1, b2) && on_edge(sec, c1, c2)) {
        return dist(fir, sec);
    } else {
        return (ld) 0.0;
    }
}

ld dist(point a, point b, triangl t) {
    if (equal(area(t.a, t.b, t.c), (ld) 0.0)) {
        return (ld) 0.0;
    }
    if (on_line(t.a, line(a, b)) && on_line(t.b, line(a, b))) {
        if (edges.find(make_pair(t.a, t.b)) != edges.end() || edges.find(make_pair(t.b, t.a)) != edges.end()) {
            return dist(t.a, t.b);
        } else {
            return dist(t.a, t.b) / 2.0;
        }
    }
    if (on_line(t.b, line(a, b)) && on_line(t.c, line(a, b))) {
        if (edges.find(make_pair(t.b, t.c)) != edges.end() || edges.find(make_pair(t.c, t.b)) != edges.end()) {
            return dist(t.b, t.c);
        } else {
            return dist(t.b, t.c) / 2.0;
        }
    }
    if (on_line(t.c, line(a, b)) && on_line(t.a, line(a, b))) {
        if (edges.find(make_pair(t.c, t.a)) != edges.end() || edges.find(make_pair(t.a, t.c)) != edges.end()) {
            return dist(t.c, t.a);
        } else {
            return dist(t.c, t.a) / 2.0;
        }
    }
    line l(a, b);
    line fir(make_pair(t.a, t.b)), sec(make_pair(t.b, t.c)), th(make_pair(t.a, t.c));
    if (!equal(dist(l, fir, sec, t.a, t.b, t.b, t.c), (ld) 0.0)) {
        return dist(l, fir, sec, t.a, t.b, t.b, t.c);
    }
    if (!equal(dist(l, sec, th, t.b, t.c, t.a, t.c), (ld) 0.0)) {
        return dist(l, sec, th, t.b, t.c, t.a, t.c);
    }
    if (!equal(dist(l, fir, th, t.a, t.b, t.a, t.c), (ld) 0.0)) {
        return dist(l, fir, th, t.a, t.b, t.a, t.c);
    }
    return (ld) 0.0;
}


void triangulation(vector<point> &a, vector<triangl> &ans) {
    int ptr1 = 0, ptr2 = 1, ptr3 = 2;
    int cnt = a.size();
    unordered_set<int> not_deleted;
    for (int i = 0; i < a.size(); i++) {
        not_deleted.insert(i);
    }
    int super_cnt = 0;
    while (cnt > 3 && super_cnt < a.size()) {
        if (clockwise(a[ptr1], a[ptr2], a[ptr3])) {
            bool inside = false;
            for (auto i: not_deleted) {
                if (!equal(a[ptr1], a[i]) && !equal(a[ptr2], a[i]) && !equal(a[ptr3], a[i])) {
                    if (inside_triangle(a[i], triangl(a[ptr1], a[ptr2], a[ptr3]))) {
                        inside = true;
                        break;
                    }
                }
            }
            if (!inside) {
                ans.emplace_back(a[ptr1], a[ptr2], a[ptr3]);
                not_deleted.erase(ptr2);
                int new_ptr = (ptr3 + 1) % a.size();
                while (not_deleted.find(new_ptr) == not_deleted.end()) {
                    new_ptr = (new_ptr + 1) % a.size();
                }
                ptr2 = ptr3;
                ptr3 = new_ptr;
                cnt--;
                super_cnt = 0;
            } else {
                int new_ptr = (ptr3 + 1) % a.size();
                while (not_deleted.find(new_ptr) == not_deleted.end()) {
                    new_ptr = (new_ptr + 1) % a.size();
                }
                swap(ptr1, ptr2);
                swap(ptr2, ptr3);
                swap(ptr3, new_ptr);
                super_cnt++;
                continue;
            }
        } else {
            int new_ptr = (ptr3 + 1) % a.size();
            while (not_deleted.find(new_ptr) == not_deleted.end()) {
                new_ptr = (new_ptr + 1) % a.size();
            }
            swap(ptr1, ptr2);
            swap(ptr2, ptr3);
            swap(ptr3, new_ptr);
            super_cnt++;
            continue;
        }
    }
    if (super_cnt == a.size()) {
        ans.clear();
    } else {
        ans.emplace_back(a[ptr1], a[ptr2], a[ptr3]);
    }
}

void triangulate(vector<point> a, vector<triangl> &ans) {
    triangulation(a, ans);
    if (ans.empty()) {
        reverse(a.begin() + 1, a.end());
        triangulate(a, ans);
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        in.emplace_back(x, y);
    }
    for (int i = 0; i < n; i++) {
        edges.insert(make_pair(in[i], in[(i + 1) % n]));
    }
    vector<triangl> triangles;
    triangulate(in, triangles);
    for (int i = 0; i < m; i++) {
        point a, b;
        cin >> a.x >> a.y >> b.x >> b.y;
        ld res = (ld) 0.0;
        for (auto j: triangles) {
            res += dist(a, b, j);
        }
        cout << setprecision(10) << fixed << res << endl;
    }
    return 0;
}
