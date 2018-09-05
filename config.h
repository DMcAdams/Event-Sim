
/*==============================================================================================
 |       Author:  Darrin McAdams
 |         Date:  September 4th, 2018
 |  Description:  This header has a struct for config information and
 |                 a function create_config that gets values for it from a config.txt file
 *==============================================================================================*/

#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 1024
//struct holds all of the config variables
struct config
{
    //Values come from config file
    int INIT_TIME;
    int FIN_TIME;
    int ARRIVE_MIN;
    int ARRIVE_MAX;
    int QUIT_PROB;
    int CPU_MIN;
    int CPU_MAX;
    int DISK1_MIN;
    int DISK1_MAX;
    int DISK2_MIN;
    int DISK2_MAX;
};

//initialize the config struct
struct config *create_config(){
    //allocate memory
    struct config *temp = malloc(sizeof(struct config));
    //initialize all variables to 0
    temp->INIT_TIME = 0;
    temp->FIN_TIME = 0;
    temp->ARRIVE_MIN = 0;
    temp->ARRIVE_MAX= 0;
    temp->QUIT_PROB = 0;
    temp->CPU_MIN = 0;
    temp->CPU_MAX = 0;
    temp->DISK1_MIN = 0;
    temp->DISK1_MAX = 0;
    temp->DISK2_MIN = 0;
    temp->DISK2_MAX = 0;
    return temp;
}

struct config *get_config(const char *filename) {

    //get a new config struct
    struct config *CONFIG_INFO = create_config();
    //open config text file
    FILE *file = fopen(filename, "r");

    char buff[BUFF_SIZE];
    char line1[BUFF_SIZE];
    char line2[BUFF_SIZE];
    int count = 0;

    if (file != NULL) {
        //holds the strings from the file
        char buff[BUFF_SIZE];
        char line1[BUFF_SIZE];
        char line2[BUFF_SIZE];

        //holds int values for each line
        int count = 0;

        //loop through each line
        while (fgets(buff, sizeof(line), file) != NULL) {
            sscanf(buff, "%s %s", line1, line2);

            switch (count) {
                case 0:
                    CONFIG_INFO->INIT_TIME = atoi(line2);
                    break;
                case 1:
                    CONFIG_INFO->FIN_TIME = atoi(line2);
                    break;
                case 2:
                    CONFIG_INFO->ARRIVE_MIN = atoi(line2);
                    break;
                case 3:
                    CONFIG_INFO->ARRIVE_MAX = atoi(line2);
                    break;
                case 4:
                    CONFIG_INFO->QUIT_PROB = atoi(line2);
                    break;
                case 5:
                    CONFIG_INFO->CPU_MIN = atoi(line2);
                    break;
                case 6:
                    CONFIG_INFO->CPU_MAX = atoi(line2);
                    break;
                case 7:
                    CONFIG_INFO->DISK1_MIN = atoi(line2);
                    break;
                case 8:
                    CONFIG_INFO->DISK1_MAX = atoi(line2);
                    break;
                case 9:
                    CONFIG_INFO->DISK2_MIN = atoi(line2);
                    break;
                case 10:
                    CONFIG_INFO->DISK2_MAX = atoi(line2);
                    break;
                default:
                    puts("ERROR: Config.txt file couldn't be read");
            }
            count++;
        }
        //close config.txt
        fclose(file);
    }
    //if file not found
    else puts("ERROR: config.txt NOT FOUND");

    return CONFIG_INFO;
}

#endif
