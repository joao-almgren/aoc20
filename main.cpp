#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <bitset>
using namespace std;

using ll = int64_t;
using ul = uint64_t;

string trim(const string& token)
{
	string word;
	stringstream stream(token);
	stream >> word;
	return word;
}

vector<string> split(const string& line, char delimiter, bool dotrim = true)
{
	vector<string> result;
	stringstream stream(line);
	string token;
	while (getline(stream, token, delimiter))
	{
		if (dotrim)
			result.push_back(trim(token));
		else
			result.push_back(token);
	}
	return result;
}

template<typename C, typename T>
bool contains(const C& container, const T& value)
{
	return (end(container) != find(begin(container), end(container), value));
}

template<typename T, typename U>
bool contains(const map<T, U>& container, const T& value)
{
	return (container.find(value) != container.end());
}

template<typename T, typename U>
vector<T> keys(const map<T, U>& container)
{
	vector<T> keys;
	for (const auto& pair : container)
		keys.push_back(pair.first);
	return keys;
}

template<typename T, typename U>
vector<T> values(const map<T, U>& container)
{
	vector<U> values;
	for (const auto& pair : container)
		values.push_back(pair.second);
	return values;
}

template<typename T>
pair<T, T> minmax_vec(const vector<T>& vec, size_t i, size_t j)
{
	T min = vec[i];
	T max = vec[i];
	for (size_t x = i; x <= j; x++)
	{
		if (vec[x] < min)
			min = vec[x];
		if (vec[x] > max)
			max = vec[x];
	}
	pair<T, T> p(min, max);
	return p;
}

void day1(string fname)
{
	ifstream in(fname);

	vector<ll> input;

	string line;
	while (getline(in, line))
	{
		ll i = stoll(line);
		input.push_back(i);
	}

	for (size_t i = 0; i < input.size(); i++)
	{
		for (size_t j = i + 1; j < input.size(); j++)
		{
			if (input[i] + input[j] == 2020)
			{
				cout << "Part 1: " << input[i] * input[j] << endl;
			}

			for (size_t k = j + 1; k < input.size(); k++)
			{
				if (input[i] + input[j] + input[k] == 2020)
				{
					cout << "Part 2: " << input[i] * input[j] * input[k] << endl;
				}
			}
		}
	}
}

void day2(string fname)
{
	ifstream in(fname);

	int p1 = 0, p2 = 0;

	string line;
	while (getline(in, line))
	{
		stringstream ss(line);

		char tmp, c;
		int min, max;
		string pw;

		ss >> min;
		ss >> tmp;
		ss >> max;
		ss >> c;
		ss >> tmp;
		ss >> pw;

		int count = 0;
		for (int i = min; i <= max; i++)
		{
			if (pw[i - 1] == c)
				count++;
		}
		if (count == 1)
			p1++;

		if (pw[min - 1] == c && pw[max - 1] != c
			|| pw[min - 1] != c && pw[max - 1] == c)
		{
			p2++;
		}
	}

	cout << "Part 1: " << p1 << endl;
	cout << "Part 2: " << p2 << endl;
}

ul treecount(int stepx, int stepy, int width, int height, vector<bool> data)
{
	ul count = 0;
	int y = 0, x = 0;

	while (y < height - stepy)
	{
		y += stepy;
		x += stepx;

		if (data[y * width + (x % width)])
			count++;
	}

	return count;
}

void day3(string fname)
{
	ifstream in(fname);

	vector<bool> data;
	int width = 0, height = 0;

	string line;
	while (getline(in, line))
	{
		width = line.size();
		height++;

		for (char c : line)
		{
			data.push_back(c == '#');
		}
	}

	ul trees[5] =
	{
		treecount(1, 1, width, height, data),
		treecount(3, 1, width, height, data),
		treecount(5, 1, width, height, data),
		treecount(7, 1, width, height, data),
		treecount(1, 2, width, height, data),
	};

	ul total = trees[0] * trees[1] * trees[2] * trees[3] * trees[4];

	cout << "Part 1: " << trees[1] << endl;
	cout << "Part 2: " << total << endl;
}

