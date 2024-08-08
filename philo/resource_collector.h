#ifndef RESOURCE_COLLECTOR_H
# define RESOURCE_COLLECTOR_H

/*--- STRUCTS ---*/

enum e_resource_codes
{
	RSRC_MUTEX,
	RSRC_HEAP
};

typedef struct s_collector
{
	int					resource_type;
	void				*resource;
	struct s_collector	*next_resource;
}	t_resources;

void	*resource_append(t_resources **collector, void *resource, int type);
void	release_resources(t_resources **collector);

#endif // !RESOURCE_COLLECTOR_H