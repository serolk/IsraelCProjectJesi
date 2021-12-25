#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

#define ARRAY_SIZE 200


typedef struct Word {
    char **translations;
    struct Word *next;
} Word;

typedef struct Dictionary {
    char **languages;
    int numOfLanguages;
    Word *wordList;
} Dictionary;

void printAllDictionaries(struct Dictionary *firstDictPtr, int numOfDicts) {
    char **ptrLangs;
    for (int i = 0; i < numOfDicts; ++i) {
        printf("%d.", i + 1);
        ptrLangs = (firstDictPtr + i)->languages;
        int numOfLangs = (firstDictPtr + i)->numOfLanguages;
        for (int j = 0; j < numOfLangs; ++j) {
            if (j == numOfLangs - 1) {
                printf("%s\n", ptrLangs[j]);
            } else {
                printf("%s,", ptrLangs[j]);
            }
        }
    }
}

void printSelectedDictionaryName(struct Dictionary *firstDictPtr, int dictIndex) {
    char **ptrLangs = (firstDictPtr + dictIndex)->languages;
    int numOfLangs = (firstDictPtr + dictIndex)->numOfLanguages;
    printf("Enter a word in ");
    for (int j = 0; j < numOfLangs; ++j) {
        if (j == numOfLangs - 1) {
            printf("%s:\n", ptrLangs[j]);
        } else {
            printf("%s,", ptrLangs[j]);
        }
    }
}

void printTranslations(char **ptr_languages, int numOfLangs, struct Word *ptr_Word) {
    printf("The translations are:\n");
    for (int j = 1; j < numOfLangs; ++j) {
        if (j == numOfLangs - 1) {
            printf("%s: %s\n", ptr_languages[j], ptr_Word->translations[j]);
        } else {
            printf("%s: %s,", ptr_languages[j], ptr_Word->translations[j]);
        }
    }
}

void printSelectedDictionaryMainName(struct Dictionary *firstDictPtr, int dictIndex) {
    char **ptrLangs = (firstDictPtr + dictIndex)->languages;
    int numOfLangs = (firstDictPtr + dictIndex)->numOfLanguages;
    printf("Enter a word in %s\n", ptrLangs[0]);
}

int selectDictionary() {
    int dictIndex = 0;
    scanf("%d", &dictIndex);
    return dictIndex;
}

void eraseDictionary(struct Dictionary *ptrDict, int selectedDict, int numberOfDicts, struct Dictionary *ptrNewDict) {

    int k = 0;
    for (int i = 0; i < numberOfDicts; ++i) {
        if(i != selectedDict) {
            (ptrNewDict+k)->wordList = (ptrDict+i)->wordList;
            (ptrNewDict+k)->languages = (ptrDict+i)->languages;
            (ptrNewDict+k)->numOfLanguages = (ptrDict+i)->numOfLanguages;
            ++k;
        }
    }
    free(ptrDict);
}

struct Word *wordSearch(struct Word *ptr_word) {

    char sourceWord[50];
    scanf("%s", sourceWord);
//    strcmp()
    char *destWord = ptr_word->translations[0];
    while (strcmp(sourceWord, destWord)) {
        if (!ptr_word->next)
            return NULL;
        ptr_word = ptr_word->next;
        destWord = ptr_word->translations[0];
    }
    return destWord;
}

int eraseWord(struct Word *ptr_word) {
    char sourceWord[50];
    char *ptr_firstWord = ptr_word;
    scanf("%s", sourceWord);
    printf("Are you sure? (y/n)");
    char answer = 'n';
    scanf("%c", &answer);
    if (answer == 'y') {
        char *destWord = ptr_word->translations[0];
        struct Word *ptr_previousWord = ptr_word;
        while (strcmp(sourceWord, destWord)) {
            if (!ptr_word->next) {//is Last word in linkedList?
                printf("Word doesn't found");
                return 0;
            }
            ptr_previousWord = ptr_word;
            ptr_word = ptr_word->next;
            destWord = ptr_word->translations[0];
        }

        if (ptr_word == ptr_firstWord) {
            ptr_firstWord = NULL; //Means first word deleted in dictionary;
            return 1;
        } else {
            ptr_previousWord->next = ptr_word->next;
            free(ptr_word);
            return 1;
        }
    } else {
        printf("The deletion of the word has been canceled.");
        return 0;
    }
}

