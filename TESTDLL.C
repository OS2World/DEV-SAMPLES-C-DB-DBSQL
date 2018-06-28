/* Test of DbSql.DLL */


#include <os2.h>
#include <stdio.h>
#include "dbsql.h"

PSQLPROCESS pSqlProcess;

void DoQuery ( PSQLPROCESS pSqlProcess );

main ( )
{
    pSqlProcess = SqlOpenDB ( "Sample", "MASTER", "ACCESS" );

    printf ( "\n\nStart Query\n\n" ); 
    DoQuery ( pSqlProcess );
    
    SqlCloseDB ( pSqlProcess );

    return 0;
}


void DoQuery ( PSQLPROCESS pSqlProcess )
{
    SQLCOLUMNINFO   SqlCI;
    SHORT   nc;
    SHORT   i;
    SHORT   sRow;
    CHAR    szName[16];
    CHAR    szJob[11];
    CHAR    szDeptName[16];
    CHAR    szDivision[16];
    CHAR    szLocation[21];
    double  salary;
    
    SqlCommand ( pSqlProcess, "SELECT Name, Job, DeptName, Division, Location, Salary * 1.5 " );
    SqlCommand ( pSqlProcess, "FROM   Staff, Org " );
    SqlCommand ( pSqlProcess, "WHERE Manager = ID " );
    
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

        SqlBindByNum ( pSqlProcess, 1, szName,     BIND_CHAR );
        SqlBindByNum ( pSqlProcess, 2, szJob,      BIND_CHAR );
        SqlBindByNum ( pSqlProcess, 3, szDeptName, BIND_CHAR );
        SqlBindByNum ( pSqlProcess, 4, szDivision, BIND_CHAR );
        SqlBindByNum ( pSqlProcess, 5, szLocation, BIND_CHAR );
        SqlBindByNum ( pSqlProcess, 6, &salary,    BIND_DECIMAL );

	SqlOpenCursor  ( pSqlProcess );

	sRow = 0;

	while ( SqlFetchRow ( pSqlProcess ) )
	{
	    sRow++;
            printf ( "%3d. %-10s  %-5s  %-15s  %-10s  %-13s  %7.2lf\n", sRow, szName, szJob, szDeptName, szDivision, szLocation, salary );
	}

	SqlCloseCursor ( pSqlProcess );
    }
}
