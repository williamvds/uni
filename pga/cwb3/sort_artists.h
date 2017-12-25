#ifndef SORTART_H
#define SORTART_H

#define inc_pc 0
#define dec_pc 1
#define inc_id 2
#define dec_id 3  // assuming ec_id = dec_id

void print_artists( struct list *a );

struct list *update_counts( struct list *a, struct list *p );

int a_geq_id(void *a, void *b);

int a_leq_pc(void *a, void *b);

void sort_artists( char *artist_file, char *plays_file, int criterion );

#endif
