#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

//For Admin Password
#define MAX_SIZE_USER_NAME 30
#define MAX_SIZE_PASSWORD 20
#define FILE_NAME "CourseManagementSystem.bin"
#define FILE_HEADER_SIZE  sizeof(sFileHeader)


//define for Student Info
#define MAX_SEMESTERS 12
#define MAX_FIRST_SEMESTER_COURSES 3
#define MAX_SELECTED_COURSES 4
#define COURSE_CREDITS 3
#define COST_PER_CREDIT 5300


bool IsRunning = true;


//structure for admin password in file
typedef struct
{
    char username[MAX_SIZE_USER_NAME];
    char password[MAX_SIZE_PASSWORD];
} sFileHeader;


//structure for student in file
typedef struct student
{
    int id;
    char name[20];
} student;


//structure for semester in file
typedef struct Semester
{
    char sem[20];
}semester;


//structure for course in file
typedef struct Course
{
    char name[20];
}course;


//structure for Student Info
struct Student
{
    int semester;
    char id[20];
    char name[20];
    char courses[MAX_SELECTED_COURSES][10];
};



//Start of Student Function in Admin Panel With FILE
void AddStudent()
{
    FILE *fp = fopen("mystudent.txt","a");
    student *s;
    int n,i;
    printf("\n\n\n\t\t\tHow many students you want to add : ");
    scanf("%d",&n);

    s = (student*)calloc(n,sizeof(student));

    for(int i=0;i<n;i++)
    {
        printf("\n\n\t\t\tEnter Id : ");
        scanf("%d",&s[i]);
        fflush(stdin);
        printf("\n\t\t\tEnter Name : ");
        scanf("%[^\n]s",s[i].name);
        fwrite(&s[i],sizeof(student),1,fp);
    }
    printf("\n\t\t\tStudent Add Successfully\n");
    fclose(fp);
    free(s);
}

void DeleteStudent()
{
    student s1;
    FILE *fp,*fp1;
    int id,found=0;
    fp = fopen("mystudent.txt","r");
    fp1 = fopen("temp.txt","w");
    printf("\n\t\t\tEnter ID to delete : ");
    scanf("%d",&id);
    while(fread(&s1,sizeof(student),1,fp))
    {
        if(s1.id == id)
            found = 1;
        else
            fwrite(&s1,sizeof(student),1,fp1);
    }
    fclose(fp);
    fclose(fp1);
    if(found)
    {
        fp1 = fopen("temp.txt","r");
        fp = fopen("mystudent.txt","w");
        while(fread(&s1,sizeof(student),1,fp1))
        {
            fwrite(&s1,sizeof(student),1,fp);
        }
        fclose(fp);
        fclose(fp1);
        printf("\n\t\t\tSuccessfully Deleted.\n");
    }
    else printf("\n\t\t\tThere is no students found.\n");
}

void UpdateStudent()
{
    student s1;
    FILE *fp,*fp1;
    int id,found = 0;
    fp = fopen("mystudent.txt","r");
    fp1 = fopen("temp.txt","w");
    printf("\n\n\n\t\t\tEnter ID to Update : ");
    scanf("%d",&id);
    while(fread(&s1,sizeof(student),1,fp))
    {
        if(s1.id == id)
        {
            found = 1;
            fflush(stdin);
            printf("\n\n\n\t\t\tEnter New Name : ");
            scanf("%[^\n]s",s1.name);
        }
        fwrite(&s1,sizeof(student),1,fp1);
    }
    fclose(fp);
    fclose(fp1);
    if(found)
    {
        fp1 = fopen("temp.txt","r");
        fp = fopen("mystudent.txt","w");
        while(fread(&s1,sizeof(student),1,fp1))
        {
            fwrite(&s1,sizeof(student),1,fp);
        }
        fclose(fp1);
        fclose(fp);
        printf("\n\t\t\tSuccessfully Updated.\n");
    }
    else printf("\n\t\t\tThere is no students found.\n");
}

void ShowAllStudent()
{
    student s1;
    FILE *fp = fopen("mystudent.txt","r");
    while (fread(&s1,sizeof(student),1,fp))
    {
        printf("\n\t\t\tID : %-5d, Name : %-20s",s1.id,s1.name);
    }
    fclose(fp);
}
//End of Student Function in Admin Panel With FILE




