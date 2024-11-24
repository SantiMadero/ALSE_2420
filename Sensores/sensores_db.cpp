#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <sstream>
#include <string>

using namespace std;
/*funcion callback print*/
static int callbackp(void *data, int argc, char **argv, char **azColName){
   int i;
   std::cout << (const char*)data << std::endl;
   
   for(i = 0; i<argc; i++){
      std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL")  << std::endl;
   }
   
   std::cout << std::endl;
   return 0;
}

/*funcion callback suma*/
static int callback(void *data, int argc, char **argv, char **azColName) {
   double* sum = (double*)data;
   for(int i = 0; i < argc; i++) {
      *sum += atof(argv[i]);
   }
   return 0;
}

int main(int argc, char* argv[]){
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   stringstream sqlstr;
   const char* data = "He llamado la función Callback";
   double sum = 0.0;

   /* Open database */
   rc = sqlite3_open("test.db", &db);
   
   if( rc != 0 ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(1);
   } else {
      fprintf(stdout, "Opened database successfully\n");
   }

   /* Create table datos */
   sqlstr << "CREATE TABLE IF NOT EXISTS datos (id_datos INTEGER PRIMARY KEY NOT NULL,"
          << "fecha TEXT ,"
          << "hora TEXT ,"
          << "temperatura REAL NOT NULL,"
          << "humedad_aire REAL NOT NULL,"
          << "humedad_suelo REAL NOT NULL,"
          << "velocidad REAL NOT NULL,"
          << "direccion REAL NOT NULL,"
          << "precipitacion REAL NOT NULL,"
          << "intensidad REAL NOT NULL);";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sqlstr.str().c_str(), 0, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return (2);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }

   /* Create table promedios */
   sqlstr << "CREATE TABLE IF NOT EXISTS promedios (id_promedios INTEGER PRIMARY KEY NOT NULL,"
          << "fecha TEXT ,"
          << "hora TEXT ,"
          << "temperatura_p REAL NOT NULL,"
          << "humedad_aire_p REAL NOT NULL,"
          << "humedad_suelo_p REAL NOT NULL,"
          << "velocidad_p REAL NOT NULL,"
          << "direccion_p REAL NOT NULL,"
          << "precipitacion_p REAL NOT NULL,"
          << "intensidad_p REAL NOT NULL);";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sqlstr.str().c_str(), 0, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return (2);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }

   double temperatura_p, humedad_aire_p, humedad_suelo_p, velocidad_p, direccion_p, precipitacion_p, intensidad_p;

