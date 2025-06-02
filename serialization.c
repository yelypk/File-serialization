#define _CRT_SECURE_NO_WARNINGS  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <stdbool.h>

//���������  

// ��������� ��� ��������� ����
// ��
// �����
// ����
struct Date {
	int year;
	int month;
	int day;
};

// �����
enum Sex
{
	male,
	female
};

// ��������� ��� ��������� ���������� ��� ��������
struct Student {
	char name[50]; // ��'� ��������
	char surname[50]; // ��'� ��������
	char patronymic[50]; // �� ������� ��������

	struct Date birthDate; // ���� ���������� ��������

	char group[10]; // ����� ��������

	enum Sex sex; // ����� �������� 
};

// defining a node
typedef struct LList {
	struct Student data;
	struct LList* next;
	struct LList* prev;
} LList;

// ��������� �������  
int main();
int myinput();
int mystringinput(char* line, int bufsize);
int sexToString(enum Sex val, char* result);
enum Sex sexFromString(const char* str);
LList* createLList(struct Student data);
void insertLList(LList** head, struct Student data);
void deleteLList(LList** head, char* name, char* surname);
void printLList(LList* head);
void saveToFile(LList* head, const char* filename);
void loadFromFile(LList** head, const char* filename);


// ������� ��� ����� � ��������

int sexToString(enum Sex val, char* result)
{   
    switch (val)  
    {  
    case male:  
        strcpy(result, "male");  
        break;  
    case female:  
        strcpy(result, "female");  
        break;  
    default:  
        strcpy(result, "female");  
        break;  
    }  
    return 0;  
}

enum Sex sexFromString(const char* str)
{
	if (strcmp(str, "male") == 0)
	{
		return male;
	}
	return female;
}



// �������� �����  
int myinput()
{
	char line[256];
	int i = 0;
	while (1)
	{
		if (fgets(line, sizeof(line), stdin)) {
			if (1 == sscanf(line, "%d", &i)) {
				// 1 - ������� �������� ������  
				break;
			}
			else
			{
				fprintf(stdout, "Incorrect number format, lets try again:\n");
			}
		}
		else
		{
			fprintf(stdout, "Input error, lets try again:\n");
		}
	}
	fprintf(stdout, "Parsed decimal number: %d \n", i);
	return i;
}

int mystringinput(char* line, int bufsize)
{
	while (1)
	{
		// ������� �����  
		memset(line, 0, bufsize);
		// ������� ����� � ���������  
		fgets(line, bufsize, stdin);

		if (strchr(line, '\n'))
		{
			// ��������� ������ ������ ����� � ���� �����
			line[strcspn(line, "\n")] = 0;
		}
		else
		{
			// ������� �����, ���� ����� �� ��������� � �����
			while (getchar() != '\n');
		}
		// ����������, �� ����� �� �������
		if (strlen(line) == 0) {
			fprintf(stdout, "Empty string, please enter a valid string:\n");
		}
		else if (strchr(line, '|') != NULL)
		{
			fprintf(stdout, "String contains forbidden character '|', please enter a valid string:\n");
		}
		else {
			break;
		}
	}

	// �������� ����� �� �����
	fprintf(stdout, "Parsed string: %s \n", line);

	return 0;
}

// Doubly Linked List


// Function to create a new node with given value as data
LList* createLList(struct Student data)
{
	LList* newNode = (LList*)malloc(sizeof(LList));
	if (newNode == NULL) {
		fprintf(stderr, "Memory allocation failed for new node.\n");
		exit(EXIT_FAILURE); // �������� �������(
	}
	newNode->data = data;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}

// Function to insert a node at the beginning
void insertLList(LList** head, struct Student data)
{
	// creating new node
	LList* newNode = createLList(data);

	// check if DLL is empty
	if (*head == NULL) {
		*head = newNode;
		return;
	}
	newNode->next = *head;
	(*head)->prev = newNode;
	*head = newNode;
}

