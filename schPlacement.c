#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for usleep()
#include <time.h>
#include <math.h>

#define MAX_LINE_LENGTH 100

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

int search_student(char *filename, char *first_name, char *last_name, int index_number);

char *get_school(char *filename, char *first_name, char *last_name, int index_number, int aggregate);
int get_aggregate(char *filename, char *first_name, char *last_name, int index_number);
char *get_course(char *filename, char *first_name, char *last_name, int index_number);

int compare_cutoff_for_FCS(char *filename, char *first_choice, int aggregate, char *course);
int compare_cutoff_for_SCS(char *filename, char *second_choice, int aggregate, char *course);
int compare_cutoff_for_TCS(char *filename, char *third_choice, int aggregate, char *course);
int compare_cutoff_for_FoCS(char *filename, char *fourth_choice, int aggregate, char *course);

void congratulations();
void progressBar(int progress, int total, int barWidth);

int main()
{
  char students[] = "students.csv";
  char fcs[] = "first_choice_schools.csv";
  char scs[] = "second_choice_schools.csv";
  char tcs[] = "third_choice_schools.csv";
  char focs[] = "fourth_choice_schools.csv";

  char first_name[20], last_name[20];
  int index_number;

  int found1, found2, found3, found4, found5;

    printf("\n\tWELCOME TO HOW CAN YOU FAIL PORTAL :)\nFollow the instructions to check your results\n");
    start:
      printf("\nEnter Your First Name: ");
      scanf("%s", first_name);
      printf("Now Enter Your Last Name: ");
      scanf("%s", last_name);
      printf("Finally Enter Index Number: ");
      scanf("%d", &index_number);

      int i;
      const char *anim = "|/-\\"; // animation sequence
      for (i = 0; i < 20; i++)
      {
        printf("\rTHE MOMENT OF TRUTH... %c", anim[i % 4]);    // print the current character and move the cursor to the beginning of the line
        fflush(stdout);    // flush the output buffer to make sure the characters are displayed immediately
        usleep(100500);   // wait for 100ms
      }

      found1 = search_student(students, first_name, last_name, index_number);

      if (!found1)
      {
        printf("\n\nStudent not found!!!\n");
        goto start;
      }
      else 
      {
        char message[] = "\nNow use this time to think about what you've done\nAre you happy with yourself :(\nDo you even think you'll get a school?\nIf not at least look on the bright side :| Ideal college is happy and always ready to have you :)\n\n";
        int message_length = strlen(message);

        for (int i = 0; i < message_length; i++)
        {
          putchar(message[i]);
          fflush(stdout);
          usleep(50500);
        }

        const int total = 100;
        const int barWidth = 40;

        for (int progress = 0; progress <= total; progress++)
        {
          progressBar(progress, total, barWidth);
          for (i = 0; i < 20; i++)
        {
          printf("\rProcessing School... %c", anim[i % 4]); // print the current character and move the cursor to the beginning of the line
          fflush(stdout);                                   // flush the output buffer to make sure the characters are displayed immediately
          usleep(700);
        }
        }

        int aggregate = get_aggregate(students, first_name, last_name, index_number);
        char *school = get_school(students, first_name, last_name, index_number, aggregate);
        char *course = get_course(students, first_name, last_name, index_number);
        
        congratulations();
        found2 = compare_cutoff_for_FCS(fcs, get_school(students, first_name, last_name, index_number, aggregate), aggregate, course);

        found3 = compare_cutoff_for_SCS(scs, get_school(students, first_name, last_name, index_number, aggregate), aggregate, course);

        found4 = compare_cutoff_for_TCS(tcs, get_school(students, first_name, last_name, index_number, aggregate), aggregate, course);

        found5 = compare_cutoff_for_FoCS(focs, get_school(students, first_name, last_name, index_number, aggregate), aggregate, course);

        printf("\n");
      }

  return 0;
}

int search_student(char *filename, char *first_name, char *last_name, int index_number)
{
  FILE *fp;
  char line[MAX_LINE_LENGTH];
  int found = 0;

  fp = fopen(filename, "r");
  if (fp == NULL)
  {
    printf("Failed to open  file %s\n", filename);
    return -1;
  }

  while (fgets(line, MAX_LINE_LENGTH, fp))
  {
    int cur_index_number;
    char cur_first_name[20], cur_last_name[20];
    int english, core_math, science, social, e_math, physics;
    char first_choice[20], second_choice[20], third_choice[20], fourth_choice[20], course[20];

    sscanf(line, "%d,%[^,],%[^,],%d,%d,%d,%d,%d,%d,%[^,],%[^,],%[^,],%[^,],%[^,]",
          &cur_index_number, cur_first_name, cur_last_name, &english, &core_math,
          &science, &social, &e_math, &physics, course, first_choice, second_choice,
          third_choice, fourth_choice);

    if (cur_index_number == index_number &&
        strcmp(cur_first_name, first_name) == 0 &&
        strcmp(cur_last_name, last_name) == 0)
    {
      printf("\n\n---------PROFILE---------\n");
      printf("\nName: %s %s\nIndex Number: %d\n", cur_first_name, cur_last_name, cur_index_number);
      printf("English         -->   %d\nCore Math       -->   %d\nScience         -->   %d\nSocial          -->   %d\nElective Math   -->   %d\nPhysics         -->   %d\n",
            english, core_math, science, social, e_math, physics);

      int aggregate = english + core_math + science + social + e_math + physics;
      printf("\nAggregate: %d\n", aggregate);
      printf("\nFirst Choice   -  %s\nSecond Choice  -  %s\nThird Choice   -  %s\nFourth Choice  -  %s\n", first_choice, second_choice, third_choice, fourth_choice);
      printf("\n--------------------------\n");

      found = 1;
      break;
    }
  }

  fclose(fp);

  return found;
}

