//
//  Bank.c
//  CA3.c
//
//  Created by Parsa Madinei on 10/17/1398 AP.
//  Copyright © 1398 AP Parsa Madinei. All rights reserved.
//

#include "Bank.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*defining commands*/
#define add_user "add_user"
#define login "login"
#define deposit "deposit"
#define withdraw "withdraw"
#define view "view"
#define delete "delete"
#define transfer "transfer"
#define EXIT "exit"
#define logout "logout"

/*defining structs*/
typedef struct transactions{
    int type;
    long int amount;
    struct transactions* next;
}transaction;

typedef struct user_info{
    char name[30];
    char username[30];
    char tel[30];
    double id;
    char password[20];
    double inventory;
    double num_of_transactions;
    transaction list_of_transactions;
    struct user_info* next;
}userInfo;

void users_head_initiator (userInfo *head){
    head->id=0;
    head->inventory=0;
    head->list_of_transactions.type=0;
    head->list_of_transactions.amount=0;
    head->list_of_transactions.next=NULL;
    strcpy(head->name," ");
    head->next=NULL;
    head->num_of_transactions=0;
    strcpy(head->password," ");
    strcpy(head->tel," ");
}

void admin_initiator(userInfo *admin){
    strcpy(admin->name,"admin");
    strcpy(admin->username,"admin");
    strcpy(admin->tel,"0000000000");
    admin->id = 00000;
    strcpy(admin->password,"123");
}

void user_initiator (userInfo *user,double *ID){
    user->inventory=0;
    user->num_of_transactions=0;
    user->id=*ID++;
    user->list_of_transactions.type=0;
    user->list_of_transactions.amount=0;
    user->list_of_transactions.next=NULL;
}

/*three functions below will help us to read data from our file*/
void manualcpy(char *str,char *line,int len){
    int j=0;
    if (line[len-1]=='*'){
        for (int i=3;i<len-1;i++){
            str[j]=line[i];
            j++;
        }
    }
    else {
        for (int i=3;i<len;i++){
            str[j]=line[i];
            j++;
        }
    }
}

void struct_filler(userInfo *users,char *line,int len){
    char temp[20];
    /*our file had been saved in the format which first letter illustrates the line data type*/
    switch (line[0]) {
        case 'u':
            manualcpy(users->username,line,len);
            break;
        case 'p':
            manualcpy(users->password,line,len);
            break;
        case 't':
            manualcpy(users->tel,line,len);
            break;
        case 'i':
            manualcpy(temp,line,len);
            sscanf(temp, "%lf", &users->id);
            break;
        case 'v':
            manualcpy(temp,line,len);
            sscanf(temp, "%lf", &users->inventory);
            break;
        case 'n':
            manualcpy(temp,line,len);
            sscanf(temp, "%lf", &users->num_of_transactions);
            break;
        case 'r':
            manualcpy(temp,line,len);
            sscanf(temp, "%d", &users->list_of_transactions.type);
            break;
        case 'a':
            manualcpy(temp,line,len);
            sscanf(temp, "%lu", &users->list_of_transactions.amount);
            break;
        default:
            printf("invalid line type!\n");
            break;
    }
}

void file_reader(FILE *data,userInfo *user,int numof_users,int numof_lines){
    char line[255],c = '\0';
    int curr_char=0;
    while (c != EOF){
        fseek(data,curr_char,SEEK_SET);
        fgets(line, 255, data);
        /*process each line*/
        for (int k=0;k<255;k++){
            if (line[k]=='*'){
                struct_filler(user,line,k+1);
                curr_char += k+2;
                user = user->next;
                break;
            }
            if (line[k]=='\n'){
                struct_filler(user,line,k);
                curr_char += k+1;
                break;
            }
        }
        c = fgetc(data);
    }
}

void add_user_func(userInfo *users_head,double *ID,char *username,char *password,char *tel){
    userInfo *last_node,*to_add=(userInfo*) malloc(sizeof(userInfo));
    last_node = users_head;
    /*moving along with our nodes*/
    while (last_node->next!=NULL){
        /*checking for taken usernames*/
        if (strcmp(last_node->username,username)==0){
            printf("this username has taken befor!\n");
            return;
        }
        last_node=last_node->next;
    }
    /*now we have the last node*/
    last_node->next=to_add;
    to_add->next=NULL;
    /*lets import data*/
    strcpy(to_add->username,username);
    strcpy(to_add->password,password);
    strcpy(to_add->tel,tel);
    user_initiator(to_add,ID);
}

