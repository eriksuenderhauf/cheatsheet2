int greatestCommonDivisor(int a, int b) {
    return b == 0 ? a : greatestCommonDivisor(b, a % b);
}

int lowestCommonMultiple(int a, int b) {
    return a * b / greatestCommonDivisor(a, b);
}

pair<int, int> extendedEuclid(int a, int b) {
    if (b == 0)
        return {1, 0};
    pair<int, int> p = extendedEuclid(b, a % b);
    return {p.second, p.first - (a / b) * p.second};
}

pair<int, int> solveLinearDiophantineEquation(int a, int b, int s) {
    pair<int, int> p = extendedEuclid(a, b);
    int x = p.first, y = p.second, d = greatestCommonDivisor(a, b);
    if (s % d)
        return {0, 0};
    x *= s / d, y *= s / d;
    int dx = b / d, dy = - (a / d), n = 0;
    if (x < 0)
        n = - (x - dx + 1) / dx;
    if (y < 0)
        n = - (y + dy + 1) / dy;
    return {x + n * dx, y + n * dy};
}

int main() {
    int a, b, s;
    //the greatest common divisor
    greatestCommonDivisor(a, b);
    //the lowest common multiple
    lowestCommonMultiple(a, b);
    //solution a * p.first + b * p.second = s, no solution if p.first == 0 && p.second == 0 && s != 0
    pair<int, int> p = solveLinearDiophantineEquation(a, b, s);
}
