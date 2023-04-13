#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
#include <cctype>
#include <iomanip>
#include <Windows.h>
#include <string>
using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

//function declaration
string upper(string);
void Main_Menu(string);
void CinemaManagement(int);
void AdministratorMenu(int);
//Cinema_Hall function
void CinemaHallManagement(int);
void ReadCinemaHallRecord(int&);
void CinemaSeatPrinting(int);
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
//structure declaration

struct mapping_seats
{
	int hall; //cinema hall
	int data;	//a set of column and row = 1 data
	int row[70];	
	int column[70];
}unavailable[50];
struct PurchasedSeatType
{
	int data;
	int purchased_row[50];
	int purchased_column[50];
};
struct CinemaHallSeatType
{
	int data;
	int row[70];
	int column[70];
};
struct movie
{
	string movie_id;
	string movie_name;
	string description;
	string movie_time;
	double movie_length;
	int movie_hall;
	PurchasedSeatType seats;
	CinemaHallSeatType backup;
	
}movie[100];
struct employee {
	string name;
	string id;
	string password;
	
};
//Main Menu
int main()
{
	bool decision = true;
	int selection;
	do{
		system("cls");
		Main_Menu("MAIN");
		cout << "\t\t\tPlease input your selection >>> ";
		cin >> selection;
		switch (selection)
		{
		case(1)://Movie details
		{
			break;
		}
		case(2)://f&b
		{
			break;
		}
		case(3)://purchase now
		{
			break;
		}
		case(4)://membership details
		{
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
	//login menu
	system("cls");
	string admin_id, password;
	bool decision = true, access = true;
	int selection;
	do
	{
		cout << "\n\n\n\t\t\tPlease input your ADMIN ID >>>";
		cin >> admin_id;
		cout << "\t\t\tPlease input your password >>>";
		cin >> password;
		access = false;
	} while (access);

	do {
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
			CinemaManagement(selection);
			break;
		}
		case(2)://Cinema management
		{
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
	} while (decision);
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
			CinemaSeatPrinting(w);
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
//read cinema hall seats
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
}
//save cinema hall record
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
void CinemaSeatPrinting(int w)
{

	for (int i = 0; i < 10; i++)
	{
		cout << "\t\t\t";
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
				HallSeatPrinting(w, i, j);
			}
			cout << " ";
			for (int j = 3; j < 13; j++)
			{
				HallSeatPrinting(w, i, j);
			}
			cout << " ";
			for (int j = 13; j < 15; j++)
			{
				HallSeatPrinting(w, i, j);
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
		cout << setw(2) << "*";
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
		cout << "R1 ";
		cout << record<<endl;
		record--;
		cout << "successfully deleted..." << endl;
		cout << record;
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
			CinemaSeatPrinting(number - 1);
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
		CinemaSeatPrinting(number - 1);
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
	int record = 0;
	int selection;
	do {
		
		system("cls");
		ReadMovieRecord(record);
		cout << "\n\n\n\n\t\t\t<1> Add Movie " << endl;
		cout << "\t\t\t<2> Modify Movie " << endl;
		cout << "\t\t\t<3> Delete Movie " << endl;
		cout << "\t\t\t<4> exit " << endl;
		cout << "Input your selection" << endl;
		cin >> selection;
		switch (selection)
		{
		case(1):
		{
			AddMovie(selection);
			break;
		}
		case(2):
		{
			ModifyMovie(selection);
			break;
		}
		case(3):
		{
			DeleteMovie(selection); 
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
			for (int i = 0; i < movie[record].seats.data; i++)
				infile >> movie[record].seats.purchased_row[i];
			for (int i = 0; i < movie[record].seats.data; i++)
				infile >> movie[record].seats.purchased_column[i];
			infile >> movie[record].backup.data;
			for(int i=0;i<movie[record].backup.data;i++)
				infile >> movie[record].backup.row[i];
			for (int i = 0; i < movie[record].backup.data; i++)
				infile >> movie[record].backup.column[i];
			record++;
		}
	}

}
void LoadMovieRecord(int& record)
{
	ofstream outfile;
	outfile.open("movie.txt");
	for (int i = 0; i < record; i++)
	{
		outfile << movie[i].movie_id << endl << movie[i].movie_name << endl << movie[i].description << endl;
		outfile<< movie[i].movie_time << endl<< movie[i].movie_length << endl<< movie[i].movie_hall << endl<<movie[i].seats.data;
		for (int j = 0; j < movie[i].seats.data; j++)
			outfile << movie[i].seats.purchased_row[j];
		for (int j = 0; j < movie[i].seats.data; j++)
			outfile << movie[i].seats.purchased_column[j];
		outfile << movie[i].backup.data;
		for (int j = 0; j < movie[i].backup.data; j++)
			outfile << movie[i].backup.row[j];
		for (int j = 0; j < movie[i].backup.data; j++)
			outfile << movie[i].backup.row[j];
	}
}
void AddMovie(int& record)
{
	bool decision = true;
	do {
		char confirms;
		string movie_name, movie_id, description, movie_time;
		double movie_length;
		int movie_hall;
		bool checking = true;
		do {
			int found = 0;
			cout << "\t\t\tInput the movie id >>> ";
			cin >> movie_id;
			for (int i = 0; i < record; i++)
			{
				if (movie_id == movie[i].movie_id);
				found++;
			}
			if (found == 0)
				checking = false;
			else
				cout << "Movie id found inside system" << endl;
		} while (checking);
		
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
			cin >> movie_length;
			int hour = int(movie_length);		
			double minutes = (movie_length-hour) * 100;	
			if (minutes > 60)
				cout << "invalid input" << endl;
		} while (checking);

		
		checking = true;
		do {

			int found = 0;
			cout << "\t\t\tInput the movie_hall >>>";
			cin >> movie_hall;
			
			MovieEndDetection(movie_time, movie_hall, movie_length, found, record);
			if (found == 0)
				checking = false;

		} while (checking);

		do{
			cout << "\t\t\tMovie ID: " << movie_id << endl;
			cout << "\t\t\tMovie ID: " << movie_name << endl;
			cout << "\t\t\tMovie ID: " << description << endl;
			cout << "\t\t\tMovie ID: " << movie_time << endl;
			cout << "\t\t\tMovie ID: " << movie_length << endl;
			cout << "\t\t\tMovie ID: " << movie_hall << endl;
			cout << "Are you confirm? <Y>es <N>o >>> " << endl;
			cin >> confirms;
			confirms = toupper(confirms);
			if (confirms == 'Y' || confirms == 'N')
			{
				checking = false;
				decision = false;
			}
		}while(checking);

		if (confirms == 'Y')
		{
			MovieRecordIntoStruct(movie_id, movie_name, description, movie_time, movie_length, movie_hall, record);
		}

	} while (decision);

}
void ModifyMovie(int& record)
{
	char confirms;
	string movie_name, movie_id, description, movie_time;
	double movie_length;
	int movie_hall,trace;
	bool decision = true;
	do {
		int found = 0,selection,storage;
		cout << "\t\t\tInput the Movie ID: ";
		cin >> movie_id;
		for (int i = 0; i < record; i++)
		{
			if (movie_id == movie[i].movie_id)
			{
				found++;
				storage = i;
			}
			else
				cout << "please reinput the movie id" << endl;
		}
		if (found > 0)
		{
			cout << "Which section you want to modify???" << endl;
			cout << "<1> Movie ID " << endl;
			cout << "<2> Movie Name" << endl;
			cout << "<3> Movie Description" << endl;
			cout << "<4> Movie Start time" << endl;
			cout << "<5> Movie length" << endl;
			cout << "<6> Cinema Hall of movie" << endl;
			cout << "<7> Exit" << endl;
			cout << "Input your selection" << endl;
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
						cout << "Movie ID was found inside the system" << endl;
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
				cout << "Enter the new movie length in Hours.Minutes(X.XX) >>>";
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
				cout << "Enter the new movie hall >>>";
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
		LoadMovieRecord(record);
	} while (decision);
}
void DeleteMovie(int& record) 
{
	int found=0;
	string movie_id;
	bool decision = true;
	do {
		cout << "Input the movie id you want to delete >>>>";
		cin >> movie_id;
		for (int i = 0; i < record; i++)
		{
			if (movie_id == movie[i].movie_id)
			{
				cout << "Movie ID found in system" << endl;
				found++;
				for (int j = i; j < record; j++)
				{
					movie[j].movie_id = movie[j + 1].movie_id;
					movie[j].movie_name = movie[j + 1].movie_name;
					movie[j].description = movie[j + 1].description;
					movie[j].movie_time = movie[j + 1].movie_time;
					movie[j].movie_length = movie[j + 1].movie_length;
					movie[j].movie_hall = movie[j + 1].movie_hall;
					movie[j].seats.data = movie[j + 1].seats.data;
					for (int z = 0; z < movie[j].seats.data; z++)
						movie[j].seats.purchased_row[z] = movie[j+1].seats.purchased_row[z];
					for (int z = 0; z < movie[j].seats.data; z++)
						movie[j].seats.purchased_row[z] = movie[j+1].seats.purchased_column[z];
					movie[j].backup.data = movie[j + 1].backup.data;
					for (int z = 0; z < movie[j].backup.data; z++)
						movie[j].backup.row[z] = movie[j+1].backup.row[z];
					for (int z = 0; z < movie[j].backup.data; z++)
						movie[j].backup.column[z] = movie[j+1].backup.column[z];
				}
				
			}
		}
		if (found > 0)
		{
			record--;
			decision = false;
			LoadMovieRecord(record);
		}
		else
			cout << "Invalid movie id" << endl;
	} while (decision);

}
void MoviePrinting(int& record,int w)
{
	for (int i = 0; i < record; i++)
	{
		cout << "No. " << i + 1 << endl;
		if (w == 99) //only print for admin
			cout << "\n\n\n\n\n\n\n\t\t\tMovie Id: " << movie[i].movie_id << endl;
		cout << "\t\t\tMovie Name: " << movie[i].movie_name << endl;
		cout << "Movie Description: " << movie[i].description << endl;
		cout << "Movie Time: " << movie[i].movie_time << endl;
		cout << "Movie Length: " << movie[i].movie_length << endl;
		cout << "Movie Hall: " << movie[i].movie_hall << endl;
	}
}
bool MovieStartDetection(string movie_time)   //detect start time of movie
{													//sample output

	int checking = stoi(movie_time);				//2401      2061
	int integer_hours = checking / 100 * 100;		//2400		2000
	int remain = checking%integer_hours;			//1			61
	int size=movie_time.size();
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
	for (int i = 0; i < movie[record - 1].backup.data; i++)
	{
		movie[record - 1].backup.row[i] = unavailable[hall - 1].row[i];
	}
	for (int i = 0; i < movie[record - 1].backup.data; i++)
	{
		movie[record - 1].backup.column[i] = unavailable[hall - 1].column[i];
	}
	LoadMovieRecord(record);
}
void MovieEndDetection(string movie_time,int movie_hall,double movie_length,int& found,int &record)
{
	int movie_end = stoi(movie_time) + (int(movie_length) * 100 + (movie_length - int(movie_length)) * 100);
	if (movie_end - movie_end / 100 * 100 > 60)
		movie_end = movie_end - 60 + 100;

	for (int i = 0; i < record; i++)
	{
		if (movie_hall == movie[i].movie_hall)
		{
			string time = movie[i].movie_time;					//1200
			int timing = stoi(time);
			int hour = int(movie_length);						//2.40=2
			int minutes = (movie_length - hour) * 100;			//40
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

















void Main_Menu(string Name)
{
	int i=142, j=48;
	system("Color 30");
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