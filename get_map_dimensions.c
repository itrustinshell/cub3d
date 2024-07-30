# include "cub3d.h"

/*
   una volta che ho lo stringone malloccato, ottenuto dal read_the_map
   questo lo devo riportare in forma di matrice bidimensionale (ovvere char **).

   Se ragioniamo è possibile che la varie linee della mappa abbiano lunghesse diverse. Ma questo è solo in apparenza. 

   Vediamola da wusto punto di vista: quando scrivi una mappa...effettivamente un determinato rigo potrebbe cominicare più tardi nel disegnare un muro e finire ad esempio prima.
   In questo caso avremmo una riga della mappa più stretta rispetto alle altre.
   ma quello che èdavvero strerro è appunto quella rappresentazione di quella riga. 
   Quella riga in se comincia dove cominicano le altre righe del file. Ovvero cominia da sinistra e finisce a destra con un \n.
   Solo che cominicia con spazi vuoti.
   A te quindi serve sapere la lunghezza in altezza e larghezza dove quella in larghezza corrisponde effettivamente alla riga piu' ampia piu che trovi nel tuo file. Per intenderci potrebbe essere anche la riga con un solo muro da rappresetare...ragionando per assurod...ma non importa se è quella piu lunga allora la mappa avra quella larghezza. 
   poi quando si disegnera' per qulela riga verranno riportati spazi non rappresentabili e quell'unico muro rappresentabile.
   tu quindi vai a prendere sempre il mega quadrato in cui ci sta tutta la mappa....poi vai a disegnarla facendo iniziare alcune righe con spazi vuoti se i muri cominiciano piu a sinistra...se cioe' le mappe non sono esattamente quadrati o rettangoli.
  */

/*quindi questa funzione va ad aggiornare dei vlori in lunghezza e ampiezza che utilizzerai fuori da questa funzione per costruire la mappa. Quindi passaimoanche i riferimenti a qei valori..*/
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
