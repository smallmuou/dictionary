#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "hash.h"
#include "log.h"

#define KEY_MAX_LEN     (256)


struct hash_entry {
    char key[KEY_MAX_LEN];
    void* value;
    struct hash_entry* next;
};
typedef struct hash_entry hash_entry_t;

static hash_entry_t* hash_entry_init(const char* key, const void* value, int value_len) {
    assert(key);

    hash_entry_t* entry = (hash_entry_t* )calloc(sizeof(hash_entry_t), 1);
    if (!entry) {
        XERROR("calloc entry fail");
        return NULL;
    }

    strncpy(entry->key, key, sizeof(entry->key));

    /* value */
    if (value && value_len > 0) {
        entry->value = calloc(sizeof(unsigned char), value_len);
        memcpy(entry->value, value, value_len);
    }

    return entry;
}

static void hash_entry_deinit(hash_entry_t* entry) {
    if (entry) {
        if (entry->value) free(entry->value);
        free(entry);
    }
}

struct hash {
    unsigned int count;
    unsigned int size;
    unsigned char ignore_case;
    hash_entry_t** array;
};

static void strupper(char* src) {
    if (!src) return;
    while (*src) {
        *src = toupper(*src);
        src++;
    }
}

unsigned int strhash(const char* key, unsigned int size, int ignore_case) {
    int i, l;
    unsigned long ret = 0;
    unsigned short *s;
    char* src = NULL;
    int len = 0;

    if (!key || size <= 0) return 0;

    len = strlen(key)+1;
    src = calloc(sizeof(char), strlen(key)+1);
    strncpy(src , key, len);

    /* case */
    if (ignore_case) {
        strupper(src);
    }

    l = (strlen(src) + 1) / 2;
    s = (unsigned short *)src;

    for (i = 0; i < l; i++) 
        ret ^= s[i]<<(i&0x0f);

    return ret%(size-1);
}

hash_t* hash_init(unsigned int size, unsigned char ignore_case) {
    assert(size > 0);
    hash_t* h = (hash_t* )calloc(sizeof(hash_t), 1);
    if (!h) { 
        XERROR("calloc hash fail");
        return NULL;
    }

    h->array = (hash_entry_t** )calloc(sizeof(hash_entry_t* ), size);
    if (!h->array) {
        XERROR("calloc array fail");
        goto _ERR;
    }

    h->size = size;
    h->ignore_case = ignore_case;

    return h;

_ERR:
    hash_deinit(h);
    return NULL;
}

void hash_clear(hash_t* h) {
    if (!h) return;

    if (h->array) {
        int i = 0;
        for (i = 0; i < h->size; i++) {
            hash_entry_t* e = h->array[i];
            while (e) {
                hash_entry_t* p = e;
                e = e->next;
                hash_entry_deinit(p);
                h->count--;
            }
        }
        free(h->array);
        h->array = NULL;
    }
}

void hash_deinit(hash_t* h) {
    if (h) {
        hash_clear(h);
        free(h);
    }
}

int hash_insert(hash_t* h, const char* key, const void* value, int value_len) {
    if (!h || !key ||!value) return -1;

    unsigned int index = strhash(key, h->size, h->ignore_case);
    hash_entry_t* entry = hash_entry_init(key, value, value_len);

    if (entry) {
        /* insert to header */
        hash_entry_t* header = h->array[index];
        entry->next = header;
        h->array[index] = entry;

        h->count++;
        return 0;
    }
    return -1;
}

static hash_entry_t* hash_find(hash_t* h, const char* key, hash_entry_t** parent, unsigned int *index) {
    assert(h && key);

    unsigned int idx = strhash(key, h->size, h->ignore_case);
    hash_entry_t* header = h->array[idx];
    int ret = 0;

    if (index) *index = idx;
    if (parent) *parent = NULL;

    while(header) {
        if (h->ignore_case) {
            ret = strcasecmp(key, header->key);
        } else {
            ret = strcmp(key, header->key);
        }

        if (!ret) {
            return header;
        }

        if (parent) *parent = header;
        header = header->next;
    }

    return NULL;
}

