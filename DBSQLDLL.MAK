# DbSql
#
# Make File
#
# Build Interface to OS/2 EE 1.2 DBM

.sqc.c:
        sqlprep $*.sqc  Sample /b

.c.obj:
        cl -c -Alfu -G2s -W2 -Zi $*.c


DbSql.C     :	DbSql.sqc

DbSql.OBJ   :	DbSql.c     DbSql.h

DbSql.DLL   :   DbSql.obj
        link /noi DbSql.obj, DbSql.dll /align:16, NUL, /nod llibcdll+os2+Sql_Stat+Sql_Dyn, DbSql.def
        implib DbSql.lib DbSql.Def
