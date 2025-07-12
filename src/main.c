#include <stdlib.h>

typedef struct request_line
{
    char *method;
    char *request_target;
    char *http_version;
} RequestLine;

RequestLine *parse_request_line(const char *raw_request_line)
{
    RequestLine *request_line = (RequestLine *)malloc(sizeof(RequestLine));
    if (request_line == NULL)
    {
        return NULL;
    }

    request_line->method = NULL;
    request_line->request_target = NULL;
    request_line->http_version = NULL;

    // TODO: actual parsing

    return request_line;
}

void destroy_request_line(RequestLine *request_line)
{
    if (request_line == NULL)
    {
        return;
    }

    free(request_line->method);
    free(request_line->request_target);
    free(request_line->http_version);
    request_line->method = NULL;
    request_line->request_target = NULL;
    request_line->http_version = NULL;

    free(request_line);
    request_line = NULL;
}

int main()
{
    const char *raw_request_line = "GET /hello HTTP 1.1\r\n";

    RequestLine *request_line = parse_request_line(raw_request_line);
    if (request_line == NULL)
    {
        return EXIT_FAILURE;
    }
    destroy_request_line(request_line);
    request_line = NULL;

    return EXIT_SUCCESS;
}
