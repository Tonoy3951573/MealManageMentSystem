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
    printf("────────────────────── Transaction Log ──────────────────\n\n");
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

void genarate_monthly_bill(Students student){
    int bf = 0,lu = 0, di = 0;
    for(int i = 0; i < 31; i++){
        if((student.meals_consumed[i]&1) == 1) bf++;
        if(((student.meals_consumed[i]>>1) & 1) == 1) lu++;
        if(((student.meals_consumed[i]>>2) & 1) == 1) di++;
    }
    printf("\n────────────────────────────────────────────────────────────────────────\n");
    printf("Breakfast  : %d \tTotal : %d taka.\n",bf,bf*MEAL_RATE_M);
    printf("Lunch      : %d \tTotal : %d taka.\n",lu,lu*MEAL_RATE_D);
    printf("Dinner     : %d \tTotal : %d taka.\n",di,di*MEAL_RATE_N);
    printf("\n────────────────────────────────────────────────────────────────────────\n");
    printf("Total Meal : %d \tTotal : %d taka.\n",bf+lu+di,bf*MEAL_RATE_M + lu*MEAL_RATE_D + di*MEAL_RATE_N);
}

void print_credit_log_by_Id(char* roll_no){
    Credit_Log credit_Log[1000];
    int size = load_credit_log(credit_Log);
    printf("─────────────────────────── Transaction Log ───────────────────────────\n\n");
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

