// List of Tables in a database
// Dec 1, 1990

#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <dbsql.h>

PSQLPROCESS pSqlProcess;
CHAR	    szDatabaseName[21];

VOID main ( VOID );
VOID ListTables ( PSQLPROCESS pSqlProcess );

VOID main ( VOID )
{
    printf ( "Enter Database Name: " );
    scanf  ( "%s", szDatabaseName );

    printf ( "\n\n" );
    printf ( "Program Started \n" );
    pSqlProcess = SqlOpenDB ( szDatabaseName );

    ListTables ( pSqlProcess );
}

VOID ListTables ( PSQLPROCESS pSqlProcess )
{
    SHORT   sRow;
    CHAR    szName[19];
    CHAR    szCreator[9];
    CHAR    szType[2];
    SHORT   sColCount;
    LONG    lNumRows;
    CHAR    szComment[255];

    printf ( "Opening Database: %s \n\n", szDatabaseName );

    SqlCommand ( pSqlProcess, "SELECT Name, Creator, Type, ColCount, Card, Remarks " );
    SqlCommand ( pSqlProcess, "FROM SYSIBM.SYSTABLES " );

    if ( SqlExecute ( pSqlProcess ) )
    {
	SqlBindByNum ( pSqlProcess, 1, szName,	    BIND_CHAR );
	SqlBindByNum ( pSqlProcess, 2, szCreator,   BIND_CHAR );
	SqlBindByNum ( pSqlProcess, 3, szType,	    BIND_CHAR );
	SqlBindByNum ( pSqlProcess, 4, &sColCount,  BIND_CHAR );
	SqlBindByNum ( pSqlProcess, 5, &lNumRows,   BIND_CHAR );
	SqlBindByNum ( pSqlProcess, 6, szComment,   BIND_CHAR );

	printf ( "Binded\n\n" );

	SqlOpenCursor  ( pSqlProcess );

	printf ( "Cursor Open\n\n" );

	sRow = 0;

	while ( SqlFetchRow ( pSqlProcess ) )
	{
	    sRow++;
	    printf ( "%3d.  %-18s  %-8s  %1s  %d  %ld  %s\n",
			     sRow, szName, szCreator, szType,
			     sColCount, lNumRows, szComment );
	}

	SqlCloseCursor ( pSqlProcess );
    }
}
