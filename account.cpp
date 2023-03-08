#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;
//database
static int db_number=0;
//BankAccount Creation (Mother class)
class BankAccount{
    protected:
        string acc_name, depositor_name;
        char acc_type;
        int acc_number;
        double acc_balance, deposit;
        int PIN;
    public:
        //creating account
        void createAccount(char account_type);
        //displaying details in the account
        void DisplayAccountsInfor();
        void depositToAccount(int acc_number);
        void checkBalance(int acc_number);

};
void BankAccount::createAccount(char account_type){
    system("CLS");
    cout<<"Account Creator's Name: "<<"\n";
    cin>>acc_name;
    acc_name_db[db_number] =acc_name;
    cout<<"Account Number: "<<"\n";
    cin>>acc_number;
    acc_number_db[db_number] = acc_number;
    cout<<"Set Pin: "<<"\n";
    cin>>PIN;
    PIN_db[db_number] =PIN;
    acc_type_db[db_number] = account_type;
    cout<<"Initial Deposit (for cur_account>=5000 and sav_account>=10000): "<<"\n";
    cin>>deposit;
    acc_balance_db[db_number] = deposit;
    depositor_name = acc_name;
    depositor_name_db[db_number]=depositor_name;
    //Establishing to deduct the minimum requirement so that it is ot shown to the account owner;
    //increaments everytime an account is created.
    db_number++;
}
//checking Balance
void BankAccount::checkBalance(int acc_number){
    for (int a=0;a<=db_number;a++){
        if (acc_number_db[a]==acc_number){
            cout<<acc_balance_db[a]<<"\n";
            break;
        }
    }

}
//Displaying all the accounts in the system
void BankAccount::DisplayAccountsInfor(){
    system("CLS");
    cout<<"|Account Number |Account Name |Account Type |Account Balance |Depositor Name|"<<"\n";
     for (int a=0;a<db_number;a++){
        cout<<"|"<<setw(15)<<acc_number_db[a]<<"|"<<setw(13)<<acc_name_db[a]<<"|"<<setw(13)<<acc_type_db[a]<<"|"<<setw(16)<<acc_balance_db[a]<<"|"<<setw(14)<<depositor_name_db[a]<<"|"<<"\n";
    }
}
//Depositing to the account
void BankAccount::depositToAccount(int acc_number){
    for (int i=0;i<db_number+1;i++){
        if (acc_number_db[i]==acc_number){
            cout<<"Input amount: ";cin>>deposit;
            acc_balance_db[i] +=deposit;
            break;
        }
    }
}
//savings account inheriting from BankAccount
class Sav_Account:public BankAccount{
    private:
        double compound_interest,bank_interest;
    public:
        double minimum_amount = 5000.0;
        void computeInterest(int acc_number);
        void withdraw(int acc_number, double amount, int pin);
}sav_group[120];
//computing for compound interest
void Sav_Account::computeInterest(int acc_number){
    const int time_period = 1;
    float rate=0.02;

    for (int i=0;i<db_number+1;i++){
        if (acc_number_db[i]==acc_number){
            double Amount = pow(acc_balance_db[i]*(1+rate),time_period);
            compound_interest = Amount - acc_balance_db[i];
            acc_balance_db[i] = Amount;
            break;
            
        }
    }
    
}
//withdrawing 
void Sav_Account::withdraw(int acc_number,double amount, int pin){
    //constraint to check for penalty
     for (int i=0;i<db_number+1;i++){
        if ((acc_number_db[i]==acc_number)&&(PIN_db[i]==pin)){
            if (((acc_balance_db[i]-amount)<minimum_amount)&&((acc_balance_db[i]-amount)>0)){
                cout<<"You have successfully withdrawn"<<amount<<"but with a penality of 2000 imposed"<<"\n";
                acc_balance_db[i] -=(amount+2000);
            }
            else if((acc_balance_db[i]-amount)>minimum_amount){
                cout<<"You have successfully withdrawn "<<amount<<"\n";
                acc_balance_db[i] -=amount;
            }
            else if((acc_balance_db[i]-amount)<0){
                cout<<"Your account balance is low for this transaction to occur"<<"\n";
                cout<<"You have "<<acc_balance_db[i]<<"left on your account"<<"\n";
            }else{
                cout<<"Problems with your account"<<"\n";
            }
            break;
        } else if((acc_number_db[i]!=acc_number)or(PIN_db[i]!=pin)){
            cout<<"Problems with your account"<<"\n";
        }else{
            
        } 
    }
}
//current account inheriting from BankAccount
class Cur_Account:public BankAccount{
    private:
        int cheque_no;
        string receiver_name, memo, cheque_date;
        double cheque_amount;
    public:
        double minimum_amount = 10000.0;
        void createCheque();
        void chequeWithdraw();
}cur_group[100];
void Cur_Account:: createCheque(){
    cout<<"Enter the account Number to create cheque"<<"\n";
    cin>>acc_number;
    cout<<"Enter your pin"<<"\n";
    cin>>PIN;
    cout<<"Enter the cheque Number"<<"\n";
    cin>>cheque_no;
    cout<<"Enter the REceiver Name"<<"\n";
    cin>>receiver_name;
    cout<<"Enter the Reason For cheque creation"<<"\n";
    cin>>memo;
    cout<<"Enter the Amount"<<"\n";
    cin>>cheque_amount;
    cout<<"Enter the date of maturity"<<"\n";
    cin>>cheque_date;
    for (int i=0;i<db_number+1;i++){
        //constraint implemented here for penality and the penality is of 2000
        if (PIN_db[i]==PIN){
            if (((acc_balance_db[i]-cheque_amount)<minimum_amount)&&((acc_balance_db[i]-cheque_amount)>0)){
                cout<<"You have successfully initiated a cheque of  "<<cheque_amount<<"but with a penality of 2000 imposed "<<"\n";
                acc_balance_db[i] -=(cheque_amount+2000);
            }
            else if((acc_balance_db[i]-cheque_amount)>minimum_amount){
                cout<<"You have successfully initiated a cheque of"<<cheque_amount<<"\n";
                acc_balance_db[i] -=cheque_amount; 
            }
            else if((acc_balance_db[i]-cheque_amount)<0){
                cout<<"Your account balance is low for this transaction to occur"<<"\n";
                cout<<"You have"<<acc_balance_db[i]<<"left on your account"<<"\n";
            }
            else{
                cout<<"Error with your account"<<"\n";
            }
            break;
        }  
    }
}
void Cur_Account:: chequeWithdraw(){
    int cheque_number;
    cout<<"Enter cheque Number"<<"\n";
    cin>>cheque_number;
    cout<<"Enter account Number"<<"\n";
    cin>>acc_number;
    if (cheque_number == cheque_no)
    {
        cout<<"You have withdrawn: "<<cheque_amount<<"\n";
    }else{
        cout<<"invalid Cheque"<<"\n";
    }
}
int main(){
    system("CLS");
    //creating the accounts
    int acc_number;
    int op;
    while(1){
        int control=1;
        char type;
        cout<<"================WELCOME TO STANBIC BANNK==================="<<"\n";
        cout<<"Enter S for saving's a/c and C for current a/c customer :"<<"\n";
        cin>>type;
        type=toupper(type);
        //op is the option for selecting
        if (type=='S'){
            do{
                cout<<"=====================SAVINGS ACCOUNT============================="<<"\n";
                cout<<"\t\t1. NEW ACCOUNT";
                cout<<"\n\t\t2. DEPOSIT AMOUNT";
                cout<<"\n\t\t3. WITHDRAW AMOUNT";
                cout<<"\n\t\t4. CHECK BALANCE";
                cout<<"\n\t\t5. ALL ACCOUNT HOLDER LIST";
                cout<<"\n\t\t6. EXIT";
                cout<<"\n==========================================================\n";
                cout<<"\nSelect your Option:\n";
                cin>>op;
                switch (op){
                    case 1:
                        sav_group[].createAccount(type);
                        sav_group[].DisplayAccountsInfor();
                        break;
                    case 2:
                        cout<<"Enter the account Number";
                        cin>>acc_number;
                        sav_group[].depositToAccount(acc_number);
                        sav_group[].computeInterest(acc_number);
                        break;
                    case 3:
                        cout<<"Withdrawing Mode by "<<"\n";
                        int acc_number;
                        float amount; 
                        int pin;
                        cout<<"Enter the Account Number"<<"\n";
                        cin>>acc_number;
                        cout<<"Enter the Account Pin"<<"\n";
                        cin>>pin;
                        cout<<"Enter the Amount to withdraw"<<"\n";
                        cin>>amount;
                        sav_group[].withdraw(acc_number, amount, pin);
                        break; 
                    case 4:
                        cout<<"Enter the account Number";
                        cin>>acc_number;
                        sav_group[].checkBalance(acc_number);
                        break;
                    case 5:
                        sav_group[].DisplayAccountsInfor();
                        break;
                    case 6:
                        cout<<"Thanks for using our system";
                        exit(0);
                    default:
                        exit(0);
                }
                cout<<". Continue\n1. Choose Account"<<"\n";
                cin>>control;
            } while(control!=0);
        }
        else if (type='C')
        {
            do{
                cout<<"=====================CURRENT ACCOUNT============================="<<"\n";
                cout<<"\t\t1. NEW ACCOUNT";
                cout<<"\n\t\t2. DEPOSIT AMOUNT";
                cout<<"\n\t\t3. CHECK BALANCE";
                cout<<"\n\t\t4. WITHDRAW BY CHEQUE";
                cout<<"\n\t\t5. CREATE CHEQUE";
                cout<<"\n\t\t6. ALL ACCOUNT HOLDER LIST";
                cout<<"\n\t\t7. EXIT";
                cout<<"\nSelect your Option:\n";
                cout<<"\n==========================================================\n";
                cin>>op;
                switch (op){
                    case 1:
                        cur_group[].createAccount(type);
                        cur_group[].DisplayAccountsInfor();
                        break;
                    case 2:
                        cout<<"Enter the account Number";
                        cin>>acc_number;
                        cur_group[].depositToAccount(acc_number);
                        break;
                    case 3:
                        cout<<"Enter the account Number";
                        cin>>acc_number;
                        cur_group[].checkBalance(acc_number);
                        break;
                    case 4:
                        cur_group[].chequeWithdraw(); 
                        break;
                    case 5:
                        cur_group[].createCheque();
                        break;
                    case 6:
                        cur_group[].DisplayAccountsInfor();
                        break;
                    case 7:
                        cout<<"Thanks for using our system";
                        exit(0);
                    default:
                        cout<<"Option not there  chose another one"<<"\n";
                }
                cout<<"0. Continue\n1. Choose Account"<<"\n";
                cin>>control;
            }while(control!=0);      
        }
        else{
                cout<<"Not what is expected"<<"\n";
        }
    }
    //at exit waits for you to press any key
    cin.get();
}