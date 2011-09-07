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
const char SQL_QUERY_DATE[] =
    "select strftime('%Y-%m-%d %H:%M:%f', 'now', 'localtime');";
const char SQL_DROP_TABLE[] =
    "drop table if exists %s;";
const char SQL_QUERY_TABLE_EXISTS[] =
    "select name from sqlite_master "
    "where type='table' and name='%s'";

/* based on cashio_tags */
const char SQL_CREATE_TABLE_TAGS[] =
    "create table if not exists cashio_tags ("
    "Tag varchar(255) primary key,"
    "Color int );";
const char SQL_INSERT_TAG[] =
    "insert into cashio_tags values('%s', %d);";
const char SQL_UPDATE_TAG[] =
    "update cashio_tags set Tag='%s', Color=%d;";
const char SQL_DROP_TAG[] =
    "drop from cashio_tags where Tag='%s';";
const char SQL_QUERY_TAGS_HAS_TAG[] =
    "select Tag from cashio_tags where Tag='%s';";

/* based on cashio_account */
const char SQL_CREATE_TABLE_ACCOUNT[] =
    "create table if not exists cashio_account ("
    "Date datetime primary key,"
    "IO varchar(255) not null,"
    "Amount double not null,"
    "Note text );";
const char SQL_INSERT_ACCOUNT[] =
    "insert into cashio_account values('%s', '%s', %.2f, '%s');";
const char SQL_UPDATE_ACCOUNT[] =
    "update cashio_account set IO='%s', Amount=%f, Note='%s' where Date='%s';";
const char SQL_DROP_ACCOUNT[] =
    "drop from cashio_account where Date='%s';";
const char SQL_QUERY_ACCOUNT_HAS_DATE[] =
    "select Date from cashio_account where Date='%s';";
const char SQL_QUERY_ACOUNT_ALL_DATE[] =
    "select Date from cashio_account order by Date;";
const char SQL_QUERY_ACCOUNT_ROW[] =
    "select * from cashio_account where Date='%s';";

/* based on cashio_account_tag */
const char SQL_CREATE_TABLE_ACCOUNT_TAG[] =
    "create table if not exists cashio_account_tag ("
    "ID integer primary key autoincrement,"
    "Date datetime,"
    "Tag varchar(255),"
    "foreign key(Date) references cashio_account(Date)"
    "   on delete cascade on update cascade,"
    "foreign key(Tag) references cashio_tags(Tag)"
    "   on delete cascade on update cascade );";
const char SQL_INSERT_ACCOUNT_TAG[] =
    "insert into cashio_account_tag values(null, '%s', '%s');";
const char SQL_DROP_ACCOUNT_TAG[] =
    "drop from cashio_account_tag where Date='%s' and Tag='%s';";
const char SQL_QUERY_ACCOUNT_TAG[] =
    "select Tag from cashio_account_tag where Date='%s';";

#endif // DBDEF_H
