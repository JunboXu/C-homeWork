#include<iostream>
#include<istream>

using namespace std;

class  GPU {
protected:
	int price;
	int hashRate;
	double income;
public:
	virtual void calculate() {};
	void setPirce(int p) {
		price = p;
	}
	int getPrice() {
		return price;
	}
	void setHashRate(int hR) {
		hashRate = hR;
	}
	int gethashRate() {
		return hashRate;
	}
	double getincome() {
		calculate();
		return income;
	}
	friend istream &operator>>(istream &input, GPU& gpu) {
		input >> gpu.price >> gpu.hashRate;
		return input;
	}
	GPU() {};
	~GPU() {};
};

class GPU1 : public GPU {
public:
	void calculate() {
		income = hashRate * 0.02 - consumeDaily;
	}
protected:
	double consumeDaily=16.2;

};
class GPU2 : public GPU {
public:
	void calculate() {
		income = hashRate * 0.02 - consumeDaily;
	}
protected:
	double consumeDaily = 28.8;

};
class GPU3 : public GPU {
public:
	void calculate() {
		income = hashRate * 0.02 - consumeDaily;
	}
protected:
	double consumeDaily = 19.44;

};



void start() {
	GPU1 g1;
	GPU2 g2;
	GPU3 g3;

	cin >> g1 >> g2 >> g3;

	int costAll = g1.getPrice() + g2.getPrice() + g3.getPrice();
	double earnDaily = (double)(g1.getincome() + g2.getincome() + g3.getincome());
	int day = 0;
	if (earnDaily>0)
	{
		while ((day*earnDaily < costAll)) {
			day++;
		}
		cout << day;
	}
	else {
		cout << -1;
	}
}

int main() {
	start();
//	system("PAUSE");
	return 0;
}