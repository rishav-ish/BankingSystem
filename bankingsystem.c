/*
    BANKING SYSTEM 
    @author:- Rishav Kumar
    
    No input check has been done 
    
    and no data will be saved
     
*/




#include<stdio.h>
#include<stdlib.h>

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
    
    int accountNumber;
};


void decoration();
void options();
int createAccount();
int signIn();
float transaction();
void depositMoney(int,float);
int withdrawMoney(int,float);
int transferMoney(int, int, float);
void welcome_user(int index);


struct People p[MAX];
unsigned int count;



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
                index = signIn();
                
                if(index < 0){
                    printf("\nNo Account Found");
                }else
                    welcome_user(index);
                    
                break;
                
            case 3:
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
    printf("\n3.Exit");
    printf("\nYour choice ");
}


int createAccount(){
    
    
    
    if(count > MAX)
            return 0;
            
  
    
    printf("\nEnter your first name ");
    scanf("%s",p[count].firstName);
    
    printf("\nEnter your last name ");
    scanf("%s",p[count].lastName);
    
    p[count].balance = 0;
    
    
    p[count].accountNumber = count;
    
    count += 1;
    
    return 1;           //account get successfully created...
    
}

int signIn(){
    
    int user_acc_no;
    
    printf("\nEnter your account number ");
    scanf("%d",&user_acc_no);
    
    if(user_acc_no > count)
        return -1;
        
    return user_acc_no;
    
}

float transaction(){
    float m;
    
    printf("\nEnter the amount of money ");
    scanf("%f",&m);
    
    return m;
}

void depositMoney(int index, float money){
    
    
    p[index].balance += money;

    printf("\nMoney is successfully deposited to your account");    
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
    
    int t_acc_no;
    int choice;
    int flag = 0;                                          //flag value
    
    
    
    while(1){
    system("clear");
    printf("\nWelcome %s %s",p[index].firstName,p[index].lastName);
    printf("\nAccount Number :- %d",p[index].accountNumber);
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
            depositMoney(index,transaction());
            printf("\nYour update balance is Rs %.2f",p[index].balance);
            break;
            
        case 3:
            flag = withdrawMoney(index,transaction());
            
            if(flag == 1){
                printf("\nSuccessfully withdrawn the given amount");
                printf("\nYour current balance is Rs %.2f",p[index].balance);
            }else   
                printf("\nSorry, not able to withdraw the money");
                
            break;
            
        case 4:
           printf("\nPlease enter the account number of people you want to transfer ");
           scanf("%d",&t_acc_no);
            
            
           if(t_acc_no > count || t_acc_no < 0){
                printf("\nNot valid account number");
                break;
           }
            
           flag = transferMoney(index, t_acc_no, transaction());
           
           if(flag == 1){
                printf("\nMoney transfer successfully");
                
           }else
                printf("\nMoney doesn't transfer, may be account number you enter is wrong");
                
           break;
            
        case 5:
            return;
            
        default:
            printf("\nSorry, you have been signed out");
            break;
    }
    
    }
    
    return;
    
}


                    
        
