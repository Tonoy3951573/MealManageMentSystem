#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "def.h"
const char* get_meal_status(int meal_consumed[], int day) {
    if (meal_consumed[day - 1] == 0)
        return "OFF";
    else
        return "ON";
}

int book_meal(Students students[], int ind,int day){
    if(getTime() >= 16) return 0;
    int running = 1;
    char symb[2][10] = {" ","✓"};
    while(running){
        clear_s();
        printf("─────────────── Meal Booking Panel ───────────────\n");
        printf("1. Book Breakfast [\033[33m%s\033[0m]\n",symb[(students[ind].meals_consumed[day - 1] >> 0) & 1]);
        printf("2. Book Lunch     [\033[33m%s\033[0m]\n",symb[(students[ind].meals_consumed[day - 1] >> 1) & 1]);
        printf("3. Book Dinner    [\033[33m%s\033[0m]\n",symb[(students[ind].meals_consumed[day - 1] >> 2) & 1]);
        printf("4. Back \n");

        int choice;
        printf("Enter [1-4] : ");
        scanf("%d",&choice);
        int meal_stat = students[ind].meals_consumed[day - 1];
        if(choice == 1){
            if((students[ind].meals_consumed[day - 1]&1 ) == 0){
                if(students[ind].current_balance >= MEAL_RATE_M){
                    meal_stat = meal_stat | 1;
                    students[ind].meals_consumed[day - 1] = meal_stat;
                    students[ind].current_balance -= MEAL_RATE_M;
                }
                else{
                    printf("You don't have sufficient Balance\n");
                    sleep(1);
                }

            }
            else{
                printf("Breakfast is already booked.\n");
                sleep(1);
            }
        }
        else if(choice == 2){
            if(((students[ind].meals_consumed[day - 1]>>1)&1 ) == 0){
                if(students[ind].current_balance >= MEAL_RATE_M){
                    meal_stat = meal_stat | 1<<1;
                    students[ind].meals_consumed[day - 1] = meal_stat;
                    students[ind].current_balance -= MEAL_RATE_D;
                }
                else{
                    printf("You don't have sufficient Balance\n");
                    sleep(1);
                }

            }
            else{
                printf("Lunch is already booked.\n");
                sleep(1);
            }
        }
        else if(choice == 3){
            if(((students[ind].meals_consumed[day - 1]>>2)&1 ) == 0){
                if(students[ind].current_balance >= MEAL_RATE_M){
                    meal_stat = meal_stat | (1<<2);
                    students[ind].meals_consumed[day - 1] = meal_stat;
                    students[ind].current_balance -= MEAL_RATE_N;
                }
                else{
                    printf("You don't have sufficient Balance\n");
                    sleep(1);
                }

            }
            else{
                printf("Dinner is already booked.\n");
                sleep(1);
            }
        }
        else running = 0;
    }
    return 1;
}
int cancel_meal(Students students[], int ind,int day){
    if(getTime() >= 16) return 0;
    int running = 1;
    char symb[2][20] = {"\033[31m✕\033[0m","\033[33m✓\033[0m"};
    while(running){
        clear_s();
        printf("─────────────── Meal Canceling Panel ───────────────\n");
        printf("1. Cancel Breakfast [%s]\n",symb[(students[ind].meals_consumed[day - 1] >> 0) & 1]);
        printf("2. Cancel Lunch     [%s]\n",symb[(students[ind].meals_consumed[day - 1] >> 1) & 1]);
        printf("3. Cancel Dinner    [%s]\n",symb[(students[ind].meals_consumed[day - 1] >> 2) & 1]);
        printf("4. Back \n");

        int choice;
        printf("Enter [1-4] : ");
        scanf("%d",&choice);
        int meal_stat = students[ind].meals_consumed[day - 1];
        if(choice == 1){
            if((students[ind].meals_consumed[day - 1]&1 ) == 1){
                meal_stat = meal_stat & ~1;
                students[ind].meals_consumed[day - 1] = meal_stat;
                students[ind].current_balance += MEAL_RATE_M;

            }
            else{
                printf("Breakfast is already canceled.\n");
                sleep(1);
            }
        }
        else if(choice == 2){
            if(((students[ind].meals_consumed[day - 1]>>1)&1 ) == 1){
                meal_stat = meal_stat & ~(1<<1);
                students[ind].meals_consumed[day - 1] = meal_stat;
                students[ind].current_balance += MEAL_RATE_D;

            }
            else{
                printf("Lunch is already canceled.\n");
                sleep(1);
            }
        }
        else if(choice == 3){
            if(((students[ind].meals_consumed[day - 1]>>2)&1 ) == 1){
                meal_stat = meal_stat & ~(1<<2);
                students[ind].meals_consumed[day - 1] = meal_stat;
                students[ind].current_balance += MEAL_RATE_N;

            }
            else{
                printf("Dinner is already canceled.\n");
                sleep(1);
            }
        }
        else running = 0;
    }
    return 1;
}

