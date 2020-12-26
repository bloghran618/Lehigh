#include <iostream>

using namespace std;

int main()
{
    int years;
    int money;
    int moneyAnnually
    cout<<"Enter the years you are saving for"<<endl;
    cin<<years;
    cout<<"Enter the amount of money you are saving daily"<<endll;
    cin<<money;
    moneyAnnually = money * 365;

    int yearsRemaining
    int totalMoney = 0;
    for (yearsRemaining = years; yearsRemaining >= 0; yearsRemaining = yearsRemaining - 1) {
        totalMoney = totalMoney + ((moneyAnnually * 1.1) ^ yearsRemaining);
    }
    cout<<"The money you will save is: " <<cout totalMoney;
}
