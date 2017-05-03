all: q11 q12 q21 q22

q11: 1_1.c
	gcc -Wall -std=c99 1_1.c -o p11
q12: 1_2.c
	gcc -Wall -std=c99 1_2.c -o p12
q21: 2_1.c
	gcc -Wall -std=c99 2_1.c -o p21
q22: 2_2.c
	gcc -Wall -std=c99 2_2.c -o p22 -lm