userInfo *login_func(userInfo *admin,userInfo *users_head,char *user,char *pass,int *user_type){
    if((strcmp(user, admin->username)==0) && (strcmp(pass, admin->password)==0)){
        printf("Access Granted!\nwelcome %s\n",admin->username);
        *user_type=1;
        return admin;
    }
    userInfo *next_node=users_head->next;
    while (next_node!=NULL){
        if((strcmp(user, next_node->username)==0) && (strcmp(pass, next_node->password)==0)){
            *user_type=2;
            return next_node;
        }
        next_node = next_node->next;
    }
    printf("Wrong username or password!\n");
    *user_type=3;
    return NULL;
}

void logout_func(int *user_type,userInfo *our_user){
    *user_type=3;
    our_user=NULL;
    printf("Logged out!\n");
}

void deposit_func(userInfo *users_head,double amount,char *user){
    userInfo *next_node=users_head->next;
    while (next_node!=NULL){
        if(strcmp(user, next_node->username)==0){
            next_node->inventory+=amount;
            next_node->num_of_transactions++;
            /*lets have a new transaction node!*/
            transaction *new_transaction;
            new_transaction = (transaction*) malloc(sizeof(transaction));
            next_node->list_of_transactions.next=new_transaction;
            new_transaction->next=NULL;
            new_transaction->amount=amount;
            new_transaction->type=1;
            /*1 for recieved money from admin
            2 for take-away money from admin
            3 for give money to someone else
            4 for take money from someone else*/
            printf("%f$ has been added to %s\n",amount,user);
            return;
        }
        next_node = next_node->next;
    }
    printf("we don't have such a user!\n");
}

void withdraw_func(userInfo *users_head,double amount,char *user){
    userInfo *next_node=users_head->next;
    while (next_node!=NULL){
        if(strcmp(user, next_node->username)==0){
            /*checking if he has enough money or not*/
            if(next_node->inventory < amount){
                printf("%s does't have that amount of money! his inventory: %f$\n",next_node->username,next_node->inventory);
                return;
            }
            next_node->inventory-=amount;
            next_node->num_of_transactions++;
            /*lets have a new transaction node!*/
            transaction *new_transaction;
            new_transaction = (transaction*) malloc(sizeof(transaction));
            next_node->list_of_transactions.next=new_transaction;
            new_transaction->next=NULL;
            new_transaction->amount=-amount;
            new_transaction->type=2;
            /*1 for recieved money from admin
            2 for take-away money from admin
            3 for give money to someone else
            4 for take money from someone else*/
            printf("%f$ has been removed from %s\n",amount,user);
            return;
        }
        next_node = next_node->next;
    }
    printf("we don't have such a user!\n");
}

void delete_func(userInfo *users_head,char *username){
    userInfo *curr=users_head,*next_node=users_head->next;
    while (next_node!=NULL){
        if(strcmp(username, next_node->username)==0){
            curr->next = next_node->next;
            printf("%s has been eliminated!\n",next_node->username);
            free(next_node);
            return;
        }
        curr = next_node;
        next_node = next_node->next;
    }
    printf("we don't have such a user!\n");
}

void view_func_admin(userInfo *users_head,char *username){
    userInfo *next_node=users_head->next;
    transaction *next_transaction=next_node->list_of_transactions.next;
    int transactions_counter=1;
    while (next_node->next!=NULL){
        if(strcmp(username, next_node->username)==0){
            printf("Username: %s\n",next_node->username);
            printf("Password: %s\n",next_node->password);
            printf("ID: %f\n",next_node->id);
            printf("Inventory: %f\n",next_node->inventory);
            printf("num_of_transactions: %f\n",next_node->num_of_transactions);
            printf("Telephone: %s\n",next_node->tel);
            /*printing transactions*/
            printf("transactions:\n");
            while (next_transaction!=NULL){
                printf("%d- type: %d/tamount: %ld",transactions_counter,next_transaction->type,next_transaction->amount);
                transactions_counter++;
                next_transaction = next_transaction->next;
            }
            return;
        }
        next_node = next_node->next;
    }
    printf("we don't have such a user!\n");
}

