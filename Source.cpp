#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
#include <cctype>
#include <iomanip>
#include <Windows.h>
#include <string>
#include <time.h>
using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
SYSTEMTIME systemTime;


//function declaration
string upper(string);
void Main_Menu(string);
void CinemaManagement(int);
void AdministratorMenu(int);
//Cinema_Hall function
void CinemaHallManagement(int);
void ReadCinemaHallRecord(int&);
void CinemaSeatPrinting(int,int);
void HallSeatPrinting(int, int, int);
bool AddCinemaHall(bool);
void ModifyCinemaHall(int&);
void DeleteCinemaHall(int&);
void LoadCinemaHallRecord(int&);
void AddCinemaSeat(int&);
void DeleteCinemaSeat(int&);
void ConfirmAddCinemaSeat(int, int, int);
//movie function
void MovieManagement(int);
void AddMovie(int&);
void ReadMovieRecord(int&);
void LoadMovieRecord(int&);
void ModifyMovie(int&);
void DeleteMovie(int&);
void MoviePrinting(int&,int);
bool MovieStartDetection(string);
void MovieEndDetection(string,int,double,int&,int&);
void MovieRecordIntoStruct(string, string, string, string, double, int,int&);
//employee function
void EmployeeManagement(int);
void ReadEmployeeRecord(int&);
void LoadEmployeeRecord(int&);
void AddEmployee(int&);
void DeleteEmployee(int&);
void ModifyEmployee(int&);
bool EmployeeID(string,int&);
//Movie details
void MovieDetails(int);
//Purchase now
void PurchaseNow(int);
void BookMovie(int);
void TimeChecking(int, int, int, int, int, int, int&);
void DateRecord(int, int, int, int, int, int, int&);
void BookSeatPrinting(int, int, int);
//refresh the cinema hall
void CinemaRefresh(int);
//open member info files
void OpenMemberDetails(int&);
void OpenPurchaseHistory();
//Membership details
void MembershipDetails();
void UserLogIn();
void UserRegister();
//structure declaration
struct mapping_seats
{//cinema hall	//a set of column and row = 1 data
	int hall, data, row[70], column[70];
}unavailable[50];
struct PurchasedSeatType
{
	int data,purchased_row[50],purchased_column[50];
};
struct CinemaHallSeatType
{
	int data,row[70],column[70];
};
struct movie
{
	string movie_id,movie_name,description,movie_time;
	double movie_length;
	int movie_hall;
	PurchasedSeatType seats;
	CinemaHallSeatType backup;
	
}movie[100];
struct employee {
	string id,name,department,position;
	int password;
}employee[100];
string department[5] = { "INFORMATION TECHNOLOGY","HUMAN RESOURCES","FINANCE","MARKETING","BUSINESS" };
struct MemberDetails
{
	string Details_user, Details_name, Details_password, Details_join, Details_phone, Details_email, Details_status, Details_point;
}Member[100];
struct PurchaseHistory
{
	string Purchase_user, Purchase_name, Purchase_password, Purchase_movie[5], Purchase_date[5], Purchase_pax[5], Purchase_food[5];
}Purchase[100];