int show_menu(){
    char Breakfast_items[MENU_LIMIT][MAX_LEN];
    char Lunch_items[MENU_LIMIT][MAX_LEN];
    char Dinner_items[MENU_LIMIT][MAX_LEN];
    int size = load_menu(Breakfast_items,"../resources/breakfast_menu.txt");
    printf("\n─────────── Menu ──────────\n");
    printf("Breakfast : \n");
    if(size == 0){
        printf("\tNo Item has been added yet!\n");
    }
    else{
        for(int i = 0; i < size; i++){
            printf("\t%d. %s\n",i+1,Breakfast_items[i]);
        }
    }
    size = load_menu(Lunch_items,"../resources/lunch_menu.txt");
    printf("Lunch : \n");
    if(size == 0){
        printf("\tNo Item has been added yet!\n");
    }
    else{
        for(int i = 0; i < size; i++){
            printf("\t%d. %s\n",i+1,Lunch_items[i]);
        }
    }
    size = load_menu(Dinner_items,"../resources/dinner_menu.txt");
    printf("Dinner : \n");
    if(size == 0){
        printf("\tNo Item has been added yet!\n");
    }
    else{
        for(int i = 0; i < size; i++){
            printf("\t%d. %s\n",i+1,Dinner_items[i]);
        }
    }
    return 1;
}

int delete_item(int ind,char* filename){
    char items[MENU_LIMIT][MAX_LEN];
    int size =  load_menu(items,filename);
    FILE* temp = fopen("../resources/temp.txt","w");
    if(temp == NULL) return 0;
    for(int i = 0; i < size; i++){
        if(i == ind - 1) continue;
        else{
            fprintf(temp,"%s",items[i]);
            fprintf(temp,"\n");
        }
    }
    fclose(temp);
    remove("../resources/menu.txt");
    rename("../resources/temp.txt",filename);
    return 1;
}

int checkDuplicateMenu(char Menu[][MAX_LEN],int size, char* item){
    for(int i = 0; i < size; i++){
        if(strcmp(Menu[i], item) == 0){
            return 1;
        }
    }
    return 0;
}

