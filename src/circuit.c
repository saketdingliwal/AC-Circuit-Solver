#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circuit.h"

elemlist elems;
nodelist nodes;

FILE *outp;
void setfile(FILE *out)
{
	outp = out;
}


double unitfn(char * str)
{
	if(strcmp(str,"F")==0 || strcmp(str,"H")==0 || strcmp(str,"S")==0 ||strcmp(str,"hz")==0)
		return 1;
	else if(str[0]=='P')
		return 0.000000000001;
	else if(str[0]=='N')
		return 0.000000001;
	else if(str[0]=='M')
		return 0.001;
	else if(str[0]=='K')
		return 1000;
	else if(str[0]=='U')
		return 0.000001;
	else if(str[0]=='F')
		return 0.000000000000001;
	else
		return 1000000;
}


char * haha(double a)
{
	double temp;
	char * ans;
	char arr[100];


	if(a==0)
	{
		return "0";
	}
	if(a>=1000000)
	{
		temp=a/1000000.0;
		sprintf(arr,"%g",temp);
		asprintf(&ans,"%s%s",arr,"MEG");
		return ans;
	}
	else if(a>=1000)
	{
		temp=a/1000.0;
		sprintf(arr,"%g",temp);
		asprintf(&ans,"%s%s",arr,"K");
		return ans;
	}
	else if(a>=1)
	{
		temp=a;
		sprintf(arr,"%g",temp);
		asprintf(&ans,"%s",arr);
		return ans;
	}
	else if(a>=0.001)
	{
		temp=a*1000.0;
		sprintf(arr,"%g",temp);
		asprintf(&ans,"%s%s",arr,"M");
		return ans;
	}
	else if(a>=0.000001)
	{
		temp=a*1000000.0;
		sprintf(arr,"%g",temp);
		asprintf(&ans,"%s%s",arr,"U");
		return ans;
	}
	else if(a>=0.000000001)
	{
		temp=a*1000000000.0;
		sprintf(arr,"%g",temp);
		asprintf(&ans,"%s%s",arr,"N");
		return ans;
	}
	else if(a>=0.000000000001)
	{
		temp=a*1000000000000.0;
		sprintf(arr,"%g",temp);
		asprintf(&ans,"%s%s",arr,"P");
		return ans;
	}
	else
	{
		temp=a*1000000000000000.0;
		sprintf(arr,"%g",temp);
		asprintf(&ans,"%s%s",arr,"F");
		return ans;
	}
	return ans;	

}

void set()
{
	elems.size = 0;
	nodes.size = 0;
}

void add_node(char *name)
{	
	nodes.size++;
	int size = nodes.size;
	nodes.list = (node *)realloc(nodes.list,nodes.size*sizeof(node));
	nodes.list[size-1].id = size-1;
	nodes.list[size-1].name = name;
	nodes.list[size-1].size = 0;
	nodes.list[size-1].flag1 = 0;
	nodes.list[size-1].flag2 = 0;
	nodes.list[size-1].yf = 0;

}

int node_id(char *name)
{
	
	for(int i=0;i<nodes.size;i++)
	{
		if(strcmp(nodes.list[i].name,name)==0)
		{
			return i;

		}
	}
	add_node(name);
	return nodes.size-1;

}

void add_elem_to_node(int node_id,int elem_id)
{
	nodes.list[node_id].size++;
	int sz = nodes.list[node_id].size;
	nodes.list[node_id].elemidlist = (int *)realloc(nodes.list[node_id].elemidlist,sz*sizeof(int));
	nodes.list[node_id].elemidlist[sz-1] = elem_id;
}