//Main Menu
int main()
{
	bool decision = true;
	string input;
	int selection;
	do{
		system("cls");
		Main_Menu("MAIN");
		cout << "\t\t\tPlease input your selection >>> ";
		getline(cin, input);
		selection=stoi (input);
		switch (selection)
		{
		case(1)://Movie details
		{
			MovieDetails(selection);
			break;
		}
		case(2)://f&b
		{
			break;
		}
		case(3)://purchase now
		{
			PurchaseNow(selection);
			break;
		}
		case(4)://membership details
		{
			MembershipDetails();
			break;
		}
		case(5)://administrator menu
		{
			AdministratorMenu(5);
			break;
		}
		case(6)://exit
		{
			decision = false;
			break;
		}
		default://reinput
		{
			cout << "\t\t\tInvalid input found" << endl;

			break;
		}
		}
	} while (decision);


	system("pause");
	return 0;
}
//change string to uppercase
string upper(string uppercase)
{
	for (int i = 0; i < uppercase.size(); i++)
		uppercase[i] = toupper(uppercase[i]);
	return uppercase;
}
//Administrator Menu (havent implement employee function)
void AdministratorMenu(int option)
{
	int index;
	bool decision = true, access = true;
	string id;
	do{
		system("cls");
		int record = 0,password,found=0;
		ReadEmployeeRecord(record);
		cout << "\n\n\n\n\n\n\n\n\n\t\t\tid=ew001 and password=12345 for lecturer used only!!"<<endl;
		cout << "\n\t\t\tPlease input your ADMIN ID <E>xit >>";
		cin >> id;
		id = upper(id);
		if (id == "E")
			break;
		cout << "\t\t\tPlease input your password >>>";
		cin >> password;
		if(id.length()==5)
		{ 
			for (int i = 0; i < record; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (password == employee[i].password && id[j] == employee[i].id[j])
					{
						index = i;
						found++;
					}
				}
			}
		}
		if (found == 0 || !(id.length() == 5))
		{
			cout << "\t\t\tPlease reinput your id and password " << endl;
			Sleep(1000);
		}
		else if(found==5)
			access = false;
	} while (access);
	while(decision&&!(id=="E"))
	{	
		int selection;
		system("cls");
		cout << "\n\n\n" << endl;
		cout << "\t\t\t<1> Cinema Refreshing" << endl;
		cout << "\t\t\t<2> Cinema management" << endl;
		cout << "\t\t\t<3> Food & Beverages management" << endl;
		cout << "\t\t\t<4> Membership Management" << endl;
		cout << "\t\t\t<5> Employee management" << endl;
		cout << "\t\t\t<6> Exit " << endl;
		cout << "\t\t\tPlease input your selection >>> ";
		cin >> selection;
		switch (selection)
		{
		case(1):
		{
			CinemaRefresh(selection);
			break;
		}
		case(2)://Cinema management
		{
			CinemaManagement(selection);
			break;
		}
		case(3)://F&B management
		{
			break;
		}
		case(4)://Membership managements
		{
			break;
		}
		case(5)://Employee management
		{
			EmployeeManagement(selection);
			break;
		}
		case(6):
		{
			decision = false;
			break;
		}
		default://reinput
		{
			cout << "\t\t\tInvalid input found" << endl;
			break;
		}
		}
	}
}
//Cinema Management
void CinemaManagement(int option)
{
	int selection;
	bool decision = true;
	do
	{	
		cout << "\n\n\n\t\t\t<1> Movies management " << endl;
		cout << "\t\t\t<2> Cinema Hall modification " << endl;
		cout << "\t\t\t<3> Exit " << endl;
		cout << "\t\t\tPlease input your selection >>> ";
		cin >> selection;
		switch (selection)
		{
		case(1)://Movie management
		{
			MovieManagement(selection);
			break;
		}
		
		case(2)://Cinema Hall Modification
		{
			CinemaHallManagement(selection);
			break;
		}
		case(3)://exit
		{
			decision = false;
			break;
		}
		default://reinput
		{
			cout << "\t\t\tInvalid input found" << endl;
			break;
		}
		}
	} while (decision);
}
//Cinema Hall Page
void CinemaHallManagement(int option)
{
	int selection;
	bool decision = true;
	do
	{
		system("cls");
		int record = 0;
		bool result = false;
		ReadCinemaHallRecord(record);
		cout << "\n\n\n" << string(100, char(61)) << "\n\n\n";
		for (int w = 0; w < record; w++)
		{
			cout << "\n\n\t\t\t\t HALL " << unavailable[w].hall << "\n\n";
			CinemaSeatPrinting(w,99);
		}

		cout << string(100, char(61)) << "\n\n\n";
		cout << "\t\t\t<1> Add Cinema Hall" << endl;
		cout << "\t\t\t<2> Modify Cinema Hall space" << endl;
		cout << "\t\t\t<3> Delete Cinema Hall" << endl;
		cout << "\t\t\t<4> Exit" << endl;
		cout << "\t\t\tInput your selection >>> ";
		cin >> selection;

		switch (selection)
		{
		case(1)://Add cinema Hall
		{
			result = AddCinemaHall(result);
			if (result)
			{
				record++;
				unavailable[record - 1].hall = record;
				unavailable[record - 1].data = 0;
				unavailable[record - 1].row[0] = 0;
				unavailable[record - 1].column[0] = 0;
				LoadCinemaHallRecord(record);
			}
			break;
		}
		case(2)://Modify Cinema Seat
		{
			ModifyCinemaHall(record);
			break;
		}
		case(3)://Delete Cinema Hall
		{
			DeleteCinemaHall(record);
			break;
		}
		case(4)://exit
		{
			decision = false;
			break;
		}
		default://reinput
		{
			cout << "\t\t\tInvalid input found" << endl;
			break;
		}
		}
	} while (decision);
}
void ReadCinemaHallRecord(int& record)
{
	ifstream infile;
	infile.open("seatcontrol.txt");
	if (infile.fail())
	{
		cout << "unable to open the file";
	}
	else
	{
		int i = 0;
		while (!infile.eof())
		{
			infile >> unavailable[i].hall;
			infile >> unavailable[i].data;
			infile.ignore();
			if (unavailable[i].data > 0)
			{
				for (int j = 0; j < unavailable[i].data; j++)
					infile >> unavailable[i].row[j];
				for (int j = 0; j < unavailable[i].data; j++)
					infile >> unavailable[i].column[j];
			}
			else
			{
				infile >> unavailable[i].row[0];
				infile >> unavailable[i].column[0];
			}
			
			infile.ignore();
			i++;
			record++;
		}
	}
	infile.close();
}
void LoadCinemaHallRecord(int& record)
{
	ofstream outfile;
	outfile.open("seatcontrol.txt");
	for (int i = 0; i < record; i++)
	{
		outfile << unavailable[i].hall << endl;
		outfile << unavailable[i].data << endl;
		if (unavailable[i].data > 0)
		{
			for (int j = 0; j < unavailable[i].data; j++)
			{
				if (j > 0)
					outfile << " ";
				outfile << unavailable[i].row[j];
			}
			outfile << endl;
			for (int j = 0; j < unavailable[i].data; j++)
			{
				if (j > 0)
					outfile << " ";
				outfile << unavailable[i].column[j];
			}

		}
		else
		{
			outfile << unavailable[i].row[0] << endl;
			outfile << unavailable[i].column[0];
		}
		if (i != record - 1)
			outfile << endl;
	}
	outfile.close();
}
//print selected cinema seat mapping
void CinemaSeatPrinting(int w,int f)
{
	for (int i = 0; i < 10; i++)
	{
		cout << "\t\t\t\t\t";
		cout << i;
		if (i == 0)
		{
			for (int j = 1; j < 15; j++)
			{
				if (j == 2 || j == 12)
					cout << setw(2) << j << " ";
				else
					cout << setw(2) << j;
			}
			cout << endl;
		}
		else
		{
			for (int j = 1; j < 3; j++)
			{
				if (f == 99)
					HallSeatPrinting(w, i, j);
				else
					BookSeatPrinting(w, i, j);

			}
			cout << " ";
			for (int j = 3; j < 13; j++)
			{
				if (f == 99)
					HallSeatPrinting(w, i, j);
				else
					BookSeatPrinting(w, i, j);
			}
			cout << " ";
			for (int j = 13; j < 15; j++)
			{
				if (f == 99)
					HallSeatPrinting(w, i, j);
				else
					BookSeatPrinting(w, i, j);;
			}
			cout << endl;
		}

	}
}
//check availability of seat
void HallSeatPrinting(int w, int i, int j)
{
	int checking = 1;
	if (unavailable[w].data != 0)
	{
		for (int z = 0; z < unavailable[w].data; z++)
		{
			if (i == unavailable[w].row[z] && j == unavailable[w].column[z])
			{
				cout << setw(2) << "X";
				checking = 0;
			}
		}
	}
	if (checking)
		cout << setw(2) << "A";
}
//add cinema hall
bool AddCinemaHall(bool result) 
{
	char confirms;
	bool decision = true;
	do
	{
		cout << "Do you want to add a new cinema hall <Y>es or <N>o >>> ";
		cin >> confirms;
		confirms = toupper(confirms);
		if (confirms == 'Y' || confirms == 'N')
			decision = false;

	} while (decision);
	if (confirms == 'Y')
		return true;
	else
		return false;
}
void ModifyCinemaHall(int& record)
{
	int selection;
	bool decision = true;
	do {
		cout << "\t\t\t<1> Add Cinema Unavailable Seat" << endl;
		cout << "\t\t\t<2> Delete Cinema Unavailable Seat" << endl;
		cout << "\t\t\t<3> Exit" << endl;
		cout << "\t\t\tInput your selection >>> ";
		cin >> selection;
		switch (selection)
		{
		case(1)://	Add
		{
			AddCinemaSeat(record);
			break;
		}
		case(2)://Delete
		{
			DeleteCinemaSeat(record);
			break;
		}
		case(3)://Exit
		{
			decision = false;
			break;
		}
		default://reinput
		{
			cout << "\t\t\tInvalid input found" << endl;

			break;
		}
		}

	} while (decision);


}
void DeleteCinemaHall(int& record)
{
	int number;
	cout << "Please input the cinema hall number >>>";
	cin >> number;

	if (number > 0 && number <= record)
	{
		for (int i = 0; i < record; i++)
		{
			if (unavailable[i].hall == number)
			{
				for (int j = i; j < record; j++)
				{
					unavailable[j].hall = unavailable[j + 1].hall;
					unavailable[j].data = unavailable[j + 1].data;
					for (int z = 0; z < unavailable[j].data; z++)
					{
						unavailable[j + 1].row[z] = unavailable[j].row[z];
						unavailable[j + 1].column[z] = unavailable[j].column[z];
					}
				}
			}
		}
		record--;
		cout << "successfully deleted..." << endl;
		LoadCinemaHallRecord(record);
	}
	else
		cout << "no cinema hall found" << endl;
}
void AddCinemaSeat(int& record)
{
	int number;
	char continued;
	cout << "\t\t\tInput the number of cinema hall >>>";
	cin >> number;
	if (number > 0 && number <= record)
	{
		bool decision = true;
		do {
			int row, column;
			number -= 1;
			CinemaSeatPrinting(number,99);
			cout << "\t\t\tInput the row that you want to modify >>>";
			cin >> row;
			cout << "\t\t\tInput the column that you want to modify >>>";
			cin >> column;
			if (unavailable[number - 1].data > 0)
			{
				int found = 0;
				for (int i = 0; i < unavailable[number - 1].data; i++)
				{
					if (row > 10 || column > 14)
					{
						found++;
						cout << "\t\t\tplease ensure row and column within the range: 0 < row < 10 and 0 < column < 15" << endl;
						cout << "\t\t\tPlease reinput row and column" << endl;
						break;
					}
					else if (unavailable[number - 1].row[i] == row && unavailable[number - 1].column[i] == column)
					{
						found++;
						cout << "\t\t\tInput have found inside the system..." << endl;
						cout << "\t\t\tPlease reinput row and column" << endl;
						break;
					}
				}
				if (found == 0)
				{
					ConfirmAddCinemaSeat(number, row, column);
				}
				
			}
			else
				ConfirmAddCinemaSeat(number, row, column);
			LoadCinemaHallRecord(record);
			cout << "\t\t\tDo you want to continue <Y>es <N>o >>";
			cin >> continued;
			continued = toupper(continued);
			if (continued == 'N')
				decision = false;
		} while (decision);

	}
	else
		cout << "\t\t\tNo cinema hall found."<<endl;
}
void DeleteCinemaSeat(int& record)
{
	int number;
	cout << "\t\t\tPlease input the cinema hall number >>>";
	cin >> number;

	if (number > 0 && number <= record)
	{
		cout << "\n\n" << string(100, char(61)) << "\n\n";
		cout << "\t\t\tCinema hall " << number << endl;
		CinemaSeatPrinting(number - 1, 99);
		bool decision = true;
		do {
			char continued;
			int row, column;
			cout << "\t\t\tInput the row of the seat >> ";
			cin >> row;
			cout << "\t\t\tInput the column of the seat >> ";
			cin >> column;
			int found = 0;
			for (int i = 0; i < unavailable[number - 1].data; i++)
			{
				if (row > 10 || column > 14)
				{
					cout << "\t\t\tplease ensure row and column within the range: 0 < row < 10 and 0 < column < 15" << endl;
					break;
				}
				else if (unavailable[number - 1].row[i] == row && unavailable[number - 1].column[i] == column)
				{
					found++;
					char confirms;
					cout << "\t\t\tAre you confirm delete row " << row << " and " << "column " << column << " <Y>es <N>o  >>";
					cin >> confirms;
					confirms = toupper(confirms);					
					if (confirms == 'Y')
					{
						for (int j = i; j < unavailable[number - 1].data; j++)
						{
							unavailable[number - 1].row[j] = unavailable[number - 1].row[j + 1];
							unavailable[number - 1].column[j] = unavailable[number - 1].column[j + 1];
						}
						unavailable[number - 1].data -= 1;
						LoadCinemaHallRecord(record);
					}
					else
					{
						cout << "\t\t\tConfirmation Unsuccessful" << endl;
						cout << "\t\t\tPlease reinput the row and column" << endl;
					}
					break;
				}

			}
			if (found == 0)
				cout << "\t\t\tNo data found in system" << endl;
			cout << "\t\t\tDo you want to continue <Y>es <N>o >>";
			cin >> continued;
			continued = toupper(continued);
			if (continued == 'N')
				decision = false;
		} while (decision);
	}
	else
		cout << "\t\t\tno cinema hall seat found" << endl;
}
void ConfirmAddCinemaSeat(int number, int row, int column)
{
	char confirms;
	cout << "Are you confirm add row " << row << " and " << "column " << column << " <Y>es <N>o  >>";
	cin >> confirms;
	confirms = toupper(confirms);
	if (confirms == 'Y')
	{
		cout << "confirmation successful" << endl;
		unavailable[number - 1].data += 1;
		unavailable[number - 1].row[unavailable[number - 1].data - 1] = row;
		unavailable[number - 1].column[unavailable[number - 1].data - 1] = column;
		cout << "succesfully added" << endl;
	}
	else
	{
		cout << "Confirmation Unsuccessful" << endl;
		cout << "Please reinput the row and column" << endl;
	}
}

