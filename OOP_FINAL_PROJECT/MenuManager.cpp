#include "MenuManager.h"

void MenuManager::createPerson(long id , Person& p,Worker& w,char tav)
{
	string Name, LastName;
	Date dtmp;
	cin >> dtmp;
	cout << "Please insert name: ";
	cin >> Name;
	cout << "Please insert last name: ";
	cin >> LastName;
	Person tmp2(Name, LastName, id, dtmp);
	p = tmp2;

	if (tav =='w')
	{ 
	float salary;
	cout << "Please insert salary: ";
	cin >> salary;
	Worker tmp(Name, LastName, id, dtmp,salary);
	w = tmp;
	}
}

void MenuManager::AddFine()
{
	long id;
	cout << "Enter customer id: ";
	cin >> id;
	int idx=isExist(CustomerArray, id);
	if (idx == -1)
	{
		cout << "Customer not found";
		return;
	}
	string data,phone;
	Document* d1;
	double price;
	Date dtmp;
	cout << "What is the subject of the letter?" << endl;
	char tmp[MAX_SIZE];
	fseek(stdin, 0, SEEK_SET);
	cin.getline(tmp, MAX_SIZE);
	char* subject = new char[strlen(tmp) + 1];
	strcpy(subject, tmp);

	cout << "What is the fine data? " << endl;
	fseek(stdin, 0, SEEK_SET);
	getline(cin, data);	
	cout << "What is the price? " << endl;
	cin >> price;
	cout << "Please insert last day payment details " << endl;
	cin>>dtmp;
	cout << "Which police station? " << endl;
	fseek(stdin, 0, SEEK_SET);
	cin.getline(tmp, MAX_SIZE);
	char* stname = new char[strlen(tmp) + 1];
	strcpy(stname, tmp);
	cout << "What is the police station phone number? " << endl;
	cin >> phone;

	d1 = new Fine(subject, 0, id, data, price, dtmp,stname,phone);
	d1->setWords(d1->wordsCounter());

	CustomerArray[idx] += d1;	//push fine to person
}



void MenuManager::TrackUpdate()
{
	bool flag = false;
	int idx;
	char tav;
	vector<Document*> v;
	int CsArraySize= CustomerArray.size();
	int DocsSize;
	string update;
	cout << "Please insert tracking number:";
	cin >> idx;
	for (int i = 0; i < CsArraySize; i++)
	{
		v = CustomerArray[i].getDocs();
		DocsSize= v.size();
		for (int k = 0; k < DocsSize; k++)
		{
			TrackedLetter* tmp = dynamic_cast<TrackedLetter*>(v[k]);
			if (tmp)
			{
				if (tmp->getTrackingNum() == idx)
				{
					if (tmp->isArrived())
					{
						cout << "Package already arrived,can not update" << endl;
						return;
					}
					cout << "What is current location of the letter?" << endl;

					while (!flag)
					{
						fseek(stdin, 0, SEEK_SET);
						getline(cin, update);
						try { tmp->changeStatus(update); }
						catch (const char* str) { cout << str; continue; }
						flag = true;
					}
					flag = false;
					cout << "Delivery arrived?: (1) Yes (0) No ";
					while (!flag)
					{
						cin >> tav;
						try { tmp->setArrived(tav); }			//throw exception
						catch (const char* str) { cout << str; continue; }
						return;
					}
				}
			}
		}
	}
	cout << "Letter with tracking number: " << idx << " not in data base" << endl;
}

void MenuManager::DeleteCostumer()
{
	long tmpId;
	cout << "Please insert customer id:" << endl;
	cin >> tmpId;
	int idx = isExist(CustomerArray, tmpId);
	if (idx == -1)
	    {
		cout << "No customer found with this id." << endl;
		return;
		}
	vector<Person>::iterator itr = CustomerArray.begin();
	itr += idx;
	CustomerArray[idx].clearDoc();
	CustomerArray.erase(itr);
	CustomerArray.shrink_to_fit();
}