int edit_menu(){
    int running = 1;
    while(running){
        clear_s();
        printf("────────────────── Edit Menu ──────────────────\n");
        printf("1. Show Menu\t\t2. Add Item\n3. Delete Item\t\t4. Back\n");
        int choice;
        printf("Enter [1-4] : ");
        scanf("%d",&choice);
        getchar();

        if(choice == 1){
            show_menu();
            printf("\nPress any key to back.\n");
            getchar();
        }
        else if(choice == 2){
           int running = 1;
           while(running){
                char item[MAX_LEN];
                show_menu();
                printf("1. Add item to Breakfast Menu\n");
                printf("2. Add item to Lunch Menu\n");
                printf("3. Add item to Dinner Menu\n");
                printf("4. Back\n");

                int choice;
                printf("Enter [1-4] : ");
                scanf("%d",&choice);

                if(choice == 1){
                    printf("Item Name at Breakfast Menu : ");
                    scanf(" %[^\n]",item);
                    char Breakfast_items[MENU_LIMIT][MAX_LEN];
                    int size = load_menu(Breakfast_items,"../resources/breakfast_menu.txt");
                    if(!checkDuplicateMenu(Breakfast_items,size,item)&& save_item(item,"../resources/breakfast_menu.txt")){
                        printf("Item Added Succefully!\n");
                        sleep(1);
                    }
                    else{
                        printf("Something Went Wrong!\n");
                        sleep(1);
                    }
                }
                else if(choice == 2){
                    printf("Item Name at Lunch Menu : ");
                    scanf(" %[^\n]",item);
                    char Lunch_items[MENU_LIMIT][MAX_LEN];
                    int size = load_menu(Lunch_items,"../resources/lunch_menu.txt");
                    if(!checkDuplicateMenu(Lunch_items,size,item) && save_item(item,"../resources/lunch_menu.txt")){
                        printf("Item Added Succefully!\n");
                        sleep(1);
                    }
                    else{
                        printf("Something Went Wrong!\n");
                        sleep(1);
                    }
                }
                else if(choice == 3){
                    char Dinner_items[MENU_LIMIT][MAX_LEN];
                    int size = load_menu(Dinner_items,"../resources/dinner_menu.txt");
                    printf("Item Name at Dinner Menu : ");
                    scanf(" %[^\n]",item);
                    if(!checkDuplicateMenu(Dinner_items,size,item) && save_item(item,"../resources/dinner_menu.txt")){
                        printf("Item Added Succefully!\n");
                        sleep(1);
                    }
                    else{
                        printf("Something Went Wrong!\n");
                        sleep(1);
                    }
                }
                else{
                    running = 0;
                    break;
                }
           }
           

        }
        else if(choice == 3){

            
            show_menu();
            printf("1. Delete Items from Breakfast\n");
            printf("2. Delete Items from Lunch\n");
            printf("3. Delete Items from Dinner\n");
            printf("4. Back\n");
            int choice;
            printf("Enter [1-4] : ");
            scanf("%d",&choice);
            if(choice == 1){
                int ind;
                printf("\nWhich Item you want to delete from Breakfast [Serial number] : ");
                scanf("%d",&ind);
                delete_item(ind,"../resources/breakfast_menu.txt");
                printf("Item no %d has been removed.\n",ind);
                sleep(2);
            }
            else if(choice == 2){
                int ind;
                printf("\nWhich Item you want to delete from Lunch [Serial number] : ");
                scanf("%d",&ind);
                delete_item(ind,"../resources/lunch_menu.txt");
                printf("Item no %d has been removed.\n",ind);
                sleep(2);
            }
            else if(choice == 3){
                int ind;
                printf("\nWhich Item you want to delete from Dinner [Serial number] : ");
                scanf("%d",&ind);
                delete_item(ind,"../resources/dinner_menu.txt");
                printf("Item no %d has been removed.\n",ind);
                sleep(2);
            }
            
        }
        else if(choice == 4){
            running = 0;
        }
    }
    return 1;
}

void show_meal_log(int day){
    Students students[MAX_USERS];
    int size = load_students_info(students,"../resources/students_basic_info.txt");
    int bf = 0,lu = 0, di = 0;
    printf("──────────── Breakfast ──────────\n");
    printf("\nRoll No\t\t\tName\t\t\tRoom Number\tStatus\n");
    for(int i = 0; i < size; i++){
        if(((students[i].meals_consumed[day - 1])&1 ) == 1){
            printf("%-s\t\t%-22s\t%d\t\tON\n",students[i].roll_no,students[i].name,students[i].room_number);
            bf++;
        }
    }
    if(bf == 0) printf("No record\n");
    printf("\n\n────────────── Lunch ────────────\n");
    printf("\nRoll No\t\t\tName\t\t\tRoom Number\tStatus\n");
    for(int i = 0; i < size; i++){
        if(((students[i].meals_consumed[day - 1]>>1)&1 ) == 1){
            printf("%-s\t\t%-22s\t%d\t\tON\n",students[i].roll_no,students[i].name,students[i].room_number);
            lu++;
        }
    }
    if(lu == 0) printf("No record\n");
    printf("\n\n────────────── Dinner ────────────\n");
    printf("\nRoll No\t\t\tName\t\t\tRoom Number\tStatus\n");
    for(int i = 0; i < size; i++){
        if(((students[i].meals_consumed[day - 1]>>2)&1 ) == 1){
            printf("%-s\t\t%-22s\t%d\t\tON\n",students[i].roll_no,students[i].name,students[i].room_number);
            di++;
        }
    }
    if(di == 0) printf("No record\n");
    printf("\n────────────────────────────────────────────────────────────────────────\n");
    printf("Breakfast  : %d \tTotal : %d taka.\n",bf,bf*MEAL_RATE_M);
    printf("Lunch      : %d \tTotal : %d taka.\n",lu,lu*MEAL_RATE_D);
    printf("Dinner     : %d \tTotal : %d taka.\n",di,di*MEAL_RATE_N);
    printf("\n────────────────────────────────────────────────────────────────────────\n");
    printf("Total Meal : %d \tTotal : %d taka.\n",bf+lu+di,bf*MEAL_RATE_M + lu*MEAL_RATE_D + di*MEAL_RATE_N);
}