/*
    BANKING SYSTEM 
    @author:- Rishav Kumar
    
    No input check has been done 
    
    and no data will be saved
     
*/




#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>                                 //will use unix timestamp for account number.....


#include <termios.h>                            //for implementing getch in gcc
#include <unistd.h>

#define MAX 100


/*
    GLOBAL VARIABLE DECLARATION
    
    saving us from referencing pointer's 
    not a wise choice thuogh
    
*/

struct People{
    
    char firstName[50];
    char lastName[50];
    float balance;
    char password[5];
    
    unsigned long accountNumber;
};


//--------------------------- user's function declaration start's here ---------------

void decoration();
void options();
int createAccount();
void signIn();
int validateUser(int);
int searchIndex(unsigned long);
float transaction();
int depositMoney(int,float);
int withdrawMoney(int,float);
int transferMoney(int, int, float);
void welcome_user(int index);

//------------------------- user's function declaration end's heree ----------------------------


//------------------------- admin function declaration start's here ----------------------------

void admin_options();
void admin();
int admin_validation();
void user_records();
void notice();
void admin_update_record();

//------------------------- admin function declaration end's here. -----------------------------




int getch(void);
int getche(void);

struct People p[MAX];
unsigned int count;

int index_for_acc_no[MAX];



int main(){
    
    
    
    int choice;
    int index = -1; //index for signing in...
    int flag = 0; //Account can't be created flag, it will turn to some positive integer when account get created...
    
    count = 0;
    
    while(1){  //infinite loops start's here....
    
        system("clear");
        decoration();
        options();
        scanf("%d",&choice);
        
        switch(choice){ //swith start's here
            
            case 1:
                flag = createAccount();
                
                if(flag == 1)
                    welcome_user(count-1);
                else
                    printf("\n Unable to create account");
                    
                break;
                
            case 2:
                signIn();
                break;
                
            case 3:
                //admin, needed it to know the account number and password of users....
                admin();
                break;
                
                
            case 4:
                exit(0);
                
            default:
                printf("\n Something goes wrong");
                printf("\n Rechoose your options");
                break;
            
            
        }   //switch end's here...
        
        
        
    }                                  //infinite loops end here....
    
    return 0;
    
}


// users' function definition here

void decoration(){
    
    
    /*
    
    printf("\n\t\t\t\t\t ######   #######   ######   ##    ## #### ########     ###    ##    ## ##    ## \n");
    printf("\t\t\t\t\t##    ## ##     ## ##    ##  ###   ##  ##  ##     ##   ## ##   ###   ## ##   ##  \n");
    printf("\t\t\t\t\t##       ##     ## ##        ####  ##  ##  ##     ##  ##   ##  ####  ## ##  ##   \n");
    printf("\t\t\t\t\t##       ##     ## ##   #### ## ## ##  ##  ########  ##     ## ## ## ## #####    \n");
    printf("\t\t\t\t\t##       ##     ## ##    ##  ##  ####  ##  ##     ## ######### ##  #### ##  ##   \n");
    printf("\t\t\t\t\t##    ## ##     ## ##    ##  ##   ###  ##  ##     ## ##     ## ##   ### ##   ##  \n");
    printf("\t\t\t\t\t ######   #######   ######   ##    ## #### ########  ##     ## ##    ## ##    ## \n\n");
    
    */
    
    
    
    printf("\n\t\t\t\t\t  _____                  _ ____              _    ");
    printf("\n\t\t\t\t\t / ____|                (_)  _ \\            | |   ");
    printf("\n\t\t\t\t\t| |     ___   __ _ _ __  _| |_) | __ _ _ __ | | __");
    printf("\n\t\t\t\t\t| |    / _ \\ / _` | '_ \\| |  _ < / _` | '_ \\| |/ /");
    printf("\n\t\t\t\t\t| |___| (_) | (_| | | | | | |_) | (_| | | | |   < ");
    printf("\n\t\t\t\t\t \\_____\\___/ \\__, |_| |_|_|____/ \\__,_|_| |_|_|\\_\\");
    printf("\n\t\t\t\t\t              __/ |                               ");
    printf("\n\t\t\t\t\t             |___/      \n\n");
    
}


