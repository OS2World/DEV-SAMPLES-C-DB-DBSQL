/****************************************************************************/
/*                                                                          */
/* MODULE     : DBSQL.H                                                     */
/* TITLE      : Database Engine for C                                       */
/* ENVIROMENT : OS/2 Base Enviroment                                        */
/* VERSION    : 1.10                                                        */
/* STATUS     : ALPHA                                                       */
/*                                                                          */
/* DEVELOPED BY:                                                            */
/*      Bradley S. Gibson                                                   */
/*                                                                          */
/* COPYRIGHT:                                                               */
/*      Copyright (c) 1989, 1990 Bradley S. Gibson                          */
/*                                                                          */
/*  DESCRIPTION:                                                            */
/*                                                                          */
/* MODULE REQUIREMENTS:                                                     */
/*                                                                          */
/****************************************************************************/

#define SQL_MAXCMDBUF	1024
#define SQL_MAXPROCESS	64

#define DBSQLMSG    "DbSql.Msg"

typedef struct sqlda SQLDA;
typedef SQLDA *PSQLDA;

typedef struct tagBINDTYPE
{
    SHORT   sBindType;
    PBYTE   pBindAddress;
}BINDTYPE;

typedef BINDTYPE *PBINDTYPE;

typedef struct tagBINDVAR
{
    USHORT    cbBind;
    BINDTYPE  pBindType[1];
}BINDVAR;

typedef BINDVAR *PBINDVAR;

// BIND TYPES

#define BIND_NULL       0
#define BIND_BYTE       1
#define BIND_CHAR       2
#define BIND_SHORT      3
#define BIND_USHORT     4
#define BIND_LONG       5
#define BIND_ULONG      6
#define BIND_FLOAT      7
#define BIND_DOUBLE     8
#define BIND_DECIMAL    9
#define BIND_PSZ        10

typedef struct tagSQLPROCESS
{
    CHAR        szDbName[10];
    CHAR        szUserID[10];
    PSZ         pszCmdBuf;
    PSQLDA      pSqlDa;
    PBINDVAR	pBindVar;
    SHORT	sProcessNum;
}SQLPROCESS;

typedef SQLPROCESS *PSQLPROCESS;

typedef struct tagSQLCOLUMNINFO
{
    CHAR    szColumnName[31];
    SHORT   sSqlType;
    SHORT   sSqlLength;
}SQLCOLUMNINFO;

typedef struct tagVARCHAR
{
    short   sVarLen;
    char    achString[4000];
}VARCHAR;

typedef VARCHAR  *PVARCHAR;

typedef struct tagDECIMAL
{
    BYTE percision;
    BYTE scale;
    BYTE len;
    BYTE data[17];
}DECIMAL;

typedef DECIMAL   *PDECIMAL;

#define CEXPENTRY cdecl FAR _loadds

BOOL		CEXPENTRY  SqlCreateDatabase	( PSZ pszDbName, PSZ pszComment, CHAR cDrive );
PSQLPROCESS	CEXPENTRY  SqlOpenDB		( PSZ pszDbName );
VOID		CEXPENTRY  SqlCloseDB		( PSQLPROCESS pSqlProcess );
BOOL		CEXPENTRY  SqlCommand		( PSQLPROCESS pSqlProcess, PSZ pszSqlCmd );
BOOL		CEXPENTRY  SqlCommandf		( PSQLPROCESS pSqlProcess, PSZ pszSqlCmd, ... );
BOOL		CEXPENTRY  SqlExecute		( PSQLPROCESS pSqlProcess );
VOID		CEXPENTRY  SqlBindByNum 	( PSQLPROCESS pSqlProcess, USHORT usColNum, PVOID pVar, SHORT sBindType );
VOID		CEXPENTRY  SqlBindByName	( PSQLPROCESS pSqlProcess, PSZ pszColName, PVOID pVar, SHORT sBindType );
BOOL		CEXPENTRY  SqlResults		( PSQLPROCESS pSqlProcess );
BOOL		CEXPENTRY  SqlOpenCursor	( PSQLPROCESS pSqlProcess );
BOOL		CEXPENTRY  SqlCloseCursor	( PSQLPROCESS pSqlProcess );
BOOL		CEXPENTRY  SqlFetchRow		( PSQLPROCESS pSqlProcess );
BOOL		CEXPENTRY  SqlCommit		( PSQLPROCESS pSqlProcess );
BOOL		CEXPENTRY  SqlRollback		( PSQLPROCESS pSqlProcess );
BOOL		CEXPENTRY  SqlImport		( PSQLPROCESS pSqlProcess, PSZ pszTable, PSZ pszFile, SHORT sFileType, SHORT sInsert );
BOOL		CEXPENTRY  SqlExport		( PSQLPROCESS pSqlProcess, PSZ pszTable, PSZ pszFile, SHORT sFileType );
USHORT		CEXPENTRY  SqlGetNumberColumns	( PSQLPROCESS pSqlProcess );
SQLCOLUMNINFO	CEXPENTRY  SqlGetColumnNameInfo ( PSQLPROCESS pSqlProcess, SHORT sColNum );
PVOID		CEXPENTRY  SqlCreateColumnVar	( PSQLPROCESS pSqlProcess, SHORT sColNum );
VOID		CEXPENTRY  SqlDeleteColumnVar	( PSQLPROCESS pSqlProcess, PVOID pVar );
VOID		CEXPENTRY  SqlListDatabases	( VOID );
VOID		CEXPENTRY  SqlListTables	( PSQLPROCESS pSqlProcess );
VOID		CEXPENTRY  SqlListColumns	( PSQLPROCESS pSqlProcess );

PSQLDA AllocSqlDa       ( int );
void   FreeSqlDa        ( PSQLDA );
int    AllocRow         ( PSQLDA );
void   FreeRow          ( PSQLDA );
void   BindRow          ( PSQLPROCESS );
double PackedToDouble   ( BYTE, BYTE, BYTE, PBYTE );
