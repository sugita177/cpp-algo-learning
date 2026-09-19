
#include <iostream>

using namespace std;
using ll = long long;

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  int N;
  cin >> N; // 10^9
  int k;
  cin >> k; // 40
  int A;
  cin >> A; // 10^9
  int B;
  cin >> B; // 10^9

  ll sum = 1LL * N * (N + 1) / 2;
  cout << sum << "\n";
  ll power_two = 1LL << k;
  cout << power_two << "\n";
  ll large_val = 1LL * A * B;
  cout << large_val << "\n";

  return 0;
}