void options(){
    
    printf("\n Please choose the number from the below options\n");
    printf("\n 1.Create Account");
    printf("\n 2.Sign In");
    printf("\n 3.Admin");
    printf("\n 4.Exit");
    printf("\n Your choice ");
}


int createAccount(){
    
    
    
    if(count > MAX)
            return 0;
            
    
    
    notice();
    
    printf("\n Enter your first name :- ");
    scanf("%s",p[count].firstName);
    
    printf("\n Enter your last name :- ");
    scanf("%s",p[count].lastName);
    
    printf("\n Enter the 4 character password :- ");
    scanf("%s",p[count].password);
    
    p[count].balance = 0;
    
    
    p[count].accountNumber = (unsigned long) time(NULL);
    
    index_for_acc_no[count] = p[count].accountNumber;
    
    count += 1;
    
    return 1;           //account get successfully created...
    
}

void signIn(){
    
    unsigned long user_acc_no;
    int index;
    
    printf("\n Enter your account number ");
    scanf("%lu",&user_acc_no);
    
    index = searchIndex(user_acc_no);
    
    if(index >= 0){
        
        if(validateUser(index)){
            welcome_user(index);
            
        }else{
            printf("\n Wrong password, please re-try.");
        }
        
    }else
        printf("\n Sorry, this account doesn't exist");
    
    
}

int searchIndex(unsigned long acc_no){
    
    for(int i = 0; i <  MAX; ++i)
        if(index_for_acc_no[i] == acc_no)
            return i;
    
    return -1;
    
}

int validateUser(int index){
    
    char dup_password[5];
    
    printf("\n Enter your password\n");
    scanf("%s",dup_password);
    
    if(strcmp(p[index].password, dup_password) == 0)
        return 1;
    else
        return 0;
    
}

float transaction(){
    float m;
    
    printf("\n Enter the amount of money ");
    scanf("%f",&m);
    
    return m;
}

int depositMoney(int index, float money){
    
    if(index > count || index < 0)
            return 0;
    
    p[index].balance += money;

    return 1;
}


int withdrawMoney(int index, float money){
    
 
    if(p[index].balance - money >= 0){
            p[index].balance -= money;
            return 1;
    }
    else
        return 0;
    
}

int transferMoney(int index1, int index2, float money){
    int flag = 0;
    
    
    flag = withdrawMoney(index1,money);
    
    if(flag == 1){
        depositMoney(index2,money);
        return 1;
        
    }else
        return 0;
    
    
}

void welcome_user(int index){
    
    unsigned long t_acc_no;
    int choice;
    int index_for_other_user = -1;                                        // by default no account exist.
    int flag = 0;                                          //flag value
    
    
    
    while(1){
        
    system("clear");                   //system("cls") for windows....
    
    printf("\n\n Welcome %s %s",p[index].firstName,p[index].lastName);
    printf("\n Account Number :- %lu",p[index].accountNumber);
    printf("\n\n Here is what you can do");
    printf("\n 1.Look at your balance");
    printf("\n 2.Deposit Money");
    printf("\n 3.Withdraw Money");
    printf("\n 4.Transfer Money");
    printf("\n 5.Log out");
    printf("\n Enter number of your choice ");
    
    scanf("%d",&choice);
    
    
    switch(choice){
        
        case 1:
            printf("\n Your current Balance is Rs %.2f",p[index].balance);
            break;
            
        case 2:
            flag = depositMoney(index,transaction());
            if(flag == 1)
                printf("\n Successfully deposited, Your update balance is Rs %.2f",p[index].balance);
            else
                printf("\n Unable to deposite money");
            break;
            
        case 3:
            flag = withdrawMoney(index,transaction());
            
            if(flag == 1){
                printf("\n Successfully withdrawn the given amount");
                printf(", Your current balance is Rs %.2f",p[index].balance);
            }else   
                printf("\n Sorry, not able to withdraw the money");
                
            break;
            
        case 4:
           printf("\n Please enter the account number of person you want to transfer ");
           scanf("%lu",&t_acc_no);
            
            
            index_for_other_user = searchIndex(t_acc_no);
            
           if(index_for_other_user >= 0){
               
               if(validateUser(index))
                        flag = transferMoney(index, index_for_other_user, transaction());
                else{
                    
                    printf("\n Wrong password, you are logged out!");
                    
                    getch();
                    return;
                }
           }else{
               printf("\n Sorry, no account exist with this account number");
           }
            
           //flag = transferMoney(index, index_for_other_user, transaction());
           
           if(flag == 1){
                printf("\n Money transfer successfully");
                flag = 0;
                
           }else
                printf("\n Money doesn't transfer, may be account number you enter is wrong");
                
           break;
            
        case 5:
            return;
            
        default:
            printf("\n Sorry, you have been signed out");
            break;
    }
    
    
    getch();
    
    
    }
    
    return;
    
}


