#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct RequestLine
{
    char *method;
    char *request_target;
    char *http_version;
} RequestLine;

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

void print_request_line(const RequestLine *request_line)
{
    fprintf(stdout, "%s %s %s\n", request_line->method, request_line->request_target, request_line->http_version);
}

int parse_method(const char *raw_value, const int raw_length, char **output)
{
    // Check and initialize output
    if (output == NULL)
    {
        // TODO: error message
        return -1;
    }
    *output = NULL;

    // Check raw value and length
    if (raw_value == NULL || raw_length <= 0)
    {
        // TODO: error message
        return -1;
    }

    // Find first space
    int space_index = -1;

    for (int i = 0; i < raw_length; i++)
    {
        if (raw_value[i] == ' ')
        {
            space_index = i;
            break;
        }
    }

    if (space_index <= 0)
    {
        // TODO: error message
        return -1;
    }

    const int method_length = space_index;

    // Allocate output
    *output = (char *)malloc((method_length + 1) * sizeof(char));
    if (*output == NULL)
    {
        // TODO: error message
        return -1;
    }

    // Copy content
    memcpy(*output, raw_value, method_length * sizeof(char));

    // Place null terminator
    (*output)[method_length] = '\0';

    return space_index;
}

RequestLine *parse_request_line(const char *raw_value)
{
    // Check raw value
    if (raw_value == NULL)
    {
        // TODO: error message
        return NULL;
    }

    // Allocate request line
    RequestLine *request_line = (RequestLine *)malloc(sizeof(RequestLine));
    if (request_line == NULL)
    {
        // TODO: error message
        return NULL;
    }

    request_line->method = NULL;
    request_line->request_target = NULL;
    request_line->http_version = NULL;

    // Parse and assign elements
    const int raw_length = strlen(raw_value);

    if (parse_method(raw_value, raw_length, &request_line->method) == -1)
    {
        destroy_request_line(request_line);
        return NULL;
    }

    // TODO: parse request target
    // TODO: parse http version

    return request_line;
}

int main()
{
    const char *raw_request_line = "GET /hello HTTP 1.1\r\n";

    RequestLine *request_line = parse_request_line(raw_request_line);
    if (request_line == NULL)
    {
        return EXIT_FAILURE;
    }
    print_request_line(request_line);
    destroy_request_line(request_line);

    return EXIT_SUCCESS;
}
