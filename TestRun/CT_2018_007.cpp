//CT/2018/007

#include <algorithm>  // for std::find_if, std::random_shuffle, std::min_element, std::max_element, std::remove_copy_if
#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <functional>

class Card {
 public:
  Card(int value, char suit) : value(value), suit(suit) {}

  int getValue() const { return value; }
  char getSuit() const { return suit; }

  bool operator==(const Card &other) const {
    return value == other.value && suit == other.suit;
  }

  bool operator < (const Card &other) const {
    return value < other.value;
}


 private:
  int value;
  char suit;
};

int evaluateHand(const Card bestCardSoFar) {
  std::unordered_map<int, int> points = {{14, 4}, {11, 1}, {12, 2}, {13, 3}};
  int totalPoints = 0;
    int value = bestCardSoFar.getValue();
    if (points.count(value) > 0) {
      totalPoints += points[value];
    }
  return totalPoints;
}


bool playACard(std::vector<Card> &hand, Card firstCard, Card &bestCardSoFar,
               std::function<bool(Card)> suitTester, Card &randomCard) {
    // Find all cards of the same suit as the first card
    std::vector<Card> oneSuit;
    std::remove_copy_if(hand.begin(), hand.end(), std::back_inserter(oneSuit),
                        [&](const Card &c) { return !suitTester(c); });

    if (oneSuit.empty()) {
        // If the hand doesn't contain any cards of the same suit as the first card,
        // pick a random card from the hand
        int randomIndex = rand() % hand.size();
        Card card = hand[randomIndex];
        hand.erase(std::find(hand.begin(), hand.end(), card));
        if (card.getValue() > bestCardSoFar.getValue()) {
            bestCardSoFar = card;
            return true;
        }

        randomCard = card;
        return false;
    } else {
        // Find the lowest and highest cards of the same suit as the first card
        auto lowest = std::min_element(oneSuit.begin(), oneSuit.end(),
                                      [](const Card &c1, const Card &c2) {
                                          return c1.getValue() < c2.getValue();
                                      });
        auto highest = std::max_element(oneSuit.begin(), oneSuit.end(),
                                       [](const Card &c1, const Card &c2) {
                                           return c1.getValue() < c2.getValue();
                                       });

        if (bestCardSoFar.getValue() >= (*highest).getValue()) {
            // If the best card so far can't be beaten, put down the lowest card

            hand.erase(std::find(hand.begin(), hand.end(), *lowest));
            bestCardSoFar = *lowest;
            return true;
        } else {
            // Put down the highest card that can beat the best card so far
            hand.erase(std::find(hand.begin(), hand.end(), *highest));
            bestCardSoFar = *highest;
            return true;
        }
    }
}


