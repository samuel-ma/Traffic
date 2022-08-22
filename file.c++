#include <iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAXCARS 3
#define MaxFines 30
#define MaxDrivers 50
using namespace std;
    
//structures
struct Date 
{
    int Day;
    int Month;
    int Year;
};
struct Fines
{
    float FineValue;
    string StreetName;
    Date FineDate;
    bool Paid = false;
};
struct Cars 
{
    int PlateNum;
    string Model;
    int PYear;
    Fines Fine[MaxFines];
};
struct Drivers  
{
    string Name;
    int licenseNum;
    Cars OwnedCars[MAXCARS];
    Date BirthDate;
}driver[MaxDrivers];
  
  
//Functions
void Violation( bool &IsCorrectPlateNumber)//violation recording function
{
    int MaxSpeed, Speed;
    cout << "enter the car plate number:";
    Cars x;
    cin >> x.PlateNum;
    for (int i = 0; i < MaxDrivers; i++)
    {
        for (int j = 0; j < MAXCARS; j++)

        {
            if (x.PlateNum == driver[i].OwnedCars[j].PlateNum)//checking that plate number exists
            {
                IsCorrectPlateNumber = true;
                cout << "enter the car speed:";
                cin >> Speed;
                cout << "enter the maximum speed for the street:";
                cin >> MaxSpeed;
                for (int k = 0; k < MaxFines; k++)
                    if (driver[i].OwnedCars[j].Fine[k].FineValue == 0)
                    {
                        cout << "enter the street name:";
                        cin.ignore();
                        getline(cin,driver[i].OwnedCars[j].Fine[k].StreetName);
                        driver[i].OwnedCars[j].Fine[k].FineValue = (Speed - MaxSpeed) * 2;
                        cout << "Enter Current day: ";
                        cin >> driver[i].OwnedCars[j].Fine[k].FineDate.Day;
                        cout << "Enter Current month: ";
                        cin >> driver[i].OwnedCars[j].Fine[k].FineDate.Month;
                        cout << "Enter Current  year: ";
                        cin >> driver[i].OwnedCars[j].Fine[k].FineDate.Year;
                        k = MaxFines;
                    }


            }

        }

    }

    if (IsCorrectPlateNumber == false)
        cout << "This plate number doesnot exist\n\n";//the plate number doesnt exist

}
void Driver_information_or_payment (bool &driverMenu, bool &Back ,int &i)
{

    int counter2 = 0;
    do
    {
        cout << "To add a new car information press(1)\nor view your registered cars and unpayed fines press(2): ";
        int driverChoice;
        cin >> driverChoice;
        system("cls");
        if (driverChoice == 1)
        {
            int counter3 = 0;
            for (int j = 0; j < MAXCARS; j++)
            {
                if (driver[i].OwnedCars[j].PlateNum == 0)
                {
                    counter3++;
                    cout << "Enter car plate num:";
                    cin >> driver[i].OwnedCars[j].PlateNum;
                    cout << "Enter car model: ";
                    cin.ignore();
                    getline(cin,driver[i].OwnedCars[j].Model);
                    cout << "Enter car production year:";
                    cin >> driver[i].OwnedCars[j].PYear;
                    j = MAXCARS;
                }
                if (j == MAXCARS - 1 && counter3 == 0)
                {
                    cout << "Can't add more cars\nMax number of cars is 3!!\n\n";

                }
            }
        }
        else if (driverChoice == 2)
        {
            cout << "*your registered cars and their plate numbers*\n";
            int TotalNumberOfFines = 0;
            for (int j = 0; j < MAXCARS; j++)
            {
                if (driver[i].OwnedCars[j].PlateNum != 0)
                    cout << j + 1 << '-' << driver[i].OwnedCars[j].Model << ' ' << driver[i].OwnedCars[j].PlateNum << endl;

                for ( int k = 0; k < MaxFines; k++)
                    if (driver[i].OwnedCars[j].Fine[k].FineValue != 0)
                        TotalNumberOfFines++;

            } cout << endl << "Total number of fines: " << TotalNumberOfFines << endl;
            if (TotalNumberOfFines > 0)//when fines are zero it goes to previous menu
            {
                cout << "To view fine for a specific car enter the car's plate number: ";
                Cars x;
                cin >> x.PlateNum;
                int counter = 0;

                for (int j = 0; j < MAXCARS; j++)
                    if (driver[i].OwnedCars[j].PlateNum == x.PlateNum)
                    {
                        for (int k = 0; k < MaxFines; k++)
                        {
                            if (driver[i].OwnedCars[j].Fine[k].FineValue != 0 && driver[i].OwnedCars[j].Fine[k].Paid == false)
                            {
                                counter++;
                                cout << k + 1 << '-' << "Fine value: " << driver[i].OwnedCars[j].Fine[k].FineValue << endl;
                                cout << "Fine date: " << driver[i].OwnedCars[j].Fine[k].FineDate.Day << '/' <<
                                    driver[i].OwnedCars[j].Fine[k].FineDate.Month << '/' << driver[i].OwnedCars[j].Fine[k].FineDate.Year << endl;
                                cout << "Fine on street: " << driver[i].OwnedCars[j].Fine[k].StreetName << endl;
                            }
                            if (k == MaxFines - 1 && counter > 0)
                            {
                                bool isfinenumber = false;
                                while (isfinenumber == false)
                                {
                                    cout << "If you want to pay a fine enter its number \n or press(0)for more: ";
                                    int finenumber;
                                    cin >> finenumber;
                                    system("cls");

                                    if (driver[i].OwnedCars[j].Fine[finenumber - 1].FineValue != 0 && finenumber != 0)
                                    {
                                        isfinenumber = true;
                                        cout << "Your fine has been paid!!\n\n";
                                        driver[i].OwnedCars[j].Fine[finenumber - 1].Paid = true;
                                        driver[i].OwnedCars[j].Fine[finenumber - 1].FineValue = 0;
                                        k = MaxFines;

                                    }
                                    else if (finenumber > counter)
                                        cout << "Fine number does not exist!!" << endl;

                                    else if (finenumber == 0)
                                    {
                                        isfinenumber = true;
                                        Back = true;
                                        system("cls");
                                    }
                                }
                            }
                        }
                    }

            } if (TotalNumberOfFines == 0)
            {
                cout << "There's no fines for this car!!\n\n";
            }//when fines are zero it goes to previous menu
        }
        cout << "To sign out of your account press(1) \nTo go back to driver's options menu press(2) \nTo exit to main menu press(3): ";
        int driverSignOut;
        cin >> driverSignOut;
        if (driverSignOut == 1)
        {
            Back = true;
            driverMenu = false;
            system("cls");
        }
        else if (driverSignOut == 2)
        {
            Back = false;
            system("cls");
        }
        else if (driverSignOut == 3)
        {
            Back = true;
            driverMenu = true;
            system("cls");
        }
    } while (Back == false);
}
  
  
  
