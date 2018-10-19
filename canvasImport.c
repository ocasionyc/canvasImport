// Change 1
/* ....... */
/* ........ */
//
//

/* Carlos  and Jim */

/************************************************************************************/
/*            																		*/
/*	Developers: 	Carlos J. Ocasio & Jim Brubaker									*/
/*																					*/
/*	Date: 			December 2, 2017												*/
/*																					*/
/*	Desription: 	Program which allows an end user to select a Blacbaud export 	*/
/* 					fileto convert into an acceptable Canvas import file that is	*/
/*					used to populate courses, sections, faculty enrollments, new	*/ 
/*					students, new parents and observers.							*/
/*																					*/
/************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define source 0
#define destination 1
#define TRUE 1
#define FALSE 0


/* Prototypes */
void printHeader();
void menu();
void menuSelection();
void askForFiles(int menuChoice);
void checkFileExist(char *file);
void sectionsCSV(char *file);
void coursesCSV(char *file);
void createNewParent();
void addParentObservers();
void facultyEnrollmentsCSV();
/* End of Prototypes */


/* Declarations of variables and structs  */
int whichFile=source;
int error=0;
int invalidChoice=TRUE;
int invalidChoiceFlag=FALSE;
char sourceFile[50];
char destinationFile[50];
char courseDestinationFile[50];
char sectionDestinationFile[50];
char facultyEnrollmentDestinationFile[50];
char tempCourseDestinationFile[200];
char choice;
FILE *file_ptr;

struct parent {
	char fname[50];
	char lname[50];
	char email[100];
};

struct observer {
	char observerID[50];
	char studentID[6];
};
/* End of Declarations of variables and structs */


/* Entry point for Friends Select School Blackbaud / Canvas Import-Export Program */
int main()
{
	system("clear");
	menu();

	system ("clear");
	printf("\n Friends Select School - Canvas Import Menu\n");
	printf("--------------------------------------------\n\n");
	printf("CONGRATULATIONS !!!\n\n");
	printf("You can now import the following files into Canvas:\n\n");
	printf("Course Import File: %s\n",courseDestinationFile);
	printf("Section Import File: %s\n",sectionDestinationFile);
	printf("Faculty Enrollment Import File: %s\n\n\n\n",facultyEnrollmentDestinationFile);
	
	return 0;
}
/* End of main function */


/************************************************************************************/
/*            																		*/
/*	Function: 		Menu															*/
/*																					*/
/*	Desription: 	Provides the end user with a menu system so that they can 	 	*/
/* 					select the type of Blackbaud export files that needs to be		*/
/*					converted into an acceptable Canvas import file.				*/
/*																					*/
/*	Parameters:		None															*/
/*																					*/
/************************************************************************************/
void menu(){
	while (invalidChoice==TRUE) {

		/* Presents the Menu System to the end user */
		system("clear");
		printf("\n Friends Select School - Canvas Import Menu\n");
		printf("--------------------------------------------\n\n");
		printf("Please select Canvas Imports to create: \n\n");
		printf("1. Courses, Sections and Faculty Enrollments\n");
		printf("2. New Parents and Parent Observers\n");
		printf("3. New Students and Course Enrollments\n");
		printf("4. Blackbaud / Canvas Import Documentation\n");
		printf("5. Exit Program\n");
	

		/* Determines if an invalid choice has been selected */
		if (invalidChoiceFlag==TRUE) {
			printf("\nInvalid Choice. Try Again! \n");
			printf("\nSelect choice (1-5): ");
			scanf("%c",&choice);
		} else 
		{
			printf("\nSelect choice (1-5): ");
			scanf("%c",&choice);
		}


		/* Determines which choice has been selected and calls the appropriate functions */
		if (choice=='1') {
			invalidChoice=FALSE;
			invalidChoiceFlag=FALSE;
			askForFiles(1);
			coursesCSV(sourceFile);
			sectionsCSV(courseDestinationFile);
			// facultyEnrollmentsCSV(courseDestinationFile);
			facultyEnrollmentsCSV();
		} else

		if (choice=='2') {
			invalidChoice=FALSE;
			invalidChoiceFlag=FALSE;
			printf("\nNew Parents and Parent Observers code not yet finished!\n\n");
		} else

		if (choice=='3') {
			invalidChoice=FALSE;
			invalidChoiceFlag=FALSE;
			printf("\nNew Students and Course Enrollments code not yet finished!\n\n");
		}

		if (choice=='4') {
			invalidChoice=FALSE;
			invalidChoiceFlag=FALSE;
			printf("\nBlackbaud / Canvas Import Documentation not yet finished!\n\n");
		}

		if (choice=='5') { 
			invalidChoice=FALSE;
			invalidChoiceFlag=FALSE;		
			printf("\nYou have now exited the program! \n\n\n\n");
		} else
			invalidChoiceFlag=TRUE;
	}
}


