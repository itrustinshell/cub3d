#include "../cub3d.h"

/* this function receives a "file path",
opens it, reads it, saves its content in a malloced string
and finally returns this string.
First of all it opens the file using open() with READ_ONLY options.
This functions allow us to know the fd (file descriptor) to pass to read function.
We can then read the file using read(), which returns the number of bytes read! 
To remember: read requires as parameters: the fd, the buffer where to temporary memorize what has been read,and the dimension of the buffer.
when i call read I make it read for a total of (buffer_Size -1) so that the last byte of buffer can be reserved to null terminator \0.
After one reading, buffer could be full or it could be not completely full...i will know this info thanks to read_bytes returned by read();
So even if buffer is not completely full..I can know how manu bytes of buffer have been actually filled during the reading;
This means that I can put a null terminator exactly at the end of the reading. With buffer[read_bytes] = \0
 */

char	*read_the_map(char *file_path)
{
	int	fd;
	int	read_bytes;
	int	total_size;
	int	buffer_size;
	char 	buffer[1024];	
	char	*content_file;
	char 	*reallocated_reading;
	
	total_size = 0;
	buffer_size = 1024;
	content_file = malloc(1);
	content_file[0] = '\0';
	fd = open(file_path, O_RDONLY);

	while((read_bytes = read(fd, buffer, buffer_size - 1)) > 0)
	{
		buffer[read_bytes] = '\0';
		total_size += read_bytes;
		/* ora ho quanti byte ho letto e un buffer pieno di questi elementi.

		questo bufferlo posso coipare altrove cosi che non lo perdo.. 
		a tal proposito mi sono fatto un char *content_file. che man mano verra' popolato 
		dei nuovi buffer letti.
	
		rialloco content_file..aumentando la sua dimensione della lettura fatta...
		cosi poi posso ineserire appunto la lettura fatta + un null terminaitor..
		ma attenzione io non devo aumentare degli ultimi bytes_letti...
		io di volta in volta devo allocare dell dimensione totale fin qui letta...
		quinid dovò avere una variabile che mi tiene il conto tale..*/
		reallocated_reading = realloc(content_file, total_size);
		content_file = reallocated_reading;
		content_file[total_size] = '\0';
		strcat(content_file, buffer);
	}
	close(fd);
	return (content_file);
}

void build_map(char *path, t_c3d *c3d)	
{	
	c3d->raw_map.data = read_the_map(path);
	get_map_dimensions(c3d->raw_map.data, &c3d->raw_map.dimension.width, &c3d->raw_map.dimension.heigth);
	c3d->raw_map.grid = get_map_from_file(c3d->raw_map.data, c3d->raw_map.dimension.width, c3d->raw_map.dimension.heigth);
}