bool MenuManager::ReadFromFile(const char* str)
{
	char tmp[256];
	ifstream MyReadFile;
	MyReadFile.open(str, ios::in);
	if (!MyReadFile.is_open()) { cout << "Can't open the file " << "'" << str << "'" << endl; return false; }
	int size = Jump2Class(MyReadFile,tmp);
	char tav;
	bool status;
	int amount,day, year,empId,tracknum;
	float salary;
	double price;
	long id,rid,sid;
	char month[3];
	string name,lastName,data,stname,phone,tracking;
	for (int i = 0; i < size; i++)		////read person array
	{
		MyReadFile >> id >> name >> lastName >> amount>>tav>>day>>month>>year>>tav;
		CustomerArray.push_back(Person(name, lastName, id, Date(day, month, year)));
	}
	size = Jump2Class(MyReadFile,tmp);
	for (int i = 0; i < size; i++)		////read workers array
	{
		MyReadFile >> id >> name >> lastName >> amount >> tav >> day >> month >> year >> tav>>salary;
		WorkersArray.push_back(Worker(name, lastName, id, Date(day, month, year),salary));
	}
	Document* doc;

	size = Jump2Class(MyReadFile, tmp);		////read fines
	for (int i = 0; i < size; i++)
	{
		MyReadFile >> rid >> id >> name >> amount;
		MyReadFile.get(tav);
		while (MyReadFile.get(tav))
		{
			if (tav != ',')
			data += tav;
			else break;
		}
		MyReadFile.get(tav);

		MyReadFile >> price >> tav >> day >> month >> year >> tav >> stname >> phone;
		doc = new Fine(string2char(name), amount, rid, data, price, Date(day, month, year), string2char(stname), phone);
		data.clear();
		CustomerArray[isExist(CustomerArray, rid)] += doc;
	}
	
	size = Jump2Class(MyReadFile, tmp);
	for (int i = 0; i < size; i++)			////read letters
	{
		MyReadFile >> rid >> id >> name >> amount;
			MyReadFile.get(tav);
		while (MyReadFile.get(tav))
		{
			if (tav != ',')
				data += tav;
			else break;
		}
		MyReadFile.get(tav);
		MyReadFile >> sid ;
		doc = new Letter(string2char(name), amount, sid,rid, data);
		data.clear();
		CustomerArray[isExist(CustomerArray, rid)] += doc;
	}

	size = Jump2Class(MyReadFile, tmp);
	for (int i = 0; i < size; i++)		////read trackedletters
	{
		MyReadFile >> rid >> id >> name >> amount;
		MyReadFile.get(tav);
		while (MyReadFile.get(tav))
		{
			if (tav != ',')
				data += tav;
			else break;
		}
		MyReadFile.get(tav);
		MyReadFile >> sid >> status >> tracknum;
		MyReadFile.get(tav);
		while (MyReadFile.get(tav))
		{
			if (tav != '.')
				tracking += tav;
			else break;
		}
	doc = new TrackedLetter(string2char(name), amount, sid, rid, data,tracknum,status,tracking);
	data.clear();
	tracking.clear();
		CustomerArray[isExist(CustomerArray, rid)] += doc;
	}
}

bool MenuManager::WriteToFile(const char* str)
{
	ofstream MyReadFile;
	MyReadFile.open(str, ios::trunc);
	if (!MyReadFile.is_open()) { cout << "Can't open the file " << "'" << str << "'" << endl; return false; }
	Fine fine;
	Letter letter;
	TrackedLetter tletter;
	int size = CustomerArray.size();
	MyReadFile << '\n';
	int NumOfFine=0, NumOfLetter=0,NumOftrackedLetter =0;
	PrintPeople(CustomerArray, MyReadFile);			//write person to file
	PrintPeople(WorkersArray, MyReadFile);			//write workers to file

	DocsCounter(fine, NumOfFine);					//count amount of fines
	PrintDocs(fine, MyReadFile, NumOfFine);			//write fines to file

	DocsCounter(tletter, NumOftrackedLetter);		//count amount of trackedletters
	DocsCounter(letter, NumOfLetter);				//count amount of letters
	NumOfLetter -= NumOftrackedLetter;				//start process of writing letters to file
	int docSize;
	Letter* ptr;
	vector<Document*> dtmp;
	MyReadFile << "class Letter- <" << NumOfLetter << "> in system\nRecipientId, Id number, Name, Words count, Data, SenderId:" << endl;
	for (int i = 0; i < size; i++)
	{
		dtmp = CustomerArray[i].getDocs();
		docSize = dtmp.size();

		for (int k = 0; k < docSize; k++)
		{
			ptr = dynamic_cast<Letter*>(dtmp[k]);
			if (ptr&&ptr->father())
				MyReadFile << *ptr << endl;
		}
	}
	MyReadFile << endl;

	PrintDocs(tletter, MyReadFile, NumOftrackedLetter);		//write trackedletters to file
	

	MyReadFile.close();
	return true;

}

