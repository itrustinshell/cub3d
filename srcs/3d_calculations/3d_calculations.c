#include "c3d.h"

/*  1. per ogni punto di impatto va disegnata una linea verticale sullo schermo.
    2. questa linea passa per una determinata ascissa quindi. 
    3. quel punto di impatto è associato ad un ben preciso angolo che è l'angolo del raggio associato.

Ogni raggio che parte dal giocatore rappresenta una specifica direzione 
all'interno del FOV. 
Il raggio colpisce un punto di impatto (dopo aver percorso una certa distanza).
Considerando una persona in generale, quando questa guarda davanti a se ha una vista periferica.
questa vista la chiamiamo FOV: field of view, ovvero campo di vista.
Supponiamo ora di considerare il raggio centrale del FOV (quindi
consideriamo proprio quel raggio che idealmente divide il nostro campo di vista in due pati uguali. 
quello a cui comunemente ci riferiamo con l'espressione guardare dritto davanti a te.)
Questo raggio prima o poi in contra una superfice.
consideriamo ora un raggio alla destra di questo (ache questo rggio inconterò una superfice).
La differenza tra i due raggi p una differenza di un tot angolo.
Se consideriamo questa cosa per tutti i raggi del nostro campo di vista avremo tanti punti di impatto
quanti ne sono i raggi. E questi raggi variano l'uno dall'altro di una certa equidistanza angolare.
Ad esempio se ho un FOV di 90 gradi e voglio rappresentare 90 raggi, ebbene questi saranno
equidistanti tra loro di 1 grado ciascuno (in variaizone angolare).
Attenzione ora a questo passaggio.
La finestra che vedi in cube3d, o la finestra che vedi un un gioco sparatutto, se ci pensi 
rappresenta il tuo FOV. è come se i tuoi occhi fossero sulla superfice dello schermo e tu 
vedessi proprio quello che lo schermo ti fa vedere.
In altre parole si inutisce che c'è una correlazione tra i limiti del tuo FOV ed i limiti destro e sinistro
dello schermo (sicuramente c'è una correlazione anche con i limiti alto e basso dello schermo ma 
non probabilmente non rientrano nelle considerazione di questo progetto).
Per ora io so che su un pinao bidimensionale visto dall'alto, posso rappresentare un player con un certo
campo di vista. Posso rappreentare questo campo di vista con due lineete. E mentre si muove il player io dll'alto vedo che si muove insime 
al suo campo di vista ...avendo quindi la percezinoe di dove sta puntado il giocatore.
Ebbene quel campo di vista portato nella visualizzazione 3D corrisponde ai limiti della finestra del gioco.
Quindi se la finestra è ad esempio di 500 pixel, e il FOV è di 90 gradi, allora queste corrisponderanno.
il margine sinistro della finestra corrisponde al marigne sinistro del fov, il centro al centro e la destr alla destra.
Se dividi la finestra per il numero di raggi che hai scelto, avrai la visualizzazione di ogni raggio su quella finestra.
Questo indica dove dovrà essere disegnato quel raggio.
O meglio dove dovrò essere disegnato il punto di impatto incontrato da quel raggio.
Se il raggio è quello dritto davanti a te....dove tocca toca il muro, che sia a 1 metro, che sia adue metri, che sia a 100 metri
sempre davanti a te viene disegnato.
Stessa cosa vale per tutte i raggi del FOV. I rispetivi punti di impatti saranno disegnati in corrispondenza 
della x della window associata a quel raggio.
 // continuare la spiegazione sotto facendola prosegueire a questa sopra.


la proiezione indica invece l'altezza che dovrà avere quella linea colorata sullo schermo

Quindi:
io ora ho quel punto...
ho angolo di quel raggio che ha incontrao il punto
ho proiezione.
Adesso  devo fare una funzione che riceve il punto, l'angolo e la proiezione....
Questa funzione va a disegnare in una finestra una linea di pixel.
Questa linea è disegnata ad una determinata x di quella finestra che è correlata all'angolo del raggio
....e l'altezza di quella linea sarà di una certa misura correlata alla proiezione individuata

sinifica che i puntini saranno sempre equidistanti perchè i raggi sono equidistanti...
non confonderti con le proiezioni...
tu stai qui considerando le varizioni andgolai.*/

/*i raggi variano dall'estremità sinistra del fov a quella destra
un raggio centrale (bisettrice) corrisponderà a: posizione cenrale finestra
un raggio poco poco piu a sinistra corrisponde alla posizione poco poco piu a sinistra rispetto al centro della finestra...
il limite sinistro del fov coriisponde al margine della finestra.
in altri termini c'è una associazione angolare tra il fov e la width della finestra
per calcolare con quanta percentuale un angolo si trova all'interno del FOV rispetto al "margine sinistor)" */
double  find_x_3d(double ray_angle, double fov_left_ray, double win_width)
{
    double x_3d;
    double angular_fov_percentage;
    double winWidth_angle_proportion;

    angular_fov_percentage = (ray_angle - fov_left_ray) / FOV_ANGLE;
    winWidth_angle_proportion = angular_fov_percentage * win_width;
    x_3d = winWidth_angle_proportion;
    return (x_3d);
}

double calculate_3d_wall_height(double projection)
{
	double line_height;

	line_height = SCALE_FACTOR / projection;
	return (line_height);
}

/*attenzione ora non sto guardando alla x_3d,
non sto calcolando quella x sul piano orizzontale dello schermo corrispondente
alla variazione angolare del ray.
qui sto calcolando la x all'interno della texture...ovvero quella x da cui
risalire lungo lìaltezza della texture da riportare nell'ambiente 3d.
quindi dato un certo punto di impatto...avrò una x...vedo in che cella ricade
vedo quindi a che distanza dall'inizio di quella cella la x si trova, e tento
di riprodurre quella distanza a apartire dall'inizio della texture.
una volta posizionatomi sulla giu
sta x nella textur avrò poi una funzione che mi sale lungo 
quella x...ovvero stessa x ma y diverse....*/
int find_x_texture(t_point impact_point, t_ray ray)
{
    t_point tile_point;
    int x_texture;
    x_texture = 0;
    tile_point = tile_reference(impact_point);
    if (ray.last_increment == INCREMENT_Y)
        x_texture = (impact_point.x - (tile_point.x * TILE_SIZE) ); 
    else 
        x_texture = (impact_point.y - (tile_point.y * TILE_SIZE) );
    //printf("ecco la x_end_point: %f\n", impact_point.x);
    //printf("ecco tile_point.x: %f\n", tile_point.x);
    //printf("ecco la x_texture: %d\n", x_texture);
    return (x_texture);
}