void add_elem(char *name,int type,char *node1,char *node2,double val,double offset,double amp,double freq,double delay,double damp)
{
	elems.size++;
	int size = elems.size;
	elems.list = (element *)realloc(elems.list,elems.size*sizeof(element));
	//printf("%d",elems.size);
	//printf("%f", val);
	elems.list[size-1].id = size-1;
	elems.list[size-1].name = name;
	elems.list[size-1].p1_id = node_id(node1);
	nodes.list[elems.list[size-1].p1_id].size++;
	//add_elem_to_node(elems.list[size-1].p1_id,elems.list[size-1].id);
	elems.list[size-1].p2_id = node_id(node2);
	nodes.list[elems.list[size-1].p2_id].size++;
	//add_elem_to_node(elems.list[size-1].p2_id,elems.list[size-1].id);
	if(type==3)
	{
		if(name[0]=='I' || name[0]=='i')
		{
			type = 4;
		}
		else if(name[0]=='V' || name[0]=='v')
		{

		}
		else
		{
			fprintf(stderr, "assumed element to be voltage source\n");
		}
	}
	elems.list[size-1].type = type;
	elems.list[size-1].val = val;
	elems.list[size-1].offset = offset;
	elems.list[size-1].amp = amp;
	elems.list[size-1].freq = freq;
	elems.list[size-1].delay = delay;
	elems.list[size-1].damp = damp;
	elems.list[size-1].drawn = 0;
	
	
}
void start_print()
{
	fprintf(outp,"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n<!-- Created with Inkscape (http://www.inkscape.org/) -->\n<svg\n   xmlns:dc=\"http://purl.org/dc/elements/1.1/\"\n   xmlns:cc=\"http://web.resource.org/cc/\"\n   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n   xmlns:svg=\"http://www.w3.org/2000/svg\"\n   xmlns=\"http://www.w3.org/2000/svg\"\n   xmlns:sodipodi=\"http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd\"\n   xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\"\n   id=\"svg2\"\n   sodipodi:version=\"0.32\"\n   inkscape:version=\"0.45.1\"\n   version=\"1.0\"\n   sodipodi:docbase=\"/home/force/Pictures\"\n   sodipodi:docname=\"resistors.svg\"\n   inkscape:output_extension=\"org.inkscape.output.svg.inkscape\">\n  <defs\n     id=\"defs4\" />\n  <sodipodi:namedview\n     id=\"base\"\n     pagecolor=\"#ffffff\"\n     bordercolor=\"#666666\"\n     borderopacity=\"1.0\"\n     gridtolerance=\"10000\"\n     guidetolerance=\"10\"\n     objecttolerance=\"10\"\n     inkscape:pageopacity=\"0.0\"\n     inkscape:pageshadow=\"2\"\n     inkscape:zoom=\"3.959798\"\n     inkscape:cx=\"72.753232\"\n     inkscape:cy=\"35.155889\"\n     inkscape:document-units=\"px\"\n     inkscape:current-layer=\"layer1\"\n     height=\"30px\"\n     width=\"99.516678px\"\n     inkscape:window-width=\"1280\"\n     inkscape:window-height=\"954\"\n     inkscape:window-x=\"0\"\n     inkscape:window-y=\"44\" />\n  <metadata\n     id=\"metadata7\">\n    <rdf:RDF>\n      <cc:Work\n         rdf:about=\"\">\n        <dc:format>image/svg+xml</dc:format>\n        <dc:type\n           rdf:resource=\"http://purl.org/dc/dcmitype/StillImage\" />\n      </cc:Work>\n    </rdf:RDF>\n  </metadata> \n" );	
}
void printreg()
{
	fprintf(outp,"<g\n    inkscape:label=\"Layer 1\"\n    inkscape:groupmode=\"layer\"\n    id=\"layer1\"\n    transform=\"translate(-350.12512,-540.87206)\">\n   <g\n      id=\"g3359\"\n      transform=\"translate(-0.48334,-1.2626907)\">\n     <path\n        id=\"path2160\"\n        d=\"M 351.35169,548.62453 L 371.26473,548.62453\"\n        style=\"fill:none;fill-rule:evenodd;stroke:#000000;stroke-width:1.4864676;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\" />\n     <path\n        id=\"path3149\"\n        d=\"M 430.17601,548.62453 L 449.3819,548.62453\"\n        style=\"fill:none;fill-rule:evenodd;stroke:#000000;stroke-width:1.4864676;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\" />\n     <path\n        sodipodi:nodetypes=\"ccccccccc\"\n        id=\"path3344\"\n        d=\"M 370.62756,548.90283 L 374.96171,544.32858 L 383.56813,552.98228 L 392.30206,544.39042 L 401.22724,553.04409 L 409.64241,544.45221 L 417.93009,553.1059 L 427.04651,544.14316 L 430.87067,548.96478\"\n        style=\"fill:none;fill-rule:evenodd;stroke:#000000;stroke-width:1.49143946;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\" />\n   </g>\n  </g>\n ") ;
}
void printind()
{
	fprintf(outp," <path\n    style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n    d=\"M 1,8.5 L 6.5,8.5 C 6.5,8.5 6.5,4.5 10.5,4.5 C 14.5,4.5 14.5,8.5 14.5,8.5 C 14.5,8.5 14.5,4.5 18.5,4.5 C 22.5,4.5 22.5,8.5 22.5,8.5 C 22.5,8.5 22.5,4.5 26.5,4.5 C 30.5,4.5 30.5,8.5 30.5,8.5 C 30.5,8.5 30.5,4.5 34.5,4.5 C 38.5,4.5 38.5,8.5 38.5,8.5 L 44,8.5\"\n    id=\"path1318\"\n    sodipodi:nodetypes=\"ccscscscscc\" />\n   ");
}
void printcap()
{
	fprintf(outp," <path\n      d=\"M 16,5.0010577 C 16,26.999992 16,26.999992 16,26.999992\"\n      style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:1.5;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n      id=\"path17478\" />\n   <path\n      d=\"M 19.000016,26.999994 L 19.000016,5.0010588\"\n      style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:1.5;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n      id=\"path17480\" />\n   <path\n      d=\"M 16.11348,16 L 1.69e-005,16\"\n      style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n      id=\"path17482\" />\n   <path\n      d=\"M 18.980533,16 C 19.743365,16 35,16 35,16\"\n      style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n      id=\"path17484\" /> ");
}

