#ifndef DBDEF_H
#define DBDEF_H

/* for app store config */
const char DB_CONF[] = "conf.db";
const char TABLE_CONF[] = "conf";

/* for custom data */
const char DB_DEFAULT[] = "a.db";
const char TABLE_TAGS[] = "cashio_tags";
const char TABLE_ACCOUNT[] = "cashio_account";
const char TABLE_ACCOUNT_TAG[] = "cashio_account_tag";
//const char TABLE_ACCOUNT_ARCHIVE[] = "cashio_account_archive_%s";
//const char TABLE_ACCOUNT_ARCHIVE_TAG[] = "cashio_account_archive_tag_%s";

/* common sql command */
const char SQL_BEGIN[] = "BEGIN;";
const char SQL_COMMIT[] = "COMMIT;";
const char SQL_CREATE_TABLE_TAGS[] =
    "create table if not exists cashio_tags ("
    "Tag varchar(255) primary key,"
    "Color int );";
const char SQL_CREATE_TABLE_ACCOUNT[] =
    "create table if not exists cashio_account ("
    "Date datetime primary key,"
    "IO varchar(255) not null,"
    "Amount double not null,"
    "Note text );";
const char SQL_CREATE_TABLE_ACCOUNT_TAG[] =
    "create table if not exists cashio_account_tag ("
    "ID integer primary key autoincrement,"
    "Date datetime,"
    "Tag varchar(255),"
    "foreign key(Date) references cashio_account(Date)"
    "   on delete cascade on update cascade,"
    "foreign key(Tag) references cashio_tags(Tag)"
    "   on delete cascade on update cascade );";
const char SQL_DROP_TABLE[] =
    "drop table if exists %s;";
const char SQL_QUERY_TABLE_EXISTS[] =
    "select name from sqlite_master "
    "where type='table' and name='%s'";
const char SQL_QUERY_DATE[] =
    "select strftime('%Y-%m-%d %H:%M:%f', 'now', 'localtime');";

#endif // DBDEF_H
