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

    //new component
    double price;

};

/* Function prototypes/declaration */
int find_part(int number, struct part inventory[], int num_parts);
int insert(struct part inventory[], int num_parts);
void search(struct part inventory[], int num_parts);
void update(struct part inventory[], int num_parts);
void set_price(struct part inventory[], int num_parts);
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
        printf("Select u for updating a car part quantity in the database\n");
        printf("Select c for updating a car part price in the database\n");
        printf("Select p for printing a car part in the database\n");
        printf("Select q for quitting\n");

        /* Get user-defined choice */
        printf("Enter your choice: ");
        scanf("%c", &code);

        //make sure character stream is completely cleared
        //before attempting any other request
        clear_input();

        /* Check selected operation and execute */
        switch (code)
        {

            case 'i': 
                num_parts = insert(inventory, num_parts);                   //inserts a new non-existing part
                break;
            case 's':
                search(inventory, num_parts);                               //searches for an existing part
                break;
            case 'u':
                update(inventory, num_parts);                               //updates an existing part
                break;
            case 'p':
                print(inventory, num_parts);                                //prints the current parts
                break;
            case 'c':
                set_price(inventory, num_parts);                            //sets a new price for the current part
                break;
            case 'q':
                return 0;                                                   //end of program

            default: 
                printf("Illegal choice. Please try again.\n");              //indicates invalid command
                //break here not required

        } //end of switch statement

    } //end of for loop

}

/*

Returns the index of a part if its part number exists in inventory
If the the part number doeent exist, it returns -1

*/

int find_part(int number, struct part inventory[], int num_parts)
{

    //local variable
    int i;

    //go through each part in inventory
    for (i = 0; i < num_parts; i++)
    {

        //if an inventory part number matches the given number,
        //return the part's index
        if (inventory[i].number == number)
        {

            return i;

        }

    } //end of for

    //if not found return invalid index
    return -1;

}


//inserts a new part into inventory
int insert(struct part inventory[], int num_parts)
{

    //create local variable
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

    //adding number attribute for the current part
    inventory[num_parts].number = part_num;

    //asking for user input
    printf("Enter your part name: ");
    read_line(inventory[num_parts].name, NAME_LEN);                         //defined by readline.h header file

    printf("Enter quantity on-hand: ");
    scanf("%d", &inventory[num_parts].on_hand);

    //clear the input stream
    clear_input();

    //ask user for price
    printf("Enter price: $");
    scanf("%lf", &inventory[num_parts].price);

    //clear the input stream (again)
    clear_input();

    //increment the total num of parts
    num_parts++;

    //return updated num_parts
    return num_parts;


}

//searches for an existing part in the inventory by part number
void search(struct part inventory[], int num_parts)
{

    //create local variables
    int part_number, i;

    /* Request for user input of part number */
    printf("Please enter your part number: ");
    scanf("%d", &part_number);

    //search for part
    i = find_part(part_number, inventory, num_parts);

    //Print out the data if true, otherwise state part not found
    if (i >= 0)
    {

        printf("Part name: %s\n", inventory[i].name);
        printf("Quantity On-Hand: %d\n", inventory[i].on_hand);
        printf("Price: $%.2lf\n", inventory[i].price);

    }
    else
    {

        printf("Part number not found\n");

    }

    //clear input stream
    clear_input();



} // end of search

//updates an indicated existing part
void update(struct part inventory[], int num_parts)
{

    //local variables
    int i, part_number, change;

    /* Ask user for input of part number to update */
    printf("Enter part number: ");
    scanf("%d", &part_number);

    //search for part number to update
    i = find_part(part_number, inventory, num_parts);

    //if exists, update quantity on-hand, otherwise print error
    if (i >= 0)
    {

        /* Ask user for change in the on hand amount */
        printf("Please enter change in quantity on-hand: ");
        scanf("%d", &change);

        //change the on_hand amount by obtained amount
        inventory[i].on_hand += change;

    }
    else
    {

        printf("Didn't find part\n");

    }

    //clear input stream
    clear_input();

} //end of update

//sets the price of the item requested
void set_price(struct part inventory[], int num_parts)
{

    //local variables
    int i, part_number;

    /* Ask user for input of part number to set_price */
    printf("Enter part number: ");
    scanf("%d", &part_number);

    //search for part number to update
    i = find_part(part_number, inventory, num_parts);

    //if exists, update price, otherwise print error
    if (i >= 0)
    {

        /* Ask user for a new price */
        printf("Please enter a new price: $");
        scanf("%lf", &inventory[i].price);

    }
    else
    {

        printf("Didn't find part\n");

    }

    //clear input stream
    clear_input();

} //end of set_price

//print current inventory
void print(struct part inventory[], int num_parts)
{

    //local variables
    int i;
    
    //print table chart
    printf("Part number    Part name    On hand      Price\n");
    
    //print data of each inventory part
    for (i = 0; i < num_parts; i++)
    {

        printf("%-15d%-13s%-13d$%.2lf\n", inventory[i].number, inventory[i].name, inventory[i].on_hand, inventory[i].price);

    }

} //end of print

//clear input stream
void clear_input(void)
{

    while (getchar() != '\n');                  //skip to the end of line

} //end of clear_input