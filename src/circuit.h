#ifndef BIG_H_   /* Include guard */
#define BIG_H_


typedef struct _element element;
struct _element
{
	int id;
	char *name;
	int type;
	int p1_id;
	int p2_id;
	double val;
	double offset;
	double amp;
	double freq;
	double delay;
	double damp;	
	int drawn;
};

typedef struct _node node;
struct _node
{
	int id;
	char *name;
	int flag1;
	int flag2;
	int yf;
	int *elemidlist;
	int size;

};

void setfile(FILE *out);
typedef struct _nodelist nodelist;
struct _nodelist
{
	node *list;
	int size;
};

typedef struct _elemlist elemlist;
struct _elemlist
{
	element *list;
	int size;
};
void printlist();
void set();
void add_node(char *name);
int node_id(char *name);
void add_elem_to_node(int node_id,int elem_id);
void add_elem(char *name,int type,char *node1,char *node2,double val,double offset,double amp,double freq,double delay,double damp);
double unitfn(char *unitt);

void printcircuit();




#endif // BIG_H_