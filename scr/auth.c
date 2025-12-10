#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "def.h"

int detectAdmin(char* roll_no){
    
    if(strcmp("admin",roll_no) == 0) return 1;
    return 0;
}

int reset_Pass(char* roll_no, char* pass,char* filename){
    Login_pass paswords[MAX_USERS];
    int size = load_login_pass(paswords,filename);
    int ind = -1;
    for(int i = 0; i < size; i++){
        if(strcmp(paswords[i].rollno,roll_no) == 0){
            ind =  i;
            break;
        }
    }
    if(ind == -1) return 0;
    strcpy(paswords[ind].password,pass);
    if(update_passwords(paswords,size,filename)) return 1;
    return 0;
}

void admin_panel(){
    int running = 1;
    while(running){
        clear_s();
        printf("----------------------- Admin Panel ----------------------\n");
        printf("1. Edit Menu\t\t\t\t2. Show Meal Log.\n");
        printf("3. Add Creadit to a account\t\t4. Transaction Log\n");
        printf("5. Reset Password\t\t\t6. Veiw all Students\n");
        printf("7. Search by roll number\t\t8. LogOut\n");

        int choice;
        printf("Enter Your Choice [1-8] : ");
        if (scanf("%d", &choice) != 1) {
            return;
        }
        getchar();
        if (choice == 1) {
            edit_menu();
        } else if (choice == 2) {
            show_meal_log(getDay());
            printf("Press any key to back.\n");
            getchar();
        }
        else if (choice == 3) {
            char roll_no[MAX_LEN];
            double credit;
            printf("Enter Roll No : ");
            scanf(" %[^\n]",roll_no);
            printf("Enter Ammount : ");
            scanf("%lf",&credit);
            if(add_credit(roll_no,credit) == 1){
                printf("At %s , %lf taka has been added.\n",roll_no,credit);
                sleep(4);
            }
            else{
                printf("Something Went Wrong!\n");
                sleep(2);
            }
        }
        else if (choice == 4) {
            show_credit_log();
            printf("\nPress any key to back.\n");
            getchar();
        }
        else if(choice == 5){
            
            printf("Enter Your New Password : ");
            char password[MAX_LEN];
            scanf(" %[^\n]",password);
            if(reset_Pass("admin",password,"../resources/admin_pass.txt")){
                printf("Password Has been updated Successfully!\n");
                sleep(2);
            }
            else{
                printf("something went Wrong!\n");
                sleep(2);
           }
        }
        else if(choice == 6){
            all_student_list();
            printf("Press Any key to back.\n");
            getchar();
        }
        else if(choice == 7){
            char roll_no[MAX_LEN];
            printf("Enter Roll No : ");
            scanf("%s",roll_no);
            getchar();
            search_by_rollno(roll_no);
            printf("Press Any key to back.\n");
            getchar();
        }
        else if(choice == 8){
            pre_login_page();
            running = 0;
        }
        else {
            printf("Please Select 1, 2, 3, 4, 5, 6, 7 or 8.\n");
            sleep(1);
        }
    }
    

}

int auth(char roll_no[], char password[], const char filename[]) {

    Login_pass passKeys[MAX_USERS];
    int Current_size;
    int returnValue;

    if(detectAdmin(roll_no)){
        Current_size = load_login_pass(passKeys,"../resources/admin_pass.txt");
        returnValue = -1;
    }
    else{
        Current_size = load_login_pass(passKeys, filename);
        returnValue = 1;
    }
    

    if (Current_size < 0 || Current_size > MAX_USERS) {
        return 0;   
    }

    int ind = -1;
    for (int i = 0; i < Current_size; i++) {
        if (strcmp(passKeys[i].rollno, roll_no) == 0) {
            ind = i;
            break;
        }
    }

    if (ind == -1) {
        return 0;
    }

    if (strcmp(passKeys[ind].password, password) == 0) {
        return returnValue;   
    }

    return 0;
}

void login_page(void) {
    clear_s();
    printf("------------Login Page------------\n");
    char roll_no[MAX_LEN];
    char password[MAX_LEN];

    printf("Roll no : ");
    scanf("%29s", roll_no);

    printf("Password : ");
    scanf("%29s", password);   
    int stat = auth(roll_no, password, "../resources/students_pass.txt");   

    if (stat == 1) {
        clear_s();
        printf("Login successful!\n");
        sleep(2);
        view_profile(roll_no);

    } 
    else if(stat == -1){
        clear_s();
        printf("Admin Login successful!\n");
        sleep(2);
        admin_panel();
    }
    else {
        printf("Incorrect Roll no or Password. If you are new Create new Account.\n");
        sleep(2);
        pre_login_page();
    }
}

void pre_login_page(void) {

    clear_s();

    printf("+-------------------+\n");
    printf("|                   |\n");
    printf("| 1. login          |\n");
    printf("| 2. Create Account |\n");
    printf("| 3. Exit           |\n");
    printf("|                   |\n");
    printf("+-------------------+\n");

    int choice;
    printf("Enter Your Choice [1,2,3] : ");
    if (scanf("%d", &choice) != 1) {
        return;
    }

    while (choice != 3) {
        if (choice == 1) {
            login_page();
            break;
        } else if (choice == 2) {
            register_student();
            break;
        } else {
            printf("Please Select 1, 2, or 3.\n");
        }

        printf("Enter Your Choice [1,2,3] : ");
        if (scanf("%d", &choice) != 1) {
            break;
        }
    }
}