/************************************************************************************/
/*            																		*/
/*	Function: 		askForFiles														*/
/*																					*/
/*	Desription: 	Prompts the end user to enter the Blackbaud export file, as 	*/
/* 					well as entering the file names for each Canvas import file		*/
/*					that the system will create.									*/
/*																					*/
/*	Parameters:		None															*/
/*																					*/
/************************************************************************************/
void askForFiles(int menuChoice){
	printf("\nEnter the name of the source file: ");
	scanf("%49s",sourceFile);
	checkFileExist(sourceFile);

	if (menuChoice==1) {
		if (whichFile==destination) 
			{
				printf("\nEnter a filename to save the Course CSV file: ");
				scanf("%49s",courseDestinationFile);
				// printf("\n");
				printf("\nEnter a filename to save the Section CSV file: ");
				scanf("%49s",sectionDestinationFile);
				// printf("\n");
				printf("\nEnter a filename to save the Faculty Enrollment CSV file: ");
				scanf("%49s",facultyEnrollmentDestinationFile);
			}
		}
	else if (menuChoice==4) {
				printf("\nEnter the name of the Faculty Enrollment CSV file: ");
				scanf("%49s",destinationFile);
				printf("\n");
	}


	printf("\n\n");
}


/************************************************************************************/
/*            																		*/
/*	Function: 		coursesCSV														*/
/*																					*/
/*	Desription: 	Prompts the end user to enter the Blackbaud export file, as 	*/
/* 					well as entering the file names for each Canvas import file		*/
/*					that the system will create.									*/
/*																					*/
/*	Parameters:		None															*/
/*																					*/
/************************************************************************************/
void coursesCSV(char sourceFile[])
{
	char *sourceFile_ptr=sourceFile;
	char *destinationFile_ptr=courseDestinationFile;


	/* Create new file with filename specified by user, and insert the column names required */
	file_ptr=fopen(courseDestinationFile,"w");														// Opens file in write-enabled mode
	fprintf(file_ptr,"course_id,short_name,long_name,account_id,term_id,status,full_name\n");					// Inserts the column names required
	fclose(file_ptr);																				// Closes the file
	/* End of creating new file */


	/* Create Strings consisting of AWK and SED commands (not complete statements since filenames must be appended) */
	char append[100] =" >> ";
	char extractColumnsFromOriginalExport[200]="awk -v RS=\'\\r?\\n\' -F \",\" '{print $1\"_2018-19,\"$2\",\"$7\",\"$3\",FullYear1819\"\",active\"\",\"$5}' ";
	// char extractColumnsFromOriginalExport[200]="awk -v RS=\'\\r?\\n\' -F \",\" '{print $1\"_2018-19,\"$2\",\"$7\",\"$3\",Fall2018-19\"\",active\"\",\"$5}' ";
	
	// char extractColumnsFromOriginalExport[200]="awk -v RS=\'\\r?\\n\' -F \",\" '{print $1\"_2018-19,\"$1\"_2018-19,\"\",\"$7\",\"$3\",Fall2018-19\"\",active\"}' ";
	

	char removeOriginalColumns[300]="sed -i ' ' '2d' ";
	char removeQuotes[200]="sed -i ' ' 's/\"//g' ";
	char convertDepttoAcctID[350]="awk -F \",\" -v OFS=\",\" '$4==\"Study\"{$4=\"a300\"} $4==\"Math\"{$4=\"a310\"} $4==\"English\"{$4=\"a311\"} $4==\"History\"{$4=\"a312\"} $4==\"Science\"{$4=\"a313\"} $4==\"World Language\"{$4=\"a314\"} $4==\"Physical Education\"{$4=\"a318\"} $4==\"Visual Art\"{$4=\"a315\"} $4==\"Performing Art\"{$4=\"a316\"} $4==\"Religious Thought\"{$4=\"a317\"}1 ' ";
	char copyTemptoDestinationFile[200]="cp temp.csv ";
	char removeLastLine[200]="sed -i ' ' \'$d\' ";
	char removeBlankLines[200]="sed -i ' ' '/^\\s*$/d' ";
	

	// strcpy (tempCourseDestinationFile,destinationFile_ptr);

	char removeLastColumn[200]="awk -F \",\" '{print $1\",\"$2\",\"$3\",\"$4\",\"$5\",\"$6}' ";
	/* End of creating AWK and SED command strings */



	/* Concatenate source and destination filenames to AWK and SED command strings */
	strcat(append,destinationFile_ptr);														// 
	strcat(extractColumnsFromOriginalExport,sourceFile_ptr);								//
	strcat(extractColumnsFromOriginalExport,append);										//
	strcat(removeOriginalColumns,destinationFile_ptr);										//
	strcat(removeQuotes,destinationFile_ptr);												//
	strcat(convertDepttoAcctID,destinationFile_ptr);										//
	strcat(convertDepttoAcctID," > temp.csv ");												//
 	
 	strcat(copyTemptoDestinationFile, destinationFile_ptr);									//
 	strcat(removeLastLine, destinationFile_ptr);											//
 	strcat(removeBlankLines, destinationFile_ptr);	
 	strcat(removeLastLine, " temp.csv");													//
 	strcat(removeBlankLines, " temp.csv");													//
 	strcat(removeLastColumn, " temp.csv");
 	strcat(removeLastColumn, " > ");
 	strcat(removeLastColumn, destinationFile_ptr);
 	/* End of concatenation of source and destination filenames to strings */

// convertDepttoAcctID[strlen(convertDepttoAcctID)-1]=0;


 	/* Execute AWK and SED commands */
	system(extractColumnsFromOriginalExport);												// Necessary to extract exact columns needed for Canvas import file
	system(removeOriginalColumns);															// Necessary to remove original columns headers now located on row 2
	system(removeQuotes);																	// Necessary to remove quotes from records to allow manipulation of data
	system(convertDepttoAcctID);															// Necessary to convert Department Names to Account IDs
	system(copyTemptoDestinationFile);														// Necessary to allow manipulation of data on Temp to save to Destination file
	system(removeLastLine);																	// Necessary to remove junk data at end of CSV file
	system(removeBlankLines);																// Necessary to remove alternating blank lines from CSV file
	system(removeLastColumn);
	/* End of execution of AWK and SED commands */

}


