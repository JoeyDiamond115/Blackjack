#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <random>
#include <ctime>
#include <algorithm>

using namespace std;

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

const int cardsInDeck = 52;
stack<Card> DeckClear (stack<Card> &deck)
{
    for( int i =0; i < cardsInDeck; i++)
    {
        if(!deck.empty())
        {
            deck.pop();
        }
    }
    return deck;
}

stack<Card> DeckShuffle (vector<Card> allCards)
{
    stack<Card> shuffledDeck;
    std::random_device random_dev;
    std::mt19937       generator(random_dev());
    std::shuffle(allCards.begin(), allCards.end(), generator);
        for(Card card : allCards)
        {
            shuffledDeck.push(card);
        }
    return shuffledDeck;
}
stack<Card> TestingDeck = DeckShuffle(Cards);

const int totalGames = 100;
void testNewRound(){}
int PlayGame(const function<void()> &newGame)
{
    int numberOfGamesPlayed = 0;
    for(int i = 0; i < totalGames; i++)
    {
        newGame();
        numberOfGamesPlayed++;
    }
    return numberOfGamesPlayed;
}



int playerTotal = 0;
int playerWins = 0;
int dealerTotal = 0;
int dealerWins = 0;
int gamesPlayed = 0;

void playerDraw(stack<Card> &deck)
{
    Card drawnCard = deck.top();
    deck.pop();
    playerTotal += drawnCard.cardValue;
}

bool playerHit(stack<Card> &deck)
{
    while(playerTotal < 16)
    {
        playerDraw(deck);
    }
    if(playerTotal > 21)
    {
        return false;
    }
    return true;
}


void dealerDraw(stack<Card> &deck)
{
    Card drawnCard = deck.top();
    deck.pop();
    dealerTotal += drawnCard.cardValue;

}

bool dealerHit(stack<Card> &deck)
{
    while(dealerTotal<playerTotal)
    {
        dealerDraw(deck);
    }
    if(dealerTotal > 21)
    {
        return false;
    }
    return true;
}

stack<Card> Deck;

void newRound()
{
    DeckClear (Deck);
    Deck = DeckShuffle(Cards);
    gamesPlayed++;
    playerTotal = 0;
    dealerTotal = 0;
    if(playerHit(Deck) && !dealerHit(Deck))
    {
        playerWins++;
        cout << "Player won" <<endl;
    }
    else
    {
        dealerWins++;
        cout << "Dealer won" << endl;
    }
}

int main()
{ 
    cout<<"Hello world"<<endl;
    PlayGame(newRound);
    cout<<"Player won: " << playerWins << " times" << endl;
    cout <<"Dealer won: " << dealerWins << " times" << endl;

    return 0;
}
