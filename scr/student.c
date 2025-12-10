#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "def.h"

int checkDuplicateRollNo(Students students[],int size, char* roll_no){
    for(int i = 0; i < size; i++){
        if(strcmp(students[i].roll_no, roll_no) == 0){
            return 1;
        }
    }
    return 0;
}

void register_student(){

    clear_s();
    Students student = {0};
    Login_pass passKey;
    printf("-------------Register a Student-------------\n");
    printf("Name : ");
    scanf(" %[^\n]",student.name);
    strtok(student.name,"\n");
    printf("Roll no : ");
    scanf("%s",student.roll_no);
    printf("Room Number : ");
    scanf("%d",&student.room_number);
    printf("Password : ");
    scanf("%s",passKey.password);
    strcpy(passKey.rollno, student.roll_no);

    // a function to check if the account aleady exist or not.
    Students students[MAX_USERS];
    int size = load_students_info(students,"../resources/students_basic_info.txt");
    if(checkDuplicateRollNo(students,size,student.roll_no)){
        printf("Already an account exist on this roll number!\n");
        
    }
    else{
        if(save_basic_info(student) && save_login_pass(passKey)){
            printf("Account Created Succesfully!\n");
            fflush(stdout);
            sleep(2);
            pre_login_page();
            
        }
        else{
            printf("Something Went Wrong!\n");
            register_student();
        }
    }
    

}


void printCalender(int arr[]){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 7; j++){
            int day = i*7 + j ;
            if(day > getDay() - 1) printf("  .  ");
            else{
                if(arr[day] == 0){
                    printf(" OFF ");
                }
                else printf(" ON  ");
            }
        }
        printf("\n");
    }
    for(int i = 0; i < 3; i++){
        int day = 28 + i;
        if(day > getDay()) printf("  .  ");
        else{
            if(arr[day] == 0){
                printf(" OFF ");
            }
            else printf(" ON  ");
        }
    }
    printf("\n");
}

int update_room_number(Students Students[], int ind){
    int new_room_number;
    printf("Enter Your New Room Number : ");
    scanf("%d",&new_room_number);
    Students[ind].room_number = new_room_number;
    return 1;
}

void view_profile(char* roll_no){

    Students students[MAX_USERS];
    int ind = -1;
    int size = load_students_info(students,"../resources/students_basic_info.txt");
    for(int i = 0; i < size; i++){
        if(strcmp(students[i].roll_no,roll_no) == 0){
            ind  = i;
            break;
        }
    }

    if (ind == -1) {
        printf("No student found with roll %s\n", roll_no);
        return;
    }

    int running = 1;
    while (running) {
        clear_s();
        printf("-----------Student Profile------------\n\n");
        printf("name : %s\n",students[ind].name);
        printf("Roll no : %s\n",students[ind].roll_no);
        printf("Room No : %d\n",students[ind].room_number);
        printf("Balance : %.2lf taka\n",students[ind].current_balance);
        printf("Meal Status : %s\n",get_meal_status(students[ind].meals_consumed,getDay()));

        char date[50];
        getDate(date,sizeof(date));
        printf("Date : %s\n",date);

        printf("\n----------Meal Calender----------\n");
        printCalender(students[ind].meals_consumed);

        printf("----------------------------------------\n\n");
        printf("1. Show Menu\t\t2. Book meal\n");
        printf("3. Cancel Meal\t\t4. Update Room Number\n");
        printf("5. Monthly Bill\t\t6. Transaction Log\n");
        printf("7. Reset Password\t8. LogOut\n");

        int choice = 0;
        printf("Select [1-8] : ");
        scanf("%d",&choice);
        getchar();

        if(choice == 1){
            show_menu();
            printf("\nPress any key to back.\n");
            getchar();
        }
        else if(choice == 2){
            int stat = book_meal(students,ind,getDay());
            if( stat == 1){
                update_students_info(students,size);
            }
            else if(stat == -1){
                printf("You Don't Have Sufficient Credit.\n");
                sleep(2);
            }
            else {
                printf("Can not Book or Cancel Meal after 4 PM.\n");
                sleep(2);
            }
        }
        else if(choice == 3){
            if(cancel_meal(students,ind,getDay())){
                update_students_info(students,size);
            }
            else {
                printf("Can not Book or Cancel Meal after 4 PM.\n");
                sleep(2);
            }
        }
        else if(choice == 4){
            update_room_number(students,ind);
            update_students_info(students,size);
            printf("Room Number Updated succesfully.\n");
            sleep(2);

        }
        else if(choice == 5){
            genarate_monthly_bill(students[ind]);
            printf("Press any key to back\n");
            getchar();
        }
        else if(choice == 6){
            print_credit_log_by_Id(students[ind].roll_no);
            printf("Press any key to back\n");
            getchar();
           
        }
        else if(choice == 7){
            
            printf("Enter Your New Password : ");
            char password[MAX_LEN];
            scanf(" %[^\n]",password);
            if(reset_Pass(students[ind].roll_no,password,"../resources/students_pass.txt")){
                printf("Password Has been updated Successfully!\n");
                sleep(2);
            }
            else{
                printf("something went Wrong!\n");
                sleep(2);
           }

        }
        else if(choice == 8){
            pre_login_page();
            running = 0;
        }
    }
}
