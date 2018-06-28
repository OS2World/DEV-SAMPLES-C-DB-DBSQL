// List of Tables in a database
// Dec 1, 1990

#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <dbsql.h>

PSQLPROCESS pSqlProcess;
CHAR	    szDatabaseName[21];
CHAR	    szTableName[21];

VOID main ( VOID );
VOID ListTables ( PSQLPROCESS pSqlProcess );

VOID main ( VOID )
{
    printf ( "Enter Database Name: " );
    scanf  ( "%s", szDatabaseName );
    printf ("\n" );
    printf ( "Enter Table Name: " );
    scanf  ( "%s", szTableName );

    printf ( "\n\n" );
    printf ( "Program Started \n" );
    pSqlProcess = SqlOpenDB ( szDatabaseName );

    ListTables ( pSqlProcess );
}

VOID ListTables ( PSQLPROCESS pSqlProcess )
{
    SHORT   sRow;
    CHAR    szName[19];
    CHAR    szType[9];
    SHORT   sLength;
    SHORT   sScale;
    CHAR    szNulls[2];
    CHAR    szComment[255];

    printf ( "Opening Database: %s \n\n", szDatabaseName );

    SqlCommand ( pSqlProcess, "SELECT Name, ColType, Length, Scale, Nulls, Remarks " );
    SqlCommand ( pSqlProcess, "FROM SYSIBM.SYSCOLUMNS " );
    SqlCommandf ( pSqlProcess, "WHERE TbName = '%s' ", szTableName );

    if ( SqlExecute ( pSqlProcess ) )
    {
	SqlBindByNum ( pSqlProcess, 1, szName,	    BIND_CHAR );
	SqlBindByNum ( pSqlProcess, 2, szType,	    BIND_CHAR );
	SqlBindByNum ( pSqlProcess, 3, &sLength,    BIND_SHORT );
	SqlBindByNum ( pSqlProcess, 4, &sScale,     BIND_SHORT );
	SqlBindByNum ( pSqlProcess, 5, szNulls,     BIND_CHAR );
	SqlBindByNum ( pSqlProcess, 6, szComment,   BIND_CHAR );

	printf ( "Binded\n\n" );

	SqlOpenCursor  ( pSqlProcess );

	printf ( "Cursor Open\n\n" );

	sRow = 0;

	while ( SqlFetchRow ( pSqlProcess ) )
	{
	    sRow++;
	    printf ( "%3d.  %-18s  %-8s  %d  %d  %1s  %s\n",
			     sRow, szName, szType, sLength,
			     sScale, szNulls, szComment );
	}

	SqlCloseCursor ( pSqlProcess );
    }
}