void view_func_user(userInfo *our_user){
    transaction *next_transaction=our_user->list_of_transactions.next;
    int transactions_counter=1;
    printf("Username: %s\n",our_user->username);
    printf("Password: %s\n",our_user->password);
    printf("ID: %f\n",our_user->id);
    printf("Inventory: %f\n",our_user->inventory);
    printf("num_of_transactions: %f\n",our_user->num_of_transactions);
    printf("Telephone: %s\n",our_user->tel);
    /*printing transactions*/
    printf("transactions:\n");
    while (next_transaction!=NULL){
        printf("%d- type: %d/tamount: %ld",transactions_counter,next_transaction->type,next_transaction->amount);
        transactions_counter++;
        next_transaction = next_transaction->next;
    }
}

void transfer_func(userInfo *our_user,userInfo *users_head,char *destination,double amount){
    /*first of all, lets check if he has such amount of money or not :D */
    if (our_user->inventory<amount){
        printf("Not enough money! your inventory: %f",our_user->inventory);
        return;
    }
    /*check if amount is bigger than 0*/
    if (amount<=0){
        printf("you pressed invalid amount of money!\n");
        return;
    }
    userInfo *next_node=users_head->next;
    while (next_node!=NULL){
        if(strcmp(destination, next_node->username)==0){
            next_node->inventory+=amount;
            our_user->inventory-=amount;
            next_node->num_of_transactions++;
            our_user->num_of_transactions++;
            /*lets have two new transaction nodes!*/
            transaction *new_transaction_A,*new_transaction_B;
            new_transaction_A = (transaction*) malloc(sizeof(transaction));
            new_transaction_B = (transaction*) malloc(sizeof(transaction));
            next_node->list_of_transactions.next=new_transaction_B;
            our_user->list_of_transactions.next=new_transaction_A;
            new_transaction_A->next=NULL;
            new_transaction_B->next=NULL;
            new_transaction_A->amount=-amount;
            new_transaction_B->amount=amount;
            new_transaction_A->type=3;
            new_transaction_B->type=4;
            /*1 for recieved money from admin
            2 for take-away money from admin
            3 for give money to someone else
            4 for take money from someone else*/
            printf("%f$ has been added to %s\n",amount,destination);
            printf("your inventory after this transaction: %f\n",our_user->inventory);
            return;
        }
        next_node = next_node->next;
    }
    printf("we don't have such a user!\n");
    return;
}

int exit_func(FILE *data,userInfo *users_head){
    userInfo *next_node=users_head->next,*temp;
    free(users_head);
    transaction *next_transaction=&next_node->list_of_transactions.next;
    while(next_node!=NULL){
        fprintf(data, "u: %s\n",next_node->username);
        fprintf(data, "p: %s\n",next_node->password);
        fprintf(data, "t: %s\n",next_node->tel);
        fprintf(data, "i: %f\n",next_node->id);
        fprintf(data, "v: %f\n",next_node->inventory);
        fprintf(data, "n: %f\n",next_node->num_of_transactions);
        while (next_transaction!=NULL){
            fprintf(data, "r: %d\n",next_node->list_of_transactions.type);
            fprintf(data, "a: %ld",next_node->list_of_transactions.amount);
            next_transaction = next_transaction->next;
            if (next_transaction==NULL){
                fprintf(data,"*\n");
                break;
            }
        }
        temp=next_node;
        next_node = next_node->next;
        free(temp);
    }
    int flag=fclose(data);
    if (flag!=0){
        printf("can not close the file\n");
        return 1;
    }
    printf("See you soon!\n");
    return 2;
}

void get_word(char *command,int *j,char *temp){
    int i=0,flag=0;
    while (command[*j]!=' ' && command[*j]!='\n'){
        temp[i]=command[*j];
        *j += 1 ;
        i++;
        flag=1;
    }
    if (flag==0){
        /*you did not enter required info, so we put NULL instead of that!*/
        strcpy(temp,"logout");
        *j += 1 ;
        temp[0] = '\0';
        return;
    }
    temp[i] = '\0';
    return;
}

