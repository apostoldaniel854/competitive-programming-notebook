
void addTo(int &a, int b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
}

int mult(int a, int b) {
    return 1ll * a * b % MOD;
}

int lgput(int a, int b) {
    int ans = 1;
    while (b > 0) {
        if (b & 1)
            ans = mult(ans, a);
        a = mult(a, a);
        b /= 2;
    }
    return ans;
}

int invMod(int x) {
    return lgput(x, MOD - 2);
}
