/*

    Name: inventory_prob1.c
    Purpose: Represents the storage of car parts in a warehouse
    Author: grivera64
    Date: 04/07/2021

*/

/* Inclusion of header files */
#include <stdio.h>
#include <ctype.h>
#include "readline.h"

/* Macros defining constants within the program */
#define NAME_LEN 25
#define MAX_PARTS 100

/* Structure definition by identifier */
struct part 
{

    //components
    int number;
    char name[NAME_LEN + 1];
    int on_hand;

};

/* Function prototypes/declaration */
int find_part(int number, struct part inventory[], int num_parts);
int insert(struct part inventory[], int num_parts);
void search(struct part inventory[], int num_parts);
void update(struct part inventory[], int num_parts);
void print(struct part inventory[], int num_parts);
void clear_input(void);

/* Beginning of main function */

int main()
{

    //declaration of local variables
    char code;                                                              //represents the code entered by user
    struct part inventory[MAX_PARTS];                                       //represents the number of inventory parts
    int num_parts = 0;                                                      //represents the current number of parts

    //infinitely loop until user chooses to break
    for (;;)
    {

        /* Print the Operation List */
        printf("Select i for inserting a car part in the database\n");
        printf("Select s for searching a car part in the database\n");
        printf("Select u for updating a car part in the database\n");
        printf("Select p for printing a car part in the database\n");
        printf("Select q for quitting\n");

        /* Get user-defined choice */
        printf("Enter your choice: ");
        scanf("%c", &code);

        //make sure character stream is completely cleared
        //before attempting any other request
        clear_input();

        switch (code)
        {

            case 'i': 
                num_parts = insert(inventory, num_parts);
                break;
            case 's':
                search(inventory, num_parts);
                break;
            case 'u':
                update(inventory, num_parts);
                break;
            case 'p':
                print(inventory, num_parts);
                break;
            case 'q':
                return 0;                     //end of program

            default: 
                printf("Illegal choice. Please try again.\n");
                //break here not required

        } //end of switch statement

    } //end of for loop

}

int find_part(int number, struct part inventory[], int num_parts)
{

    int i;
    for (i = 0; i < num_parts; i++)
    {

        if (inventory[i].number == number)
        {

            return i;

        }

    } //end of for

    return -1;

}

int insert(struct part inventory[], int num_parts)
{

    int part_num;

    //Checking the data base capacity
    if (num_parts == MAX_PARTS)
    {

        printf("Database is full. Can't add more parts\n");
        return num_parts;

    }

    //asking for user input
    printf("Enter your part number: ");
    scanf("%d", &part_num);

    //checking database entry for duplication
    if (find_part(part_num, inventory, num_parts) >= 0)
    {
        printf("This part already exists\n");
        return num_parts;
    }

    inventory[num_parts].number = part_num;

    //asking for user input
    printf("Enter your part name: ");
    read_line(inventory[num_parts].name, NAME_LEN);         //we need to define this
    printf("Enter quantity on-hand: ");
    scanf("%d", &inventory[num_parts].on_hand);

    num_parts++;

    clear_input();

    return num_parts;


}

void search(struct part inventory[], int num_parts)
{

    int part_number, i;

    printf("Please enter your part number: ");
    scanf("%d", &part_number);

    i = find_part(part_number, inventory, num_parts);

    if (i >= 0)
    {

        printf("Part name: %s\n", inventory[i].name);
        printf("Quantity On-Hand: %d\n", inventory[i].on_hand);

    }
    else
    {

        printf("Part number not found\n");

    }

    clear_input();



} // end of search

void update(struct part inventory[], int num_parts)
{

    int i, part_number, change;

    printf("Enter part number: ");
    scanf("%d", &part_number);

    i = find_part(part_number, inventory, num_parts);

    if (i >= 0)
    {

        printf("Please enter change in quantity on-hand: ");
        scanf("%d", &change);

        inventory[i].on_hand += change;

    }
    else
    {

        printf("Didn't find part\n");

    }

    clear_input();

}

void print(struct part inventory[], int num_parts)
{

    int i;
    printf("Part number    Part name    On hand\n");
    
    for (i = 0; i < num_parts; i++)
    {

        printf("%-15d%-13s%d\n", inventory[i].number, inventory[i].name, inventory[i].on_hand);

    }

}

void clear_input(void)
{

    while (getchar() != '\n');                  //skip to the end of line

}