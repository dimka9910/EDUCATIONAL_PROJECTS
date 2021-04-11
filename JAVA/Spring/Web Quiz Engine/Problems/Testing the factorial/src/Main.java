public long get(int x) {
    if (x < 0)
        return -1;
    if (x == 0)
        return 1;

    int tmp = 1;
    do{
        tmp *= x;
        } while (--x > 0);

    return tmp;
    // implement me
}