#include "minishell.h"

// int	main(void)
int	main(int argc, char *argv[], char *envp[])
{
	(void)argc; (void)argv; (void)envp;
	// create null terminated array with 10 names of people
	const char *arr1[] = {
		"John", "Paul", "George", "Ringo", "Mick",
		"Keith", "Ron", "Charlie", "David", NULL
	};
	// create null terminated array with 20 names of fruits
	const char *arr2[] = {
		"apple", "banana", "cherry", "durian", "elderberry",
		"fig", "grape", "honeydew", "jackfruit", "kiwi",
		"lemon", "mango", "nectarine", "orange", "papaya",
		"quince", "raspberry", "strawberry", "tangerine", "watermelon",
		NULL
	};
	ft_arr_print((char **)arr1);
	ft_arr_print((char **)arr2);
	return (0);
}

/*
	t_dict *dict = new_dict(NULL);
	// set 1 to 11
	dict_set(dict, "1", "value1");
	dict_set(dict, "2", "value2");
	dict_set(dict, "3", "value3");
	dict_set(dict, "4", "value4");
	dict_set(dict, "5", "value5");
	dict_set(dict, "6", "value6");
	dict_set(dict, "7", "value7");
	dict_set(dict, "8", "value8");
	dict_set(dict, "9", "value9");
	dict_set(dict, "10", "value10");
	dict_set(dict, "11", "value11");
	// print

	dict_print(dict);
	char **arr = new_dict_to_arr(dict);
	ft_arr_print(arr);
	del_arr(arr);
	del_dict(dict);
	// t_dict *env = new_env(envp);
	// // dict_print(env);
	// char **new_envp = new_dict_to_arr(env);
	// for (int i = 0; new_envp[i]; i++)
	// 	printf("%s\n", new_envp[i]);
	// del_dict(env);
	// del_arr(new_envp);
	*/