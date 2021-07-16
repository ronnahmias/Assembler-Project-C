#ifndef MAMAN14_SHARED_DATA_H
#define MAMAN14_SHARED_DATA_H

typedef struct {
    int address;
    struct dataNode *next;
    union {
        char db;
        struct {
            long dw:32;
        };
        struct {
            int dh:16;
        };
    };
}dataNode;

typedef struct {
    int size;
    char * string;

}asciz_row;

#endif //MAMAN14_SHARED_DATA_H