void printvol()
{
	fprintf(outp," <g\n     id=\"g4164\"\n     transform=\"translate(1.4854403,0.19886494)\">\n    <path\n       sodipodi:nodetypes=\"czzzc\"\n       inkscape:connector-curvature=\"0\"\n       id=\"path5536-8-3\"\n       d=\"m 0.3478974,9.7865691 c 0.67934,2.0380199 2.07525,4.0760499 4.09466,4.0760499 2.01941,0 3.3781,-2.03803 4.05744,-4.0760499 0.6793396,-2.03803 2.0380296,-4.07605 4.0760496,-4.07605 2.03803,0 3.39671,2.03802 4.07605,4.07605\"\n       style=\"fill:none;fill-rule:evenodd;stroke:#000000;stroke-width:1;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\" />\n    <circle\n       r=\"9.4854374\"\n       cy=\"9.7865725\"\n       cx=\"8.4999971\"\n       id=\"path14021-7-1-7\"\n       style=\"color:#000000;clip-rule:nonzero;display:inline;overflow:visible;visibility:visible;opacity:1;isolation:auto;mix-blend-mode:normal;color-interpolation:sRGB;color-interpolation-filters:linearRGB;solid-color:#000000;solid-opacity:1;fill:none;fill-opacity:1;fill-rule:nonzero;stroke:#000000;stroke-width:1;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1;marker:none;color-rendering:auto;image-rendering:auto;shape-rendering:auto;text-rendering:auto;enable-background:accumulate\" />\n  </g> ");
}

