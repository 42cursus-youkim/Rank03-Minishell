#ifndef DICT_H
# define DICT_H

# include "type.h"

typedef enum e_dictconfig
{
	DICT_INITIAL_CAPACITY = 32,
	FNV_OFFSET = 14695981039346656037UL,
	FNV_PRIME = 1099511628211UL,
}	t_dictconfig;

typedef enum e_dpad
{
	PAD_SIZE,
	PAD_KEY,
}	t_dpad;

typedef struct s_ditem
{
	char	*key;
	void	*value;
	int		order;
}	t_ditem;

typedef struct s_dict
{
	int		exitcode;
	char	*exitcode_str;
	int		size;
	int		capacity;
	t_ditem	**items;
	t_del_f	del_value;
}	t_dict;

//@func
/*
** < del.c > */

void		no_free(void *data);
t_res		del_ditem(t_dict *dict, int id);
void		del_dict(t_dict *dict);
/*
** < drop.c > */

t_res		dict_drop(t_dict *dict, char *key);
/*
** < expand.c > */

int			dict_expand(t_dict *dict);
/*
** < get.c > */

int			dict_getid(int capacity, char *key);
void		*dict_get(t_dict *dict, char *key);
char		*dict_get_default(t_dict *dict, char *key, char *default_value);
/*
** < hash.c > */

uint64_t	hash_fnv1a(const char *key);
/*
** < new.c > */

t_dict		*new_dict(t_del_f del_value);
t_dict		*new_dict_str(char *key[], char *value[]);
/*
** < print.c > */

void		dict_print(t_dict *dict);
void		dict_print_ordered(t_dict *dict);
/*
** < set.c > */

t_res		dict_set(t_dict *dict, char *key, void *value);
/*
** < status.c > */

bool		is_input_valid(const t_dict *dict, const char *key,
				const void *value);
bool		is_key_vacant(const t_dict *dict, int id);
bool		is_key_update(const t_dict *dict, int id, const char *key);
bool		is_dict_almostfull(const t_dict *dict);
bool		is_capacity_overflow(const t_dict *dict);
/*
** < util.c > */

t_ditem		*new_ditem(const char *key, void *value);
t_ditem		**new_ditem_arr(int capacity);
t_ditem		**new_dict_kv_ordered(t_dict *dict);
#endif