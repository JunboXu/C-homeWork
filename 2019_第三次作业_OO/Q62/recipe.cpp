#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Food {
private:
	double carbohydrate;
	double protein;
	double Df;
	double fat;
protected:
	Food(double car, double pro, double df, double fa) {
		carbohydrate = car;
		protein = pro;
		Df = df;
		fat = fa;
	}
public:
	double getCar() {
		return carbohydrate;
	}
	double getPro() {
		return protein;
	}
	double getDf() {
		return Df;
	}
	double getFat() {
		return fat;
	}
};

class Rice :public Food {
public:
	Rice() :Food(16.2, 3.7, 0, 0) {};
};

class Beef :public Food {
public:
	Beef() :Food(1.8, 17.5, 0, 7.2) {}
};

class Bro :public Food {
public:
	Bro() :Food(0.2, 0.4, 3.6, 0) {}
};

class Oat :public Food {
public:
	Oat() :Food(12.3, 5.7, 7.3, 3) {}
};

class Duck :public Food {
public:
	Duck() :Food(6.9, 9, 0, 9.3) {}
};

class Cab :public Food {
public:
	Cab():Food(2.1, 0.8, 4.3, 0) {}
};

class Diet {
private:
	vector<Food*> dietList;
	double sumCar = 0;
	double sumPro = 0;
	double sumDF = 0;
	double sumFat = 0;
	double min_car = 13.3;
	double min_pro = 13.5;
	double min_DF = 3.3;
	double max_fat = 10.3;
public:
	Diet() {}
	void if_healthy() {
		for (int i = 0; i < dietList.size(); i++)
		{
			sumCar += dietList[i]->getCar();
			sumDF += dietList[i]->getDf();
			sumPro += dietList[i]->getPro();
			sumFat += dietList[i]->getFat();
		}
		if ((sumCar >= min_car) && (sumDF >= min_DF) && (sumPro >= min_pro) && (sumFat <= max_fat))
		{
			cout << "healthy" << endl;
		}
		else {
			cout << "unhealthy" << endl;
		}
	}
	vector<Food*> getList() {
		return dietList;
	}
	Diet& operator+=(Food &food) {
		this->dietList.push_back(&food);
		return *this;

	}
};

void start() {
	int id1, id2, id3;
	cin >> id1 >> id2 >> id3;
	int l[3];
	l[0] = id1;
	l[1] = id2;
	l[2] = id3;
	Food *food;
	Diet diet;
	vector<Food*> list = diet.getList();
	if ((id1 > 6 || id1 < 1) || (id2 > 6 || id2 < 1) || (id3 > 6 || id3 < 1))
	{
		cout << -1 << endl;
	}
	else {		
	
		for (int i = 0; i < 3; i++)
		{

			switch (l[i])
			{
			case 1:
				food = new Rice();
				diet += *food;
				break;
			case 2:
				food = new Beef();
				diet += *food;
				break;

			case 3:
				food = new Bro();
				diet += *food;
				break;

			case 4:
				food = new Oat();
				diet += *food;
				break;

			case 5:
				food = new Duck();
				diet += *food;
				break;

			case 6:
				food = new Cab();
				diet += *food;
				break;

			default:
				break;

			}
			//diet+= *food;
		}
		diet.if_healthy();
	}
}

int main() {
	start();
	//system("PAUSE");
	return 0;
}