// Function to delete a specified node
void deleteLList(LList** head, char* name, char* surname)
{
	if (*head == NULL) {
		fprintf(stdout, "The list is already empty.\n");
		return;
	}
	LList* temp = *head;

	while (temp != NULL) {
		if (strcmp(temp->data.name, name) == 0 && strcmp(temp->data.surname, surname) == 0) {
			// Node found
			break;
		}
		temp = temp->next;
	}

	if (temp == NULL) {
		fprintf(stdout, "Student with such name and surname not found.\n");
		return;
	}

	if(*head == temp) {
		// If the node to be deleted is the head node
		*head = temp->next;
		if (*head != NULL) {
			(*head)->prev = NULL;
		}
	} else {
		// If the node to be deleted is not the head node
		if (temp->prev != NULL) {
			temp->prev->next = temp->next;
		}
		if (temp->next != NULL) {
			temp->next->prev = temp->prev;
		}
	}

	free(temp);
}

// Function to print the list in forward direction
void printLList(LList* head)
{
	LList* temp = head;
	fprintf(stdout, "Students list.\n");
	while (temp != NULL) {
		fprintf(stdout, "Name: %s, Surname: %s, Group: %s\n", temp->data.name, temp->data.surname, temp->data.group);
		
		temp = temp->next;
	}
	printf("\n");
}

// ������ � �������

void saveToFile(LList* head, const char* filename) 
{
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		fprintf(stderr, "Could not open file %s for writing.\n", filename);
		return;
	}
	LList* temp = head;
	char sexStr[7]="female";
	while (temp != NULL) {
		sexToString(temp->data.sex, sexStr);
		fprintf(file, "%s|%s|%s|%d-%02d-%02d|%s|%s\n", 
			temp->data.name, 
			temp->data.surname, 
			temp->data.patronymic, 
			temp->data.birthDate.year, 
			temp->data.birthDate.month, 
			temp->data.birthDate.day, 
			temp->data.group,
			sexStr);
		

		temp = temp->next;
	}
	fclose(file);
	fprintf(stdout, "Data saved to %s\n", filename);
}

void loadFromFile(LList** head, const char* filename) 
{
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		fprintf(stdout, "File %s does not exist. Starting with an empty list.\n", filename);
		return;
	}

	char line[256]="";

	while (fgets(line, sizeof(line), file)) {
		if (strchr(line, '|') == NULL)
		{
			fprintf(stdout, "Invalid line format: %s", line);
			continue; // ���������� ��������� �����
		}

		struct Student student = { 0 }; // ���������� ��������� ��������

		char* part;
		part = strtok(line, "|");
		for (int i = 0; i < 6 && part != NULL; i++)
		{
			switch (i)
			{
			case 0:
			{
				strncpy(student.name, part, sizeof(student.name) - 1);
				student.name[sizeof(student.name) - 1] = '\0'; // �������� ���������
				break;
			}
			case 1:
			{
				strncpy(student.surname, part, sizeof(student.surname) - 1);
				student.surname[sizeof(student.surname) - 1] = '\0'; // �������� ���������
				break;
			}
			case 2:
			{
				strncpy(student.patronymic, part, sizeof(student.patronymic) - 1);
				student.patronymic[sizeof(student.patronymic) - 1] = '\0'; // �������� ���������
				break;
			}
			case 3:
			{
				if (sscanf(part, "%d-%02d-%02d", &student.birthDate.year, &student.birthDate.month, &student.birthDate.day) != 3) {
					fprintf(stdout, "Invalid date format: %s", part);
					continue; // ���������� ��������� �����
				}
				break;
			}
			case 4:
			{
				strncpy(student.group, part, sizeof(student.group) - 1);
				student.group[sizeof(student.group) - 1] = '\0'; // �������� ���������
				break;
			}
			case 5:
			{
				student.sex = sexFromString(part);
			}

			default:
				break;
			}

			part = strtok(NULL, "|");
		}
		// �������� �� ���������� �������� �����
		if (strlen(student.name) > 0 && strlen(student.surname) > 0) {
			insertLList(head, student);
		}

	}



	fclose(file);
}