void day4(string fname)
{
	ifstream in(fname);

	const vector<string> flags{
		"byr",
		"iyr",
		"eyr",
		"hgt",
		"hcl",
		"ecl",
		"pid"
	};
	vector<string> pass1, pass2;
	ul count1 = 0, count2 = 0;

	string line;
	while (getline(in, line))
	{
		if (line.empty())
		{
			if (pass1.size() == flags.size())
				count1++;

			pass1.clear();

			if (pass2.size() == flags.size())
				count2++;

			pass2.clear();
		}
		else
		{
			vector<string> words = split(line, ' ');

			for (string s : words)
			{
				vector<string> pair = split(s, ':');

				if (contains(flags, pair[0]))
					pass1.push_back(pair[0]);

				bool valid = false;
				if (pair[0] == "byr")
				{
					ll byr = stoll(pair[1]);
					if (byr >= 1920 && byr <= 2002)
						valid = true;
				}
				else if (pair[0] == "iyr")
				{
					ll iyr = stoll(pair[1]);
					if (iyr >= 2010 && iyr <= 2020)
						valid = true;
				}
				else if (pair[0] == "eyr")
				{
					ll eyr = stoll(pair[1]);
					if (eyr >= 2020 && eyr <= 2030)
						valid = true;
				}
				else if (pair[0] == "hgt")
				{
					ll hgt = stoll(pair[1]);
					if (pair[1][pair[1].size() - 2] == 'c')
					{
						if (hgt >= 150 && hgt <= 193)
							valid = true;
					}
					else if (pair[1][pair[1].size() - 2] == 'i')
					{
						if (hgt >= 59 && hgt <= 76)
							valid = true;
					}
				}
				else if (pair[0] == "hcl")
				{
					if (pair[1][0] == '#' && pair[1].size() == 7)
					{
						const vector<char> alp = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
						bool found = true;
						for (size_t i = 1; i < pair[1].size() - 1; i++)
						{
							char t = pair[1][i];
							if (!contains(alp, t))
								found = false;
						}
						if (found)
							valid = true;
					}
				}
				else if (pair[0] == "ecl")
				{
					const vector<string> col = { "amb", "blu" ,"brn","gry", "grn", "hzl", "oth" };
					if (contains(col, pair[1]))
						valid = true;
				}
				else if (pair[0] == "pid")
				{
					if (pair[1].size() == 9)
					{
						const vector<char> num = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
						bool found = true;
						for (char t : pair[1])
							if (!contains(num, t))
								found = false;
						if (found)
							valid = true;
					}
				}

				if (valid)
					pass2.push_back(s);
			}
		}
	}

	cout << "Part 1: " << count1 << endl;
	cout << "Part 2: " << count2 << endl;
}

void day5(string fname)
{
	ifstream in(fname);

	int max = 0;
	vector<int> all;

	string line;
	while (getline(in, line))
	{
		int rowmin = 0;
		int rowmax = 127;
		int colmin = 0;
		int colmax = 7;

		for (int i = 0; i < 7; i++)
		{
			char c = line[i];
			int size = rowmax - rowmin + 1;
			int half = size / 2;
			if (c == 'F')
			{
				rowmax = rowmax - half;
			}
			else if (c == 'B')
			{
				rowmin = rowmin + half;
			}
		}

		for (int i = 7; i < 10; i++)
		{
			char c = line[i];
			int size = colmax - colmin + 1;
			int half = size / 2;
			if (c == 'L')
			{
				colmax = colmax - half;
			}
			else if (c == 'R')
			{
				colmin = colmin + half;
			}
		}

		int seat = rowmin * 8 + colmin;
		all.push_back(seat);

		if (seat > max)
			max = seat;
	}

	cout << "Part 1: " << max << endl;

	sort(all.begin(), all.end());

	int prev = all[0] - 1;
	for (int i : all)
		if (i != prev + 1)
		{
			cout << "Part 2: " << prev + 1 << endl;
			break;
		}
		else
		{
			prev = i;
		}
}

void day5_alt(string fname)
{
	ifstream in(fname);

	int max = 0;
	vector<int> all;

	string line;
	while (getline(in, line))
	{
		int n = (int)pow(2, 9);
		int id = 0;

		for (char c : line)
		{
			if (c == 'B' || c == 'R')
			{
				id += 1 * n;
			}

			n /= 2;
		}

		all.push_back(id);

		if (id > max)
			max = id;
	}

	cout << "Part 1: " << max << endl;

	sort(all.begin(), all.end());

	int prev = all[0] - 1;
	for (int i : all)
	{
		if (i != prev + 1)
		{
			cout << "Part 2: " << prev + 1 << endl;
			break;
		}
		else
		{
			prev = i;
		}
	}
}

