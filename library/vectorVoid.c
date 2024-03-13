#include <malloc.h>
#include <stdio.h>
#include <string.h>

#include "vectorVoid.h"

// Создание вектора
vectorVoid createVectorV(size_t n, size_t baseTypeSize) {
    vectorVoid vecV;
    if(n == 0) {
        vecV.data = NULL;
        vecV.size = 0;
        vecV.capacity = 0;
        vecV.baseTypeSize = baseTypeSize;
        return vecV;
    }
    vecV.data = malloc(n * sizeof(int));
    if(vecV.data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    vecV.size = 0;
    vecV.capacity = n;
    vecV.baseTypeSize = baseTypeSize;
    return vecV;
}

// Изменение количества памяти
void reserveV(vectorVoid *v, size_t newCapacity) {
    if (newCapacity == 0) {
        free(v->data); // Освобождаем память, если новая вместимость равна 0
        v->data = NULL;
        v->size = 0;
        v->capacity = 0;
    } else if (newCapacity > v->capacity) {
        void *newData = realloc(v->data, newCapacity * v->baseTypeSize);
        if (newData == NULL) {
            fprintf(stderr, "Failed to reallocate memory for the vector\n");
            exit(1);
        }
        v->data = newData;
        v->capacity = newCapacity;
        if (newCapacity < v->size) {
            v->size = newCapacity; // Уменьшаем размер, если новая вместимость меньше текущего размера
        }
    }
}


// Освобождает память, выделенную под неиспользуемые элементы
void shrinkToFitV(vectorVoid *v) {
    v->data = realloc(v->data, v->size * v->baseTypeSize);
    v->capacity = v->size;
}

// Удаление элементов из контейнера, но не освобождает выделенную память
void clearV(vectorVoid *v) {
    v->size = 0;
}

// Освобождает память, выделенную вектору
void deleteVectorV(vectorVoid *v) {
    free(v->data);
    v->capacity = 0;
    v->size = 0;
    v->data = NULL;
}

// Проверка, является ли вектор пустым
bool isEmptyV(vectorVoid *v) {
    return v->size == 0;
}

// Проверка, является ли вектор полным
bool isFullV(vectorVoid *v) {
    return v->size == v->capacity;
}

// Запись значения по адресу destination в index-ый элемент вектора v
void getVectorValueV(vectorVoid *v, size_t index, void *destination) {
    char *source = (char *) v->data + index * v->baseTypeSize;
    memcpy(destination, source, v->baseTypeSize);
}

// Запись значения по адресу source в index-ый элемент вектора v
void setVectorValueV(vectorVoid *v, size_t index, void *source) {
    char *destination = (char *) v->data + index * v->baseTypeSize;
    memcpy(destination, source, v->baseTypeSize);
}

// Удаление последнего элемента из вектора
void popBackV(vectorVoid *v) {
    if(v->size == 0) {
        fprintf(stderr, "vector is empty");
        exit(1);
    }
    v->size--;
}

// Добавление элемента в конец вектора
void pushBackV(vectorVoid *v, void *source) {
    if (v == NULL || source == NULL) {
        return;
    }

    if (v->capacity == v->size) {
        size_t newCapacity = (v->capacity == 0) ? 1 : (v->capacity * 2);
        reserveV(v, newCapacity);
    }

    setVectorValueV(v, v->size, source);
    v->size++;
}

