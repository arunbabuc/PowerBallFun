#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// global
int data_count, number_read;
// first 5 numbers
int num_freq[70];
int num_even_x_odd_y[6];
int num_first_second_half[6];
int num_top10[10];
int total[8];

// power ball
int pb_freq[27];
int pb_even;
int pb_odd;
int pb_first_half;
int pb_sec_half;
int pb_top10[10];

int recommend[40];
int pb_recommend[15];

int main() {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int status, odd, even, f_half, s_half, sum;

    fp = fopen("pb_data.txt", "r");
    if (fp == NULL)
        exit(1);
    int numbers[5];
    int pb;
    while ((read = getline(&line, &len, fp)) != -1) {
        // init local
        for (int i=0; i < 5; i++) { numbers[i] = 0;}
        pb = 0;

        // read
        if( ( status = sscanf( line, "%d %d %d %d %d %d", &numbers[0], &numbers[1], &numbers[2], &numbers[3], &numbers[4], &pb ) ) > 0 ) {
            //printf("\n %d-%d-%d-%d-%d : pb-%d", numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], pb);
            number_read++;
        }
        //printf("==> %s", line);
        data_count++;

        //Calculations - numbers
        odd = 0;
        even = 0;
        f_half = 0;
        s_half = 0;
        sum = 0;
        for (int i = 0; i < 5; i++) {
            num_freq[numbers[i]]++;
            sum += numbers[i];
            if (numbers[i]%2) {odd++;}
            if (!(numbers[i]%2)) {even++;}
            if (numbers[i] <= 35) {
                f_half++;
            } else {
                s_half++;
            }
        }
        total[(sum/50)-1]++;

        num_first_second_half[f_half]++;
        num_even_x_odd_y[even]++;

        //Calculations - pb
        pb_freq[pb]++;
        if (pb % 2) {
            pb_odd++;
        } else {
            pb_even++;
        }
        if (pb <= 13) {
            pb_first_half++;
        } else {
            pb_sec_half++;
        }
    }
    fclose(fp);
    if (line)
        free(line);

    printf("\n Total data count : %d\n", data_count);
    printf("\n Total read count : %d\n", number_read);

    // Find top count
    int top_freq = 0;
    for (int i = 0; i < 70; i++) {
        if (num_freq[i] > top_freq) { top_freq = num_freq[i];}
    }

    printf ("\n############# 5 numbers(1-69) #############\n ");

    printf ("\nStart========Freq Distribution ===========\n");
    int temp_count = 0;
    int recommend_count = 0;
    printf ("Freq   : Numbers\n");
    for (int top_cnt = top_freq; top_cnt > 0; top_cnt--) {

        temp_count = 0;
        for (int i = 0; i < 70; i++) {
            if (num_freq[i] == top_cnt) { temp_count++;}
        }
        if (temp_count) {
            printf ("%d     :", top_cnt);
        }
        for (int i = 0; i < 70; i++) {
            if (num_freq[i] == top_cnt) {
                printf(" %d", i);
                if (recommend_count < 40) {recommend[recommend_count] = i; recommend_count++;}
            }
        }
        if (temp_count) {
            printf("\n");
        }
    }
    printf ("End==========Freq Distribution ===========\n");

    printf ("\nStart========Sum  Distribution ===========\n");
    for (int i = 0; i < 7; i++) {
        printf ("%d to %d  : %d\n", i*50, (i+1)*50, total[i]);
    }
    printf ("End==========Sum Distribution ===========\n");

    printf ("\nStart========Even-Odd Distrn ===========\n");
    for (int i = 0; i < 6; i++) {
        printf ("%d even %d Odd : %d\n", i, 5-i, num_even_x_odd_y[i]);
    }
    printf ("End==========Even-Odd Distrn ===========\n");

    printf ("\nStart========Value Distrn ===========");
    for (int i = 0; i < 6; i++) {
        printf (" \n%d First half %d Second half : %d ", i, 5-i, num_first_second_half[i]);
    }
    printf ("\nEnd==========Value Distrn ===========\n");

    printf ("\n############# PowerBall(1-26) #############\n ");
    int pb_top_freq = 0;
    for (int i = 0; i < 27; i++) {
        if (pb_freq[i] > pb_top_freq) { pb_top_freq = pb_freq[i];}
    }
    printf ("\nStart========PB Freq Distribution ===========\n");
    int pb_temp_count = 0;
    int pb_recommend_count = 0;
    printf ("Freq   : Numbers\n");
    for (int top_cnt = pb_top_freq; top_cnt > 0; top_cnt--) {

        pb_temp_count = 0;
        for (int i = 0; i < 27; i++) {
            if (pb_freq[i] == top_cnt) { pb_temp_count++;}
        }
        if (pb_temp_count) {
            printf ("%d     :", top_cnt);
        }
        for (int i = 0; i < 27; i++) {
            if (pb_freq[i] == top_cnt) {
                printf(" %d", i);
                if (pb_recommend_count < 15) {pb_recommend[pb_recommend_count] = i; pb_recommend_count++;}
              }
        }
        if (pb_temp_count) {
            printf("\n");
        }
    }
    printf("\n*******Recommendation pick.txt \n");

    printf ("End==========PB Freq Distribution ===========\n");

    printf ("\nStart========PB Even-Odd Distrn ===========\n");
    printf("PB Even : %d\n", pb_even);
    printf("PB Odd  : %d\n", pb_odd);
    printf ("End==========PB Even-Odd Distrn ===========\n");

    printf ("\nStart========PB Value Distrn ===========\n");
    printf("PB First-half(1-13)    : %d\n", pb_first_half);
    printf("PB Second-half(14-26)  : %d\n", pb_sec_half);
    printf ("End==========PB Value Distrn ===========\n");

    printf("\n\n*******Recommendation pick.txt \n");
    for (int i = 0; i < 40; ) {
        for (int j = 0; j < 5 ; j++, i++) {
            printf("%d ", recommend[i]);
        }
        printf("\n");
    }
    for (int i = 0; i < 15; ) {
        for (int j = 0; j < 5 ; j++, i++) {
            printf("%d ", pb_recommend[i]);
        }
        printf("\n");
    }

    exit(0);
}
