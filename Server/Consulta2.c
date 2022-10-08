#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;

	int num;
	char consulta[400];
	//Creo una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicializar la conexion
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "bd",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	// consulta: Cuantas partidas se han perdido partizipando 3 jugadores y uno
	//           de ellos siendo Enric?
	strcpy(consulta,"SELECT COUNT(partidas.id) FROM (partidas,jugadores,registro) WHERE "
		   "partidas.resultado='Derrota' AND partidas.num=3 AND jugadores.username='enric' AND "
		   "jugadores.id=registro.id_j AND registro.id_p=partidas.id;");

	err=mysql_query (conn, consulta);
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//recojo el resultado de la consulta.
	resultado = mysql_store_result (conn);
	// El resultado es un numero en la primera fila
	row = mysql_fetch_row (resultado);
	
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	else
		num = atoi(row[0]);
		printf ("Partidas de 3 jugadores perdidas con Enric: %d", num);
	// cerrar la conexion con el servidor MYSQL 
	mysql_close (conn);
	exit(0);
}

