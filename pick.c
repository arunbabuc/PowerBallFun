#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int number_recommendation[40];
int pb_recommendation[15];
int main() {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int status;

    fp = fopen("pick.txt", "r");
    if (fp == NULL)
        exit(1);
    int numbers[5];
    int line_count = 0, line_read = 0;
    int num_cnt = 0, pb_count = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        // init local
        for (int i=0; i < 5; i++) { numbers[i] = 0;}

        // read
        if( ( status = sscanf( line, "%d %d %d %d %d", &numbers[0], &numbers[1], &numbers[2], &numbers[3], &numbers[4] ) ) > 0 ) {
            //printf("\n %d-%d-%d-%d-%d : pb-%d", numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], pb);
            line_read++;
        }
        if (line_count < 8) {
            for (int i = 0; i < 5; i++) {
                number_recommendation[num_cnt++] = numbers[i];
            }
        } else {
          for (int i = 0; i < 5; i++) {
              pb_recommendation[pb_count++] = numbers[i];
          }
        }

        line_count++;
    }
    /* Debug
    for (int i = 0; i < 40; ) {
        for (int j = 0; j < 5 ; j++, i++) {
            printf("%d ", number_recommendation[i]);
        }
        printf("\n");
    }
    for (int i = 0; i < 15; ) {
        for (int j = 0; j < 5 ; j++, i++) {
            printf("%d ", pb_recommendation[i]);
        }
        printf("\n");
    } */
    int pick_count = 0;
    int pick_num[5];
    int pick_pb;

    while (pick_count < 5) {
        time_t t;

        srand((unsigned)time(&t));
        for(int i = 0;i < 5; i++){
            pick_num[i] = 0;
            pick_num[i] = number_recommendation[rand()%40];
            int j = i-1;
            while (j >= 0) {
                if (pick_num[i] == pick_num[j]) {goto SKIP;}
                j--;
            }
            //printf("%d ", pick_num[i]);

        }
        int odd = 0, even = 0, fh = 0, sh = 0, sum = 0;
        for(int i = 0;i < 5; i++){
            if (pick_num[i]%2) { odd++; }
            else { even++; }
            if (pick_num[i] <= 35) { fh++; }
            else { sh++; }
            sum += pick_num[i];
        }

        if ((odd == 3 || even == 3) && (fh == 3 || sh == 3) && (sum > 50 && sum < 150)) {
            pick_count++;
            srand((unsigned)time(&t));
            pick_pb = pb_recommendation[rand()%15];
            printf("\n");
            for (int i = 0; i < 5; i++) {
                printf ("%d ", pick_num[i]);
            }
            printf("PB: %d", pick_pb);
        }
SKIP:
        sleep(1);
    }
    printf("\n");

    fclose(fp);
    if (line)
        free(line);
    exit(0);
}