void day6(string fname)
{
	ifstream in(fname);

	ll part1 = 0, part2 = 0, count = 0;
	map<char, int> answer;

	string line;
	while (getline(in, line))
	{
		if (line.empty())
		{
			ul num = 0;
			for (const auto& pair : answer)
			{
				part1++;

				if (pair.second == count)
					num++;
			}
			part2 += num;

			count = 0;
			answer.clear();
		}
		else
		{
			count++;

			for (char c : line)
			{
				if (contains(answer, c))
					answer[c]++;
				else
					answer[c] = 1;
			}
		}
	}

	cout << "Part 1: " << part1 << endl;
	cout << "Part 2: " << part2 << endl;
}

struct Bag
{
	string color;
	vector<pair<int, Bag>> bags;
};

bool baghasgold(const vector<Bag>& bags, const string& color)
{
	if (color == "shinygold")
		return true;

	for (const auto& b : bags)
	{
		if (b.color == color)
		{
			for (const auto& p : b.bags)
			{
				if (baghasgold(bags, p.second.color))
					return true;
			}

			return false;
		}
	}

	return false;
}

ll countbags(const vector<Bag>& bags, const string& color)
{
	for (const auto& b : bags)
	{
		if (b.color == color)
		{
			ll count = 1;

			for (const auto& p : b.bags)
			{
				count += p.first * countbags(bags, p.second.color);
			}

			return count;
		}
	}

	return 0;
}

void day7(string fname)
{
	ifstream in(fname);

	ll part1 = 0, part2 = 0;
	vector<Bag> bags;

	string line;
	while (getline(in, line))
	{
		stringstream ss(line);

		string col1, col2, tmp;
		int num;
		ss >> col1;
		ss >> col2;
		ss >> tmp;
		ss >> tmp;

		Bag b;
		b.color = col1.append(col2.c_str());

		while (true)
		{
			ss >> tmp;
			if (tmp == "no")
				break;

			stringstream numss(tmp);
			numss >> num;

			ss >> col1;
			ss >> col2;

			Bag c;
			c.color = col1.append(col2.c_str());
			pair<int, Bag> p;
			p.first = num;
			p.second = c;
			b.bags.push_back(p);

			ss >> tmp;
			if (tmp[tmp.size() - 1] == '.')
				break;
		}

		bags.push_back(b);
	}

	for (const auto& b : bags)
	{
		if (b.color != "shinygold" && baghasgold(bags, b.color))
			part1++;
	}

	part2 = countbags(bags, "shinygold") - 1;

	cout << "Part 1: " << part1 << endl;
	cout << "Part 2: " << part2 << endl;
}

struct Code
{
	string op;
	int parm;
};

int run(const vector<Code>& code, bool& terminated)
{
	int acc = 0;
	size_t ip = 0;
	vector<int> visited;

	while (true)
	{
		if (ip >= code.size())
		{
			terminated = true;
			break;
		}

		if (contains(visited, ip))
		{
			terminated = false;
			break;
		}

		visited.push_back(ip);

		if (code[ip].op == "nop")
		{
		}
		else if (code[ip].op == "acc")
		{
			acc += code[ip].parm;
		}
		else if (code[ip].op == "jmp")
		{
			ip += code[ip].parm;
			continue;
		}

		ip++;
	}

	return acc;
}

void day8(string fname)
{
	ifstream in(fname);

	ll part1 = 0, part2 = 0;
	vector<Code> code;
	bool terminated;
	int prevtest = -1;
	Code prevcode;

	string line;
	while (getline(in, line))
	{
		stringstream ss(line);

		Code c;
		ss >> c.op;
		ss >> c.parm;
		code.push_back(c);
	}

	part1 = run(code, terminated);

	while (true)
	{
		int acc = run(code, terminated);

		if (terminated)
		{
			part2 = acc;
			break;
		}

		if (prevtest >= 0)
		{
			code[prevtest] = prevcode;
		}

		for (size_t i = prevtest + 1; i < code.size(); i++)
		{
			if (code[i].op == "nop")
			{
				prevtest = i;
				prevcode = code[i];
				code[i].op = "jmp";
				break;
			}
			else if (code[i].op == "jmp")
			{
				prevtest = i;
				prevcode = code[i];
				code[i].op = "nop";
				break;
			}

		}
	}

	cout << "Part 1: " << part1 << endl;
	cout << "Part 2: " << part2 << endl;
}

