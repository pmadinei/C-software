//
//  main.c
//  CA3.c
//
//  Created by Parsa Madinei on 10/17/1398 AP.
//  Copyright © 1398 AP Parsa Madinei. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Bank.h"

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

int main() {
    /*variable defines*/
    double *IDs;
    char c=' ';
    int *user_type,numof_lines=0,numof_users=0,flag=0,three=3,thousand=1000;
    IDs = &thousand;
    user_type = &three;
    /*1 for admin   2 for normal    3 for not logged in*/
    FILE *data;
    /*lets start with allocating structures*/
    userInfo *user_head,*admin,*our_user;
    admin = (userInfo*) malloc(sizeof(userInfo));
    admin_initiator(admin);
    user_head = (userInfo*) malloc(sizeof(userInfo));
    users_head_initiator(user_head);
    our_user = (userInfo*) malloc(sizeof(userInfo));
    our_user=user_head;
    /*to load our data to our variables*/
    data=fopen("data.txt","w+");
    /*check if resource file neither could not be opened or created*/
    if (data==NULL){
            printf("resource file could not be opened!\n");
            return 0;
    }
    /*finding out that how many users we have*/
    for (c=getc(data); c!=EOF; c=getc(data)){
        if (c=='\n')
            numof_lines++;
        if (c=='*')
            numof_users++;
    }
    /*lets have our file*/
    file_reader(data, user_head, numof_users, numof_lines);
    while (flag==0){
        flag = command_func(data, user_head, admin,our_user, user_type, IDs);
    }
    /*lets find out how our program just ended!*/
    switch (flag) {
        case 1:
            printf("program has ended with the problem of closing file\n");
            break;
        case 2:
            printf("program has ended with no problem\n");
        default:
            break;
    }
    return 0;
}
