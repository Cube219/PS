#include <sstream>

int qNum, maxQNum;
vector<int> d;

void get_data(int n)
{
#ifdef CUBE_PS
    maxQNum = n;
    qNum = 0;

    // ----- Get the data from cin -----
    d.resize(n);
    // -----------------------------
#endif
}

int query()
{
    stringstream ss;
    // ----- Query -----
    ss << "? ";
    // -----------------

    int res;
#ifdef CUBE_PS
    cout << "query: " << ss.str() << "\n";
    qNum++;
    if(qNum > maxQNum) {
        cout << "WA: Too many queries (" << qNum << ")\n";
        exit(1);
    }

    // ----- Generate a query result -----
    res = 0;
    // ----------------------------

    cout << "  - result: " << res << "\n";
#else
    cout << ss.str() << endl;
    cin >> res;
#endif

    return res;
}

void answer()
{
    stringstream ss;
    // ----- Answer -----
    ss << "! ";
    // ------------------

#ifdef CUBE_PS
    cout << "answer: " << ss.str() << "\n";

    // ----- Check the answer -----
    bool res = true;

    // --------------------------

    if(res == false) {
        cout << "WA: the answer is incorrect\n";
        exit(1);
    } else {
        cout << "Correct (" << qNum << " queries)\n";
    }
#else
    cout << ss.str() << endl;
#endif
}
