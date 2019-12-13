#ifndef FILLER_DEFINES_H
# define FILLER_DEFINES_H

# define DEBUG_FD 3
# define RELEASE_FD STDIN_FILENO
//# define INPUT_FD RELEASE_FD
# define INPUT_FD DEBUG_FD

# define DEBUG_OUT_FD STDOUT_FILENO
# define RELEASE_OUT_FD STDERR_FILENO
//# define OUT_FD RELEASE_OUT_FD
# define OUT_FD DEBUG_OUT_FD

# define CMP_SUCCESS 0
# define NOT_SET (-1)

# define PLAYER (-21)
# define ENEMY (0)
# define EMPTY (-42)

# define CANT_PLACE (-1)

# define SHAPE_CHAR '*'
# define EMPTY_CHAR '.'

# define TRUE 1
# define FALSE 0

# define ERR_MALLOC 4
# define ERR_INVALID_INIT_STR 5
# define ERR_INVALID_PLAYER_NUMBER 6
# define ERR_INVALID_MAP_SIZE 7

#endif
