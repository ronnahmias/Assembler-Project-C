#ifndef MAMAN14_SHARED_DATA_H
#define MAMAN14_SHARED_DATA_H

typedef struct dataNode {
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

#endif //MAMAN14_SHARED_DATA_H