int addWord(char **ptr_Translation) {
    char entry[ARRAY_SIZE];
    scanf("%s", entry);

    char val = entry[0];
    int numOfComma = 0;
    int numOfWordLetter = 0;
    int k = 0;
    int startIndex = 0;

    while (val != '\0') {
        if (val != ',') {
            //Counting Letters:
            numOfWordLetter++;
        } else {
            //Language adding:
            char words[numOfWordLetter + 1];
            if (numOfWordLetter > 0) {
                strncpy(words, &entry[startIndex], numOfWordLetter);
                words[numOfWordLetter] = '\0';
            }

            printf("Diller: %s\n", words);
            startIndex += numOfWordLetter + 1;

            //First Language Allocating and Copying:
            ptr_Translation[numOfComma] = (char *) malloc(sizeof(char) * numOfWordLetter);
            if (ptr_Translation[numOfComma] == NULL) {
                printf("dinamik bir blok elde edilemiyor!\n");
                exit(EXIT_FAILURE);
            }
            strcpy(ptr_Translation[numOfComma], ptr_Translation);

            printf("Diller PTR->: %s\n", ptr_Translation[numOfComma]);
            numOfWordLetter = 0;
            numOfComma++;
        }

        val = entry[++k];

        if (val == '\0') {
            char lastLang[numOfWordLetter + 1];
            if (numOfWordLetter > 0) { //Burada dil ismi için gerekli diziyi allocate edeceğiz:
                strncpy(lastLang, &entry[startIndex], numOfWordLetter);
                lastLang[numOfWordLetter] = '\0';
            }
            printf("Diller: %s\n", lastLang);

            //First Language Allocating and Copying:
            ptr_Translation[numOfComma] = (char *) malloc(sizeof(char) * numOfWordLetter);
            if (ptr_Translation[numOfComma] == NULL) {
                printf("dinamik bir blok elde edilemiyor!\n");
                exit(EXIT_FAILURE);
            }
            strcpy(ptr_Translation[numOfComma], lastLang);
            printf("Diller PTR->: %s\n", ptr_Translation[numOfComma]);

            //Other languages slots initalizing:
//            for (int i = numOfComma + 1; i < 5; ++i) {
//                ptr_languages[i] = 0;
//            }
            numOfComma++;
            numOfWordLetter = 0;
        }
    }
}

void addDictionary(char **ptr_languages, int *ptr_numOfLanguages) {

    char entry[ARRAY_SIZE];
    //Getting Languages for Dictionary on Keyboard:
    printf("Dilleri giriniz: ");
//    gets(entry);
    scanf("%s", entry);
    //Parsing string by ",":
    char val = entry[0];
    int numOfComma = 0;
    int numOfLangLetter = 0;
    int k = 0;
    int startIndex = 0;

    while (val != '\0') {
        if (val != ',') {
            //Counting Letters:
            numOfLangLetter++;
        } else {
            //Language adding:
            char languages[numOfLangLetter + 1];
            if (numOfLangLetter > 0) {
                strncpy(languages, &entry[startIndex], numOfLangLetter);
                languages[numOfLangLetter] = '\0';
            }

            printf("Diller: %s\n", languages);
            startIndex += numOfLangLetter + 1;

            //First Language Allocating and Copying:
            ptr_languages[numOfComma] = (char *) malloc(sizeof(char) * numOfLangLetter);
            if (ptr_languages[numOfComma] == NULL) {
                printf("dinamik bir blok elde edilemiyor!\n");
                exit(EXIT_FAILURE);
            }
            strcpy(ptr_languages[numOfComma], languages);

            printf("Diller PTR->: %s\n", ptr_languages[numOfComma]);
            numOfLangLetter = 0;
            numOfComma++;
        }

        val = entry[++k];

        if (val == '\0') {
            char lastLang[numOfLangLetter + 1];
            if (numOfLangLetter > 0) { //Burada dil ismi için gerekli diziyi allocate edeceğiz:
                strncpy(lastLang, &entry[startIndex], numOfLangLetter);
                lastLang[numOfLangLetter] = '\0';
            }
            printf("Diller: %s\n", lastLang);

            //First Language Allocating and Copying:
            ptr_languages[numOfComma] = (char *) malloc(sizeof(char) * numOfLangLetter);
            if (ptr_languages[numOfComma] == NULL) {
                printf("dinamik bir blok elde edilemiyor!\n");
                exit(EXIT_FAILURE);
            }
            strcpy(ptr_languages[numOfComma], lastLang);
            printf("Diller PTR->: %s\n", ptr_languages[numOfComma]);

            //Other languages slots initalizing:
//            for (int i = numOfComma + 1; i < 5; ++i) {
//                ptr_languages[i] = 0;
//            }
            numOfComma++;
            numOfLangLetter = 0;
        }
    }
    *ptr_numOfLanguages = numOfComma;
}

void getFreeAllMemory(struct Dictionary *ptrDict, int numberOfDicts) {
//    char *ptr;
//    Word *wordList;
//    for (int i = 0; i < numberOfDicts; ++i) {
//        ptr = ptrDict[i].languages;
//        for (int j = 0; j < ptr; ++j) {
//
//        }
//    }
}