//Start Semester Function in Admin Panel With FILE
void AddSemester() {
    FILE *sm = fopen("mysemester.txt", "a");
    semester *s;
    int n, i;
    printf("\n\n\n\t\t\tHow many semesters do you want to add: ");
    scanf("%d", &n);

    s = (semester*)calloc(n, sizeof(semester));

    for (i = 0; i < n; i++) {
        fflush(stdin);
        printf("\n\t\t\tEnter Name: ");
        scanf(" %[^\n]s", s[i].sem);
        fwrite(&s[i], sizeof(semester), 1, sm);
    }
    printf("\n\t\t\tSemesters added successfully\n");
    fclose(sm);
    free(s);
}


void DeleteSemester()
{
    semester s1;
    FILE *sm,*sm1;
    char name[50];
    int found=0;

    sm = fopen("mysemester.txt","r");
    sm1 = fopen("temp.txt","w");
    printf("\n\t\t\tEnter semester name to delete : ");
    fflush(stdin);
    gets(name);

    while(fread(&s1,sizeof(semester),1,sm))
    {
        if(strcmp(s1.sem, name)==0)
            found = 1;
        else
            fwrite(&s1,sizeof(semester),1,sm1);
    }
    fclose(sm);
    fclose(sm1);
    if(found)
    {
        sm1 = fopen("temp.txt","r");
        sm = fopen("mysemester.txt","w");
        while(fread(&s1,sizeof(semester),1,sm1))
        {
            fwrite(&s1,sizeof(semester),1,sm);
        }
        printf("\n\t\t\tSuccessfully Deleted.\n");
        fclose(sm);
        fclose(sm1);
    }
    else
    {
        printf("\n\t\t\tThere is no semester found.\n");
    }
    fclose(sm);
    fclose(sm1);
}



void ShowAllSemester() {
    semester s1;
    FILE *sm = fopen("mysemester.txt", "r");
    if (sm == NULL) {
        printf("\n\n\n\t\t\tFile not found or unable to open the file\n");
        return;
    }
    while (fread(&s1, sizeof(semester), 1, sm)) {
        printf("\n\t\t\tSemester Name: %-20s\n", s1.sem);
    }
    fclose(sm);
}
//End of Semester Function in Admin Panel With FILE




//Start of Course Function in Admin Panel With FILE
void AddCourse() {
    FILE *cn = fopen("mycourse.txt", "a");
    course *c;
    int n, i;
    printf("\n\n\n\t\t\tHow many Course do you want to add: ");
    scanf("%d", &n);

    c = (course*)calloc(n, sizeof(course));

    for (i = 0; i < n; i++) {
        fflush(stdin);
        printf("\n\t\t\tEnter Name: ");
        scanf(" %[^\n]s", c[i].name);
        fwrite(&c[i], sizeof(course), 1, cn);
    }
    printf("\n\t\t\tCourse added successfully\n");
    fclose(cn);
    free(c);
}


void DeleteCourse()
{
    course c1;
    FILE *cn,*cn1;
    char name[50];
    int found=0;

    cn = fopen("mycourse.txt","r");
    cn1 = fopen("temp.txt","w");
    printf("\n\t\t\tEnter course name to delete : ");
    fflush(stdin);
    gets(name);

    while(fread(&c1,sizeof(course),1,cn))
    {
        if(strcmp(c1.name, name)==0)
            found = 1;
        else
            fwrite(&c1,sizeof(course),1,cn1);
    }
    fclose(cn);
    fclose(cn1);
    if(found)
    {
        cn1 = fopen("temp.txt","r");
        cn = fopen("mycourse.txt","w");
        while(fread(&c1,sizeof(course),1,cn1))
        {
            fwrite(&c1,sizeof(course),1,cn);
        }
        fclose(cn);
        fclose(cn1);
        printf("\n\t\t\tSuccessfully Deleted.\n");
    }
    else printf("\n\t\t\tThere is no course found.\n");
}


void ShowAllCourse() {
    course c1;
    FILE *cn = fopen("mycourse.txt", "r");
    if (cn == NULL) {
        printf("\n\n\n\t\t\tFile not found or unable to open the file\n");
        return;
    }
    while (fread(&c1, sizeof(course), 1, cn)) {
        printf("\n\t\t\tCourse Name: %-20s\n", c1.name);
    }
    fclose(cn);
}
//End of Course Function in Admin Panel With FILE




//Loading in every function
void wait()
{
    system("cls");
    int i;
    printf("\n\n");
    char LoadingPleaseWait[100]   = "\n\t\t\t\t\t ========= Loading Please Wait ======\n";
    for(i=0; i<strlen(LoadingPleaseWait); i++)
    {
        printf("%c",LoadingPleaseWait[i]);
        Sleep(16);
    }
}
//End of Loading in every function



