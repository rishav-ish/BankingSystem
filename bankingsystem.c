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
void admin();
int admin_validation();


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
    
    while(1){                               //infinite loops start's here....
    
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
                    printf("\nUnable to create account");
                    
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
                printf("\nSomething goes wrong");
                printf("\nRechoose your options");
                break;
            
            
        }   //switch end's here...
        
        
        
    }                                  //infinite loops end here....
    
    return 0;
    
}


void decoration(){
    
    
    printf("\n ######   #######   ######   ##    ## #### ########     ###    ##    ## ##    ## \n");
    printf("##    ## ##     ## ##    ##  ###   ##  ##  ##     ##   ## ##   ###   ## ##   ##  \n");
    printf("##       ##     ## ##        ####  ##  ##  ##     ##  ##   ##  ####  ## ##  ##   \n");
    printf("##       ##     ## ##   #### ## ## ##  ##  ########  ##     ## ## ## ## #####    \n");
    printf("##       ##     ## ##    ##  ##  ####  ##  ##     ## ######### ##  #### ##  ##   \n");
    printf("##    ## ##     ## ##    ##  ##   ###  ##  ##     ## ##     ## ##   ### ##   ##  \n");
    printf(" ######   #######   ######   ##    ## #### ########  ##     ## ##    ## ##    ## \n\n");

    
    
    
}


void options(){
    
    printf("\nPlease choose the number from the below options\n");
    printf("\n1.Create Account");
    printf("\n2.Sign In");
    printf("\n3.Admin");
    printf("\n4.Exit");
    printf("\nYour choice ");
}


int createAccount(){
    
    
    
    if(count > MAX)
            return 0;
            
    
    
    printf("\n------------------------------------INFORMATION------------------------------------\n");
    printf("\n Welcome User, to cognibank.");
    printf("\n Here are some information that you need to remember.");
    printf("\n Remember your account number, for future transaction.");
    printf("\n Create four character password only.");
    printf("\n Never share your password with anyone.");
    printf("\n And don't forget your password either.");
    printf("\n Thank you, for giving us chance to serve you.");
    printf("\n\n-----------------------------------------------------------------------------------\n\n");
    
    printf("\nEnter your first name :- ");
    scanf("%s",p[count].firstName);
    
    printf("\nEnter your last name :- ");
    scanf("%s",p[count].lastName);
    
    printf("\nEnter the 4 character password :- ");
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
    
    printf("\nEnter your account number ");
    scanf("%lu",&user_acc_no);
    
    index = searchIndex(user_acc_no);
    
    if(index >= 0){
        
        if(validateUser(index)){
            welcome_user(index);
            
        }else{
            printf("\nWrong password, please re-try.");
        }
        
    }else
        printf("\nSorry, this account doesn't exist");
    
    
}

int searchIndex(unsigned long acc_no){
    
    for(int i = 0; i <  MAX; ++i)
        if(index_for_acc_no[i] == acc_no)
            return i;
    
    return -1;
    
}

int validateUser(int index){
    
    char dup_password[5];
    
    printf("\nEnter your password\n");
    scanf("%s",dup_password);
    
    if(strcmp(p[index].password, dup_password) == 0)
        return 1;
    else
        return 0;
    
}

float transaction(){
    float m;
    
    printf("\nEnter the amount of money ");
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
    
    printf("\n\n\nWelcome %s %s",p[index].firstName,p[index].lastName);
    printf("\nAccount Number :- %lu",p[index].accountNumber);
    printf("\n\nHere is what you can do");
    printf("\n1.Look at your balance");
    printf("\n2.Deposit Money");
    printf("\n3.Withdraw Money");
    printf("\n4.Transfer Money");
    printf("\n5.Log out");
    printf("\nEnter number of your choice ");
    
    scanf("%d",&choice);
    
    
    switch(choice){
        
        case 1:
            printf("\nYour current Balance is Rs %.2f",p[index].balance);
            break;
            
        case 2:
            flag = depositMoney(index,transaction());
            if(flag == 1)
                printf("\nSuccessfully deposited, Your update balance is Rs %.2f",p[index].balance);
            else
                printf("\nUnable to deposite money");
            break;
            
        case 3:
            flag = withdrawMoney(index,transaction());
            
            if(flag == 1){
                printf("\nSuccessfully withdrawn the given amount");
                printf(", Your current balance is Rs %.2f",p[index].balance);
            }else   
                printf("\nSorry, not able to withdraw the money");
                
            break;
            
        case 4:
           printf("\nPlease enter the account number of person you want to transfer ");
           scanf("%lu",&t_acc_no);
            
            
            index_for_other_user = searchIndex(t_acc_no);
            
           if(index_for_other_user >= 0){
               
               if(validateUser(index))
                        flag = transferMoney(index, index_for_other_user, transaction());
                else{
                    
                    printf("\nWrong password, you are logged out!");
                    
                    getch();
                    return;
                }
           }else{
               printf("\nSorry, no account exist with this account number");
           }
            
           //flag = transferMoney(index, index_for_other_user, transaction());
           
           if(flag == 1){
                printf("\nMoney transfer successfully");
                flag = 0;
                
           }else
                printf("\nMoney doesn't transfer, may be account number you enter is wrong");
                
           break;
            
        case 5:
            return;
            
        default:
            printf("\nSorry, you have been signed out");
            break;
    }
    
    
    getch();
    
    
    }
    
    return;
    
}


int admin_validation(){
    char admin_name[] = "rishav";                                     //change it as you need
    char admin_password[] = "helloworld";                             //change it as you need
    
    char temp_name[50], temp_password[50];
    
    printf("\nEnter your username :- ");
    scanf("%s",temp_name);
    
    printf("\nEnter your password :- ");
    scanf("%s",temp_password);
    
    if(strcmp(admin_name, temp_name) == 0 && strcmp(admin_password, temp_password) == 0)
        return 1;
    else
        return 0;
    
}



void admin(){
    
    
    if(admin_validation() == 0){
        printf("\nSorry, you are not authorized to view this page");
        return;
    }
    
    for(int i = 0; i<count; ++i){
        
        printf("\n-----------------------------User %d---------------------------------\n",i+1);
        printf("\n%s %s", p[i].firstName, p[i].lastName);
        printf("\nAccount Number :- %lu",p[i].accountNumber);
        printf("\nPassword :- %s",p[i].password);
        
    }
    
    getch();
    
    return;
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


                    
        
