//main file
#include <stdio.h>
#include "organizer.h"


void waitAndReturnToMenu() {
    char again;
    printf("\nReturn to menu? (y/n): ");
    scanf(" %c", &again);
    if (again == 'y' || again == 'Y') {
        clearScreen();
    } else {
        printf("Goodbye!\n");
        exit(0);
    }
}

int main() {
    char directory[MAX_PATH];
    int choice;
 	pressToBegin();
    clearScreen();
    
    animatedPrint("\t\t\t\t\t\t\t\t\t\t\tHello Welcome to The Skibidi File Sorter \n\n", 50);  // 50ms delay per character in the console
    
    
    playMusic("Everybodywantstoruletheworld.wav"); // call the function and play the music
    
	printf("\n");
    printf("    								_______             ________   _______    ______          ______      __      ________            \n");
    printf("		     						|           |\\   |     ||      |         |     |         |     |     /  \\        ||       |    | \n");
    printf("		    						|______     | \\  |     ||      |______   |_____|         |_____|    /____\\       ||       |____| \n");
    printf("		    						|           |  \\ |     ||      |         |    \\          |         /      \\      ||       |    | \n");
    printf("		    						|______     |   \\|     ||      |______   |     \\         |        /        \\     ||       |    | \n");
    printf("::::_____________________________________________________________________________________________________________________________________________________________________________________________________________::::");
    scanf(" %[^\n]", directory);

    while (1) {
    	clearScreen();
    	printf("                                                 							 ______\n");
    	printf("											|\\      //|     |           |\\   |      |     |\n");
    	printf("											| \\    // |     |______     | \\  |      |     |\n");
    	printf("											|  \\  //  |     |           |  \\ |      |     |\n");
    	printf("											|   \\//   |     |______     |   \\|      |_____|\n");
        printf("\n================================================================================================================================================================================================================\n\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t1. Sort Files\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t2. Search Files by Keyword Format\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t3. View Folders and Their Files\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t4. Reset to Original\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t5. Exit\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t6. Change Directory\n");  // New option
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        clearScreen();

        if (choice == 1) {
    			sortFiles(directory);
    			Sleep(3000); // 1 second delay for feedback
    			system("cls"); // clear screen
			
        } else if (choice == 2) {
            char keyword[MAX_PATH];
            printf("Enter keyword to search (ex: 'docx', 'pptx', 'pdf' etc.): ");
            scanf(" %[^\n]", keyword);
            searchByKeyword(directory, keyword);
            waitAndReturnToMenu();
        } else if (choice == 3) {
            viewFoldersAndFiles(directory);
            waitAndReturnToMenu();
        } else if (choice == 4) {
            resetToOriginal(directory);
            waitAndReturnToMenu();
        } else if (choice == 5) {
        	PlaySound(NULL, NULL, 0); // Stop music
        	printf("\n");
			printf("\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\tThank you for using The SKibidi File Sorter!\n");
            break;
        } else if (choice == 6) {
            printf("Enter new directory path: ");
            scanf(" %[^\n]", directory);
            printf("Directory updated!\n");
            waitAndReturnToMenu();
        } else {
            printf("Invalid choice.\n");
            waitAndReturnToMenu();
        }
    }
    
return 0;
}

