#include<stdio.h>
#include<malloc.h>
#include<string.h>

#define MAX_CHAR 26


struct t{
	struct t *next[MAX_CHAR];
	int isword;
	int prefix;
};
typedef struct t TRIE;
TRIE *root;

char print_data[30];


TRIE *get_trie_node()
{

	int i;
	TRIE *node;
	node = (TRIE *)malloc(sizeof(TRIE));
	for(i=0;i<MAX_CHAR;i++)
		node->next[i] = NULL;
	node->isword = 0;
	node->prefix = 0;
	return(node);
}

void delete_trie(TRIE *root)
{
	int i;
	if(root == NULL)
		return;
	for(i=0;i<MAX_CHAR;i++) {
		if(root->next[i]) {
			delete_trie(root->next[i]);
			free(root->next[i]);
			root->next[i] = NULL;
		}
	}
}

TRIE *search_trie(char *ch)
{
	int index;
	TRIE *temp;
	temp = root;
	while(*ch) {
		index = *ch - 'a';
		if(temp->next[index] == NULL)
			return NULL;
		temp = temp->next[index];
		ch++;
	}
	return(temp);
}

void insert_trie(char *ch)
{
	int index;
	TRIE *temp;
	temp = root;
	while(*ch) {
		if(*ch >= 65 && *ch <=90)
			*ch = *ch + 32;
		index = *ch -'a';
		if(temp->next[index] == NULL)
			temp->next[index] = get_trie_node();
		temp = temp->next[index];
		temp->prefix++;
		ch++;
	}
	temp->isword++;
}

void print_trie(TRIE *root,int level)
{
	int i;
	TRIE *temp;
	if(root == NULL)
		return;
	temp = root;
	if(temp->isword) {
		print_data[level] = '\0';
		printf("%s\n",print_data);
	}

	for(i=0;i<MAX_CHAR;i++) {
		if(temp->next[i]) {
			print_data[level] = 'a' + i;
			print_trie(temp->next[i],level+1);
		}
	}
}

int main()
{
	int N,Q;
	char word[30];
	int len;
	TRIE *temp;
	root = get_trie_node();
	scanf("%d",&N);
	while(N--) {
		scanf("%s",word);
		insert_trie(word);
	}
	scanf("%d",&Q);
	while(Q--) {
		scanf("%s",word);
		temp = search_trie(word);
		if(temp == NULL) {
			printf("No suggestions\n");
			insert_trie(word);
		}
		else{
			strcpy(print_data,word);
			len = strlen(word);
			print_trie(temp,len);
		}
	}

	return(0);
}
