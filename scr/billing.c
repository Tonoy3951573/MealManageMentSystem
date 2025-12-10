#include <stdio.h>
#include <string.h>
#include "def.h"

 int add_credit(char* roll_no, double credit){
    Students students[MAX_USERS];
    int size = load_students_info(students,"../resources/students_basic_info.txt");
    int ind = -1;
    for(int i = 0; i < size; i++){
        if(strcmp(students[i].roll_no,roll_no)==0){
            ind = i;
        }
    }
    if(ind == -1) return 0;
    students[ind].current_balance += credit;
    update_students_info(students,size);
    char date[MAX_LEN];
    getDate(date,sizeof(date));
    save_cradit_log(date,roll_no,credit);
    return 1;
}

void show_credit_log(){
    Credit_Log credit_Log[1000];
    int size = load_credit_log(credit_Log);
    printf("---------------------- Transaction Log ---------------------\n\n");
    if(size == 0){
        printf("No records\n");
    }

    else{
        printf("Roll No\t\t\tDate\t\t\tAmount\n");
        for(int i = 0; i < size; i++){
            printf("%s\t\t%s\t\t%lf\n",credit_Log[i].roll_no,credit_Log[i].date,credit_Log[i].ammount);
        }
    }
}

void genarate_monthly_bill(Students students){
    int count = 0;
    for(int i = 0; i < 31; i++){
        if(students.meals_consumed[i] == 1) count++;
    }
    printf("------------------------------------\n");
    printf("Meal consumed : %d\n Total Bill : %d\n",count,count*BILL_PER_MEAL);

}

void print_credit_log_by_Id(char* roll_no){
    Credit_Log credit_Log[1000];
    int size = load_credit_log(credit_Log);
    printf("---------------------- Transaction Log ---------------------\n\n");
    if(size == 0){
        printf("No records\n");
    }

    else{
        printf("Roll No\t\t\tDate\t\t\tAmount\n");
        for(int i = 0; i < size; i++){
            if(strcmp(credit_Log[i].roll_no,roll_no) == 0)
                printf("%s\t\t%s\t\t%lf\n",credit_Log[i].roll_no,credit_Log[i].date,credit_Log[i].ammount);
        }
    }
}

