#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "def.h"        

int load_login_pass(Login_pass passKeys[], const char *filename) {
    int count = 0;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("E: No account exist in the system or the file is broken!\n");
        return 0; 
    }

    while (count < MAX_USERS &&
           fscanf(fp, " %29[^,],%29[^\n]",
                  passKeys[count].rollno,
                  passKeys[count].password) == 2) {
        count++;
    }

    fclose(fp);
    return count;
}

int save_basic_info(Students student){

    FILE *fp_info = fopen("../resources/students_basic_info.txt","a");
    if(fp_info == NULL) return 0;
    fprintf(fp_info,"%s,%s,%d,0.0,",student.roll_no,student.name,student.room_number);
    for(int i = 0; i < 31; i++){
        if(i == 30){
            fprintf(fp_info,"%d",student.meals_consumed[i]);
            
        }
        else
            fprintf(fp_info,"%d,",student.meals_consumed[i]);
    }
    fprintf(fp_info,"\n");
    fclose(fp_info);
    return 1;
}

int save_login_pass(Login_pass passKey){

    FILE *fp_pass = fopen("../resources/students_pass.txt","a");
    if(fp_pass == NULL) return 0;
    fprintf(fp_pass,"%s,%s",passKey.rollno,passKey.password);
    fprintf(fp_pass,"\n");
    fclose(fp_pass);
    return 1;
}

int load_students_info(Students students[], const char *filename){
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Could not open file!\n");
        return -1;
    }

    char line[512];
    int count = 0;

    while (fgets(line, sizeof(line), fp) && count < MAX_USERS) {

        char *token = strtok(line, ",");
        if (!token) break;
        trim_leading_spaces(token);
        strcpy(students[count].roll_no, token);

        token = strtok(NULL, ",");
        if (!token) break;
        trim_leading_spaces(token);
        strcpy(students[count].name, token);
       

        token = strtok(NULL, ",");
        if (!token) break;
        students[count].room_number = atoi(token);

        token = strtok(NULL, ",");
        if (!token) break;
        students[count].current_balance = atof(token);
       
        token = strtok(NULL, ",");
        for (int i = 0; i < 31 && token; i++) {
            students[count].meals_consumed[i] = atoi(token);
            token = strtok(NULL, ",");
        }
        count++;  
    }

    fclose(fp);
    return count;
}

int update_students_info(Students students[], int size){
    FILE *fp_info = fopen("../resources/students_basic_info.txt","w");
    if(fp_info == NULL) return 0;
    for(int i = 0; i < size; i++){
        fprintf(fp_info,"%s,%s,%d,%lf,",students[i].roll_no,students[i].name,students[i].room_number,students[i].current_balance);
   
        for(int j = 0; j < 31; j++){
            if(j == 30){
                fprintf(fp_info,"%d",students[i].meals_consumed[j]);
            
            }
            else
                fprintf(fp_info,"%d,",students[i].meals_consumed[j]);
        }
        fprintf(fp_info,"\n");
    }
    fclose(fp_info);
    return 1;

}

int update_passwords(Login_pass paswords[], int size, char* filename){
    FILE* pass = fopen(filename,"w");
    if(pass == NULL) return 0;
    for(int i = 0; i < size; i++){
        fprintf(pass,"%s,%s",paswords[i].rollno,paswords[i].password);
        fprintf(pass,"\n");
    }
    fclose(pass);
    return 1;
}

int save_item(char* item){
    FILE* menu = fopen("../resources/menu.txt","a");
    if(menu == NULL) return 0;
    fprintf(menu,"%s",item);
    fprintf(menu,"\n");
    fclose(menu);
    return 1;
}

int load_menu(char items[][MAX_LEN]){
    FILE* menu = fopen("../resources/menu.txt","r");
    if(menu == NULL) return 0;
    int count = 0;
    while(count < MENU_LIMIT && fgets(items[count],sizeof(items[count]),menu)){
        strcpy(items[count],strtok(items[count],"\n"));
        count++;
    }
    fclose(menu);
    return count;
}

int save_cradit_log(char* date, char* roll_no, double ammount){
    FILE *credit_log = fopen("../resources/credit_log.txt","a");
    if(credit_log == NULL) return 0;
    fprintf(credit_log,"%s,%s,%lf",roll_no,date,ammount);
    fprintf(credit_log,"\n");
    fclose(credit_log);
    return 1;
}

int load_credit_log(Credit_Log credit_log[]){
    FILE *fp = fopen("../resources/credit_log.txt","r");
    if(fp == NULL) return 0;
    int count = 0;
    while(count < MAX_USERS && fscanf(fp," %29[^,],%29[^,],%lf",credit_log[count].roll_no,credit_log[count].date,&credit_log[count].ammount)==3){
        count++;
    }
    fclose(fp);
    return count;
}
