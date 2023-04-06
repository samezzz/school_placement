Program Name: How Can You Fail Portal

Program Description: This is a command line application that allows students to check their results and determine which schools they are eligible for based on their aggregate score. The program takes input from the user in the form of their first name, last name and index number, then searches for the student in a CSV file. If the student is found, the program calculates their aggregate score and determines which schools they are eligible for by comparing their score to the cutoff scores of each school. The program then displays a congratulations message if the student is eligible for a school, and an appropriate message if they are not.

Function Definitions:

int search_student(char *filename, char*first_name, char *last_name, int index_number): This function searches for a student in a CSV file by their first name, last name, and index number. It returns 1 if the student is found, and 0 if they are not found.
char*get_school(char *filename, char*first_name, char *last_name, int index_number, int aggregate): This function takes the filename of a CSV file containing school data, the first name, last name, index number, and aggregate score of a student, and returns the name of the school the student is eligible for.

int get_aggregate(char*filename, char *first_name, char*last_name, int index_number): This function takes the filename of a CSV file containing student data, the first name, last name, and index number of a student, and calculates and returns the student's aggregate score.

char *get_course(char*filename, char *first_name, char*last_name, int index_number): This function takes the filename of a CSV file containing student data, the first name, last name, and index number of a student, and returns the course the student applied for.

int compare_cutoff_for_FCS(char *filename, char*first_choice, int aggregate, char *course): This function takes the filename of a CSV file containing cutoff scores for a particular school, the name of the school, the student's aggregate score, and the course they applied for. It returns 1 if the student is eligible for the school, and 0 if they are not eligible.

int compare_cutoff_for_SCS(char*filename, char *second_choice, int aggregate, char*course): This function is similar to compare_cutoff_for_FCS, but it checks the cutoff scores for the student's second choice school.

int compare_cutoff_for_TCS(char *filename, char*third_choice, int aggregate, char *course): This function is similar to compare_cutoff_for_FCS, but it checks the cutoff scores for the student's third choice school.

int compare_cutoff_for_FoCS(char*filename, char *fourth_choice, int aggregate, char*course): This function is similar to compare_cutoff_for_FCS, but it checks the cutoff scores for the student's fourth choice school.

void congratulations(): This function displays a congratulations message if the student is eligible for a school.

void progressBar(int progress, int total, int barWidth): This function displays a progress bar during the processing of school data.

Global Constants:
MAX_LINE_LENGTH: The maximum number of characters allowed in a line of a CSV file.
RED, GRN, YEL, BLU, MAG, CYN, WHT, RESET: These constants are used to change the color of text in the console output.

Global Variables:
students, fcs, scs, tcs, focs: These variables

GROUP MEMBERS
Joel Larbi Asare - 7080121
Erica Afriyie Anti- 7079721
Henry Tutu Adjei - 7078521
Derek Yendoh - 7085021
Samuel Essilfie - 7082021
Michael Dennis Ankomah - 7079521
Magdalene Akua Aseda Obeng Baah - 7083521
