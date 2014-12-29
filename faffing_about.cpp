#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

enum status { KO, Poisoned /*more to come for sure.*/ };

class Player
{
private:
	int strength, hitPoints;
	string charName;
	status playerStatus;

	void knockOut()
	{
		if (getHP() < 0)
		{
			hitPoints = 0;
		}
		if (getHP() == 0)
		{
			setStatus(KO);
			cout << charName << " has died\n";
		}
	}

public:
	~Player() {};
	Player(string initName){ charName = initName; };
	Player(string initName, int initStr)
	{
		charName = initName;
		strength = initStr;
	}
	Player(string initName, int initStr, int initHitPoints)
	{
		charName = initName;
		strength = initStr;
		hitPoints = initHitPoints;
	}
	status getStatus()
	{
		return playerStatus;
	}
	void setStatus(status newStatus)
	{
		playerStatus = newStatus;
	}

	void setName(string newName)
	{
		charName = newName;
	}
	string getName()
	{
		return charName;
	}
	int getStr()
	{
		return strength;
	}
	void setStr(int newStr)
	{
		strength = newStr;
	}
	int getHP()
	{
		return hitPoints;
	}
	void getHP(bool pretty)
	{
		if (pretty == 1)
		{
			cout << getName() << " has " << getHP() << " hit points\n";
		}
	}
	void setHP(int newHP)
	{
		hitPoints = newHP;
		knockOut();
	}
	void getStats()
	{
		cout << "Name:\t" << getName() << endl;
		cout << "\tHit Points: " << getHP() << endl;
		cout << "\tStrength: " << getStr() << endl;
		cout << "\tStatus: " << getStatus() << "\n\n";
	}
};

class Battle
{
	/*
	 * Ideally this will be a (singleton?) mediator class.
	 * Let's see how it goes.
	 */

private:
	Battle(){ srand(time(NULL)); };
	int getRandom(int multiplier)
	{
		//int var = ;
		return rand() % multiplier;
	}
public:

	//static duel* newDuel();


	Battle & newBattle()
	{
		static Battle *globalBattle = new Battle();
		return *globalBattle;
	}
	~Battle(){};
	void attack(Player &attacker, Player &defender)
	{
		//do stuff. Attacky like.
		if (attacker.getHP() > 0 && defender.getHP() > 0)
		{
			int attackVal = getRandom(attacker.getStr());
			cout << "\nAttacker " << attacker.getName() << " hits " << defender.getName() << " for " << attackVal << " HP\n";
			defender.setHP(defender.getHP() - attackVal);
			attacker.getHP(1);
			defender.getHP(1);
		}
	}
	void duel(Player &p1, Player &p2)
	{
		// To the death!
		string winner;

		cout << p1.getName() << " Vs. " << p2.getName() << " battle to the death" << endl;

		while (p1.getHP() > 0 && p2.getHP() > 0)
		{
			attack(p1, p2);
			attack(p2, p1);
		}
		if (p1.getHP() > 0){
			winner = p1.getName();
		}
		else if (p2.getHP() > 0)
		{
			winner = p2.getName();
		}
		cout << "The winner is: " << winner << endl;
	}

	void teamBattle(Player *team1[3], Player *team2[3])
	{
		//This is hard.
	}
};

int main()
{
	Battle battle = battle.newBattle();
	Player * pTeam1[3];
	
	pTeam1[0] = new Player("Cloud", 100, 7777);
	pTeam1[1] = new Player("Yuffie", 80, 8000);
	pTeam1[2] = new Player("Red13", 90, 7000);
		
	
	Player* pTeam2[3];
	pTeam2[0] = new Player("Sephiroth", 50, 9999);
	pTeam2[1] = new Player("Jenova", 60, 9999);
	pTeam2[2] = new Player("Hojo", 55, 9999);
	
	for (int i = 0; i <= 2; i++)
	{
		battle.duel(*pTeam1[i], *pTeam2[i]);
		cin.get();
	}
		
	// battle.duel(c1, c2);
	cout << "\n\nBattle complete, press enter to quit" << endl;
	cin.get();

	return 0;
}