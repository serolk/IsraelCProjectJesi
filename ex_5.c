#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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
    char **ptrLangs;// = (char **) malloc(sizeof(char *));
    ptrLangs = (firstDictPtr + dictIndex)->languages;
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

void printTranslations(char **ptr_languages, int numOfLangs, char **ptr_Word) {
    printf("The translations are:\n");
    for (int j = 1; j < numOfLangs; ++j) {
        if (j == numOfLangs - 1) {
            printf("%s: %s\n", ptr_languages[j], ptr_Word[j]);
        } else {
            printf("%s: %s, ", ptr_languages[j], ptr_Word[j]);
        }
    }
}

void printSelectedDictionaryMainName(struct Dictionary *firstDictPtr, int dictIndex) {
    char **ptrLangs = (firstDictPtr + dictIndex)->languages;
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
        if (i != selectedDict) {
            (ptrNewDict + k)->wordList = (ptrDict + i)->wordList;
            (ptrNewDict + k)->languages = (ptrDict + i)->languages;
            (ptrNewDict + k)->numOfLanguages = (ptrDict + i)->numOfLanguages;
            ++k;
        }
    }
    free(ptrDict);
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
            startIndex += numOfWordLetter + 1;
            //First Language Allocating and Copying:
            ptr_Translation[numOfComma] = (char *) malloc(sizeof(char) * numOfWordLetter);
            if (ptr_Translation[numOfComma] == NULL) {
                printf("The addition of the word has failed!\n");
                exit(EXIT_FAILURE);
            }
            strcpy(ptr_Translation[numOfComma], words);
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
            //First Language Allocating and Copying:
            ptr_Translation[numOfComma] = (char *) malloc(sizeof(char) * numOfWordLetter);
            if (ptr_Translation[numOfComma] == NULL) {
                printf("The addition of the word has failed!\n");
                exit(EXIT_FAILURE);
            }
            strcpy(ptr_Translation[numOfComma], lastLang);

            numOfComma++;
            numOfWordLetter = 0;
        }
    }
}

void addDictionary(char **ptr_languages, int *ptr_numOfLanguages) {

    char entry[ARRAY_SIZE];
    //Getting Languages for Dictionary on Keyboard:
    printf("Define a new dictionary: ");
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
            startIndex += numOfLangLetter + 1;

            //First Language Allocating and Copying:
            ptr_languages[numOfComma] = (char *) malloc(sizeof(char) * numOfLangLetter);
            if (ptr_languages[numOfComma] == NULL) {
                printf("The creation of the dictionary has failed!\n");
                exit(EXIT_FAILURE);
            }
            strcpy(ptr_languages[numOfComma], languages);
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

            //First Language Allocating and Copying:
            ptr_languages[numOfComma] = (char *) malloc(sizeof(char) * numOfLangLetter);
            if (ptr_languages[numOfComma] == NULL) {
                printf("The creation of the dictionary has failed!\n");
                exit(EXIT_FAILURE);
            }
            strcpy(ptr_languages[numOfComma], lastLang);
            numOfComma++;
            numOfLangLetter = 0;
        }
    }
    *ptr_numOfLanguages = numOfComma;
}

void printMenu(){
    printf("Welcome to the dictionaries manager!\n");
    printf("Choose an option : \n");
    printf("1. Create a new dictionary.\n");
    printf("2. Add a word to a dictionary.\n");
    printf("3. Delete a word from a dictionary.\n");
    printf("4. Find a word in a dictionary.\n");
    printf("5. Delete a dictionary.\n");
    printf("6. Exit.\n");
}