void day9(string fname, const size_t preamble = 25)
{
	ifstream in(fname);
	ofstream out("out.txt");

	ul part1 = 0, part2 = 0;
	vector<ul> amb;

	string line;
	while (getline(in, line))
	{
		stringstream ss(line);
		ul num;
		ss >> num;
		amb.push_back(num);
	}

	bool found = false;
	for (size_t n = preamble; n < amb.size(); n++)
	{
		found = false;
		for (size_t i = n - preamble; i < n; i++)
		{
			for (size_t j = i + 1; j < n; j++)
			{
				if (amb[i] + amb[j] == amb[n])
				{
					found = true;
					break;
				}
			}
			if (found)
				break;
		}
		if (!found)
		{
			part1 = amb[n];
			break;
		}
	}

	ul sum = 0;

	found = false;
	for (size_t i = 0; i < amb.size(); i++)
	{
		sum = amb[i];

		for (size_t j = i + 1; j < amb.size(); j++)
		{
			sum += amb[j];

			if (sum > part1)
			{
				break;
			}
			else if (sum == part1)
			{
				auto p = minmax_vec(amb, i, j);
				part2 = p.first + p.second;
				found = true;
				break;
			}
		}
		if (found)
			break;
	}

	cout << "Part 1: " << part1 << endl;
	cout << "Part 2: " << part2 << endl;
}

void day10(string fname)
{
	ifstream in(fname);

	ll part1 = 0, part2 = 0;

	vector<int> jolt;

	string line;
	while (getline(in, line))
	{
		stringstream ss(line);
		int j;
		ss >> j;
		jolt.push_back(j);
	}
	jolt.push_back(0);
	sort(jolt.begin(), jolt.end());
	jolt.push_back(jolt[jolt.size() - 1] + 3);

	ll c1 = 0;
	ll c3 = 0;

	for (size_t i = 1; i < jolt.size(); i++)
	{
		if (jolt[i] - jolt[i - 1] == 1)
			c1++;
		else
			c3++;
	}
	part1 = c1 * c3;

	vector<ul> ways(jolt.size());
	ways[0] = 1;

	for (size_t i = 0; i < jolt.size(); i++)
		for (size_t j = i + 1; j < jolt.size(); j++)
		{
			if (jolt[j] - jolt[i] > 3)
				break;

			ways[j] += ways[i];
		}

	part2 = ways[ways.size() - 1];

	cout << "Part 1: " << part1 << endl;
	cout << "Part 2: " << part2 << endl;
}

int ray(vector<int>& vec, int width, int height, int x, int y, int dx, int dy)
{
	int y1 = y;
	int x1 = x;

	while (true)
	{
		y1 += dy;
		x1 += dx;

		if (x1 >= width || x1 < 0 || y1 >= height || y1 < 0)
			return 0;

		int i = x1 + y1 * width;
		int s = vec[i];

		if (s != 0)
			return s;
	}
}

int occup2(vector<int>& vec, int width, int height, int x, int y)
{
	int dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
	int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

	int occ = 0;
	for (int i = 0; i < 8; i++)
	{
		int s = ray(vec, width, height, x, y, dx[i], dy[i]);
		if (s == 1)
		{
			occ++;
		}
	}
	return occ;
}

int occup1(vector<int>& vec, int width, int height, int x, int y)
{
	int occ = 0;
	for (int x1 = x - 1; x1 < x + 2; x1++)
		for (int y1 = y - 1; y1 < y + 2; y1++)
		{
			if (x1 == x && y1 == y)
				continue;
			if (x1 < 0 || y1 < 0)
				continue;
			if (x1 >= width || y1 >= height)
				continue;
			int val = vec[x1 + y1 * width];
			if (val == 1)
				occ++;
		}
	return occ;
}

