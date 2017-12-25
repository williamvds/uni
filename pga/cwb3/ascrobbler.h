#ifndef ASCROBBLER_H
#define ASCROBBLER_H

#define NAMELEN 64
#define BUFSIZE 100

struct play
{
  int user_id;
  int artist_id;
  int playcount;
};

struct artist
{
  int id;
  char name[NAMELEN];
  int count;
  float similarity;
  struct list *fans;
};

void print_play(void *p);
void print_artist(void *p);

struct play *create_play(int id, int artist_id, int playcount);
struct artist *create_artist(int id, char *name, int count);

void *parse_play(char *line);
void *parse_artist(char *line);

struct artist **create_index(struct list *head, int n);
struct artist *lookup_artist(struct artist **index, int n, int artist_id);

void register_fan(struct artist *a, struct play *p);
void register_fans(struct artist **index, int n, struct list *plays);
struct list *sort_similarity(struct artist *a, struct list *artists);

void free_index(struct artist **index);

int a_leq_jc(void *a, void *b);
int a_leq_id(void *a, void *b);
int p_leq_id(void *a, void *b);
int p_leq_uid(void *a, void *b); 
int a_geq_pc(void *a, void *b);
int p_leq_uid_geq_count(void *a, void *b);

#endif
