#include <stdio.h>

#include <sys/shm.h>
#include <sys/stat.h>
#include "sqlite3.h" 

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
 /*int i;
 for(i=0; i<argc; i++){
   printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
 }
 printf("\n");*/
 return 0;
}

int main(int argc, char **argv){
	argc = 3;
	argv[1] = "testJan29";
	argv[2] = "select * from test WHERE emergency BETWEEN 1000 and 2000";
 sqlite3 *db;
 char *zErrMsg = 0;
 int rc;

 if(argc!=3){
   fprintf(stderr, "Usage: %s DATABASE SQL-STATEMENT\n", argv[0]);
   return(1);
 }
 int i = 0;

while(1) {

rc = sqlite3_open(argv[1], &db);

 if( rc ){
   fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
   sqlite3_close(db);
   return(1);
 }
 rc = sqlite3_exec(db, argv[2], callback, 0, &zErrMsg);
 if( rc!=SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
   sqlite3_free(zErrMsg);
 }

 sqlite3_close(db);

}
 return 0;
}