// Function to get first choice of searched student
char *get_school(char *filename, char *first_name, char *last_name, int index_number, int aggregate)
{
  FILE *fp;
  char line[1024];
  char *token;
  char *school = NULL;

  fp = fopen(filename, "r");
  if (fp == NULL)
  {
    printf("Error: Unable to open file %s\n", filename);
    return NULL;
  }

  // Loop through each line of the file
  while (fgets(line, 1024, fp))
  {
    // Parse the line into tokens
    token = strtok(line, ",");
    int i = 0;
    char *record[14];
    while (token != NULL)
    {
      record[i++] = token;
      token = strtok(NULL, ",");
    }

    // Check if this is the correct record
    if (strcmp(record[1], first_name) == 0 &&
        strcmp(record[2], last_name) == 0 &&
        atoi(record[0]) == index_number && aggregate <= 9)
    {
      school = strdup(record[10]);
      break;
    }
    else if (strcmp(record[1], first_name) == 0 &&
            strcmp(record[2], last_name) == 0 &&
            atoi(record[0]) == index_number && 9 < aggregate <= 15)
    {
      school = strdup(record[11]);
      break;
    }
    else if (strcmp(record[1], first_name) == 0 &&
            strcmp(record[2], last_name) == 0 &&
            atoi(record[0]) == index_number && 15 < aggregate <= 20)
    {
      school = strdup(record[12]);
      break;
    }
    else if (strcmp(record[1], first_name) == 0 &&
            strcmp(record[2], last_name) == 0 &&
            atoi(record[0]) == index_number && aggregate > 20)
    {
      school = strdup(record[13]);
      break;
    }
  }

  fclose(fp);
  return school;
}

// Function to get aggregate of searched student
int get_aggregate(char *filename, char *first_name, char *last_name, int index_number)
{
  FILE *file = fopen(filename, "r"); // open file for reading
  if (!file)
  {
    printf("Error: could not open file %s\n", filename);
    return -1; // return -1 to indicate error
  }

  char line[MAX_LINE_LENGTH];
  int total_grades = 0;

  while (fgets(line, sizeof(line), file))
  {
    // parse line into tokens using comma as delimiter
    char *token = strtok(line, ",");
    int current_index_number = atoi(token); // convert token to integer

    // check if current row corresponds to given student
    if (current_index_number == index_number)
    {
      token = strtok(NULL, ",");   // skip first name
      token = strtok(NULL, ",");   // skip last name
      int english = atoi(token);   // skip english grade
      int core_math = atoi(token); // skip core math grade
      int science = atoi(token);   // skip science grade
      int social = atoi(token);    // skip social grade
      int e_math = atoi(token);    // convert token to integer
      int physics = atoi(token);   // skip physics grade

      total_grades = english + core_math + science + social + e_math + physics; // start with e_math grade

      // loop through remaining grades and add them to total
      for (int i = 0; i < 6; i++)
      {
        token = strtok(NULL, ",");
        total_grades += atoi(token); // convert token to integer and add to total
      }

      break; // break out of loop since we found the row we need
    }
  }

  fclose(file); // close file

  return total_grades;
}

// Function to get course of searched student
char *get_course(char *filename, char *first_name, char *last_name, int index_number)
{
  FILE *fp;
  char line[1024];
  char *token;
  char *course = NULL;

  fp = fopen(filename, "r");
  if (fp == NULL)
  {
    printf("Error: Unable to open file %s\n", filename);
    return NULL;
  }

  // Loop through each line of the file
  while (fgets(line, 1024, fp))
  {
    // Parse the line into tokens
    token = strtok(line, ",");
    int i = 0;
    char *record[14];
    while (token != NULL)
    {
      record[i++] = token;
      token = strtok(NULL, ",");
    }

    // Check if this is the correct record
    if (strcmp(record[1], first_name) == 0 &&
        strcmp(record[2], last_name) == 0 &&
        atoi(record[0]) == index_number)
    {
      course = strdup(record[9]);
      break;
    }
  }

  fclose(fp);
  return course;
}


