#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "dictionary.h"
#include "hash.h"
#include "log.h"

#define CHANGE 1
#define HASH_SIZE   (256) 

struct dictionary {
    hash_t* h;
};

static void hello() {
    printf("hello world\n");
    printf("hello world\n");
}

dictionary_t* dictionary_init(void) {
    dictionary_t* dict = calloc(sizeof(dictionary_t), 1);
    if (!dict) {
        XERROR("calloc dictionary fail");
        return NULL;
    }

    /* hash */
    dict->h = hash_init(HASH_SIZE, 0);
    if (!dict->h) {
        XERROR("hash init fail");
        goto _ERR;
    }

    return dict;
_ERR:
    dictionary_deinit(dict);
    return NULL;
}

void dictionary_deinit(dictionary_t* dict) {
    if (dict) {
        hash_deinit(dict->h);
        dict->h = NULL;
        free(dict);
    }
}

int dictionary_count(dictionary_t* dict) {
    assert(dict);
    return hash_count(dict->h);
}


void dictionary_insert(dictionary_t* dict, const char* key, void* value, int value_len) {
    assert(dict);
    hash_insert(dict->h, key, value, value_len);
}

const void* dictionary_value(dictionary_t* dict, const char* key) {
    assert(dict);
    return hash_value(dict->h, key);
}

void dictionary_remove(dictionary_t* dict, const char* key) {
    assert(dict);
    hash_remove(dict->h, key);
}

void dictionary_clear(dictionary_t* dict) {
    assert(dict);
    hash_clear(dict->h);
}

dictionary_t* dictionary_init_with_file(const char* url) {
    return NULL;
}

int dictionary_write_to_file(dictionary_t* dict, const char* url) {
}

#define DICTIONARY_TEST
#ifdef DICTIONARY_TEST
int main(int argc, char* argv[]) {
    dictionary_t* dict = dictionary_init();

    dictionary_insert(dict, "hello", "world", 5);

    const char* value = dictionary_value(dict, "hello");
    XINFO("value=%s\n", value);

    dictionary_deinit(dict);

}
#endif

