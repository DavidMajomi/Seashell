// Initial code for shell along with header files which maybe required for reference


# include <stdio.h> 
# include <stdlib.h>   // used to execute subprocess and commands
# include <string.h>   
# include <unistd.h>   // used for exit, getcwd,read, write, exec
# include <sys/wait.h>  
# include <sys/types.h>
# include <dirent.h> // for ls
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>  // used for open
#include <stdbool.h>


void removeTrailingNewLine(char * arr) {
    arr[strlen(arr) - 1] = '\0';
}


// read command line for the input line in shell
void read_line(char * buffer, int bufferSize)
{
    printf(">");
    // printf("%i", bufferSize);
    if (fgets(buffer, bufferSize, stdin) != NULL) {
        // printf("You entered: %s", buffer);
    } else {
        printf("Error reading input.");
    }

    // if (fgets(buffer, bufferSize, stdin) != NULL) {
    //     printf("You entered too many characters");
    //     printf("\n");

    // }

}


// Check for spaces etc
bool isValidOrCorrectableCommand(char * myLine) {
    bool valid = false;
    int numArgs = 0;
    char * res = strtok(myLine, " ");


    while(res != NULL) {
            
        res = strtok(NULL, " ");

        if (res != NULL) {
            numArgs++;
        }

    }

    if (numArgs > 1) {
        valid = false;
    }
    else {
        valid = true;
    }
    
    return valid;
}


void help(char * target) {
    // printf("In help");
    if (strcmp(target, "cd\n") == 0) {
        printf("cd: Change the shell working directory.\n\n");
        printf("Usage: cd [DIR]\n");
        printf("  Change the current directory to DIR. If no directory is given, "
               "it changes to the user's home directory.\n");
        printf("  DIR can be an absolute or relative path.\n\n");
        printf("Examples:\n");
        printf("  cd /path/to/directory\n");
        printf("  cd ..  # Move up one level\n");
        printf("  cd      # Change to home directory\n");

    } else if (strcmp(target, "ls\n") == 0) {
        printf("ls: List directory contents.\n\n");
        printf("Usage: ls [OPTION]... [FILE]...\n");
        printf("  List information about the FILEs (the current directory by default).\n");
    } else if (strcmp(target, "pwd\n") == 0) {
        printf("pwd: Print the name of the current working directory.\n\n");
        printf("Usage: pwd\n");
        printf("  Print the absolute pathname of the current working directory.\n\n");

    } else if (strcmp(target, "mkdir\n") == 0) {
        printf("mkdir: Create directories.\n\n");
        printf("Usage: mkdir [OPTION] DIRECTORY...\n");
        printf("  Create the DIRECTORY, if they do not already exist.\n");
        printf("Examples:\n");
        printf("  mkdir new_folder\n");

    } else if (strcmp(target, "rmdir\n") == 0) {
        printf("rmdir: Remove empty directories.\n\n");
        printf("Usage: rmdir [OPTION] DIRECTORY...\n");
        printf("  Remove empty DIRECTORY.\n");
        printf("Examples:\n");
        printf("  rmdir empty_folder\n");
    } else if (strcmp(target, "help") == 0) {
        printf("Available Commands:\n");
        printf("1. cd - Change the shell working directory\n");
        printf("2. ls - List directory contents\n");
        printf("3. pwd - Print the name of the current working directory\n");
        printf("4. mkdir - Create directories\n");
        printf("5. rmdir - Remove empty directories\n");
        printf("6. help - Display this help message\n");
        printf("\nFor detailed information on each command, type: help <command_name>\n");
    }
    else {
        removeTrailingNewLine(target);
        printf("Help is not available for the command '%s'.\n", target);
    }
}


void rmdir_func(const char * dirName) {
    if (rmdir(dirName) != 0) {
        perror("rmdir() error");
    }   
    else
    {
        puts("removed!");
    }
}


void mkdir_func(const char * dirName) {
    if (mkdir(dirName, 0777) == -1)
    {
        printf("Could not create directory\n");
    }
    else
    {
        printf("Directory created\n");
    }
}


void cd(char * dir) {
    if (strcmp(dir, "..\n") == 0) {
        if (chdir("..") != 0) {
            perror("cd"); // Print system error message
        }
    }
    else if (chdir(dir) != 0) {
        // Check the specific error that occurred
        if (errno == ENOENT) {
            // Directory does not exist
            printf("cd: no such file or directory: %s", dir);
        } else if (errno == EACCES) {
            // Permission denied
            printf("cd: permission denied: %s\n", dir);
        } else {
            // General error
            perror("cd");
        }
    }
}


void pwd() {
    // Define a buffer 
    const size_t size = 1024; 
    // Allocate a character array to store the directory path
    char buffer[size];        
    
    // Call _getcwd to get the current working directory and store it in buffer
    if (getcwd(buffer, size) != NULL) {
    
        printf("Current working directory: ");
        printf("%s", buffer);
        printf("\n");
    } 
    else {
        // If _getcwd returns NULL, print an error message
        printf("Error getting current working directory");
    }
}


void ls() {
    struct dirent *de;  // Pointer for directory entry 
  
    // opendir() returns a pointer of DIR type.  
    DIR *dr = opendir("."); 
  
    if (dr == NULL)  // opendir returns NULL if couldn't open directory 
    { 
        printf("Could not open current directory" ); 
    } 
  

    while ((de = readdir(dr)) != NULL) 
    {
        printf("%s\n", de->d_name); 

    }
  
    closedir(dr);
}


// parse the input command
void parse(char * myLine, int length)
{
    char command[6];
    char target[200];
    char line_copy[200];

    strcpy(line_copy, myLine);

    bool validOrCorrectable = isValidOrCorrectableCommand(line_copy);

    if (validOrCorrectable) {
        char * res;

        res = strtok(myLine, " ");

        strcpy(command, res);

        while(res != NULL) {
            
            res = strtok(NULL, " ");

            if (res != NULL) {
                // printf("%s \n", res);
                strcpy(target, res);

            }
        }

        if (strcmp(command, "help\n") == 0) {
            help("help");
        }
        else if (strcmp(command, "help") == 0) {
            help(target);
        }
        else if (strcmp(command, "cd") == 0) {
            if (strlen(target) > 0) {
                cd(target);
            } else {
                printf("cd: missing operand\n");
            }
        }
        else if (strcmp(command, "ls\n") == 0) {
            ls();
        }
        else if (strcmp(command, "pwd\n") == 0) {
            pwd();
        }
        else if (strcmp(command, "mkdir") == 0) {
            if (strlen(target) > 0) {
                mkdir_func(target);
            } else {
                printf("mkdir: missing operand\n");
            }
        }
        else if (strcmp(command, "rmdir") == 0) {
            if (strlen(target) > 0) {
                rmdir_func(target);
            } else {
                printf("rmdir: missing operand\n");
            }
        }
        else {
            printf("Unknown command: Type 'help' for a list of commands.\n");
        }

    }
    else {
        printf("Unknown command: Type 'help' for a list of commands.\n");
    }
}


int main(int argc, char** argv)
{
    bool running = true;

    while (running)
    {
        char buffer[200];
        char bufferCopy[200];

        read_line(buffer, sizeof(buffer));


        strcpy(bufferCopy, buffer);
        parse(bufferCopy, sizeof(bufferCopy));

    }

    return 0;
}