void printcur()
{
	fprintf(outp," <path\n       d=\"M 25,35.04878 L 25,17\"\n       style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n       id=\"path1309\" />\n    <path\n       d=\"M 25,15.5 L 27,18.5 L 23,18.5 L 25,15.5 z \"\n       style=\"fill:#000000;fill-opacity:1;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n       id=\"path1311\" />\n    <path\n       d=\"M 40,25 C 40,33.284271 33.284271,40 25,40 C 16.715729,40 10,33.284271 10,25 C 10,16.715729 16.715729,10 25,10 C 33.284271,10 40,16.715729 40,25 L 40,25 z \"\n       style=\"opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:1;stroke-linecap:square;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1\"\n       id=\"path1319\" /> ");
}

void printend()
{
	fprintf(outp,"</svg>");
}
void printdot(int x,int y,int rad)
{
	fprintf(outp," <circle cx=\"%d\" cy=\"%d\" r=\"%d\" fill=\"purple\" /> ",x,y,rad);
}


void printline(int color,int x1,int y1,int x2,int y2)
{
	int r = color/(256*256);
	int g = (color%(256*256))/256;
	int b = (color%(256*256))%256;
	fprintf(outp," <line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" style=\"stroke:rgb(%d,%d,%d);stroke-width:2\" /> ",x1,y1,x2,y2,r,g,b);
}
void printtext(char *str,int x,int y,int size)
{
	fprintf(outp," <text x=\"%d\" y=\"%d\" font-size=\"%d\" fill=\"blue\"> \n %s</text> ",x,y,size,str);
}
int radi = 5;
int txtst = 5;
int txtsz =10;
int txty = 0;
void printcapi(int color,int x1,int y1,int x2,int y2,char *name)
{
	printdot(x1,y1,radi);
	printdot(x2,y2,radi);
	int wd  = 30;
	int ht = 32;
	int pointx = x2 - x1 - wd;
	int sta = x1 + pointx/2;
	int end = x2 - pointx/2;
	int y = y1 - ht/2;
	printline(color,x1,y1,sta,y1);
	printtext(name,sta,y-txty+3,txtsz);
	fprintf(outp," <g transform = \"translate(%d,%d)\"  > ",sta,y);
	printcap();
	fprintf(outp,"</g>");
	printline(color,end,y1,x2,y2);

}
void printregi(int color,int x1,int y1,int x2,int y2,char *name)
{
	printdot(x1,y1,radi);
	printdot(x2,y2,radi);
	int wd  = 98;
	int ht = 15;
	int pointx = x2 - x1 - wd;
	int sta = x1 + pointx/2;
	int end = x2 - pointx/2;
	int y = y1 - ht/2;
	printline(color,x1,y1,sta,y1);
	printtext(name,sta+20,y-txty,txtsz);
	fprintf(outp," <g transform = \"translate(%d,%d)\"  > ",sta,y);
	printreg();
	fprintf(outp,"</g>");
	printline(color,end,y1,x2,y2);

}

void printindi(int color,int x1,int y1,int x2,int y2,char *name)
{
	printdot(x1,y1,radi);
	printdot(x2,y2,radi);
	int wd  = 44;
	int ht = 16;
	int pointx = x2 - x1 - wd;
	int sta = x1 + pointx/2;
	int end = x2 - pointx/2;
	int y = y1 - ht/2;
	printline(color,x1,y1,sta,y1);
	printtext(name,sta,y-txty,txtsz);
	fprintf(outp," <g transform = \"translate(%d,%d)\"  > ",sta,y);
	printind();
	fprintf(outp,"</g>");
	printline(color,end,y1,x2,y2);

}

void printvoli(int color,int x1,int y1,int x2,int y2,char *name)
{
	printdot(x1,y1,radi);
	printdot(x2,y2,radi);
	int wd  = 22;
	int ht = 18;
	int pointx = x2 - x1 - wd;
	int sta = x1 + pointx/2;
	int end = x2 - pointx/2;
	int y = y1 - ht/2;
	printline(color,x1,y1,sta,y1);
	printtext(name,sta-16,y-txty,txtsz);
	fprintf(outp," <g transform = \"translate(%d,%d)\"  > ",sta,y);
	printvol();
	fprintf(outp,"</g>");
	printline(color,end,y1,x2,y2);

}


