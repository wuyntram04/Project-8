#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include "input.h"
#include <queue>
#include <vector>
#include "Patient.h"


using namespace std;

void option1();
void option2();
struct Card;
vector<Card> buildDeck(int cardsPerSuit);
void deal(const vector<Card>& deck, deque<Card>& p1, deque<Card>& p2);

int main()
{
	do
	{
		system("cls");
		cout << "\n\t\t CMPR131 Chapter 8: Applications using Queues by Prof Q";
		cout << "\n\t\t" << string(70, char(205));
		cout << "\n\t\t1> Simulation of War (card game) using deque STL";
		cout << "\n\t\t2> Simulation of an emergency room (ER) using priority queue STL (DONE)";
		cout << "\n\t\t3> Simulation of checkout lines at CostCo using multiple queues STL";
		cout << "\n\t\t" << string(70, char(196));
		cout << "\n\t\t0> Exit";
		cout << "\n\t\t" << string(70, char(205)) << '\n';
		switch (inputInteger("\t\t  Option: ", 0, 3))
		{
		case 0: exit(1);
		case 1: option1(); break;
		case 2: option2(); break;
			//			case 3: option3(); break;
		default: cout << "\n\tERROR: invalud option.\n";
		}

		cout << '\n';
		system("pause");

	} while (true);

	return 0;
}

// ============================
// Struct + Helper Functions
// ============================
struct Card
{
    int rank; // 2..(1 + number of cards per suit)
};

// Build deck dynamically based on user input
vector<Card> buildDeck(int cardsPerSuit)
{
    vector<Card> deck;
    for (int s = 0; s < 4; s++) { // 4 suits (ignored)
        for (int r = 2; r < 2 + cardsPerSuit; r++) {
            deck.push_back({ r });
        }
    }
    return deck;
}

// Deal evenly between two players
void deal(const vector<Card>& deck, deque<Card>& p1, deque<Card>& p2)
{
    for (size_t i = 0; i < deck.size(); i++) {
        if (i % 2 == 0)
            p1.push_back(deck[i]);
        else
            p2.push_back(deck[i]);
    }
}

// ============================
// Option 1: War Card Game
// ============================
void option1()
{
    system("cls");
    cout << "\n\t1>Simulation of War (card game) using deque STL\n";
    int cardsPerSuit = inputInteger("\n\t\tEnter a number of cards per suit: ", 1, 13);

    vector<Card> deck = buildDeck(cardsPerSuit);
    srand(time(0));
    random_shuffle(deck.begin(), deck.end());

    deque<Card> p1, p2;
    deal(deck, p1, p2);

    cout << "\n\tDeck created with " << deck.size() << " cards (" << cardsPerSuit << " per suit).\n";
    cout << "\tEach player gets " << p1.size() << " cards.\n\n";

    int round = 1;
    const int maxRounds = 5000;

    while (!p1.empty() && !p2.empty() && round <= maxRounds) {
        vector<Card> pile; // cards on the table for this round

        // both players play top card
        Card c1 = p1.front(); p1.pop_front();
        Card c2 = p2.front(); p2.pop_front();

        pile.push_back(c1);
        pile.push_back(c2);

        cout << "\n\tRound " << round++ << ":  Player1: " << c1.rank << "  Player2: " << c2.rank;

        // normal win
        if (c1.rank > c2.rank) {
            cout << " -> Player1 wins!\n";
            for (auto& c : pile) p1.push_back(c);
        }
        else if (c2.rank > c1.rank) {
            cout << " -> Player2 wins!\n";
            for (auto& c : pile) p2.push_back(c);
        }
        else {
            cout << " -> Tie breaker begins!\n\n";

            bool warOver = false;
            while (!warOver) {
               
                // each player places 3 face-down cards if possible
                for (int i = 0; i < 3; i++) {
                    if (!p1.empty()) { pile.push_back(p1.front()); p1.pop_front(); }
                    if (!p2.empty()) { pile.push_back(p2.front()); p2.pop_front(); }
                }

                if (p1.empty() && p2.empty()) {
                    cout << "\tBoth players ran out of cards during war!\n";
                    warOver = true;
                    break;
                }
                else if (p1.empty()) {
                    cout << "\tPlayer 1 has no cards left to flip.\n";
                    warOver = true;
                    break;
                }
                else if (p2.empty()) {
                    cout << "\tPlayer 2 has no cards left to flip.\n";
                    warOver = true;
                    break;
                }

                Card war1 = p1.front(); p1.pop_front();
                Card war2 = p2.front(); p2.pop_front();

                pile.push_back(war1);
                pile.push_back(war2);

                cout << "\tWAR cards -> Player1: " << war1.rank << "  Player2: " << war2.rank;

                if (war1.rank > war2.rank) {
                    cout << " -> Player1 wins the tie breaker!\n";
                    for (auto& c : pile) p1.push_back(c);
                    warOver = true;
                }
                else if (war2.rank > war1.rank) {
                    cout << " -> Player2 wins the tie breaker!\n";
                    for (auto& c : pile) p2.push_back(c);
                    warOver = true;
                }
                else {
                    cout << " -> ANOTHER TIE BREAKER!\n";
                    // loop continues until someone wins
                }
            }
        }
    }

    cout << "\n\n\n\t============== FINAL RESULT ==============\n";
    if (p1.empty() && p2.empty())
        cout << "\n\tDraw! Both players ran out of cards.\n";
    else if (p1.empty())
        cout << "\n\tPlayer2 wins the game!\n";
    else if (p2.empty())
        cout << "\n\tPlayer1 wins the game!\n";
    else
        cout << "\n\n\tNo winner (maximum rounds reached).\n";

}


