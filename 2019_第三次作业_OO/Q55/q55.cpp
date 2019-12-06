#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<Windows.h>
using namespace std;


void getTest() {
	string input;
	ofstream myout("F:\\drinks.txt", ios::app);
	while (getline(cin, input))
	{
		myout << input << endl;
	}
	cin >> input;
	myout << "done" << endl;
	myout.close();
}

class Drinksstore {
protected:
	Drinksstore() {}
	Drinksstore(const Drinksstore &);

public:
	static Drinksstore* getstoreHouse() {
		return drinkSt == NULL ? drinkSt = new Drinksstore() : drinkSt;
	}
	//static void destroy() { delete drinkSt; drinkSt = NULL;}
	void addDrink(int i,int num) {
		switch (i)
		{
		case 1:
			coffeeNum+=num;
			break;
		case 2:
			milkNum += num;
			break;
		case 3:
			teaNum += num;
			break;
		case 4:
			beerNum += num;
			break;
		default:
			break;
		}
		kucun += num;
	}
	void subDrink(int i,int num) {
		switch (i)
		{
		case 1:
			coffeeNum -= num;
			break;
		case 2:
			milkNum -= num;
			break;
		case 3:
			teaNum -= num;
			break;
		case 4:
			beerNum -= num;
			break;
		default:
			break;
		}
		kucun -= num;
	}
	int getKuncun() {return kucun;}
	int getCoffeeNum() { return coffeeNum; }
	int getMilkNum() { return milkNum; }
	int getTeaNum() { return teaNum; }
	int getBeerNum() { return beerNum; }
private:
	static Drinksstore *drinkSt;
	int kucun=0;
	int coffeeNum=0;
	int milkNum = 0;
	int teaNum = 0;
	int beerNum = 0;

};

Drinksstore * Drinksstore::drinkSt =NULL;

class Drink {
public:
	virtual void buy() = 0;
};

class Coffee :public Drink {
public:
	Coffee() {};
	void buy() {

		cout << name << ":"<<price << endl;
	}
protected:
	int price=5;
	string name = "coffee";
};
class Milk :public Drink {
public:
	Milk() {};
	void buy() {

		cout << name << ":" << price << endl;
	}
protected:
	int price = 4;
	string name = "milk";
};
class Tea :public Drink {
public:
	Tea() {};
	void buy() {

		cout << name << ":" << price << endl;
	}
protected:
	int price = 3;
	string name = "tea";
};
class Beer :public Drink {
public:
	Beer() {};
	void buy() {
		cout << name << ":"<<price << endl;
	}
protected:
	int price=6;
	string name = "beer";
};

class DrinkFactory {
public:
	Drink* create(int i) {
		switch (i) {
		case 1:
			return new Coffee();
			break;
		case 2:
			return new Milk();
			break;
		case 3:
			return new Tea();
		case 4:
			return new Beer();
		}
	}

};


void add() {
	Drinksstore *drinkSt = Drinksstore::getstoreHouse();
	int dType, dAmount;
	cin >> dType >> dAmount;
	if ((drinkSt->getKuncun()) > (10-dAmount))
	{
		cout << "DrinkOverflow"<<endl;
		//添加失败抛出异常，打印DrinkOverFlow；
	}
	else {
		drinkSt->addDrink(dType, dAmount);
	}
}

void buyOperation() {
	Drinksstore *drinkSt = Drinksstore::getstoreHouse();
	DrinkFactory df =DrinkFactory();
	int dType;
	cin >> dType;
	switch (dType)
	{
	case 1:{
		Drink *coff = df.create(1);
		if (drinkSt->getCoffeeNum() <= 0)
		{
			cout << "coffee is not found" << endl;
		}
		else {
			coff->buy();
			drinkSt->subDrink(dType, 1);
		}
		break;
	}
	case 2:{
		Drink *milk = df.create(2);
		if (drinkSt->getMilkNum() <= 0)
		{
			cout << "milk is not found" << endl;
		}
		else {
			milk->buy();
			drinkSt->subDrink(dType, 1);
		}
		break;
	}
	case 3:{
		Drink *tea = df.create(3);
		if (drinkSt->getTeaNum() <= 0)
		{
			cout << "tea is not found" << endl;
		}
		else {
			tea->buy();
			drinkSt->subDrink(dType, 1);
		}
		break;
	}
	case 4: {
		Drink *beer = df.create(4);
		if (drinkSt->getBeerNum() == 0)
		{
			cout << "beer is not found" << endl;
		}
		else {
			beer->buy();
			drinkSt->subDrink(dType, 1);
		}
		break;
	}
	default:
		break;
	}
}

void start() {
	int commandType;
	cin >> commandType;
	while (commandType != 3) {
		switch (commandType)
		{
		case 1:
			add();
			break;
		case 2:
			buyOperation();
			break;
		case 3:
			break;
		default:
			break;
		}
		cin >> commandType;
	}
}

int main() {
	start();
	//getTest();
	//Sleep(1000);
	system("PAUSE");
	return 0;
}