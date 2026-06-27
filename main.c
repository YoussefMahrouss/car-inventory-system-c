#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum Role {
	Admin = 1,
	Customer = 2
};

enum CarStatus {
	Available,
	Sold
};

struct car {
	char model[30];
	int year;
	float price;
	enum CarStatus status;

	// 2D Array
	char features[3][30];
};

void showMenuByRole(enum Role role) {

	if (role == Admin) {

		printf("\n========== ADMIN MENU ==========\n");
		printf("1. Add Cars\n");
		printf("2. Display Cars\n");
		printf("3. Search By Model\n");
		printf("4. Sort By Price\n");
		printf("5. Sort By Year\n");
		printf("6. Exit\n");
	}
	else if (role == Customer) {

		printf("\n========= CUSTOMER MENU =========\n");
		printf("1. View Cars\n");
		printf("2. Search Car By Model\n");
		printf("3. Search By Budget\n");
		printf("4. Sort By Price\n");
		printf("5. Sort By Year\n");
		printf("6. Exit\n");
	}
	else {
		printf("Invalid role.\n");
	}
}

void addCars(struct car* Cars, int* n) {

	int x;

	printf("How many cars do you want to add? ");
	scanf_s("%d", &x);

	for (int i = 0; i < x; i++) {

		printf("\nEnter details for car %d\n", i + 1);

		printf("Model: ");
		scanf_s("%s", Cars[*n].model, (unsigned)_countof(Cars[*n].model));

		printf("Year: ");
		scanf_s("%d", &Cars[*n].year);

		printf("Price: ");
		scanf_s("%f", &Cars[*n].price);

		Cars[*n].status = Available;

		// 2D array input
		printf("Enter 3 features for the car:\n");

		for (int j = 0; j < 3; j++) {

			printf("Feature %d: ", j + 1);

			scanf_s("%s",
				Cars[*n].features[j],
				(unsigned)_countof(Cars[*n].features[j]));
		}

		(*n)++;
	}
}

void displayCars(struct car* Cars, int n) {

	if (n == 0) {
		printf("No cars available.\n");
		return;
	}

	printf("\n========== CAR LIST ==========\n");

	for (int i = 0; i < n; i++) {

		printf("\nCar %d\n", i + 1);
		printf("Model : %s\n", Cars[i].model);
		printf("Year  : %d\n", Cars[i].year);
		printf("Price : %.2f\n", Cars[i].price);

		printf("Features:\n");

		for (int j = 0; j < 3; j++) {
			printf("- %s\n", Cars[i].features[j]);
		}
	}
}

void searchByModel(struct car* Cars, int n) {

	char key[30];
	int found = 0;

	printf("Enter model to search: ");
	scanf_s("%s", key, (unsigned)_countof(key));

	for (int i = 0; i < n; i++) {

		if (strcmp(Cars[i].model, key) == 0) {

			printf("\nCar Found!\n");
			printf("Model : %s\n", Cars[i].model);
			printf("Year  : %d\n", Cars[i].year);
			printf("Price : %.2f\n", Cars[i].price);

			found = 1;
		}
	}

	if (!found) {
		printf("Car not found.\n");
	}
}

void bubbleSortByPrice(struct car* Cars, int n) {

	struct car temp;

	for (int i = 0; i < n - 1; i++) {

		for (int j = 0; j < n - i - 1; j++) {

			if (Cars[j].price < Cars[j + 1].price) {

				temp = Cars[j];
				Cars[j] = Cars[j + 1];
				Cars[j + 1] = temp;
			}
		}
	}

	printf("Cars sorted by price.\n");
}

void bubbleSortByYear(struct car* Cars, int n) {

	struct car temp;

	for (int i = 0; i < n - 1; i++) {

		for (int j = 0; j < n - i - 1; j++) {

			if (Cars[j].year < Cars[j + 1].year) {

				temp = Cars[j];
				Cars[j] = Cars[j + 1];
				Cars[j + 1] = temp;
			}
		}
	}

	printf("Cars sorted by year.\n");
}

void searchBudget(struct car* Cars, int n) {

	float budget;
	int found = 0;

	printf("Enter your budget: ");
	scanf_s("%f", &budget);

	for (int i = 0; i < n; i++) {

		if (Cars[i].price <= budget) {

			printf("\nRecommended Car\n");
			printf("Model : %s\n", Cars[i].model);
			printf("Year  : %d\n", Cars[i].year);
			printf("Price : %.2f\n", Cars[i].price);

			found = 1;
		}
	}

	if (!found) {
		printf("No cars available within your budget.\n");
	}
}

int main() {

	struct car* Cars;

	Cars = (struct car*)malloc(100 * sizeof(struct car));

	if (Cars == NULL) {

		printf("Memory allocation failed.\n");
		return 1;
	}

	int n = 0;
	int choice;
	enum Role role;

	while (1) {

		printf("\n1. Admin\n");
		printf("2. Customer\n");
		printf("Choose your role: ");

		scanf_s("%d", &role);

		showMenuByRole(role);

		printf("Enter your choice: ");
		scanf_s("%d", &choice);

		if (role == Admin) {

			switch (choice) {

			case 1:
				addCars(Cars, &n);
				break;

			case 2:
				displayCars(Cars, n);
				break;

			case 3:
				searchByModel(Cars, n);
				break;

			case 4:
				bubbleSortByPrice(Cars, n);
				break;

			case 5:
				bubbleSortByYear(Cars, n);
				break;

			case 6:
				free(Cars);
				printf("Program ended.\n");
				return 0;

			default:
				printf("Invalid choice.\n");
			}
		}

		else if (role == Customer) {

			switch (choice) {

			case 1:
				displayCars(Cars, n);
				break;

			case 2:
				searchByModel(Cars, n);
				break;

			case 3:
				searchBudget(Cars, n);
				break;

			case 4:
				bubbleSortByPrice(Cars, n);
				break;

			case 5:
				bubbleSortByYear(Cars, n);
				break;

			case 6:
				free(Cars);
				printf("Program ended.\n");
				return 0;

			default:
				printf("Invalid choice.\n");
			}
		}

		else {
			printf("Invalid role.\n");
		}
	}
}
