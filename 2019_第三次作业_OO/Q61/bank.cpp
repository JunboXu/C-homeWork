#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<iomanip>
#include <stdio.h>
#include<Windows.h>

using namespace std;

vector<string> split(string input, string seperator) {
	vector<string> res;
	string cutPart = input + seperator;
	int firstPosition;
	while ((firstPosition = cutPart.find(seperator)) != -1)
	{
		res.push_back(cutPart.substr(0, firstPosition));
		cutPart = cutPart.substr(firstPosition + seperator.length());
	}
	return res;
}
void getTest() {
	string input;
	ofstream myout("F:\\bank.txt", ios::app);
	int i = 1;
	while (getline(cin, input))
	{
		myout << input << endl;
	}
	cin >> input;
	myout << "第" << i << "个用例：" << "done" << endl;
	i++;
	myout.close();
}

class Account {
private:
	int id;
	string owner;
	double balance;
	int type;//type 取值 0,1,2 创建对应类型的银行账号
	string description;
	vector<string> record;
	double interest;
public:
	void setInterest() {
		if (this->type==0)
		{
			this->interest = balance * 0.001;
		}

		else if (this->type == 1) {
			if (this->balance>1000)
			{
				this->interest = 1000 * 0.001 + (balance - 1000)*0.002;
			}
			else {
				this->interest = balance * 0.001;
			}
		}
		else if (this->type == 2) {
			if (this->balance<=1000)
			{
				this->interest = 0.02*balance;
			}
			else if ((this->balance <= 2000)&&(this->balance>1000)) {
				this->interest = 0.02 * 1000 + 0.05*(this->balance - 1000);
			}
			else if(this->balance>2000)
			{
				this->interest = 0.02 * 1000 + 0.05 * 1000 + (this->balance - 2000)*0.1;
			}
		}
	}
	double getInterest() {
		return this->interest;
	}
	int getId() {
		return this->id;
	}
	void setId(int i) {
		this->id = i;
	}
	string getOwner() {
		return this->owner;
	}
	void setOwner(string owner){
		this->owner = owner;
	}
	void deposit(double i) {
		this->balance += i;
		string midRecord = "deposit $"+to_string(i).substr(0, to_string(i).find(".")+3);
		this->record.push_back(midRecord);
		setInterest();
	}
	void withdraw(double i) {
		this->balance -= i;
		string midRecord = "withdrawal $" + to_string(i).substr(0, to_string(i).find(".") + 3);
		this->record.push_back(midRecord);
		setInterest();
	}
	double getBalance() {
		return this->balance;
	}
	int getType() {
		return this->type;
	}
	void setType(int i) {
		this->type = i;
		switch (i)
		{
		case 0:
			this->description = "Checking Account";
			break;
		case 1:
			this->description = "Savings Account";
			break;
		case 2:
			this->description = "Maxi-Savings Account";
			break;
		default:
			break;
		}
	}
	string getDescription() {
		return this->description;
	}
	vector<string> getRecord() {
		return this->record;
	}
};

class Customer {
private:
	string name;
	int accountAmount;
	vector<Account*> personalAccountsList;
public:
	int getAccountAmount(){
		return this->accountAmount;
	}
	void addAccount(Account *a) {
		this->personalAccountsList.push_back(a);
		this->accountAmount += 1;
	}
	vector<Account*> getAccountList() {
		return this->personalAccountsList;
	}
	string getName() {
		return this->name;
	}
	void setName(string n) {
		this->name = n;
	}
};

