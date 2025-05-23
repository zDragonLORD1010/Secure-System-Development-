#ifndef _JSON_H
#define _JSON_H

#define json_char char

#ifndef json_int_t
   #ifndef _MSC_VER
      #include <inttypes.h>
      #define json_int_t int64_t
   #else
      #define json_int_t __int64
   #endif
#endif

#include <stdlib.h>

#ifdef __cplusplus
   #include <string.h>
   extern "C" {
#endif

typedef struct {
   unsigned long max_memory;
   int settings;
   void * (* mem_alloc) (size_t, int zero, void * user_data);
   void (* mem_free) (void *, void * user_data);
   void * user_data;
   size_t value_extra;
} json_settings;

#define json_enable_comments  0x01

typedef enum {
   json_none,
   json_object,
   json_array,
   json_integer,
   json_double,
   json_string,
   json_boolean,
   json_null
} json_type;

extern const struct _json_value json_value_none;

typedef struct _json_object_entry {
    json_char * name;
    unsigned int name_length;
    struct _json_value * value;
} json_object_entry;

typedef struct _json_value {
   struct _json_value * parent;
   json_type type;
   union {
      int boolean;
      json_int_t integer;
      double dbl;
      struct {
         unsigned int length;
         json_char * ptr;
      } string;
      struct {
         unsigned int length;
         json_object_entry * values;
      } object;
      struct {
         unsigned int length;
         struct _json_value ** values;
      } array;
   } u;
   union {
      struct _json_value * next_alloc;
      void * object_mem;
   } _reserved;
   #ifdef JSON_TRACK_SOURCE
      unsigned int line, col;
   #endif
} json_value;

#define json_error_max 128
json_value * json_parse (const json_char * json, size_t length);
json_value * json_parse_ex (json_settings * settings, const json_char * json, size_t length, char * error);
void json_value_free (json_value *);
void json_value_free_ex (json_settings * settings, json_value *);

#ifdef __cplusplus
   }
#endif

#endif
