#include "resource_collector.h"
#include <pthread.h>
#include <stdlib.h>

void *resource_append(t_resources **collector, void *resource, int type)
{
    t_resources *new_resource;
    t_resources *current;

    new_resource = resource_create(resource, type);
    if (!new_resource)
        return (NULL);
    if (!*collector)
        *collector = new_resource;
    else
    {
        current = *collector;
        while (current->next_resource)
            current = current->next_resource;
        current->next_resource = new_resource;
    }
    return (new_resource);
}

t_resources *resource_create(void *resource, int type)
{
    t_resources *new_resource;

    new_resource = malloc(sizeof(t_resources));
    if (!new_resource)
        return (NULL);

    new_resource->resource_type = type;
    new_resource->resource = resource;
    new_resource->next_resource = NULL;
    return (new_resource);
}

void    release_resources(t_resources **collector)
{
    t_resources *to_release;
    t_resources *temp;

    if (collector)
    {
        if (!*collector)
            return;
        to_release = *collector;
        while (to_release)
        {
            if (to_release->resource_type == RSRC_MUTEX)
                pthread_mutex_destroy((pthread_mutex_t *)to_release->resource);
            else if (to_release->resource_type == RSRC_HEAP)
                free(to_release->resource);
            temp = to_release;
            to_release = to_release->next_resource;
            free(temp);
        }
        *collector = NULL;
    }
}