//admin function definition start's here



void notice(){
    
    printf("\n------------------------------------INFORMATION------------------------------------\n");
    printf("\n Welcome User, to cognibank.");
    printf("\n Here are some information that you need to remember.");
    printf("\n Remember your account number, for future transaction.");
    printf("\n Create four character password only.");
    printf("\n Never share your password with anyone.");
    printf("\n And don't forget your password either.");
    printf("\n In case you forget password, please contanct admin.");
    printf("\n Thank you, for giving us chance to serve you.");
    printf("\n\n-----------------------------------------------------------------------------------\n\n");
    
    
}


void admin_options(){
    
    printf("\n Hello Admin, enter the number of your choice\n");
    printf("\n 1. Look at Records");
    printf("\n 2. Change User password");
    printf("\n 3. Logout");
    printf("\n Your choice ");
    
    
}


void user_records(){
    
    for(int i = 0; i< count; ++i){
        printf("\n\n -----------------------------------Users %d-------------------------------\n",i+1);
        printf("\n %s %s",p[i].firstName, p[i].lastName);
        printf("\n Account Number :- %lu",p[i].accountNumber);
    }    
    
        printf("\n ------------------------------------END-----------------------------------\n\n");
    return;
}

int admin_validation(){
    char admin_name[] = "rishav";                                     //change it as you need
    char admin_password[] = "helloworld";                             //change it as you need
    
    char temp_name[50], temp_password[50];
    
    printf("\n Enter your username :- ");
    scanf("%s",temp_name);
    
    printf("\n Enter your password :- ");
    scanf("%s",temp_password);
    
    if(strcmp(admin_name, temp_name) == 0 && strcmp(admin_password, temp_password) == 0)
        return 1;
    else
        return 0;
    
}



void admin(){
    
    int choice;
    
    if(admin_validation() == 0){
        printf("\n Sorry, you are not authorized to view this page");
        return;
    }
    
    system("clear");
    
    while(1){                          //infinite loops start here..
        
        
        admin_options();
        scanf("%d",&choice);
        
        switch(choice){                //switch start's here..
            
            case 1:
                user_records();
                getch();
                break;
            
            case 2:
                admin_update_record();
                break;
            
            case 3:
                return;
            
            default:
                printf("\n Please choose from the given options");
                
            
        }                            //switch end's here....
        
    }                               //infinite loops end here.....
}



void admin_update_record(){
    
    unsigned long acc_no;
    int index = -1;        //by default account doesn't exist.
    
    printf("\n Enter the user accout number :- ");
    scanf("%lu",&acc_no);
    
    index = searchIndex(acc_no);
    
    if(index < 0){
        
        printf("\n Sorry, looks like account doesn't exist.");
        return;
        
    }
    
    
    printf("\n Enter the new password :- ");
    scanf("%s",p[index].password);
    
    printf("\n successfully changed the password");
    
    
}



/*
    STACK OVERFLOW CODE FOR IMPLEMENTING GETCH IN GCC COMPILER
    
    it has been simpley copy pasted here
    
*/


/* reads from keypress, doesn't echo */
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

/* reads from keypress, echoes */
int getche(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}


                    
        
