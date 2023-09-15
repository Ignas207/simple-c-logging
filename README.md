# C logging functions!

- Simple C logging!

## Usage

- Adjust `LOGS_MAX_LENGHT` in `logs.h` to your desired size.
- Only `WriteLogFile(const char* msg, uint32_t len)` needs to be implemented!

- The following functions:

```C
LOG_INFO("We are starting!\n");
LOG_ERROR("This is an error!\n");
LOG_EVENT("This is an event!\n");
```

- Yields:
```
INFO (Core/Src/main.c:122): We are starting!
ERROR (Core/Src/main.c:123): This is an error!
EVENT (Core/Src/main.c:124): This is an event!
```

## Getting the relative path

- If you are using CMake, then add the following to your `CMakeLists`:
```
string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)
add_definitions("-DSOURCE_PATH_SIZE=${SOURCE_PATH_SIZE}")
```

- Otherwise, you can set this manualy.