void MovieManagement(int option)
{
	bool decision = true;
	int selection;
	do {
		int record = 0;
		system("cls");
		ReadMovieRecord(record);
		MoviePrinting(record,99);
		cout << "\n\n\n\n\t\t\t<1> Add Movie " << endl;
		cout << "\t\t\t<2> Modify Movie " << endl;
		cout << "\t\t\t<3> Delete Movie " << endl;
		cout << "\t\t\t<4> exit " << endl;
		cout << "\t\t\tInput your selection >>> ";
		cin >> selection;
		switch (selection)
		{
		case(1):
		{
			AddMovie(record);
			break;
		}
		case(2):
		{
			ModifyMovie(record);
			break;
		}
		case(3):
		{
			DeleteMovie(record); 
			break;
		}
		case(4):
		{
			decision = false;
			break;
		}
		default:
		{
			cout << "\t\t\tInvalid input found" << endl; 
			break;
		}
		}
	} while (decision);
}
void ReadMovieRecord(int& record)
{
	ifstream infile;
	infile.open("movie.txt");
	if (infile.fail())
		cout << "unable to open the file";
	else
	{
		while (!infile.eof())
		{
			getline(infile,movie[record].movie_id);
			getline(infile, movie[record].movie_name);
			getline(infile, movie[record].description);
			getline(infile, movie[record].movie_time);
			infile >> movie[record].movie_length;
			infile >> movie[record].movie_hall;
			infile >> movie[record].seats.data;
			if (movie[record].seats.data > 0)
			{
				for (int i = 0; i < movie[record].seats.data; i++)
					infile >> movie[record].seats.purchased_row[i];
				for (int i = 0; i < movie[record].seats.data; i++)
					infile >> movie[record].seats.purchased_column[i];
			}
			else
			{
				infile >> movie[record].seats.purchased_row[0];
				infile >> movie[record].seats.purchased_column[0];

			}
			infile >> movie[record].backup.data;
			if (movie[record].backup.data > 0)
			{
				for (int i = 0; i < movie[record].backup.data; i++)
					infile >> movie[record].backup.row[i];
				for (int i = 0; i < movie[record].backup.data; i++)
					infile >> movie[record].backup.column[i];
			}
			else
			{
				infile >> movie[record].backup.row[0];
				infile >> movie[record].backup.column[0];

			}
			infile.ignore();
			record++;
		}
	}
	infile.close();

}
void LoadMovieRecord(int& record)
{
	ofstream outfile;
	outfile.open("movie.txt");
	for (int i = 0; i < record; i++)
	{
		outfile << movie[i].movie_id << endl << movie[i].movie_name << endl << movie[i].description << endl;
		outfile << movie[i].movie_time << endl << movie[i].movie_length << endl << movie[i].movie_hall << endl;
		outfile << movie[i].seats.data << endl;
		if (movie[i].seats.data > 0)
		{
			for (int j = 0; j < movie[i].seats.data; j++)
			{
				if (j > 0)
					outfile << " ";
				outfile << movie[i].seats.purchased_row[j];
			}
			outfile << endl;
			for (int j = 0; j < movie[i].seats.data; j++)
			{
				if (j > 0)
					outfile << " ";
				outfile << movie[i].seats.purchased_column[j];
			}
		}
		else
		{
			outfile << movie[i].seats.purchased_row[0] << endl;
			outfile << movie[i].seats.purchased_column[0] << endl;
		}
		outfile << movie[i].backup.data << endl;
		if (movie[i].backup.data > 0)
		{
			for (int j = 0; j < movie[i].backup.data; j++)
			{
				if (j > 0)
					outfile << " ";
				outfile << movie[i].backup.row[j];
			}
			outfile << endl;
			for (int j = 0; j < movie[i].backup.data; j++)
			{
				if (j > 0)
					outfile << " ";
				outfile << movie[i].backup.column[j];
			}
		}
		else
		{
			outfile << movie[i].backup.row[0]<<endl;
			outfile << movie[i].backup.column[0];
		}
		if (!(i == record - 1))
			outfile << endl;
	}
	outfile.close();
}
void AddMovie(int& record)
{
	bool decision = true;
	do {
		int hallrecord = 0;
		ReadCinemaHallRecord(hallrecord);
		char confirms;
		string movie_name, movie_id, description, movie_time;
		double movie_length;
		int movie_hall;
		bool checking = true;
		do {
			int found = 0;
			cout << "\t\t\tInput the movie id >>> ";
			cin >> movie_id;
			movie_id = upper(movie_id);
			for (int i = 0; i < record; i++)
			{
				if (movie_id == movie[i].movie_id)
					found++;
			}
			if (found == 0)
				checking = false;
			else
				cout << "\t\t\tMovie id found inside system" << endl;
		} while (checking);
		cin.ignore();
		cout << "\t\t\tInput the movie name >>> "; //same name allowed(same name,diff. movie
		getline(cin, movie_name);
		movie_name = upper(movie_name);
		
		cout << "\t\t\tInput the movie description >>> ";
		getline(cin, description);

		checking = true;
		do {
			cout << "\t\t\tInput the movie_time (24 Hours format XXXX) >>> ";
			cin >> movie_time;								
			bool result = MovieStartDetection(movie_time);
			if (result)
				checking = false;
			else
				cout << "\t\t\tinvalid input" << endl;
		} while (checking);

		checking = true;
		do {
			cout << "\t\t\tInput the movie_length in (Hours.minutes~~~ X.XX)>>> ";
			cin >> movie_length;							//2.60		2.50	(input)
			int hour = int(movie_length);					//2.00		2
			double minutes = (movie_length-hour) * 100;		//60		50
			if (minutes >= 60)
				cout << "invalid input" << endl;
			else
				checking = false;
		} while (checking);
		checking = true;
		do {

			int found = 0,hall=0;
			cout << "\t\t\tInput the movie_hall >>>";
			cin >> movie_hall;
			if (movie_hall<=hallrecord||movie_hall>0)
			{
				MovieEndDetection(movie_time, movie_hall, movie_length, found, record);
				if (found == 0)
					checking = false;
			}
			else
				cout << "\t\t\tPlease input again the movie hall" << endl;
		} while (checking);

		do{
			cout << "\t\t\tMovie ID: " << movie_id << endl;
			cout << "\t\t\tMovie Name: " << movie_name << endl;
			cout << "\t\t\tMovie description: " << description << endl;
			cout << "\t\t\tMovie time: " << movie_time << endl;
			cout << "\t\t\tMovie length H.MM: " << movie_length << endl;
			cout << "\t\t\tMovie hall: " << movie_hall << endl;
			cout << "\t\t\tAre you confirm? <Y>es <N>o >>> ";
			cin >> confirms;
			confirms = toupper(confirms);
			if (confirms == 'Y' || confirms == 'N')
			{
				checking = false;
			}
		}while(checking);

		if (confirms == 'Y')
		{
			MovieRecordIntoStruct(movie_id, movie_name, description, movie_time, movie_length, movie_hall, record);
		}
		char cont='w';
		while (!(cont == 'Y' || cont == 'N'))
		{
			cout << "\t\t\tDO you want to continue <Y>es <N>o >>> ";
			cin >> cont;
			cont = toupper(cont);
			if (!(cont == 'Y' || cont == 'N'))
				cout << "\t\t\tInvalid input" << endl;
		}
		if (cont == 'N')
			decision = false;
	} while (decision);

}
void ModifyMovie(int& record)
{
	//char confirms;
	string movie_name, movie_id, description, movie_time;
	double movie_length;
	int movie_hall,trace;
	bool decision = true;
	do {
		int found = 0,selection,storage;
		cout << "\t\t\tInput the Movie ID: ";
		cin >> movie_id;
		movie_id = upper(movie_id);
		for (int i = 0; i < record; i++)
		{
			if (movie_id == movie[i].movie_id)
			{
				found++;
				storage = i;
			}
		}
		if (found > 0)
		{
			cout << "\n\t\t\tWhich section you want to modify???" << endl;
			cout << "\t\t\t<1> Movie ID " << endl;
			cout << "\t\t\t<2> Movie Name" << endl;
			cout << "\t\t\t<3> Movie Description" << endl;
			cout << "\t\t\t<4> Movie Start time" << endl;
			cout << "\t\t\t<5> Movie length" << endl;
			cout << "\t\t\t<6> Cinema Hall of movie" << endl;
			cout << "\t\t\t<7> Exit" << endl;
			cout << "\t\t\tInput your selection" << endl;
			cin >> selection;
			switch (selection)
			{
			case(1):
			{
				int check = 0;
				cout << "\t\t\tInput new movie id: " << endl;
				cin >> movie_id;
				for(int i = 0; i < record; i++)
				{
					if (movie_id == movie[i].movie_id)
					{
						cout << "\t\t\tMovie ID was found inside the system" << endl;
						check++;
					}
				}
				if (check == 0)
				{
					movie[storage].movie_id = movie_id;
				}
				break;
			}
			case(2):
			{
				//assume that movie can have the same name !!!
				cout << "\t\t\tInput new movie name: " << endl;
				getline(cin, movie_name);
				movie[storage].movie_name = movie_name;
				break;
			}
			case(3):
			{
				//assume that description can have the same !!!
				cout << "\t\t\tInput new movie description: " << endl;
				getline(cin, description);
				movie[storage].description = description;
				break;
			}
			case(4):
			{

				cout << "\t\t\tInput the new start time in 24 Hours format (XXXX)>>> " << endl;
				cin >> movie_time;
				bool result = MovieStartDetection(movie_time);
				if (result)
				{
					MovieEndDetection(movie_time, movie[storage].movie_hall, movie[storage].movie_length, trace, record);
					if (trace == 0)
					{
						movie[storage].movie_time = movie_time;
					}
				}
				break;
			}
			case(5)://enter length (start time,movie hall)
			{
				cout << "\t\t\tEnter the new movie length in Hours.Minutes(X.XX) >>>";
				cin >> movie_length;
				MovieEndDetection(movie[storage].movie_time, movie[storage].movie_hall,movie_length, trace, record);
				if (trace == 0)
				{
					movie[storage].movie_length = movie_length;
				}
				break;
			}
			case(6)://movie hall( start time, end time)
			{
				cout << "\t\t\tEnter the new movie hall >>>";
				cin >> movie_hall;
				MovieEndDetection(movie[storage].movie_time,movie_hall, movie[storage].movie_length, trace, record);
				if (trace == 0)
				{
					movie[storage].movie_hall = movie_hall;
					movie[storage].seats.data = 0;
					movie[storage].seats.purchased_row[0] = 0;
					movie[storage].seats.purchased_column[0] = 0;
					movie[storage].backup.data = unavailable[storage].data;
					for (int i = 0; i < movie[storage].backup.data; i++)
						movie[storage].backup.row[i] = unavailable[storage].row[i];
					for (int i = 0; i < movie[storage].backup.data; i++)
						movie[storage].backup.column[i] = unavailable[storage].column[i];
				}
				break;
			}
			case(7):
			{
				decision = false;
				break;
			}
			default:
			{
				cout << "\t\t\tPlease reinput again!!!" << endl;
			}
			}
		
		}
		else
			cout << "\t\t\tinvalid input" << endl;
		LoadMovieRecord(record);
	} while (decision);
}
void DeleteMovie(int& record) 
{
	int found=0,index;
	string movie_id;
	bool decision = true;
	do {
		char confirm = 'W';
		cout << "\t\t\tInput the movie id you want to delete <E>xit >>>>";
		cin >> movie_id;
		movie_id = upper(movie_id);
		if (!(movie_id == "E"))
		{
			for (int i = 0; i < record; i++)
			{
				if (movie_id == movie[i].movie_id)
				{
					found++;
					index = i;
				}

			}
			if (found==1)
			{
				cout << "\t\t\tMovie ID found in system" << endl;
				while (!(confirm == 'Y' || confirm == 'N'))
				{
					cout << "\t\t\tFinal confirmation <Y>es <N>o >>>";
					cin >> confirm;
					if (!(confirm == 'Y' || confirm == 'N'))
						cout << "\t\t\tInvalid input" << endl;
				}
				if (confirm == 'Y')
				{
					cout << "\t\t\tLoading..." << endl;
					Sleep(3500);
					for (int j = index; j < record; j++)
					{
						movie[j].movie_id = movie[j + 1].movie_id;
						movie[j].movie_name = movie[j + 1].movie_name;
						movie[j].description = movie[j + 1].description;
						movie[j].movie_time = movie[j + 1].movie_time;
						movie[j].movie_length = movie[j + 1].movie_length;
						movie[j].movie_hall = movie[j + 1].movie_hall;
						movie[j].seats.data = movie[j + 1].seats.data;
						if (movie[j].seats.data > 0) {
							for (int z = 0; z < movie[j].seats.data; z++)
								movie[j].seats.purchased_row[z] = movie[j + 1].seats.purchased_row[z];
							for (int z = 0; z < movie[j].seats.data; z++)
								movie[j].seats.purchased_row[z] = movie[j + 1].seats.purchased_column[z];
						}
						else {
							movie[j].seats.purchased_row[0] = movie[j + 1].seats.purchased_row[0];
							movie[j].seats.purchased_row[0] = movie[j + 1].seats.purchased_column[0];
						}
						movie[j].backup.data = movie[j + 1].backup.data;
						if (movie[j].backup.data > 0)
						{
							for (int z = 0; z < movie[j].backup.data; z++)
								movie[j].backup.row[z] = movie[j + 1].backup.row[z];
							for (int z = 0; z < movie[j].backup.data; z++)
								movie[j].backup.column[z] = movie[j + 1].backup.column[z];
						}
						else {
							movie[j].backup.row[0] = movie[j + 1].backup.row[0];
							movie[j].backup.column[0] = movie[j + 1].backup.column[0];

						}
						decision = false;
						record--;
						LoadMovieRecord(record);

					}
				}
				else if (found == 0)
					cout << "\t\t\tInvalid movie id" << endl;
			}
		}
		else
			decision = false;
		
	} while (decision);

}
void MoviePrinting(int& record,int w)
{
	for (int i = 0; i < record; i++)
	{
		cout << "\n\t\t\tNo. " << i + 1 << endl;
		if (w == 99) //only print for admin
			cout << "\t\t\tMovie Id: " << movie[i].movie_id << endl;
		cout << "\t\t\tMovie Name: " << movie[i].movie_name << endl;
		cout << "\t\t\tMovie Description: " << movie[i].description << endl;
		cout << "\t\t\tMovie Time: " << movie[i].movie_time << endl;
		cout << "\t\t\tMovie Length H.MM: " <<fixed<<setprecision(2)<< movie[i].movie_length << endl;
		cout << "\t\t\tMovie Hall: " << movie[i].movie_hall << endl;
	}
}
bool MovieStartDetection(string movie_time)   //detect start time of movie
{													//sample output

	int checking = stoi(movie_time);				//2401      2061
	int integer_hours = checking / 100 * 100;		//2400		2000
	int remain = checking%integer_hours;			//1			61
	int size=int (movie_time.length());
	if (size > 4 || size < 4)
		return false;
	else if (integer_hours > 2400)		//if more than 24 hours (a day)
		return false;
	else if (remain > 60)		//if minutes more than 60
		return false;
	else
		return true;
}
void MovieRecordIntoStruct(string id,string name,string description,string time,double length,int hall,int &record)
{
	record++;
	movie[record - 1].movie_id = id;
	movie[record - 1].movie_name = name;
	movie[record - 1].description = description;
	movie[record - 1].movie_time = time;
	movie[record - 1].movie_length = length;
	movie[record - 1].movie_hall = hall;
	movie[record - 1].seats.data = 0;
	movie[record - 1].seats.purchased_row[0] = 0;
	movie[record - 1].seats.purchased_column[0] = 0;
	movie[record - 1].backup.data = unavailable[hall - 1].data;
	if (movie[record - 1].backup.data > 0)
	{
		for (int i = 0; i < movie[record - 1].backup.data; i++)
		{
			movie[record - 1].backup.row[i] = unavailable[hall - 1].row[i];
		}
		for (int i = 0; i < movie[record - 1].backup.data; i++)
		{
			movie[record - 1].backup.column[i] = unavailable[hall - 1].column[i];
		}
	}
	else
	{
		movie[record - 1].backup.row[0] = unavailable[hall - 1].row[0];
		movie[record - 1].backup.column[0] = unavailable[hall - 1].column[0];
	}
	LoadMovieRecord(record);
}
void MovieEndDetection(string movie_time,int movie_hall,double movie_length,int& found,int &record)
{
	double movie_end = stoi(movie_time) + (int(movie_length) * 100 + (movie_length - int(movie_length)) * 100);
	movie_end = int(movie_end);
	if (movie_end - movie_end / 100 * 100 > 60)
		movie_end = movie_end - 60 + 100;

	for (int i = 0; i < record; i++)
	{
		if (movie_hall == movie[i].movie_hall)
		{
			string time = movie[i].movie_time;					//1200
			int timing = stoi(time);
			int hour = int(movie_length);						//2.40=2
			int minutes = int((movie_length - hour) * 100);			//40
			int ending = timing + hour * 100 + minutes;			//1200+2*100+40
			int overflow = ending - int(ending / 100 * 100);
			if (overflow >= 60)
				ending = ending - 60 + 100;

			if (stoi(movie_time) >= timing && stoi(movie_time) <= ending)
			{
				found++;
			}
			else if (movie_end >= timing && movie_end <= ending)
			{
				found++;
			}
		}
	}
}

