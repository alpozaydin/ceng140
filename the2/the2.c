#include<stdio.h>
#include<stdlib.h>

int transform_name(const char name[]) {
    int c = 0, i = 0;
    while (name[i])
    {
        c += (i + 1) * (i + 1) * name[i];
        i++;
    }
    return c;
}


int is_data_array_empty(int* array, int array_size) { /* return -1 if full, return the index to be inserted if empty */
    int i;
    for (i = 0; i < array_size; i++) {
        if (!array[i]) {
            return i;
        }
    }
    return -1;
}


int** initialize_storage(int IA_size, int DA_size, int** DA_sizes) { /* initializing the storage(2D-array structure to store the name codes dynamically) */
    int i;
    int** index_array = (int **)calloc(IA_size, sizeof(int *)); /* allocating the index array */

    if (!index_array) return NULL; /* check if index_array allocated correctly */

    if (*DA_sizes) free(*DA_sizes);
    *DA_sizes = (int *)calloc(IA_size, sizeof(int)); /* allocating array to hold the size(length) of each data array */

    if (!(*DA_sizes)) /*check if DA_sizes array allocated correctly */
    {
        free(index_array);
        return NULL;
    }
    

    for (i = 0; i < IA_size; i++){
        (*DA_sizes)[i] = DA_size;
        index_array[i] = (int *)calloc(DA_size, sizeof(int));
        if (!index_array[i]) /* check if index_array[i] is allocated correctly */
        {
            while (i > 0) /* free all data arrays iteratively, then free data sizes array and index array */
            {
                i--;
                free(index_array[i]);
            }
            free(*DA_sizes);
            free(index_array);
            return NULL;
        }
    }
    return index_array;
}


void print_storage(int** storage, int IA_size, int* DA_sizes) {
    int i;
    for (i = 0; i < IA_size; i++) {
        int n = 0;
        printf("%d ->", i);
        for (n = 0; n < DA_sizes[i]; n++) {
            printf(" %d", storage[i][n]);
        } 
        printf("\n");
    }
}


int double_data_array(int** data_array, int DA_size) { /* take the address of the pointer to the data array -> change it inside the function */
    int* ptr = (int *)realloc(*data_array, DA_size * 2 * sizeof(int));
    if (ptr) /* if reallocating is successful */
    {
        int i = 0;
        *data_array = ptr;
        for (i = DA_size; i < DA_size * 2; i++)
        {
            (*data_array)[i] = 0;
        }
        return 1; /* for successful reallocation */
    } else
    {
        return 0; /* for NULL */
    }
}



void insert(int** storage, int IA_size, const char* name, int* DA_sizes) {
    int name_code = transform_name(name);
    int index = name_code % IA_size;
    int data_array_index = is_data_array_empty(storage[index], DA_sizes[index]);
    if (data_array_index != -1) { /* if empty */
        storage[index][data_array_index] = name_code;
    } else /* data array is full */
    {
        if (double_data_array(&storage[index], DA_sizes[index]))
        {
            storage[index][DA_sizes[index]] = name_code; /* since data_array_index = -1 -> current index = current size of data array */
            DA_sizes[index] *= 2;
        } else /* realloc failed */
        {
            int i;
            for (i = 0; i < IA_size; i++) { /* free all data arrays and index array */
            free(storage[i]);
            }
            free(storage);
            free(DA_sizes); 
            printf("unsuccessful reallocation on insert!\n");
        }
    }
}


void insert2(int**storage, int IA_size, int name_code, int* DA_sizes) {
    int index = name_code % IA_size;
    int data_array_index = is_data_array_empty(storage[index], DA_sizes[index]);
    if (data_array_index != -1) { /* if empty */
        storage[index][data_array_index] = name_code;
        /*printf("empty\n");*/
    } else
    {
        /*printf("full\n");*/
        if (double_data_array(&storage[index], DA_sizes[index]))
        {
            /*printf("%d %d %d\n", index, data_array_index, DA_sizes[index]);*/
            storage[index][DA_sizes[index]] = name_code; /* since data_array_index = -1 -> current index = current size of data array */
            DA_sizes[index] *= 2;
        } else
        {
            int i;
            for (i = 0; i < IA_size; i++) { /* free all data arrays and index array */
            free(storage[i]);
            }
            free(storage);
            free(DA_sizes); 
            printf("unsuccessful reallocation on insert2!\n");
        }
    }
}


void fill_new_storage(int** storage, int IA_size, int** new_storage, int* DA_sizes, int* new_DA_sizes) {
    int i, j;
    /*printf("inside fill func\n");*/
    for (i = 0; i < IA_size; i++) /* iterating through the old storage array */
    {
        j = 0;
        for (j = 0; j < DA_sizes[i]; j++)
        {
            insert2(new_storage, IA_size * 2, storage[i][j], new_DA_sizes);
        }
    } 
}


int extension_rule(int* DA_sizes, int IA_size, int DA_size) {
    int i, sum = 0;
    for (i = 0; i < IA_size; i++)
    {
        sum += DA_sizes[i];
    }
    return sum >= (IA_size * DA_size) * 1.5;
}


void resize_IA(int*** storage, int* IA_size, int DA_size, int** DA_sizes) {
    if (extension_rule(*DA_sizes, *IA_size, DA_size)) { /* extension rule is violated! */
    int i;
        int old_IA_size = *IA_size;
        int* temp_DA_sizes;
        int** temp_storage;
        (*IA_size) *= 2; 
        temp_DA_sizes = (int *)calloc(*IA_size, sizeof(int));
        if (!temp_DA_sizes) printf("alloc fail in temp_DA_sizes\n"); /* check allocation */

        temp_storage = initialize_storage(*IA_size, DA_size, &temp_DA_sizes);
        if (!temp_storage) { /* check allocation */
            free(temp_DA_sizes);
            printf("alloc fail in temp_storage\n");
        }

        fill_new_storage(*storage, old_IA_size, temp_storage, *DA_sizes, temp_DA_sizes);
        for (i = 0; i < old_IA_size; i++) { /* free old arrays */
            free((*storage)[i]);
        }

        free(*storage);
        free(*DA_sizes);
        *storage = temp_storage;
        *DA_sizes = temp_DA_sizes;
    }
}