void option2()
{

	system("cls");
	cout << "\n\t2> Simulation of an emergency room (ER) using priority queue STL\n";

	priority_queue<Patient> pq2; //key
	vector<Patient> submit;

	do
	{
		system("cls");
		cout << "\n\t2> Simulation of an emergency room (ER) using priority queue STL";
		cout << "\n\t" << string(60, char(205));
		cout << "\n\t\tA> Register a patient";
		cout << "\n\t\tB> Transfer patient(s) to the designation";
		cout << "\n\t\tC> Display transferred patients";
		cout << "\n\t" << string(60, char(196));
		cout << "\n\t\t0> return\n";
		cout << "\n\t" << string(60, char(205));

		switch (toupper(inputChar("\n\t\tOption: ", static_cast<string>("ABC0"))))
		{
		case '0': return;
		case 'A':
		{
			Patient patient;
			string name;
			cout << "\n\t\tEnter the patient's name: ";
			getline(cin, name);
			patient.setName(name);
			patient.setAge(inputInteger("\t\tEnter the patient's age: ", true));
			patient.setCheckedInTime(time(0));
			patient.setGender(toupper(inputChar("\t\tChoose the patient's gender (F-female or M-male): ", 'F', 'M')));
			patient.setPriority(inputInteger("\t\tChoose the ER level 1)Non-urgent, 2)Less Urgent, 3)Urgent, 4)Emergent, or 5)Resuscitation: ", 1, 5));

			pq2.push(patient); // enqueue
			cout << "\n\t\tPatient information has been registered.\n\n";
		}
		break;
		case 'B':
		{
			if (!pq2.empty())
			{
				if (pq2.top().getPriority() == 5)
				{
					submit.push_back(pq2.top());
					cout << "\n\t\t" << pq2.top().getName() << " - transfers to ICU...\n\n";
					pq2.pop(); // dequeue
					break;
				}
				else if (pq2.top().getPriority() == 4)
				{
					submit.push_back(pq2.top());
					cout << "\n\t\t" << pq2.top().getName() << " - transfers to surgery room...\n\n";
					pq2.pop();
					break;
				}
				else if (pq2.top().getPriority() == 3)
				{
					submit.push_back(pq2.top());
					cout << "\n\t\t" << pq2.top().getName() << " - transfers to emergency room...\n\n";
					pq2.pop();
					break;
				}
				else if (pq2.top().getPriority() == 2)
				{
					submit.push_back(pq2.top());
					cout << "\n\t\t" << pq2.top().getName() << " - transfers to x-ray lab...\n\n";
					pq2.pop();
					break;
				}
				else if (pq2.top().getPriority() == 1)
				{
					submit.push_back(pq2.top());
					cout << "\n\t\t" << pq2.top().getName() << " - examines and gives prescription...\n";
					pq2.pop();
					break;
				}
			}
		}
		break;
		case 'C':
		{
			if (!submit.empty())
			{

				sort(submit.begin(), submit.end());
				reverse(submit.begin(), submit.end());
				cout << '\n';
				for (int i = 0; i < submit.size(); i++)
					cout << "\t\t" << i + 1 << " - " << submit[i] << '\n';
			}
			else
				cout << "\n\t\tNo patient has been transferred.\n\n";
		}
		break;
		}

		cout << "\n";
		system("pause");
	} while (true);
}