void main() {

    struct Dictionary *ptrDict;
    struct Dictionary *ptrNewDict;
    struct Word *ptrWord;
    int numberOfDicts = 0;
    int selectedDictionaryIndex = -1;

    int x;

    printMenu();
    while (x != 6) {
        scanf("%d", &x);
        switch (x) {
            case 1:
                //Creating dictionary allocation:
                if (numberOfDicts == 0) {
                    ptrDict = (struct Dictionary *) malloc(sizeof(struct Dictionary) * 1);
                    if (ptrDict == NULL) {
                        printf("The creation of the dictionary has failed!\n");
                        exit(EXIT_FAILURE);
                    }
                } else {
                    ptrDict = (struct Dictionary *) realloc(ptrDict, sizeof(struct Dictionary) * (numberOfDicts + 1));
                    if (ptrDict == NULL) {
                        printf("The creation of the dictionary has failed!\n");
                        exit(EXIT_FAILURE);
                    }
                }
                (ptrDict + numberOfDicts)->languages = (char **) malloc(sizeof(char *));
                if ((ptrDict + numberOfDicts)->languages == NULL) {
                    printf("The creation of the dictionary has failed!\n");
                    exit(EXIT_FAILURE);
                }

                addDictionary((ptrDict + numberOfDicts)->languages, &((ptrDict + numberOfDicts)->numOfLanguages));
                (ptrDict + numberOfDicts)->wordList = NULL;
                numberOfDicts++;
                break;
            case 2:
                if (numberOfDicts > 0) {
                    printf("Choose a dictionary:\n");
                    printAllDictionaries(ptrDict, numberOfDicts);
                    selectedDictionaryIndex = selectDictionary(ptrDict) - 1;
                    printSelectedDictionaryName(ptrDict, selectedDictionaryIndex);

                    if ((ptrDict + selectedDictionaryIndex)->wordList == NULL) { //There is no word
                        ptrWord = (struct Word *) malloc(sizeof(struct Word));
                        if (ptrWord == NULL) {
                            printf("The addition of the word has failed!\n");
                            exit(EXIT_FAILURE);
                        }
                        (ptrDict + selectedDictionaryIndex)->wordList = ptrWord;
                    } else {
                        ptrWord = (struct Word *) malloc(sizeof(struct Word));
                        if (ptrWord == NULL) {
                            printf("The addition of the word has failed!\n");
                            exit(EXIT_FAILURE);
                        }
                        struct Word *ptrLastWord;// = (struct Word *) malloc(sizeof(struct Word));

                        ptrLastWord = (ptrDict + selectedDictionaryIndex)->wordList;
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
                    if (ptrWord == NULL) {
                        printf("The addition of the word has failed!\n");
                        exit(EXIT_FAILURE);
                    }
                    ptrWord->next = NULL;
                    addWord((ptrWord)->translations);
                    printf("The word has been added successfully!\n");
//                    free(ptrWord);
                } else {
                    printf("This option is not available right now, try again:\n");
                }
                break;
            case 3:
                if (numberOfDicts > 0) {
                    printf("Choose a dictionary:\n");
                    printAllDictionaries(ptrDict, numberOfDicts);
                    selectedDictionaryIndex = selectDictionary(ptrDict) - 1;
                    if ((ptrDict + selectedDictionaryIndex)->wordList != NULL) {
                        printSelectedDictionaryMainName(ptrDict, selectedDictionaryIndex);
                        ptrWord = (struct Word *) malloc(sizeof(struct Word));
                        if (ptrWord == NULL) {
                            printf("The deletion of the word has failed!\n");
                            exit(EXIT_FAILURE);
                        }
                        char sourceWord[50];
                        scanf("%s", sourceWord);
                        printf("Are you sure? (y/n)\n");
                        char answer[1];
                        scanf("%s", answer);
                        if (answer[0] == 'y') {
                            int k = 0;
                            char *destWord = (ptrDict + selectedDictionaryIndex)->wordList->translations[0];
                            struct Word *ptr_previousWord = (ptrDict + selectedDictionaryIndex)->wordList;
                            ptrWord = (ptrDict + selectedDictionaryIndex)->wordList;
                            while (strcmp(sourceWord, destWord)) {
                                if (!(ptrWord->next)) {//is Last word in linkedList?
                                    printf("Word doesn't found");
                                }
                                ptr_previousWord = ptrWord;
                                ptrWord = ptrWord->next;
                                destWord = ptrWord->translations[0];
                                ++k;
                            }
                            if (k == 0) { //is first word?
                                (ptrDict +
                                 selectedDictionaryIndex)->wordList = NULL; //Means first word deleted in dictionary;
                            }
                            if (k == 1) { //is second word?
                                (ptrDict + selectedDictionaryIndex)->wordList = ptrWord->next;
                                free(ptrWord);
                            } else {
                                ptr_previousWord->next = ptrWord->next;
                                free(ptrWord);
                            }
                        } else {
                            printf("The deletion of the word has been canceled.\n");
                        }
                        printf("The word has been deleted successfully!\n");
                    } else {
                        printf("This option is not available right now, try again:\n");
                    }
                } else {
                    printf("This option is not available right now, try again:\n");
                }
                break;
            case 4:
                if (numberOfDicts > 0) {
                    printf("Choose a dictionary:\n");
                    printAllDictionaries(ptrDict, numberOfDicts);
                    selectedDictionaryIndex = selectDictionary(ptrDict) - 1;
                    if ((ptrDict + selectedDictionaryIndex)->wordList != NULL) {
                        printSelectedDictionaryMainName(ptrDict, selectedDictionaryIndex);
                        char **wrdSearch; // = (char *) malloc(sizeof(char *));
                        char sourceWord[50];
                        scanf("%s", sourceWord);
                        struct Word *ptr_word = (ptrDict + selectedDictionaryIndex)->wordList;

                        char *destWord;// = (char *) malloc(sizeof(char));
                        destWord = ptr_word->translations[0];
                        while (strcmp(sourceWord, destWord)) {
                            if (!ptr_word->next) {
                                printf("There are no translations for '%s' in this dictionary.\n", sourceWord);
                                wrdSearch = NULL;
                                break;
                            }
                            ptr_word = ptr_word->next;
                            destWord = ptr_word->translations[0];
                        }
                        if(strcmp(sourceWord, destWord)){
                            wrdSearch = NULL;
                        } else {
                            wrdSearch = ptr_word->translations;
                        }

                        if (wrdSearch != NULL)
                            printTranslations((ptrDict + selectedDictionaryIndex)->languages,
                                              (ptrDict + selectedDictionaryIndex)->numOfLanguages, wrdSearch);
                    } else {
                        printf("This option is not available right now, try again:\n");
                    }
                } else {
                    printf("This option is not available right now, try again:\n");
                }
                break;
            case 5:
                if (numberOfDicts > 0) {
                    printf("Choose a dictionary:\n");
                    printAllDictionaries(ptrDict, numberOfDicts);
                    selectedDictionaryIndex = selectDictionary(ptrDict) - 1;
                    if (numberOfDicts == 1) {
                        numberOfDicts--;
                        free(ptrDict);//Means All dictionaries are deleted.
                    } else {
                        ptrNewDict = (struct Dictionary *) malloc(sizeof(struct Dictionary) * (numberOfDicts - 1));
                        if (ptrNewDict == NULL) {
                            printf("The deletion of the dictionary has failed!\n");
                            exit(EXIT_FAILURE);
                        }
                        printf("Are you sure? (y/n)\n");
                        char answer[1];
                        scanf("%s", answer);
                        if (answer[0] == 'y') {
                            eraseDictionary(ptrDict, selectedDictionaryIndex, numberOfDicts, ptrNewDict);
                            ptrDict = ptrNewDict;
                            numberOfDicts--;
                        } else {
                            printf("The deletion of the dictionary has been canceled.\n");
                        }
                    }
                } else {
                    printf("This option is not available right now, try again:\n");
                }
                break;
            case 6:
                printf("Bye!");
                free(ptrNewDict);
                free(ptrDict);
                break;

            default:
                printf("Wrong option, try again:\n");
                break;
        }
    }

}
