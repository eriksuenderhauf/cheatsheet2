string s = "abc.xabc";

// copy string
string r(s.begin(), s.end()); // "abc.xabc"

// reverse string (2 ways)
reverse(s.begin(), s.end()); // "cbax.cba"
s = string(s.rbegin(), s.rend()); // "abc.xabc"

// find in string
size_t i = s.find('b'); // 1 (find character)
i = s.find("bc"); // 1 (substring in O(n*m))
i = s.find("bc", 2); // 6 (from position 2)
i = s.rfind("bc", 6); // 6 (backwards from 6)
i = s.find_first_of("xyz"); // 4 (first occurrence of x,y or z)
i = s.find_last_of("xyz"); // 4
i = s.find_first_not_of("abc"); // 3 ('.')

if(i != string::npos) cout << i; // found

// substrings
r = s.substr(s.find('x'), 2); // xa

// number conversion
r = to_string(42); // "42"
r = to_string(42.0);// "42.000000"
int x = stoi("42"); // 42
long long y = stoll("123456789123456789"); // 123...
double z = stod("1e7"); // 1e+007

// alternative conversion approach
r = "42 123456789123456789 1e7";
sscanf(r.c_str(), "%d %lld %lf", &x, &y, &z);

// more complex transformations
transform(s.begin(), s.end(), s.begin(), ::toupper); // "ABC.XABC"
transform(s.begin(), s.end(), s.begin(), ::tolower); // "abc.xabc"
// where tolower takes and returns a char

// with stringstream
stringstream ss("This is a test.");
while(!ss.eof()) {
    string next;
    ss >> next;
}

// getline with custom delimiter
ss = stringstream("comma,separ\nated,text");
cout << ss.str() << endl; // "comma...text"
string token;
while(getline(ss, token, ',')) {
    cout << token << endl; // "comma", "separ\nated", "text"
}
