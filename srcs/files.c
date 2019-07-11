#include "../includes/sokoban.h"

int     upload_map(int **level)
{
    FILE    *file = NULL;
    char	line_file[XBLOC * YBLOC + 1] = {0};
	int i = 0;
	int j = 0;

	file = fopen("niveaux.lvl", "r");
	if (file == NULL)
		return (0);

	fgets(line_file, XBLOC * YBLOC + 1, file);
	while ( i < XBLOC)
	{
    j = 0;
		while (j < YBLOC)
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
      j++;
		}
    i++;
	}
	fclose(file);
	return (1);
}

int		save_level(int **level)
{
	FILE	*file = NULL;
	int	 x = 0;
	int y = 0;

	file = fopen("niveau.lvl", "w");
	if (file == NULL)
		return (0);
	while (y < YBLOC)
	{
    x = 0;
		while (x < XBLOC)
		{
			fprintf(file,"%d",level[y][x]);
		  x++;
    }
    y++;
	}
	fclose(file);
	return (1);
}
