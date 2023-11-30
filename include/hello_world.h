#ifndef HELLO_WORLD_H_
#define HELLO_WORLD_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

EXPORT char* hello_world();

EXPORT char* hello_world_foo();

#ifdef __cplusplus
}
#endif

#endif // HELLO_WORLD_H_