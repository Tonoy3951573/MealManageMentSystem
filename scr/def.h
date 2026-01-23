#ifndef DEF_H
#define DEF_H

#define MAX_USERS 50
#define MAX_LEN   30
#define MEAL_RATE_M 15
#define MEAL_RATE_D 40
#define MEAL_RATE_N 30
#define MENU_LIMIT 100

typedef struct 
{
    char roll_no[MAX_LEN];
    char date[MAX_LEN];
    double ammount;

} Credit_Log;


typedef struct {
    char rollno[MAX_LEN];
    char password[MAX_LEN];
} Login_pass;

typedef struct {
    char name[MAX_LEN];
    char roll_no[MAX_LEN];
    int room_number;
    double current_balance;
    int meals_consumed[31];
} Students;

// function prototypes
void clear_s(void);
void pre_login_page(void);
int  load_login_pass(Login_pass passKeys[], const char *filename);
int save_basic_info(Students student);
int  save_login_pass(Login_pass passKey);
void register_student(void);
void exit_p(void);
int load_students_info(Students students[],const char* filename);
int getDay();
int getTime();
void view_profile(char* roll_no);
void trim_leading_spaces(char *s);
void getDate(char *buffer, int size);
const char* get_meal_status(int meal_consumed[], int day);
int update_students_info(Students students[], int size);
int book_meal(Students students[], int ind,int day);
int cancel_meal(Students students[], int ind,int day);
int save_item(char* item, char* filename);
int edit_menu();
int load_menu(char items[][MAX_LEN], char* filename);
int show_menu();
int save_cradit_log(char* date, char* roll_no, double ammount);
int add_credit(char* roll_no, double credit);
int load_credit_log(Credit_Log credit_log[]);
void show_credit_log();
void show_meal_log(int day);
void genarate_monthly_bill(Students students);
int update_passwords(Login_pass paswords[], int size, char* filename);
void print_credit_log_by_Id(char* roll_no);
int reset_Pass(char* roll_no, char* pass,char* filename);
void all_student_list();
void search_by_rollno(char* roll_no);

#endif
