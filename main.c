#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

void list_files()
{
    struct dirent *de;
    DIR *dr = opendir(".");

    if (dr == NULL)
    {
        printf("Could not open current directory\n");
        return;
    }

    while ((de = readdir(dr)) != NULL)
        printf("%s\n", de->d_name);

    closedir(dr);
}

void print_working_directory()
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("Current working dir: %s\n", cwd);
    }
    else
    {
        perror("getcwd() error");
    }
}

void display_file_content(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Could not open file %s\n", filename);
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF)
        putchar(ch);

    fclose(file);
}

void create_directory(char *dirname)
{
    if (mkdir(dirname) == 0)
    {
        printf("Directory created successfully\n");
    }
    else
    {
        perror("mkdir() error");
    }
}

void remove_directory(char *dirname)
{
    if (rmdir(dirname) == 0)
    {
        printf("Directory removed successfully\n");
    }
    else
    {
        perror("rmdir() error");
    }
}

void remove_file(char *filename)
{
    if (remove(filename) == 0)
    {
        printf("File removed successfully\n");
    }
    else
    {
        perror("remove() error");
    }
}

void display_help()
{
    printf("Available commands:\n");
    printf("ls     - List files in the current directory\n");
    printf("pwd    - Print the current working directory\n");
    printf("cat    - Display the contents of a file\n");
    printf("mkdir  - Create a new directory\n");
    printf("rmdir  - Remove an empty directory\n");
    printf("rm     - Remove a file\n");
    printf("whoami - Display the current user's username\n");
    printf("help   - Display this help message\n");
    printf("exit   - Exit the program\n");
}

void whoami()
{
    char *username = getenv("USER");
    if (username == NULL)
    {
        username = getenv("USERNAME");
    }
    if (username != NULL)
    {
        printf("Current user: %s\n", username);
    }
    else
    {
        printf("Could not determine the current user\n");
    }
}

int main()
{
    char command[100];
    char argument[100];
    static int first_run = 1;

    if (first_run)
    {
        printf("Welcome to the Linux shell on Windows!\n");
        printf("This shell simulation was created by -\n");
        printf("+--------------------+----------------------+\n");
        printf("| Name               | USN                  |\n");
        printf("+--------------------+----------------------+\n");
        printf("| Taufeeq Riyaz      | 1RVU23CSE506         |\n");
        printf("| Sushanth Harsha    | 1RVU23CSE501         |\n");
        printf("| T Nihal            | 1RVU23CSE502         |\n");
        printf("+--------------------+----------------------+\n");
        first_run = 0;
    }

    while (1)
    {
        printf("\nEnter a command (type 'help' for list of commands): ");
        scanf("%s", command);

        if (strcmp(command, "ls") == 0)
        {
            list_files();
        }
        else if (strcmp(command, "pwd") == 0)
        {
            print_working_directory();
        }
        else if (strcmp(command, "cat") == 0)
        {
            printf("Enter filename: ");
            scanf("%s", argument);
            display_file_content(argument);
        }
        else if (strcmp(command, "mkdir") == 0)
        {
            printf("Enter directory name: ");
            scanf("%s", argument);
            create_directory(argument);
        }
        else if (strcmp(command, "rmdir") == 0)
        {
            printf("Enter directory name: ");
            scanf("%s", argument);
            remove_directory(argument);
        }
        else if (strcmp(command, "rm") == 0)
        {
            printf("Enter filename: ");
            scanf("%s", argument);
            remove_file(argument);
        }
        else if (strcmp(command, "whoami") == 0)
        {
            whoami();
        }
        else if (strcmp(command, "help") == 0)
        {
            display_help();
        }
        else if (strcmp(command, "exit") == 0)
        {
            break;
        }
        else
        {
            printf("Invalid command. Type 'help' for list of commands.\n");
        }
    }

    return 0;
}