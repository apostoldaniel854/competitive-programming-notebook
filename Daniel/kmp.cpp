vector <int> matches (string s, int target) { /// for string matches put s = a + "#" + c
    vector <int> pi (s.size ());
    pi[0] = 0;
    vector <int> sol;
    for (int i = 1; i < s.size (); i++) {
        int cur = pi[i - 1];
        while (cur && s[i] != s[cur])
            cur = pi[cur - 1];
        if (s[i] == s[cur])
            cur++;
        pi[i] = cur;
        if (pi[i] == target)
            sol.push_back (i - 2 * target);
    }
    return sol;
}