void EmployeeManagement(int)
{
	bool decision = true;
	do {
		system("cls");
		int record = 0,selection;
		ReadEmployeeRecord(record);
		cout <<"\n\n\n\t\t\t"<< string(161, char(61)) << endl;
		cout << "\t\t\t=" << setw(15) << "Employee ID" << setw(35) << "Employee Name" << setw(45) << "Department" << setw(40) << "Position" <<setw(20)<< "Password" << setw(5) << "=" << endl;
		cout << "\t\t\t" << string(161, char(61)) << endl;
		for (int i = 0; i < record; i++)
		{
			cout << "\t\t\t=" << setw(15) << employee[i].id << setw(35) << employee[i].name << setw(45) << employee[i].department << setw(40) << employee[i].position << setw(20) << employee[i].password <<setw(5)<<"="<< endl;
		}
		cout << "\t\t\t" << string(161, char(61)) << endl;
		cout << "\t\t\t<1> Add Employee " << endl;
		cout << "\t\t\t<2> Modify Employee" << endl;
		cout << "\t\t\t<3> Delete Employee" << endl;
		cout << "\t\t\t<4> Exit" << endl;
		cout << "\t\t\tInput your selection >>>";
		cin >> selection;
		switch (selection)
		{
		case(1):
		{
			AddEmployee(record);
			break;
		}
		case(2):
		{
			ModifyEmployee(record);
			break;
		}
		case(3):
		{
			DeleteEmployee(record);
			break;
		}
		case(4):
		{
			decision = false;
			break;
		}
		default:
		{
			cout << "\n\t\t\tinvalid input" << endl;
		}
		}
	} while (decision);
}
void ReadEmployeeRecord(int& record)
{
	ifstream details;
	details.open("employee.txt");
	if (details.fail())
		cout << "unable to open the file" << endl;
	else
	{
		while (!details.eof())
		{
			getline(details, employee[record].id);
			getline(details,employee[record].name);
			getline(details,employee[record].department);
			getline(details,employee[record].position);
			details >> employee[record].password;
			details.ignore();
			record++;
		}
	}
	details.close();
}
void LoadEmployeeRecord(int& record)
{
	ofstream details;
	details.open("employee.txt");
	if (details.fail())
		cout << "unable to open the file" << endl;
	else
	{
		for (int i = 0; i < record; i++)
		{
			details << employee[i].id << endl;
			details << employee[i].name << endl;
			details << employee[i].department << endl;
			details << employee[i].position << endl;
			if (i == record - 1)
				details << employee[i].password;
			else
				details << employee[i].password << endl;
		}
	}
	details.close();
}
void AddEmployee(int& record)
{
	bool decision = true;
	do {
		char confirms;
		bool checking = true,result;
		int password;
		string employee_id, employee_department, employee_name, employee_position;
		do {
			cout << "\t\t\tInput employee id ('EW' and 3 numerial numbers)>>>";
			cin >> employee_id;
			employee_id = upper(employee_id);
			result = EmployeeID(employee_id, record);
			if (result)
				checking = false;
			else
				cout << "\t\t\tPlease reinput again employee id" << endl;
		} while (checking);
		char cont;
		do {
			cin.ignore();
			cout << "\t\t\tInput employee name >>>";
			getline(cin, employee_name);
			employee_name = upper(employee_name);
			cout << "\t\t\tEmployee name, "<<employee_name<<"\n\t\t\tconfirmation <Y>es >>> ";
			cin >> cont;
			cont = toupper(cont);
		} while (!(cont == 'Y'));
		
		char conts;
		do {
			int number;
			for (int i = 0; i < 5; i++)
			{
				cout << "\t\t\t<"<<i+1<<"> " << department[i] << endl;
				
			}
			cout << "\t\t\tinput your selection >>>";
			cin >> number;
			employee_department = department[number - 1];
			cout << "\t\t\tThis employee under deparment of " << employee_department << endl;
			cout << "\t\t\tEmployee department confirmation <Y>es >>> ";
			cin >> conts;
			conts = toupper(conts);
		} while (!(conts=='Y'));

		char resume;
		do {
			cin.ignore();
			cout << "\t\t\tInput the position of employee >>> ";
			getline(cin,employee_position);
			employee_position = upper(employee_position);
			cout << "\t\t\tHer/His position is "<<employee_position<<endl;
			cout << "\t\t\tEmployee position confirmation <Y>es >>> ";
			cin >> resume;
			resume = toupper(resume);
		} while (!(resume == 'Y'));
		bool check = true;
		do {
			int found = 0;
			int number[4] = { 10000,20000,30000,40000 };
			int index = rand() % 4; //index=(0,1,2,3)
			int value = number[index] + rand() % 10000;//10000+XXXX
			for (int i = 0; i < record; i++)
			{
				if (value == employee[i].password)
					found++;
			}
			if (found == 0)
			{
				password = value;//password will be assigned automatically
				check = false;
			}
		} while (check);
		
		do {
			cout << "\t\t\tFinal confirmation <Y>es <N>o >>>";
			cin >> confirms;
			confirms = toupper(confirms);
			if (confirms == 'Y')
			{
				cout << "\t\t\tSuccessfully added employee named " << employee_name << "," << employee_id << endl;
				employee[record].id = employee_id;
				employee[record].name = employee_name;
				employee[record].department = employee_department;
				employee[record].position = employee_position;
				employee[record].password = password;
				record++;
				LoadEmployeeRecord(record);
				decision = false;
			}
			else if (confirms == 'N')
			{
				cout << "\t\t\tPending exit to employee page." << endl;
				Sleep(20);
				decision = false;
			}
		} while (!(confirms == 'Y' || confirms == 'N'));
	} while (decision);
	

}
void DeleteEmployee(int& record)
{
	string employee_id;
	char cont;
	do {
		int found = 0;
		cout << "\n\t\t\tInput the employee ID that want to delete >>>";
		cin >> employee_id;
		employee_id = upper(employee_id);
		for(int i=0;i<record;i++)
		{
			if (employee_id == employee[i].id)//must character by character
			{
				for (int j = i; j < record; j++)
				{
					found++;
					record--;
					employee[j].id = employee[j + 1].id;
					employee[j].name = employee[j + 1].name;
					employee[j].department = employee[j + 1].department;
					employee[j].position = employee[j + 1].position;
					employee[j].password = employee[j + 1].password;
					LoadEmployeeRecord(record);
				}
				break;
			}
		}
		if (found == 0)
			cout << "\t\t\tThe employee id did not found in the system" << endl;
		do {
			cout << "\t\t\tDo you want to continue <Y>es <N>o >> >";
			cin >> cont;
			cont = toupper(cont);
			if (!(cont == 'N' || cont == 'Y'))
				cout << "\t\t\tPlease input 'Y' or 'N' " << endl;
		} while (!(cont == 'N' || cont == 'Y'));
	} while (cont=='Y');
}
void ModifyEmployee(int& record)
{
	char cont;
	do {
		bool result;
		int index, found=0,selection,number=0;
		string id,employee_id, employee_name, employee_position;
		cout << "\t\t\tInput the employee id to further modify >>> ";
		cin >> id;
		id = upper(id);
		for (int i = 0; i < record; i++)
		{
			if (id == employee[i].id)
			{
				index = i;
				found++;
			}
		}
		if (found > 0)
		{
			bool checking = true;
			do {
				cout << "\t\t\tEmployee id found in system " << endl;
				cout << "\t\t\t<1> Employee id" << endl;
				cout << "\t\t\t<2> Employee name" << endl;
				cout << "\t\t\t<3> employee department" << endl;
				cout << "\t\t\t<4> employee position" << endl;
				cout << "\t\t\t<5> Exit" << endl;
				cout << "\t\t\tinput your selection to modify >>> " ;
				cin >> selection;
				switch (selection)
				{
				case(1):
				{
					cout << "\t\t\tinput new employee id ('EW' and 3 numerial numbers)>>>";
					cin >> employee_id;
					employee_id = upper(employee_id);
					result = EmployeeID(employee_id, record);
					if (result)
						employee[index].id = employee_id;
					else
						cout << "\t\t\tInvalid employee id" << endl;
					break;
				case(2):
				{
					cin.ignore();
					cout << "\t\t\tInput new employee name: ";
					getline(cin, employee_name);
					employee_name = upper(employee_name);
					employee_name = employee[index].name;
					break;
				}
				case(3):
				{
					for (int i = 0; i < 5; i++)
					{
						cout << "< " << i << " > " << department[i] << endl;
					}
					cin >> number;
					employee[index].department = department[number - 1];
					break;
				}
				case(4):
				{
					cin.ignore();
					cout << "\t\t\tInput new position of employee >>> ";
					getline(cin, employee_position);
					employee_position = upper(employee_position);
					cout << "Position is " << employee_position;
					employee_position = employee[index].position;
					break;
				}
				}case(5):
				{
					checking = false;
					break;
				}
				default:
				{
					cout << "\t\t\tInvalid input" << endl;
				}
				}
			} while (checking);
		}
		LoadEmployeeRecord(record);
		cout << "\t\t\tDo you want to continue <Y>es >>>";
		cin >> cont;
	} while (cont=='Y');
}
bool EmployeeID(string employee_id,int &record)
{
	int found = 0,size;
	size = signed(employee_id.size());
	for (int i = 0; i < record; i++)
	{
		if (employee_id == employee[i].id)
			found++;
	}
	if (found == 0 && size == 5)
	{
		if ((employee_id[0] == 'E' && employee_id[1] == 'W') && (isdigit(employee_id[3]) && (isdigit(employee_id[3]) && isdigit(employee_id[3]))))
			return true;//&& is binary operator(only can compare two items)
		else
			return false;
	}
	else
		return false;
}

