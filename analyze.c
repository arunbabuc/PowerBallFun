#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TOTAL_NUM_RANGE 70
#define PB_RANGE 27
#define RECOMMEND_NUM 60
#define LINE_NUM_COUNT 5
#define HALF_NUM 35
#define COMBINATIONS_DISTR 6
#define SUM_DISTRIBUTION 25
#define TOTAL_SUM 350

// global
int data_count, number_read;
// first 5 numbers
int num_freq[TOTAL_NUM_RANGE];
int num_even_x_odd_y[COMBINATIONS_DISTR];
int num_first_second_half[COMBINATIONS_DISTR];
int num_top10[10];
int total[TOTAL_SUM/SUM_DISTRIBUTION+1];

// power ball
int pb_freq[PB_RANGE];
int pb_even;
int pb_odd;
int pb_first_half;
int pb_sec_half;
int pb_top10[10];

int recommend[RECOMMEND_NUM];

int main() {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int status, odd, even, f_half, s_half, sum;

    fp = fopen("pb_data.txt", "r");
    if (fp == NULL)
        exit(1);
    int numbers[LINE_NUM_COUNT];
    int pb;
    // Read the file and get the info to array
    while ((read = getline(&line, &len, fp)) != -1) {
        // init local temp array
        for (int i=0; i < LINE_NUM_COUNT; i++) { numbers[i] = 0;}
        pb = 0;

        // read line by line
        if( ( status = sscanf( line, "%d %d %d %d %d %d", &numbers[0], &numbers[1], &numbers[2], &numbers[3], &numbers[4], &pb ) ) > 0 ) {
            number_read++;
        }
        data_count++;

        //Calculations - numbers
        odd = 0;
        even = 0;
        f_half = 0;
        s_half = 0;
        sum = 0;
        for (int i = 0; i < LINE_NUM_COUNT; i++) {
            num_freq[numbers[i]]++;
            sum += numbers[i];
            if (numbers[i]%2) {odd++;}
            if (!(numbers[i]%2)) {even++;}
            if (numbers[i] <= HALF_NUM) {
                f_half++;
            } else {
                s_half++;
            }
        }
        total[(sum/SUM_DISTRIBUTION)-1]++;

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
    for (int i = 0; i < TOTAL_NUM_RANGE; i++) {
        if (num_freq[i] > top_freq) { top_freq = num_freq[i];}
    }

    printf ("\n############# 5 numbers(1-%d) #############\n ", TOTAL_NUM_RANGE-1);

    printf ("\nStart========Freq Distribution ===========\n");
    int temp_count = 0;
    int recommend_count = 0;
    printf ("Freq   : Numbers\n");
    for (int top_cnt = top_freq; top_cnt > 0; top_cnt--) {

        temp_count = 0;
        for (int i = 0; i < TOTAL_NUM_RANGE; i++) {
            if (num_freq[i] == top_cnt) { temp_count++;}
        }
        if (temp_count) {
            printf ("%d     :", top_cnt);
        }
        for (int i = 0; i < TOTAL_NUM_RANGE; i++) {
            if (num_freq[i] == top_cnt) {
                printf(" %d", i);
                if (recommend_count < RECOMMEND_NUM) {recommend[recommend_count] = i; recommend_count++;}
            }
        }
        if (temp_count) {
            printf("\n");
        }
    }
    printf ("End==========Freq Distribution ===========\n");

    printf ("\nStart========Sum  Distribution ===========\n");
    for (int i = 0; i < TOTAL_SUM/SUM_DISTRIBUTION; i++) {
        printf ("%d to %d  : %d\n", i*SUM_DISTRIBUTION, (i+1)*SUM_DISTRIBUTION, total[i]);
    }
    printf ("End==========Sum Distribution ===========\n");

    printf ("\nStart========Even-Odd Distrn ===========\n");
    for (int i = 0; i < COMBINATIONS_DISTR; i++) {
        printf ("%d even %d Odd : %d\n", i, LINE_NUM_COUNT-i, num_even_x_odd_y[i]);
    }
    printf ("End==========Even-Odd Distrn ===========\n");

    printf ("\nStart========Value Distrn ===========");
    for (int i = 0; i < COMBINATIONS_DISTR; i++) {
        printf (" \n%d First half %d Second half : %d ", i, LINE_NUM_COUNT-i, num_first_second_half[i]);
    }
    printf ("\nEnd==========Value Distrn ===========\n");

    printf ("\n############# PowerBall(1-%d) #############\n ", PB_RANGE-1);
    int pb_top_freq = 0;
    for (int i = 0; i < PB_RANGE; i++) {
        if (pb_freq[i] > pb_top_freq) { pb_top_freq = pb_freq[i];}
    }
    printf ("\nStart========PB Freq Distribution ===========\n");
    int pb_temp_count = 0;
    int pb_recommend_count = 0;
    printf ("Freq   : Numbers\n");
    for (int top_cnt = pb_top_freq; top_cnt > 0; top_cnt--) {

        pb_temp_count = 0;
        for (int i = 0; i < PB_RANGE; i++) {
            if (pb_freq[i] == top_cnt) { pb_temp_count++;}
        }
        if (pb_temp_count) {
            printf ("%d     :", top_cnt);
        }
        if (pb_temp_count) {
            printf("\n");
        }
    }

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
    for (int i = 0; i < RECOMMEND_NUM; ) {
        for (int j = 0; j < LINE_NUM_COUNT ; j++, i++) {
            printf("%d ", recommend[i]);
        }
        printf("\n");
    }

    exit(0);
}
