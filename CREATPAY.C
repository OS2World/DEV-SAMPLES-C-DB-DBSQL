/* CreatPay.C */
/* Programs to Create Payroll Database and It's Tables */
/* Oct-19-1990 */

#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include "dbsql.h"

PSQLPROCESS pSqlProcess;

VOID main ( VOID );
VOID CreateEmployeeTable     ( PSQLPROCESS pSqlProcess );
VOID CreateStandardAcctTable ( PSQLPROCESS pSqlProcess );
VOID CreateAccountsTable     ( PSQLPROCESS pSqlProcess );
VOID CreateHoursTable	     ( PSQLPROCESS pSqlProcess );
VOID CreatePayPeriodTable    ( PSQLPROCESS pSqlProcess );


VOID main ( VOID )
{
    PSZ pszDatabaseName = "PAYROLL";

    printf ( "Program Started \n" );
    printf ( "Please Wait .....\n\n " );

    if ( SqlCreateDatabase ( pszDatabaseName, "Payroll Database", 'C' ) )
    {
	printf	( "Created Database: %s\n\n", pszDatabaseName );

	pSqlProcess = SqlOpenDB ( pszDatabaseName, "", "" );

	CreateEmployeeTable	( pSqlProcess );
	CreateStandardAcctTable ( pSqlProcess );
	CreateAccountsTable	( pSqlProcess );
	CreateHoursTable	( pSqlProcess );
	CreatePayPeriodTable	( pSqlProcess );

	SqlCloseDB ( pSqlProcess );
    }
    else
	printf	( "Error Createing Database: %s\n\n", pszDatabaseName );
}


VOID CreateEmployeeTable     ( PSQLPROCESS pSqlProcess )
{
    PSZ pszTableName = "Employee";

    SqlCommandf ( pSqlProcess, "CREATE Table %s ", pszTableName );
    SqlCommand	( pSqlProcess, "( " );
    SqlCommand	( pSqlProcess, "FirstName VARCHAR(15), " );
    SqlCommand	( pSqlProcess, "Middle    VARCHAR(15), " );
    SqlCommand	( pSqlProcess, "LastName  VARCHAR(20), " );
    SqlCommand	( pSqlProcess, "EmpNum    CHAR(5), " );
    SqlCommand	( pSqlProcess, "AdpNum    CHAR(6), " );
    SqlCommand	( pSqlProcess, "SSNum     CHAR(9), " );
    SqlCommand	( pSqlProcess, "DeptNum   SMALLINT, " );
    SqlCommand	( pSqlProcess, "JobTitle  VARCHAR(50) " );
    SqlCommand	( pSqlProcess, ") " );

    if ( SqlExecute ( pSqlProcess ) )
	printf	( "\tCreated Table: %s\n", pszTableName );
    else
	printf	( "\tError Createing Table: %s\n", pszTableName );
}


VOID CreateStandardAcctTable ( PSQLPROCESS pSqlProcess )
{
    PSZ pszTableName = "StdAcct";

    SqlCommandf ( pSqlProcess, "CREATE Table %s ", pszTableName );
    SqlCommand	( pSqlProcess, "( " );
    SqlCommand	( pSqlProcess, "EmpNum    CHAR(5), " );
    SqlCommand	( pSqlProcess, "Account   CHAR(8), " );
    SqlCommand	( pSqlProcess, "Center    CHAR(7), " );
    SqlCommand	( pSqlProcess, "Slid      CHAR(1), " );
    SqlCommand	( pSqlProcess, "Slac      CHAR(6) " );
    SqlCommand	( pSqlProcess, ") " );

    if ( SqlExecute ( pSqlProcess ) )
	printf	( "\tCreated Table: %s\n", pszTableName );
    else
	printf	( "\tError Createing Table: %s\n", pszTableName );
}


VOID CreateAccountsTable     ( PSQLPROCESS pSqlProcess )
{
    PSZ pszTableName = "Accounts";

    SqlCommandf ( pSqlProcess, "CREATE Table %s ", pszTableName );
    SqlCommand	( pSqlProcess, "( " );
    SqlCommand	( pSqlProcess, "Account   CHAR(8), " );
    SqlCommand	( pSqlProcess, "Center    CHAR(7), " );
    SqlCommand	( pSqlProcess, "Slid      CHAR(1), " );
    SqlCommand	( pSqlProcess, "Slac      CHAR(6), " );
    SqlCommand	( pSqlProcess, "Description VARCHAR(50) " );
    SqlCommand	( pSqlProcess, ") " );

    if ( SqlExecute ( pSqlProcess ) )
	printf	( "\tCreated Table: %s\n", pszTableName );
    else
	printf	( "\tError Createing Table: %s\n", pszTableName );
}


VOID CreateHoursTable	     ( PSQLPROCESS pSqlProcess )
{
    PSZ pszTableName = "Hours";

    SqlCommandf ( pSqlProcess, "CREATE Table %s ", pszTableName );
    SqlCommand	( pSqlProcess, "( " );
    SqlCommand	( pSqlProcess, "EmpNum    CHAR(5), " );
    SqlCommand	( pSqlProcess, "Account   CHAR(8), " );
    SqlCommand	( pSqlProcess, "Center    CHAR(7), " );
    SqlCommand	( pSqlProcess, "Slid      CHAR(1), " );
    SqlCommand	( pSqlProcess, "Slac      CHAR(6), " );
    SqlCommand	( pSqlProcess, "Rate      DECIMAL(8,4), " );
    SqlCommand	( pSqlProcess, "Hours     DECIMAL(5,2), " );
    SqlCommand	( pSqlProcess, "WeekDay   DATE " );
    SqlCommand	( pSqlProcess, ") " );

    if ( SqlExecute ( pSqlProcess ) )
	printf	( "\tCreated Table: %s\n", pszTableName );
    else
	printf	( "\tError Createing Table: %s\n", pszTableName );
}


VOID CreatePayPeriodTable    ( PSQLPROCESS pSqlProcess )
{
    PSZ pszTableName = "PayPeriod";

    SqlCommandf ( pSqlProcess, "CREATE Table %s ", pszTableName );
    SqlCommand	( pSqlProcess, "( " );
    SqlCommand	( pSqlProcess, "PeriodStart   DATE, " );
    SqlCommand	( pSqlProcess, "PeriodEnd   DATE, " );
    SqlCommand	( pSqlProcess, "MonthEnd   DATE " );
    SqlCommand	( pSqlProcess, ") " );

    if ( SqlExecute ( pSqlProcess ) )
	printf	( "\tCreated Table: %s\n", pszTableName );
    else
	printf	( "\tError Createing Table: %s\n", pszTableName );
}