void MovieDetails(int option)
{
	system("cls");
	int record = 0;
	string leave;
	GetSystemTime(&systemTime);
	ReadMovieRecord(record);
	cout << "\n\n\n\n\t\t\t" << string(150, char(95)) << endl;
	cout << "\t\t\t" << setw(134) << systemTime.wDay << "/" <<systemTime.wMonth << "/" << systemTime.wYear << " " << systemTime.wHour << ":" << systemTime.wMinute << ":" << systemTime.wSecond << endl;
	cout << "\t\t\t" << string(150, char(95)) << endl;
	MoviePrinting(record, 0);
	cout << "\t\t\t" << string(150, char(95)) << endl;
	cout << "\t\t\t";
	system("pause");
}
void PurchaseNow(int option)
{
	int selection;
	bool decision=true;
	do {
		system("cls");
		cout << "\t\t\t<1> Book a movie UwU " << endl;
		cout << "\t\t\t<2> Food & Beverages " << endl;
		cout << "\t\t\t<3> Exit " << endl;
		cout << "\t\t\tInput your selection >>> ";
		cin >> selection;
		switch (selection)
		{
		case(1):
		{
			BookMovie(selection);
			break;
		}
		case(2):
		{

			break;
		}
		case(3):
		{
			decision = false;
			break;
		}
		default:
		{
			cout << "\t\t\tinvalid input" << endl;
		}
		}
	} while (decision);

}
void BookMovie(int option)
{
	bool decision=true,validated=true;
	do {
		int record = 0, result=0,time_validate=0,inner=0;
		string keyword, movie_name,movie_time;
		system("cls");
		ReadMovieRecord(record);
		GetSystemTime(&systemTime);
		cout << "\n\n\n\n\t\t\t" << string(150, char(95)) << endl;
		cout << "\t\t\t" << setw(134) <<systemTime.wDay << "/" <<systemTime.wMonth << "/" << systemTime.wYear << " " << systemTime.wHour << ":" << systemTime.wMinute << ":" << systemTime.wSecond << endl;
		cout << "\t\t\t" << string(150, char(95)) << endl;
		MoviePrinting(record, 0);
		cout << "\t\t\t" << string(150, char(95)) << endl;
		int date=0, month=0, year=0,dd,mm,yyyy;
		do {
			cout << "\t\t\tDear customer, please input current date (refer to upper right)" << endl;
			cout << "\t\t\tcurrent date in DD MM YYYY form >>>";
			cin >> dd >> mm >> yyyy;
			TimeChecking(dd, mm, yyyy, date, month, year, result);
			if (result > 0)
			{
				validated = false;
				string currentdate = to_string(dd) + " " + to_string(mm) + " " + to_string(yyyy);
			}
			else
				cout << "\t\t\tInvalid input. Please input again." << endl;
		} while (validated);
		cout << "\t\t\tInput the keyword to search the movie <E>xit >>>";
		cin >> keyword;
		keyword = upper(keyword);
		for (int i = 0; i < record; i++)
		{
			if (movie[i].movie_name.find(keyword) != string::npos)//keyword checking process
			{
				inner++;
				if (inner== 1)
				{
					system("cls");
					cout << "\n\n\n\n\t\t\t" << string(150, char(95)) << endl;
					cout << "\t\t\t" << setw(135) <<systemTime.wDay << "/" <<systemTime.wMonth << "/" << systemTime.wYear << " " << systemTime.wHour << ":" << systemTime.wMinute << ":" << systemTime.wSecond << endl;

					cout << "\t\t\t" << string(150, char(95)) << endl;
				}
				movie_name = movie[i].movie_name;
				cout << "\n\t\t\tNo. " << inner << endl;
				cout << "\t\t\tMovie Name: " << movie[i].movie_name << endl;
				cout << "\t\t\tMovie Description: " << movie[i].description << endl;
				cout << "\t\t\tMovie Time: " << movie[i].movie_time << endl;
				cout << "\t\t\tMovie Length H.MM: " << fixed << setprecision(2) << movie[i].movie_length << endl;
				cout << "\t\t\tMovie Hall: " << movie[i].movie_hall << endl;
			}
		}
		if (keyword == "E")
			decision = false;
		else if (result == 0)
		{
			cout << "\t\t\tno result found" << endl;
			return BookMovie(0);
		}
		else {
			cout << "\t\t\t" << string(150, char(95)) << endl;
			bool confirms = true;
			int found = 0,adult,child;
			char booking;
			while (confirms)
			{
				cout << "\t\t\tInput the showtime of the movie <E>xit >>>";
				cin >> movie_time;
				if (movie_time == "E" || movie_time == "e")
				{
					confirms = false;
					decision = false;
				}
				else
				{
					int index = 0;
					bool result = MovieStartDetection(movie_time);

					for (int i = 0; i < record; i++)
					{
						if (movie_name == movie[i].movie_name && movie_time == movie[i].movie_time)
						{
							index = i;
							found++;
						}
					}
					if (result&&found>0)
					{
						cout << "\t\t\tMovie Name: " << movie[index].movie_name << endl;
						cout << "\t\t\tMovie Description: " << movie[index].description << endl;
						cout << "\t\t\tMovie Time: " << movie[index].movie_time << endl;
						cout << "\t\t\tMovie Length H.MM: " << fixed << setprecision(2) << movie[index].movie_length << endl;
						cout << "\t\t\tMovie Hall: " << movie[index].movie_hall << endl;
						cout << "\t\t\tAre this movie you want to book <Y>es <N>o >> >";
						cin >> booking;
						booking = toupper(booking);
						if (booking == 'Y')
						{
							bool payment = true;
							char final = 'W';
							do {
								int row[50];
								int column[50];
								CinemaSeatPrinting(index, 0);
								cout << "\t\t\tInput the number of children you want to book for >>>";
								cin >> child;
								cout << "\t\t\tInput the number of adult you want to book for >>>";
								cin >> adult;
								for (int i = 0; i < child + adult; i++)
								{
									cout << "\t\t\tNo. " << i + 1 << endl;
									cout << "\t\t\tInput the row you want >>>>";
									cin >> row[i];
									cout << "\t\t\tInput the colomn you want >>>>";
									cin >> column[i];
								}
								cout << "Successfully booked the seats with ";
								for (int i = 0; i < child + adult; i++)
								{
									cout << "Row " << row[i] <<"Column "<< column[i]<<endl;
								}
								while (final != 'Y' || (final != 'N' || final != 'E'))
								{
									cout << "Are you confirms with this booking <Y>es <N>o <E>xit >>>";
									cin >> final;
									final = toupper(final);
									if (final == 'Y' || final == 'E')
									{
										payment = false;
										confirms = false;
									}
									else if (final != 'N')
										cout << "Invalid input" << endl;
								}
							} while (payment);
						}
					}
				}
			}
			//proceed to payment
		}
	} while (decision);
}

