
#ifdef __cplusplus
extern "C" {
#endif

#include <ncurses.h>
#include <unistd.h>
#include <term.h>

void ClearScreen()
{
    if (!cur_term)
    {
        int result;
        setupterm( NULL, STDOUT_FILENO, &result );
        if (result <= 0) 
            return;
    }

    putp( tigetstr( "clear" ) );
}

#ifdef __cplusplus
}
#endif
