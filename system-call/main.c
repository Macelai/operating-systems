#include <stdio.h>

struct Employee {
	unsigned int id;
	char name[256];
	char gender;
	float salary;
};

void addEmployee(FILE *f) {
	struct Employee emp;
	printf("Adding a new employee, please type his id \n");
	int id;
	scanf("%d", &id);
	if (id > 0) {
		while (1) { //search if id already in use
			struct Employee tmp;
			fread(&tmp, sizeof(struct Employee), 1, f);
			if (feof(f) != 0) //end of file
				break;
			if (id == tmp.id) {
				printf("Id already in use, id must be unique \n");
				return;
			} else {
				emp.id = id;			
			}			
		}
	} else {
		printf("Id must be greater than 0 \n");
		return;
	}
	printf("Please type his name \n");
	scanf("%s", &emp.name);
	printf("Please type his gender (m or f) \n");
	scanf(" %c", &emp.gender);
	printf("Please type his salary \n");
	scanf("%f", &emp.salary);
	fwrite(&emp, sizeof(struct Employee), 1, f);
}

void removeEmployee(FILE *f) {
	printf("Removing employee, please type his id");
	int id;
	scanf("%d)", &id);
	while (1) {
		struct Employee tmp;
		fread(&tmp, sizeof(struct Employee), 1, f);
		if (feof(f) != 0)
			break;
		if (id == tmp.id) {
			
		}
	}
	
}

void calculateAvarageSalaryByGender(FILE *f) {
	
}

void exportTextFile(FILE *f) {
	
}

void compactData(FILE *f) {
	
}

int main(int argc, char *argv[]) {
	if (argc == 3) {
		FILE *f;
		if ((f = fopen(argv[1], "ab+")) == NULL) {
			printf("Error opening/creating the file");
		} else {
			int option = atoi(argv[2]);
			switch(option) {
				case 1:
					addEmployee(f);
				case 2:
					removeEmployee();
				case 3:
					calculateAvarageSalaryByGender();
				case 4:
					exportTextFile();
				case 5:
					compactData();
			}
		}
	} else {
		printf("Need to provide two arguments, the first one is the binary file and second is the option. \n");
		printf("1 - Add employee \n");
		printf("2 - Remove employee \n");
		printf("3 - Calculate avarage salary by gender \n");
		printf("4 - Export data to a text file \n");
		printf("5 - Compact data \n");
	}
	return 0;
}
