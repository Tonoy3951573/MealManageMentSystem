#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "def.h"
const char* get_meal_status(int meal_consumed[], int day) {
    if (meal_consumed[day - 1] == 0)
        return "OFF";
    else
        return "ON";
}

int book_meal(Students students[], int ind,int day){
    if(students[ind].current_balance < BILL_PER_MEAL) return -1;
    if(getTime() >= 16) return 0;
    if(students[ind].meals_consumed[day - 1] == 0){
        students[ind].current_balance -= BILL_PER_MEAL;
    }
    students[ind].meals_consumed[day - 1] = 1;
    
    return 1;
}
int cancel_meal(Students students[], int ind,int day){
    if(getTime() >= 16) return 0;
    if(students[ind].meals_consumed[day - 1] == 1){
        students[ind].current_balance += BILL_PER_MEAL;
    }
    students[ind].meals_consumed[day - 1] = 0;
    return 1;
}

int show_menu(){
    char items[MENU_LIMIT][MAX_LEN];
    int size = load_menu(items);
    printf("\n----------- Menu -----------\n");
    if(size == 0){
        printf("No Item has been added yet!\n");
        sleep(1);
    }
    else{
        for(int i = 0; i < size; i++){
            printf("%d. %s\n",i+1,items[i]);
        }
    }
    return 1;
}

int delete_item(int ind){
    char items[MENU_LIMIT][MAX_LEN];
    int size =  load_menu(items);
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
    rename("../resources/temp.txt","../resources/menu.txt");
}

int edit_menu(){
    int running = 1;
    while(running){
        clear_s();
        printf("----------------- Edit Menu ----------------\n");
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
            char item[MAX_LEN];
            printf("Item Name : ");
            scanf(" %[^\n]",item);
            if(save_item(item)){
                printf("Item Added Succefully!\n");
                sleep(1);
            }
            else{
                printf("Something Went Wrong!\n");
                sleep(1);
            }

        }
        else if(choice == 3){
            show_menu();
            int ind;
            printf("\nWhich Item you want to delete [Serial number] : ");
            scanf("%d",&ind);
            delete_item(ind);
            printf("Item no %d has been removed.\n",ind);
            sleep(2);
        }
        else if(choice == 4){
            running = 0;
        }
    }
}

void show_meal_log(int day){
    Students students[MAX_USERS];
    int size = load_students_info(students,"../resources/students_basic_info.txt");
    int count = 0;
    printf("\nRoll No\t\t\tName\t\t\tRoom Number\tStatus\n");
    for(int i = 0; i < size; i++){
        if(students[i].meals_consumed[day-1] == 1){
            printf("%-s\t\t%-22s\t%d\t\tON\n",students[i].roll_no,students[i].name,students[i].room_number);
            count++;
        }
    }
    printf("------------------------------------------------------------\n");
    printf("Meal ON : %d Total : %d taka.\n",count,count*BILL_PER_MEAL);
}