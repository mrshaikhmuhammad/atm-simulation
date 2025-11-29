#include<iostream>
#include<ctime>
#include<string>
#include<vector>
#include<fstream>
#include<conio.h>
using namespace std;

string txt_address="DATABASE.txt";

string year(int n=0){
	time_t now=time(0);
	tm local_time=*localtime(&now);
	return to_string(local_time.tm_year-100+n);	
}

string generate_id(int ID){ //24-29-24
    string result=year()+"-"+year(5)+"-";
    string temp_id=to_string(ID);
    if(temp_id.length()>=4){
        result+=temp_id;
    }
    else{
        for(int i=0; i<4-temp_id.length(); i++){
            result+="0";               
        }
        result+=temp_id;
    }
    return result;
}

int decode_id(string id){
    string temp=id.substr(7);
    return stoi(temp);
}

int four_digit(int input){
    while((input/10000)!=0){
        input/=10;
    }
    return input;
}

class account{
	private:
		string name;
        string id;
		unsigned int balance;
		unsigned short int pin;
        int attemps=0;
	
	public:
		account(){
		}
        account(string NAME, int PIN, int ID, int BALANCE=0){
			name=NAME;
			pin=four_digit(PIN);
			balance=BALANCE;
			id=generate_id(ID);
		}

        string use_id(){
            return id;
        }
        string use_name(){
            return name;
        }
        int use_attempts(){
            return attemps;
        }
        void add_attemps(){
            attemps++;
        }

        void display(){
            cout<<"ID: "<<id<<endl;
            cout<<"Name: "<<name<<endl;
            cout<<"PIN : "<<pin<<endl;
            cout<<"Balance: "<<balance<<endl;
        }

        bool login(string ID, int PIN){
            if(ID==id){
                if(name=="Blocked Account"){
                    system("CLS");
                    cout<<"================================"<<endl;
                    cout<<"Your Account Was Blocked!"<<endl;
                    cout<<"================================"<<endl;
                    getch();
                    exit(-1);
                }
                if(PIN==pin){
                    return 1;
                }
                else{
                    add_attemps();
                }
            }
            return 0;
        }

		void create(int ID){
			string temp;
            string n1, n2;
            id=generate_id(ID);
            cout<<"================================"<<endl;
            cout<<"Enter First Name: ";
            cin>>n1;
            cout<<"Enter Last Name: ";
            cin>>n2;
            name=n1+" "+n2;
            cout<<"Enter 4 Digit Pin: ";
            cin>>pin;
            pin=four_digit(pin);
            cout<<"Enter Phone Number: ";
            cin.ignore();
            getline(cin, temp);

            cout<<"Enter Cinic: ";
            cin.ignore();
            getline(cin, temp);

            cout<<"Enter Address: ";
            cin.ignore();
            getline(cin, temp);
            balance=0;
            cout<<"================================"<<endl;
		}

        bool deposit(int amount=0, bool dialuoge=true){
                balance+=amount;
                if(dialuoge==true)
                    cout<<"Deposit Succesful"<<endl;
                return 1;
        }
        bool withdraw(int amount=0, bool dialuoge=true){
            if(balance>=amount){
                balance-=amount;
                if(dialuoge==true)
                    cout<<"Withdrawl Succesful"<<endl;
                return true;
            }
            if(dialuoge==true)
                cout<<"Unsufficient Balance"<<endl;
            return false;
        }

        void show_balance(){
            cout<<"================================"<<endl;
            cout<<"Current Balnce: "<<balance<<endl;
            cout<<"================================"<<endl;
        }

        void block(){
            name="Blocked Account";
			pin=0;
			balance=0;
        }

        string write_for_txt(){//creates row of table (Name|ID|Pin|Balance)
            return name+"|"+id+"|"+to_string(pin)+"|"+to_string(balance)+".";
        }
};

void create_account(vector <account> &input){
    account temp;
    temp.create(input.size());
    input.push_back(temp);

    system("cls");
    cout<<"================================"<<endl;
    cout<<"Details: "<<endl;
    cout<<"================================"<<endl;
    temp.display();
    cout<<"================================"<<endl;
    cout<<"Account was created Successfully"<<endl;
    cout<<"================================"<<endl;
}

string read_txt(){
    string temp, txt;
    ifstream txt_file(txt_address);
    if(txt_file.is_open()){
        while (getline(txt_file, temp)) { // Read line by line
            txt+=temp;
        }
    }
    else{
        cerr<<"Error! File can not be open for reading";
        exit(0);
    }
    txt_file.close();
    return txt;
}

void sync_line(string line, vector<account> &input) {
    string name, id;
    unsigned int balance;//salman|24-29-0002|2322|0.
    unsigned short int pin;

    // Extract `name`
    int pos = line.find('|');
    name = line.substr(0, pos);

    // Extract `id`
    int start = pos + 1;
    pos = line.find('|', start);
    id = line.substr(start, pos - start);

    // Extract `pin`
    start = pos + 1;
    pos = line.find('|', start);
    pin = stoi(line.substr(start, pos - start));

    // Extract `balance`
    start = pos + 1;
    pos = line.find('.', start);
    balance = stoi(line.substr(start, pos - start));

    // Create and add account to vector
    account temp(name, pin, decode_id(id), balance);
    input.push_back(temp);
}


