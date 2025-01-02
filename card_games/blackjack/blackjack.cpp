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

/*>----------------------------------------------------------------------------<*/

void createDeck(stack<int>& deck)

void deal(stack<int>& deck, vector<int>& player) {
  if(deck.empty()) {cout << "ERROR: empty deck\n"; return;} 
  player.push_back(deck.top());
  deck.pop();
}

void initGame(stack<int>& deck, vector<int>& player){}

int aceCount(vector<int>& player) {
  int out = 0;
  for(int c : player) { out += (c == 1 ? 1 : 0); }
  return out;
}

int bestVal(vector<int>& player) {
  int val = 0;
  for (int c : player) { val += (c == 1 ? 0 : c); }
  int ac = aceCount(player);
  while(val + ac <= 11 && ac > 0) {
    val += 10;
  }

  return val + ac;
}

bool prob(double probability) {
    static std::mt19937 gen(std::random_device{}());
    return std::uniform_real_distribution<>(0.0, 1.0)(gen) < probability;
}

int main() {
  vector<int> vDeck;
  stack<int> deck;
  for(int i = 0; i < 52; i++) {
    int num = (i % 13) + 1;
    if(num >= 11) num = 10;
    vDeck.push_back(num);
  }
  std::shuffle(begin(vDeck), end(vDeck), std::mt19937{std::random_device{}()});
  for(int n : vDeck) {deck.push(n);}
  

  int playerCount = 5;
  

  vector<vector<int>> players;
  for(int i = 0; i < playerCount; i++) {
    players.push_back({});
    deal(deck, players[i]);
    deal(deck, players[i]);
  }

  players.push_back({1, 1});
  players.push_back({1, 1, 1});
  players.push_back({1, 10});

  for(auto I : players) { for(int II : I) { printf("%d\n", II); } printf("bestVal:%d\n\n", bestVal(I)); }
}

bool BadBot(vector<int>& hand) {
  return bestVal(hand) < 15 ? true : false;
}

bool GoodBot(vector<int>& hand, vector<int> vDeck) {
  int val = bestVal(hand);
  if(val >= 21) return false;

  for(int c : hand){
    auto it = find(vDeck.begin(), vDeck.end(), c);
    if (it != vDeck.end()) vDeck.erase(it);
  }

  int need = 21 - val;
  int k = 0;
  for(int c : vDeck) {
    if(c <= need) k++;
  }
  
  return prob((float)(k / vDeck.size()));
}