/*Generar datos random*/
srand(time(0));
   for (int i = 0; i < 100; i++) {
      double temperatura = rand() % 56 - 10; // Rango -10 a 45
      double humedad_aire = rand() % 101; // Rango 0 a 100
      double humedad_suelo = rand() % 101; // Rango 0 a 100
      double velocidad = rand() % 41; // Rango 0 a 40
      double direccion = rand() % 361 - 180; // Rango -180 a 180
      double precipitacion = rand() % 201; // Rango 0 a 200
      double intensidad = rand() % 4001; // Rango 0 a 4000


   /* Insertar datos */
   std::stringstream sql;
   sql << "INSERT INTO datos (fecha, hora, temperatura, humedad_aire, humedad_suelo, velocidad, direccion, precipitacion, intensidad) "
       << "VALUES ('21/11/2024', null, "
       << temperatura << ", " << humedad_aire << ", " << humedad_suelo << ", " << velocidad << ", " << direccion << ", " << precipitacion << ", " << intensidad << ");";

      /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.str().c_str(), 0, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Records created successfully\n");
   }

   if( i % 12 == 0 && i != 0) {

         /* Select temperatura */
         sum = 0.0; // Reiniciar la variable sum
         sqlstr.str("");
         sqlstr << "SELECT temperatura FROM (SELECT * FROM datos ORDER BY id_datos DESC LIMIT 12);";
         rc = sqlite3_exec(db, sqlstr.str().c_str(), callback, &sum, &zErrMsg);

         if( rc != SQLITE_OK ) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
         } else {
            fprintf(stdout, "Promedio de temperatura: %f\n", sum / 12);
            temperatura_p = sum / 12;
         }

         /* Select humedad_aire */
         sum = 0.0; // Reiniciar la variable sum
         sqlstr.str("");
         sqlstr << "SELECT humedad_aire FROM (SELECT * FROM datos ORDER BY id_datos DESC LIMIT 12);";
         rc = sqlite3_exec(db, sqlstr.str().c_str(), callback, &sum, &zErrMsg);

         if( rc != SQLITE_OK ) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
         } else {
            fprintf(stdout, "Promedio de humedad_aire: %f\n", sum / 12);
            humedad_aire_p = sum / 12;
         }

         /* Select humedad_suelo */
         sum = 0.0; // Reiniciar la variable sum
         sqlstr.str("");
         sqlstr << "SELECT humedad_suelo FROM (SELECT * FROM datos ORDER BY id_datos DESC LIMIT 12);";
         rc = sqlite3_exec(db, sqlstr.str().c_str(), callback, &sum, &zErrMsg);

         if( rc != SQLITE_OK ) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
         } else {
            fprintf(stdout, "Promedio de humedad_suelo: %f\n", sum / 12);
            humedad_suelo_p = sum / 12;
         }

         /* Select velocidad */
         sum = 0.0; // Reiniciar la variable sum
         sqlstr.str("");
         sqlstr << "SELECT velocidad FROM (SELECT * FROM datos ORDER BY id_datos DESC LIMIT 12);";
         rc = sqlite3_exec(db, sqlstr.str().c_str(), callback, &sum, &zErrMsg);

         if( rc != SQLITE_OK ) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
         } else {
            fprintf(stdout, "Promedio de velocidad: %f\n", sum / 12);
            velocidad_p = sum / 12;
         }

         /* Select direccion */
         sum = 0.0; // Reiniciar la variable sum
         sqlstr.str("");
         sqlstr << "SELECT direccion FROM (SELECT * FROM datos ORDER BY id_datos DESC LIMIT 12);";
         rc = sqlite3_exec(db, sqlstr.str().c_str(), callback, &sum, &zErrMsg);

         if( rc != SQLITE_OK ) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
         } else {
            fprintf(stdout, "Promedio de direccion: %f\n", sum / 12);
            direccion_p = sum / 12;
         }

         /* Select precipitacion */
         sum = 0.0; // Reiniciar la variable sum
         sqlstr.str("");
         sqlstr << "SELECT precipitacion FROM (SELECT * FROM datos ORDER BY id_datos DESC LIMIT 12);";
         rc = sqlite3_exec(db, sqlstr.str().c_str(), callback, &sum, &zErrMsg);

         if( rc != SQLITE_OK ) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
         } else {
            fprintf(stdout, "Promedio de precipitacion: %f\n", sum / 12);
            precipitacion_p = sum / 12;
         }

         /* Select intensidad */
         sum = 0.0; // Reiniciar la variable sum
         sqlstr.str("");
         sqlstr << "SELECT intensidad FROM (SELECT * FROM datos ORDER BY id_datos DESC LIMIT 12);";
         rc = sqlite3_exec(db, sqlstr.str().c_str(), callback, &sum, &zErrMsg);

         if( rc != SQLITE_OK ) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
         } else {
            fprintf(stdout, "Promedio de intensidad: %f\n", sum / 12);
            intensidad_p = sum / 12;
         }

   /* Insertar promedios */
   sql << "INSERT INTO promedios (fecha, hora, temperatura_p, humedad_aire_p, humedad_suelo_p, velocidad_p, direccion_p, precipitacion_p, intensidad_p) "
       << "VALUES ('21/11/2024', null, "
       << temperatura_p << ", " << humedad_aire_p << ", " << humedad_suelo_p << ", " << velocidad_p << ", " << direccion_p << ", " << precipitacion_p << ", " << intensidad_p << ");";

      /* Execute SQL statement */
      rc = sqlite3_exec(db, sql.str().c_str(), 0, 0, &zErrMsg);
   
      if( rc != SQLITE_OK ){
       fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
      } else {
      fprintf(stdout, "Records created successfully\n");
      }


   }

}

   /*Select promedios*/
   /* Create SQL statement */
   sqlstr << "SELECT * FROM promedios;";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sqlstr.str().c_str(), callbackp, (void*)data, &zErrMsg);
   
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Operation done successfully\n");
   }

   sqlite3_close(db);
   return 0;





   sqlite3_close(db);
   return 0;
}