#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <random>
#include <ctime>
#include <algorithm>
using namespace std;

const int cardsInDeck = 52;
int playerRoundTotal = 0;
int dealerRoundTotal = 0;
int playerTotalWins = 0;
int dealerTotalWins = 0;

class Card
{
    public:
  int cardValue;

  Card(int value)
  {
    cardValue = value;
  }
};

vector<Card> Cards =
{
    {1},{2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}, {13},
    {1},{2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}, {13},
    {1},{2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}, {13},
    {1},{2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}, {13}
};

stack<Card> Deck;

stack<Card> EmptyDeck(stack<Card> &deckOfCards)
{
    for(int removedCards = 0; removedCards < cardsInDeck; removedCards++)
    {
        if(!deckOfCards.empty())
        {
            deckOfCards.pop();
        }
    }
    return deckOfCards;
}

stack<Card> ShuffleDeck(vector<Card> deckOfCards)
{
    stack<Card> shuffledCards;
    std::random_device random_dev;
    std::mt19937       generator(random_dev());
    std::shuffle(deckOfCards.begin(), deckOfCards.end(), generator);
        for(Card card : deckOfCards)
        {
            shuffledCards.push(card);
        }
    return shuffledCards;
}

void DealPlayerCard(stack<Card> &deckLeft)
{
    Card dealtCard = deckLeft.top();
    deckLeft.pop();
    playerRoundTotal += dealtCard.cardValue;
}

bool HitPlayer(stack<Card> &deckLeft)
{
    if (playerRoundTotal < 16)
        {     
            DealPlayerCard(deckLeft);
            return true;
            HitPlayer(Deck);
            
        }
        else
        {
            return false;
        }
}

void DealDealerCard(stack<Card> &deckLeft)
{
    Card dealtCard = deckLeft.top();
    deckLeft.pop();
    dealerRoundTotal += dealtCard.cardValue;

}

bool HitDealer(stack<Card> &deckLeft)
{
   if (dealerRoundTotal < playerRoundTotal)
        {
            DealDealerCard(deckLeft);
            return true;
            HitDealer(Deck);
            
        }
        else
        {
            return false;
        }
}

void NewGame(int totalGames)
{
    for(int gameNumber = 0; gameNumber < totalGames; gameNumber++)
    {
        playerRoundTotal = 0;
        dealerRoundTotal = 0;
        EmptyDeck (Deck);
        Deck = ShuffleDeck(Cards);
        HitPlayer(Deck);
        HitDealer(Deck);
        if(playerRoundTotal > dealerRoundTotal && playerRoundTotal <= 21)
        {
            playerTotalWins++;
            cout << "Player won" <<endl;
        }
        else
        {
            dealerTotalWins++;
            cout << "Dealer won" << endl;
        }
    }
}

int main()
{ 
    NewGame(100);
    cout << "Player wins: " << playerTotalWins << endl;
    cout << "Dealer wins: " << dealerTotalWins << endl;
    return 0;
}