/************************************************************************************/
/*            																		*/
/*	Function: 		sectionsCSV														*/
/*																					*/
/*	Desription: 	Prompts the end user to enter the Blackbaud export file, as 	*/
/* 					well as entering the file names for each Canvas import file		*/
/*					that the system will create.									*/
/*																					*/
/*	Parameters:		None															*/
/*																					*/
/************************************************************************************/
// void addSections(char sourceFile[])
void sectionsCSV(char sourceFile[])
{

	char *sourceFile_ptr=sourceFile;
	char *destinationFile_ptr=sectionDestinationFile;


	/* Create new file with filename specified by user, and insert the column names required */
	file_ptr=fopen(sectionDestinationFile,"w");
	fprintf(file_ptr,"section_id,course_id,name,status\n");
	fclose(file_ptr);
	/* End of creating new file */

	
	/* Create Strings consisting of AWK and SED commands */
	char output[100] =" >> ";
	// char string1[100]="awk -F \",\" '{print $1\",\" $2\",\" $3\",\"\"active\"}' ";
	char string1[100]="awk -F \",\" '{print $1\",\" $1\",\" $3\",\"\"active\"}' ";
	char string2[100]="sed -i ' ' '2d' ";
 	/* End of concatenation of source and destination filenames to strings */


	/* Concatenate Strings to form command statements */
	strcat(output,destinationFile_ptr);
	strcat(string1,sourceFile_ptr);
	strcat(string1,output);
	strcat(string2,destinationFile_ptr);
 	/* End of concatenation of source and destination filenames to strings */


 	/* Execute AWK and SED commands */
	system(string1);
	system(string2);
	/* End of execution of AWK and SED commands */

}


/************************************************************************************/
/*            																		*/
/*	Function: 		facultyEnrollmentsCSV											*/
/*																					*/
/*	Desription: 	Prompts the end user to enter the Blackbaud export file, as 	*/
/* 					well as entering the file names for each Canvas import file		*/
/*					that the system will create.									*/
/*																					*/
/*	Parameters:		None															*/
/*																					*/
/************************************************************************************/
void facultyEnrollmentsCSV()
{

	char *sourceFile_ptr=sourceFile;
	char *destinationFile_ptr=facultyEnrollmentDestinationFile;

	/* Create new file with filename specified by user, and insert the column names required */
	file_ptr=fopen(facultyEnrollmentDestinationFile,"w");
	fprintf(file_ptr,"course_id,user_id,role,section_id,status\n");
	fclose(file_ptr);
	/* End of creating new file */


	if (error==0) {
		char output[100] =" > ";
		char tempFile[100]=" temp.csv ";


		/* Create Strings consisting of AWK and SED commands (not complete statements since filenames must be appended) */
		char append[100] =" >> ";
		char extractColumnsFromOriginalExport[200]="awk -F \",\" '{print $1\",\"$7\",teacher\"\",\"$1\",\"\"active\"}' ";
		char removeOriginalColumns[300]="sed -i ' ' '2d' ";
		char removeQuotes[200]="sed -i ' ' 's/\"//g' ";
		char removeLastLine[200]="sed -i ' ' \'$d\' ";
		char removeBlankLines[200]="sed -i ' ' '/^\\s*$/d' ";
		/* End of creating AWK and SED command strings */


		/* Concatenate Strings to form command statements */
		strcat(append,destinationFile_ptr);
		// strcat(output,destinationFile_ptr);
		strcat(extractColumnsFromOriginalExport, tempFile);
		strcat(extractColumnsFromOriginalExport, append);
		strcat(removeOriginalColumns,destinationFile_ptr);
		strcat(removeQuotes,destinationFile_ptr);
		strcat(removeLastLine, destinationFile_ptr);
		strcat(removeBlankLines, destinationFile_ptr);
	 	/* End of concatenation of source and destination filenames to strings */


	 	/* Execute AWK and SED commands */
		system(output);
		system(extractColumnsFromOriginalExport);
		system(removeOriginalColumns);
		system(removeQuotes);
		system(removeLastLine);
		system(removeBlankLines);
		/* End of execution of AWK and SED commands */


		checkFileExist(facultyEnrollmentDestinationFile);

	}
}


