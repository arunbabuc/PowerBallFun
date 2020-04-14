# Power Ball Fun

## What is this?
Just a lazy Sunday evening 1 hour effort. Wanted some software to give recommendation while playing the CA PowerBall lottery. But did not want that recommendation to be a random pick kind of dump one also .. hmm.. so this was born :)

pb_data.txt - is the actual results from 2010 for the CA PowerBall.
analyze - Gives some data from the pb_data.txt
pick - uses the pick.txt for the top numbers picked from last 10 years and uses some hard coded checks to give the recommendation.

NB: Software is not optimized. Its a bit of dirty coding :)

## How to use
### Compile :
* gcc analyze.c -o analyze
* gcc pick.c -o pick

### Run
* ./analyze
* Copy the numbers under
  "*******Recommendation pick.txt"
* pick.txt format
  12x5 (60 numbers)

Example pick.txt:
```
23 32 41 20 28
39 59 12 10 14
45 54 52 7 8
11 16 17 22 36
56 53 3 40 9
29 44 50 57 1
5 13 21 27 30
19 31 49 55 25
47 42 48 6 18
24 13 25 6 8
11 18 19 15 3
7 17 10 12 21
```
* ./pick