void TimeChecking(int dd, int mm, int yyyy, int date, int month, int year, int& result)
{
	if (mm >= 1 && mm <= 12)
	{
		if (to_string(yyyy).size() == 4)  //check year
		{
			if (mm >= 1 && mm <= 7)//check month
			{
				if (mm == 2)
				{
					if ((dd >= 1 && dd <= 29) && (yyyy % 4 == 0))
						DateRecord(dd, mm, yyyy, date, month, year, result);
					else if ((dd >= 1 && dd <= 28) && (yyyy % 4 != 0))
						DateRecord(dd, mm, yyyy, date, month, year, result);
				}
				else if (mm % 2 == 0)//check date
				{
					if (dd >= 1 && dd <= 30)
						DateRecord(dd, mm, yyyy, date, month, year, result);
				}
				else
				{
					if (dd >= 1 && dd <= 31)
						DateRecord(dd, mm, yyyy, date, month, year, result);
				}
			}
			else
			{
				if (mm % 2 == 1)
				{
					if (dd >= 1 || dd <= 30)
						DateRecord(dd, mm, yyyy, date, month, year, result);
				}
				else
				{
					if (dd >= 1 && dd <= 31)
						DateRecord(dd, mm, yyyy, date, month, year, result);
				}
			}
		}
	}
}
void DateRecord(int dd, int mm, int yyyy, int date, int month, int year, int& result)
{
	result++;
	date = dd, month = mm, year = yyyy;
}
void BookSeatPrinting(int w, int i, int j)
{
	int checking = 1;
	if (movie[w].backup.data != 0)
	{
		for (int z = 0; z < movie[w].backup.data; z++)
		{
			if (i == movie[w].seats.purchased_row[z] && j == movie[w].seats.purchased_column[z])
			{
				cout << setw(2) << "X";
				checking = 0;
			}
			else if (i == movie[w].backup.row[z] && j == movie[w].backup.column[z])
			{
				cout << setw(2) << " ";
				checking = 0;
			}
		}
	}
	if (checking)
		cout << setw(2) << "A";
}
void CinemaRefresh(int option)
{
	string confirms;
	bool decision=true;
	cin.ignore();
	int movie_record=0, hall_record=0;
	while (decision)
	{
		cout << "\n\n\n\t\t\tCinema Refreshing terms and conditions!!!" << endl;
		cout << "\t\t\tOnce you confirm to refresh the cinema, the available seats and the cinema hall record of each movie will be refreshed " << endl;
		cout << "\t\t\t to the latest updated from the cinema hall record" << endl;
		cout << "\t\t\tThe system is not reversable after confirmation have made" << endl;
		cout << "\t\t\tCinema Refreshing Confirmation" << endl;
		cout << "\t\t\t if Confirms <Y>es, else <N>o  >>>";
		getline(cin, confirms);
		confirms = upper(confirms);
		if (confirms == "Y")
		{
			ReadMovieRecord(movie_record);
			ReadCinemaHallRecord(hall_record);
			for (int i = 0; i < movie_record; i++)
			{
				movie[i].seats.data = 0;
				movie[i].seats.purchased_row[0] = 0;
				movie[i].seats.purchased_column[0] = 0;
				if (movie[i].movie_hall <= hall_record || movie[i].movie_hall > 0)
				{
					movie[i].backup.data = unavailable[movie[i].movie_hall - 1].data;
					if (movie[i].backup.data > 0)
					{
						for (int j = 0; j < movie[i].backup.data; j++)
						{
							movie[i].backup.row[j] = unavailable[movie[i].movie_hall - 1].row[j];
						}
						for (int j = 0; j < movie[i].backup.data; j++)
						{
							movie[i].backup.column[j] = unavailable[movie[i].movie_hall - 1].column[j];
						}
					}
					else
					{
						movie[i].backup.row[0] = 0;
						movie[i].backup.column[0] = 0;
					}
				}
			}
			LoadMovieRecord(movie_record);
			decision = false;

		}
		else if (confirms == "N")
			decision = false;
		else
			cout << "\t\t\tInvalid Input found" << endl;
	}
}
//Open member info file
void OpenPurchaseHistory()
{
	ifstream Ad_purchase;
	int k = 0;

	Ad_purchase.open("Admin_purchase.txt");
	if (Ad_purchase.is_open())
	{
		while (!Ad_purchase.eof())
		{
			getline(Ad_purchase, Purchase[k].Purchase_user);
			getline(Ad_purchase, Purchase[k].Purchase_name);

			for (int i = 0; i < 5; i++)
			{
				getline(Ad_purchase, Purchase[k].Purchase_date[i]);
				getline(Ad_purchase, Purchase[k].Purchase_pax[i]);
				getline(Ad_purchase, Purchase[k].Purchase_movie[i]);
				getline(Ad_purchase, Purchase[k].Purchase_food[i]);
			}
			k++;
		}
	}
	else
		cout << "Please contact admin for further assistance..." << endl;
	Ad_purchase.close();
}
void OpenMemberDetails(int& nomember)
{
	int i = 0;
	ifstream Ad_memberlist;
	Ad_memberlist.open("Admin_memberlist.txt");
	if (Ad_memberlist.is_open())
	{
		while (!Ad_memberlist.eof())
		{
			getline(Ad_memberlist, Member[i].Details_user);
			getline(Ad_memberlist, Member[i].Details_password);
			getline(Ad_memberlist, Member[i].Details_name);
			getline(Ad_memberlist, Member[i].Details_status);
			getline(Ad_memberlist, Member[i].Details_join);
			getline(Ad_memberlist, Member[i].Details_point);
			getline(Ad_memberlist, Member[i].Details_phone);
			getline(Ad_memberlist, Member[i].Details_email);
			i++;
			nomember = i;
		}
	}
	else
		cout << "Please contact admin for further assistance..." << endl;
	Ad_memberlist.close();
}
//Membership details
void UserRegister()
{
	ofstream Add_member, Add_purchase;
	int i = 0, newmember = 0, existing = 0, nomember = 0;
	string username, password;

	system("cls");
	cout << "Good day!\nWelcome to be part of us!\n\n";
	cout << "\t\t\tKindly fill in the below information. \n";
	cout << "\t\t\t*Compulsory\n\n";
	cout << "\t\t\t*Username: ";
	cin.ignore();
	getline(cin, username);

	OpenMemberDetails(nomember);

	for (int i = 0; i < nomember; i++)
	{
		if (!(upper(username) == upper(Member[i].Details_user)))
			newmember = i;
		else if (upper(username) == upper(Member[i].Details_user))
			existing = i;
	}

	if (!(upper(username) == upper(Member[existing].Details_user)))
	{
		Member[newmember].Details_user = username;
		cout << "\t\t\t*Full name as per NRIC: ";
		getline(cin, Member[newmember].Details_name);
		Member[newmember].Details_status = "Classic";
		cout << "\t\t\t*Password: ";
		getline(cin, Member[newmember].Details_password);
		cout << "\t\t\t*Register date (DD MM YYYY): ";
		getline(cin, Member[newmember].Details_join);
		Member[newmember].Details_point = "0";
		cout << "\t\t\t*Phone number: ";
		getline(cin, Member[newmember].Details_phone);
		cout << "\t\t\t*Email: ";
		getline(cin, Member[newmember].Details_email);
		cout << "\n\t\t\tCongratulations!\n\t\t\tYour registration was successful!\n\t\t\tKindly log in to access more.\n\t\t\tThank you ^^\n";
		system("PAUSE");
	}
	else if (upper(username) == upper(Member[existing].Details_user))
	{
		cout << "\t\t\tRegistered member!\n\t\t\tPlease log in to access your account.\n";
		system("PAUSE");
	}

	Add_member.open("Admin_memberlist.txt", ios::app);
	{
		Add_member << Member[newmember].Details_user << endl;
		Add_member << Member[newmember].Details_password << endl;
		Add_member << Member[newmember].Details_name << endl;
		Add_member << Member[newmember].Details_status << endl;
		Add_member << Member[newmember].Details_join << endl;
		Add_member << Member[newmember].Details_point << endl;
		Add_member << Member[newmember].Details_phone << endl;
		Add_member << Member[newmember].Details_email << endl;
	}
	Add_member.close();

	Add_purchase.open("Admin_purchase.txt", ios::app);
	{
		Purchase[newmember].Purchase_user = Member[newmember].Details_user;
		Purchase[newmember].Purchase_name = Member[newmember].Details_name;
		Add_purchase << Purchase[newmember].Purchase_user << endl;
		Add_purchase << Purchase[newmember].Purchase_name << endl;
		for (int i = 0; i < 5; i++)
		{
			Add_purchase << "N/A" << endl;
			Add_purchase << "N/A" << endl;
			Add_purchase << "N/A" << endl;
			Add_purchase << "N/A" << endl;
		}
	}
	Add_purchase.close();
}