MenuManager::MenuManager()
{
	WorkersArray.push_back(Worker("CEO", "Admin", 111111, Date(1, "1", 1950), 1000000));
	CustomerArray.push_back(Person("CEO", "Admin", 111111, Date(1, "1", 1950)));

}

MenuManager::MenuManager(const char* FileName)		//constructor for build system from file 
{
	ReadFromFile(FileName);
}

MenuManager::MenuManager(vector<Person> C, vector<Worker> W) : CustomerArray(C), WorkersArray(W)
{
}

MenuManager::MenuManager(vector<Worker> W): WorkersArray(W)
{
}

void MenuManager::startProgram()  //menu
{
	int choice;
	cout<< "Welcome to mail system."<<endl<<"To continute, please select your choice from the following list:"<<endl;
	cout <<"Please identify yourself : (1) Customer (2) Worker "<< endl;
	cout << "To end the program press (3)" << endl;

	cout << "your choice:";
	cin >> choice;
	switch (choice)
	{
	case 1: CustomerMenu();
		break;
	case 2: 
		long tmpId;
		cout << "Please insert your id number:" << endl;
		cin >> tmpId;
			if (isExist(WorkersArray, tmpId)!=-1)
			{
				cout << "Access granted:" << endl;
				WorkerMenu();
			}
			else
			{ 
				cout << "Access denied:" << endl;
				startProgram();
			}
	case 3:
		if (WriteToFile("OUT.TXT"))
		cout << "\nData saved successfully";
		DeleteData();
		cout << "\nSystem data erased successfully";
		exit(0);


	default:
		cout << "your choice is illegal"<<endl<<"============================="<<endl<<endl;
		startProgram();
	}
}

void MenuManager::CustomerMenu() //menu helper
{
	long tmpId;
	int op;
	cout << "Please insert your id number:" << endl;
	cin >> tmpId;
	int idx=isExist(CustomerArray, tmpId);
	if (idx==-1)
	{ 
	cout << "ID not found, please contact the workers for register." << endl;
	startProgram();
	}
	int choice;
	cout << "Please select an option from the following list:" << endl;
	cout << "(1) Send letter\n(2) Pay fine\n";
	cout << "(3) Back to previous menu " << endl;
	cout << "your choice:";
	cin >> choice;
	cout << endl;
	switch (choice)
	{
	case 1:
		cout << "Which letter do you like to send (1) Normal (2) With tracking" << endl;
		op = Ask4Choice(1, 2);
		SendLetter(tmpId,op);
		break;
	case 2: PayFine(idx);
		break;
	case 3: startProgram();
			break;
	default:
		cout << "your choice is illegal" << endl << "=============================" << endl << endl;
		break;
	}
	startProgram();



}


void MenuManager::WorkerMenu()	//menu helper
{
	int choice;
	cout << "Please select an option from the following list:" << endl;
	cout <<"(1) Add customer\n(2) Add worker\n(3) Add fine to customer\n(4) Update Letter delivery status\n(5) Print customer database\n(6) Print workers database\n(7) Delete customer" << endl;
	cout << "(8) Return to general Menu " << endl;
	cout << "your choice:";
	cin >> choice;
	cout <<endl;

	switch (choice)
	{
		case 1: addGeneral(CustomerArray,'c');
		break;
		case 2: addGeneral(WorkersArray,'w');
			break;
		case 3: AddFine();
			break;
		case 4:TrackUpdate();
			break;
		case 5: PrintData(CustomerArray);
			break;
		case 6: PrintData(WorkersArray);
			break;
		case 7: DeleteCostumer();
			break;
		case 8: startProgram();
			break;

	default:
		cout << "your choice is illegal" << endl << "=============================" << endl << endl;
		break;
	}
	WorkerMenu();
}

