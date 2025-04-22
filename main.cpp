void mv(const long long* src, long long* dst);

long long g_src;
long long g_dst;

int main() {
  mv(&g_src, &g_dst);
}
