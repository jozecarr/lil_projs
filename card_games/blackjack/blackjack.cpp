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

void initGame(stack<int>& deck, vector<int>& vDeck, vector<vector<int>>& players, int playerCount)
{
  fillDeck(deck, vDeck);
  players = {};
  for(int i = 0; i < playerCount; i++){
    players.push_back({});
    deal(deck, players[i]);
    deal(deck, players[i]);
  }
}

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

void printVals(vector<vector<int>> players) {
  for(auto I : players) {
    for(int II : I) {
      printf("%d\n", II);
    }
    printf("bestVal:%d\n\n", bestVal(I));
  }
}

bool prob(double probability) {
    static std::mt19937 gen(std::random_device{}());
    return std::uniform_real_distribution<>(0.0, 1.0)(gen) < probability;
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

int winnerIndex(vector<vector<int>>& players) {
  int currIndx = -1;
  int currBest = -1;
  for(int i = 0; i < players.size(); i++) {
    int val = bestVal(players[i]);
    if(val <= 21 && val > currBest) { currBest = val; currIndx = i; }
  } return currIndx;
}

int main() {
  int playerCount = 2;
  vector<int> vDeck; // vector deck used to store full deck without changes
  stack<int> deck; // actual play deck
  vector<vector<int>> players;
  initGame(deck, vDeck, players, playerCount);

  vector<int> wins = {0,0};
  int draws = 0;

  for(int i = 0; i < 100000; i++) {
    initGame(deck, vDeck, players, playerCount);
    while( (BadBot(players[0]) || GoodBot(players[1], vDeck)) ) {
      if( BadBot(players[0]) ) {
       deal(deck, players[0]);
      }

      if( GoodBot(players[1], vDeck) ) {
        deal(deck, players[1]);
      }
    }
    if(winnerIndex(players) != -1) { wins[winnerIndex(players)]++; } 
    else draws++;
  }

  printf("Bad bot win count: %d\nGood bot win count: %d\nDraws: %d\n", wins[0], wins[1], draws);
}