int command_func(FILE *data,userInfo *users_head,userInfo *admin,userInfo *our_user,int *user_type,double *ID){
    char command[100],temp[35],one_letter;
    int j=0,i=0;
    printf("write your command!\n");
    while((one_letter=getchar()) != '\n'){
        command[i]=one_letter;
        i++;
    }
    command[i]='\0';
    /*now we have our command!*/
    get_word(command, &j, temp);
    j++;
    /*now we have the word in temp!*/
    /*invalid inputs*/
    if((strcmp(temp,add_user)!=0) && (strcmp(temp,login)!=0) && (strcmp(temp,deposit)!=0) && (strcmp(temp,withdraw)!=0) && (strcmp(temp,view)!=0) && (strcmp(temp,delete)!=0) && (strcmp(temp,transfer)!=0) && (strcmp(temp,EXIT)!=0) && (strcmp(temp,logout)!=0)){
        printf("invalid command! try again.\n");
        return 0;
    }
    else if ((*user_type == 3) && (strcmp(temp, add_user) == 0 || strcmp(temp, deposit) == 0 || strcmp(temp, withdraw) == 0 || strcmp(temp, view) == 0 || strcmp(temp, delete) == 0 || strcmp(temp, transfer) == 0)) {
        printf("Guest, you are now allowed! try again.\n");
        return 0;
    }
    else if ((*user_type == 2) && (strcmp(temp, add_user) == 0 || strcmp(temp, deposit) == 0 || strcmp(temp, withdraw) == 0 || strcmp(temp, login) == 0 || strcmp(temp, delete) == 0)) {
        printf("User, you are now allowed! try again.\n");
        return 0;
    }
    else if ((*user_type == 1) && (strcmp(temp, transfer) == 0 || strcmp(temp, login) == 0)) {
        printf("Admin, invalid request! try again.\n");
        return 0;
    }
    /*exit*/
    if(strcmp(temp,EXIT)==0){
        return exit_func(data, users_head);
    }
    /*add user*/
    if(strcmp(temp, add_user)==0){
        char username[20],password[20],tel[15];
        /*lets have next word!*/
        get_word(command, &j, temp);
        strcpy(username,temp);
        j++;
        get_word(command, &j, temp);
        strcpy(password,temp);
        j++;
        get_word(command, &j, temp);
        strcpy(tel,temp);
        add_user_func(users_head, ID, username, password, tel);
        return 0;
    }
    /*login*/
    if (strcmp(temp,login)==0){
        char username[20],password[20];
        /*lets have next word!*/
        get_word(command, &j, temp);
        strcpy(username,temp);
        j++;
        get_word(command, &j, temp);
        strcpy(password,temp);
        j++;
        our_user = login_func(admin, users_head, username, password, user_type);
        return 0;
    }
    /*logout*/
    if (strcmp(temp,logout)==0){
        logout_func(user_type,our_user);
        return 0;
    }
    /*deposit*/
    if (strcmp(temp,deposit)==0){
        double amount;
        char username[20];
        /*lets have next word!*/
        get_word(command, &j, temp);
        strcpy(username,temp);
        j++;
        get_word(command, &j, temp);
        sscanf(temp,"%lf",&amount);
        j++;
        deposit_func(users_head, amount, username);
        return 0;
    }
    /*withdraw*/
    if (strcmp(temp,withdraw)==0){
        double amount;
        char username[20];
        /*lets have next word!*/
        get_word(command, &j, temp);
        strcpy(username,temp);
        j++;
        get_word(command, &j, temp);
        sscanf(temp,"%lf",&amount);
        j++;
        withdraw_func(users_head, amount, username);
        return 0;
    }
    /*view*/
    if (strcmp(temp,view)==0){
        char username[20];
        switch (*user_type) {
            case 1:
                /*lets have next word!*/
                get_word(command, &j, temp);
                j++;
                if (temp[0]=='\0'){
                    printf("you should enter an username!\n");
                    return 0;
                }
                strcpy(username,temp);
                view_func_admin(users_head, username);
                break;
            case 2:
                view_func_user(our_user);
                break;
            default:
                break;
        }
        return 0;
    }
    /*delete*/
    if (strcmp(temp,delete)==0){
        char username[20];
        /*lets have next word!*/
        get_word(command, &j, temp);
        strcpy(username,temp);
        j++;
        delete_func(users_head, username);
        return 0;
    }
    /*transfer*/
    if (strcmp(temp,transfer)==0){
        double amount;
        char username[20];
        /*lets have next word!*/
        get_word(command, &j, temp);
        strcpy(username,temp);
        j++;
        get_word(command, &j, temp);
        sscanf(temp,"%lf",&amount);
        j++;
        transfer_func(our_user, users_head, username, amount);
        return 0;
    }
    return 0;
}
