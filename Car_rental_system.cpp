#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <iterator>
using namespace std;

//Creating Car class for individual car
class Car {
  public:
    int id;
    string model;
    string type;
    int speed;
    int rent_price_hourly;
    Car();
    Car(int id, string model, string type, int speed, int rent_price_hourly) {
        this->id = id;
        this->model = model;
        this->type = type;
        this->speed = speed;
        this->rent_price_hourly = rent_price_hourly;
    }

    string getModel() {
        return model;
    }
    int getId() {
        return id;
    };
    // extraction
    void setCarInfo(int id, string model, string type, int speed, int rent_price_hourly) {
        this->id = id;
        this->model = model;
        this->type = type;
        this->speed = speed;
        this->rent_price_hourly = rent_price_hourly;
    }

    friend ostream& operator <<(ostream& os, Car &car);
};
//Overload << car
ostream& operator << (ostream& os, Car &car) {
    os <<"Id: " << car.id << "\n" << "\tBrand: " << car.model << "\n";
    os << "\tType: " << car.type << "\n" << "\tSpeed: " << car.speed << " mph\n";
    os << "\tRent Price per hour: " << car.rent_price_hourly << " TK\n";
    return os;
}

//Class to manage all the cars that are in stock
//Actully it's a database of cars
class ManageCar { // showRoom
  public:
    vector <Car> cars;
    set <string> models; // brand

    void addCar(Car *car) {
        cars.push_back(*car);
    }

    void removeCar(int id) { // 0
        for(int i = 0; i < cars.size(); i++) {
            if(cars[i].getId()== id) {
                cars.erase(cars.begin()+i);
                break;
            }
        }
    }

    void showModels() {
        for(auto it = cars.begin(); it!=cars.end(); it++) {
            string model = it->getModel();
            models.insert(model);
        }
        int i = 1;
        for(auto it : models) {
            cout << "\t" << i << " : " << it << "\n";
            i++;
        }
    }

    void showCars(string model) {
        for(auto it = cars.begin(); it != cars.end(); it++) {
            if(it->getModel() == model) cout << "\t" << *it << "\n";
        }
    }

    void showCarList() {
        for(auto it = cars.begin(); it!=cars.end(); it++) {
            cout << "\t" << *it << "\n";
        }
    }

    string getModel(int i) {
        int j = 0;
        string found;
        for(auto it = models.begin(); it!=models.end(); it++) {
            found = *it;    j++;
            if(j==i) break;
        }
        return found;
    }

    int bills(int car_id,int duration) {
        int temp=0;
        for(auto it = cars.begin(); it!=cars.end(); it++) {
            if(it->id==car_id) return (it->rent_price_hourly * duration);
        }
        return temp;
    }
};

class Person {
  public:
    string name;
    int age;
    Person();
    Person(string name, int age) { //Parameterized constructor
        this->name = name;
        this->age = age;
    }
    string getName() {
        return name;
    }
    int getAge() {
        return age;
    }
    void print() {
        cout << "\tName: " << name << "\n" << "\tAge: " << age << "\n";
    }
};

class Renter:public Person { //Inheriting the person class
    public:
    string address;
    string email;
  public:
    Renter();
    Renter(string name, int age, string address, string email):Person(name,age) {
        this->address = address;
        this->email = email;
    }
    void setRenterInfo(string name, int age, string address, string email) {
        Person(name,age);
        this->address = address;
        this->email = email;
    }
    string getAddress() {
        return address;
    }
    string getEmail() {
        return email;
    }
    void print() {
        Person::print();//function overriding
        cout << "\tAddress: " << address << "\n" << "\tEmail: " << email << "\n";
    }
};

