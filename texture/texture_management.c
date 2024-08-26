#include "../cub3d.h"


int find_t_color()
{
    int color;
    color = 0;



    return (color);


}

char *get_texture_data_addr(t_my_texture my_texture)
{
    my_texture.data_addr = NULL;

   return (my_texture.data_addr);
}

// char *get_texture_info(t_my_texture *my_texture)
// {
//     // my_texture->dimension.width;
//     // my_texture->dimension.heigth;
//     // my_texture->how_many_colors;
// }

// char *read_texture(char *path)
// {
//     t_my_texture my_texture;


//     return (my_texture.data_addr);
// }



char	*read_texture(char *file_path)
{
	int	fd;
	int	read_bytes;
	int	total_size;
	int	buffer_size;
	char 	buffer[5000];	
	char	*content_file;
	char 	*reallocated_reading;
	
	total_size = 0;
	buffer_size = 5000;
	content_file = malloc(1); /*qui arbitrariamente alloco 1 byte per il contenuto finale che dovrà avere il mio testo
    ovviamente si tratta di una prima allocazione a cui seguirà un realloc di una
    certa nuova quantità, quella di volta in volta indivuduata dalla lettura che procede */
	content_file[0] = '\0'; /*qui abbiamo allocato 1, quinndi esiste solo un elemento nel nostro
    content_file. e lo mettiamo a '\0'*/
	fd = open(file_path, O_RDONLY); /*apriamo il file_path in sola lettura*/
	while((read_bytes = read(fd, buffer, buffer_size - 1)) > 0)
	{
        /*la condizionedl while: mentre i byte_letti sono magiori di zero...significa che 
        la fuznioen read ha letto appunto qualcosa e ha ristetuiro quel numero di bytes
        letti...quando restituisce zero significa che nonha letto nulla ed è finito 
        quanto da leggere*/
		buffer[read_bytes] = '\0'; /*allora qui: sappiamo che ha letto 10 caratteri
        ma sappiamo che la nostra numerazione parte in base zro. quindi abbiamo da 0 a 9 i 10 caratteri letti.
        l'indice 10 corrisponderà quindi al nostro \0*/
		total_size += read_bytes; /*a questo punto iniziamo ad aggiornare il notsto toal_size*/
		/* ora ho quanti byte ho letto e un buffer pieno di questi elementi.

		questo bufferlo posso coipare altrove cosi che non lo perdo.. 
		a tal proposito mi sono fatto un char *content_file. che man mano verra' popolato 
		dei nuovi buffer letti.
	
		rialloco content_file..aumentando la sua dimensione della lettura fatta...
		cosi poi posso ineserire appunto la lettura fatta + un null terminaitor..
		ma attenzione io non devo aumentare degli ultimi bytes_letti...
		io di volta in volta devo allocare dell dimensione totale fin qui letta...
		quinid dovò avere una variabile che mi tiene il conto tale..*/
		reallocated_reading = realloc(content_file, total_size + 1);
		content_file = reallocated_reading;
		content_file[total_size] = '\0';
		strcat(content_file, buffer); /*qui concateno il buffer letto al content file. 
        ora content file, a cui è stata poco fa riallocata la memoria di un tot 
        read_bytes, contiene il contenuto che è stato salvato nel buffer durante
        la lettura. Ecco ora buffer può essere risovrascritto...può essere fatto
        riterminar dinuovo con il null terminator dell'ultima lettura...e puoò essere
        riconcatenato a file content*/
	}
	close(fd);
    printf("read_bytes: %d\n", total_size);
	return (content_file);
}



void scale_texture(t_img *src, t_img *dest, double scale)
{
    int x, y;
    int color;

    for (y = 0; y < dest->img_dimension.heigth; y++)
    {
        for (x = 0; x < dest->img_dimension.width; x++)
        {
            // Calculate the corresponding source coordinates
            double src_x = x / scale;
            double src_y = y / scale;

            // Use the floor function to get the nearest integer pixel in the source
            int src_x_int = (int)floor(src_x);
            int src_y_int = (int)floor(src_y);

            // Check bounds (ensure you don't access outside the source image)
            if (src_x_int >= 0 && src_x_int < src->img_dimension.width && src_y_int >= 0 && src_y_int < src->img_dimension.heigth)
            {
                color = get_pixel(src, src_x_int, src_y_int);
                //printf("aaa color aaa color: %d\n", color);
                put_pixel(dest, x, y, color);
            }
        }
    }
}
