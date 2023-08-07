#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#pragma warning(disable:4996)

#define BOOK_A 69.00
#define BOOK_B 70.00
#define BOOK_C 55.50
#define BOOK_D 58.00
#define BOOK_E 65.00
#define BOOK_F 89.00
#define BOOK_G 73.50
#define BOOK_H 80.00
#define BOOK_I 50.00

int option();
int field();
int order(num);
double discount(subtotal);
int bookOrder[100][9] = { 0 };

int main() {
	int selOption, repeat;

	printf("< LOGO, WELCOME message, etc >\n");
	printf("UMT POS System\n");

	do{
		selOption = option();
		printf("\n");

		switch (selOption) {
		case 1: 
			repeat = field();
			break;
		case 2:
			repeat = 0;
			order(0);
			break;
		case 3:
			return 0;
		default:
			printf("Please enter number 1,2 or 3.\n");
			repeat = 1;
			break;
		}
	} while (repeat == 1);

	return 0;
}

int option() {
	int selection;
	printf("\nSelect an option (1 = View Menu, 2 = Sales Order, 3 = Exit): ");
	rewind(stdin);
	scanf("%d", &selection);
	return selection;
}

int field() {
	int selection;
	do {
		printf("Select a field to view:\n");
		printf("1 = Software Development Programming\n");
		printf("2 = Web Programming\n");
		printf("3 = Mobile Programming\n");
		printf("Input: ");
		rewind(stdin);
		scanf("%d", &selection);
		printf("\n");
	} while (!(selection > 0 && selection < 4));

	switch (selection) {
	case 1:
		printf("Software Development Programming Books: \n");
		printf("%-50s %s%.2f\n", "A = Beginning with Programming Logic and Design", "RM", BOOK_A);
		printf("%-50s %s%.2f\n", "B = C Programming", "RM", BOOK_B);
		printf("%-50s %s%.2f\n", "C = Programming Fundamentals", "RM", BOOK_C);
		break;
	case 2:
		printf("Web Programming Books: \n");
		printf("%-50s %s%.2f\n", "D = HTML and CSS Design", "RM", BOOK_D);
		printf("%-50s %s%.2f\n", "E = Web Programming", "RM", BOOK_E);
		printf("%-50s %s%.2f\n", "F = ASP .NET Programming", "RM", BOOK_F);
		break;
	case 3:
		printf("Mobile Programming Books: \n");
		printf("%-50s %s%.2f\n", "G = Mobile Design and Programming", "RM", BOOK_G);
		printf("%-50s %s%.2f\n", "H = Building Mobile App", "RM", BOOK_H);
		printf("%-50s %s%.2f\n", "I = Andriod Programming", "RM", BOOK_I);
		break;
	}

	printf("Press any key to continue...\n");
	getch();
	return 1;
}

int order(num) {
	int orderNo = num, i, qty, valid;
	char book, confirmation;
	char next = 'Y';
	char bookList[9] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I' };
	double bookPrice[9] = { BOOK_A, BOOK_B, BOOK_C, BOOK_D, BOOK_E, BOOK_F, BOOK_G, BOOK_H, BOOK_I };
	double sum[9] = {0};
	double subtotal[100] = {0};
	double discounts;
	int quantity, totalQty = 0;
	double total, totalPrice = 0;

	do {
		printf("Sales Order No: %d\n", orderNo + 1);
		for (i = 0; i < 9; i++) {
			bookOrder[orderNo][i] = 0;
		}

		do {
			printf("Book A,B,C,D,E,F,G,H,I (X = Exit): ");
			rewind(stdin);
			scanf("%c", &book);
			book = toupper(book);

			if (book != 'X') {
				valid = 0;
				for (i = 0; i < 9; i++) {
					if (book == bookList[i]) {
						valid += 1;
						do {
							qty = 0;
							rewind(stdin);
							printf("Quantity: ");
							scanf("%d", &qty);
							if (qty > 0) {
								bookOrder[orderNo][i] += qty;
							}
							else {
								printf("- Please input a positive integer.\n\n");
							}
						} while (qty <= 0);
					}
				}
				if (valid != 1) {
					printf("- Please choose a valid book.\n\n");
				}
			}
		} while (book != 'X');

		do {
			printf("Confirm the order? (Y = Yes, N = No): ");
			rewind(stdin);
			scanf("%c", &confirmation);
			confirmation = toupper(confirmation);
		} while (confirmation != 'Y' && confirmation != 'N');
		
		if (confirmation == 'Y') {
			printf("\n");
			subtotal[orderNo] = 0;
			for (i = 0; i < 9; i++) {
				sum[i] = 0;
				if (bookOrder[orderNo][i] < 0) {
					bookOrder[orderNo][i] = 0;
					sum[i] = 0;
				} else if (bookOrder[orderNo][i] != 0) {
					sum[i] = bookOrder[orderNo][i] * bookPrice[i];
					printf("Book %c: %d @ RM %-13.2f = %s%7.2f\n", bookList[i], bookOrder[orderNo][i], bookPrice[i], "RM", sum[i]);
				}
				subtotal[orderNo] += sum[i];
			}

			discounts = discount(subtotal[orderNo]);
			printf("%40s\n", "=========");
			printf("%-28s = %s%7.2f\n", "Subtotal", "RM", subtotal[orderNo]);
			printf("%-28s = %s%7.2f\n", "Discounts", "RM", discounts);
			printf("%40s\n", "=========");
			printf("%-28s = %s%7.2f\n", "Total to pay", "RM", subtotal[orderNo] - discounts);
			printf("\n %33s \n\n", "THANK YOU, HAVE A NICE DAY!!");
		}
		else if (confirmation == 'N') {
			printf("=========== Order Cancelled ===========\n\n");
			order(orderNo);
			break;
		}

		do {
			printf("Next order? (Y = Yes, N = No): ");
			rewind(stdin);
			scanf("%c", &next);
			next = toupper(next);
			printf("\n");

			if (next == 'Y') {
				orderNo += 1;
			}
		} while (next != 'Y' && next != 'N');

	} while (next == 'Y');
	
	if (next == 'N') {
		printf("=========================================\n");
		printf("%36s\n", "DAILY SALES ORDER SUMMARY REPORT");
		printf("=========================================\n");
		printf("Total Number of Sales Orders = %d\n\n", orderNo + 1);
		printf("%-10s %10s %10s\n", "Book", "Quantity Sold Sales", "Amount");
		for (i = 0; i < 9; i++) {
			quantity = 0;
			for (int j = 0; j <= orderNo; j++) {
				quantity += bookOrder[j][i];
			}
			total = bookPrice[i] * quantity;
			printf("%-10c %10d %19.2f\n", bookList[i], quantity, total);

			totalQty += quantity;
			totalPrice += total;
		}
		
		printf("=========================================\n");
		printf("%-10s %10d %19.2f\n", "TOTAL", totalQty, totalPrice);
		printf("=========================================\n");
	}

	return 0;
}

double discount(double(subtotal)) {
	double discount;
	if (subtotal > 500) {
		discount = subtotal * 15 / 100;
	}
	else if (subtotal > 300) {
		discount = subtotal * 10 / 100;
	}
	else if (subtotal > 200) {
		discount = subtotal * 5 / 100;
	}
	else {
		discount = 0;
	}

	return discount;
}