int main(){

    //Drivers samples
    Drivers driver1 = { "zack",456,
    {
        {784,"kia cerato",2012, { {  100 ,"90's street",  {5,8,2014} } ,{} }  }//fines
       ,{655,"BMW X6",2018, { {  50 ,"el tayaran street",  {11,2,2020} }, {} ,{} }  }
       ,{153,"Renault logan",2015, { { 200 ,"el nozha street",  {20,6,2016} } ,{} ,{} }  }
    
    }
        ,{15,6,1999} 

    };

    Drivers driver2={ "sam",114,
    {
        {417,"BMW X3",2017,{ { 70,"makram ebeid street",{19,10,2019} },{},{}}  }//fines
       ,{174,"chevorlet lanos",2013,{ { 200,"abo bakr el sedek street",{19,10,2017} },{},{}}  }
       ,{}//cars
    }
       ,{9,11,1980}
    };

    Drivers driver3={ "malcom",963,
    {
        {239,"nissan sunny",2016,{ { 80,"othman ebn afan street",{19,10,2018}},{},{}  } }//fines
       ,{}//carss
       ,{}
    }
       ,{21,8,1990}
    };

    driver[0] = driver1;
    driver[1] = driver2;
    driver[2] = driver3;

  
    char input = 'f';
    while (input != 'l') //system is open
    {
        system("color F0");
        //MAIN MENU:
        cout << "\nWelcome to the traffic control system\n\n";
        cout << "For traffic men adding fines press(1)\nFor driver's menu and fine payment press(2): ";
        int  press;
        cin >> press;
        system("cls");
        if (press == 1)//TRAFFIC MAN MENU:
        {
           
                cout << "*Traffic man menu*\n\n"; 
                bool trafficManMenu = false;
                while (trafficManMenu == false)//entering traffic man menu
                {
                    bool IsCorrectPlateNumber = false;
                    while (IsCorrectPlateNumber == false)
                    {
                        //violation function:
                        Violation(IsCorrectPlateNumber);
                    } //end of function
                    cout << "If you want to enter another fine press(y)\nor exit to the main menu press(n): ";//enter another fine or main menu
                    char key;
                    cin >> key;
                    if (key == 'y' || key == 'Y')
                    {
                        trafficManMenu = false;
                        system("cls");
                    }
                    else if (key == 'n' || key == 'N')
                    {
                        system("cls");
                        trafficManMenu = true;
                    }
                   
                }
        }
       

        else if (press == 2)//DRIVER MENU
        {
            string dname;
            Drivers d;
                  bool driverMenu = false;
                  while (driverMenu == false)
                  {
                     
                      int DriverPress = 0;
                      cout << "If you are already registered on this system and you want to sign in press(1)\nIf you're new and signing up press(2): ";
                      cin >> DriverPress;
                      system("cls");
                     if (DriverPress == 1)//signIn
                     {
                             int counter2 = 0;
                             cout << "*Driver's menu and fine payment*\n\n";
                             cout << "Please enter your license number: ";
                             cin >> d.licenseNum;
                             cout << "Enter your name: ";
                             cin.ignore();
                             getline(cin, dname);

                             //driver sign in with correct license number and name
                             for (int i = 0; i < MaxDrivers; i++)
                             {
                                 if (driver[i].licenseNum == d.licenseNum) 
                                     if ( driver[i].Name == dname)
                                 {
                                     //function (I,J)
                                     counter2++;
                                     bool Back = false;
                                     {

                                         Driver_information_or_payment(driverMenu, Back, i);
                                         i = MaxDrivers;
                                     }
                                     
                                 }
                             } if (counter2 == 0)
                             {
                                 cout << "INCORRECT license number or name!!\n\n";
                             }
                         
                     }
                     if (DriverPress == 2)//signUp
                     {
                       
                         int CurrentDriverIndex;
                         for (int i = 0; i < MaxDrivers; i++)
                         {
                             if (driver[i].licenseNum == 0)
                             {
                                 CurrentDriverIndex = i;
                                 cout << "Add driver's name: ";
                                 cin.ignore();
                                 getline(cin, driver[i].Name);
                                 cout << "Add driver's birthdate: \n(Day): ";
                                 cin >> driver[i].BirthDate.Day;
                                 cout << "(Month): ";
                                 cin >> driver[i].BirthDate.Month;
                                 cout << "(Year): ";
                                 cin >> driver[i].BirthDate.Year;

                                 bool IsLicenseTaken = false;
                                 while (IsLicenseTaken == false)
                                 {
                                     cout << "\nAdd your license number: ";
                                     int licenseNum;
                                     cin >> licenseNum;
                                     IsLicenseTaken = true;
                                     for (int j = 0; j < MaxDrivers; j++)
                                         if (licenseNum == driver[j].licenseNum)
                                             IsLicenseTaken = false;

                                     if (IsLicenseTaken == false)
                                         cout << "This license number is already taken\nPlease enter another one ";
                                     else if (IsLicenseTaken == true)//to save the lisence number:
                                     {
                                         driver[i].licenseNum = licenseNum;
                                         i = MaxDrivers;
                                     }
                                 }
                                 //driver can't sign up more than 3 cars
                                 bool carSignup = false;
                                 int k = 0;
                                 do
                                 {
                                     if (k < 2)
                                     {
                                         cout << "Add your car plate number: ";
                                         cin >> driver[CurrentDriverIndex].OwnedCars[k].PlateNum;
                                         cout << "Add car production year: ";
                                         cin >> driver[CurrentDriverIndex].OwnedCars[k].PYear;
                                         cout << "Add car model: ";
                                         cin.ignore();
                                         getline(cin,driver[CurrentDriverIndex].OwnedCars[k].Model);
                                         cout << "If you want to enter another car press(y)\n If not press(n)";
                                         char anotherCar;
                                         cin >> anotherCar;
                                         if (anotherCar == 'y' || anotherCar == 'Y')
                                         {
                                             carSignup = false;
                                             k++;
                                         }
                                         else if (anotherCar == 'n' || anotherCar == 'N')
                                         carSignup = true;  

                                     }
                                     else if (k == 2)
                                     {
                                         cout << "enter your car plate number: ";
                                         cin >> driver[CurrentDriverIndex].OwnedCars[k].PlateNum;
                                         cout << "enter car production year: ";
                                         cin >> driver[CurrentDriverIndex].OwnedCars[k].PYear;
                                         cout << "enter car model: ";
                                         cin >> driver[CurrentDriverIndex].OwnedCars[k].Model;
                                         cout << "Max number of cars is 3\n\n ";
                                         carSignup = true;
                                     }

                                 } while (carSignup == false);


                             }

                         }//function (current driver index ,J)
                             bool Back = false;

                                 
                                 Driver_information_or_payment( driverMenu, Back, CurrentDriverIndex);
                                 
                                   //end of function

                         
                     }
         
                  }
            
           
        }
 
    }


    return 0;
}
