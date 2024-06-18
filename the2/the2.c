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

int is_data_array_empty(int* array, int array_size) {
    int i;
    for (i = 0; i < array_size; i++) {
        if (!array[i]) {
            return i;
        }
    }
    return -1;
}

int** initialize_storage(int IA_size, int DA_size, int** DA_sizes) {
    int i;
    int** storage = (int **)calloc(IA_size, sizeof(int *));
    if (!storage) return NULL;
    *DA_sizes = (int *)calloc(IA_size, sizeof(int));
    if (!(*DA_sizes)) {
        free(storage);
        return NULL;
    }
    for (i = 0; i < IA_size; i++) {
        (*DA_sizes)[i] = DA_size;
        storage[i] = (int *)calloc(DA_size, sizeof(int));
        if (!storage[i]) {   
            while (i > 0) {
                i--;
                free(storage[i]);
                storage[i] = NULL;
            }
            free(*DA_sizes);
            *DA_sizes = NULL;
            free(storage);
            storage = NULL;
            return NULL;
        }
    }
    return storage;
}

void print_storage(int** storage, int IA_size, int* DA_sizes) {
    int i;
    if (!storage || !DA_sizes)
    {
        printf("null pointer in print_storage function!!!");
        return;
    }
    for (i = 0; i < IA_size; i++) {
        int n = 0;
        printf("%d ->", i);
        for (n = 0; n < DA_sizes[i]; n++) {
            printf(" %d", storage[i][n]);
        } 
        printf("\n");
    }
}

int double_data_array(int** data_array, int DA_size) {
    int* ptr = (int *)realloc(*data_array, DA_size * 2 * sizeof(int));
    if (ptr)
    {
        int i = 0;
        *data_array = ptr;
        for (i = DA_size; i < DA_size * 2; i++)
        {
            (*data_array)[i] = 0;
        }
        return 1;
    } else
    {
        return 0;
    }
}

void insert(int** storage, int IA_size, const char* name, int* DA_sizes) {
    int name_code = transform_name(name);
    int index = name_code % IA_size;
    int data_array_index = is_data_array_empty(storage[index], DA_sizes[index]);
    if (data_array_index != -1) {
        storage[index][data_array_index] = name_code;
    } else {
        if (double_data_array(&storage[index], DA_sizes[index])) {
            storage[index][DA_sizes[index]] = name_code;
            DA_sizes[index] *= 2;
        } else {
            for (int i = 0; i < IA_size; i++) {
                if (storage[i] != NULL) {
                    free(storage[i]);
                    storage[i] = NULL;
                }
            }
            free(storage);
            storage = NULL;
            free(DA_sizes);
            DA_sizes = NULL;
            printf("unsuccessful reallocation on insert!\n");
        }
    }
}

void insert2(int** storage, int IA_size, int name_code, int* DA_sizes) {
    int index = name_code % IA_size;
    int data_array_index = is_data_array_empty(storage[index], DA_sizes[index]);
    if (data_array_index != -1) {
        storage[index][data_array_index] = name_code;
    } else {
        if (double_data_array(&storage[index], DA_sizes[index])) {
            storage[index][DA_sizes[index]] = name_code;
            DA_sizes[index] *= 2;
        } else {
            for (int i = 0; i < IA_size; i++) {
                if (storage[i] != NULL) {
                    free(storage[i]);
                    storage[i] = NULL;
                }
            }
            free(storage);
            storage = NULL;
            free(DA_sizes);
            DA_sizes = NULL;
            printf("unsuccessful reallocation on insert2!\n");
        }
    }
}

void fill_new_storage(int** storage, int IA_size, int** new_storage, int* DA_sizes, int* new_DA_sizes) {
    int i, j;
    for (i = 0; i < IA_size; i++)
    {
        j = 0;
        for (j = 0; j < DA_sizes[i] && storage[i][j]; j++)
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
    if (extension_rule(*DA_sizes, *IA_size, DA_size)) {
        int i;
        int old_IA_size = *IA_size;
        int* temp_DA_sizes;
        int** temp_storage;
        (*IA_size) *= 2; 
        temp_storage = initialize_storage(*IA_size, DA_size, &temp_DA_sizes);
        if (!temp_storage) {
            printf("alloc fail in temp_storage!!!\n");
            return;
        }
        fill_new_storage(*storage, old_IA_size, temp_storage, *DA_sizes, temp_DA_sizes);
        for (i = 0; i < old_IA_size; i++) {
            free((*storage)[i]);
        }
        free(*storage);
        free(*DA_sizes);
        *storage = temp_storage;
        *DA_sizes = temp_DA_sizes;
    }
}