/************************************************************************************/
/*            																		*/
/*	Function: 		checkFileExist													*/
/*																					*/
/*	Desription: 	Prompts the end user to enter the Blackbaud export file, as 	*/
/* 					well as entering the file names for each Canvas import file		*/
/*					that the system will create.									*/
/*																					*/
/*	Parameters:		None															*/
/*																					*/
/************************************************************************************/
void checkFileExist(char *file)
{
	file_ptr=fopen(file,"r");
	if (file_ptr==NULL) 
	{
		if (whichFile==source)
		{
			system("clear");
			printf("The file %s does not exist.\n\n",file);
			error=1;
		}
		else if (whichFile==destination)
		{
			system("clear");
			printf("You do not have permissions to create the file.\n");
			printf("Please use SUDO, or select a path which you have rights to save to.\n\n");
			error=1;
		}
	} else
			whichFile=destination; 
}


/************************************************************************************/
/*            																		*/
/*	Function: 		addParentObservers												*/
/*																					*/
/*	Desription: 	Prompts the end user to enter the Blackbaud export file, as 	*/
/* 					well as entering the file names for each Canvas import file		*/
/*					that the system will create.									*/
/*																					*/
/*	Parameters:		None															*/
/*																					*/
/************************************************************************************/
void addParentObservers()
{	
	int numObservers=0, i=0;
	system("clear");
	printf("ADD PARENT OBSERVERS\n");
	printf("---------------------------------\n\n");
	printf("Parents must ALREADY EXIST within Canvas to make\n");
	printf("them observers of their children. If the parent\n");
	printf("do not yet exist, please select Option 7 to create\n");
	printf("new parents accounts first.\n\n");
	printf("Enter how many OBSERVERS you would like to add: ");
	scanf("%i",&numObservers);
	if (numObservers>0) 
	{
		printf("\nEnter the name of the destination file: ");
		scanf("%s",destinationFile);
	
	struct observer newObserver[numObservers];
	for (i=0; i<numObservers; i++)
	{
		printf("\n\nOBSERVER %i\n",i+1);
		printf("---------------------------------\n");
		printf("\nEnter Observer ID (email address): ");
		scanf("%s",newObserver[i].observerID);

		printf("\nEnter the Student ID (child's ID): ");
		scanf("%s",newObserver[i].studentID);	
	}

	printf("\n\n");
	i=0;

	file_ptr=fopen(destinationFile,"w");
	fprintf(file_ptr,"observer_id, student_id, status\n");

	for (i=0; i<numObservers; i++)
	{
		fprintf(file_ptr,"%s, %s, %s\n",newObserver[i].observerID, newObserver[i].studentID, "active");
	}
		fclose(file_ptr);
	}
	printf("\n\nExiting Program\n\n");
}


/************************************************************************************/
/*            																		*/
/*	Function: 		createNewParent													*/
/*																					*/
/*	Desription: 	Prompts the end user to enter the Blackbaud export file, as 	*/
/* 					well as entering the file names for each Canvas import file		*/
/*					that the system will create.									*/
/*																					*/
/*	Parameters:		None															*/
/*																					*/
/************************************************************************************/
void createNewParent()
{

	int numParents=0, i=0;
	system("Clear");
	printf("CREATE NEW PARENTS\n");
	printf("---------------------------------\n\n");
	printf("Enter how many PARENTS you would like to create: ");
	scanf("%i",&numParents);
	printf("\nEnter the name of the destination file: ");
	scanf("%s",destinationFile);

	struct parent newParent[numParents];
	for (i=0; i<numParents; i++)
	// printf("Parent %i\n",i+1);
	{
		printf("\n\nPARENT %i\n",i+1);
		printf("---------------------------------\n");
		printf("\nEnter First Name: ");
		scanf("%s",newParent[i].fname);
		// printf("");

		printf("\nEnter Last Name: ");
		scanf("%s",newParent[i].lname);
		// printf("");

		printf("\nEnter Email Address: ");
		scanf("%s",newParent[i].email);
		// printf("\n");
	}
	printf("\n\n");
	i=0;

	file_ptr=fopen(destinationFile,"w");
	fprintf(file_ptr,"user_id, login_id, email, first_name, last_name, status\n");

	for (i=0; i<numParents; i++)
	{
		fprintf(file_ptr,"%s, %s, %s, %s, %s, %s\n",newParent[i].email, newParent[i].email, newParent[i].email, newParent[i].fname, newParent[i].lname, "active");
	}
		fclose(file_ptr);
}


















// /************************************************************************************/
// /*            																		*/
// /*	Developers: 	Carlos J. Ocasio & Jim Brubaker									*/
// /*																					*/
// /*	Date: 			December 2, 2017												*/
// /*																					*/
// /*	Desription: 	Program which allows an end user to select a Blacbaud export 	*/
// /* 					fileto convert into an acceptable Canvas import file that is	*/
// /*					used to populate courses, sections, faculty enrollments, new	*/ 
// /*					students, new parents and observers.							*/
// /*																					*/
// /************************************************************************************/

// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>
// #define source 0
// #define destination 1
// #define TRUE 1
// #define FALSE 0


