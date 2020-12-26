#include <iostream> //allows for standard input and output
#include <stdlib.h> //opens the standard library, which includes function rand()


using namespace std;

struct gambler { //make a structure to store player information
int money;
char name[50];
bool fold;
int anntiMoney;
int riverMoney;
int turnMoney;
int flopMoney;
}player[9]; //this allows 10 players, from 0 to 9

struct buyInAndBlinds {
int buyIn;
int bigBlind;
int littleBlind;
}blinds;

void declarePlayers(int numberParticipants) {

    int buyIn;
    cout<<"Enter the Buy In"<<endl;
    cin>>buyIn;

    int n;
 //   char namePlayer[50];
    for (n=0; (n<numberParticipants); n++) {
 //       cout<<"Enter the Name of Player ";
 //       cout<<(n+1);
 //       cout<<" : ";
 //       cin.getline ( namePlayer, 50 );
 //       cin.get();
 //       cout<<endl;
        player[n+1].money = buyIn;
        player[n+1].fold = 0;
  //      player[n].name[50] = namePlayer[50];
    }
        blinds.buyIn = buyIn;
    return;
}

int decideDealer(int numberParticipants) {

    int n;
    int dealerPlayer;
    for (n=0; (n<numberParticipants); n++) {
        dealerPlayer= rand() % numberParticipants + 1; // something is wrong with the initial dealer selection randomizer, needs to be fixed
    }
    return dealerPlayer;
}

int decideLittleBlind(int numberParticipants, int dealerPosition) {

    int littlePlayer;
    littlePlayer = dealerPosition + 1;
    if (littlePlayer > numberParticipants) {
        littlePlayer = littlePlayer - numberParticipants;
    }
    while (player[littlePlayer].money <= 0) {
        littlePlayer = littlePlayer + 1;
        if (littlePlayer > numberParticipants) {
            littlePlayer = littlePlayer - numberParticipants;
        }
    }
    return littlePlayer;
}

int decideBigBlind(int numberParticipants, int dealerPosition) {

    int bigPlayer;
    bigPlayer = decideLittleBlind(numberParticipants, dealerPosition) + 1;
    if (bigPlayer > numberParticipants) {
        bigPlayer = bigPlayer - numberParticipants;
    }
    while (player[bigPlayer].money <= 0) {
        bigPlayer = bigPlayer + 1;
        if (bigPlayer > numberParticipants) {
            bigPlayer = bigPlayer - numberParticipants;
        }
    }
    return bigPlayer;
}

int findNextPlayer(int numberParticipants, int activePlayer) {
    int nextPlayer;
    nextPlayer = activePlayer + 1;
    if (nextPlayer > numberParticipants) {
        nextPlayer = nextPlayer - numberParticipants;
    }
    return nextPlayer;
}


void decideBlinds() { // This can be upgraded to utilize custom blinds, or increase blinds with number players remaining
    blinds.bigBlind = 2;
    blinds.littleBlind = 1;
    return;
}

void displayMoney(int numberParticipants, int potMoney) {
    int n;
    for (n=0; (n<numberParticipants); n++) {
        cout<<"Player "<<n+1<<" has "<<player[n+1].money<<" remaining"<<endl;
    }
    cout<<"Pot Money is : "<<potMoney<<endl<<endl;
}

int findDidntFold(int numberParticipants) {
    int n;
    for (n=0; (n<numberParticipants); n++) {
        if (player[n+1].fold == 0) {
            return (n+1);
        }
    }
}

