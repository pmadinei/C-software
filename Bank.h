//
//  Bank.h
//  CA3.c
//
//  Created by Parsa Madinei on 10/17/1398 AP.
//  Copyright © 1398 AP Parsa Madinei. All rights reserved.
//

#ifndef Bank_h
#define Bank_h
#include <stdio.h>

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

typedef struct transactions transaction;
typedef struct user_info userInfo;
void users_head_initiator (userInfo *head);
void admin_initiator(userInfo *admin);
void user_initiator (userInfo *user,double *ID);
void manualcpy(char *str,char *line,int len);
void struct_filler(userInfo *users,char *line,int len);
void file_reader(FILE *data,userInfo *user,int numof_users,int numof_lines);
void add_user_func(userInfo *users_head,double *ID,char *username,char *password,char *tel);
userInfo *login_func(userInfo *admin,userInfo *users_head,char *user,char *pass,int *user_type);
void logout_func(int *user_type,userInfo *our_user);
void deposit_func(userInfo *users_head,double amount,char *user);
void withdraw_func(userInfo *users_head,double amount,char *user);
void delete_func(userInfo *users_head,char *username);
void view_func_admin(userInfo *users_head,char *username);
void view_func_user(userInfo *our_user);
void transfer_func(userInfo *our_user,userInfo *users_head,char *destination,double amount);
int exit_func(FILE *data,userInfo *users_head);
void get_word(char *command,int *j,char *temp);
int command_func(FILE *data,userInfo *users_head,userInfo *admin,userInfo *our_user,int *user_type,double *ID);
#endif /* Bank_h */
