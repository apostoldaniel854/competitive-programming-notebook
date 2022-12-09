struct CTC
{
    vector <vector <int>> adia, adia_rev;
    vector <int> comp;

    void AddEdge(int a, int b) {
        adia[a].push_back(b);
        adia_rev[b].push_back(a);
    }

    void ComputeComps() {
        int n = adia.size();
        vector <int> sortop, taken(n);
        function <void(int)> GetSortop = [&](int nod) {
            taken[nod] = 1;
            for (auto i : adia[nod]) {
                if (!taken[i])
                    GetSortop(i);
            }
            sortop.push_back(nod);
        };

        for (int i = 0; i < n; i++)
            if (!taken[i])
                GetSortop(i);
        
        reverse(sortop.begin(), sortop.end());

        function <void(int, int)> ColorComps = [&](int nod, int col) {
            comp[nod] = col;
            for (auto i : adia_rev[nod])
                if (comp[i] == -1)
                    ColorComps(i, col);
        };

        int nr_cols = 0;
        for (auto i : sortop)
            if (comp[i] == -1)
                ColorComps(i, nr_cols++);
    }

    CTC(int n) : adia(n), adia_rev(n), comp(n, -1) { }
};

struct SAT
{
    CTC ctc;
    int n;

    void AddEq(int i, int j) { /// adaugam xi v xj si daca i este negativ atunci xi este negat, la fel pentru j
        i = 2 * (abs(i) - 1) + (i < 0);
        j = 2 * (abs(j) - 1) + (j < 0);

        ctc.AddEdge(i ^ 1, j);
        ctc.AddEdge(j ^ 1, i);
    }

    vector <int> GetSolution() {
        ctc.ComputeComps();
        auto comps = ctc.comp;

        vector <int> ans(n);
        for (int i = 0; i < n; i++) {
            if (comps[2 * i] == comps[2 * i + 1])
                return { };
            ans[i] = (comps[2 * i] > comps[2 * i + 1]);
        }
        return ans;
    }

    SAT(int n) : ctc(2 * n), n(n) { }
};
