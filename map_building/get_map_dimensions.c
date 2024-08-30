# include "../c3d.h"

void	get_map_dimensions(char *file_content, int *width, int *height)
{
	int	i;
	int	current_width;
	i = 0;
	current_width = 0;
	*width = 0;
	*height = 0;

	if (file_content)
		*height = 1;
	
	while (file_content[i])
	{
		if (file_content[i] == '\n')
		{
			*height = *height + 1;
			//ricorda che quella riga potrebbe essere piu corta della precedente quindi la larghezza della mappa deve esser quella più lunga trovata sin ora.
			if (*width < current_width)
			{
			*width = current_width;
			current_width = 0;
			}
			else
			{
				current_width = 0;
			}
		}
		else
		{
			current_width++;
		}
		i++;
	}
}
