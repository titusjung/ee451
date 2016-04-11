all: p1_serial p1_for p1_sections p2_serial p2_omp

p1_serial: p1_serial.c
	gcc -lrt -fopenmp  p1_serial.c -o p1_serial

p1_for: p1_for.c
	gcc -lrt -fopenmp p1_for.c -o p1_for

p1_sections: p1_sections.c
	gcc -lrt -fopenmp  p1_sections.c -o p1_sections

p2_serial: p2_serial.c
	gcc -lrt -fopenmp p2_serial.c -o p2_serial

p2_omp: p2_omp.c
	gcc -lrt -fopenmp p2_omp.c -o p2_omp