void headMessage(const char *message)
{
    system("cls");
    printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############      Admin Panel of Course Management System      ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\t\t\t----------------------------------------------------------------------------");
}

void welcomeMessage()
{
    system("cls");
    printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############      Admin Panel of Course Management System      ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\t\t\t----------------------------------------------------------------------------");
    printf("\n\n\n\t\t\t Enter any key to continue.....");
    getch();
}

void menu()
{
    int choice = 0;
    do
    {
        headMessage("ADMIN MENU");
        printf("\n\n\n\t\t\t1.Add Student");
        printf("\n\t\t\t2.Delete Student");
        printf("\n\t\t\t3.Update Student");
        printf("\n\t\t\t4.Show All Student");
        printf("\n\t\t\t5.Add Semester");
        printf("\n\t\t\t6.Delete Semester");
        printf("\n\t\t\t7.Show All Semester");
        printf("\n\t\t\t8.Add Course");
        printf("\n\t\t\t9.Delete Course");
        printf("\n\t\t\t10.Show All Course");
        printf("\n\t\t\t11.Update Password");
        printf("\n\t\t\t12.Go Back or Exit Project");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            wait();
            AddStudent();
            GoBackOrExit();
            break;
        case 2:
            wait();
            DeleteStudent();
            GoBackOrExit();
            break;
        case 3:
            wait();
            UpdateStudent();
            GoBackOrExit();
            break;
        case 4:
            wait();
            ShowAllStudent();
            GoBackOrExit();
            break;
        case 5:
            wait();
            AddSemester();
            GoBackOrExit();
            break;
        case 6:
            wait();
            DeleteSemester();
            GoBackOrExit();
            break;
        case 7:
            wait();
            ShowAllSemester();
            GoBackOrExit();
            break;
        case 8:
            wait();
            AddCourse();
            GoBackOrExit();
            break;
        case 9:
            wait();
            DeleteCourse();
            GoBackOrExit();
            break;
        case 10:
            wait();
            ShowAllCourse();
            GoBackOrExit();
            break;
        case 11:
            wait();
            UpdatePassword();
            break;
        case 12:
            GoBack_From_Admin();
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }                                            //Switch Ended
    }
    while(choice!=0);                                        //Loop Ended
}



//For Admin Password in File
void login()
{
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    int L=0;
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    headMessage("Login");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    fflush(stdin);
    do
    {
        printf("\n\n\n\t\t\t\tUsername:");
        fgets(userName,MAX_SIZE_USER_NAME,stdin);
        printf("\n\t\t\t\tPassword:");
        fgets(password,MAX_SIZE_PASSWORD,stdin);
        if((!strcmp(userName,fileHeaderInfo.username)) && (!strcmp(password,fileHeaderInfo.password)))
        {
            menu();
        }
        else
        {
            printf("\n\t\t\t\tLogin Failed Enter Again Username & Password\n\n");
            L++;
        }
    }
    while(L<=1);
    if(L>1)
    {
        headMessage("\n\nLogin Failed");
        int i;
        char SorryUnknownUser[100] = "\n\n\n\n\t\t\t\t\t ========= Sorry Unknown User ======\n";
        for(i=0; i<strlen(SorryUnknownUser); i++)
        {
            printf("%c",SorryUnknownUser[i]);
            Sleep(40);
        }
        getch();
        system("cls");
    }
}



//For default Password
void init()
{
    FILE *fp = NULL;
    int status = 0;
    const char defaultUsername[] ="Shamim\n";
    const char defaultPassword[] ="Shamim\n";
    sFileHeader fileHeaderInfo = {0};
    status = isFileExists(FILE_NAME);
    if(!status)
    {
        //create the binary file
        fp = fopen(FILE_NAME,"wb");
        if(fp != NULL)
        {
            //Copy default password
            strncpy(fileHeaderInfo.password,defaultPassword,sizeof(defaultPassword));
            strncpy(fileHeaderInfo.username,defaultUsername,sizeof(defaultUsername));
            fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
            fclose(fp);
        }
    }
}



//For Admin Update Password
void UpdatePassword(void)
{
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    headMessage("Update Password");
    fp = fopen(FILE_NAME,"rb+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    if (fseek(fp,0,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while updating password\n");
        exit(1);
    }
    printf("\n\n\t\t\tNew Username:");
    fflush(stdin);
    fgets(userName,MAX_SIZE_USER_NAME,stdin);
    printf("\n\n\t\t\tNew Password:");
    fflush(stdin);
    fgets(password,MAX_SIZE_PASSWORD,stdin);
    strncpy(fileHeaderInfo.username,userName,sizeof(userName));
    strncpy(fileHeaderInfo.password,password,sizeof(password));
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    printf("\n\t\t\tYour Password has been changed successfully");
    printf("\n\n\t\t\tPress any key to continue : ");
    fflush(stdin);
    GoBackOrExit();
}



