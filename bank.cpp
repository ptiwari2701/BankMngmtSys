#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<stdlib.h>
#include<vector>
#include<sstream>
#include<string.h>
using namespace std;
class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
public:
	void create_account();
	void show_account() const;
	void modify();
	void dep(int);
	void draw(int);
	void report() const;
	int retacno() const;
	int retdeposit() const;
	char rettype() const;
	string retname() const;
};

void account::create_account()
{
	fstream outFile;
	outFile.open("account.csv",ios::out|ios::app);
	cout<<"\nEnter The account No. :";
	cin>>acno;
	cout<<"\n\nEnter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin>>deposit;
	cout<<"\n\n\nAccount Created..";
	outFile<<acno<<","<<name<<","<<type<<","<<deposit<<'\n';
	outFile.close();
}

void account::show_account() const
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
}


void account::modify()
{
	cout<<"\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nModify Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nModify Balance amount : ";
	cin>>deposit;
}

	
void account::dep(int x)
{
	deposit+=x;
}
	
void account::draw(int x)
{
	deposit-=x;
}
	
void account::report() const
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}

	
int account::retacno() const
{
	return acno;
}

int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}

string account::retname() const
{
	return name;
}

void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);
void intro();

int main()
{
	char ch;
	int num;
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. NEW ACCOUNT";
		cout<<"\n\n\t02. DEPOSIT AMOUNT";
		cout<<"\n\n\t03. WITHDRAW AMOUNT";
		cout<<"\n\n\t04. BALANCE ENQUIRY";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t07. MODIFY AN ACCOUNT";
		cout<<"\n\n\t08. EXIT";
		cout<<"\n\n\tSelect Your Option (1-8) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4': 
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			modify_account(num);
			break;
		 case '8':
			cout<<"\n\n\tThanks for using bank managemnt system";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
}

void write_account()
{
	account ac;
	ac.create_account();
}

void display_sp(int n)
{
	account ac;
	bool flag=false;
	fstream in;
	in.open("account.csv",ios::in);
	vector<string> row;
	string line,word,temp;
	in.seekp(0);
	if(!in)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";
	ostringstream str1;
	str1 << n;
	string geek=str1.str();
	while(in.good()){
		row.clear();
		getline(in,line);
		stringstream s(line);
		while(getline(s,word,',')){
			row.push_back(word);
		}
		if(geek == row[0]){
			flag=true;
			cout<<row[0]<<" "<<row[1]<<" "<<row[2]<<" "<<row[3];
			break;
		}
	}
	in.close();
		if(flag==false)
			cout<<"\n\nAccount number does not exist";
}

void modify_account(int n)
{
	bool found=false;
	account ac;
	fstream File,File2;
	File.open("account.csv",ios::in|ios::app);
	File2.open("account1.csv",ios::out);
	vector<string> row;
	string line,word,temp;
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	ostringstream str1;
	str1 << n;
	string geek=str1.str();
	while(!File.eof() && found == false){
		row.clear();
		getline(File,line);
		stringstream s(line);
		while(getline(s,word,',')){
			row.push_back(word);
		}
		if(geek == row[0]){
			found=true;
			cout<<"\nAccount No. : "<<row[0];
			ac.modify();
			row[1]=ac.retname();
			row[2]=ac.rettype();
			row[3]=ac.retdeposit();
			if(!File.eof()){
				for(int i=0;i<row.size()-1;i++){
					File2<<row[i]<<",";
				}
				File2<<row[row.size()-1]<<"\n";
			}
		}
		else{
			if(!File.eof()){
				for(int i=0;i<row.size()-1;i++){
					File2<<row[i]<<",";
				}
				File2<<row[row.size()-1]<<"\n";
			}
		}
		if(File.eof())
			break;
	}
	if(found==false)
		cout<<"\n\n Record Not Found ";
	File.close();
	File2.close();
	remove("account.csv");
	rename("account1.csv","account.csv");
}

void delete_account(int n)
{
	account ac;
	fstream File;
	fstream File2;
	File.open("account.csv",ios::in);
	File2.open("account1.csv",ios::out);
	vector<string> row;
	string line,word,temp;
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	ostringstream str1;
	str1 << n;
	string geek=str1.str();
	while(!File.eof()){
		row.clear();
		getline(File,line);
		stringstream s(line);
		while(getline(s,word,',')){
			row.push_back(word);
		}
		if(geek == row[0]){
			cout<<"\nAccount No. : "<<row[0];
		}
		else{
			if(!File.eof()){
				for(int i=0;i<row.size()-1;i++){
					File2<<row[i]<<",";
				}
				File2<<row[row.size()-1]<<"\n";
			}
		}
		if(File.eof())
			break;
	}
	File.close();
	File2.close();
	remove("account.csv");
	rename("account1.csv","account.csv");
	cout<<"\n\n\tRecord Deleted ..";
}

void display_all()
{
	account ac;
	fstream File,file;
	File.open("account.csv",ios::in);
	file.open("account.csv",ios::in);
	vector<string> row;
	string line,word,temp;
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME           Type  Balance\n";
	cout<<"====================================================\n";
	int count=0;
	while (getline(file,line))
	{
		count++;
	}
	while(!File.eof() && count!=0){
		row.clear();
		getline(File,line);
		stringstream s(line);
		while(getline(s,word,',')){
			row.push_back(word);
		}
		for(int i=0;i<row.size()-1;i++){
			cout<<row[i]<<"\t\t";
		}
		cout<<row[row.size()-1]<<"\n";
		if(File.eof())
			break;
		count--;
	}
	File.close();
}

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File,File2;
	File.open("account.csv",ios::in|ios::out);
	File2.open("account1.csv",ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	vector<string> row;
	string line,word,temp;
	ostringstream str1;
	str1 << n;
	string geek=str1.str();
	while(!File.eof() && found==false)
	{
		row.clear();
		getline(File,line);
		stringstream s(line);
		while(getline(s,word,',')){
			row.push_back(word);
		}
		if(row[0]==geek)
		{
			cout<<"\nAccount No. : "<<row[0];
			File2<<row[0]<<",";
			cout<<"\nAccount Holder Name : ";
			cout<<row[1];
			File2<<row[1]<<",";
			cout<<"\nType of Account : "<<row[2];
			File2<<row[2]<<",";
			cout<<"\nBalance amount : "<<row[3];
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				stringstream g(row[3]);
				int x=0;
				g >> x;
				int sum = x+amt;
				string str;
				ostringstream temp;
				temp << sum;
				str = temp.str();
				row[3]=str;
			}
			if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
				stringstream g(row[3]);
				int x=0;
				g >> x;
				int bal = x-amt;
				string str;
				ostringstream temp;
				temp << bal;
				str = temp.str();
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficience balance";
				else
					row[3]=str;
			}
			cout<<"\n\n\t Record Updated";
			found=true;
			File2<<row[3]<<"\n";
	       }
         }
	File.close();
	File2.close();
	remove("account.csv");
	rename("account1.csv","account.csv");
	if(found==false)
		cout<<"\n\n Record Not Found ";
}