class Bank {
private:
	vector<Account*> allAccounts;
	vector<Customer*> allCustomers;
public:
	vector<Account*> getAllAccouts() {
		return this->allAccounts;
	}
	vector<Customer*> getAllCustomers() {
		return this->allCustomers;
	}
	void createAccount(int type) {
		Account *a=new Account();
		a->setType(type);
		a->setId(allAccounts.size());
		this->allAccounts.push_back(a);
	}
	void createCustomer(string nam) {
		Customer* c = new Customer();
		c->setName(nam);
		this->allCustomers.push_back(c);
	}
	Customer * findCustomerByName(string targetName) {
		for (int i = 0; i < allCustomers.size(); i++)
		{
			if (allCustomers[i]->getName()==targetName)
			{
				return allCustomers[i];
			}
		}
	}//问题：因为返回的是指针，所以对指针的内容进行的操作时可以直接改变该位置
	Account * findAccountById(int id) {
		for (int i = 0; i < allAccounts.size(); i++)
		{
			if (allAccounts[i]->getId() == id)
			{
				return allAccounts[i];
			}
		}
	}
	void addToCustomer(int accountId, string customerName) {
		Customer * c = findCustomerByName(customerName);
		Account *a = findAccountById(accountId);
		c->addAccount(a);
		a->setOwner(customerName);
	}
	void accountDeposit(int index, double amount) {
		if (amount <= 0)
		{
			cout << "amount must be greater than zero" << endl;
			return;
		}
		else {
			Account* a = findAccountById(index);
			a->deposit(amount);
		}
	}
	void accountWithdraw(int index, double amount) {
		Account* a = findAccountById(index);
		if (amount <= 0)
		{
			cout << "amount must be greater than zero" << endl;
			return;
		}
		if (a->getBalance() < amount)
		{
			cout << "sumTransactions must be greater than zero" << endl;
		}
		else {
			a->withdraw(amount);
		}
	}
	double sumTransactions(int index) {
		Account* a = findAccountById(index);
		cout << setiosflags(ios::fixed)<<setprecision(1) << a->getBalance()<<endl;
		return a->getBalance();
	}
	int numberOfAccount(string name) {
		Customer *c = findCustomerByName(name);
		return c->getAccountAmount();
	}
	void customsum() {
		cout << "Customer Summary" << endl;
		for (int i = 0; i < this->allCustomers.size(); i++)
		{
			Customer *c = allCustomers[i];
			string s = " account)";
			if (c->getAccountAmount()>=2)
			{
				s = " accounts)";
			}
			cout << " - " << c->getName() << " (" << c->getAccountAmount()<<s<< endl;
		}
	}
	double totalInterestEarned(string name) {
		Customer* c = findCustomerByName(name);
		vector<Account*> listAccOfThisMan = c->getAccountList();
		double interestEarned=0;
		for (int i = 0; i < listAccOfThisMan.size(); i++)
		{
			interestEarned += listAccOfThisMan[i]->getInterest();
		}
		//cout << setiosflags(ios::fixed) << setprecision(1) << interestEarned << endl;
		return interestEarned;
	}
	double banktotalInserstPaid() {
		vector<Customer*> list = this->allCustomers;
		double sum=0;
		for (int i = 0; i < list.size(); i++)
		{
			sum += this->totalInterestEarned(list[i]->getName());
		}
		cout << setiosflags(ios::fixed) << setprecision(1) << sum << endl;
		return sum;
	}
	void getStatement(string name) {
		cout << "Statement for " << name << endl;
		cout << endl;
		Customer * c = findCustomerByName(name);
		vector<Account*> accountList = c->getAccountList();
		double allSum = 0;
		for (int i = 0; i <accountList.size() ; i++)
		{
			Account *a = accountList[i];
			cout << a->getDescription() << endl;
			allSum += a->getBalance();
			vector<string> record = a->getRecord();
			for (int k = 0; k < record.size(); k++)
			{
				cout << "  " << setiosflags(ios::fixed) << setprecision(2) << record[k] << endl;
			}
			cout << "Total $" << setiosflags(ios::fixed) << setprecision(2) << a->getBalance() << endl << endl;;
		}
		cout << "Total In All Accounts $" << setiosflags(ios::fixed) << setprecision(2) << allSum << endl;
	}
};

void start() {
	Bank bank;
	string instruction;
	getline(cin, instruction);
	//getchar();
	while (instruction != "end") {
		vector<string> instructionItem = split(instruction, " ");
		if (instructionItem[0]=="createAccount") {
			bank.createAccount(stoi(instructionItem[1]));
		}
		else if (instructionItem[0] == "createCustomer") {
			bank.createCustomer(instructionItem[1]);
		}
		else if (instructionItem[0] == "addToCustomer") {
			bank.addToCustomer(stoi(instructionItem[1]), instructionItem[2]);
		}
		else if (instructionItem[0] == "accountDeposit") {
			bank.accountDeposit(stoi(instructionItem[1]), stod(instructionItem[2]));
		}
		else if (instructionItem[0] == "accountWithdraw")
		{
			bank.accountWithdraw(stoi(instructionItem[1]), stod(instructionItem[2]));
		}
		else if (instructionItem[0] == "sumTransactions")
		{
			bank.sumTransactions(stoi(instructionItem[1]));
		}
		else if (instructionItem[0] == "numberOfAccount") {
			bank.numberOfAccount(instructionItem[1]);
		}
		else if (instructionItem[0] == "totalInterestEarned") {
			double interestEarn=bank.totalInterestEarned(instructionItem[1]);
			cout << setiosflags(ios::fixed) << setprecision(1) << interestEarn << endl;
		}
		else if (instructionItem[0] == "getStatement") {
			bank.getStatement(instructionItem[1]);
		}
		else if (instructionItem[0] == "banktotalInserstPaid") {
			bank.banktotalInserstPaid();
		}
		else if (instructionItem[0] == "customsum") {
			bank.customsum();
		}

		getline(cin, instruction);
	}
}

int main() {
	//getTest();

	start();
	system("PAUSE");
	//Sleep(500);
	return 0;
}