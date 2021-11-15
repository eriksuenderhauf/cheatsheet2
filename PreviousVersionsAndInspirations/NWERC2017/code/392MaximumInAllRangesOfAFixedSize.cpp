int n, a[1000000];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int k;
    //the maximum in all ranges of the requested size: ";
    deque<int> d;
    for (int i = 0; i < k; i++) {
        while (!d.empty() && a[i] >= a[d.back()])
            d.pop_back();
        d.push_back(i);
    }
    //the maximum in the first range a[d.front()]
    for (int i = k; i < n; i++) {
        while (!d.empty() && i - d.front() >= k)
            d.pop_front();
        while (!d.empty() && a[i] >= a[d.back()])
            d.pop_back();
        d.push_back(i);
        //the maximum in the other ranges a[d.front()]
    }
}
