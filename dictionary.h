#ifndef __DICTIONARY_H_
#define __DICTIONARY_H_

struct dictionary;
typedef struct dictionary dictionary_t;

/**
 * @function dictionary_init
 * @brief   init dictionary
 * @param void
 * @return  NULL return if error, otherwise return a dictionary point
 */
dictionary_t* dictionary_init(void);

/**
 * @function dictionary_deinit
 * @brief   deinit dictionary(free resource)
 * @param dict[in] dict to free
 * @return  void
 */
void dictionary_deinit(dictionary_t* dict);

/**
 * @function dictionary_count
 * @brief get item count in dictionary
 * @param dict[in]
 * @return 0 return if error, otherwise return item count
 */
int dictionary_count(dictionary_t* dict);

/**
 * @function dictionary_insert
 * @brief set value for key
 * @param dict[in] dict for set
 * @param key[in] key for set
 * @param value[in] value for set
 * @return  void
 */
void dictionary_insert(dictionary_t* dict, const char* key, void* value, int value_len);

/**
 * @function dictionary_value
 * @brief   get value for key
 * @param dict[in] dictionary
 * @param key[in] key
 * @return  NULL return if not found, otherwise return value
 */
const void* dictionary_value(dictionary_t* dict, const char* key);

/**
 * @function dictionary_remove
 * @brief   remove entry for key
 * @param dict[in] dictionary
 * @param key[in] key
 * @return  void
 */
void dictionary_remove(dictionary_t* dict, const char* key);

/**
 * @function dictionary_clear
 * @brief   remove all object
 * @param dict[in] dictionary
 * @return  void
 */
void dictionary_clear(dictionary_t* dict);

/**
 * @function dictionary_init_with_file
 * @brief   init dictionary with file
 * @param url [in] file url for read
 * @return  NULL return if error, otherwise return a dictionary point
 */
dictionary_t* dictionary_init_with_file(const char* url);

/**
 * @function dictionary_write_to_file
 * @brief  write a dictionary to file
 * @param dict[in] dictionary to write
 * @param url[in] file url to write
 * @return  -1 return if error, otherwise return 0;
 */
int dictionary_write_to_file(dictionary_t* dict, const char* url);

#endif /* __DICTIONARY_H_ */
