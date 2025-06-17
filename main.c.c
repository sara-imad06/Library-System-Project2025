/*Sara Imad Abdou
ID #1241167
Section: Lab #1 , lecture #1 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXSIZE 100
#define NAMESIZE 50

void menu ();
void addBook(char names[][NAMESIZE], int bins[], double prices[], int *size);
void removeBook(char names[][NAMESIZE], int bins[], double prices[], int *size);
void searchForBook(char names[][NAMESIZE], int bins[], double prices[], int size);
void uploadDataFile(char names[][NAMESIZE], int bins[], double prices[], int *size);
void updateDataFile(char names[][NAMESIZE], int bins[], double prices[], int size);
void printBooks(char names[][NAMESIZE], int bins[], double prices[], int size);


int main()
{
    int bins[MAXSIZE]; int size = 0; int opp;
    double prices[MAXSIZE];
    char names[MAXSIZE][NAMESIZE];
    printf("Welcome to My BookStore Managment System: \n");
    uploadDataFile(names, bins, prices, &size);

        do {
        menu();
        scanf("%d",&opp);
        switch (opp) {
            case 1: addBook(names, bins, prices, &size); break;
            case 2: removeBook(names, bins, prices, &size); break;
            case 3: searchForBook(names, bins, prices, size); break;
            case 4: printBooks(names, bins, prices, size); break;
            case 5: updateDataFile(names, bins, prices, size);uploadDataFile(names, bins, prices, &size);printf("\nThank you for using My BookStore Managment System. GoodBye.\n");break;
            default: printf("Invalid Number \n");
        }
    }
        while (opp != 5);
    return 0;
}



void menu (){
    printf("\nPlease Select an Operation (1-5):\n");
    printf("1- Add a Book:\n");
    printf("2- Remove a Book:\n");
    printf("3- Search for a Book:\n");
    printf("4- Print Book List:\n");
    printf("5- Exit System:\n");
}




void addBook(char names[][NAMESIZE], int bins[], double prices[], int *size) {
    if (*size >= MAXSIZE) {
        printf("Error, Book list is full ! \n");
        return;
    }

    int newBin, pos = 0;
    double newPrice;
    char book_name[NAMESIZE];
    printf("Enter bin number for book \n");
    scanf("%d", &newBin);
    while (pos < *size) {
        if (bins[pos] == newBin) {
            printf("Book number already exists\n");
            return;
        }
        if (bins[pos] > newBin) {
            break;
        }
        pos++;
    }

    printf("Enter name of book\n");
    scanf("%s", book_name);

    for (int i = *size; i > pos; i--) {
    bins[i] = bins[i - 1];
    prices[i] = prices[i - 1];
    strcpy(names[i], names[i - 1]);
}

    printf("Enter price for book\n");
    scanf("%lf", &newPrice);

    bins[pos] = newBin;
        prices[pos] = newPrice;
    strcpy(names[pos], book_name);

    (*size)++;


    printf("Book with bin %d has been added\n", newBin);
}


void removeBook(char names[][NAMESIZE], int bins[], double prices[], int *size) {
    if (*size <= 0) {
        printf("Error,Book list is empty \n");
        return;
    }

    int binToRemove, pos = -1;
    printf("Enter bin number for book to remove\n");
    scanf("%d", &binToRemove);
    for (int i = 0; i < *size; i++) {
        if (bins[i] == binToRemove) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Book with bin %d does not exist\n", binToRemove);
        return;
    }
    for (int i = pos; i < *size - 1; i++) {
        bins[i] = bins[i + 1];
        prices[i] = prices[i + 1];
        strcpy(names[i], names[i + 1]);

    }
    (*size)--;
    printf("Book with bin %d has been removed\n", binToRemove);
}



void searchForBook(char names[][NAMESIZE], int bins[], double prices[], int size) {
    if (size <= 0) {
        printf("Error:,Book list is empty\n");
    }
    int binToSearch, found = 0;
    printf("Enter bin number for book to search for\n");
    scanf("%d", &binToSearch);

    for (int i = 0; i < size; i++) {
        if (bins[i] == binToSearch) {
            printf("Name = %-50s bin# = %d \t price = %.2f\n", names[i], bins[i], prices[i]);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book with bin %d does not exist\n", binToSearch);
    }
}


void printBooks(char names[][NAMESIZE], int bins[], double prices[], int size) {
    if (size == 0) {
        printf("The book list is empty\n");
        return;
    }


    for (int i = 0; i < size; i++) {
        printf("Name = %-50s bin# = %d \t price = %.2f\n", names[i], bins[i], prices[i]);

    }


}

void uploadDataFile(char names[][NAMESIZE], int bins[], double prices[], int *size) {
    FILE *in = fopen("books.txt", "r");

    if (in == NULL) {
        printf("Error\n");
        *size = 0;
        return;
    }

    int bin;
    double price;
    char bookName[NAMESIZE];
    *size = 0;

    while (fscanf(in, "%d%s%lf", &bin,bookName, &price) == 3 && *size < MAXSIZE){
        bins[*size] = bin;
        prices[*size] = price;
        strcpy(names[*size], bookName);
        (*size)++;
    }

     fclose(in);
     printf("\nUploading data file ...\n");
     printf("Data file uploaded \n");
}


void updateDataFile(char names[][NAMESIZE], int bins[], double prices[], int size) {
    FILE *out = fopen("books.txt", "w");

    if (out == NULL) {
        printf("Error\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(out, "%d\t%s\t%f\n", bins[i],names[i], prices[i]);
    }

    fclose(out);
    printf("Book data has been saved\n");
}

