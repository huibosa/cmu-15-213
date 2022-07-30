double apod(double a[], long n) {
  long i;
  double x, y, z;
  double r = 1;
  for (i = 0; i < n - 2; i += 3) {
    x = a[i];
    y = a[i + 1];
    z = a[i + 2];
    r = r * x * y * z;
  }
  for (; i < n; i++) {
    r *= a[i];
  }
  return r;
}
