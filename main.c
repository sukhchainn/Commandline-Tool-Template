#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "pack.h"
#include "unpack.h"

#define VERSION "0.0.0.1"

// Options available globally
char OPTIONS[10], FEATURES[4];

// File to be used if no arguments provided
char* default_file = "input.txt";

int main(int argc, char *argv[]) {
    printf("file-pack version : %s\n", VERSION);

    // Checks if arguments are provided or not.
    if (argc > 1) {
        // Checks if file exists or not.
        if ( access( argv[1], F_OK ) != -1 ) {
            printf("\nusing %s\n", argv[1]);
        } else { 
            printf("\n%s does not exist or not readable\n", argv[1]);
            exit(EXIT_FAILURE);
        }

        // OPTIONS count block
        char options_count = 0;
        {
            char temp[11];
            for (int i = 2; i < argc; ++i)
            {
                strcpy(temp, argv[i]);
                if (temp[0] == '-' && temp[1] != '-') {
                    options_count++;
                } else if (temp[0] == '-' && temp[1] == '-') {
                    break;
                } else {
                    printf("Invalid option : %s\n", argv[i]);
                    exit(EXIT_FAILURE);
                }
            }
        }

        // FEATURES count block
        char features_count = 0;
        {
            char temp[11];
            for (int i = options_count+2; i < argc; ++i)
            {
                strcpy(temp, argv[i]);
                if (temp[0] == '-' && temp[1] == '-') {
                    features_count++;
                } else {
                    printf("Invalid feature : %s\n", argv[i]);
                    exit(EXIT_FAILURE);
                }
            }
        }


        // will contain the options provided through arguments
        // options start from 2nd argument
        char buffer[12];

        // Convert arguments to string buffer
        for (char i = 2; i < options_count+2; ++i)
        {
            int len = strlen(argv[i]);

            if (len > 11) {
                printf("%s exceeds the option's allowed length!\n", argv[i]);
                exit(EXIT_FAILURE);
            } else {
                // Enable OPTIONS
                strcpy(buffer, argv[i]);
                for (int i = 1; i < len; ++i)
                {
                    switch (buffer[i])
                    {
                    case 'P':
                        OPTIONS[P] = 1;
                        break;
                    case 'o':
                        OPTIONS[o] = 1;
                        break;
                    case 'r':
                        OPTIONS[r] = 1;
                        break;
                    case 't':
                        OPTIONS[t] = 1;
                        break;
                    case 'U':
                        OPTIONS[U] = 1;
                        break;
                    case 'g':
                        OPTIONS[g] = 1;
                        break;
                    case 'u':
                        OPTIONS[u] = 1;
                        break;
                    case 'E':
                        OPTIONS[E] = 1;
                        break;
                    case 's':
                        OPTIONS[s] = 1;
                        break;
                    case 'e':
                        OPTIONS[e] = 1;
                        break;

                    default:
                        printf("Not an Option %c, ", buffer[i]);
                        break;
                    }
                } printf("\n");
            }
        }


        // Enable the features provided to the program.
        for (char i = options_count+2; i < argc; i++)
        {
            if (!strcmp(argv[i], "--test")) {
                FEATURES[test] = 1;
            } else if (!strcmp(argv[i], "--verbose")) {
                FEATURES[verbose] = 1;
            } else if (!strcmp(argv[i], "--help")) {
                FEATURES[help] = 1;
            } else if (!strcmp(argv[i], "--quite")) {
                FEATURES[quite] = 1;
            } else
                printf("%s not a feature! \n", argv[i]);
        }
        printf("\n");
    }

    // Print this if arguments weren't provided.
    else {
        printf("You didn't provide any arguments.\n");
        printf("Finding \"%s\" file\n", default_file);

        if ( access( default_file, F_OK ) != -1 ) {
            printf("\nusing \"%s\"\n", default_file);
        } else {
            printf("\n%s does not exist or not readable\n", default_file);
            exit(EXIT_FAILURE);
        }

    }


    /**
     * From here the application logic starts
     *
    */

    
    // To be removed after the implementation of pack.c and unpack.c
    for (char i = 0; i < 10; i++)
    {
        printf("%d ", OPTIONS[i]);
    } printf(" ");
    for (char i = 0; i < 4; i++)
    {
        printf("%d ", FEATURES[i]);
    } printf("\n");

    return 0;
}