void hash_remove(hash_t* h, const char* key) {
    hash_entry_t* parent = NULL;
    unsigned int index = 0;
    hash_entry_t* entry = hash_find(h, key, &parent, &index);

    if (entry) {
        if (parent) {
            parent->next = entry->next;
        } else {
            h->array[index] = entry->next;
        }
        h->count--;
        hash_entry_deinit(entry);
    }
}


const void* hash_value(hash_t* h, const char* key) {
    hash_entry_t* entry = hash_find(h, key, NULL, NULL);
    if (entry) return entry->value;
    return NULL;
}

int hash_count(hash_t* h) {
    return h ? h->count : 0;
}

//#define HASH_TEST
#ifdef HASH_TEST
int main(int argc, char* argv[]) {
    hash_t* h = hash_init(100, 1);
    int i = 0;

    char* buf[] = {
        "Allow"
            ,"Content-Encoding"
            ,"Content-Language"
            ,"Content-Length"
            ,"Content-Location"
            ,"Content-MD5"
            ,"Content-Range"
            ,"Content-Type"
            ,"Content-Expires"
            ,"Last-Modified"
            ,"Cache-Control"
            ,"Connection"
            ,"Date"
            ,"Pragma"
            ,"Transfer-Encoding"
            ,"Update"
            ,"TRAILER"
            ,"Via"
            ,"Accept"
            ,"Accept-Charset"
            ,"Accept-Encoding"
            ,"Accept-Language"
            ,"Authorization"
            ,"Expect"
            ,"From"
            ,"Host"
            ,"If-Modified-Since"
            ,"If-Match"
            ,"If-None-Match"
            ,"If-Range"
            ,"If-Unmodified-Since"
            ,"Max-Forwards"
            ,"Proxy-Authorization"
            ,"Range"
            ,"Referer"
            ,"TE"
            ,"User-Agent"
            ,"Accept-Ranges"
            ,"Age"
            ,"ETag"
            ,"Location"
            ,"Retry-After"
            ,"Server"
            ,"Vary"
            ,"Warning"
            ,"WWW-Authenticate"
            ,"Set-Cookie"
            ,NULL
    };

    XINFO("hash count=%d", hash_count(h));

    /* insert */
    {
        XINFO("======================insert=======================");
        while (buf[i]) {
            hash_insert(h, buf[i], buf[i], strlen(buf[i]));
            i++;
        }

        XINFO("hash count=%d", hash_count(h));
    }

    /* get known value */
    {
        XINFO("=====================get value===================");
        i = 0;
        while (buf[i]) {
            const char* value = hash_value(h, buf[i]);
            XINFO("key=%s, value=%s", buf[i],  value ? value:"");
            i++;
        }
    }

    /* remove */
    {
        i = 3;
        XINFO("=====================remove  ===================");
        hash_remove(h, buf[i]);

        XINFO("remove key:%s\n", buf[i]);
        XINFO("hash count=%d", hash_count(h));

        const char* value = hash_value(h, buf[i]);
        XINFO("key=%s, value=%s", buf[i],  value ? value:"");
    }

    /* get unknown value */
    {
        XINFO("=====================unknown key===================");
        const char* key = "TEST KEY";
        const char* value = hash_value(h, key);
        XINFO("key=%s, value=%s", key,  value ? value:"");

        key = "Set-cookie";
        value = hash_value(h, key);
        XINFO("key=%s, value=%s", key,  value ? value:"");

    }

    /* clear */
    {
        XINFO("=====================clear===================");
        hash_clear(h);
        XINFO("hash count=%d", hash_count(h));
    }

    XINFO("=====================deinit===================");
    hash_deinit(h);
    return 0;
}
#endif