int compare_cutoff_for_FCS(char *filename, char *first_choice, int aggregate, char *course)
{
  FILE *fp;
  char line[MAX_LINE_LENGTH];
  int found = 0;

  fp = fopen(filename, "r");
  if (fp == NULL)
  {
    printf("Failed to open  file %s\n", filename);
    return -1;
  }

  while (fgets(line, MAX_LINE_LENGTH, fp))
  {
    char cur_school[20];
    char cur_course[20];
    int cur_cutoff;

    sscanf(line, "%[^,],%[^,],%d", cur_course, cur_school, &cur_cutoff);

    if (strcmp(cur_school, first_choice) == 0 && strcmp(cur_course, course) == 0)
    {
      if (aggregate <= cur_cutoff)
      {
        printf("\nCongratulations on your admission to %s to offer %s :)\n", cur_school, cur_course, cur_cutoff);
      }
      else 
      {
        printf("\nCongratulations on your admission to %s to offer %s :)\n", cur_school, cur_course, cur_cutoff);
      }
      found = 1;
    }
  }

  fclose(fp);

  return found;
}

int compare_cutoff_for_SCS(char *filename, char *second_choice, int aggregate, char *course)
{
  FILE *fp;
  char line[MAX_LINE_LENGTH];
  int found = 0;

  fp = fopen(filename, "r");
  if (fp == NULL)
  {
    printf("Failed to open  file %s\n", filename);
    return -1;
  }

  while (fgets(line, MAX_LINE_LENGTH, fp))
  {
    char cur_school[20];
    char cur_course[20];
    int cur_cutoff;

    sscanf(line, "%[^,],%[^,],%d", cur_course, cur_school, &cur_cutoff);

    if (strcmp(cur_school, second_choice) == 0 && strcmp(cur_course, course) == 0)
    {
      if (aggregate <= cur_cutoff)
      {
        printf("\nCongratulations on your admission to %s to offer %s :)\n", cur_school, cur_course, cur_cutoff);
      }
      else
      {
        printf("\nCongratulations on your admission to %s to offer %s :)\n", cur_school, cur_course, cur_cutoff);
      }
      
      found = 1;
    }
  }

  fclose(fp);

  return found;
}

int compare_cutoff_for_TCS(char *filename, char *third_choice, int aggregate, char *course)
{
  FILE *fp;
  char line[MAX_LINE_LENGTH];
  int found = 0;

  fp = fopen(filename, "r");
  if (fp == NULL)
  {
    printf("Failed to open  file %s\n", filename);
    return -1;
  }

  while (fgets(line, MAX_LINE_LENGTH, fp))
  {
    char cur_school[20];
    char cur_course[20];
    int cur_cutoff;

    sscanf(line, "%[^,],%[^,],%d", cur_course, cur_school, &cur_cutoff);

    if (strcmp(cur_school, third_choice) == 0 && strcmp(cur_course, course) == 0)
    {
      if (aggregate <= cur_cutoff)
      {
        printf("\nCongratulations on your admission to %s to offer %s :)\n", cur_school, cur_course, cur_cutoff);
      }
      else
      {
        printf("\nCongratulations on your admission to %s to offer %s :)\n", cur_school, cur_course, cur_cutoff);
      }
      found = 1;
    }
  }

  fclose(fp);

  return found;
}

int compare_cutoff_for_FoCS(char *filename, char *fourth_choice, int aggregate, char *course)
{
  FILE *fp;
  char line[MAX_LINE_LENGTH];
  int found = 0;

  fp = fopen(filename, "r");
  if (fp == NULL)
  {
    printf("Failed to open  file %s\n", filename);
    return -1;
  }

  while (fgets(line, MAX_LINE_LENGTH, fp))
  {
    char cur_school[20];
    char cur_course[20];
    int cur_cutoff;

    sscanf(line, "%[^,],%[^,],%d", cur_course, cur_school, &cur_cutoff);

    if (strcmp(cur_school, fourth_choice) == 0 && strcmp(cur_course, course) == 0)
    {
      if (aggregate <= cur_cutoff)
      {
        printf("\nCongratulations on your admission to %s to offer %s :)\n", cur_school, cur_course, cur_cutoff);
      }
      else
      {
        printf("\nCongratulations on your admission to %s to offer %s :)\n", cur_school, cur_course, cur_cutoff);
      }
      found = 1;
    }
  }

  fclose(fp);

  return found;
}

void congratulations()
{
  printf("\n\n");
  printf(RED "C" RESET);
  printf(GRN "O" RESET);
  printf(YEL "N" RESET);
  printf(BLU "G" RESET);
  printf(MAG "R" RESET);
  printf(CYN "A" RESET);
  printf(WHT "T" RESET);
  printf(RED "U" RESET);
  printf(GRN "L" RESET);
  printf(YEL "A" RESET);
  printf(BLU "T" RESET);
  printf(MAG "I" RESET);
  printf(CYN "O" RESET);
  printf(WHT "N" RESET);
  printf(RED "S!!!" RESET "\n");
}


void progressBar(int progress, int total, int barWidth)
{
  int i, j;
  int percentComplete = (int)(((float)progress / (float)total) * 100);
  int progressWidth = (int)(((float)progress / (float)total) * barWidth);

  printf("[");
  for (i = 0; i < progressWidth; i++)
  {
    printf("=");
  }
  for (j = i; j < barWidth; j++)
  {
    printf(" ");
  }
  printf("] %3d%%\r", percentComplete);
  fflush(stdout);
}