void runTurn(int numberParticipants, int dealerPosition) {
    //blinds (preflop):
    int potMoney = 0;
    int foldCount = 0;
    player[decideBigBlind(numberParticipants, dealerPosition)].money = player[decideBigBlind(numberParticipants, dealerPosition)].money - blinds.bigBlind;
    potMoney = potMoney + blinds.bigBlind;
    player[decideBigBlind(numberParticipants, dealerPosition)].anntiMoney = blinds.bigBlind;
    player[decideLittleBlind(numberParticipants, dealerPosition)].money = player[decideLittleBlind(numberParticipants, dealerPosition)].money - blinds.littleBlind;
    potMoney = potMoney + blinds.littleBlind;
    player[decideLittleBlind(numberParticipants, dealerPosition)].anntiMoney = blinds.littleBlind;

    int minBet = blinds.bigBlind;
    int minPreFlop = blinds.bigBlind;
    int activePlayer = decideBigBlind(numberParticipants, dealerPosition);

    cout<<"--------------------------------------------------"<<endl;
    cout<<"After Blinds, the money on the board is as follows: "<<endl;
    displayMoney(numberParticipants, potMoney);

    cout<<endl<<endl<<"Deal 2 cards to each player : ";
    int thePreFlop;
    cin>>thePreFlop;
    cout<<endl<<endl;

    while (player[findNextPlayer(numberParticipants, activePlayer)].anntiMoney != minPreFlop) {
        activePlayer = findNextPlayer(numberParticipants, activePlayer);
        if (player[activePlayer].fold == 0) {
            cout<<"Player "<<activePlayer<<", It is your turn"<<endl;
            cout<<"Enter 1 to call: "<<minPreFlop - player[activePlayer].anntiMoney<<endl;
            cout<<"Enter 2 to raise"<<endl;
            cout<<"Enter 3 to fold"<<endl;

            int selection;
            cin>>selection;
            if (player[activePlayer].money <= 0) {
                selection = 3;
            }
            switch (selection) {
                case 1:
                    player[activePlayer].money = player[activePlayer].money + player[activePlayer].anntiMoney - minPreFlop;
                    potMoney = potMoney + minPreFlop - player[activePlayer].anntiMoney;
                    player[activePlayer].anntiMoney = player[activePlayer].anntiMoney + (minPreFlop - player[activePlayer].anntiMoney);
                break;
                case 2:
                    cout<<endl<<"How much money would you like to raise? ";
                    int raise;
                    cin>>raise;
                    cout<<endl;
                    minPreFlop = minPreFlop + raise;
                    player[activePlayer].money = player[activePlayer].money + player[activePlayer].anntiMoney - minPreFlop;
                    potMoney = potMoney + minPreFlop - player[activePlayer].anntiMoney;
                    player[activePlayer].anntiMoney = player[activePlayer].anntiMoney + (minPreFlop - player[activePlayer].anntiMoney);
                break;
                case 3:
                    player[activePlayer].fold = 1;
                    foldCount = foldCount + 1;
                    if (foldCount == numberParticipants - 1) {
                        activePlayer = findDidntFold(numberParticipants);
                        cout<<"Player "<<activePlayer<<" has won the hand!"<<endl;
                        cout<<"Player "<<activePlayer<<" wins "<<potMoney<<endl<<endl<<endl;
                        player[activePlayer].money = player[activePlayer].money + potMoney;
                        potMoney = 0;
                        displayMoney(numberParticipants, potMoney);
                        return;
                    }
                break;
                default:
                    cout<<"\nEnter correct choice\n\n";
                }
            cout<<endl;
            cout<<"--------------------------------------------------"<<endl;
            displayMoney(numberParticipants, potMoney);
        }
        else {
            cout<<"Player "<<activePlayer<<" has folded: no action neccesary"<<endl<<endl;
        }
    }


    //the river
    cout<<"Deal the river : ";
    int river;
    cin>>river;
    cout<<endl<<endl;

    activePlayer = dealerPosition;
    int n;
    int minRiver = 0;
    for (n=0; n<numberParticipants; n++) {
        activePlayer = findNextPlayer(numberParticipants, activePlayer);
        if (player[activePlayer].fold == 0) {
            cout<<"Player "<<activePlayer<<", It is your turn"<<endl;
            cout<<"Enter 1 to call: "<<minRiver - player[activePlayer].riverMoney<<endl;
            cout<<"Enter 2 to raise"<<endl;
            cout<<"Enter 3 to fold"<<endl;

            int selection;
            cin>>selection;
            if (player[activePlayer].money <= 0) {
                selection = 3;
            }
            switch (selection) {
                case 1:
                    player[activePlayer].money = player[activePlayer].money + player[activePlayer].riverMoney - minRiver;
                    potMoney = potMoney + minRiver - player[activePlayer].riverMoney;
                    player[activePlayer].riverMoney = player[activePlayer].riverMoney + (minRiver - player[activePlayer].riverMoney);
                break;
                case 2:
                    cout<<endl<<"How much money would you like to raise? ";
                    int raise;
                    cin>>raise;
                    cout<<endl;
                    minRiver = minRiver + raise;
                    player[activePlayer].money = player[activePlayer].money + player[activePlayer].riverMoney - minRiver;
                    potMoney = potMoney + minRiver - player[activePlayer].riverMoney;
                    player[activePlayer].riverMoney = player[activePlayer].riverMoney + (minRiver - player[activePlayer].riverMoney);
                break;
                case 3:
                    player[activePlayer].fold = 1;
                    foldCount = foldCount + 1;
                    if (foldCount == numberParticipants - 1) {
                        activePlayer = findDidntFold(numberParticipants);
                        cout<<"Player "<<activePlayer<<" has won the hand!"<<endl;
                        cout<<"Player "<<activePlayer<<" wins "<<potMoney<<endl<<endl<<endl;
                        player[activePlayer].money = player[activePlayer].money + potMoney;
                        potMoney = 0;
                        displayMoney(numberParticipants, potMoney);
                        return;
                    }
                break;
                default:
                    cout<<"\nEnter correct choice\n\n";
                }
            cout<<endl;
            cout<<"--------------------------------------------------"<<endl;
            displayMoney(numberParticipants, potMoney);
        }
        else {
            cout<<"Player "<<activePlayer<<" has folded: no action neccesary"<<endl<<endl;
        }
    }

    while (player[findNextPlayer(numberParticipants, activePlayer)].riverMoney != minRiver) {
        activePlayer = findNextPlayer(numberParticipants, activePlayer);
        if (player[activePlayer].fold == 0) {
            cout<<"Player "<<activePlayer<<", It is your turn"<<endl;
            cout<<"Enter 1 to call: "<<minRiver - player[activePlayer].riverMoney<<endl;
            cout<<"Enter 2 to raise"<<endl;
            cout<<"Enter 3 to fold"<<endl;

            int selection;
            cin>>selection;
            if (player[activePlayer].money <= 0) {
                selection = 3;
            }
            switch (selection) {
                case 1:
                    player[activePlayer].money = player[activePlayer].money + player[activePlayer].riverMoney - minRiver;
                    potMoney = potMoney + minRiver - player[activePlayer].riverMoney;
                    player[activePlayer].riverMoney = player[activePlayer].riverMoney + (minRiver - player[activePlayer].riverMoney);
                break;
                case 2:
                    cout<<endl<<"How much money would you like to raise? ";
                    int raise;
                    cin>>raise;
                    cout<<endl;
                    minRiver = minRiver + raise;
                    player[activePlayer].money = player[activePlayer].money + player[activePlayer].riverMoney - minRiver;
                    potMoney = potMoney + minRiver - player[activePlayer].riverMoney;
                    player[activePlayer].riverMoney = player[activePlayer].riverMoney + (minRiver - player[activePlayer].riverMoney);
                break;
                case 3:
                    player[activePlayer].fold = 1;
                    foldCount = foldCount + 1;
                    if (foldCount == numberParticipants - 1) {
                        activePlayer = findDidntFold(numberParticipants);
                        cout<<"Player "<<activePlayer<<" has won the hand!"<<endl;
                        cout<<"Player "<<activePlayer<<" wins "<<potMoney<<endl<<endl<<endl;
                        player[activePlayer].money = player[activePlayer].money + potMoney;
                        potMoney = 0;
                        displayMoney(numberParticipants, potMoney);
                        return;
                    }
                break;
                default:
                    cout<<"\nEnter correct choice\n\n";
                }
            cout<<endl;
            cout<<"--------------------------------------------------"<<endl;
            displayMoney(numberParticipants, potMoney);
        }
        else {
            cout<<"Player "<<activePlayer<<" has folded: no action neccesary"<<endl<<endl;
        }
    }


    //the turn
    cout<<"Deal the turn : ";
    int turn;
    cin>>turn;
    cout<<endl<<endl;

    activePlayer = dealerPosition;
    int minTurn = 0;
    for (n=0; n<numberParticipants; n++) {
        activePlayer = findNextPlayer(numberParticipants, activePlayer);
        if (player[activePlayer].fold == 0) {
            cout<<"Player "<<activePlayer<<", It is your turn"<<endl;
            cout<<"Enter 1 to call: "<<minTurn - player[activePlayer].turnMoney<<endl;
            cout<<"Enter 2 to raise"<<endl;
            cout<<"Enter 3 to fold"<<endl;

            int selection;
            cin>>selection;
            if (player[activePlayer].money <= 0) {
                selection = 3;
            }
            switch (selection) {
                case 1:
                    player[activePlayer].money = player[activePlayer].money + player[activePlayer].turnMoney - minTurn;
                    potMoney = potMoney + minTurn - player[activePlayer].turnMoney;
                    player[activePlayer].turnMoney = player[activePlayer].turnMoney + (minTurn - player[activePlayer].turnMoney);
                break;
                case 2:
                    cout<<endl<<"How much money would you like to raise? ";
                    int raise;
                    cin>>raise;
                    cout<<endl;
                    minTurn = minTurn + raise;
                    player[activePlayer].money = player[activePlayer].money + player[activePlayer].turnMoney - minTurn;
                    potMoney = potMoney + minTurn - player[activePlayer].turnMoney;
                    player[activePlayer].turnMoney = player[activePlayer].turnMoney + (minTurn - player[activePlayer].turnMoney);
                break;
                case 3:
                    player[activePlayer].fold = 1;
                    foldCount = foldCount + 1;
                    if (foldCount == numberParticipants - 1) {
                        activePlayer = findDidntFold(numberParticipants);
                        cout<<"Player "<<activePlayer<<" has won the hand!"<<endl;
                        cout<<"Player "<<activePlayer<<" wins "<<potMoney<<endl<<endl<<endl;
                        player[activePlayer].money = player[activePlayer].money + potMoney;
                        potMoney = 0;
                        displayMoney(numberParticipants, potMoney);
                        return;
                    }
                break;
                default:
                    cout<<"\nEnter correct choice\n\n";
                }
            cout<<endl;
            cout<<"--------------------------------------------------"<<endl;
            displayMoney(numberParticipants, potMoney);
        }
        else {
            cout<<"Player "<<activePlayer<<" has folded: no action neccesary"<<endl<<endl;
        }
    }

    while (player[findNextPlayer(numberParticipants, activePlayer)].turnMoney != minTurn) {
        activePlayer = findNextPlayer(numberParticipants, activePlayer);
        if (player[activePlayer].fold == 0) {
            cout<<"Player "<<activePlayer<<", It is your turn"<<endl;
            cout<<"Enter 1 to call: "<<minTurn - player[activePlayer].turnMoney<<endl;
            cout<<"Enter 2 to raise"<<endl;
            cout<<"Enter 3 to fold"<<endl;

            int selection;
            cin>>selection;
            if (player[activePlayer].money <= 0) {
                selection = 3;
            }
            switch (selection) {
                case 1:
                    player[activePlayer].money = player[activePlayer].money + player[activePlayer].turnMoney - minTurn;
                    potMoney = potMoney + minTurn - player[activePlayer].turnMoney;
                    player[activePlayer].turnMoney = player[activePlayer].turnMoney + (minTurn - player[activePlayer].turnMoney);
                break;
                case 2:
                    cout<<endl<<"How much money would you like to raise? ";
                    int raise;
                    cin>>raise;
                    cout<<endl;
                    minTurn = minTurn + raise;
                    player[activePlayer].money = player[activePlayer].money + player[activePlayer].turnMoney - minTurn;
                    potMoney = potMoney + minTurn - player[activePlayer].turnMoney;
                    player[activePlayer].turnMoney = player[activePlayer].turnMoney + (minTurn - player[activePlayer].turnMoney);
                break;
                case 3:
                    player[activePlayer].fold = 1;
                    foldCount = foldCount + 1;
                    if (foldCount == numberParticipants - 1) {
                        activePlayer = findDidntFold(numberParticipants);
                        cout<<"Player "<<activePlayer<<" has won the hand!"<<endl;
                        cout<<"Player "<<activePlayer<<" wins "<<potMoney<<endl<<endl<<endl;
                        player[activePlayer].money = player[activePlayer].money + potMoney;
                        potMoney = 0;
                        displayMoney(numberParticipants, potMoney);
                        return;
                    }
                break;
                default:
                    cout<<"\nEnter correct choice\n\n";
                }
            cout<<endl;
            cout<<"--------------------------------------------------"<<endl;
            displayMoney(numberParticipants, potMoney);
        }
        else {
            cout<<"Player "<<activePlayer<<" has folded: no action neccesary"<<endl<<endl;
        }
    }



    //the flop
    cout<<"Deal the flop : ";
    int flop;
    cin>>flop;
    cout<<endl<<endl;

    activePlayer = dealerPosition;
    int minFlop = 0;
    for (n=0; n<numberParticipants; n++) {
        activePlayer = findNextPlayer(numberParticipants, activePlayer);
        if (player[activePlayer].fold == 0) {
            cout<<"Player "<<activePlayer<<", It is your turn"<<endl;
            cout<<"Enter 1 to call: "<<minFlop - player[activePlayer].flopMoney<<endl;
            cout<<"Enter 2 to raise"<<endl;
            cout<<"Enter 3 to fold"<<endl;

            int selection;
            cin>>selection;
            if (player[activePlayer].money <= 0) {
                selection = 3;
            }
            switch (selection) {
                case 1:
                    player[activePlayer].money = player[activePlayer].money + player[activePlayer].flopMoney - minFlop;
                    potMoney = potMoney + minFlop - player[activePlayer].flopMoney;
                    player[activePlayer].flopMoney = player[activePlayer].flopMoney + (minFlop - player[activePlayer].flopMoney);
                break;
                case 2:
                    cout<<endl<<"How much money would you like to raise? ";
                    int raise;
                    cin>>raise;
                    cout<<endl;
                    minFlop = minFlop + raise;
                    player[activePlayer].money = player[activePlayer].money + player[activePlayer].flopMoney - minFlop;
                    potMoney = potMoney + minFlop - player[activePlayer].flopMoney;
                    player[activePlayer].flopMoney = player[activePlayer].flopMoney + (minFlop - player[activePlayer].flopMoney);
                break;
                case 3:
                    player[activePlayer].fold = 1;
                    foldCount = foldCount + 1;
                    if (foldCount == numberParticipants - 1) {
                        activePlayer = findDidntFold(numberParticipants);
                        cout<<"Player "<<activePlayer<<" has won the hand!"<<endl;
                        cout<<"Player "<<activePlayer<<" wins "<<potMoney<<endl<<endl<<endl;
                        player[activePlayer].money = player[activePlayer].money + potMoney;
                        potMoney = 0;
                        displayMoney(numberParticipants, potMoney);
                        return;
                    }
                break;
                default:
                    cout<<"\nEnter correct choice\n\n";
                }
            cout<<endl;
            cout<<"--------------------------------------------------"<<endl;
            displayMoney(numberParticipants, potMoney);
        }
        else {
            cout<<"Player "<<activePlayer<<" has folded: no action neccesary"<<endl<<endl;
        }
    }

    while (player[findNextPlayer(numberParticipants, activePlayer)].flopMoney != minFlop) {
        activePlayer = findNextPlayer(numberParticipants, activePlayer);
        if (player[activePlayer].fold == 0) {
            cout<<"Player "<<activePlayer<<", It is your turn"<<endl;
            cout<<"Enter 1 to call: "<<minFlop - player[activePlayer].flopMoney<<endl;
            cout<<"Enter 2 to raise"<<endl;
            cout<<"Enter 3 to fold"<<endl;

            int selection;
            cin>>selection;
            if (player[activePlayer].money <= 0) {
                selection = 3;
            }
            switch (selection) {
                case 1:
                    player[activePlayer].money = player[activePlayer].money + player[activePlayer].flopMoney - minFlop;
                    potMoney = potMoney + minFlop - player[activePlayer].flopMoney;
                    player[activePlayer].flopMoney = player[activePlayer].flopMoney + (minFlop - player[activePlayer].flopMoney);
                break;
                case 2:
                    cout<<endl<<"How much money would you like to raise? ";
                    int raise;
                    cin>>raise;
                    cout<<endl;
                    minFlop = minFlop + raise;
                    player[activePlayer].money = player[activePlayer].money + player[activePlayer].flopMoney - minFlop;
                    potMoney = potMoney + minFlop - player[activePlayer].flopMoney;
                    player[activePlayer].flopMoney = player[activePlayer].flopMoney + (minFlop- player[activePlayer].flopMoney);
                break;
                case 3:
                    player[activePlayer].fold = 1;
                    foldCount = foldCount + 1;
                    if (foldCount == numberParticipants - 1) {
                        activePlayer = findDidntFold(numberParticipants);
                        cout<<"Player "<<activePlayer<<" has won the hand!"<<endl;
                        cout<<"Player "<<activePlayer<<" wins "<<potMoney<<endl<<endl<<endl;
                        player[activePlayer].money = player[activePlayer].money + potMoney;
                        potMoney = 0;
                        displayMoney(numberParticipants, potMoney);
                        return;
                    }
                break;
                default:
                    cout<<"\nEnter correct choice\n\n";
                }
            cout<<endl;
            cout<<"--------------------------------------------------"<<endl;
            displayMoney(numberParticipants, potMoney);
        }
        else {
            cout<<"Player "<<activePlayer<<" has folded: no action neccesary"<<endl<<endl;
        }
    }
    cout<<"Show your hands "<<endl<<endl<<endl;
    cout<<"Which player has the best hand? (Enter 0 to chop) : ";
    int winner;
    int numberWinners;
    cin>>winner;
    if (winner > 0) {
    cout<<"Congratulations Player "<<winner<<" you win "<<potMoney<<endl<<endl<<endl;
    player[winner].money = player[winner].money + potMoney;
    }

    if (winner == 0) {
        cout<<"Enter the number of players who chop : ";
        cin>>numberWinners;
        cout<<endl;
        for (n=0; (n<numberWinners); n++) {
            cout<<"Enter winner : ";
            cin>>winner;
            player[winner].money = player[winner].money + potMoney / numberWinners;
        }
    }
    potMoney = 0;
    displayMoney(numberParticipants, potMoney);

return;
}

