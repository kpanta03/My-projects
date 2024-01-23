#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int sn = 1;

void insert();
void search();
void modify();
void display();
void removerecord();
void sort();

struct emp {
    char name[50];
    int age;
    float salary;
    int emp_id;
    char join_date[10];
    int phone_number;
    char department[20];
    struct emp *prev;
    struct emp *next;
};

struct emp *head = NULL;
struct emp *tail = NULL;

void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void insertatend(char name[], int age, float salary, int emp_id, char join_date[], int phone_number, char department[]) {
    struct emp *newnode;
    struct emp *temp;
    newnode = (struct emp *)malloc(sizeof(struct emp));
    strcpy(newnode->name, name);
    newnode->age = age;
    newnode->salary = salary;
    newnode->emp_id = emp_id;
    strcpy(newnode->join_date, join_date);
    newnode->phone_number = phone_number;
    strcpy(newnode->department, department);

    newnode->prev = NULL;
    newnode->next = NULL;

    if (head == NULL) {
        head = newnode;
        tail = newnode;
        return;
    }
    temp = tail;
    temp->next = newnode;
    newnode->prev = temp;
    tail = newnode;
}

void savetofile() {
    FILE *file = fopen("employee_records.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    struct emp *temp = head;

    while (temp != NULL) {
        fprintf(file, "%s %d %.2f %d %s %d %s\n", temp->name, temp->age, temp->salary,
                temp->emp_id, temp->join_date, temp->phone_number, temp->department);

        temp = temp->next;
    }

    fclose(file);
}

void loadfromfile() {
    FILE *file = fopen("employee_records.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    struct emp employee;

    while (fscanf(file, "%49[^\n] %d %f %d %9s %d %19[^\n]",
                  employee.name, &employee.age, &employee.salary,
                  &employee.emp_id, employee.join_date, &employee.phone_number,
                  employee.department) != EOF) {

        insertatend(employee.name, employee.age, employee.salary, employee.emp_id,
                    employee.join_date, employee.phone_number, employee.department);
    }

    fclose(file);
}

void printEmployeeDetails(struct emp *employee) {
    printf("\n");
    printf("---------------------------------\n");
    printf("\t --Employee found--\n");
    printf("---------------------------------\n");
    printf("\n");
    printf("\t Found Detail is : \n");
    printf("\t Name: %-30s \n", employee->name);
    printf("\t Age: %d \n", employee->age);
    printf("\t Salary: %.2f \n", employee->salary);
    printf("\t Employee Id: %d \n", employee->emp_id);
    printf("\t Join Date: %s \n", employee->join_date);
    printf("\t Phone number: %.d \n", employee->phone_number);
    printf("\t Department: %s \n", employee->department);
}

int main() {
    int choice;
    char another;
    loadfromfile();

    do {
        system("cls");
        printf("\n***********************************************************************************************************************************\n\n");
        printf("*\t\t\t\t\tEmployee Management System    \t\t\t\t\t\t\t  *\n\n");
        printf("************************************************************************************************************************************\n\n");
        printf("1. Insert record\n");
        printf("2. Search record\n");
        printf("3. Modify record\n");
        printf("4. Display record\n");
        printf("5. Delete record\n");
        printf("6. Sort record\n");
        printf("7. Exit\n");
        printf("************************************************************************************************************************************\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                system("cls");
                another = 'y';
                while (another == 'y' || another == 'Y') {
                    insert();
                    savetofile();
                    printf("\nAdd another record(y/n) : ");
                    clear_buffer();
                    scanf(" %c", &another);  // Note the space before %c
                }
                break;

            case 2:
                system("cls");
                search();
                clear_buffer();
                getch();
                break;

            case 3:
                system("cls");
                another = 'y';
                while (another == 'y' || another == 'Y') {
                    modify();
                    printf("\nModify another record(y/n) : ");
                    clear_buffer();
                    scanf(" %c", &another);
                }
                break;

            case 4:
                system("cls");
                another = 'y';
                while (another == 'y' || another == 'Y') {
                    display();
                    printf("\nPress any key other than y to go to record menu : ");
                    clear_buffer();
                    scanf(" %c", &another);
                }
                break;

            case 5:
                system("cls");
                another = 'y';
                while (another == 'y' || another == 'Y') {
                    removerecord();
                    savetofile();
                    printf("\nDelete another record(y/n) : ");
                    clear_buffer();
                    scanf(" %c", &another);
                }
                break;

            case 6:
                system("cls");
                sort();
                clear_buffer();
                getch();
                break;

            case 7:
                printf("\n");
                printf("\t EXIT FROM THE RECORD\n");
                printf("\t THANK YOU :)\n");
                return 0;

            default:
                printf("Invalid operation\n");
                break;
        }
    } while (choice != 8);

    return 0;
}

void insert() {
    char name[50];
    int age;
    float salary;
    int emp_id;
    char join_date[10];
    int phone_number;
    char department[20];

    printf("\n\n\n\n");
    printf("\tEnter the name of employee:\t ");
    clear_buffer();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("\tEnter age of employee:\t\t ");
    scanf("%d", &age);

    printf("\tEnter salary of employee:\t ");
    scanf("%f", &salary);

    printf("\tEnter employee_id:\t\t");
    scanf("%d", &emp_id);

    printf("\tEnter joindate of employee:\t ");
    clear_buffer();
    fgets(join_date, sizeof(join_date), stdin);
    join_date[strcspn(join_date, "\n")] = '\0';

    printf("\tEnter phone number of employee: ");
    scanf("%d", &phone_number);

    printf("\tEnter department of employee:\t");
    clear_buffer();
    fgets(department, sizeof(department), stdin);
    department[strcspn(department, "\n")] = '\0';

    insertatend(name, age, salary, emp_id, join_date, phone_number, department);
}

void display() {
    struct emp *temp;
    if (head == NULL) {
        printf("No employee record found.\n");
        return;
    }

    temp = head;
    printf("\n");
    printf("\---------------------------------\n");
    printf("\t--- Employees Records ---\n");
    printf("---------------------------------\n");
    while (temp != NULL) {
        printf("\t SN    :   00%d \n", sn++);
        printf("\t Name  :   %-30s \n", temp->name);
        printf("\t Age   :   %d \n", temp->age);
        printf("\t Salary:   %.2f \n", temp->salary);
        printf("\t Employee-id  :  %d \n", temp->emp_id);
        printf("\t Join Date  :  %s \n", temp->join_date);
        printf("\t Phone number:  %.d \n", temp->phone_number);
        printf("\t Department:  %s \n", temp->department);

        printf("-------------------------------\n");
        printf("-------------------------------\n");
        temp = temp->next;
    }
}

void search() {
    
int choice;
printf("\n");
printf("Search by employee Id:\n");
clear_buffer();

struct emp *temp = head;

        int emp_id;
        printf("\nEnter the employee ID to search for: ");
        scanf("%d", &emp_id);
        clear_buffer();

        while (temp != NULL) {
            if (temp->emp_id == emp_id) {
                printEmployeeDetails(temp);
                return;
            }
            temp = temp->next;
        }

        printf("\t Employee not found.\n");
    }



void modify() {
    char name[30];
    struct emp *temp;

    printf("\n");
    printf("Enter the name of the employee to Modify : ");
    clear_buffer();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    temp = head;

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            printf("\t Enter Name: ");
            clear_buffer();
            fgets(temp->name, sizeof(temp->name), stdin);
            temp->name[strcspn(temp->name, "\n")] = '\0';
            printf("\t Enter Age: ");
            scanf("%d", &temp->age);
            printf("\t Enter new Salary: ");
            scanf("%f", &temp->salary);
            printf("\t Enter employee id: ");
            scanf("%d", &temp->emp_id);
            printf("\t Enter join date: ");
            clear_buffer();
            fgets(temp->join_date, sizeof(temp->join_date), stdin);
            temp->join_date[strcspn(temp->join_date, "\n")] = '\0';
            printf("\t Enter new phone number: ");
            scanf("%d", &temp->phone_number);
            printf("\t Enter new department:");
            clear_buffer();
            fgets(temp->department, sizeof(temp->department), stdin);
            temp->department[strcspn(temp->department, "\n")] = '\0';

            printf("\t Record modified successfully.\n");
            return;
        }

        temp = temp->next;
    }

    printf("Employee record not found.\n");
}

