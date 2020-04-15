#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUM_PICK_SELECT 45
#define PB_PICK_SELECT 15
#define LINE_NUM_COUNT 5
#define ODD_EVEN_1  3
#define FH_SH_1 3
#define SUM_LIMIT_MIN 75
#define SUM_LIMIT_MAX 175
#define SLEEPTIME_FOR_RAND 1
#define HALF_NUM 35

int number_recommendation[NUM_PICK_SELECT];
int pb_recommendation[PB_PICK_SELECT];
int main() {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int status;

    fp = fopen("pick.txt", "r");
    if (fp == NULL)
        exit(1);
    int numbers[LINE_NUM_COUNT];
    int line_count = 0, line_read = 0;
    int num_cnt = 0, pb_count = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        // init local
        for (int i=0; i < LINE_NUM_COUNT; i++) { numbers[i] = 0;}

        // read
        if( ( status = sscanf( line, "%d %d %d %d %d", &numbers[0], &numbers[1], &numbers[2], &numbers[3], &numbers[4] ) ) > 0 ) {
            line_read++;
        }
        if (line_count < (NUM_PICK_SELECT/LINE_NUM_COUNT)) {
            for (int i = 0; i < LINE_NUM_COUNT; i++) {
                number_recommendation[num_cnt++] = numbers[i];
            }
        } else {
          for (int i = 0; i < LINE_NUM_COUNT; i++) {
              pb_recommendation[pb_count++] = numbers[i];
          }
        }

        line_count++;
    }

    int pick_count = 0;
    int pick_num[LINE_NUM_COUNT];
    int pick_pb;

    while (pick_count < LINE_NUM_COUNT) {
        time_t t;

        srand((unsigned)time(&t));
        for(int i = 0;i < LINE_NUM_COUNT; i++){
            pick_num[i] = 0;
            pick_num[i] = number_recommendation[rand()%NUM_PICK_SELECT];
            int j = i-1;
            while (j >= 0) {
                if (pick_num[i] == pick_num[j]) {goto SKIP;}
                j--;
            }
            //printf("%d ", pick_num[i]);

        }
        int odd = 0, even = 0, fh = 0, sh = 0, sum = 0;
        for(int i = 0;i < LINE_NUM_COUNT; i++){
            if (pick_num[i]%2) { odd++; }
            else { even++; }
            if (pick_num[i] <= HALF_NUM) { fh++; }
            else { sh++; }
            sum += pick_num[i];
        }

        if ((odd == ODD_EVEN_1 || even == ODD_EVEN_1) && (fh == FH_SH_1 || sh == FH_SH_1) && (sum > SUM_LIMIT_MIN && sum < SUM_LIMIT_MAX)) {
            pick_count++;
            srand((unsigned)time(&t));
            pick_pb = pb_recommendation[rand()%PB_PICK_SELECT];
            printf("\n");
            for (int i = 0; i < LINE_NUM_COUNT; i++) {
                printf ("%d ", pick_num[i]);
            }
            printf("PB: %d", pick_pb);
        }
SKIP:
        sleep(SLEEPTIME_FOR_RAND);
    }
    printf("\n");

    fclose(fp);
    if (line)
        free(line);
    exit(0);
}
