#include <iostream>
#include <vector>
#include <stack>
#include <iterator>
#include <random>
#include <algorithm>

using std::cout;
using std::vector;
using std::begin;
using std::end;
using std::stack;
using std::find;
using std::shuffle;

/*>----------------------------------------------------------------------------<*/

void fillDeck(stack<int>& deck, vector<int>& vDeck) {
  vDeck = {};
  deck = {};
  for(int i = 0; i < 52; i++) {
    int num = (i % 13 + 1);
    if (num >= 11) num = 10;
    vDeck.push_back(num);
  }
  shuffle(begin(vDeck), end(vDeck), std::mt19937{std::random_device{}()});
  for(int n : vDeck) {deck.push(n);}
}

void deal(stack<int>& deck, vector<int>& player) {
  if(deck.empty()) {cout << "ERROR: empty deck\n"; return;} 
  player.push_back(deck.top());
  deck.pop();
}

bool prob(double probability) {
    static std::mt19937 gen(std::random_device{}());
    return std::uniform_real_distribution<>(0.0, 1.0)(gen) < probability;
}
