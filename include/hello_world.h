#ifndef CMAKE_LIBRARY_TEMPLATE_HELLO_WORLD_H_
#define CMAKE_LIBRARY_TEMPLATE_HELLO_WORLD_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

EXPORT char* hello_world();

#ifdef __cplusplus
}
#endif

#endif // CMAKE_LIBRARY_TEMPLATE_HELLO_WORLD_H_