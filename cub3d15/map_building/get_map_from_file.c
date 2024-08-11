#include "../cub3d.h"
static void	test_draw_map(char **map, int width, int heigth)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	printf("start a new stamp\n");
	while(y < heigth)
	{
		x = 0;
		while(x < width)
		{
			printf("%c", map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
printf("finish stamp\n");

}

char	**get_map_from_file(char *file_content, int width, int height)
{
	char	**map;
	int	x;
	int	y;
	int	i;
	int j;
	(void)file_content;
	x = 0;
	y = 0,
	j = 0;
	i = 0;
	map = (char **)malloc((height + 1) * sizeof(char *));
	while (i < height)
	{
		map[i] = (char *)malloc((width + 1) * sizeof(char));
		j = 0;
		while (j < width)
		{
			map[i][j] = ' ';
			j++;
		}
		map[i][j] = '\0'; 
		i++;
	}
	map[height] = NULL;
	
	/*
	sono arrivato a questa funzione effettuando molte prove
	di seguito la spiegazione dettagliata
	*/
	i = 0;
	//mentre y è minore di height. se h è 10 significa che
	//ci sono 10 righe e ovviamente qii si dice miore di 10
	//perchè 10 righe sono rappresentate da 9 digits 
	//in una numerazione che parte da zero
	while (y < height)
	{
		//qui la x riparte sempre da capo
		x = 0;
		/*alla fine ho optato per questa condizione
		perchè fornive più garanzie. Quando ho malloccato la mappa
		ho fatto in modo di azzerare il garbage impostanto un 
		valore di fondo ' ' e poi ho messo un null terminator.
		quindi tutte le righe hanno un null terminator. E quindi posso 
		meglio gestirle facendo riferimento al loro null terminator
		sia cheiaro che terminao tute allo stesso punto.
		Ora però c'è da riflettere sullo stringone che gestisco, ovvero
		il file_contnt. Ebbene questo chiaramente ha menomeoria 
		rispetto a quella del malloc fatto con map. 
		quando lo vedo stampato in un file.cub posso vedere che
		alcune righe vanno a capo prima. hanno cioè uno \n.
		questo dovrò gestirlo nella map...allora so che le righe hanno tutte
		uguale lunghezza e che finiscono con null terminator.
		a questo punto devo solo intercettare, riga per riga
		il \n. Quando lo becco da quel momento faccio teminare la righa della mappa
		fino allo \0....e salto letterlamente lo \n della stringa file_content.*/
		while (map[y][x])
		{
			if (file_content[i] != '\n')
			{
				map[y][x] = file_content[i];
				i++;
			}
			else if (file_content[i] == '\n' && x == width)
				i++;
			else 
			{
				i++;
				while (map[y][x])
					x++;
			}
			x++;
			/*questo era un passaggio che non riuscivo a trovare
			dopo che ho aumentato la x potrei torivarmi in una condizione 
			particolare. ovvero quella in cui la x è il \0 della map
			ebbene se quando ho questo \0, ho anche la \n sul
			file_content, allora semplicemente devo skippare in questo momento
			la \n, altrimenti quando riparte da capo la riga successiva
			mi ritrovo la n\ stampata nella nuova riga della map.*/
			if (file_content[i] == '\n' && !map[y][x])
				i++;
		}
		y++;
	}
	test_draw_map(map, width, height);
	return (map);
}