void printcuri(int color,int x1,int y1,int x2,int y2,char *name)
{
	printdot(x1,y1,radi);
	printdot(x2,y2,radi);
	int wd  = 40;
	int ht = 42;
	int pointx = x2 - x1 - wd;
	int sta = x1 + pointx/2;
	int end = x2 - pointx/2;
	int y = y1 - ht/2;
	printline(color,x1,y1,sta,y1);
	printtext(name,sta,y-txty+3,txtsz);
	fprintf(outp," <g transform = \"translate(%d,%d)\"  > ",sta-10,y);
	printcur();
	fprintf(outp,"</g>");
	printline(color,end-10,y1,x2,y2);

}

void printground()
{
	fprintf(outp,"<path\n           d=\"m 0.5,24.5 24,0\"\n           style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/>\n        <path\n           d=\"m 4.5,27.5 16,0\"\n           style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/>\n        <path\n           d=\"m 16.5,30.5 -8,0\"\n           style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/>\n        <path\n           d=\"m 12.5,24.5 0,-20\"\n           style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/>");
}

void printgndi(int x1,int y1)
{
	fprintf(outp," <g transform = \"translate(%d,%d) scale(1,0.7)\"  > ",x1,y1);
	printground();
	fprintf(outp,"</g>");
}


void printlist()
{
	for(int i=0;i<elems.size;i++)
	{
		fprintf(outp,"%s\n",elems.list[i].name);
	}
	for(int i=0;i<nodes.size;i++)
	{
		fprintf(outp,"%s\n",nodes.list[i].name);
	}

}

int minid()
{
	int min = 1000000000;  //loose scalability
	int id = -1;
	for(int i=0;i<elems.size;i++)
	{	
		if(elems.list[i].drawn==0)
		{
			if(min>abs(elems.list[i].p1_id - elems.list[i].p2_id))
			{
				min = abs(elems.list[i].p1_id - elems.list[i].p2_id);
				id = i;
			}
		}

	}
	return id;

}

int ht = 700;
int width = 1200;