void day11a(string fname)
{
	ifstream in(fname);

	ll part1 = 0;

	vector<int> seat;
	int width = 0;

	string line;
	while (getline(in, line))
	{
		width = line.size();

		for (char c : line)
		{
			if (c == '.')
				seat.push_back(0);
			else if (c == '#')
				seat.push_back(1);
			if (c == 'L')
				seat.push_back(2);
		}
	}

	int height = seat.size() / width;

	bool change = true;
	while (change)
	{
		vector<int> tmp;
		tmp.resize(width * height);

		change = false;
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				int i = x + y * width;
				int s = seat[i];
				tmp[i] = s;
				if (s == 0)
					continue;
				int occ = occup1(seat, width, height, x, y);
				if (s == 2 && occ == 0)
				{
					tmp[i] = 1;
					change = true;
				}
				else if (s == 1 && occ >= 4)
				{
					tmp[i] = 2;
					change = true;
				}
			}
		}

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				int i = x + y * width;
				int s = tmp[i];
				seat[i] = s;
			}
		}
	}

	int occo = 0;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int i = x + y * width;
			int s = seat[i];
			if (s == 1)
				occo++;
		}
	}
	part1 = occo;

	cout << "Part 1: " << part1 << endl;
}

void day11b(string fname)
{
	ifstream in(fname);

	ll part2 = 0;

	vector<int> seat;
	int width = 0;

	string line;
	while (getline(in, line))
	{
		width = line.size();

		for (char c : line)
		{
			if (c == '.')
				seat.push_back(0);
			else if (c == '#')
				seat.push_back(1);
			if (c == 'L')
				seat.push_back(2);
		}
	}

	int height = seat.size() / width;

	bool change = true;
	while (change)
	{
		vector<int> tmp;
		tmp.resize(width * height);

		change = false;
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				int i = x + y * width;
				int s = seat[i];
				tmp[i] = s;
				if (s == 0)
					continue;
				int occ = occup2(seat, width, height, x, y);
				if (s == 2 && occ == 0)
				{
					tmp[i] = 1;
					change = true;
				}
				else if (s == 1 && occ >= 5)
				{
					tmp[i] = 2;
					change = true;
				}
			}
		}

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				int i = x + y * width;
				int s = tmp[i];
				seat[i] = s;
			}
		}
	}

	int occo = 0;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int i = x + y * width;
			int s = seat[i];
			if (s == 1)
				occo++;
		}
	}
	part2 = occo;

	cout << "Part 2: " << part2 << endl;
}

void turn(int& x, int& y, int degree)
{
	const int sign = (degree < 0) ? -1 : 1;
	degree = abs(degree);
	while (degree > 0)
	{
		if (sign > 0)
		{
			int tmp = y;
			y = -x;
			x = tmp;
		}
		else
		{
			int tmp = x;
			x = -y;
			y = tmp;
		}
		degree -= 90;
	}
}

void day12(string fname)
{
	ifstream in(fname);

	ll part1 = 0, part2 = 0;

	struct Action
	{
		char cmd;
		int val;
	};
	vector<Action> steps;

	string line;
	while (getline(in, line))
	{
		stringstream ss(line);

		Action action;
		ss >> action.cmd >> action.val;
		steps.push_back(action);
	}

	int x = 0;
	int y = 0;
	int dx = 1;
	int dy = 0;

	for (Action& a : steps)
	{
		if (a.cmd == 'F')
		{
			x += dx * a.val;
			y += dy * a.val;
		}
		else if (a.cmd == 'N')
		{
			y += a.val;
		}
		else if (a.cmd == 'S')
		{
			y -= a.val;
		}
		else if (a.cmd == 'E')
		{
			x += a.val;
		}
		else if (a.cmd == 'W')
		{
			x -= a.val;
		}
		else if (a.cmd == 'L')
		{
			turn(dx, dy, -a.val);
		}
		else if (a.cmd == 'R')
		{
			turn(dx, dy, a.val);
		}
	}

	part1 = (ll)abs(x) + abs(y);

	x = 0;
	y = 0;
	dx = 10;
	dy = 1;

	for (Action& a : steps)
	{
		if (a.cmd == 'F')
		{
			x += dx * a.val;
			y += dy * a.val;
		}
		else if (a.cmd == 'N')
		{
			dy += a.val;
		}
		else if (a.cmd == 'S')
		{
			dy -= a.val;
		}
		else if (a.cmd == 'E')
		{
			dx += a.val;
		}
		else if (a.cmd == 'W')
		{
			dx -= a.val;
		}
		else if (a.cmd == 'L')
		{
			turn(dx, dy, -a.val);
		}
		else if (a.cmd == 'R')
		{
			turn(dx, dy, a.val);
		}
	}

	part2 = (ll)abs(x) + abs(y);

	cout << "Part 1: " << part1 << endl;
	cout << "Part 2: " << part2 << endl;
}

