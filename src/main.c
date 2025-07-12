#include <stdio.h>
#include <sysexits.h>

int main()
{
    const char *header = "HTTP/1.1 200 OK";

    fprintf(stdout, "%s\n", header);

    return EX_OK;
}
