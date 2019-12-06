#include<stdio.h>
#include<vector>
#include<string>
#include<iostream>
using namespace std;
vector<string> split(string str, const string pattern) {
	str += pattern;
	string::size_type pos;
	vector<string> result;
	for (int i = 0; i < str.size(); i++) {
		pos = str.find(pattern, i);
		if (pos < str.size() && pos != str.npos) {
			string temp = str.substr(i, pos - i);
			result.push_back(temp);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
};
bool stringEquals(const string string1, const string string2) {
	if (string1.size() != string2.size()) {
		return false;
	}
	else {
		for (int i = 0; i < string1.size(); i++) {
			if (string1[i] != string2[i]) {
				return false;
			}
		}
	}
	return true;
}
int stringToInt(string x) {
	string temp = x.substr(1, x.size() - 1);
	int no = stoi(temp);
	return no;
}
class Car {
protected:
	int pos;//�������ʼλ����Ϣ
	int occupyLength;//ռ�ó���
	int parkTime;//ͣ��ʱ��
	int waitTime;//�Ⱥ�ʱ��
	float fee;//ͣ����;
	string id;//id
	int remainTime;//�Ⱥ��ͣ������ʱ
public:
	void setPos(int po) { pos = po; };
	int getPos() { return pos; };
	string getId() { return id; };
	float getFee() { return fee; };
	//���ǲ���Ҫ�Ƴ����У�1�Ļ�������
	int getLength() { return occupyLength; };
	void decreaseTime() { remainTime--; };
	int getRemTime() { return remainTime; };
	void setRemainTime(int flag) {//����ʣ��ȴ�ʱ��
		if (flag == 1) { remainTime = parkTime; }
		else
		{
			remainTime = waitTime;
		}
	};
};
class SCar :public Car {
public:
	//����*2��ֹ��һ��1.5 ����ûʲô�ý��͵�
	SCar(string no) { this->id = no; this->occupyLength = 2; this->parkTime = 3; this->waitTime = 1; this->fee = 1.5; };
};
class MCar :public Car {
public:
	//����*2��ֹ��һ��1.5 ����ûʲô�ý��͵�
	MCar(string no) { this->id = no; this->occupyLength = 3; this->parkTime = 2; this->waitTime = 2; this->fee = 3; };
};
class LCar :public Car {
public:
	//����*2��ֹ��һ��1.5 ����ûʲô�ý��͵�
	LCar(string no) { this->id = no; this->occupyLength = 4; this->parkTime = 1; this->waitTime = 3; this->fee = 4.5; };
};
class Sunny {
	float totalFee = 0.0;
	int totalLength;
	int pLength = 0;//��ռ�õĳ���
	int pNum = 0;
	vector<Car *> parkVect;
	int wNum = 0;//ʵ�ʵȴ�����
	vector<Car *> waitVect;
public:
	Sunny(int size) { this->totalLength = size * 2; };
	//����ͣ���⣬����ͣ������ʱ��ʼ����ջ��ͣ������++������++
	void addPark(Car * car) {
		car->setRemainTime(1);
		parkVect.push_back(car);
		pNum++;
		pLength += car->getLength();
	};
	//����ȴ����У������ȴ�����ʱ��ʼ����ջ���ȴ�����++
	void addWait(Car * car) {
		car->setRemainTime(2);
		waitVect.push_back(car);
		wNum++;
	};
	void flushPark(int pos) {//ͣ��������ǰ��λ
		pLength -= parkVect[pos]->getLength();
		for (int i = pos; i < parkVect.size() - 1; i++) {
			parkVect[i] = parkVect[i + 1];
		}
		parkVect.pop_back();
		pNum--;
	};
	void flushWait(int pos) {//�ȴ�������ǰ��λ
		for (int i = pos; i < waitVect.size() - 1; i++) {
			waitVect[i] = waitVect[i + 1];
		}
		waitVect.pop_back();
		wNum--;
	};
	//�����ʱ�����״̬���,ɾ����Ϊ0�ĳ�
	void checkState() {
		vector<int> pPos;
		vector<int>wPos;
		for (int i = 0; i < parkVect.size(); i++) {
			if (parkVect[i]->getRemTime() == 0) {//����0˵��������
				pPos.push_back(i);
				this->totalFee += parkVect[i]->getFee();
			}
		}
		for (int i = 0; i < waitVect.size(); i++) {
			if (waitVect[i]->getRemTime() == 0) {//����0˵��������
				wPos.push_back(i);
			}
		}
		while (pPos.size() != 0) {
			flushPark(pPos.back());
			pPos.pop_back();
		}
		while (wPos.size() != 0) {
			flushWait(wPos.back());
			wPos.pop_back();
		}
	}
	void allMoveOn() {
		for (auto ele : parkVect) {
			ele->decreaseTime();
		}
		for (auto ele : waitVect) {
			ele->decreaseTime();
		}
	}
	bool canAfford(int length) {
		return (this->pLength + length) <= this->totalLength;
	}
	//����addPark��addWait����������ֱ�Ӽ���ͣ���⻹�ǵȴ�����
	void addFunc(Car * car) {
		if (canAfford(car->getLength()) && (waitVect.size() == 0)) {
			addPark(car);
		}
		else {
			addWait(car);
		}
	}
	void printAllCar() {
		if ((parkVect.size() == 0) && (waitVect.size() == 0)) {
			return;
		}
		if (parkVect.size() == 0) {
			cout << "null" << endl;
			return;
		}
		for (int i = 0; i < parkVect.size(); i++) {
			cout << parkVect[i]->getId();
			if (i != parkVect.size() - 1) {
				cout << ' ';
			}
		}
		cout << endl;
	}
	void adjust() {
		if (waitVect.size() == 0) { return; }//Ϊ0˵������Ҫ����
		if (canAfford(waitVect[0]->getLength())) {
			addPark(waitVect[0]);
			flushWait(0);
		}

	}
	void start() {
		string command;
		getline(cin, command);
		while (!stringEquals(command, "end")) {
			vector<string> cmdPieces = split(command, " ");
			printAllCar();
			checkState();
			adjust();
			if (stringEquals(cmdPieces[1], "S")) {
				addFunc(new SCar(cmdPieces[2]));
			}
			else if (stringEquals(cmdPieces[1], "M")) {
				addFunc(new MCar(cmdPieces[2]));
			}
			else {
				addFunc(new LCar(cmdPieces[2]));
			}
			allMoveOn();
			getline(cin, command);
		}
		while ((parkVect.size() != 0) || (waitVect.size() != 0)) {
			printAllCar();
			checkState();
			adjust();
			allMoveOn();
		}
		cout << "null" << endl;
		cout << totalFee << endl;
		//system("pause");
	}
};
//����Ļ���Ҫ��pLength������顣�������ռλ��
class Rainy {
	float totalFee = 0.0;
	int* position;
	int size;
	vector<Car *> parkVect;
	vector<Car *> waitVect;
public:
	Rainy(int siz) {
		position = new int[siz * 2];
		size = siz;
		for (int i = 0; i < size * 2; i++) {
			position[i] = -1;
		}
	};
public:
	//ռ��postion�����е�λ�ã�����parkVect�е�˳��
	void addPark(Car* car, int pos) {
		parkVect.push_back(car);
		for (int i = parkVect.size() - 2; i >= 0; i--) {
			if (parkVect[i]->getPos() > pos) {//˵���ں���
				parkVect[i + 1] = parkVect[i];
				parkVect[i] = car;
			}
			else {
				break;
			}
		}
		car->setPos(pos);
		car->setRemainTime(1);
		int no = stringToInt(car->getId());
		for (int k = 0; k < car->getLength(); k++) {
			position[pos + k] = no;
		}
	}
	void addWait(Car* car) {
		car->setRemainTime(2); waitVect.push_back(car);
	}
	//�������£�ȥ������postion��ռ�õ�λ�ã����ҵ���parkVect
	void flushPark(int posInParkVec) {
		Car * current = parkVect[posInParkVec];
		int begin = current->getPos();
		for (int i = 0; i < current->getLength(); i++) {
			position[begin + i] = -1;
		}
		for (int i = posInParkVec; i < parkVect.size() - 1; i++) {
			parkVect[i] = parkVect[i + 1];
		}
		parkVect.pop_back();
	};
	void flushWait(int pos) {
		for (int i = pos; i < waitVect.size() - 1; i++) {
			waitVect[i] = waitVect[i + 1];
		}
		waitVect.pop_back();
	}
	void checkState() {
		vector<int> pPos;
		vector<int>wPos;
		for (int i = 0; i < parkVect.size(); i++) {
			if (parkVect[i]->getRemTime() == 0) {//����0˵��������
				pPos.push_back(i);
				this->totalFee += parkVect[i]->getFee();
			}
		}
		for (int i = 0; i < waitVect.size(); i++) {
			if (waitVect[i]->getRemTime() == 0) {//����0˵��������
				wPos.push_back(i);
			}
		}
		while (pPos.size() != 0) {
			flushPark(pPos.back());
			pPos.pop_back();
		}
		while (wPos.size() != 0) {
			flushWait(wPos.back());
			wPos.pop_back();
		}
	}
	void allMoveOn() {
		for (auto ele : parkVect) {
			ele->decreaseTime();
		}
		for (auto ele : waitVect) {
			ele->decreaseTime();
		}
	}
	int canAfford(int cLength) {
		int lens = 0;
		for (int i = 0; i < size * 2; i++) {
			if (position[i] == -1) {
				lens++;
			}
			else {
				lens = 0;
			}
			if (lens >= cLength) {
				return (i + 1 - cLength);
			}
		}
		return -1;//��ú�0����

	}
	void addFunc(Car * car) {
		int posit = canAfford(car->getLength());
		if ((posit != -1) && (waitVect.size() == 0)) {
			addPark(car, posit);
		}
		else {
			addWait(car);
		}
	}
	void printAllCar() {
		if ((parkVect.size() == 0) && (waitVect.size() == 0)) {
			return;
		}
		if (parkVect.size() == 0) {
			cout << "null" << endl;
			return;
		}
		for (int i = 0; i < parkVect.size(); i++) {
			cout << parkVect[i]->getId();
			if (i != parkVect.size() - 1) {
				cout << ' ';
			}
		}
		cout << endl;
	}
	void adjust() {
		if (waitVect.size() == 0) { return; }
		int pos = canAfford(waitVect[0]->getLength());
		while (pos != -1) {
			addPark(waitVect[0], pos);
			flushWait(0);
			if (waitVect.size() == 0) {
				break;
			}
			pos = canAfford(waitVect[0]->getLength());
		}
	}
	void start() {
		string command;
		getline(cin, command);
		while (!stringEquals(command, "end")) {
			vector<string> cmdPieces = split(command, " ");
			printAllCar();
			checkState();
			adjust();
			if (stringEquals(cmdPieces[1], "S")) {
				addFunc(new SCar(cmdPieces[2]));
			}
			else if (stringEquals(cmdPieces[1], "M")) {
				addFunc(new MCar(cmdPieces[2]));
			}
			else {
				addFunc(new LCar(cmdPieces[2]));
			}
			allMoveOn();
			getline(cin, command);
		}
		while ((parkVect.size() != 0) || (waitVect.size() != 0)) {
			printAllCar();
			checkState();
			adjust();
			allMoveOn();
		}
		cout << "null" << endl;
		cout << totalFee << endl;
		system("pause");
	}
};
int main() {
	string command;
	getline(cin, command);
	vector<string> pieces = split(command, " ");
	if (stringEquals(pieces[1], "sunny")) {
		Sunny* sun = new Sunny(stoi(pieces[0]));
		sun->start();
	}
	else {
		Rainy* rain = new Rainy(stoi(pieces[0]));
		rain->start();
	}
};