int main() {
  std::vector<Card> pack;

  const char suits[] = {'C', 'D', 'H', 'S'};
  for (int value = 2; value <= 14; value++) {
    for (char suit : suits) {
      pack.emplace_back(Card(value, suit));
    }
  }

  std::random_shuffle(pack.begin(), pack.end());



   std::cout << "\n\n ---------------- Shuffled : ----------------\n\n";
  for (const Card& card : pack) {
    std::cout << card.getValue() << card.getSuit() << " ";
  }

  std::cout << "\n\n ---------------- Hand : ----------------\n\n";


  const int numberOfPlayers = 4;
  std::vector<std::vector<Card>> hand(numberOfPlayers);

  for (int i = 0; i < 52; i++) {
    hand[i % numberOfPlayers].push_back(pack[i]);
  }

  for (int player = 0; player < numberOfPlayers; player++) {
    std::cout << "Player " << player+1 << ": ";
    for (const Card& card : hand[player]) {
      std::cout << card.getValue() << card.getSuit() << " ";
    }
    std::cout << "\n";
 }

Card firstCard = Card(0,'N');
Card bestCardSoFar = Card(0,'N');
Card randomCard = Card(0,'N');

int i =0;
int winningPlayer = -1;
int winningValue = 0;
int earlywinner = -1;
int player1=0;
int player2=0;
int player3=0;
int player4=0;
int player1Points=0;
int player2Points=0;
int player3Points=0;
int player4Points=0;

while(i<13){
    std::cout << "\n...... Round " << i+1 << ": ......\n";
    //if the first round run nomaly
    if(i==0){
            for (int player = 0; player < numberOfPlayers; player++) {
                // define a suitTester function
                auto suitTester = [&](Card c){ return c.getSuit() == bestCardSoFar.getSuit();};
                char winningSuit = bestCardSoFar.getSuit();
                // play a card
                if(playACard(hand[player], bestCardSoFar, bestCardSoFar, suitTester, randomCard)){
                  std::cout << "\n Player " << player+1 << " played: " << bestCardSoFar.getValue() << bestCardSoFar.getSuit() << std::endl;

                   if(winningSuit == bestCardSoFar.getSuit()){
                    if(winningValue < bestCardSoFar.getValue()){
                        winningValue = bestCardSoFar.getValue();
                        winningPlayer = player;

                    }}

                    if (winningPlayer == 0){
                        player1Points = player1Points + evaluateHand(bestCardSoFar);

                    }else if (winningPlayer == 1){
                        player2Points = player2Points + evaluateHand(bestCardSoFar);

                    }else if (winningPlayer == 2){
                        player3Points = player3Points + evaluateHand(bestCardSoFar);

                    }else{
                       player4Points = player4Points + evaluateHand(bestCardSoFar);
                    }


                }else{
                    std::cout << "\n Player " << player+1 << " played: " << randomCard.getValue() << randomCard.getSuit() << std::endl;

                }
          }
    }else{
        //to play card first, earlyer round winner
        int counting=0;
        while(counting < 4){
            int player = earlywinner ;
                // define a suitTester function
                auto suitTester = [&](Card c){ return c.getSuit() == bestCardSoFar.getSuit();};
                char winningSuit = bestCardSoFar.getSuit();
                // play a card
                if(playACard(hand[player], bestCardSoFar, bestCardSoFar, suitTester, randomCard)){
                  std::cout << "\n Player " << player+1 << " played: " << bestCardSoFar.getValue() << bestCardSoFar.getSuit() << std::endl;

                   if(winningSuit == bestCardSoFar.getSuit()){
                    if(winningValue < bestCardSoFar.getValue()){
                        winningValue = bestCardSoFar.getValue();
                        winningPlayer = player;

                    }}

                    if (winningPlayer == 0){
                        player1Points = player1Points + evaluateHand(bestCardSoFar);

                    }else if (winningPlayer == 1){
                        player2Points = player2Points + evaluateHand(bestCardSoFar);

                    }else if (winningPlayer == 2){
                        player3Points = player3Points + evaluateHand(bestCardSoFar);

                    }else{
                       player4Points = player4Points + evaluateHand(bestCardSoFar);
                    }

                }else{
                    std::cout << "\n Player " << player+1 << " played: " << randomCard.getValue() << randomCard.getSuit() << std::endl;

                }
                earlywinner++;
                counting++;
                if (earlywinner == 4){
                        earlywinner =0;
                }
          }
        }

    // Print out the winning player Of the round
    std::cout << "\n The winner of this round is Player " << winningPlayer+1 << std::endl;
    if (winningPlayer == 0){
            player1++;

    }else if (winningPlayer == 1){
            player2++;

    }else if (winningPlayer == 2){
            player3++;

    }else{
        player4++;
    }

  i++;
  earlywinner = winningPlayer;
  winningValue = 0;
  winningPlayer = -1;

}
    // Print out the player's points
    std::cout << "\n\n  Player 1 points : " <<  player1Points << "\n\n  Player 2 points : " <<  player2Points <<
    "\n\n  Player 3 points : " <<  player3Points << "\n\n  Player 4 points : " <<  player4Points  <<std::endl ;

    int GroupNumber1 = player1 + player3;
    int GroupNumber2 = player2 + player4;

    // Print out the winning player
    std::vector<int> playerScores = {GroupNumber1, GroupNumber2};
    int winner = std::distance(playerScores.begin(),std::max_element(playerScores.begin(),playerScores.end()));
    if (winner==0){
        std::cout << "\n\n -------- The winner of the Game : Group Number 1 : Player 1 and 3 ( " << GroupNumber1 <<" Total Tricks have won )  --------\n\n\n" <<std::endl ;
    }else{
        std::cout << "\n\n -------- The winner of the Game : Group Number 2 : Player 2 and 4 ( " << GroupNumber2 <<" Total Tricks have won )  --------\n\n\n" <<std::endl ;
    }

  return 0;
}