// /* Prototypes */
// void printHeader();
// void menu();
// void menuSelection();
// void askForFiles(int menuChoice);
// void checkFileExist(char *file);
// void sectionsCSV(char *file);
// void coursesCSV(char *file);
// void createNewParent();
// void addParentObservers();
// void facultyEnrollmentsCSV(char fileName[]);
// /* End of Prototypes */


// /* Declarations of variables and structs  */
// int whichFile=source;
// int error=0;
// int invalidChoice=TRUE;
// int invalidChoiceFlag=FALSE;
// char sourceFile[50];
// char destinationFile[50];
// char courseDestinationFile[50];
// char sectionDestinationFile[50];
// char facultyEnrollmentDestinationFile[50];
// char choice;
// FILE *file_ptr;

// struct parent {
// 	char fname[50];
// 	char lname[50];
// 	char email[100];
// };

// struct observer {
// 	char observerID[50];
// 	char studentID[6];
// };
// /* End of Declarations of variables and structs */


// /* Entry point for Friends Select School Blackbaud / Canvas Import-Export Program */
// int main()
// {
// 	system("clear");
// 	menu();

// 	system ("clear");
// 	printf("\n Friends Select School - Canvas Import Menu\n");
// 	printf("--------------------------------------------\n\n");
// 	printf("CONGRATULATIONS !!!\n\n");
// 	printf("You can now import the following files into Canvas:\n\n");
// 	printf("Course Import File: %s\n",courseDestinationFile);
// 	printf("Section Import File: %s\n",sectionDestinationFile);
// 	printf("Faculty Enrollment Import File: %s\n\n\n\n",facultyEnrollmentDestinationFile);
	
// 	return 0;
// }
// /* End of main function */


// /************************************************************************************/
// /*            																		*/
// /*	Function: 		Menu															*/
// /*																					*/
// /*	Desription: 	Provides the end user with a menu system so that they can 	 	*/
// /* 					select the type of Blackbaud export files that needs to be		*/
// /*					converted into an acceptable Canvas import file.				*/
// /*																					*/
// /*	Parameters:		None															*/
// /*																					*/
// /************************************************************************************/
// void menu(){
// 	while (invalidChoice==TRUE) {

// 		/* Presents the Menu System to the end user */
// 		system("clear");
// 		printf("\n Friends Select School - Canvas Import Menu\n");
// 		printf("--------------------------------------------\n\n");
// 		printf("Please select Canvas Imports to create: \n\n");
// 		printf("1. Courses, Sections and Faculty Enrollments\n");
// 		printf("2. New Parents and Parent Observers\n");
// 		printf("3. New Students and Course Enrollments\n");
// 		printf("4. Blackbaud / Canvas Import Documentation\n");
// 		printf("5. Exit Program\n");
	

// 		/* Determines if an invalid choice has been selected */
// 		if (invalidChoiceFlag==TRUE) {
// 			printf("\nInvalid Choice. Try Again! \n");
// 			printf("\nSelect choice (1-5): ");
// 			scanf("%c",&choice);
// 		} else 
// 		{
// 			printf("\nSelect choice (1-5): ");
// 			scanf("%c",&choice);
// 		}


// 		/* Determines which choice has been selected and calls the appropriate functions */
// 		if (choice=='1') {
// 			invalidChoice=FALSE;
// 			invalidChoiceFlag=FALSE;
// 			askForFiles(1);
// 			coursesCSV(sourceFile);
// 			sectionsCSV(courseDestinationFile);
// 			facultyEnrollmentsCSV(courseDestinationFile);
// 		} else

// 		if (choice=='2') {
// 			invalidChoice=FALSE;
// 			invalidChoiceFlag=FALSE;
// 			printf("\nNew Parents and Parent Observers code not yet finished!\n\n");
// 		} else

// 		if (choice=='3') {
// 			invalidChoice=FALSE;
// 			invalidChoiceFlag=FALSE;
// 			printf("\nNew Students and Course Enrollments code not yet finished!\n\n");
// 		}

// 		if (choice=='4') {
// 			invalidChoice=FALSE;
// 			invalidChoiceFlag=FALSE;
// 			printf("\nBlackbaud / Canvas Import Documentation not yet finished!\n\n");
// 		}

// 		if (choice=='5') { 
// 			invalidChoice=FALSE;
// 			invalidChoiceFlag=FALSE;		
// 			printf("\nYou have now exited the program! \n\n\n\n");
// 		} else
// 			invalidChoiceFlag=TRUE;
// 	}
// }


// /************************************************************************************/
// /*            																		*/
// /*	Function: 		askForFiles														*/
// /*																					*/
// /*	Desription: 	Prompts the end user to enter the Blackbaud export file, as 	*/
// /* 					well as entering the file names for each Canvas import file		*/
// /*					that the system will create.									*/
// /*																					*/
// /*	Parameters:		None															*/
// /*																					*/
// /************************************************************************************/
// void askForFiles(int menuChoice){
// 	printf("\nEnter the name of the source file: ");
// 	scanf("%49s",sourceFile);
// 	checkFileExist(sourceFile);