void MenuManager::SendLetter(long sId,int op)
{	
	int rId,idx;
	cout << "Please insert recipient id :" << endl;
	cin >> rId;
	idx = isExist(CustomerArray, rId);
	if (idx == -1)
	{
		cout << "The id you provide is not in data base. please invite the person to our service"<<endl<< "=============================" << endl;
		return;
	}
	createLetter(rId, sId, op,idx);
}	
	
void MenuManager::createLetter(long rId,long sId,int op,int idx)
{
	string data;
	Document* d1;
	cout << "What is the subject of the letter?" << endl;
	char tmp[MAX_SIZE];
	fseek(stdin, 0, SEEK_SET);
	cin.getline(tmp, MAX_SIZE);
	char* subject = new char[strlen(tmp) + 1];
	strcpy(subject, tmp);

	cout << "What do you like to send?" << endl;
	fseek(stdin, 0, SEEK_SET);
	getline(cin, data);
	if (op == 1)
		d1 = new Letter(subject, 0, sId, rId,data);
	else 	//////option 2//////
	d1 = new TrackedLetter(subject, 0, sId, rId, data);

	d1->setWords(d1->wordsCounter());
	CustomerArray[idx] += d1;
	if (op == 2)
	{
		TrackedLetter* ptr = dynamic_cast<TrackedLetter*>(d1);
		cout << "your tracking number is: " << ptr->getTrackingNum() << endl;
	}

	return;
}

void MenuManager::PayFine(int ctr)
{
	vector<Document*> tmp = CustomerArray[ctr].getDocs();
	vector<Document*>::iterator itr = tmp.begin();
	vector<Document*>::iterator itrEnd = tmp.end();
	int i = 0,k=0;
	int Choice;
	while (itr != itrEnd)
	{
		Fine* ptr = dynamic_cast<Fine*>(*itr);
		if (ptr)
		{
			i++;
			cout << "Fine number:" << i << endl;
			tmp[k]->show();
			cout  << endl;
			cout << "Would you like to pay the fine?\t (1)Yes / \ (0)No" << endl;
			Choice = Ask4Choice(1,0);
			if (Choice == 1)
			{	
				ptr->setPrice(0);
				
			}
		}
		itr++,k++;
	}
	if (i == 0)
		cout << "There are no fines" << endl;
	else 	CustomerArray[ctr].refreshFine();		// delete fines from person's docsarray
}

int MenuManager::Ask4Choice(int tmp1, int tmp2)		// user desicion helper 
{
		int input;
		cin >> input;

		while (input != tmp1 && input != tmp2)
		{
			cout << "Wrong input please insert\t " << tmp1 << "/" << tmp2 << endl;
			cin >> input;
		}
		return input;
}

int MenuManager::Jump2Class(ifstream& MyReadFile,char* tmp)  //reading from file helper
{
	MyReadFile.getline(tmp, 256);
	MyReadFile.getline(tmp, 256, '<');
	MyReadFile.getline(tmp, 256, '>');
	int size = atoi(tmp);
	MyReadFile.getline(tmp, 256);
	MyReadFile.getline(tmp, 256);
	return size;
}

char* MenuManager::string2char(string str)  //convert string to char
{
	int size = str.size();
	char* string = new char[size + 1];
	for (int i = 0; i < size; i++)
	{
		string[i] = str[i];
	}
	string[size] = '\0';
	return string;
}

void MenuManager::DeleteData()
{
	int size = CustomerArray.size();
	for (int i = 0; i < size; i++)
	{
		CustomerArray[i].clearDoc();
	}
}

ostream& operator<<(ostream& out,  MenuManager& p)
{
	out << "Here is all customers in the system\n";
	p.PrintData(p.CustomerArray, out);
	out << "Here is all workers in the system\n";
	p.PrintData(p.WorkersArray, out);
	return out;
}


