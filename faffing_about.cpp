// faffing_about.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
using namespace std;


class player
{
private:
	int strength, hitPoints;
	string charName;
	
public:
	~player() {};
	player(string initName){ charName = initName; };
	player(string initName, int initStr){
		charName = initName;
		strength = initStr;
	}
	player(string initName, int initStr, int initHitPoints){
		charName = initName;
		strength = initStr;
		hitPoints = initHitPoints;
	}
	
	void setName(string newName){
		charName = newName;
	}
	string getName(){
		return charName;
	}
	int getStr(){
		return strength;
	}
	void setStr(int newStr){
		strength = newStr;
	}
	int getHP(){
		return hitPoints;
	}
	void setHitPoints(int newHP){
		hitPoints = newHP;
	}

};

int main()
{
	player c1("Cloud", 100, 9999);
	cout << c1.getName() << endl;
	cout << c1.getHP() << endl;
	cout << c1.getStr() << endl;
	
	cin.get();

	return 0;
}