// 	if (menuChoice==1) {
// 		if (whichFile==destination) 
// 			{
// 				printf("\nEnter a filename to save the Course CSV file: ");
// 				scanf("%49s",courseDestinationFile);
// 				// printf("\n");
// 				printf("\nEnter a filename to save the Section CSV file: ");
// 				scanf("%49s",sectionDestinationFile);
// 				// printf("\n");
// 				printf("\nEnter a filename to save the Faculty Enrollment CSV file: ");
// 				scanf("%49s",facultyEnrollmentDestinationFile);
// 			}
// 		}
// 	else if (menuChoice==4) {
// 				printf("\nEnter the name of the Faculty Enrollment CSV file: ");
// 				scanf("%49s",destinationFile);
// 				printf("\n");
// 	}


// 	printf("\n\n");
// }


// /************************************************************************************/
// /*            																		*/
// /*	Function: 		coursesCSV														*/
// /*																					*/
// /*	Desription: 	Prompts the end user to enter the Blackbaud export file, as 	*/
// /* 					well as entering the file names for each Canvas import file		*/
// /*					that the system will create.									*/
// /*																					*/
// /*	Parameters:		None															*/
// /*																					*/
// /************************************************************************************/
// void coursesCSV(char sourceFile[])
// {
// 	char *sourceFile_ptr=sourceFile;
// 	char *destinationFile_ptr=courseDestinationFile;


// 	/* Create new file with filename specified by user, and insert the column names required */
// 	file_ptr=fopen(courseDestinationFile,"w");														// Opens file in write-enabled mode
// 	fprintf(file_ptr,"course_id,short_name,long_name,account_id,term_id,status\n");					// Inserts the column names required
// 	fclose(file_ptr);																				// Closes the file
// 	/* End of creating new file */


// 	/* Create Strings consisting of AWK and SED commands (not complete statements since filenames must be appended) */
// 	char append[100] =" >> ";
// 	char extractColumnsFromOriginalExport[200]="awk -v RS=\'\\r?\\n\' -F \",\" '{print $1\"_2017-18,\"$2\",\"$7\",\"$3\",Fall2017-18\"\",active\"}' ";
// 	char removeOriginalColumns[300]="sed -i ' ' '2d' ";
// 	char removeQuotes[200]="sed -i ' ' 's/\"//g' ";
// 	char convertDepttoAcctID[350]="awk -F \",\" -v OFS=\",\" '$4==\"Study\"{$4=\"a300\"} $4==\"Math\"{$4=\"a310\"} $4==\"English\"{$4=\"a311\"} $4==\"History\"{$4=\"a312\"} $4==\"Science\"{$4=\"a313\"} $4==\"World Language\"{$4=\"a314\"} $4==\"Physical Education\"{$4=\"a314\"} $4==\"Visual Art\"{$4=\"a315\"} $4==\"Performing Art\"{$4=\"a316\"} $4==\"Religious Thought\"{$4=\"a317\"}1 ' ";

// 	// char convertDepttoAcctID[350]=	"awk -F \",\" -v OFS=\",\"'"
// 	// 								" $4==\"Study\"{$4=\"a300\"} "
// 	// 								" $4==\"Math\"{$4=\"a310\"} "
// 	// 								" $4==\"English\"{$4=\"a311\"} "
// 	// 								" $4==\"History\"{$4=\"a312\"} "
// 	// 								" $4==\"Science\"{$4=\"a313\"} "
// 	// 								" $4==\"World Language\"{$4=\"a314\"} "
// 	// 								" $4==\"Physical Education\"{$4=\"a314\"} "
// 	// 								" $4==\"Visual Art\"{$4=\"a315\"} "
// 	// 								" $4==\"Performing Art\"{$4=\"a316\"} "
// 	// 								" $4==\"Religious Thought\"{$4=\"a317\"}1 ' ";
	
// 	char copyTemptoDestinationFile[200]="mv temp.csv ";
// 	char removeLastLine[200]="sed -i ' ' \'$d\' ";
// 	char removeBlankLines[200]="sed -i ' ' '/^\\s*$/d' ";
// 	/* End of creating AWK and SED command strings */


// 	/* Concatenate source and destination filenames to AWK and SED command strings */
// 	strcat(append,destinationFile_ptr);														// 
// 	strcat(extractColumnsFromOriginalExport,sourceFile_ptr);								//
// 	strcat(extractColumnsFromOriginalExport,append);										//
// 	strcat(removeOriginalColumns,destinationFile_ptr);										//
// 	strcat(removeQuotes,destinationFile_ptr);												//
// 	strcat(convertDepttoAcctID,destinationFile_ptr);										//
// 	strcat(convertDepttoAcctID," > temp.csv ");												//
//  	strcat(copyTemptoDestinationFile, destinationFile_ptr);									//
//  	strcat(removeLastLine, destinationFile_ptr);											//
//  	strcat(removeBlankLines, destinationFile_ptr);											//
//  	/* End of concatenation of source and destination filenames to strings */

// // convertDepttoAcctID[strlen(convertDepttoAcctID)-1]=0;