void refreshPlayers(int numberParticipants) {
    int n;
    for (n=0; (n<numberParticipants); n++) {
        player[n+1].fold = 0;
        player[n+1].anntiMoney = 0;
        player[n+1].riverMoney = 0;
        player[n+1].turnMoney = 0;
        player[n+1].flopMoney = 0;
    }
}

int main()
{
    int numberParticipants;
    cout<<"Enter the Number of Participants (Less than 10)"<<endl;
    cin>>numberParticipants;
    declarePlayers(numberParticipants);

    int dealerPosition = decideDealer(numberParticipants);
    cout<<"Dealer is : "<<dealerPosition<<endl;
    cout<<"Little Blind is : "<<decideLittleBlind(numberParticipants, dealerPosition)<<endl;
    cout<<"Big Blind is : "<<decideBigBlind(numberParticipants, dealerPosition)<<endl<<endl<<endl;
    cout<<"Enter 1 to start the game : ";
    int beginGame;
    cin>>beginGame;
    cout<<endl<<endl<<endl;

    decideBlinds();
    int anotherTurn = 1;
    while (anotherTurn != 0) {

        if (anotherTurn == 2) {
            int n;
            int playerMoney;
            for (n=0; (n<numberParticipants); n++) {
                cout<<"Player "<<n+1<<" money remaining is : "<<endl;
                cin>>playerMoney;
                player[n+1].money = playerMoney;
            }
            int potMoney = 0;
            displayMoney(numberParticipants, potMoney);
        }

        runTurn(numberParticipants, dealerPosition);

        cout<<endl<<"Would you like to play another turn?"<<endl;
        cout<<"Enter 0 for no, Enter 1 for yes, Enter 2 for manual override : ";
        cin>>anotherTurn;

        if (anotherTurn == 1 || anotherTurn == 2) {
            refreshPlayers(numberParticipants);

            dealerPosition = dealerPosition + 1;
            if (dealerPosition > numberParticipants) {
                dealerPosition = dealerPosition - numberParticipants;
            }
            cout<<endl<<endl<<"Dealer is : "<<dealerPosition<<endl;
            cout<<"Little Blind is : "<<decideLittleBlind(numberParticipants, dealerPosition)<<endl;
            cout<<"Big Blind is : "<<decideBigBlind(numberParticipants, dealerPosition)<<endl<<endl<<endl;
        }
    }
    return 0;
}
