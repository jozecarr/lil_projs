#include "../card_games.h"

void fillPiles(stack<int>& deck, vector<stack<int>>& piles) {
  piles = {};
  for(int i = 0; i < 13; i ++) {
    piles.push_back({});
    for(int j = 0; j < 4; j++) dealToStack(deck, piles[i]);
  }
}

bool arePilesEmpty(vector<stack<int>>& piles) {
  for(int i = 0; i < 13; i++) {
    if(!piles[i].empty()) return false;
  } return true;
}

bool clockSolitaire() {
  stack<int> deck;
  fillDeck(deck);
  vector<stack<int>> piles = {};
  fillPiles(deck, piles);

  int kingCount = 0;
  int curr = take(piles[12]);
  if(curr == 13) kingCount++;

  while(!arePilesEmpty(piles) && kingCount != 4) {
    curr = take(piles[curr - 1]);
    if(curr == 13) kingCount++;
  }

  return arePilesEmpty(piles);
}

int main() {
  int gameCount = 100000;
  int wins = 0;

  for(int i = 0; i < gameCount; i++) { if(clockSolitaire()) wins++; }

  cout << (double) 100 * wins / gameCount << "% win rate\n";
}
