const long double inf = 1e100, eps = 1e-12;

struct point {
    long double x, y;
    bool operator<(point & b) {
        if (x != b.x)
            return x < b.x;
        return y < b.y;
    }
    bool operator==(point b) {
        return x == b.x && y == b.y;
    }
    point operator+(point b) {
        return {x + b.x, y + b.y};
    }
    point operator-(point b) {
        return {x - b.x, y - b.y};
    }
    point operator*(long double b) {
        return {x * b, y * b};
    }
    point operator/(long double b) {
        return {x / b, y / b};
    }
    long double length() {
        return sqrt(x * x + y * y);
    }
};

long double dot(point a, point b) {
    return a.x * b.x + a.y * b.y;
}

long double cross(point a, point b) {
    return a.x * b.y - a.y * b.x;
}

long double dist(point a, point b) {
    point d = a - b;
    return d.length();
}

long double angle(point a, point b) {
    return acos(dot(a, b) / a.length() / b.length());
}

bool collinear(point a, point b) {
    return fabs(cross(a, b)) < eps;
}

bool collinear(point p, point a, point b) {
    return collinear(a - p, b - p);
}

bool ccw(point a, point b) {
    return cross(a, b) > 0;
}

bool ccw(point p, point a, point b) {
    return ccw(a - p, b - p);
}

point rotateCCW90(point p) {
    return {-p.y, p.x};
}

point rotateCW90(point p) {
    return {p.y, -p.x};
}

point rotateCCW(point p, double t) {
    return {p.x * cos(t) - p.y * sin(t), p.x * sin(t) + p.y * cos(t)};
}

point projectPointLine(point a, point b, point c) {
    long double r = dot(b - a, b - a);
    if (fabs(r) < eps)
        return a;
    r = dot(c - a, b - a) / r;
    return a + (b - a) * r;
}

long double distancePointLine(point a, point b, point c) {
    return dist(c, projectPointLine(a, b, c));
}

point projectPointSegment(point a, point b, point c) {
    long double r = dot(b - a, b - a);
    if (fabs(r) < eps)
        return a;
    r = dot(c - a, b - a) / r;
    if (r < 0)
        return a;
    if (r > 1)
        return b;
    return a + (b - a) * r;
}

long double distancePointSegment(point a, point b, point c) {
    return dist(c, projectPointSegment(a, b, c));
}

bool linesParallel(point a, point b, point c, point d) {
    return fabs(cross(b - a, c - d)) < eps;
}

bool linesCollinear(point a, point b, point c, point d) {
    return linesParallel(a, b, c, d) && fabs(cross(a - b, a - c)) < eps && fabs(cross(c - d, c - a)) < eps;
}

bool segmentsIntersect(point a, point b, point c, point d) {
    if (linesCollinear(a, b, c, d)) {
        if (dist(a, c) < eps || dist(a, d) < eps || dist(b, c) < eps || dist(b, d) < eps )
            return true;
        if (dot(c - a, c - b) > 0 && dot(d - a, d - b) > 0 && dot(c - b, d - b) > 0)
            return false;
        return true;
    }
    if (cross(d - a, b - a) * cross(c - a, b - a) > 0)
        return false;
    if (cross(a - c, d - c) * cross(b - c, d - c) > 0)
        return false;
    return true;
}

point computeLineIntersection(point a, point b, point c, point d) {
    b = b - a, d = c - d, c = c - a;
    if (dot(b, b) < eps || dot(d, d) < eps)
        return a;
    return a + b * cross(c, d) / cross(b, d);
}

point computeCircleCenter(point a, point b, point c) {
    b = (a + b) /2;
    c = (a + c) /2;
    return computeLineIntersection(b, b + rotateCW90(a-b), c, c + rotateCW90(a - c));
}

bool pointInPolygon(vector<point> & p, point q) {
    bool c = false;
    for (int i = 0; i < p.size(); i++) {
        int j = (i + 1) % p.size();
        if ((p[i].y <= q.y && q.y < p[j].y || p[j].y <= q.y && q.y < p[i].y) &&
            q.x < p[i].x + (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y))
            c = !c;
    }
    return c;
}

bool pointOnPolygon(vector<point> & p, point q) {
    for (int i = 0; i < p.size(); i++)
        if (dist(projectPointSegment(p[i], p[(i + 1) % p.size()], q), q) < eps)
            return true;
    return false;
}

vector<point> circleLineIntersection(point a, point b, point c, double r) {
    vector<point> ret;
    b = b - a;
    a = a - c;
    double A = dot(b, b);
    double B = dot(a, b);
    double C = dot(a, a) - r * r;
    double D = B * B - A * C;
    if (D < -eps)
        return ret;
    ret.push_back(c + a + b * (-B + sqrt(D + eps)) / A);
    if (D > eps)
        ret.push_back(c + a + b * (-B - sqrt(D)) / A);
    return ret;
}

vector<point> circleCircleIntersection(point a, point b, double r, double R) {
    vector<point> ret;
    double d = dist(a, b);
    if (d > r + R || d + min(r, R) < max(r, R))
        return ret;
    long double x = (d * d - R * R + r * r) / (2 * d);
    long double y = sqrt(r * r - x * x);
    point v = (b - a) / d;
    ret.push_back(a + v * x + rotateCCW90(v) * y);
    if (y > 0)
        ret.push_back(a + v * x - rotateCCW90(v) * y);
    return ret;
}

long double computeSignedArea(vector<point> & p) {
    long double area = 0;
    for (int i = 0; i < p.size(); i++) {
        int j = (i + 1) % p.size();
        area += p[i].x * p[j].y - p[j].x * p[i].y;
    }
    return area / 2.0;
}

long double computeArea(vector<point> & p) {
    return fabs(computeSignedArea(p));
}

point computeCentroid(vector<point> & p) {
    point c = {0 ,0};
    double scale = 6.0 * computeSignedArea(p);
    for (int i = 0; i < p.size(); i++) {
        int j = (i + 1) % p.size();
        c = c + (p[i] + p[j]) *(p[i].x * p[j].y - p[j].x * p[i].y);
    }
    return c / scale ;
}

bool isSimple(vector<point> & p) {
    for (int i = 0; i < p.size(); i++) {
        for (int k = i + 1; k < p.size(); k++) {
            int j = (i + 1) % p.size();
            int l = (k + 1) % p.size();
            if (i == l || j == k)
                continue;
            if (segmentsIntersect(p[i], p[j], p[k], p[l]))
                return false;
        }
    }
    return true;
}

int n;
point s = {1000000000, 1000000000};
point p[100000];

bool comp(point & a, point & b) {
    if (a == s)
        return true;
    if (b == s)
        return false;
    if (collinear(s, a, b))
        return dist(a, s) < dist(b, s);
    return ccw(s, a, b);
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
        if (p[i] < s)
            s = p[i];
    }
    sort(p, p + n, comp);
    p[n] = s;

    vector<int> res;
    res.push_back(0);
    res.push_back(1);
    for (int i = 2; i <= n; i++) {
        while (res.size() >= 2 && ccw(p[res[res.size() - 2]], p[i], p[res[res.size() - 1]]))
            res.pop_back();
        if (i != n)
            res.push_back(i);
    }

    //the convex hull
    for (int i : res)
        //(p[i].x , p[i])
}
