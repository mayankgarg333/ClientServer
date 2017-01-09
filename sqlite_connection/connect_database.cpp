#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <iostream> 
#include <cstring>
#include <string>
#include <string.h>


using namespace std;


void create_database();
string add_to_database(string key, string value);
string get_from_database(string key);

sqlite3 *db;

static int callback(void *data, int argc, char **argv, char **azColName){
   char * sal= (char*)data;
   //cout << "ARGC" << argc << endl;
   strcpy(sal,argv[0]);
   return 0;
}








int main(int argc, char* argv[])
{
   create_database();
  
   string st=add_to_database("MARY3", "asd");
   cout << "put status to database: " << st << endl;
   string s2=get_from_database("MARY4");
   if(s2.size())
		cout<< "value for the key: " << "" << " is " << s2 << endl;
   else
		cout<< "Key not found" << endl;

   sqlite3_close(db);

   return 0;
}













string add_to_database(string key, string value){
	char *zErrMsg = 0;
    int  rc;
    char sql[1000];
	char data[1000];
	string failure="FAILURE";
	string success="SUCCCESS";
	
	//check if key exist
	string exists=get_from_database(key);
	if(exists.size()){
	 //update	
		string s="UPDATE KEY_VALUE set value_entry = '" + value +"' where key_entry = '"+ key + "'; ";
		strcpy(sql, s.c_str());
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	}
	else{
	 //insert
		string q= "INSERT INTO KEY_VALUE (key_entry, value_entry) VALUES ('" + key + "', '" + value + "' ); ";
		strcpy(sql,q.c_str());
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		if( rc != SQLITE_OK ){
			//fprintf(stderr, "SQL ERROR2: %s\n", sqlite3_errmsg(db)); 
			//sqlite3_free(zErrMsg);
      		fprintf(stderr, "KEY not found as well as can't be inserted %s\n", zErrMsg);
			return failure;		
		}
	}
	return success;
}



string get_from_database(string key){
	char *zErrMsg = 0;
    int  rc;
    char sql[1000];
	char data[1000]={};
	string failure="FAILURE";
	string success="SUCCCESS";
	
	// create select query
	string s= "SELECT value_entry from KEY_VALUE where key_entry='"+ key + "';";
	strcpy(sql, s.c_str());
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	return string(data);

}


void create_database(){
	int  rc;
	char *zErrMsg = 0;
	char sql[1000];
	// connect to database
	rc = sqlite3_open("server_511.db", &db);
	if( rc ){
    	fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    	return;
   	}else{
    	//fprintf(stdout, "Opened database successfully\n");
   	}

	/* Create TABLE */
	string s = "CREATE TABLE if not exists KEY_VALUE("  \
	"key_entry varchar(1000)  UNIQUE NOT NULL," \
	"value_entry varchar(1000) NOT NULL );";
	
	strcpy(sql, s.c_str());
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}else{
		//fprintf(stdout, "Table created successfully\n");
	}	

}

