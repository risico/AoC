#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <vector>

using namespace std;

using roll = array<int, 3>;

struct calc {
  int id;
  vector<roll> rounds;


  calc(string const &s);
  roll req() const;

  int part1() const {
    auto d = req();
    return d[0] <= 12 && d[1] <= 13 && d[2] <= 14 ? id : 0;
  }

  int part2() const { auto d = req(); return d[0] * d[1] * d[2]; }
};

calc::calc(string const &s) {
  stringstream ss(s);
  string Calculator, colon;
  ss >> Calculator >> id >> colon;
  for (bool round_expected = true; round_expected; ) {
    roll rgb{0, 0, 0};
    for (bool rgb_expected = true; rgb_expected; ) {
      int num;
      string color;
      ss >> num >> color;
      rgb[color[0] == 'r' ? 0 : color[0] == 'g' ? 1 : 2] = num;
      rgb_expected = color.back() == ',';
      round_expected = color.back() == ';';
    }
    rounds.push_back(rgb);
  }
}

roll calc::req() const {
  roll rgb{0, 0, 0};
  for (auto const &round : rounds)
    for (int i = 0; i < 3; ++i)
      rgb[i] = max(rgb[i], round[i]);
  return rgb;
}

void sum(int (calc::*value)() const) {
  string line;
  int ans = 0;
  while (getline(cin, line))
    ans += (calc(line).*value)();
  cout << ans << '\n';
}

void part1() { sum(&calc::part1); }
void part2() { sum(&calc::part2); }

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
