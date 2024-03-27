#ifndef __WRAPPER_H__
#define __WRAPPER_H__

#include <cstddef>

extern "C" {

typedef struct {
  size_t size;
  const char *name;
  const char *path;
} file_t;

typedef struct {
  size_t count;
  size_t size;
  file_t *files;
} storage_t;

const storage_t *storage_get(const char *magnet_uri);
void storage_free(const storage_t *);
}

#endif // __WRAPPER_H__