// �������  

//�� ��������.��� ����� - �������� ������� ����������� 3 �����: 
// - ������� ������ ��������(�������� ���� �������, ��'�, �����), 
// - �������� ������ �������� (������� - �� ��������), ������� ��������� �������� (����� �� �������� �� ��'��, �������� ������� ��� ����������), 
// - �������� ��������� ��������(�� �������� �� ��'��). 
// ���������� ��� �������� ������� ������ �������, ��'�, �� - �������, ���� ����������(��������� ��� ����� ������ ���������, ������� ������ ��, �����, ����), ����� � ��� ���������(char*), �����(enum).
// ������ �������� ��������� �������� � ��'������ ������. 
// ��� ����� � �������� - �� ��� ������ ���������� � ���������� ���� data.txt. 
// ��� ����� �������� �������� �� ��� � ����� ������ ����������� 
// (���������� ������� �� ����� ���� �� �������� - � ����� ������� �������� ����������� �� ��� ���� �����, ���� ������� �������� ��������, �������� �� ����� �� �������� ���� data.txt). 
int main()
{
	LList* head = NULL; // ������ ������
	int choice;
	char filename[] = "data.txt"; // ��'� ����� ��� ���������� �����
	loadFromFile(&head, filename); // ������������ ����� � ����� ��� ����� ��������
    bool run = true; 
	while (run)
	{
		fprintf(stdout, "Choose an option:\n");
		fprintf(stdout, "1. Print students list\n");
		fprintf(stdout, "2. Add new student\n");
		fprintf(stdout, "3. Delete student\n");
		fprintf(stdout, "4. Exit\n");
		choice = myinput();
		switch (choice) {
		case 1:
			printLList(head);
			break;
		case 2: {
			struct Student newStudent = { 0 };
			fprintf(stdout, "Enter student's name:\n");
			mystringinput(newStudent.name, sizeof(newStudent.name));
			fprintf(stdout, "Enter student's surname:\n");
			mystringinput(newStudent.surname, sizeof(newStudent.surname));
			fprintf(stdout, "Enter student's patronymic:\n");
			mystringinput(newStudent.patronymic, sizeof(newStudent.patronymic));
			fprintf(stdout, "Enter birth date (YYYY-MM-DD):\n");
			char dateInput[11]; // YYYY-MM-DD + null terminator
			mystringinput(dateInput, sizeof(dateInput));
			if (sscanf(dateInput, "%d-%d-%d", &newStudent.birthDate.year, &newStudent.birthDate.month, &newStudent.birthDate.day)!=3) {
				fprintf(stdout, "Invalid date format. Please use YYYY-MM-DD.\n");
				continue; // ���������� ��������� ����
			}
			char sexInput[10];
			fprintf(stdout, "Enter student's sex (male or famale):\n");
			mystringinput(sexInput, sizeof(sexInput));
			newStudent.sex = sexFromString(sexInput);
			fprintf(stdout, "Enter student's group:\n");
			mystringinput(newStudent.group, sizeof(newStudent.group));
			insertLList(&head, newStudent);
			fprintf(stdout, "Student added successfully.\n");
			break;
		}
		case 3: {
			char name[50] = "", surname[50] = "";
			fprintf(stdout, "Enter student's name to delete:\n");
			mystringinput(name, sizeof(name));
			fprintf(stdout, "Enter student's surname to delete:\n");
			mystringinput(surname, sizeof(surname));
			deleteLList(&head, name, surname);
			fprintf(stdout, "Student deleted successfully.\n");
			break;
		}
		case 4: {
			run = false;
			break;
		}
		default:
			fprintf(stdout, "Invalid input, try again\n");
			break;
		}
	}

	saveToFile(head, filename); // ���������� ����� � ���� ����� �������

	// ����������� ������	
	LList* current = head;
	while (current != NULL) {
		LList* next = current->next;
		free(current);
		current = next;
	}
	fprintf(stdout, "Exiting program.\n");
	return 0;
}