class Booking { //This class will perform a single rent operation
    Renter *r;
    int rent_id;//automatically generated
    int rent_duration;
    int rent_bill;//automatically generated
    int transaction_id;
    string rent_name, rent_add, rent_email;
    int rent_age;
  public:
    Booking();
    Booking(Renter *r,int rent_id,int rent_duration,int rent_bill,int transaction_id) {
        this->r = r;
        this->rent_id = rent_id;
        this->rent_duration = rent_duration;
        this->rent_bill = rent_bill;
        this->transaction_id = transaction_id;
        rent_name = r->name;
        rent_age = r->age;
        rent_add = r->address;
        rent_email = r->email;
    }
    int getRentId() {
        return rent_id;
    }
    void getRentInfo() {
        cout << "\tRent id: " << rent_id << "\n";
        //r->print();//Overriding the print function
        cout << "\tName: " << rent_name << "\n" << "\tAge: " << rent_age << "\n";
        cout << "\tAddress: " << rent_add << "\n" << "\tEmail: " << rent_email << "\n";
        cout << "\tTotal rent duration : " << rent_duration << " Hours" << "\n";
        cout << "\tTotal rent bill: " << rent_bill << " TK\n";
        cout << "\tTransaction id: " << transaction_id << "\n\n";
    }
};

//RentalSystem class, The flow of the program will be controlled from here.

class RentalSystem {
    vector <Renter> renters;
    vector <Booking> rent_records;
    int rent_id = 1234500;
  public:
    void addRentRecord(Booking *r) {
        rent_records.push_back(*r);
    }

    void remove_rent_records(int id) {
        int len = rent_records.size();
        for(int i = 0; i < len; i++) {
            if(rent_records[i].getRentId()== id) {
                rent_records.erase(rent_records.begin()+i);
                break;
            }
        }
    }

    void showRentRecords() {
        for(auto it : rent_records) {
            it.getRentInfo();
            cout << "\n";
        }
    }

    ///Control the entire system from here.

