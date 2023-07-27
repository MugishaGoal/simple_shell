#include "shell.h"

int (*get_builtins(char *command))(char **args, char **front);
int shell_exit(char **args, char **front);
int shell_cd(char **args, char __attribute__((__unused__)) **front);
int shell_help(char **args, char __attribute__((__unused__)) **front);

/**
 * get_builtin - The function matches the given command with a corresponding
 * shell builtin function.
 * @command: The command to match.
 *
 * Return: A function pointer to the corresponding builtin.
 */
int (*get_builtins(char *command))(char **args, char **front)
{
	builtin_t funcs[] = {
		{ "exit", shell_exit },
		{ "env", shell_env },
		{ "setenv", shell_setenv },
		{ "unsetenv", shell_unsetenv },
		{ "cd", shell_cd },
		{ "alias", shell_alias },
		{ "help", shell_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (_strcmp(funcs[i].name, command) == 0)
			break;
	}
	return (funcs[i].f);
}

/**
 * shell_exit - The function of exiting the shell.
 * @args: An array of arguments with the exit value.
 * @front: A double pointer to the starting args.
 *
 * Return: If there are no arguments - -3.
 *         If the given exit value is invalid - 2.
 *         O/w - exits with the given status value.
 *
 * Description: In return of -3, the program 
 * exits back in the main function.
 */
int shell_exit(char **args, char **front)
{
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);
	int i;
	int length_int = 10;

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			length_int++;
		}
		for (; args[0][i]; i++)
		{
			if (i <= length_int && args[0][i] >= '0' && args[0][i] <= '9')
				num = (num * 10) + (args[0][i] - '0');
			else
				return (create_error(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (create_error(--args, 2));
	args -= 1;
	free_args(args, front);
	free_env();
	free_alias_list(aliases);
	exit(num);
}

/**
 * shell_cd - Changes the current directory of the shell process
 * @args: An array of arguments
 * @front: A double pointer to the starting args
 *
 * Return: If the given string is not a directory - 2
 * If an error occurs - -1
 * Otherwise - 0
 */
int shell_cd(char **args, char __attribute__((__unused__)) **front)
{
	char **dir_info;
	char *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (shell_setenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (shell_setenv(dir_info, dir_info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_info);
	return (0);
}

/**
 * shell_help - Displays information about shell builtin commands.
 * @args: An array of arguments.
 * @front: A pointer to the starting args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shell_help(char **args, char __attribute__((__unused__)) **front)
{
	char *name = args[0];

	if (!args[0])
		helper_all();
	else if (_strcmp(args[0], "alias") == 0)
		helper_alias();
	else if (_strcmp(args[0], "cd") == 0)
		helper_cd();
	else if (_strcmp(args[0], "exit") == 0)
		helper_exit();
	else if (_strcmp(args[0], "env") == 0)
		helper_env();
	else if (_strcmp(args[0], "setenv") == 0)
		helper_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		helper_unsetenv();
	else if (_strcmp(args[0], "help") == 0)
		helper_help();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}
