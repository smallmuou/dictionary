#ifndef __LOG_H_
#define __LOG_H_

#undef XDEBUG
#define XDEBUG(fmt, ...) do { printf("DEBUG:"fmt"\n", ##__VA_ARGS__); }while(0)

#undef XERROR
#define XERROR(fmt, ...) do { printf("ERROR:"fmt"\n", ##__VA_ARGS__); }while(0)

#undef XINFO
#define XINFO(fmt, ...) do { printf("INFO:"fmt"\n", ##__VA_ARGS__); }while(0)

#endif /* __LOG_H_ */
