#define UNIQUE_NAME_INNER(name, counter) name##counter

#define UNIQUE_NAME_OUTER(name, counter) UNIQUE_NAME_INNER(name, counter)

#define UNIQUE_NAME(name) UNIQUE_NAME_OUTER(name, __COUNTER__)
