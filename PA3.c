// Omar Azhar
// Programming Assignment 3
// COP 4531: Complexity and Analysis of Data
//           Structures and Algorithms

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define infinite 9995
#define nv 20
#define ne 50

struct MyGraph
{
	char fromName;
	int value;
	int conectionsd;
	char toNamed[ne];
	int weightd[ne];
	int conectionsud;
	char toNameud[ne];
	int weightud[ne];
};

FILE *f;
char source;
int k;
struct MyGraph graph[nv];
int nodesCounter;
int gtype;
char v[nv];
int vc;

int nodeIndex(char a)
{
	int i;
	for(i=0;i<nodesCounter;i++)
		if(graph[i].fromName == a)
			return i;
	return -1;
}

void updateV(char str)
{
	int i,c=0;
	for(i=0;i<vc;i++)
		if(v[i] == str)
			c=1;
	if(c==0)
	{
		v[vc] = str;
		vc++;
	}
}

void loadData()
{
	int i, tmpW;
	char buf[256];
	char tmpF[2], tmpT[2];
	nodesCounter = 0;
	vc =0;

	fscanf(f, "%s",buf);
	fscanf(f, "%s",buf);
	if(strncmp(buf,"UD",2) == 0)
		gtype =0;
	else
		gtype=1;

	while(fread(buf, 3,2, f) > 0 )//EOF)
	{
		sscanf(buf,"%s %s %d", tmpF,tmpT,&tmpW);
		if((i=nodeIndex(tmpF[0])) == -1)
		{
			graph[nodesCounter].fromName = tmpF[0];
			graph[nodesCounter].value = infinite;
			graph[nodesCounter].conectionsd = 1;
			graph[nodesCounter].toNamed[0] = tmpT[0];
			graph[nodesCounter].weightd[0] = tmpW;
			graph[nodesCounter].conectionsud = 1;
			graph[nodesCounter].toNameud[0] = tmpT[0];
			graph[nodesCounter].weightud[0] = tmpW;
			nodesCounter++;
		}
		else
		{
			graph[i].toNamed[graph[i].conectionsd] = tmpT[0];
			graph[i].weightd[graph[i].conectionsd] = tmpW;
			graph[i].conectionsd++;
			graph[i].toNameud[graph[i].conectionsud] = tmpT[0];
			graph[i].weightud[graph[i].conectionsud] = tmpW;
			graph[i].conectionsud++;
		}
		if((i=nodeIndex(tmpT[0])) == -1)
		{
			graph[nodesCounter].fromName = tmpT[0];
			graph[nodesCounter].value = infinite;
			graph[nodesCounter].conectionsud = 1;
			graph[nodesCounter].toNameud[0] = tmpF[0];
			graph[nodesCounter].weightud[0] = tmpW;
			graph[nodesCounter].conectionsd = 0;
			graph[nodesCounter].toNamed[0] = '\0';
			graph[nodesCounter].weightd[0] = '\0';
			nodesCounter++;
		}
		else
		{
			graph[i].toNameud[graph[i].conectionsud] = tmpF[0];
			graph[i].weightud[graph[i].conectionsud] = tmpW;
			graph[i].conectionsud++;
		}
		updateV(tmpF[0]);
		updateV(tmpT[0]);
	}

	if((i=nodeIndex(source)) == -1)
		printf("This node %c is not existed",source);
	else
		graph[i].value = 0;
}

char extract_min(char pq[nv], int pqc)
{
	int i, min = 0;
	char t;
	for(i=1;i<pqc;i++)
		if(graph[nodeIndex(pq[min])].value > graph[nodeIndex(pq[i])].value)
			min =i;
	t = pq[min];
	for(i=min+1;i<pqc;i++)
		pq[i-1]=pq[i];
	return t;
}

