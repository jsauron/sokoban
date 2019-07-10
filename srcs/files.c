#include "../includes/sokoban.h"

int     upload_level(int level[][YBLOC])
{
    FILE    *file = NULL;
    char	line_file[XBLOC * YBLOC + 1] = {0};
	int i = 0;
	int j = 0;

	file = fopen("niveaux.lvl", "r");
	if (file == NULL)
		return (0);

	fgets(line_file, XBLOC * YBLOC + 1, file);
	while (i++ < XBLOC)
	{
		while (j++ < YBLOC)
		{
			switch(line_file[(i * XBLOC) + j])
			{
				case '0':
					level[i][j] = 0;
					break;
				case '1':
					level[i][j] = 1;
					break;
				case '2':
					level[i][j] = 2;
					break;
				case '3':
					level[i][j] = 3;
					break;
				case '4':
					level[i][j] = 4;
					break;
			}
		}
	}
	fclose(file);
	return (1);
}

int		save_level(int level[][YBLOC])
{
	FILE	*file = NULL;
	int	i = 0;
	int j = 0;

	file = fopen("niveau.lvl", "w");
	if (file == NULL)
		return (0);
	while (i++ < XBLOC)
	{
		while (j++ < YBLOC)
		{
			fprintf(file,"%d",level[i][j]);
		}
	}
	fclose(file);
	return (1);
}
