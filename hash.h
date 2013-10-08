#ifndef __HASH_H_
#define __HASH_H_


struct hash;
typedef struct hash hash_t;

/**
 * @function hash_init
 * @brief init hash
 * @param size[in] hash size
 * @param ignore_case[in] ignore case when compare key. 1 ignore case, 0 case
 * @return NULL if fail, otherwise return hash
 */
hash_t* hash_init(unsigned int size, unsigned char ignore_case);

/**
 * @function hash_deinit
 * @brief deinit hash
 * @param h[in] hash
 * @return void
 */
void hash_deinit(hash_t* h);

/**
 * @function hash_insert
 * @brief insert entry to hash
 * @param h[in] hash
 * @param key[in] key 
 * @param value[in] value
 * @param value_len[in]
 * @return NULL if fail, otherwise return hash
 */
int hash_insert(hash_t* h, const char* key, const void* value, int value_len);

/**
 * @function hash_remove
 * @brief remove a entry in hash for key
 * @param h[in] hash
 * @param key[in] key for hash
 * @return void
 */
void hash_remove(hash_t* h, const char* key);

/**
 * @function hash_clear
 * @brief clear hash entry
 * @param h[in] hash
 * @return void
 */
void hash_clear(hash_t* h);

/**
 * @function hash_value
 * @brief  get value for key
 * @param h[in] hash
 * @param key[in] key for hash
 * @return NULL if fail, otherwise return value
 */
const void* hash_value(hash_t* h, const char* key);

/**
 * @function hash_count
 * @brief init hash
 * @param h[in] hash
 * @return count of hash
 */
int hash_count(hash_t* h);

#endif /* __HASH_H_ */
