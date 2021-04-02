//-----------------------------
//CIS247C Wk2 Blackjack iLab
//Alexandra Jones
//3/18/2019
//-----------------------------

#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include "Card.h"
using namespace std;

string showCards(vector<Card> cards);
short sumCardValues(vector<Card> cards);
void playHand(short &cash);

int main()
{

	short cash = 100;

	cout << "Welcome to Blackjack!" << endl;
	cout << "\nYour starting cash is: $" << cash << endl;

	//Pause
	cout << "\nPress any key to continue..";
	_getch();

	//Create the Menu Loop that accepts choice
	short choice = 0;

	do
	{
		system("cls");
		cout << "Main Menu" << endl;
		cout << "\n1) Play a Hand" << endl;
		cout << "\n2) Show Current Cash Balance" << endl;
		cout << "\n3) Exit" << endl;
		cout << "\nPlease enter your choice:" << endl;
		cin >> choice;

		//Change Application based on Choice
		switch (choice)
		{
		case 1:
			playHand(cash);
			break;
		case 2:
			cout << "Show Current Balance" << endl;
			break;
		case 3:
			cout << "Thanks for playing!" << endl;
			cout << "\nYour ending balance is: $" << cash << endl;
			break;
		default:
			cout << "Error. Please choose from the menu!" << endl;
			break;
		}
		//Pause
		cout << "\nPress any key to continue..";
		_getch();
	} while (choice != 3);
	
	return 0;
}

string showCards(vector<Card> cards)
{
	string output = "";

	for (Card c : cards)
	{
		output += c.toString() + " ";
	}
	
	return output;
}

short sumCardValues(vector<Card> cards)
{
	short total = 0;

	for (Card c : cards)
	{
		total = total + c.getValue();
	}

	return total;
}

void playHand(short &cash)
{
	vector<Card> dealerCards;
	vector<Card> playerCards;

	short dealerCardsTotal = 0;
	short playerCardsTotal = 0;

	//Place bets
	short bet = 0;
	cout << "Please place your bet: " << endl;
	cin >> bet;

	//Pull dealers hand and show top card
	Card card1;
	Card card2;

	dealerCards.push_back(card1);
	dealerCards.push_back(card2);
	dealerCardsTotal = sumCardValues(dealerCards);

	cout << "\nDealer is showing: " << dealerCards[0].toString() << endl;

	//Pull players hand
	playerCards.push_back(Card());
	playerCards.push_back(Card());
	playerCardsTotal = sumCardValues(playerCards);

	cout << "\nYour hand: " << showCards(playerCards) << endl;

	//Player chooses to hit or stand
	char answer = '?';

	do
	{
		cout << "Do you want to hit or stand (H/S)?";
		cin.sync();
		cin >> answer;
		cin.sync();

		if (toupper(answer) == 'H')
		{
			Card c;
			cout << "\nYou were dealt this card: " << c.toString() << endl;
			playerCards.push_back(c);

			playerCardsTotal = sumCardValues(playerCards);

			if (playerCardsTotal > 21)
			{
				for (Card c : playerCards)
				{
					if (c.getValue() == 11)
					{
						cout << "\nYour total is: " << playerCardsTotal << endl;
						c.flipAceToOne();
						cout << "\nYou have exceeded 21, but an Ace was found and changed from an 11 to a 1." << endl;
						playerCardsTotal = sumCardValues(playerCards);
						cout << "\nYour new total is: " << playerCardsTotal;

						if (playerCardsTotal <= 21)
							break;
					}
				}
			}

			//Show Cards and Total
			system("cls");
			cout << "\nHere are your cards: " << showCards(playerCards) << endl;
			cout << "\nYour total is: " << playerCardsTotal << endl;

			//If busted Stop
			if (playerCardsTotal > 21)
				answer = 'S';
		}
		
	}

	while (toupper(answer) != 'S');

	//If player busts subtract the bet
	if (playerCardsTotal > 21)
	{
		cout << "\nYou busted!" << endl;
		cash = cash - bet;
	}
	else
	{
		//Dealer plays until 17 
		do
		{
			if (dealerCardsTotal < 17)
			{
				Card c;

				cout << "\nDealer was dealt: " << c.toString() << endl;
				dealerCards.push_back(c);
				cout << "\nDealer cards: " << showCards(dealerCards) << endl;
				dealerCardsTotal = sumCardValues(dealerCards);
				cout << "\nDealer totals: " << dealerCardsTotal << endl;
			}
		}

		while (dealerCardsTotal < 17);
		//Show all cards
		cout << "\nYour cards: " << showCards(playerCards) << " (" << playerCardsTotal << ") " << endl;
		cout << "\nDealer cards: " << showCards(dealerCards) << " (" << dealerCardsTotal << ") " << endl;

		//Find the winner
		if (dealerCardsTotal > 21)
		{
			cout << "\nDealer Busted." << endl;
			cash = cash + bet;
		}
		else if (dealerCardsTotal > playerCardsTotal)
		{
			cout << "\nDealer wins." << endl;
			cash = cash - bet;
		}
		else if (playerCardsTotal > dealerCardsTotal)
		{
			cout << "\nYou win!!" << endl;
			cash = cash + bet;
		}
		else
		{
			cout << "\nYou pushed the dealer! (TIE)" << endl;
		}
	}

	//Show Current Cash
	cout << "\nYour current balance is: " << cash << endl;
	
}

