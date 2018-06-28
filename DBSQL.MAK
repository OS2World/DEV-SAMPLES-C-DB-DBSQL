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

DbSql.LIB   :	DbSql.obj
    LIB DbSql.lib -+DbSql.obj;