//  	/* Execute AWK and SED commands */
// 	system(extractColumnsFromOriginalExport);												// Necessary to extract exact columns needed for Canvas import file
// 	system(removeOriginalColumns);															// Necessary to remove original columns headers now located on row 2
// 	system(removeQuotes);																	// Necessary to remove quotes from records to allow manipulation of data
// 	system(convertDepttoAcctID);															// Necessary to convert Department Names to Account IDs
// 	system(copyTemptoDestinationFile);														// Necessary to allow manipulation of data on Temp to save to Destination file
// 	system(removeLastLine);																	// Necessary to remove junk data at end of CSV file
// 	system(removeBlankLines);																// Necessary to remove alternating blank lines from CSV file
// 	/* End of execution of AWK and SED commands */

// }


// /************************************************************************************/
// /*            																		*/
// /*	Function: 		sectionsCSV														*/
// /*																					*/
// /*	Desription: 	Prompts the end user to enter the Blackbaud export file, as 	*/
// /* 					well as entering the file names for each Canvas import file		*/
// /*					that the system will create.									*/
// /*																					*/
// /*	Parameters:		None															*/
// /*																					*/
// /************************************************************************************/
// // void addSections(char sourceFile[])
// void sectionsCSV(char sourceFile[])
// {

// 	char *sourceFile_ptr=sourceFile;
// 	char *destinationFile_ptr=sectionDestinationFile;


// 	/* Create new file with filename specified by user, and insert the column names required */
// 	file_ptr=fopen(sectionDestinationFile,"w");
// 	fprintf(file_ptr,"section_id,course_id,name,status\n");
// 	fclose(file_ptr);
// 	/* End of creating new file */

	
// 	/* Create Strings consisting of AWK and SED commands */
// 	char output[100] =" >> ";
// 	char string1[100]="awk -F \",\" '{print $1\",\" $2\",\" $3\",\"\"active\"}' ";
// 	char string2[100]="sed -i ' ' '2d' ";
//  	/* End of concatenation of source and destination filenames to strings */


// 	/* Concatenate Strings to form command statements */
// 	strcat(output,destinationFile_ptr);
// 	strcat(string1,sourceFile_ptr);
// 	strcat(string1,output);
// 	strcat(string2,destinationFile_ptr);
//  	/* End of concatenation of source and destination filenames to strings */


//  	/* Execute AWK and SED commands */
// 	system(string1);
// 	system(string2);
// 	/* End of execution of AWK and SED commands */

// }


// /************************************************************************************/
// /*            																		*/
// /*	Function: 		facultyEnrollmentsCSV											*/
// /*																					*/
// /*	Desription: 	Prompts the end user to enter the Blackbaud export file, as 	*/
// /* 					well as entering the file names for each Canvas import file		*/
// /*					that the system will create.									*/
// /*																					*/
// /*	Parameters:		None															*/
// /*																					*/
// /************************************************************************************/
// void facultyEnrollmentsCSV(char sourceFile[])
// {

// 	char *sourceFile_ptr=sourceFile;
// 	char *destinationFile_ptr=facultyEnrollmentDestinationFile;

// 	/* Create new file with filename specified by user, and insert the column names required */
// 	file_ptr=fopen(facultyEnrollmentDestinationFile,"w");
// 	fprintf(file_ptr,"course_id,user_id,role,section_id,status\n");
// 	fclose(file_ptr);
// 	/* End of creating new file */


// 	if (error==0) {
// 		char output[100] =" > ";
// 		char testfile[100]=" q.csv ";


// 		/* Create Strings consisting of AWK and SED commands (not complete statements since filenames must be appended) */
// 		char append[100] =" >> ";
// 		char extractColumnsFromOriginalExport[200]="awk -F \",\" '{print $1\",\"$2\",\"\"teacher\"\",\"$1\",\"\"active\"}' ";
// 		char removeOriginalColumns[300]="sed -i ' ' '2d' ";
// 		char removeQuotes[200]="sed -i ' ' 's/\"//g' ";
// 		char removeLastLine[200]="sed -i ' ' \'$d\' ";
// 		char removeBlankLines[200]="sed -i ' ' '/^\\s*$/d' ";
// 		/* End of creating AWK and SED command strings */


// 		/* Concatenate Strings to form command statements */
// 		strcat(append,destinationFile_ptr);
// 		strcat(extractColumnsFromOriginalExport, courseDestinationFile);
// 		strcat(extractColumnsFromOriginalExport, append);
// 		strcat(removeOriginalColumns,destinationFile_ptr);
// 		strcat(removeQuotes,destinationFile_ptr);
// 		strcat(removeLastLine, destinationFile_ptr);
// 		strcat(removeBlankLines, destinationFile_ptr);
// 	 	/* End of concatenation of source and destination filenames to strings */


// 	 	/* Execute AWK and SED commands */
// 		system(output);
// 		system(extractColumnsFromOriginalExport);
// 		system(removeOriginalColumns);
// 		system(removeQuotes);
// 		system(removeLastLine);
// 		system(removeBlankLines);
// 		/* End of execution of AWK and SED commands */