//Used to go back to from Admin to Main function
void GoBack_From_Admin()
{
    getchar();
    char Option;
    printf("\n\t\t\tGo back(b)? or Exit(0)?: ");
    scanf("%c",&Option);
    if(Option == '0')
    {
        ExitProject();
    }
    else if(Option=='b')
    {
        system("cls");
        main();
    }
}



//Used to go back from function
void GoBackOrExit()
{
    getchar();
    char Option;
    printf("\n\n\t\t\tGo back(b)? or Exit(0)?: ");
    scanf("%c",&Option);
    if(Option == '0')
    {
        ExitProject();
    }
    else if(Option=='b')
    {
        system("cls");
    }
}


//Welcome Message For Student
void welcomeMessage_student()
{
    system("cls");
    printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############        Student Panel of Course management         ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\t\t\t----------------------------------------------------------------------------");
}



void waitForEnter()
{
    fflush(stdin);
    printf("\n\n\t\t\tPress Enter to proceed payment...\n");
    getchar();
}



//Loading page before showing courses
void wait_In_student_panel()
{
    system("cls");
    int i;
    printf("\n\n");
    char LoadingPleaseWait[100]   = "\n\t\t\t\t\t ========= Loading Please Wait ======\n";
    for(i=0; i<strlen(LoadingPleaseWait); i++)
    {
        printf("%c",LoadingPleaseWait[i]);
        Sleep(16);
    }
}


//Loading page for payment
void wait_In_student_Payment()
{
    system("cls");
    int i;
    printf("\n\n");
    char LoadingPleaseWait[100]   = "\n\t\t\t\t\t ========= Loading Please Wait ======\n";
    for(i=0; i<strlen(LoadingPleaseWait); i++)
    {
        printf("%c",LoadingPleaseWait[i]);
        Sleep(16);
    }
}



int calculateTotalCredits(struct Student student)
{
    int totalCredit = 0;
    for (int i = 0; i < MAX_SELECTED_COURSES; i++)
    {
        totalCredit += COURSE_CREDITS;
    }
    return totalCredit;
}



void studentPayment(struct Student student)
{
    int totalCredit = calculateTotalCredits(student);
    int totalFee = totalCredit * COST_PER_CREDIT;

    printf("\n\n\t\t\t===== Payment Details =====");
    printf("\n\t\t\tTotal Credits: %d", totalCredit);
    printf("\n\t\t\tCost per Credit: %d Tk.", COST_PER_CREDIT);
    printf("\n\t\t\tTotal Fee: %d Tk.", totalFee);
    printf("\n\t\t\tSuccessully Paid.");
    printf("\n\t\t\t============================\n");
    printf("\n\t\t\tPress any key to proceed\n");
}



void displayStudentMenu(struct Student student)
{

    fflush(stdin);
    waitForEnter();
    wait_In_student_Payment();
    printf("\n\t\t\t====== Student Menu ======\n");
    printf("\n\t\t\tName: %s", student.name);
    printf("\n\t\t\tSemester: %d", student.semester);

    printf("\n\n\t\t\t====== Selected Courses ======");
    for (int i = 0; i < MAX_SELECTED_COURSES; i++)
    {
        if (strlen(student.courses[i]) > 0)
        {
            printf("\n\t\t\tCourse %d: %s", i + 1, student.courses[i]);
        }
    }

    studentPayment(student);

}