void UserLogIn()
{
	int selection, nomember = 0;
	bool decision = true;
	ifstream Ad_memberlist, Ad_purchase;
	int j = 0, i = 0, k = 0, found = 0;
	string username, password;
	system("cls");
	cout << "Good day! " << endl;
	cout << "Kindly log in for more access. " << endl << endl;

	cout << "\t\t\tPlease enter your username: ";
	cin >> username;

	OpenMemberDetails(nomember);
	for (int i = 0; i < nomember; i++)
	{
		if (upper(username) == upper(Member[i].Details_user))
			found = i;
	}
	OpenPurchaseHistory();
	if (upper(username) == upper(Member[found].Details_user))
	{
		cout << "\t\t\tPlease enter your password: ";
		cin >> password;
		if (password == Member[found].Details_password)
		{
			do {
				system("cls");
				cout << "Welcome back, our beloved member! " << endl;
				cout << "<1> Profile" << endl;
				cout << "<2> Purchase history" << endl;
				cout << "<3> Exit" << endl;

				cout << "\t\t\tPlease input your selection >>> ";
				cin >> selection;
				switch (selection) {
				case(1)://Check personal details
				{
					system("cls");
					cout << "\t**************************************************************************" << endl << endl;
					cout << "\t\t\tName: " << Member[found].Details_name << endl;
					cout << "\t\t\tStatus: " << Member[found].Details_status << endl;
					cout << "\t\t\tJoin date: " << Member[found].Details_join << endl;
					cout << "\t\t\tAccumulated point(s): " << Member[found].Details_point << endl;
					cout << "\t\t\tPhone number: " << Member[found].Details_phone << endl;
					cout << "\t\t\tEmail address: " << Member[found].Details_email << endl << endl;
					cout << "\t**************************************************************************" << endl << endl;
					system("PAUSE");
					break;
				}
				case(2)://Check purchase history
				{
					system("cls");
					cout << "\t**************************************************************************" << endl << endl;
					cout << "\t\t\tName: " << Purchase[found].Purchase_name << endl << endl;
					for (int i = 0; i < 5; i++)
					{
						cout << "\t\t\t" << i + 1 << ". Purchase Date: " << Purchase[found].Purchase_date[i] << endl;
						cout << "\t\t\tNumber of pax (Child Adult): " << Purchase[found].Purchase_pax[i] << endl;
						cout << "\t\t\tMovie: " << Purchase[found].Purchase_movie[i] << endl;
						cout << "\t\t\tF&B: " << Purchase[found].Purchase_food[i] << endl << endl;
					}
					cout << "\t**************************************************************************" << endl << endl;
					system("PAUSE");
					break;
				}
				case(3): //Exit
				{
					decision = false;
					break;
				}
				default://reinput
				{
					cout << "\t\t\tInvalid input found" << endl;
					break;
				}
				}
			} while (decision);
		}
		else
			cout << "\t\t\tInvalid password!\n\t\t\tPlease contact admin to reset password. " << endl;
	}
	else if (!(upper(username) == upper(Member[found].Details_user)))
		cout << "\t\t\tMember doesn't exist! \n";

	system("PAUSE");
}

