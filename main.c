#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

#define ARRAY_SIZE 200



typedef struct Word {
    char** translations;
    struct Word* next;
} Word;

typedef struct Dictionary {
    char** languages;
    int numOfLanguages;
    Word* wordList;
} Dictionary;

typedef struct WordParser {
    int numOfWords;
    int numOfLetters;

} WordParser;

struct WordParser parseWord(char *ptrSentence){

    struct WordParser t_Word = {};

    char val = ptrSentence[0];
    int numOfComma = 0;
    int numOfLetters = 0;

}

void printAllDictionaries(int numOfDicts, struct Dictionary *firstDictPtr){
    char **ptrLangs;
    for (int i = 0; i < numOfDicts; ++i) {
        printf("Dict %d: %p\n", i, firstDictPtr+i);
        ptrLangs = (firstDictPtr+i)->languages;
        int numOfDicts = (firstDictPtr+i)->numOfLanguages;
        for (int j = 0; j < numOfDicts; ++j) {
            if(j == numOfDicts - 1) {
                printf("%s\n", ptrLangs[j]);
            } else {
                printf("%s, ", ptrLangs[j]);
            }
        }
    }
}

int erasingDictionary() {
    int list = 0;
    printf("Choose a dictionary:\n");
    scanf("%d", &list);
    char yes;
    printf("Are you sure? (y/n)\n");
    scanf("%c", &yes);
    if (yes = 'y') {
        printf("The dictionary has been deleted successfully!\n");
    }
    else
        printf("The deletion of the dictionary has been canceled.\n");

}
int wordSearch() {
    printf("Choose a dictionary:\n");
    scanf("%s");
    printf("Enter a word in :\n");
    scanf("%s");
    printf("Enter a word in\n");//anadilde girilmesi gereken kelime
}
int erasingWord() {
    printf("Choose a dictionary:\n");
    scanf("");
    printf("Enter a word in\n");//istenen szolugun ana dilinde kelime isteniyor
    char yes;
    printf("Are you sure? (y/n)\n");
    scanf("%c", &yes);
    if (yes = 'y') {
        printf("The word has been deleted successfully!\n");
    }
    else
        printf("The deletion of the word has been canceled.\n");

}
int addWord() {
    printf("Choose a dictionary:\n");//buraya createdictionaryden var olan sozlukler yapistirilmali
    printf("Enter a word in %s:\n");//seÁilen sozlugunnd ineksine gore
    scanf("");
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

    while(val != '\0') {
        if(val != ','){
            //Counting Letters:
            numOfLangLetter++;
        } else {
            //Language adding:
            char languages[numOfLangLetter+1];
            if(numOfLangLetter > 0) {
                strncpy(languages,&entry[startIndex],numOfLangLetter);
                languages[numOfLangLetter] ='\0';
            }

            printf("Diller: %s\n", languages);
            startIndex += numOfLangLetter + 1;

            //First Language Allocating and Copying:
            ptr_languages[numOfComma] = (char *)malloc(sizeof(char) * numOfLangLetter);
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

        if(val == '\0') {
            char lastLang[numOfLangLetter+1];
            if(numOfLangLetter > 0) { //Burada dil ismi için gerekli diziyi allocate edeceğiz:
                strncpy(lastLang,&entry[startIndex],numOfLangLetter);
                lastLang[numOfLangLetter] ='\0';
            }
            printf("Diller: %s\n", lastLang);

            //First Language Allocating and Copying:
            ptr_languages[numOfComma] = (char *)malloc(sizeof(char) * numOfLangLetter);
            if (ptr_languages[numOfComma]  == NULL) {
                printf("dinamik bir blok elde edilemiyor!\n");
                exit(EXIT_FAILURE);
            }
            strcpy(ptr_languages[numOfComma], lastLang);
            printf("Diller PTR->: %s\n", ptr_languages[numOfComma]);

            //Other languages slots initalizing:
            for (int i = numOfComma+1; i < 5; ++i) {
                ptr_languages[i] = 0;
            }
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

    printf("size: %d\n", sizeof(char));
    struct Dictionary *ptrDict;
    int numberOfDicts = 0;

//////////////////
//    struct Dictionary dict1;
//    char lang1[3] = {'e', 'n', 'g'};
//    char lang2[3] = {'f', 'r', 'a'};
//    char *language[2] = {lang1, lang2};
//    dict1.numOfLanguages = 2;
//    dict1.languages = language;
////////////////////
//    struct Word wrd1;
//    char a[3] = {'a', 's', 'h'}; // "ash,kul"
//    char b[3] = {'k', 'u', 'l'};
//    char *translation[2] = {a, b};
//    wrd1.translations = translation;

    int x;
    printf("Welcome to the dictionaries manager!\n");
    while(x != 6) {
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
                    ptrDict = (struct Dictionary *)malloc(sizeof(struct Dictionary) * 1);
                } else {
                    ptrDict = (struct Dictionary *) realloc(ptrDict, sizeof(struct Dictionary) * (numberOfDicts + 1));
                }
                if (ptrDict == NULL) {
                    printf("can not allocate memory!..\n");
                    exit(EXIT_FAILURE);
                }
                (ptrDict+numberOfDicts)->languages = (char **) malloc(sizeof(char *));
                if ((ptrDict+numberOfDicts)->languages == NULL) {
                    printf("can not allocate memory!..\n");
                    exit(EXIT_FAILURE);
                }

                addDictionary((ptrDict+numberOfDicts)->languages, &((ptrDict+numberOfDicts)->numOfLanguages));
                numberOfDicts++;
                break;
            case 2:

                printf("Choose a dictionary:\n");
                for (int i = 0; i < numberOfDicts; ++i) {
                    printf("%d.", i);
                    for (int j = 0; j < (ptrDict+numberOfDicts)->numOfLanguages; ++j) {
                        printf("%s ", (ptrDict+numberOfDicts)->languages[j]);
                    }
                    printf("\n");
                }
                addWord();
                break;
            case 3:
                erasingWord();
                break;
            case 4:
                wordSearch();
                break;
            case 5:
                erasingDictionary();
                break;
            case 6:
//                getFreeAllMemory(ptrDict, numberOfDicts);
                printf("Bye");
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