void Student_Info()
{
    welcomeMessage_student();

    struct Student student;

    printf("\n\n\n\t\t\tEnter ID: ");
    scanf("%s", student.id);

    fflush(stdin);

    printf("\n\t\t\tEnter Name: ");
    fgets(student.name, sizeof(student.name), stdin);
    student.name[strcspn(student.name, "\n")] = '\0';

    printf("\n\t\t\tEnter Semester (1-%d): ", MAX_SEMESTERS);
    scanf("%d", &student.semester);

    wait_In_student_panel();

    if (student.semester == 1)
    {
        printf("\n\n\n\t\t\tCourse 1: ENG 101\n\t\t\tCourse 2: MAT 101\n\t\t\tCourse 3: CSE 103\n\t\t\tCourse 4: CSE 103 Lab\n");
        // Assign fixed courses for the first semester
        strcpy(student.courses[0], "ENG 101");
        strcpy(student.courses[1], "MAT 101");
        strcpy(student.courses[2], "CSE 103");
        strcpy(student.courses[3], "CSE 103 Lab");
    }
    else if (student.semester >= 2 && student.semester <= MAX_SEMESTERS)
    {
        printf("\n\n\n\t\t\tAvailable Courses:ENG102, MAT102, CSE106, CHE109,\n   \t\t\t\t\t  PHY109, MAT104, CSE110, GEN226,\n   \t\t\t\t\t  SAT102, CSE200, CSE209, EGE,\n   \t\t\t\t\t  MAT205, CSE207, CSE251, EGE2,\n   \t\t\t\t\t  PHY209, CSE221, EGE3, CSE326,\n   \t\t\t\t\t  CSE302, CSE345, CSE347, CM1,\n   \t\t\t\t\t  CSE360, CSE405, CSE2, CSE401,\n   \t\t\t\t\t  CSE407, EM1, ENM1, CSE402,\n   \t\t\t\t\t  CSE487, EM2, ENM2, CSE403,\n   \t\t\t\t\t  CSE495, EM3\n");
        printf("\n\n\n\t\t\tEnter up to %d Courses\n\n\t\t\t(enter course separated by space): ", MAX_SELECTED_COURSES);

        for (int i = 0; i < MAX_SELECTED_COURSES; i++)
        {
            scanf("%s", student.courses[i]);
        }
    }
    else
    {
        printf("\n\n\n\t\t\tInvalid Semester.\n");
        return 1;
    }

    fflush(stdin);

    displayStudentMenu(student);
}

//void ExitProject()
//{
//    system("cls");
//    int i;
//    printf("\n\n");
//    char ThankYou[100]     = "\n\t\t\t\t\t =========  Thank You =========\n";
//    char SeeYouSoon[100]   = "\n\t\t\t\t\t ========= See You Soon ======\n";
//    for(i=0; i<strlen(ThankYou); i++)
//    {
//        printf("%c",ThankYou[i]);
//        Sleep(40);
//    }
//    for(i=0; i<strlen(SeeYouSoon); i++)
//    {
//        printf("%c",SeeYouSoon[i]);
//        Sleep(40);
//    }
//    exit(0);
//}


void ExitProject()
{
    system("cls");
    int i;
    printf("\n\n");
    char WEHADTOWORKHARDTODOTHISPROJECT[100]= "\n\t\t\t\t========= WE WORKED VERY HARD TO DO THIS PROJECT =========\n";
    char CRYINGOUTLOUDINCORNER[100]   =     "\n\t\t\t\t   ========= (CRYING LOUDLY IN THE CORNER) =========\n";
    char ThankYou[100]     = "\n\t\t\t\t\t    ========= Thank You =========\n";
    for(i=0; i<strlen(WEHADTOWORKHARDTODOTHISPROJECT); i++)
    {
        printf("%c",WEHADTOWORKHARDTODOTHISPROJECT[i]);
        Sleep(40);
    }
    for(i=0; i<strlen(CRYINGOUTLOUDINCORNER); i++)
    {
        printf("%c",CRYINGOUTLOUDINCORNER[i]);
        Sleep(40);
    }
    for(i=0; i<strlen(ThankYou); i++)
    {
        printf("%c",ThankYou[i]);
        Sleep(40);
    }
    printf("\n\n");
    exit(0);
}



int isFileExists(const char *path)
{
    // Try to open file
    FILE *fp = fopen(path, "rb");
    int status = 0;
    // If file does not exists
    if (fp != NULL)
    {
        status = 1;
        // If File exists close file
        fclose(fp);
    }
    return status;
}


int main()
{
    while(IsRunning)
    {

        system("cls");
        printf("\t\t\t###########################################################################");
        printf("\n\t\t\t############                                                   ############");
        printf("\n\t\t\t############      Course management System Project in C        ############");
        printf("\n\t\t\t############                                                   ############");
        printf("\n\t\t\t###########################################################################");
        printf("\n\t\t\t---------------------------------------------------------------------------\n");
        printf("\n\t\t\t----------------------------------------------------------------------------");

        int n;
        printf("\n\n\n\t\t\t1.Admin");
        printf("\n\t\t\t2.Student");
        printf("\n\t\t\t3.Exit Project");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&n);

        switch(n)
        {
            case 1:
                system("cls");
                init();
                welcomeMessage();
                login();
                break;
            case 2:
                system("cls");
                Student_Info();
                GoBackOrExit();
                break;
            case 3:
                system("cls");
                ExitProject();
                break;
            default:
                printf("\n\t\t\tInvalid Input.\n");

        }
    }
}