void main() {

    struct Dictionary *ptrDict;
    struct Dictionary *ptrNewDict;
    int numberOfDicts = 0;
    int selectedDictionaryIndex = -1;
    struct Word *ptrWord;


    int x;
    printf("Welcome to the dictionaries manager!\n");
    while (x != 6) {
        printf("Choose an option : \n");
        printf("1. Create a new dictionary.\n");
        printf("2. Add a word to a dictionary.\n");
        printf("3. Delete a word from a dictionary.\n");
        printf("4. Find a word in a dictionary.\n");
        printf("5. Delete a dictionary.\n");
        printf("6. Exit.\n");
        scanf("%d", &x);
        switch (x) {
            case 1:
                //Creating dictionary allocation:
                if (numberOfDicts == 0) {
                    ptrDict = (struct Dictionary *) malloc(sizeof(struct Dictionary) * 1);
                } else {
                    ptrDict = (struct Dictionary *) realloc(ptrDict, sizeof(struct Dictionary) * (numberOfDicts + 1));
                }
                if (ptrDict == NULL) {
                    printf("can not allocate memory!..\n");
                    exit(EXIT_FAILURE);
                }
                (ptrDict + numberOfDicts)->languages = (char **) malloc(sizeof(char *));
                if ((ptrDict + numberOfDicts)->languages == NULL) {
                    printf("can not allocate memory!..\n");
                    exit(EXIT_FAILURE);
                }

                addDictionary((ptrDict + numberOfDicts)->languages, &((ptrDict + numberOfDicts)->numOfLanguages));
                (ptrDict + numberOfDicts)->wordList = NULL;
                numberOfDicts++;
                break;
            case 2:
                printf("Choose a dictionary:\n");
                printAllDictionaries(ptrDict, numberOfDicts);
                selectedDictionaryIndex = selectDictionary(ptrDict) - 1;
                printSelectedDictionaryName(ptrDict, selectedDictionaryIndex);

                if ((ptrDict + selectedDictionaryIndex)->wordList == NULL) { //TO DO: Kntrol edilecek
                    ptrWord = (struct Word *) malloc(sizeof(struct Word));
                    (ptrDict + selectedDictionaryIndex)->wordList = ptrWord;
                } else {
                    ptrWord = (struct Word *) malloc(sizeof(struct Word));
                    struct Word *ptrLastWord = (ptrDict + selectedDictionaryIndex)->wordList->next;
                    int flag = 1;
                    while (flag) {
                        if (ptrLastWord->next != NULL)
                            ptrLastWord = ptrLastWord->next;
                        else
                            flag = 0;
                    }
                    ptrLastWord->next = ptrWord;
                }
                ptrWord->translations = (char **) malloc(sizeof(char *));
                addWord((ptrWord)->translations);
                printf("The word has been added successfully!\n");
                free(ptrWord);
                break;
            case 3:
                printf("Choose a dictionary:\n");
                printAllDictionaries(ptrDict, numberOfDicts);
                selectedDictionaryIndex = selectDictionary(ptrDict) - 1;
                if ((ptrDict + selectedDictionaryIndex)->wordList != NULL) {
                    printSelectedDictionaryMainName(ptrDict, selectedDictionaryIndex);
                    if(eraseWord((ptrDict + selectedDictionaryIndex)->wordList))
                        printf("The word has been deleted successfully!");
                } else {
                    printf("This option is not available right now, try again:\n");
                }
                break;
            case 4:
                printf("Choose a dictionary:\n");
                printAllDictionaries(ptrDict, numberOfDicts);
                selectedDictionaryIndex = selectDictionary(ptrDict) - 1;
                if ((ptrDict + selectedDictionaryIndex)->wordList != NULL) {
                    printSelectedDictionaryMainName(ptrDict, selectedDictionaryIndex);
                    struct Word *wrdSearch = wordSearch((ptrDict + selectedDictionaryIndex)->wordList);
                    if (wrdSearch != NULL)
                        printTranslations((ptrDict + selectedDictionaryIndex)->languages,
                                          (ptrDict + selectedDictionaryIndex)->numOfLanguages, wrdSearch);
                    else
                        printf("Word doesn't found");
                } else {
                    printf("This option is not available right now, try again:\n");
                }
                break;
            case 5:
                printf("Choose a dictionary:\n");
                printAllDictionaries(ptrDict, numberOfDicts);
                selectedDictionaryIndex = selectDictionary(ptrDict) - 1;
                if (numberOfDicts == 1) {
                    free(ptrDict);//Means All dictionaries are deleted.
                } else {
                    ptrNewDict = (struct Dictionary *) malloc(sizeof(struct Dictionary) * (numberOfDicts - 1));
                    if (ptrNewDict == NULL) {
                        printf("can not allocate memory!..\n");
                        exit(EXIT_FAILURE);
                    }
                    eraseDictionary(ptrDict, selectedDictionaryIndex, numberOfDicts, ptrNewDict);
//                    ptrDict = (struct Dictionary *) malloc(sizeof(struct Dictionary) * (numberOfDicts - 1));
//                    if (ptrDict == NULL) {
//                        printf("can not allocate memory!..\n");
//                        exit(EXIT_FAILURE);
//                    }
                    ptrDict = ptrNewDict;
                    numberOfDicts--;
                }
                break;
            case 6:
//                getFreeAllMemory(ptrDict, numberOfDicts);
                printf("Bye");
                free(ptrNewDict);
                free(ptrDict);
//                exit(0);
                break;
            case 9:
                printAllDictionaries(numberOfDicts, ptrDict);
                break;
            default:
                printf("Wrong option, try again:\n");
                break;
        }
    }

}