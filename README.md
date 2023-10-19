# MacMahon-Problem
MacMahon Problem c++
Temps pour atteindre la solution
Algorithme Séquentielle
4x4
0.004395 sec 


5x5
1.972051 sec 


6x6
14.681739 sec 

Algorithme Avec les threads
4x4
-
5x5
- 
6x6
-


g++ -std=c++11 -pthread main_thread.cpp -o main_thread

g++ main.cpp -Wall -o main.o

g++ Ver.cpp -Wall -o main.o

4x4
Plateau final :
BBBB    BBBB    BBGG    GBBR
BBGB    GBRG    RGBR    BRBB
BBGB    GGRG    RRRB    RBBR
BBRB    RGRB    RBBB    BRBB

5x5:
Plateau final :
GGGR    GGRB    RGRR    RGGB    GGGG
GRRB    RBGR    GRRB    RBBB    BGGB
GBRB    RRGB    GBRR    RBBG    BBGR
GBGB    GBRB    RRBR    BGBB    BRGB
GBGG    GBBG    BRBG    BBGG    GBGG

6x6:
Plateau final :
BBGG    GBBG    BBRR    RBGB    GBGB    GBBB
BGBG    BGGB    GRBR    BBGR    GBRB    RBBB
BGRG    RBBB    BRGB    GRGB    GBRG    RBBR
BGRR    RBGR    GBRG    RBRG    RGBG    BRBR
BRBG    BRGR    GGRG    RGRB    RGGR    GRBB
BGGB    GRGB    GGGB    GBBB    BRBB    BBBB


