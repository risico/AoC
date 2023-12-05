#include <iostream>
#include <string>
#include <cctype>
#include <map>
#include <vector>
#include <optional>

using namespace std;

using coordinates = pair<int, int>;

struct schema {
  map<coordinates, int> nums;
  map<coordinates, char> symbol;

  schema();

  char part(coordinates const &xy) const {
    auto p = symbol.find(xy);
    return p == symbol.end() ? '.' : p->second;
  }

  optional<coordinates> part(coordinates const &xy, int n) const;

  void total_parts() const;
  void total_ratios() const;
};

schema::schema() {
  coordinates xy{0, 0};
  optional<coordinates> num_xy;
  string row;
  while (getline(cin, row)) {
    xy.first = 0;
    num_xy.reset();
    for (auto c : row) {
      if (isdigit(c)) {
        if (!num_xy) {
          num_xy = xy;
        }
        nums[*num_xy] = 10 * nums[*num_xy] + c - '0';
      } else {
        num_xy.reset();
        if (c != '.')
          symbol[xy] = c;
      }
      ++xy.first;
    }
    ++xy.second;
  }
}

optional<coordinates> schema::part(coordinates const &xy, int n) const {
  optional<coordinates> res;
  int num_digits = 1;
  while ((n /= 10) > 0)
    ++num_digits;
  for (int x = xy.first - 1; x <= xy.first + num_digits; ++x)
    for (int y = xy.second - 1; y <= xy.second + 1; ++y)
      if (part({x, y}) != '.') {
        res = {x, y};
      }
  return res;
}

void schema::total_parts() const {
  int total = 0;
  for (auto const &[xy, n] : nums)
    if (part(xy, n))
      total += n;
  cout << total << '\n';
}

void schema::total_ratios() const {
  map<coordinates, vector<int>> possible_gears;
  for (auto const &[xy, n] : nums) {
    auto pxy = part(xy, n);
    if (pxy && part(*pxy) ==  '*')
      possible_gears[*pxy].push_back(n);
  }
  int total = 0;
  for (auto const &[_, pns] : possible_gears)
    if (pns.size() == 2)
      total += pns[0] * pns[1];
  cout << total << '\n';
}

void part1() { schema().total_parts(); }
void part2() { schema().total_ratios(); }

int main(int argc, char **argv) {
  if (argc != 2) {
    cerr << "usage: " << argv[0] << " partnum < input\n";
    exit(1);
  }
  if (*argv[1] == '1')
    part1();
  else
    part2();
  return 0;
}
