#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int codigogen;//1000 a 4000
    char descripcion[36];
    char caracteris;//A a la F
    int estado;//1 preparacion,2 armado,3 terminado
    int cantidad;//1 a 100
}sComercial;
typedef struct
{
    int codigo;//1000 a 4000
    int canti;
    int zona;//1 a 10
    int fecha;//1 a 31
}sPedidos;

int cargaGen(sComercial [300]);
int buscar(sComercial [300],sPedidos , int );
void actualizar();

int main()
{
    sComercial generador[300];
    sPedidos pedido;
    int cantiG=0,cantiUTC,codigoAnt,pedidosrechazados,dia;
    float porcentajepr;
    cantiG=cargaGen(generador);
    FILE*fped;

    fped=fopen("pedidos.dat","rb");
    if(fped==NULL)
    {
        printf("Error");
        system("pause");
        exit(2);
    }
    fread(&pedido,sizeof(sPedidos),1,fped);
    while(!feof(fped))
    {

        cantiUTC=0;//cantidad de unidades totales por codigo
        codigoAnt=pedido.codigo;
        while(codigoAnt==pedido.codigo&&!feof(fped))
        {
            cantiUTC+=pedido.canti;
            fread(&pedido,sizeof(sPedidos),1,fped);
            if(generador[cantiG].cantidad<pedido.canti||generador[cantiG].estado!=3)
                pedidosrechazados++;
        }
        printf("Codigo de generador: %d\nUnidades pedidas: %d\n",codigoAnt,cantiUTC);//Punto A
        porcentajepr=(pedido.canti*pedidosrechazados)/100;
        printf("Codigo de generador: %d\nPorcentaje de pedidos rechazados: %.2f\n",codigoAnt,porcentajepr);//Punto B
    }
    fclose(fped);
    actualizar();//Punto C

        printf("Dia                 Cantidad de pedidos\n");//Punto D
        for(dia=1;dia<=31;dia++)
        {
            printf("%d                  %d\n",dia,pedido.fecha);
        }

    return 0;
}
int cargaGen(sComercial generador[300])
{
    int x=0;
    FILE*fp;
    fp=fopen("comercial.dat","rb");
    if(fp==NULL)
    {
        printf("Error");
        system("pause");
        exit(1);
    }
    fread(&generador[x],sizeof(sComercial),1,fp);
    while(!feof(fp))
    {
        x++;
        fread(&generador[x],sizeof(sComercial),1,fp);
    }
    fclose(fp);
    return x;
}
int buscar(sComercial generador[300],sPedidos pedido,int cant)
{
    int pos=-1,x=0;

    while(pos==-1&&x<cant)
    {
        if(generador[x].codigogen==pedido.codigo)
        {
            pos=x;
        }
        else
        {
            x++;
        }
    }
}
void actualizar()
{
    sPedidos pedido;
    FILE*actualizado;
    actualizado=fopen("articulosAct.dat","wb");
    if(actualizado==NULL)
    {
        printf("Error");
        system("pause");
        exit(3);
    }
    fwrite(&pedido,sizeof(sPedidos),1,actualizado);
}