    void menu() {
        int option=1;
        ManageCar manage;

        //Uncomment below part to load data from input file.

        ifstream openFile("in.txt");
        for(; !openFile.eof();) { // end of file
            int id,speed,rent_price_hourly;
            string model,type;
            openFile>>id>>model>>type>>speed>>rent_price_hourly;
            Car c(id,model,type,speed,rent_price_hourly);
            manage.addCar(&c);//Adding car to the system
        }
        openFile.close();

        while(option) {
            //Options here
            cout << "\n\t\t\t\t::CAR RENTAL SYSTEM::" << endl;
            cout << "\n........Select an option from below: \n\n";
            cout << "\t1) Manage Cars (Only for Admin)\n";
            cout << "\t2) Rent a car\n";
            cout << "\t0) Exit\n";
            cout << "\n\tEnter option: ";
            cin>>option;

            system("CLS");

            if(!option) {
                break;
            }
            switch(option) {
            case 1: {
                string pass = "Admin", s;
                cout << "\tPlease Enter your password: ";
                cin >> s;
                while(s != pass) {
                    cout << "\tWrong password! Enter again: ";
                    cin >> s;
                }
                system("CLS");
                int sub_opt = 1;
                while(sub_opt) {
                    //Sub Options for administrator
                    cout << "\n........Select an option: \n\n";
                    cout << "\t1) See all car\n";
                    cout << "\t2) See brand list\n";//From here another branch to see car by model
                    cout << "\t3) Add new car\n";
                    cout << "\t4) Remove car\n";
                    cout << "\t5) See rent records\n";
                    cout << "\t6) Remove rent records\n";
                    cout << "\t0) Go to main menu\n";
                    cout << "\n........Enter option: ";
                    cin>>sub_opt;
                    system("CLS");
                    switch(sub_opt) {
                    case 1: {
                        cout << "\n\n........Below are the cars in stock now----\n\n";
                        manage.showCarList();
                        int br;
                        cout << "\tEnter 0 to go back: ";
                        cin>>br;
                        system("CLS");
                        if(!br) break;
                    }
                    case 2: {
                        cout << "\n";
                        manage.showModels();
                        cout << "\n\tEnter an option: ";
                        int sub_opt_1;
                        cin>>sub_opt_1;
                        string model = manage.getModel(sub_opt_1);
                        cout << "\n........All cars of model " << model << "----\n\n";
                        manage.showCars(model);
                        int br;
                        cout << "\tEnter 0 to go back: ";
                        cin>>br;
                        system("CLS");
                        if(!br) break;
                    }
                    case 3: {
                        int id,speed,rent_price_daily;
                        string model,type;
                        cout << "\tEnter id: ";    cin >> id;
                        cout << "\tEnter Brand: "; cin >> model;
                        cout << "\tEnter type: ";  cin >> type;
                        cout << "\tEnter speed: "; cin >> speed;
                        cout << "\tEnter rent price per hour: ";
                        cin >> rent_price_daily;

                        Car c(id,model,type,speed,rent_price_daily);
                        manage.addCar(&c);

                        cout << "\n........A car has been added successfully. \n\n";
                        int br;
                        cout << "\tEnter 0 to go back: ";
                        cin>>br;
                        system("CLS");
                        if(!br) break;
                    }
                    case 4: {
                        int id;
                        cout << "\tEnter the id of the car: ";
                        cin>>id;
                        manage.removeCar(id);
                        cout << "\n........A car has been removed successfully\n";
                        int br;
                        cout << "\tEnter 0 to go back: ";
                        cin>>br;
                        system("CLS");
                        if(!br) break;
                    }
                    case 5: {
                        cout << "\n";
                        cout << "........Below are the rent records\n\n";
                        showRentRecords();
                        int br;
                        cout << "\tEnter 0 to go back: ";
                        cin>>br;
                        system("CLS");
                        if(!br) break;
                    }
                    case 6: {
                        cout << "\n";
                        showRentRecords();
                        int id;
                        cout << "\tEnter id of the record to be deleted: ";
                        cin>> id;

                        remove_rent_records(id);
                        cout << "\n\tRecord has been removed successfully\n\n";
                        int br;
                        cout << "\tEnter 0 to go back: ";
                        cin>>br;
                        system("CLS");
                        if(!br) break;
                    }
                    case 0:
                        break;
                    default:
                        break;
                    }
                }
                break;
            }
            case 2: {
                //Customers will see the outcome of these codes
                int sub_opt = 1;
                cout << "\n........Choose model to rent from below: \n\n";
                while(sub_opt) {
                    //Showing the car models
                    manage.showModels();
                    cout << "\n\tEnter an option: ";
                    cin>>sub_opt;
                    system("CLS");

                    string model = manage.getModel(sub_opt);
                    //Showing the of that specific model
                    cout << "\n........Please choose a car from below----\n\n";
                    manage.showCars(model);
                    cout << "\tEnter the car id to rent: ";
                    int car_id; cin>>car_id;

                    system("CLS");
                    //Complete the registration form to rent the car i.e give personal information
                    cout << "\n........Now please fill up these form to complete the rent----\n\n";
                    string name,address,email;
                    int age,transaction_id;
                    cin.ignore();

                    cout << "\tEnter name: ";   getline(cin,name);
                    cout << "\tEnter age: ";    cin>>age;
                    cin.ignore();

                    cout << "\tEnter address: ";getline(cin,address);
                    cout << "\tEnter email: ";  cin>>email;

                    //Filling personal info
                    Renter renter(name,age,address,email);
                    //Automatically setting the rent id;
                    int rent_duration,rent_bill;
                    cout << "\tEnter rent duration in hour: ";
                    cin>>rent_duration;

                    rent_bill = manage.bills(car_id,rent_duration);

                    system("CLS");
                    cout << "\n........Your rent bill is: " << rent_bill << " TK\n\n";
                    cout << "........Please pay the bill via bank account to further proceed\n\n";
                    cout << "\tNow please enter your transaction id to confirm: ";
                    cin >> transaction_id;
                    //Filling up rent info
                    Booking rent(&renter,rent_id,rent_duration,rent_bill,transaction_id);
                    rent_id += transaction_id;
                    rent_id++;

                    //Adding the record to the system after completing the rent process.
                    addRentRecord(&rent);
                    system("CLS");

                    cout << "\n\n\t!!!Congratulation, Your rent has been successfully completed\n";
                    cout << "\tYour voucher id is : " << rent_id-1 << "\n";
                    cout << "\tPlease contact our office with the voucher id to get your car.\n\n";

                    manage.removeCar(car_id);
                    cout << "\tEnter 0 to go to menu: ";
                    cin>>sub_opt;
                    system("CLS");
                    if(!sub_opt) break;
                }
                break;
            }

            }
        }
    }
};

int main() {
    //Driver code
    RentalSystem sys;
    sys.menu();
    return 0;
}
