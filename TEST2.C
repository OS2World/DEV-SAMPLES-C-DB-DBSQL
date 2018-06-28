/* Test of DbSql.DLL */


#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include "dbsql.h"

PSQLPROCESS pSqlProcess;

void DoQuery ( PSQLPROCESS pSqlProcess );

main ( )
{
    pSqlProcess = SqlOpenDB ( "Desktop", "MASTER", "ACCESS" );

    printf ( "Importing Data \n\n" );
    if ( !SqlImport ( pSqlProcess, "Bradley.Test", "A:\Address.WKS", 2, 1  ) )
    {
	printf ( "Error Importing File\n\n" );
	SqlCloseDB ( pSqlProcess );
	exit(1);
    }

    printf ( "\n\nStart Query\n\n" ); 
    DoQuery ( pSqlProcess );

    if ( !SqlExport ( pSqlProcess, "Bradley.Address", "A:\Address.TXT", 1 ) )
	printf ( "Error Exporting File\n\n" );


    SqlCloseDB ( pSqlProcess );

    return 0;
}


void DoQuery ( PSQLPROCESS pSqlProcess )
{
    SQLCOLUMNINFO   SqlCI;
    SHORT   nc;
    SHORT   i;
    SHORT   sRow;
    CHAR    szFirstName[26];
    CHAR    szLastName[26];
    CHAR    szHomePhone[16];
    CHAR    szCity[26];
    CHAR    szState[5];

    SqlCommand ( pSqlProcess, "SELECT FirstName, LastName, HomePhone, City, State " );
    SqlCommand ( pSqlProcess, "FROM Test " );
    SqlCommand ( pSqlProcess, "WHERE HomePhone IS NOT NULL " );
    SqlCommand ( pSqlProcess, "ORDER BY LastName " );

    if ( SqlExecute ( pSqlProcess ) )
    {
        nc = SqlGetNumberColumns ( pSqlProcess );
        printf ( "Number of columns: %d\n", nc );
        for ( i = 0; i < nc; i++ )
        {
            SqlCI = SqlGetColumnNameInfo ( pSqlProcess, i );
            printf ( "Column: %-30s  Type: %d   Length: %d\n", SqlCI.szColumnName, SqlCI.sSqlType, SqlCI.sSqlLength );
        }
        printf ( "\n\n" );
        
	SqlBindByNum ( pSqlProcess, 1, szFirstName, BIND_CHAR );
	SqlBindByNum ( pSqlProcess, 2, szLastName,  BIND_CHAR );
	SqlBindByNum ( pSqlProcess, 3, szHomePhone, BIND_CHAR );
	SqlBindByNum ( pSqlProcess, 4, szCity,	    BIND_CHAR );
	SqlBindByNum ( pSqlProcess, 5, szState,     BIND_CHAR );
        
	SqlOpenCursor  ( pSqlProcess );

	sRow = 0;

	while ( SqlFetchRow ( pSqlProcess ) )
	{
	    sRow++;
	    printf ( "%3d.  %-12s  %-15s  %12s  %-12s  %2s\n",
			     sRow, szFirstName, szLastName, szHomePhone,
			     szCity, szState );

	}

	SqlCloseCursor ( pSqlProcess );
    }
}
