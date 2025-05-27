

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> // open and read them folders
#include <sys/stat.h> // check sa file/folder info
#ifdef _WIN32 // My Laptop is windows so yeah
    #include <direct.h>
    #include <windows.h> 
    #include <mmsystem.h> //libraries para sa music file directory
#pragma comment(lib, "winmm.lib") 
    #define mkdir(dir) _mkdir(dir) // "Use Windows’ version of make directory"
    #define rmdir(dir) _rmdir(dir) //"Use Windows’ version of remove directory"
#endif

#define MAX_PATH 260 //  safety limit para ang file paths dili taas kaayo

// Utility functions
void clearScreen() {
    system("cls"); // Windows only
}

void pressToBegin() {
    printf("\nPress any key to begin...\n");
    system("pause >nul");
}

// print animation sa title
void animatedPrint(const char *text, int delayMs) {
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        printf("%c", text[i]);
        fflush(stdout);  //show character without waiting for new one
        Sleep(delayMs);  // delay for the next one to show up
    }
    printf("\n");
}

void createDirectory(const char *dirName) {
    struct stat st;
    if (stat(dirName, &st) != 0) {
        mkdir(dirName);
    }
}

const char* getFileExtension(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if (!dot || dot == filename) return "";
    return dot + 1;
}

void moveFile(const char *source, const char *destination) {
    rename(source, destination);
}
// sort files by classifications
void sortFiles(const char *directory) {
    DIR *dir = opendir(directory); //open a directory 
    struct dirent *entry;
    struct stat fileStat;

    if (!dir) {
        printf("Error: Cannot open directory!\n");
        return;
    }
    while ((entry = readdir(dir)) != NULL) {
        char filePath[MAX_PATH];
        snprintf(filePath, MAX_PATH, "%s/%s", directory, entry->d_name);

        if (stat(filePath, &fileStat) == 0 && S_ISREG(fileStat.st_mode)) {
            const char *ext = getFileExtension(entry->d_name);
            char subfolder[MAX_PATH] = "";
			// File Types
            if (strcmp(ext, "pdf") == 0) {
                strcpy(subfolder, "PDFs");
            } else if (strcmp(ext, "docx") == 0) {
                strcpy(subfolder, "Docs");
            } else if (strcmp(ext, "txt") == 0) {
                strcpy(subfolder, "Text");
            } else if (strcmp(ext, "ppt") == 0 || strcmp(ext, "pptx") == 0) {
                strcpy(subfolder, "PowerPoint");
            } else if (strcmp(ext, "xlsx") == 0 || strcmp(ext, "xlsx") == 0) {
                strcpy(subfolder, "Excel");
            } else if (strcmp(ext, "jpg") == 0) {
                strcpy(subfolder, "JPGs");
            } else if (strcmp(ext, "jpeg") == 0) {
                strcpy(subfolder, "JPEGs");
            } else if (strcmp(ext, "png") == 0) {
                strcpy(subfolder, "PNGs");
            } else if (strcmp(ext, "gif") == 0) {
                strcpy(subfolder, "GIFs");
            } else if (strcmp(ext, "JFIF") == 0) {
                strcpy(subfolder, "jfif");
            } else if (strcmp(ext, "mp4") == 0) {
                strcpy(subfolder, "MP4s");
            } else if (strcmp(ext, "mp3") == 0 || strcmp(ext, "wav") == 0) {
                strcpy(subfolder, "Audio");
            } else if (strcmp(ext, "zip") == 0) {
                strcpy(subfolder, "Zips");
            } else if (strcmp(ext, "exe") == 0) {
                strcpy(subfolder, "Applications");
            } else {
                strcpy(subfolder, "Others");
            }

            char folderPath[MAX_PATH];
            snprintf(folderPath, sizeof(folderPath), "%s/%s", directory, subfolder);
            createDirectory(folderPath);

            char newPath[MAX_PATH];
            snprintf(newPath, sizeof(newPath), "%s/%s/%s", directory, subfolder, entry->d_name);
            moveFile(filePath, newPath);
            printf("Moved: %s -> %s\n", entry->d_name, subfolder);
        }
    }
    closedir(dir);
    printf("File organization complete!\n");
}
// view them folders
void viewFoldersAndFiles(const char *directory) {
    DIR *dir = opendir(directory);
    struct dirent *entry;
    struct stat statbuf;
    char path[MAX_PATH];

    if (!dir) {
        printf("Unable to open directory: %s\n", directory);
        return;
    }
    printf("\n--- Folders and Their Files ---\n");

    while ((entry = readdir(dir)) != NULL) {
        snprintf(path, MAX_PATH, "%s/%s", directory, entry->d_name);
        if (stat(path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode) &&
            strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {

            printf("\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t Folder: %s\n\n", entry->d_name);
            DIR *subDir = opendir(path);
            struct dirent *subEntry;
            if (subDir) {
                while ((subEntry = readdir(subDir)) != NULL) {
                    if (strcmp(subEntry->d_name, ".") != 0 && strcmp(subEntry->d_name, "..") != 0) {
                        printf("  - %s\n", subEntry->d_name);
                    }
                }
                closedir(subDir);
            }
        }
    }
    closedir(dir);
}
	//reset tanan folders 
void resetToOriginal(const char *directory) {
    DIR *dir = opendir(directory);
    struct dirent *entry;
    struct stat statbuf;
    char subfolderPath[MAX_PATH], filePath[MAX_PATH], newFilePath[MAX_PATH];

    if (!dir) {
        printf("Unable to open directory: %s\n", directory);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        snprintf(subfolderPath, MAX_PATH, "%s/%s", directory, entry->d_name);
        if (stat(subfolderPath, &statbuf) == 0 && S_ISDIR(statbuf.st_mode) &&
            strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {

            DIR *subDir = opendir(subfolderPath);
            struct dirent *subEntry;
            if (subDir) {
                while ((subEntry = readdir(subDir)) != NULL) {
                    if (strcmp(subEntry->d_name, ".") == 0 || strcmp(subEntry->d_name, "..") == 0)
                        continue;

                    snprintf(filePath, MAX_PATH, "%s/%s", subfolderPath, subEntry->d_name);
                    snprintf(newFilePath, MAX_PATH, "%s/%s", directory, subEntry->d_name);
                    moveFile(filePath, newFilePath);
                }
                closedir(subDir);
            }
            rmdir(subfolderPath);
        }
    }
    closedir(dir);
    printf("Reset to original complete. All files moved back.\n");
}

void playMusic() {
    PlaySound("./Everybodywantstoruletheworld.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

//search it by file format
void searchByKeyword(const char *directory, const char *keyword) {
    DIR *dir = opendir(directory);
    struct dirent *entry;
    struct stat statbuf;
    char path[MAX_PATH];
    char folderPath[MAX_PATH];

    if (!dir) {
        printf("Unable to open directory: %s\n", directory);
        return;
    }

    printf("\n--- Files matching '%s' ---\n", keyword);

    while ((entry = readdir(dir)) != NULL) {
        snprintf(path, MAX_PATH, "%s/%s", directory, entry->d_name);
        if (stat(path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode) &&
            strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {

            // If we find a folder, we will check the files inside
            DIR *subDir = opendir(path);
            struct dirent *subEntry;
            if (subDir) {
                while ((subEntry = readdir(subDir)) != NULL) {
                    snprintf(folderPath, MAX_PATH, "%s/%s", path, subEntry->d_name);
                    if (strstr(subEntry->d_name, keyword) != NULL) {
                        // Print folder name and the matching file
                        printf("Folder: %s\n", entry->d_name);
                        printf("  - File: %s\n", subEntry->d_name);
                    }
                }
                closedir(subDir);
            }
        }
    }
    closedir(dir);
}


