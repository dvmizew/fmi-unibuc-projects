/*
    Homework 1 - Divide and Conquer
    This program calculates the iterative sum and pairwise sum of a given set of numbers and compares the error between them. 
    The iterative sum calculates the sum of the numbers by iterating over each element in the array and adding them up. 
    The pairwise sum, on the other hand, divides the array into two halves and recursively calculates the sum of each half, 
    then adds the two sums together.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double iterative_sum(double *vec, size_t number_of_elements) {
    double sum = 0;
    for (size_t i = 0; i < number_of_elements; i++)
        sum += vec[i];
    return sum;
}

double pairwise_sum(double *vec, int left, int right) {
    if (left == right)
        return vec[left];
    else if (left + 1 == right)
        return vec[left] + vec[right];
    else {
        int mid = (left + right) / 2;
        double left_sum = pairwise_sum(vec, left, mid);
        double right_sum = pairwise_sum(vec, mid + 1, right);
        return left_sum + right_sum;
    }
}

int main() {
    size_t number_of_elements;
    char file_name[256];
    printf("Enter the file name:\n");
    scanf("%s", file_name);
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening the file\n");
        return 1;
    }
    if (fscanf(file, "%zu", &number_of_elements) != 1) {
        fprintf(stderr, "Error reading the number of elements from the file\n");
        fclose(file);
        return 1;
    }
    if (number_of_elements < 2) {
        fprintf(stderr, "Error: the number of elements must be at least 2\n");
        fclose(file);
        return 1;
    }
    double *v = (double *) malloc(number_of_elements * sizeof(double));
    if (v == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return -1;
    }

    for (size_t i = 0; i < number_of_elements; i++)
        if (fscanf(file, " %lf", &v[i]) != 1) {
            fprintf(stderr, "Error reading element %zu from the file\n", i + 1);
            fclose(file);
            free(v);
            return 1;
        }

    fclose(file);

    double pairwise_result = 0.0, iterative_result = 0.0, err = 0.0;

    pairwise_result = pairwise_sum(v, 0, number_of_elements - 1);
    iterative_result = iterative_sum(v, number_of_elements);
    err = fabs(iterative_result - pairwise_result);

    printf("Iterative sum = %lf\nPairwise sum = %lf\n", iterative_result, pairwise_result);
    if (pairwise_result != 0.0)
        printf("Error between Iterative sum and Pairwise sum is: %0.30lf\n", err);

    free(v);
    return 0;
}