void printcircuit()
{
	start_print();
	int y = ht/2;
	int gapx = width/nodes.size;
	int gapy = (ht-50)/(elems.size+2);
	int offsett = 50;
	int coun = 1;
	int counterr = -1;
	int turn = 0;
	int r=255;
	int g=0;
	int b=0;
	int gndplace = y;
	while(minid()!=-1)
	{	
		
		int counter;
		if(turn==0)
		{
			counter = coun;
			coun++;
			//r=255-r;
			//b=255-b;
		}
		else
		{
			counter = counterr;
			counterr--;
		}
		int id = minid();
		if(strcmp(nodes.list[elems.list[id].p1_id].name,"0")==0 || strcmp(nodes.list[elems.list[id].p2_id].name,"0")==0)
		{
			if(gndplace<y-counter*gapy)
			{
				gndplace = y - counter*gapy;
			}
		}
		char *str = elems.list[id].name;
		if(nodes.list[elems.list[id].p1_id].flag1==0 && counter>0)
		{
			nodes.list[elems.list[id].p1_id].flag1 = 1;
			nodes.list[elems.list[id].p1_id].yf = y - counter*gapy;
		}
		if(nodes.list[elems.list[id].p1_id].flag2==0 && counter<0)
		{
			nodes.list[elems.list[id].p1_id].flag2 = 1;
			nodes.list[elems.list[id].p1_id].yf = y - counter*gapy;
		}

		if(nodes.list[elems.list[id].p2_id].flag1==0 && counter>0)
		{
			nodes.list[elems.list[id].p2_id].flag1 = 1;
			nodes.list[elems.list[id].p2_id].yf = y - counter*gapy;
		}
		if(nodes.list[elems.list[id].p2_id].flag2==0 && counter<0)
		{
			nodes.list[elems.list[id].p2_id].flag2 = 1;
			nodes.list[elems.list[id].p2_id].yf = y - counter*gapy;
		}
		
		if(elems.list[id].type<3)
		{
			asprintf(&str, "%s%s", str, " ");
			asprintf(&str, "%s%s", str, haha(elems.list[id].val));
		}
		else
		{
			asprintf(&str, "%s%s", str, " SINE ( ");
			asprintf(&str, "%s%s", str, haha(elems.list[id].offset));
			asprintf(&str, "%s%s", str, " ");
			asprintf(&str, "%s%s", str, haha(elems.list[id].amp));
			asprintf(&str, "%s%s", str, " ");
			asprintf(&str, "%s%s", str, haha(elems.list[id].freq));
			asprintf(&str, "%s%s", str, "hz ");
			asprintf(&str, "%s%s", str, haha(elems.list[id].delay));
			asprintf(&str, "%s%s", str, "S ");
			asprintf(&str, "%s%s", str, haha(elems.list[id].damp));
			asprintf(&str, "%s%s", str, " ) ");



			//strcat(str,valu);

			
			

		}
		int color = 256*256*r + 256*g+ b;
		elems.list[id].drawn  = 1;
		int p1,p2;
		if(elems.list[id].p1_id*gapx+offsett>elems.list[id].p2_id*gapx+offsett)
		{
			p1 = elems.list[id].p2_id*gapx+offsett;
			p2 = elems.list[id].p1_id*gapx+offsett;
		}
		else
		{
			p2 = elems.list[id].p2_id*gapx+offsett;
			p1 = elems.list[id].p1_id*gapx+offsett;
		}
		printline(color,elems.list[id].p1_id*gapx+offsett,y,elems.list[id].p1_id*gapx+offsett,y-counter*gapy);
		printtext(nodes.list[elems.list[id].p1_id].name,elems.list[id].p1_id*gapx+offsett+txtst,y-counter*gapy,txtsz);
		if(elems.list[id].type==0)
		{

			printregi(color,p1,y-counter*gapy,p2,y-counter*gapy,str);
			
		}
		if(elems.list[id].type==1)
		{
			asprintf(&str, "%s%s", str, "F");
			printcapi(color,p1,y-counter*gapy,p2,y-counter*gapy,str);
			
		}
		if(elems.list[id].type==2)
		{
			asprintf(&str, "%s%s", str, "H");
			printindi(color,p1,y-counter*gapy,p2,y-counter*gapy,str);
			
		}
		if(elems.list[id].type==3)
		{
			printvoli(color,p1,y-counter*gapy,p2,y-counter*gapy,str);
			
		}
		if(elems.list[id].type==4)
		{
			printcuri(color,p1,y-counter*gapy,p2,y-counter*gapy,str);
			
		}
		printtext(nodes.list[elems.list[id].p2_id].name,elems.list[id].p2_id*gapx+offsett+txtst,y-counter*gapy,txtsz);
		printline(color,elems.list[id].p2_id*gapx+offsett,y-counter*gapy,elems.list[id].p2_id*gapx+offsett,y);
		turn = 1 - turn;


		


	}




	for(int i=0;i<nodes.size;i++)
	{
		if(nodes.list[i].size==1)
		{
			fprintf(stderr, "open_circuit\n");
		}
		if(nodes.list[i].flag1==1 && nodes.list[i].flag2==1 || strcmp(nodes.list[i].name,"0")==0)
		{
			continue;
		}
		else
		{
			printline(16777215,i*gapx+offsett,y,i*gapx+offsett,nodes.list[i].yf);
		}

	}



	int no_of = nodes.size;
	int s = node_id("0");
	if(nodes.size==no_of)
	{
		printdot(s*gapx+offsett,gndplace,radi);
		printgndi(s*gapx+offsett-14,gndplace);
	}
	else
	{
		fprintf(stderr, "No ground net found!\n");
	}
	printend();




}