void relax(int x, int z)
{
	if(gtype==1) {
		if(graph[nodeIndex(graph[x].toNamed[z])].value > (graph[x].value + graph[x].weightd[z]))
			graph[nodeIndex(graph[x].toNamed[z])].value = (graph[x].value + graph[x].weightd[z]);
	}
	else {
		if(graph[nodeIndex(graph[x].toNameud[z])].value > (graph[x].value + graph[x].weightud[z]))
			graph[nodeIndex(graph[x].toNameud[z])].value = (graph[x].value + graph[x].weightud[z]);
	}
}

void dijkstra()
{
	int i,x,pqc,sc=0;
	char s[nv];
	char pq[nv];
	char u;
	char buf[20];

	strcpy(pq,v);
	pqc = vc;
	while(pqc != 0)
	{
		u = extract_min(pq,pqc);
		pqc--;
		sc++;
		s[sc] = u;
		x = nodeIndex(u);
		if(gtype==1)
			for(i=0;i<graph[x].conectionsd;i++)
				relax(x,i);
		else
			for(i=0;i<graph[x].conectionsud;i++)
				relax(x,i);
	}

	fprintf(f,"%s%s%c%s","Dijkstra\n","Source : ",source,"\n");
	for(i=0;i<nodesCounter;i++)
		fprintf(f,"%s%c%s%d%s","NODE ",graph[i].fromName," : ",graph[i].value,"\n");
	fprintf(f,"%s","End Dijkstra\n");
}

void resetValue()
{
	int i;
	for(i=0;i<nodesCounter;i++)
		graph[i].value = infinite;
	graph[nodeIndex(source)].value = 0;
}

void theSRPA()
{
	int i,j, z,m, tmp, ac;
	int a[nv];
	for(i=0;i<k;i++)
	{
		//memset(a,-1,nv);
		m=0;
		for(j=0;j<nodesCounter;j++)
		{
			if(graph[j].value!=infinite) {
				a[m] = j;
				m++;
			}
		}

		for(j=0;j<m;j++){
			if(gtype==1) {
				for(z=0;z<graph[a[j]].conectionsd;z++)
					if(graph[nodeIndex(graph[a[j]].toNamed[z])].value > (graph[a[j]].value + graph[a[j]].weightd[z])) {
						graph[nodeIndex(graph[a[j]].toNamed[z])].value = (graph[a[j]].value + graph[a[j]].weightd[z]);
					}
			} else {
				for(z=0;z<graph[a[j]].conectionsud;z++)
					if(graph[nodeIndex(graph[a[j]].toNameud[z])].value > (graph[a[j]].value + graph[a[j]].weightud[z])) {
						graph[nodeIndex(graph[a[j]].toNameud[z])].value = (graph[a[j]].value + graph[a[j]].weightud[z]);
					}
			}
		}
	}

	fprintf(f,"%s","\nShortest Reliable Paths Algorithm\n");
	fprintf(f,"%s%d%s%c%s","Integer k : ",k,"\nSource : ",source,"\n");
	for(i=0;i<nodesCounter;i++) {
		if(graph[i].value != infinite)
			fprintf(f,"%s%c%s%d%s","NODE ",graph[i].fromName," : ",graph[i].value,"\n");
		else
			fprintf(f,"%s%c%s%s%s","NODE ",graph[i].fromName," : ","Unreachable!","\n");
	fprintf(f,"%s","End Shortest Reliable Paths Algorithm\n");
	}
}

int main(int argc, char *argv[])
{
	int i;
	
	if(argc < 4)
	{
		printf("You should include the file name, the source and the integer!\n");
		return 0;
	}
	
	f = fopen(argv[1],"r");
	source = argv[2][0];
	k = atoi(argv[3]);
	//f = fopen("d.txt","r");
	//source = 'A';
	//k =2;
	if(f != NULL)
	{
		loadData();
		fclose(f);
		if(nodesCounter > 0)
		{
			f = fopen("out.txt","w");
			if(f != NULL)
			{
				dijkstra();
				resetValue();
				theSRPA();
				fclose(f);
			}
			else
				printf("Unable to create out.txt!\n");
		}
	}
	else
		printf("Unable to open the file!\n");
	return 0;
}