// 		checkFileExist(facultyEnrollmentDestinationFile);

// 	}
// }


// /************************************************************************************/
// /*            																		*/
// /*	Function: 		checkFileExist													*/
// /*																					*/
// /*	Desription: 	Prompts the end user to enter the Blackbaud export file, as 	*/
// /* 					well as entering the file names for each Canvas import file		*/
// /*					that the system will create.									*/
// /*																					*/
// /*	Parameters:		None															*/
// /*																					*/
// /************************************************************************************/
// void checkFileExist(char *file)
// {
// 	file_ptr=fopen(file,"r");
// 	if (file_ptr==NULL) 
// 	{
// 		if (whichFile==source)
// 		{
// 			system("clear");
// 			printf("The file %s does not exist.\n\n",file);
// 			error=1;
// 		}
// 		else if (whichFile==destination)
// 		{
// 			system("clear");
// 			printf("You do not have permissions to create the file.\n");
// 			printf("Please use SUDO, or select a path which you have rights to save to.\n\n");
// 			error=1;
// 		}
// 	} else
// 			whichFile=destination; 
// }


// /************************************************************************************/
// /*            																		*/
// /*	Function: 		addParentObservers												*/
// /*																					*/
// /*	Desription: 	Prompts the end user to enter the Blackbaud export file, as 	*/
// /* 					well as entering the file names for each Canvas import file		*/
// /*					that the system will create.									*/
// /*																					*/
// /*	Parameters:		None															*/
// /*																					*/
// /************************************************************************************/
// void addParentObservers()
// {	
// 	int numObservers=0, i=0;
// 	system("clear");
// 	printf("ADD PARENT OBSERVERS\n");
// 	printf("---------------------------------\n\n");
// 	printf("Parents must ALREADY EXIST within Canvas to make\n");
// 	printf("them observers of their children. If the parent\n");
// 	printf("do not yet exist, please select Option 7 to create\n");
// 	printf("new parents accounts first.\n\n");
// 	printf("Enter how many OBSERVERS you would like to add: ");
// 	scanf("%i",&numObservers);
// 	if (numObservers>0) 
// 	{
// 		printf("\nEnter the name of the destination file: ");
// 		scanf("%s",destinationFile);
	
// 	struct observer newObserver[numObservers];
// 	for (i=0; i<numObservers; i++)
// 	{
// 		printf("\n\nOBSERVER %i\n",i+1);
// 		printf("---------------------------------\n");
// 		printf("\nEnter Observer ID (email address): ");
// 		scanf("%s",newObserver[i].observerID);

// 		printf("\nEnter the Student ID (child's ID): ");
// 		scanf("%s",newObserver[i].studentID);	
// 	}

// 	printf("\n\n");
// 	i=0;

// 	file_ptr=fopen(destinationFile,"w");
// 	fprintf(file_ptr,"observer_id, student_id, status\n");

// 	for (i=0; i<numObservers; i++)
// 	{
// 		fprintf(file_ptr,"%s, %s, %s\n",newObserver[i].observerID, newObserver[i].studentID, "active");
// 	}
// 		fclose(file_ptr);
// 	}
// 	printf("\n\nExiting Program\n\n");
// }


// /************************************************************************************/
// /*            																		*/
// /*	Function: 		createNewParent													*/
// /*																					*/
// /*	Desription: 	Prompts the end user to enter the Blackbaud export file, as 	*/
// /* 					well as entering the file names for each Canvas import file		*/
// /*					that the system will create.									*/
// /*																					*/
// /*	Parameters:		None															*/
// /*																					*/
// /************************************************************************************/
// void createNewParent()
// {

// 	int numParents=0, i=0;
// 	system("Clear");
// 	printf("CREATE NEW PARENTS\n");
// 	printf("---------------------------------\n\n");
// 	printf("Enter how many PARENTS you would like to create: ");
// 	scanf("%i",&numParents);
// 	printf("\nEnter the name of the destination file: ");
// 	scanf("%s",destinationFile);

// 	struct parent newParent[numParents];
// 	for (i=0; i<numParents; i++)
// 	// printf("Parent %i\n",i+1);
// 	{
// 		printf("\n\nPARENT %i\n",i+1);
// 		printf("---------------------------------\n");
// 		printf("\nEnter First Name: ");
// 		scanf("%s",newParent[i].fname);
// 		// printf("");

// 		printf("\nEnter Last Name: ");
// 		scanf("%s",newParent[i].lname);
// 		// printf("");

// 		printf("\nEnter Email Address: ");
// 		scanf("%s",newParent[i].email);
// 		// printf("\n");
// 	}
// 	printf("\n\n");
// 	i=0;

// 	file_ptr=fopen(destinationFile,"w");
// 	fprintf(file_ptr,"user_id, login_id, email, first_name, last_name, status\n");

// 	for (i=0; i<numParents; i++)
// 	{
// 		fprintf(file_ptr,"%s, %s, %s, %s, %s, %s\n",newParent[i].email, newParent[i].email, newParent[i].email, newParent[i].fname, newParent[i].lname, "active");
// 	}
// 		fclose(file_ptr);
// }
