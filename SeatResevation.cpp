#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

using namespace std;

struct Seat
{
    string seat_class;
    string seat_no;
    string row_no;
    Seat(string row_no, string seat_class, char seat_no);

};

Seat::Seat(string row_no, string seat_class, char seat_no)
{
    this->seat_class = seat_class;
    this->seat_no = seat_no;
    this->row_no =row_no;
}

class Flight
{

public:
    string Flight_no;
    string date_time;
    string Departure_airport;
    string Arrival_airport;
    vector<Seat>Seats;

    Flight(string Flight_no, string date_time, string Departure_airport, string Arrival_airport, vector<Seat>Seats);
};

Flight::Flight(string Flight_no, string date_time, string Departure_airport, string Arrival_airport, vector<Seat>Seats)
{
    this->Flight_no = Flight_no;
    this->date_time = date_time;
    this->Departure_airport =Departure_airport;
    this->Arrival_airport = Arrival_airport;
    this->Seats =Seats;
}

vector<Flight> Flight_List;

void LoadFile()
{
    ifstream file;
    file.open("flights.txt");
    int count = 0;
    while (file)
    {
        count = 0;
        string line = "null";
        string data[4];
        vector<Seat>Seats;
        while (1)
        {

            getline(file, line);

            if (line == "" || !file)
                break;
            else if (count < 4)
                data[count] = line;
            else
            {
                string a[3];
                stringstream s(line);
                s >> a[0] >> a[1] >> a[2];
                int i = 0;
                for (i = 0; i < a[2].size(); i++)
                {
                    Seat t(a[0], a[1], a[2][i]);
                   Seats.push_back(t);
                }
            }

            count++;
        }

        Flight p(data[0], data[1], data[2], data[3],Seats);
        Flight_List.push_back(p);
    }
    file.close();
}

void Availableflights()
{

    for (vector<Flight>::iterator i = Flight_List.begin(); i != Flight_List.end(); ++i)
    {

        if (i->Seats.size() < 1)
            continue;
        cout << endl;
        cout << "Flight number:\t\t" << i->Flight_no << endl;
        cout << "Date and time:\t\t" << i->date_time << endl;
        cout << "Departure_airportarture Airport:\t" << i->Departure_airport << endl;
        cout << "Arrival Airport:\t" << i->Arrival_airport << endl;
        cout << "No of Seats:\t\t" << i->Seats.size() << endl;
    }
}

void ViewFlight()
{
    string f_no;
    cout << "Enter Flight Number : ";
    cin >>f_no;
    for (vector<Flight>::iterator i = Flight_List.begin(); i != Flight_List.end(); ++i)
        if (i->Flight_no == f_no)
        {
            int B = 0, E = 0;

            cout <<endl;
            cout << "Flight number:\t\t" << i->Flight_no << endl;
            cout << "Date and time:\t\t" << i->date_time << endl;
            cout << "Departure_airportarture Airport:\t" << i->Departure_airport << endl;
            cout << "Arrival Airport:\t" << i->Arrival_airport << endl;

            cout << i->Seats.size() << "Seats were available" << endl;
            cout << "Seat no\tSeat Class" << endl;

            for (vector<Seat>::iterator j = i->Seats.begin(); j != i->Seats.end(); ++j)
            {
                string seat_no = j->row_no + j->seat_no;
                cout << seat_no << "\t" << j->seat_class << endl;
                if (j->seat_class == "E")
                    E++;
                if (j->seat_class == "B")
                    B++;
            }
            cout << endl;
            cout << "Number of E ClassSeats : " << E << endl;
            cout << "Number of B ClassSeats : " << B << endl;
            cout << endl;

            return;
        }
    cout << "Flight not found";
}

void CheckSeat()
{
    string fno;
    cout << "Enter Flight Number : ";
    cin >> fno;
    for (vector<Flight>::iterator i = Flight_List.begin(); i != Flight_List.end(); ++i)
        if (i->Flight_no == fno)
        {
            int seat_nos;
            cout << "Enter the number of Seats that you are required : ";
            cin >> seat_nos;
            if (i->Seats.size() >= seat_nos)
            {
                cout << i->Seats.size() << "Seats are available now" << endl;
                cout << "Seat no\tSeat Class" << endl;

                for (vector<Seat>::iterator j = i->Seats.begin(); j != i->Seats.end(); ++j)
                {
                    string seat_no = j->row_no + j->seat_no;
                    cout << seat_no << "\t" << j->seat_class << endl;
                }
            }
            else
                cout << "Sorry!!! that number of Seats are not available" << endl;

            return;
        }
    cout << "Flight not found";
}

void BookFlight()
{
    string fno;
    cout << "Enter Flight Number : ";
    cin >> fno;
    for (vector<Flight>::iterator i = Flight_List.begin(); i != Flight_List.end(); ++i)
        if (i->Flight_no == fno)
        {
            string seat_no;
            cout << "Enter seat no : ";
            cin >> seat_no;
            for (vector<Seat>::iterator j = i->Seats.begin(); j != i->Seats.end(); ++j)
            {
                string seatno = j->row_no + j->seat_no;
                if (seatno == seat_no)
                {
                    i->Seats.erase(j);
                    cout << "Seat " << seat_no << "your seats booked succesfully ." << endl;
                    return;
                }
                
            }
            cout << "Seat are not available or invalid seat no" << endl;
            return;
        }
    cout << "Flight not found";
}

void Save()
{
    fstream fout;

    fout.open("flights.dat", ios::trunc | ios::out);
    int flag = 0;
    for (vector<Flight>::iterator i = Flight_List.begin(); i != Flight_List.end(); ++i)
    {
        if (flag) 
            fout << endl;
            fout << endl;
        flag = 1;

        fout << i->Flight_no << endl;
        fout << i->date_time << endl;
        fout << i->Departure_airport << endl;
        fout << i->Arrival_airport << endl;
        string row_no = "-1";
        string line = "-1";
        for (vector<Seat>::iterator j = i->Seats.begin(); j != i->Seats.end(); ++j)
        {
            if (row_no == j->row_no)
            {
                line = line + j->seat_no;
            }
            else
            {
                row_no = j->row_no;
                if (line != "-1")
                    fout << line << endl;
                line = j->row_no + " " + j->seat_class + " " + j->seat_no;
            }
        }
        fout << line;
    }

    fout.close();
    exit(0);
}

int main()
{
    LoadFile();
    int option;
    while (1)
    {
        cout <<"******** WELCOME TO VIRGIN AIRLINE ********"<<endl;
        cout <<"__________Menu__________"<<endl;
		cout << "1 Display available flights" << endl;
        cout << "2 View flight" << endl;
        cout << "3 Seat availability" << endl;
        cout << "4 Seat booking" << endl;
        cout << "5 Exit" << endl;
        cout << "Enter your option:";
        cin >> option;
        
		switch (option)
        {
        case 1:
            Availableflights();
            break;
        case 2:
            ViewFlight();
            break;
        case 3:
            CheckSeat();
            break;
        case 4:
            BookFlight();
            break;
        case 5:
            Save();
            break;

        default:
            break;
        }
    }

    return 0;
}