void day13()
{
	//ll time = 939;
	//vector<ll> bus = { 7, 13, 59, 31, 19 };
	//vector<ll> offset = { 0, 1, 4, 6, 7 };

	ll time = 1000655;
	vector<ll> bus = { 17, 37, 571, 13, 23, 29, 401, 41, 19 };
	vector<ll> offset = { 0, 11, 17, 35, 40, 46, 48, 58, 67 };

	//for (ll b : bus)
	//{
	//	for (ll i = 0; ; i++)
	//	{
	//		if (i * b > time)
	//		{
	//			cout << b << " " << i << endl;
	//			cout << i * b << endl;
	//			cout << (i * b) - time << endl;
	//			cout << b * ((i * b) - time) << endl;
	//			cout << endl;
	//			break;
	//		}
	//	}
	//}

	for (ll i = 0; ; i += bus[0])
	{
		bool found = true;
		for (size_t x = 1; x < bus.size(); x++)
		{
			ll b = bus[x];
			ll o = offset[x];
			ll t = i + o;

			if (t % b != 0)
			{
				found = false;
				break;
			}
		}

		if (found)
		{
			cout << i;
			break;
		}
	}
}

ul domask(string mask, ul val)
{
	string mem = bitset<36>(0).to_string();
	string y = bitset<36>(val).to_string();

	for (int i = 0; i < 36; i++)
	{
		if (mask[i] == 'X')
		{
			mem[i] = y[i];
		}
		else
		{
			mem[i] = mask[i];
		}
	}

	ul n = bitset<36>(mem).to_ullong();

	return n;
}

void makemask(map<ul, ul>& mem, ul val, const string& input, size_t index)
{
	if (index > 35)
	{
		ul n = bitset<36>(input).to_ullong();
		mem[n] = val;
		return;
	}

	if (input[index] == 'X')
	{
		string a = input;
		string b = input;
		a[index] = '0';
		b[index] = '1';
		makemask(mem, val, a, index + 1);
		makemask(mem, val, b, index + 1);
	}
	else
	{
		makemask(mem, val, input, index + 1);
	}
}

void writemask(string mask, map<ul, ul>& mem, ul ad, ul val)
{
	string x = bitset<36>(0).to_string();
	string y = bitset<36>(ad).to_string();

	for (int i = 0; i < 36; i++)
	{
		if (mask[i] == '0')
		{
			x[i] = y[i];
		}
		else if (mask[i] == '1')
		{
			x[i] = '1';
		}
		else if (mask[i] == 'X')
		{
			x[i] = 'X';
		}
	}

	makemask(mem, val, x, 0);
}

void day14(string fname)
{
	ifstream in(fname);

	ul part1 = 0, part2 = 0;

	map<ul, ul> mem;
	map<ul, ul> mem2;
	string mask;

	string line;
	while (getline(in, line))
	{
		stringstream ss(line);

		string cmd;
		ss >> cmd;

		if (cmd == "mem")
		{
			ul ad;
			ss >> ad;
			ul val;
			ss >> val;

			mem[ad] = domask(mask, val);
			writemask(mask, mem2, ad, val);
		}
		else
		{
			ss >> mask;
		}
	}

	for (auto& p : mem)
	{
		part1 += p.second;
	}

	for (auto& p : mem2)
	{
		part2 += p.second;
	}

	cout << "Part 1: " << part1 << endl;
	cout << "Part 2: " << part2 << endl;
}

void day15(string fname)
{
	ifstream in(fname);
	ofstream out("out.txt");

	ll part1 = 0, part2 = 0;

	string line;
	while (getline(in, line))
	{
		if (line.empty())
		{

		}
		else
		{
			cout << line << endl;

			stringstream ss(line);

			for (char c : line)
			{

			}

		}
	}

	cout << "Part 1: " << part1 << endl;
	cout << "Part 2: " << part2 << endl;
}

int main()
{
	cout << "start" << endl;

	day15("in15t.txt");
	//day15("in15.txt");

	cout << "stop" << endl;
	return 0;
}

/*
void day(string fname)
{
	ifstream in(fname);
	ofstream out("out.txt");

	ll part1 = 0, part2 = 0;

	string line;
	while (getline(in, line))
	{
		if (line.empty())
		{

		}
		else
		{
			cout << line << endl;

			stringstream ss(line);

			for (char c : line)
			{

			}

		}
	}

	cout << "Part 1: " << part1 << endl;
	cout << "Part 2: " << part2 << endl;
}
*/