void sync_txt(vector<account> &input) {
    string txt = read_txt(); // Read the entire file content
    size_t pos = 0;          // Current position in the string
    size_t start = 0;        // Start of the current line

    // Process each line until the end of the string
    while ((pos = txt.find('.', start)) != string::npos) {
        string line = txt.substr(start, pos - start); // Extract the line
        if (!line.empty()) {                         // Skip empty lines
            sync_line(line, input);                  // Parse the line
        }
        start = pos + 1; // Move to the start of the next line
    }

}

void update_txt(vector <account> &input){
    ofstream txt_file(txt_address);
    if(txt_file.is_open()){
        for(account temp: input){
            txt_file<<temp.write_for_txt()+"\n";
        }
    }
    else{
        cerr<<"Error! File can not be open for reading";
        exit(0);
    }
    txt_file.close();
}

void block_account(string ID, vector <account> &input){
    for(account &temp: input){
        if(temp.use_id()==ID)
            temp.block();
    }
}

bool created(){
    char option='&';
    do{ 
        system("CLS");
        if(option!='&'){
            cout<<"================================"<<endl;
            cout<<"INVALID OPTION"<<endl;
        }   
        cout<<"================================"<<endl;
        cout<<"1. Login Account"<<endl;
        cout<<"2. Create Account"<<endl;
        cout<<"================================"<<endl;
        cout<<"Choose : ";
        option=getche();
        cout<<"\n================================"<<endl;
        if(option=='1'){
            return 1;
        }
        if(option=='2'){
            return 0;
        }
    }while(true);
    return -1;
}

int input_pin(){
    char pin[5];
    pin[0]=getch();
    cout<<'*';
    pin[1]=getch();
    cout<<'*';
    pin[2]=getch();
    cout<<'*';
    pin[3]=getch();
    cout<<'*';
    pin[4]='\0';

    return stoi(pin);
}

int login_account(vector <account> &input){
    bool logged=true;
    string ID;
    int PIN;
    
    do{
        system("CLS");
        if(logged==false){
            cout<<"INVALID ID / PASSWORD"<<endl;     
        }
        cout<<"================================"<<endl;
        cout<<"Enter ID: ";
        cin.sync();
        getline(cin, ID);

        cout<<"Enter PIN: ";
        PIN=input_pin();
        cout<<"\n================================"<<endl;

        for(int i=0; i<input.size(); i++){
            if(input[i].login(ID, PIN)){
                logged=true;
                return i;
            }
            else{
                logged=false;
            }
            if(input[i].use_attempts()>=3){
                input[i].block();
                cout<<"3 WRONG ATTEMPS!!"<<endl;
                cout<<"ACOUNT BLOCKED"<<endl;
                cout<<"================================"<<endl;
                getch();
                update_txt(input);
                exit(-1);
            }
        }
    }while(logged==false);
    return -1;
}

int option_menu(account input){
    int option=0;
    do{
        system("CLS");
        if(option!=0){
            cout<<"================================"<<endl;
            cout<<"INVALID OPTION"<<endl;
        }
        cout<<"================================"<<endl;
        cout<<"Welcome "<<input.use_name()<<endl;
        cout<<"================================"<<endl;
        cout<<"1. Check Balance "<<endl;
        cout<<"2. Withdraw"<<endl;
        cout<<"3. Transfer Fund"<<endl;
        cout<<"4. Exit"<<endl;
        cout<<"================================"<<endl;
        cout<<"Choose: ";
        cin>>option;
        cout<<"================================"<<endl;
    }while(option<1 or option>4);

    return option;
}

void perform_task(int option, account &input, vector <account> &arr){
    system("CLS");
    int amount=0;
    switch(option){
        case 1: input.show_balance();
                break;
        
        case 2: cout<<"================================"<<endl;
                cout<<"Enter Amount: ";
                cin>>amount;
                cout<<"================================"<<endl;
                input.withdraw(amount);
                cout<<"================================"<<endl;
                break;
        
        case 3: do{
                    system("CLS");
                    string ID;
                    cout<<"================================"<<endl;
                    cout<<"Enter Recipent's ID: ";
                    cin>>ID;
                    cout<<"Enter Amount: ";
                    cin>>amount; 
                    cout<<"================================"<<endl;
                    for(int i=0; i<arr.size(); i++){
                        if(arr[i].use_id()==ID){
                            if(input.withdraw(amount, false)){
                                arr[i].deposit(amount, false);
                                cout<<amount<<" Transfered to "<<arr[i].use_name()<<endl;
                                cout<<"================================"<<endl;
                            }
                            else{
                                cout<<"Insufficient Balance"<<endl;
                                cout<<"================================"<<endl;
                            }
                            
                            return;
                        }
                    }
                    
                }while(true);
                break;

        case 4: cout<<"================================"<<endl;
                cout<<"Thanks "<<input.use_name()<<endl;
                cout<<"================================"<<endl; 
                update_txt(arr);
                getch();
                exit(-1);
                break;
    }
}

int main(){
    vector <account> accounts;
    int index;
    sync_txt(accounts);
    
    if(created()){
        index=login_account(accounts);
        while(true){
        perform_task(option_menu(accounts[index]), accounts[index], accounts);
        getch();
        }
    }
    else{
        system("CLS");
        create_account(accounts);
    }

    update_txt(accounts);
    getch();
	return 0;
}