void removerecord() {
    int emp_id;
    struct emp *temp, *prev;

    printf("\nEnter the employee ID to delete: ");
    scanf("%d", &emp_id);
    clear_buffer();

    temp = head;
    prev = NULL;

    while (temp != NULL) {
        if (temp->emp_id == emp_id) {
            if (prev == NULL) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }

            if (temp->next != NULL) {
                temp->next->prev = prev;
            }

            free(temp);
            printf("Record with ID %d deleted successfully.\n", emp_id);
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    printf("\t Employee with ID %d not found.\n", emp_id);
}

void sort()
{
    struct emp *temp, *swap;
    int swapped;

    if (head == NULL) {
        printf("No records to sort.\n");
        return;
    }

    do {
        swapped = 0;
        temp = head;

        while (temp->next != NULL) {
            if (temp->emp_id > temp->next->emp_id) {
                // Swap the nodes
                if (temp == head) {
                    head = temp->next;
                    temp->next->prev = NULL;
                } else {
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                }

                temp->next = temp->next->next;

                if (temp->next != NULL) {
                    temp->next->prev = temp;
                }

                temp->prev = temp->next;
                temp->next = temp->next->next;

                if (temp->next != NULL) {
                    temp->next->prev = temp;
                }

                swapped = 1;
            } else {
                temp = temp->next;
            }
        }
    } while (swapped);

    printf("Records sorted by ID.\n");
}




