#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define N 3
#define FILENAME 100
#define LINKLIST_ERROR 101



typedef struct Lnode{
    double x;
    double y;
    struct Lnode *next;
}Lnode,*linklist;


double GeometricSeriesSum(linklist p,int j){
    linklist q=p;
    int i;
    double x,sum=0,multi;
    while(q!=NULL){
        x=q->x;
        for(multi=1,i=1;i<=j;i++){
            multi=multi*x;
        }
        sum+=multi;
        q=q->next;
    }
    return sum;
}


double right(linklist p,int j){
    linklist q=p;
    int i;
    double x,y,sum=0,multi;
    while(q!=NULL){
        x=q->x;
        y=q->y;
        for(multi=1,i=1;i<=j;i++){
            multi=multi*x;
        }
        multi=multi*y;
        sum+=multi;
        q=q->next;
    }
    return sum;
}


void Sum(double a[N+1][N+2],linklist head,int n)
{
	int j,m,k;
	linklist q=head->next;
    for(k=0;k<=N;k++){
        for(m=0;m<=N;m++){
			a[k][m]=GeometricSeriesSum(q,k+m);//��ϵ��
		}
		a[k][N+1]=right(q,k);
	}
	printf("\t���������ϵ��Ϊ:\n");
	for(k=0;k<N+1;k++){
		for(m=0;m<=N+1;m++){
			printf("\t%lf",a[k][m]);}
        printf("\n");

    }
}


void Coefficient(double a[N+1][N+2])   //ȷ�������ϵ��
{
	int i,j,k,m,n;
	double b,temp;                         //b���ڴ�ű�ֵ
	for(k=0;k<N;k++){
        if(a[k][k]==0){//���Խ�Ԫ��Ϊ�㣬������Ѱ�ҶԽ�Ԫ�ز�Ϊ����У����н���
            for(m=k+1;m<=N;m++){
                if(a[m][m]!=0){
                    for(n=0;n<=N+1;n++){//
                        temp=a[k][n];a[k][n]=a[m][n];a[m][n]=temp;
                    }
                }
            }
        }
       for(i=0;i<N+1;i++){//ʹ��ƫ��ѡ��Ԫ�������ڳ����б�ֵΪ�����б�ֵ�õ�����ʽ��
            //��ѡ����Ԫ��С��(�����ֵΪ��Ԫ������Ԫ��֮��)
            k=i;
            for(j=i+1;j<N+1;j++){
                if(a[k][k]>a[j][j]){
                    k=j;
                }
            }
            if(k!=i){
                for(m=0;m<N+2;m++){
                temp=a[i][m];a[i][m]=a[k][m];a[k][m]=temp;
                }
            }
        }

		for(i=k;i<N;i++)              //���һ�ֱ�ֵ
		{
			b=a[k][k]/a[i+1][k];      //��һ����ֵ
			for(j=0;j<=N+1;j++){     //һ����������
                a[i+1][j]=a[i+1][j]*b-a[i][j];
			}
			b=0.0;                   //��ֵ��ʼ��
		}
	}
	printf("\n\n\n\n�������Ϊ:\n");
	for(k=0;k<N+1;k++){
		for(m=0;m<=N+1;m++){
			printf("\t%lf",a[k][m]);}
        printf("\n");

    }
}


void result(double a[N+1][N+2],double b[N+1]){//�ش����������ϵ��
    int i,j,k;
    double d=0.0;
    for(k=N;k>0;k--){//��ϵ������Ϊ�ԽǾ���
        for(i=k;i>0;i--)              //���һ�ֱ�ֵ
		{
			d=a[k][k]/a[i-1][k];      //��ϵ����ֵ
			for(j=0;j<=N+1;j++){     //һ����������
                a[i-1][j]=a[i-1][j]*d-a[i][j];
			}
			d=0.0;                   //��ֵ��ʼ��
		}
    }
    printf("\n\n\n�ش���õ���ϵ���ԽǾ���Ϊ:\n");
    for(i=0;i<N+1;i++){
        for(j=0;j<N+2;j++){
            printf("\t%lf",a[i][j]);

        }
        printf("\n");
    }
    for(i=0;i<N+1;i++){
        b[N-i]=a[i][N+1]/a[i][i];

    }
    printf("\n\n\nϵ��Ϊ��\n");
    for(i=0;i<N+1;i++){
        printf("\n%lf\n",b[i]);
    }

}


int main(){
    char temp;
    FILE *fp;
    char filename[FILENAME];
    int n=0;
    double A[N+1][N+2],b[N+1];
    linklist data;
    linklist p,q,tail;

    data=(linklist)malloc(sizeof(Lnode));
    if(!data) exit(LINKLIST_ERROR);
    data->next=NULL;
    tail=data;

    printf("���������������ļ�������(��Ҫ��д��׺:)\n");
    gets(filename);
    if((fp=fopen(filename,"r"))==NULL){
        printf("�ļ���ȡ����\n");
        exit(0);
    }
    else printf("�ļ���ȡ�ɹ�!\n");
    while(1){
        p=(linklist)malloc(sizeof(Lnode));
        p->next=NULL;
        tail->next=p;
        tail=p;
        fscanf(fp,"%lf",&(tail->x));
        fscanf(fp,"%c",&temp);
        fscanf(fp,"%lf",&(tail->y));
        n++;
        if(fgetc(fp)==EOF) break;
    }
    fclose(fp);

    Sum(A,data,n);
    Coefficient(A);
    result(A,b);
    return 0;
}









