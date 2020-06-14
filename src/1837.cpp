/*  1837. Число Исенбаева
 *
 *    Ограничение времени: 0.5 секунды
 *    Ограничение памяти: 64 МБ
 *
 *  Владислав Исенбаев — двукратный чемпион Урала по программированию,
 *  вице-чемпион TopCoder Open 2009, абсолютный чемпион ACM ICPC 2009. За то
 *  время, которое вы потратите на чтение этого условия, Владислав уже решил бы
 *  одну задачу. А может, и две…
 *
 *  Поскольку Владислав Исенбаев — выпускник СУНЦ УрГУ, неудивительно, что
 *  многие из бывших и действующих олимпиадников УрГУ знакомы с ним уже много
 *  лет. Некоторые из них с гордостью заявляют, что играли с Владиславом в
 *  одной команде. Или играли в команде с бывшими однокомандниками Владислава…
 *
 *  Определим число Исенбаева следующим образом. У самого Владислава это число
 *  равняется нулю. У тех, кто играл с ним в одной команде, оно равняется
 *  единице. У тех, кто играл вместе с однокомандниками Владислава, но не играл
 *  с ним самим, это число равняется двум, и так далее. Помогите
 *  автоматизировать процесс вычисления чисел Исенбаева, чтобы каждый
 *  олимпиадник в УрГУ мог знать, насколько близок он к чемпиону ACM ICPC.
 *
 *  Исходные данные
 *  В первой строке записано целое число n — количество команд (1 ≤ n ≤ 100). В
 *  каждой из следующих n строк записаны составы этих команд в виде фамилий
 *  трёх участников. Фамилия каждого участника — непустая строка, состоящая из
 *  английских букв, длиной не более 20 символов. Первая буква фамилии —
 *  заглавная, все остальные — строчные. Фамилия Владислава — «Isenbaev».
 *
 *  Результат
 *  Для каждого участника, представленного во входных данных, выведите в
 *  отдельной строке через пробел его фамилию и число Исенбаева. Если это число
 *  не определено, выведите вместо него «undefined». Участники должны быть
 *  упорядочены по фамилии в лексикографическом порядке.
 *
 *  Примеры
 *    исходные данные                       |   результат
 *  ----------------------------------------+-----------------------------
 *    7                                     |   Ayzenshteyn 2
 *    Isenbaev Oparin Toropov               |   Burmistrov 3
 *    Ayzenshteyn Oparin Samsonov           |   Chevdar 3
 *    Ayzenshteyn Chevdar Samsonov          |   Cormen undefined
 *    Fominykh Isenbaev Oparin              |   Dublennykh 2
 *    Dublennykh Fominykh Ivankov           |   Fominykh 1
 *    Burmistrov Dublennykh Kurpilyanskiy   |   Isenbaev 0
 *    Cormen Leiserson Rivest               |   Ivankov 2
 *                                          |   Kurpilyanskiy 3
 *                                          |   Leiserson undefined
 *                                          |   Oparin 1
 *                                          |   Rivest undefined
 *                                          |   Samsonov 2
 *                                          |   Toropov 1
 *
 */

#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std::string_literals;

using pair_gamers_t = std::map<std::string, std::vector<std::string>>;
using num_isenb_t = std::map<std::string, int>;

void add_pair(pair_gamers_t& pairs, const std::string& val_1, const std::string& val_2) {
  auto it = pairs.find(val_1);
  if (it != pairs.end())
    it->second.push_back(val_2);
  else
    pairs[val_1] = std::vector<std::string>{{val_2}};
}

void print(const num_isenb_t& num_isenb) {
  std::vector<std::pair<std::string, int>> vec(num_isenb.begin(), num_isenb.end());
  std::sort(vec.begin(), vec.end());

  for (const auto& p: vec) {
    if (p.second != -1)
      std::cout << p.first << " " << p.second << std::endl;
    else
      std::cout << p.first << " " << "undefined"s << std::endl;
  }
}

void calc(const pair_gamers_t& pairs, pair_gamers_t::iterator start, num_isenb_t& dist) {
  dist[start->first] = 0;

  std::queue<std::string> queue;
  queue.push(start->first);

  while (!queue.empty()) {
    std::string u = std::move(queue.front());
    queue.pop();

    for (const std::string& w: pairs.at(u)) {
      if (dist[w] == -1) {
        dist[w] = dist[u] + 1;
        queue.push(w);
      }
    }
  }
}

int main() {
  std::size_t num_teams;
  std::cin >> num_teams;

  if (!num_teams)
    return 0;

  pair_gamers_t pairs;
  std::string gamer1, gamer2, gamer3;
  for (std::size_t i = 0; i != num_teams; ++i) {
    std::cin >> gamer1 >> gamer2 >> gamer3;

    /* gamer1 */
    add_pair(pairs, gamer1, gamer2);
    add_pair(pairs, gamer1, gamer3);

    /* gamer2 */
    add_pair(pairs, gamer2, gamer1);
    add_pair(pairs, gamer2, gamer3);

    /* gamer3 */
    add_pair(pairs, gamer3, gamer1);
    add_pair(pairs, gamer3, gamer2);
  }

  num_isenb_t num_isenbaev;
  for (const auto& p: pairs) {
    num_isenbaev[p.first] = -1;
  }

  auto it_isenb = pairs.find("Isenbaev"s);
  if (it_isenb == pairs.end()) {
    print(num_isenbaev);
  }
  else {
    /* Calc Isenbaev number */
    calc(pairs, it_isenb, num_isenbaev);
    print(num_isenbaev);
  }
}
