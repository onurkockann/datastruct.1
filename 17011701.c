#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

struct node{ //double linked list yap�m�z i�in gerekli struct tan�mlamasi
	int counter;
	char adres[20];
	struct node *next;
	struct node *prev;
};

struct node *head=NULL; //structun ilk de�eri ba�ta global de�i�ken olarak null atan�yor
int elemanSayisi=0; //linked listimizin eleman sayisini tutmak i�in elemanSayisi de�i�keni tan�mlan�yor.

int sayacSorgula(struct node *dugum){	//istenilen node �n sayac�n� sorgular.
	return dugum->counter;
}

void yazdir() //linked list i�erisindeki t�m nodelar�n adres de�erlerini s�ras�yla yazd�r�r.
{
    struct node* temp = head;
    while (temp != NULL)
    {
        printf("	%s,%d	", temp->adres,temp->counter);
        temp = temp->next;
    }
}

struct node* findNode(char adres[20]){ //istenilen adres parametresi g�nderildi�i taktirde o adres de�i�kenine sahip bir node varm� yokmu kontrol�n� yapar.
	struct node* Node;
	Node=head;
	while(Node!=NULL){
		if(strcmp(Node->adres,adres)==0){ //mevcut node'un adresi=parametre olarak gelen adres 
			return Node; //BULUNDU
		}
		Node=Node->next;
	}
	//BULUNAMADI
	return NULL;
	
}

void delete(){ //linkli listemizin en son eleman�n� siler.
	struct node *temp=head;
	while(temp->next!=NULL){
		temp=temp->next;
	}
	temp->prev->next=NULL;
	free(temp);
}

int gezinti(){ //t�m nodelar� gezerek(ba�tan en son node a kadar) linkli listenin eleman sayisini d�nd�r�r.
	struct node *temp=head;
	int say=0;
	while(temp->next != NULL){
		temp = temp->next;
		say++;
	}
	return say;
}

void deleteAll(){ // program�n son k�sm�nda kulan�c� iste�i do�rultusunda t�m linkli listeyi temizleyecek olan kod par�ac���
	int say=gezinti();
	struct node *gec;
	int i;
	for (i=0;i<say;i++)
	{
		gec = head->next;
		gec->prev = NULL;
		free(head);
		head = gec;
		yazdir();
		printf("SILINIYOR...\n",gec->adres);
	}
	head=head->next;
	free(head);
	yazdir();
	printf("SILINDI!\n",gec->adres);
	return;
	
}

void insert(char adres[20],int esik,int buffer){
    if (head==NULL){ //�LK NODE EKLENIRKEN
    	struct node* newNode = (struct node*)malloc(sizeof(struct node));
    	elemanSayisi++;
    	strcpy(newNode->adres,adres);
    	newNode->next = NULL;
    	newNode->prev = NULL;
    	newNode->counter=1;
    	head=newNode;
    	yazdir();
    }
    
    else{
    	if(findNode(adres)==NULL){ // ELEMAN HIC YOKSA
    		if(elemanSayisi<buffer){	//ELEMAN SAYISI BUFFER LIMITINDEN DUSUK ISE BASA EKLE
    		struct node* newNode = (struct node*)malloc(sizeof(struct node));
    		elemanSayisi++;
    		strcpy(newNode->adres,adres);
    		newNode->next = head;
    		newNode->prev = NULL;
    		newNode->counter=1;
    		head->prev=newNode;
    		head=newNode;
    		yazdir();
    		}
    		else{//buffer limiti asildi son eleman silinecek,yeni eleman basa eklenicek
    			delete();
    			struct node* newNode = (struct node*)malloc(sizeof(struct node));
    			strcpy(newNode->adres,adres);
    			newNode->next = head;
    			newNode->prev = NULL;
    			newNode->counter=1;
    			head->prev=newNode;
    			head=newNode;
    			yazdir();
    			
			}
			
			
			
		}//ELEMAN VARSA
		else{
			struct node* node=findNode(adres);
			if(node->counter==esik){ //ilk esigi gecme
				if(node->prev==NULL){ //node bastaysa
					node->counter++;
					yazdir();
				}
				else if(node->next==NULL){ //node sondaysa
					node->counter++;
					node->prev->next=NULL;
					node->next=head;
					node->prev=NULL;
					head->prev=node;
					head=node;
					yazdir();
				}
				else{ //node ortalardaysa
					node->counter++;
					node->next->prev=node->prev;
					node->prev->next=node->next;
					node->next=head;
					head->prev=node;
					node->prev=NULL;
					head=node;
					yazdir();
					
				}
				
			}	
			
			else{ //esik gecilme problemi yok sayac articaK
				node->counter++;
				yazdir();
			}
			
		}
    	
	}
    
}


int main(int argc, char *argv[]) {
	int buffer,esik,adet,karar,karar1;
	char adres[50];
	
	
	printf("Buffer Limitini Girin(L):");
	scanf("%d",&buffer);
	printf("Esik Limitini Girin(T):");
	scanf("%d",&esik);
	
	
	printf("File Ile Islem Yapmak Icin(0)\nConsole Ile Islem Yapmak Icin(1) Giriniz:");
	scanf("%d",&karar1);
	FILE *dosya;
	if(karar1==0){//FILE ISLEMI ILE PROGRAMIN YURUTULMESI
		dosya=fopen("input.txt","r");
		while(!feof(dosya)){
			fscanf(dosya,"%s",adres);
			insert(adres,esik,buffer);
			printf("\n");
			//printf("\n Adres : %s",adres);
		}
		fclose(dosya);
		
		printf("\nTum Liste Silinsinmi?	Evet(0)	Hayir(1):");//TUM LISTENIN TEMIZLENMESI TERCIHI
		scanf("%d",&karar);
		if(karar==0){
			deleteAll();
			printf("\nCache Buffer Temizlendi!");
			yazdir();
		}
		else{
			printf("\nCache Buffer Temizlenmedi.Son Hali;");
			yazdir();
		}
	}
	
	if(karar1==1){//CONSOLE ILE PROGRAMIN YURUTULMESI
		printf("Kac Adres Girilecek?");
		scanf("%d",&adet);
		
		while(adet!=0){
			printf("\nAdres Girin:");
			scanf("%s",&adres);
			insert(adres,esik,buffer);
			adet--;
		}
		printf("\nTum Liste Silinsinmi?	Evet(0)	Hayir(1):");//TUM LISTENIN TEMIZLENMESI TERCIHI
		scanf("%d",&karar);
		if(karar==0){
			deleteAll();
			printf("\nCache Buffer Temizlendi!");
			yazdir();
		}
		else{
			printf("\nCache Buffer Temizlenmedi.Son Hali;");
			yazdir();
		}
		
	}
		
	return 0;
}
