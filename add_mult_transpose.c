#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

struct matrix {
    int values[100];
    int height;
    int width;
};

// matrix_mult(m1, m2, matrix_product) is a function that takes in 2 matrices 
// and if possible, will perform matrix multiplication on them. the values of  
// the multiplication will be stored in matrix_product's values, and the height
// and width of matrix product will be stored in matrix_product's fields 
// respectively. returns true if the matrix multiplication is successful.
// we doing m1 * m2
// Requires:
//   all pointers are not null
// Effects:
//   May modify matrix_product

bool matrix_mult(const struct matrix *m1, const struct matrix *m2, 
        struct matrix *matrix_product) {
    assert(m1);
    assert(m2);
    assert(matrix_product);
    if (m1->width != m2->height) {
      return false;
    }
    if (m1->height * m1->width > 100) {
      return false;
    }
    matrix_product->height = m1->height;
    matrix_product->width = m2->width;
    for (int i = 0; i < m1->height; ++i) {
      for (int j = 0; j < m2->width; ++j)
      // accessing the ith jth spot on m1 is (i * width + j)
      // for m1 it will be 
        for (int k = 0; k < m2->height; ++k) {
          matrix_product->values[i * m2->width + j] += 
            m1->values[i * m1->width + k] * m2->values[k * m2->width + j];
        } 
      
    }
    
    return true;
}

// matrix_add(m1, m2, matrix_sum) is a function that takes in 2 matrices 
// and if possible, will perform matrix addition on them. The values of  
// the addition will be stored in matrix_sum's values, and the height
// and width of matrix sum will be stored in matrix_sum's fields 
// respectively. returns true if the matrix addition is successful.
//
// Requires:
//   all pointers are not null
// Effects:
//   May modify matrix_sum

bool matrix_add(const struct matrix *m1, const struct matrix *m2, 
        struct matrix *matrix_sum) {
    assert(m1);
    assert(m2);
    assert(matrix_sum);
    if (m1->height != m2->height || m1->width != m2->width) {
      return false;
    }
    if (m1->height * m1->width > 100) {
      return false;
    }
    int items = m1->height * m1->width;
    for (int i = 0; i < items; ++i) {
      matrix_sum->values[i] = m1->values[i] + m2->values[i];
    }
    matrix_sum->width = m1->width;
    matrix_sum->height = m2->height;
    
    return true;
}

// matrix_transpose(m, matrix_transposed) is a function that takes in a matrix m1
// and if possible, will perform a transpose. The results of the transpose
// will be stored in matrix_transposed's values, and the height
// and width of matrix transposition will be stored in matrix_transposed's fields 
// respectively.
//
// Requires:
//   all pointers are not null
// Effects:
//   May modify matrix_transposed
void matrix_transpose(const struct matrix *m, struct matrix *matrix_transposed) {
    assert(m);
    assert(matrix_transposed);
    matrix_transposed->height = m->width;
    matrix_transposed->width = m->height;
    int width = m->width;
    int height = m->height;
    if (height * width > 100) {
      return;
    }
    for (int i = 0; i < width; ++i) {
      for (int j = 0; j < height; ++j) {
        matrix_transposed->values[(i * height) + j] = m->values[(j * width) + i];
      }
    }
}

// print_matrix(m) prints out a matrix.
// effects: Produces output
void print_matrix(struct matrix m) {
    for (int i = 0; i < m.height; i++){
        for (int j = 0; j < m.width; j++){
            printf("%2d ", m.values[(m.width * i) + j] );
        }
        printf("\n");
    }
    printf("\n");
}

int main(void) {
  int retval = -1;
  while(true){
    int height, width;
    int bigarr[50];
    int bigarr2[50];
    char command;

    // Reads in command
    retval = scanf("%c", &command);
    
    if (1 != retval) break;
    
    // Read first matrix
    scanf("%d %d", &height, &width);
    for (int i = 0; i < height * width; i++) {
        scanf("%d", &bigarr[i]);
    }

    struct matrix m1 = {{0}, height, width};
    memcpy(m1.values, bigarr, sizeof(int) * height * width);

    struct matrix the_result = {{0}, 0, 0};
    
    if (command != 't') {
        // Read second matrix
        scanf("%d %d", &height, &width);
        for (int i = 0; i < height * width; i++) {
            scanf("%d", &bigarr2[i]);
        }

        struct matrix m2 = {{0}, height, width};
        memcpy(m2.values, bigarr2, sizeof(int) * height * width);
        
        
      // Matrix addition
      if (command == 'a'){
          if (matrix_add(&m1, &m2, &the_result)) {
              print_matrix(the_result);
          } else {
              printf("Matrix addition not possible.\n");
          }
      } else if (command == 'm') { // Matrix multiplication
          if (matrix_mult(&m1, &m2, &the_result)) {
              print_matrix(the_result);
          } else {
              printf("Matrix multiplication not possible.\n");
          }
      }
    } else if (command == 't') { // Matrix transpose
        matrix_transpose(&m1, &the_result);
        print_matrix(the_result);
    }
  }
}
