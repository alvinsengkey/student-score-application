#include <stdio.h>

typedef struct Student{
    char name[100];
    float score;
    char grade;
}students;

char toLetterGrade(float score){
    char grade;
    if(score >= 85 && score <= 100){
        grade = 'A';
    } else if(score >= 70 && score < 85){
        grade = 'B';
    } else if(score >= 60 && score < 70){
        grade = 'C';
    } else if(score >= 55 && score < 60){
        grade = 'D';
    } else {
        grade = 'E';
    }
    return grade;
}

float maximum(float score1, float score2){
    if(score1 > score2){
        score2 = score1;
    }
    return score2;
}

float minimum(float score1, float score2){
    if(score1 > score2){
        score1 = score2;
    }
    return score1;
}

void printData(int num, students student[]){
    for(int i = 0; i < num; i++){
        printf("\n  %s\t|\t%.2f\t|\t%c", student[i].name, student[i].score, student[i].grade);
    }
}

void sortAndPrintAscending(int num, students student[]){
    students temp;
    for(int i = 0; i < num-1; i++){
        for(int j = 0; j < num-i-1; j++){
            if(student[j+1].score < student[j].score){
                temp = student[j+1];
                student[j+1] = student[j];
                student[j] = temp;
            }
        }
    }
    printData(num, student);
}

void sortDescending(int num, students student[]){
    students temp;
    for(int i = 0; i < num-1; i++){
        for(int j = 0; j < num-i-1; j++){
            if(student[j+1].score > student[j].score){
                temp = student[j+1];
                student[j+1] = student[j];
                student[j] = temp;
            }
        }
    }

}

int main(){
    int menu, num;
    float sum = 0, average, maxScore=0, minScore=100;
    students student[999];
    char fileName[100];
    FILE *file;

    printf("\n______________________________________________________________________\n");
    printf("\n- Alvin Sengkey/001202000115 | IT Class-2 - FINAL Exam - C.Prog.-CCAP -\n");
    printf("\n======================================================================\n");
      printf("                       Student Score Menu");
    printf("\n       -------------------             -------------------       \n");

    Menu:
    printf("\n\n  Menu:");
    printf("\n\t[1] ....... Enter New Data (NAME & SCORE)");
    printf("\n\t[2] ....... Calculate AVERAGE Score");
    printf("\n\t[3] ....... Show HIGHEST & LOWEST Score");
    printf("\n\t[4] ....... Sort Scores - ASCENDING");
    printf("\n\t[5] ....... Sort Scores - DESCENDING");
    printf("\n\t[6] ....... SAVE to File (save as)");
    printf("\n\t[7] ....... LOAD from File");
    printf("\n\t[8] ....... PRINT Data");
    printf("\n\t[Other] ... QUIT");
    printf("\n\n  *)type the number to select an option >> ");
    scanf("%d", &menu);

    if(menu == 1){
        sum = 0;
        printf("\n  -[1]- ENTER NEW DATA\n");
        printf("\n  How many students? : ");
        scanf("%d", &num);

        for(int i = 0; i < num; i++){
            printf("\n  (%d/%d) Enter student name\t : ", i+1, num);
            scanf(" %[^\n]s", student[i].name);

            printf("\t Enter valid score\t : ");
            scanf("%f", &student[i].score);
            while(student[i].score < 0 || student[i].score > 100){
                printf("\t enter valid score*\t : ");
                scanf("%f", &student[i].score);
            }

            student[i].grade = toLetterGrade(student[i].score);

            sum += student[i].score;
        }
        average = sum / num;
        goto Menu;

    }else if(menu == 2){
        printf("\n  -[2]- AVERAGE\n");
        printf("\n  Average : %.2f", average);
        goto Menu;

    }else if(menu == 3){
        maxScore=0;
        minScore=100;
        printf("\n  -[3]- HIGHEST & LOWEST\n");

        for(int i = 0; i < num; i++){
            maxScore = maximum(student[i].score, maxScore);
            minScore = minimum(student[i].score, minScore);
        }

        for(int i = 0; i < num; i++){
            if(student[i].score == maxScore){
                printf("\n  Highest score: \t%s,\t%.2f\t(%c)", student[i].name, student[i].score, student[i].grade);
            }
        }
        printf("\n");
        for(int i = 0; i < num; i++){
            if(student[i].score == minScore){
                printf("\n  Lowest score: \t%s,\t%.2f\t(%c)", student[i].name, student[i].score, student[i].grade);
            }
        }
        goto Menu;

    }else if(menu == 4){
        printf("\n  -[4]- SORT ASCENDING\n");

        sortAndPrintAscending(num, student);
        goto Menu;

    }else if(menu == 5){
        printf("\n  -[5]- SORT DESCENDING\n");

        sortDescending(num, student);
        printData(num, student);
        goto Menu;

    }else if(menu == 6){
        printf("\n  -[6]- SAVE AS\n");
        printf("\n  Enter file name (\"fileName.extension\") : ");
        scanf(" %[^\n]s", fileName);

        file = fopen(fileName, "w");

        sortDescending(num, student);
        for(int i = 0; i < num; i++){
            fprintf(file, "%.2f %c %s\n", student[i].score, student[i].grade, student[i].name);
        }

        fclose(file);
        goto Menu;

    }else if(menu == 7){
        printf("\n  -[7]- LOAD FROM\n");
        printf("\n  Enter file name (\"fileName.extension\") to load : ");
        scanf(" %[^\n]s", fileName);

        file = fopen(fileName, "r");

        if(file == NULL){
            printf("\n  FILE NOT FOUND!");
            goto Menu;
        }

        num = 0;
        sum = 0;
        int i = 0;
        fscanf(file, "%f %c %[^\n]s", &student[i].score, &student[i].grade, student[i].name);
        while(!feof(file)){
            printf("\n  %s\t|\t%.2f\t|\t%c", student[i].name, student[i].score, student[i].grade);
            sum += student[i].score;
            num++;

            i++;
            fscanf(file, "%f %c %[^\n]s", &student[i].score, &student[i].grade, student[i].name);
        }
        average = sum/num;

        fclose(file);
        goto Menu;

    }else if(menu == 8){
        printf("\n  -[8]- PRINT\n");

        printData(num, student);
        goto Menu;

    }else {
        printf("\n  ..THANK YOU.. BYE~\n");

    }

    printf("\n======================================================================\n");

    return 0;
}
