/***********************************************************************************************
* THIS PROJECT MAINLY FOCUS ON RECOMMENDATION OF SELF HELP BOOKS.
* WE CAN EXTEND THIS PROGRAM FOR RECOMMENDATION OF ALL TYPES OF BOOKS.
* THE DETAIL OF BOOK IS STORED IN THE TEXT FILES IN THE MENTIONED ORDER
*	- NAME OF THE BOOK.
*	- AUTHOR NAME
*	- PUBLISHER NAME
*	- GENRE OF THE BOOK.
*	- NO OF THE PAGES.
*	- PRICE OF THE BOOK
*	- ABOUT BOOK.
*	- ABOUT AUTHOR.
*
* FEATURES OF THE PROGRAM ARE -
*	- CREATE A NEW BOOK FROM DETAILS ENTERED BY USER.
*	- LIST THE BOOKS AVAILABLE.
*	- PRINT THE DETAILS ABOUT THE BOOK.
*	- SAVES THE NEWLY ADDED BOOK DETAILS(book name, address of the file of that book)
	  INTO A SEPERATE FILE AND CREATE A NEW FILE FOR DETAILS ABOUT BOOK.
*	- DETAILS OF ALL BOOKS AND ITS TEXT FILE ADDRESS IS STORED INTO A SEPERATE TEXT FILE.
*
**********************************************************************************************
* NOTE : THE LOCATION DETAILS OF THE FILES ARE IN LINUX UBUNTU CONVETIONS. IF YOU ARE USING 
	WINDOWS OR OTHER OS, PLEASE CHANGE THE LOCATION OF FILE BEFORE COMPILING THE PROGRAM.
**********************************************************************************************
*
* CODED BY : CHETAN S
* DATE : 15/12/21
************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX_CAPACITY 200

typedef struct{
	char bookName[200];
	char genre[40];
	char authorName[50];
	char publisherName[50];
	char bookSummary[800];
	char aboutAuthor[800];
	char *fileName;
	int noOfPages;
	int price;  // Prices from amazon only
}Book;

//add sound wheNever error occur.

// Returns the no of lines in the text file.
int noOfValuesInFile(char *fileName){
	int n = 0;
	FILE *fbook = fopen(fileName,"r");
	char c;
	while((c = fgetc(fbook)) != EOF){
		if(c == '\n')
			++n;
	}
	return n;
}

// Returns the size of 2d character array.
int noOfValuesInVar(char** values){
	int n = 0;
	while(values[n] != NULL){
		n++;
	}
	return n;
}

// Returns a newly created file name. (location/nameOfFile.txt)
char* createFileName(char *location,char *nameOfFile){
	char *str,*str1;
	str = (char*)malloc(sizeof(char)*200);
	str1 = (char*)malloc(sizeof(char)*204);
	strcpy(str,location);
	strcat(str,nameOfFile);
	sprintf(str1,"%s.txt",str);
	free(str);
	return str1;
}

// Copies the text from the opened text file and returns the read string.
char* copy(FILE* fbook){
	char *str = (char*)malloc(sizeof(char)*200);
	int i = 0;
	char c;
	while((c = fgetc(fbook)) != '\n'){
		if(c == EOF)
			break;
			
		str[i] = c;
		++i;
	}
	return str;
}

// Add text into the text file in provided format
bool add(char* value,FILE* fbook){
	if(fprintf(fbook,"%s\n",value))
		return true;
	else
		return false;
}

// Copies the text from the text file to 2D characted array during the starting of program.
void load(char **storeValues,char *fileName){
	FILE *fbook = fopen(fileName,"r");
	if(!fbook){
		printf("\aFailed to open File !!\n");
		exit(0);
	}
	fseek(fbook,0,SEEK_SET);
	
	int n = 0;
	
// To load values in file into their respective variables.
	n = noOfValuesInFile(fileName); // get max. no. of values stored in file.
	for(int i = 0; i < n; ++i){
		storeValues[i] = (char*)malloc(200*sizeof(char));
		strcpy(storeValues[i],copy(fbook));
	}
	fclose(fbook);
}

// Stores the data into text file by copying the data from 2D character array
void save(char **storedValues,char *fileName){
	FILE *fbook = fopen(fileName,"w");
	int n = noOfValuesInVar(storedValues);
	
	for(int i = 0; i < n; ++i){
		add(storedValues[i],fbook);
	}
}

// Creates a new book file, from getting the details from user.
bool createBook(char** newlyAddedBookNames,char **newlyAddedBookFileNames,char **bookNames){
	
//Temporary Variables
	char *str = (char*)malloc(sizeof(char)*204);
	char chr;
	bool foundInBooks = false;
	bool foundInNew = false;
	int n1,n2;
	FILE* fbook;
	
//Variables to store details of the book
	Book *book = (Book*)malloc(sizeof(Book));
	book->fileName = (char*)malloc(sizeof(char)*204);
	
	n1 = noOfValuesInVar(bookNames);
	n2 = noOfValuesInVar(newlyAddedBookNames);
	
	printf("PLEASE ENTER DETAILS ABOUT BOOK (KINDLY ENTER DETAILS IN CAPITAL LETTER) :-\n");
	
	printf("Enter the Name of the Book : ");
	scanf("%[^\n]%*c",book->bookName);
	strcpy(str,book->bookName);
	
//check for already exist condition	

	//check for value n
	for(int i = 0; i < n1; ++i){
		 if(strcmp(book->bookName,bookNames[i]) == 0)	
			foundInBooks = true;
	}
	for(int i = 0; i < n2; ++i){
		if(strcmp(book->bookName,newlyAddedBookNames[i]) == 0)	
			foundInNew = true;
	}
	
	if(foundInNew){
		//Add sound here
		printf("\aENTRY EXIST! BOOK IS BEING REVIEVED BY US. THANK YOU FOR YOUR PATIENCE ......\n");
		return false;
	}else if(foundInBooks){
		//Add sound here
		printf("\aENTRY EXIST! PLEASE CHECK BY SELECTING CORRECT KEYWORD or BY ENTERING THE NAME OF BOOK\n");
		return false;
	}

//Reading the values	
	printf("Enter the Name of the Author : ");
	scanf("%[^\n]%*c",book->authorName);

	printf("Enter the Genre of the Book : ");
	scanf("%[^\n]%*c",book->genre);
	
	printf("Enter the Number of Pages : ");
	scanf("%d",&book->noOfPages);
	scanf("%c",&chr);
		
	printf("Enter the Publisher Name : ");
	scanf("%[^\n]%*c",book->publisherName);
		
	printf("Enter the Price of Book : ");
	scanf("%d",&book->price);
	scanf("%c",&chr);
		
	printf("Enter the Summary of book (less than 800 words): ");
	scanf("%[^\n]%*c",book->bookSummary);
		
	printf("Enter About Author (less than 800 words): ");
	scanf("%[^\n]%*c",book->aboutAuthor);
	
//tokenizing the string and creating a fileName 
	char titles[10][50];
	char * token = NULL;
	char delimeter[2] = " ";

	//tokenizing strings
	
	token = strtok(str,delimeter);
	int i = 0;
	while(token != NULL){
		strcpy(titles[i],token);
		token = strtok(NULL,delimeter);
		++i;
	}

	//concatenating the titles into title
	strcpy(str,"");
	for(int j = 0; j < i; ++j){
		strcat(str,titles[j]);
	}
	
	//creating fileName
	char *location = (char*)malloc(sizeof(char)*170);
	strcpy(location,"/home/chetans/Downloads/Book_Recommendation_project/books/newlyAddedBooks/");
	book->fileName = createFileName(location,str);
	
// Storing name of book and address into respective variables.
	newlyAddedBookNames[n2] = (char*)malloc(sizeof(char)*200);
	newlyAddedBookFileNames[n2] = (char*)malloc(sizeof(char)*204);
	strcpy(newlyAddedBookNames[n2],book->bookName);
	strcpy(newlyAddedBookFileNames[n2],book->fileName);
	
// Creating values into text file.
	fbook = fopen(book->fileName,"w");
	if(fbook == NULL){
		printf("FAILED TO CREATE FILE.\n");
		return false;
	}
	
	fprintf(fbook,"%s\n%s\n%s\n%s\n%d\n%d\n%s\n%s\n",book->bookName,book->authorName,book->genre,book->publisherName,book->noOfPages,book->price,book->bookSummary,book->aboutAuthor);
	printf("\nENTER ANY KEY TO ENTER MAIN MENU\n");
	scanf("%c",&chr);
	system("clear");
	return true;
}

// Prints the book stored in the 2D character array
void listBooks(char** bookNames){
	int n = noOfValuesInVar(bookNames);
	printf("\n______________ THE BOOKS IN OUR LIBRARY ARE _____________\n\n");
	sleep(1);
        for(int i = 0; i < n; ++i){
                printf(" %2d ||  %s\n",i+1,bookNames[i]);
		sleep(0.5);
        }
	sleep(1);
        printf("_________________________________________________________\n");
	sleep(1);
        printf("\nTHE TOTAL NO. OF BOOKS ARE : %d\n",n);
		printf("\nENTER ANY KEY TO ENTER MAIN MENU\n");
		char c;
		scanf("%c",&c);
		system("clear");
}

// Prints the details about book by reading the text file
void printBook(char *fileName){
	Book *book = (Book*)malloc(sizeof(Book));
	FILE*fbook = fopen(fileName,"r");
// Handle file creation
	if(fbook){
	}
// Opening the book file.
	fseek(fbook,0,SEEK_SET);
	
	if(fbook == NULL){
		printf("Falied to open FILE\n");
		exit(0);
	}else{
		fscanf(fbook,"%[^\n]%*c\n%[^\n]%*c\n%[^\n]%*c\n%[^\n]%*c\n%d\n%d\n%[^\n]%*c\n%[^\n]%*c\n",book->bookName,book->authorName,book->genre,book->publisherName,&book->noOfPages,&book->price,book->bookSummary,book->aboutAuthor);
		printf("\n_________________________ ABOUT THE BOOK ________________________\n");	
		sleep(1);
		printf("\nBOOK NAME      :-  %s\n",book->bookName);
		sleep(1);
		printf("AUTHOR NAME    :-  %s\n",book->authorName);
		sleep(1);
		printf("GENRE OF BOOK  :-  %s\n",book->genre);
		sleep(1);
		printf("PUBLISHER NAME :-  %s\n",book->publisherName);
		sleep(1);
		printf("NO. OF PAGES   :-  %d\n",book->noOfPages);
		sleep(1);
		printf("PRICE          :-  %d\n",book->price);
		sleep(1);
		printf("BOOK SUMMARY   :- \n\t\t   ");
	
		char c;
		for(int i = 0; i < strlen(book->bookSummary);++i){
			c = book->bookSummary[i];
			if(i % 45 == 0 && i != 0){
				printf("%c\n\t\t  ",c);
			}else{
				printf("%c",c);
			}
		}
		sleep(1);
		printf("\n\nABOUT AUTHOR   :-  \n\t\t   ");
		for(int i = 0; i < strlen(book->aboutAuthor);++i){
			c = book->aboutAuthor[i];
			if(i % 45 == 0 && i != 0){
				printf("%c\n\t\t  ",c);
			}else{
				printf("%c",c);
			}
		}
		printf("\n__________________________________________________________________\n");
		printf("\nENTER ANY KEY TO ENTER MAIN MENU\n");
		scanf("%c",&c);
		sleep(1);
	}
}

// Driver for the program.
int main(void){
//Temporary Variables
	char *location = malloc(sizeof(char)*160);
	char *name = malloc(sizeof(char)*160);
	FILE* fbook;

	
//Creating filename for selfHelpBooks.txt and selfHelpBooksAddress.txt
	char *selfHelpBooksFileName = (char*)malloc(sizeof(char)*205);
	strcpy(location,"/home/chetans/Downloads/Book_Recommendation_project/books/selfHelpBooks/"); // location of the file
	strcpy(name,"selfHelpBooks"); //name of text file
	selfHelpBooksFileName = createFileName(location,name);
	
	char *selfHelpBooksAddressFileName = (char*)malloc(sizeof(char)*205); 
	strcpy(location,"/home/chetans/Downloads/Book_Recommendation_project/books/selfHelpBooks/"); // location of the file
	strcpy(name,"selfHelpBooksAddress"); //name of text file.
	selfHelpBooksAddressFileName = createFileName(location,name);
	
//Creating filename for newlyAddedBooks.txt and newlyAddedAddress.txt
	char *newlyAddedBooksFileName = (char*)malloc(sizeof(char)*200);
	strcpy(location,"/home/chetans/Downloads/Book_Recommendation_project/books/newlyAddedBooks/");// location of the file
	strcpy(name,"newlyAddedBooks"); //name of text file
	newlyAddedBooksFileName = createFileName(location,name);
	
	char *newlyAddedAddressFileName = (char*)malloc(sizeof(char)*200);
	strcpy(location,"/home/chetans/Downloads/Book_Recommendation_project/books/newlyAddedBooks/");// location of the file
	strcpy(name,"newlyAddedAddress"); //name of text file.
	newlyAddedAddressFileName = createFileName(location,name);
	
//Create fileNames for feedback.txt and sugggestions.txt .
	char *feedbacksFileName = (char*)malloc(sizeof(char)*204);
	strcpy(location,"/home/chetans/Downloads/Book_Recommendation_project/books/");// location of the file
	strcpy(name,"feedbacks");//name of text file
	feedbacksFileName = createFileName(location,name);
	
	char *requestsFileName = (char*)malloc(sizeof(char)*204);
	strcpy(location,"/home/chetans/Downloads/Book_Recommendation_project/books/");// location of the file
	strcpy(name,"requests");//name of text file
	requestsFileName = createFileName(location,name);
	
//Creating and assigning memory to varibles to store bookNames and address
	char **selfHelpBookNames;
	char **selfHelpBookFileNames;
	
	selfHelpBookNames = (char**)malloc(sizeof(char*)*MAX_CAPACITY);
	for(int i = 0; i < MAX_CAPACITY; ++i)
		selfHelpBookNames[i] = NULL;

	selfHelpBookFileNames = (char**)malloc(sizeof(char*)*MAX_CAPACITY);
        for(int i = 0; i < MAX_CAPACITY; ++i)
                selfHelpBookFileNames[i] = NULL;

//Creating and assigning memory to  variables to store newly added books name and address.
	char **newlyAddedBookNames;
	char **newlyAddedFileNames;
	
	newlyAddedBookNames = (char**)malloc(sizeof(char*)*MAX_CAPACITY);
	for(int i = 0; i < MAX_CAPACITY; ++i)
		newlyAddedBookNames[i] = NULL;
		
	newlyAddedFileNames = (char**)malloc(sizeof(char*)*MAX_CAPACITY);
	for(int i = 0; i < MAX_CAPACITY; ++i)
		newlyAddedFileNames[i] = NULL;
	
//loading selfHelp books.
	load(selfHelpBookNames,selfHelpBooksFileName);
	load(selfHelpBookFileNames,selfHelpBooksAddressFileName);
	
//loading newlyAddedBooks
	load(newlyAddedBookNames,newlyAddedBooksFileName);
	load(newlyAddedFileNames,newlyAddedAddressFileName);

	
	printf("LOADING THE BOOKS AND FILES ...\n");
	sleep(2);

	system("clear");
	
//INDEX FOR THE PROGRAM
	int choice = 0;	
	do{

		printf("\n**********	BOOK RECOMMENDATION PORTAL	**********\n");
		printf("----------------------------------------------------------\n");
	
lab1 :	printf("SELECT TYPE OF BOOKS \n");
		sleep(1);
		printf("\t1. ACADEMICS\n\t2. SELF-HELP BOOKS\n\t3. NOVELS\n\t4. AUTO BIOGRAPHY\n\t5. BIOGRAPHY\n\nFEEL FREE TO CHECK OUT THESE OPTIONS ALSO ..\n\t6. REQUEST FOR A BOOK\n\t7. ADD BOOK\n\t8. FEEDBACK\n\t9. LIST ALL BOOKS\n\t0. EXIT\n----->> ");
		scanf("%d",&choice);
		printf("\n");
		int choice1,choice2,choice3;
		char c,bookName[100],str[200];
		bool found = false;
		switch(choice){
			case 0:
				goto lab3;
			case 1:
				sleep(1);
				printf("Coming Soon ........\n");
				break;
lab2:			case 2:
				sleep(1);
				printf("\t1. FIND BOOKS BY ENTERING NAME.\n\t2. CHECKOUT OUR RECOMMENDEDATIONS BY SELECTING KEYWORDS.\n\t3. BACK TO MAIN MENU.\n----->> ");
				scanf("%d",&choice1);
				printf("\n");
				if(choice1 == 1){
					scanf("%c",&c);
					printf("ENTER THE NAME OF BOOK : ");
					scanf("%[^\n]%*c",bookName);

					for(int i = 0; i < noOfValuesInVar(selfHelpBookNames); ++i){
						if(strcmp(selfHelpBookNames[i],bookName) == 0){
							found = true;
							printBook(selfHelpBookFileNames[i]);
						}
					}
					if(!found)
						printf("SORRY.... BOOK IS NOT AVAILABLE\n");
							
				}else if(choice1 == 2){
					printf("\n\t1.HAPPINESS AND PEACE\n\t2.FINANCE\n\t3.SOCIALIZING\n\t4.FOCUS\n\t5.HABITS\n\t6.BACK TO LAST MENU\n->");
					scanf("%d",&choice2);
					printf("\n");
					switch(choice2){
						case 1:
							printf("SELECT FROM AVAILABLE BOOKS :\n\t1.THE SUBTLE ART OF NOT GIVING A FUCK\n\t2.THE ALCHEMIST\n--->> ");
							scanf("%d",&choice3);

							if(choice3 == 1)
								printBook(selfHelpBookFileNames[0]);
							else	//check for error input
								printBook(selfHelpBookFileNames[1]);

							break;
						case 2:
							printf("SELECT FROM AVAILABLE BOOKS :\n\t1.RICH DAD POOR DAD\n\t2.RICHEST MAN IN BABYLON\n--->> ");
							scanf("%d",&choice3);

							if(choice3 == 1)
								printBook(selfHelpBookFileNames[2]);
							else    //check for error input
								printBook(selfHelpBookFileNames[3]);

							break;
						 case 3:
							printf("SELECT FROM AVAILABLE BOOKS :\n\t1.HOW TO WIN FREINDS & INFLUENCE PEOPLE\n\t2.SO GOOD THEY CAN'T IGNORE YOU\n--->> ");
							scanf("%d",&choice3);

							if(choice3 == 1)
								printBook(selfHelpBookFileNames[4]);
							else    //check for error input
								printBook(selfHelpBookFileNames[5]);

							break;
						 case 4:
							printf("SELECT FROM AVAILABLE BOOKS :\n\t1.DEEP WORK\n\t2.THE POWER OF YOUR SUBCONSCIOUS MIND\n--->> ");
							scanf("%d",&choice3);

							if(choice3 == 1)
								printBook(selfHelpBookFileNames[6]);
							else    //check for error input
								printBook(selfHelpBookFileNames[7]);
																
							break;
						 case 5:
							printf("SELECT FROM AVAILABLE BOOKS :\n\t1.ATOMIC HABITS\n\t2.THE 7 HABITS OF HIGHLY EFFECTIVE PEOPLE\n--->> ");
							scanf("%d",&choice3);
							
							if(choice3 == 1)
								printBook(selfHelpBookFileNames[8]);
							else    //check for error input
								printBook(selfHelpBookFileNames[9]);
							
							break;
						case 6:
							goto lab2;
						default:
							printf("BOOKS ADDITION IS IN PROCESS ......\n");
	
					}
				}else{
					goto lab1;
				}

				break;
			case 3:
				sleep(1);
                                printf("Coming Soon ........\n");
                                break;
			case 4:
				sleep(1);
                                printf("Coming Soon ........\n");
                                break;
			case 5:
				sleep(1);
                                printf("Coming Soon ........\n");
                                break;
//need work here
			case 6:
				sleep(1);
				scanf("%c",&c);
                                printf("ENTER THE NAME OF BOOK : ");
				scanf("%[^\n]%*c",bookName);
				fbook = fopen(requestsFileName,"a");
				add(bookName,fbook);
				break;
			case 7:
				sleep(1);
				scanf("%c",&c);
				createBook(newlyAddedBookNames,newlyAddedFileNames,selfHelpBookNames);
				break;
//need work here
			case 8:
				sleep(1);
				scanf("%c",&c);
				printf("Enter Your Suggestions / Feedback : ");
				scanf("%[^\n]%*c",str);
				fbook = fopen(feedbacksFileName,"a");
				add(str,fbook);
				break;
			case 9:
				scanf("%c",&c);
				listBooks(selfHelpBookNames);
				break;
		}
	}while(true);
	
	lab3 : printf("\nSaving the Changes Made ...");
	save(newlyAddedBookNames,newlyAddedBooksFileName);
	save(newlyAddedFileNames,newlyAddedAddressFileName);
	
	printf("\nSaving the Book Names ...\n");
	sleep(1);
	printf("Saving the Address of Books ...\n");
	sleep(1);
	printf("Saving the Feedbacks and Requests ...\n\n");
	sleep(1);

	return 0;
}