void MembershipDetails()
{
	int selection;
	bool decision = true;
	system("cls");
	do {
		system("cls");
		cout << "<1> Log in" << endl;
		cout << "<2> Register" << endl;
		cout << "<3> Exit" << endl;

		cout << "\t\t\tPlease input your selection >>> ";
		cin >> selection;
		switch (selection)
		{
		case(1)://Existing member log in
		{
			UserLogIn();
			break;
		}
		case(2)://New member
		{
			UserRegister();
			break;
		}
		case(3): //Exit
		{
			decision = false;
			break;
		}
		default://reinput
		{
			cout << "\t\t\tInvalid input found" << endl;
			break;
		}
		}
	} while (decision);
}
void Main_Menu(string Name)
{
	int i=112, j=112;
	system("Color 70");
	cout << "\n\n\n\t\t\t" << string(121, char(61)) << "\n";
	cout << "\t\t\t=" << right << setw(121) << "=\n";
	cout << "\t\t\t=" << string(4, ' ') << string(20, char(126)) << string(20, ' ') << string(25, char(126)) << string(25, ' ') << string(19, char(126)) << string(5, ' ') << " = \n";
	cout << "\t\t\t=" << string(4, ' ') << "[";
	SetConsoleTextAttribute(console, i);
	cout << " 1. Movie Details ";
	SetConsoleTextAttribute(console, j);
	cout << "]" << string(20, ' ') << "[";
	SetConsoleTextAttribute(console, i);
	cout << " 2. Food and Beverages ";
	SetConsoleTextAttribute(console, j);
	cout << "]" << string(25, ' ') << "[";
	SetConsoleTextAttribute(console, i);
	cout << " 3. Purchase Now ";
	SetConsoleTextAttribute(console, j);
	cout << "]" << string(5, ' ') << " = \n";
	cout << "\t\t\t=" << string(4, ' ') << string(20, char(126)) << string(20, ' ') << string(25, char(126)) << string(25, ' ') << string(19, char(126)) << string(5, ' ') << " = \n";
	cout << "\t\t\t=" << right << setw(121) << "=\n";
	cout << "\t\t\t=" << string(24, ' ') << string(22, char(95)) << string(23, ' ') << string(25, char(95)) << string(24, ' ') << " = \n";
	cout << "\t\t\t=" << string(24, ' ') << "[";
	SetConsoleTextAttribute(console, i);
	cout << " 4. Membership Page ";
	SetConsoleTextAttribute(console, j);
	cout << "]" << string(23, ' ') << "[";
	SetConsoleTextAttribute(console, i);
	cout << " 5. Administrator Page ";
	SetConsoleTextAttribute(console, j);
	cout << "]" << string(24, ' ') << " = \n";
	cout << "\t\t\t=" << string(24, ' ') << string(20, char(126)) << string(25, ' ') << string(25, char(126)) << string(24, ' ') << " = \n";
	cout << "\t\t\t=" << right << setw(121) << "=\n";
	cout << "\t\t\t=" << string(50, ' ') << string(14, char(126)) << string(54, ' ') << " = \n";
	cout << "\t\t\t=" << string(50, ' ') << "[";
	SetConsoleTextAttribute(console, i);
	cout << " 5.   EXIT  ";
	SetConsoleTextAttribute(console, j);
	cout << "]" << string(54, ' ') << " = \n";
	cout << "\t\t\t=" << string(50, ' ') << string(14, char(126)) << string(54, ' ') << " = \n";
	cout << "\t\t\t" << string(121, char(61)) << "\n";
}





