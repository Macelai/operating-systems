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
			if (feof(f) != 0) { //end of file
				emp.id = id;
				break;				
			}
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
	if ((emp.gender != 'm') && (emp.gender != 'f')) {
		printf("Gender should be 'm' or 'f'");
		return;
	}
	printf("Please type his salary \n");
	scanf("%f", &emp.salary);
	fwrite(&emp, sizeof(struct Employee), 1, f);
}

void removeEmployee(FILE *f) {
	printf("Removing employee, please type his id \n");
	int id;
	scanf("%d)", &id);
	while (1) {
		struct Employee tmp;
		fread(&tmp, sizeof(struct Employee), 1, f);
		if (feof(f) != 0) {
			printf("Employee not found");
			return;
		}
		if (id == tmp.id) {
			fseek(f, -sizeof(struct Employee), SEEK_CUR);
			tmp.id = 0;
			fwrite(&tmp, sizeof(struct Employee), 1, f);
			printf("Sucess \n");
			return;
		}
	}
}

void calculateAvarageSalaryByGender(FILE *f) {
	printf("Calculating the avarage salary by gender \n");
	int maleNumber = 0;
	int femaleNumber = 0;
	float sumMale = 0;
	float sumFemale = 0;
	while (1) {
		struct Employee tmp;
		fread(&tmp, sizeof(struct Employee), 1, f);
		if (feof(f) != 0)
			break;
		if (tmp.id == 0)
			continue;
		if (tmp.gender == 'm') {
			maleNumber++;
			sumMale += tmp.salary;
		} else {
			femaleNumber++;
			sumFemale += tmp.salary;
		}
	}
	printf("Avarage male salary: %f \n", sumMale/maleNumber);
	printf("Avarage female salary: %f \n", sumFemale/femaleNumber);
}

void exportTextFile(FILE *f) {
	char path[256];
	printf("Please type the name of the file to store the data \n");
	scanf("%s)", &path);
	FILE *final;
	if ((final = fopen(path, "w")) == NULL) {
		printf("Error opening/creating the file");			
	} else {
		while (1) {
			struct Employee tmp;
			fread(&tmp, sizeof(struct Employee), 1, f);
			if (feof(f) != 0)
				break;
			if (tmp.id != 0) {
				fprintf(final, "ID: %d \n", tmp.id);
				fprintf(final, "Name: %s \n", tmp.name);
				fprintf(final, "Gender: %c \n", tmp.gender);
				fprintf(final, "Salary: %f \n", tmp.salary);
			}
		}
	}
	fclose(final);
}

void compactData(FILE *f, char fileName[]) {
	FILE *copy;
	if ((copy = fopen("copy", "wb")) == NULL) {
		printf("Error creating the copy file");
	} else {
	  	while (1) {
			struct Employee tmp;
			fread(&tmp, sizeof(struct Employee), 1, f);
			if (feof(f) != 0)
				break;
			if (tmp.id != 0) {
				fwrite(&tmp, sizeof(struct Employee), 1, copy);
			}
		}
		fclose(copy);
		remove(fileName);
		rename("copy", fileName);
	}
	printf("Database compacted");
}

int main(int argc, char *argv[]) {
	if (argc == 3) {
		int option = atoi(argv[2]);
		FILE *f;
		f = fopen(argv[1], "ab+");
		fclose(f);
		switch(option) {
			case 1:
				if ((f = fopen(argv[1], "ab+")) == NULL) {
					printf("Error opening/creating the file");
				} else {
					addEmployee(f);
					fclose(f);
				}
				break;
			case 2:
				if ((f = fopen(argv[1], "rb+")) == NULL) {
					printf("Error opening/creating the file");			
				} else {
					removeEmployee(f);
					fclose(f);
				}
				break;
			case 3:
				if ((f = fopen(argv[1], "rb")) == NULL) {
					printf("Error opening/creating the file");
				} else {
					calculateAvarageSalaryByGender(f);
					fclose(f);
				}
				break;
			case 4:
				if ((f = fopen(argv[1], "rb")) == NULL) {
					printf("Error opening/creating the file");
				} else {
					exportTextFile(f);					
					fclose(f);
				}
				break;
			case 5:
				if ((f = fopen(argv[1], "rb")) == NULL) {
					printf("Error opening/creating the file");
				} else {
					compactData(f, argv[1]);					
					fclose(f);
				}
				break;
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
