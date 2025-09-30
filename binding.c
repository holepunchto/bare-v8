#include <bare.h>
#include <uv.h>

static js_value_t *
bare_v8_heap_statistics(js_env_t *env, js_callback_info_t *info) {
  int err;

  js_heap_statistics_t stats = {
    .version = 1,

    // Since 0
    .total_heap_size = -1,
    .used_heap_size = -1,

    // Since 1
    .external_memory = -1,
  };

  err = js_get_heap_statistics(env, &stats);
  assert(err == 0);

  js_value_t *result;
  err = js_create_object(env, &result);
  assert(err == 0);

#define V(name, property) \
  { \
    if (stats.property != (size_t) -1) { \
      js_value_t *value; \
      err = js_create_int64(env, stats.property, &value); \
      assert(err == 0); \
\
      err = js_set_named_property(env, result, name, value); \
      assert(err == 0); \
    } \
  }

  V("heapTotal", total_heap_size)
  V("heapUsed", used_heap_size)
  V("external", external_memory)
#undef V

  return result;
}

static js_value_t *
bare_v8_exports(js_env_t *env, js_value_t *exports) {
  int err;

#define V(name, fn) \
  { \
    js_value_t *val; \
    err = js_create_function(env, name, -1, fn, NULL, &val); \
    assert(err == 0); \
    err = js_set_named_property(env, exports, name, val); \
    assert(err == 0); \
  }

  V("heapStatistics", bare_v8_heap_statistics)
#undef V

  return exports;
}

BARE_MODULE(bare_v8, bare_v8_exports)
