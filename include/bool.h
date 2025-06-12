#ifndef BOOL_H
#define BOOL_H

#ifndef NOT
#define NOT !
#endif

#ifndef AND
#define AND &&
#endif

#ifndef OR
#define OR ||
#endif

#ifndef IS
#define IS ==
#endif

#ifndef ISNT
#define ISNT !=
#endif

typedef enum { FALSE, TRUE } bool;

#endif