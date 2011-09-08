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
    "select strftime('%Y-%m-%d %H:%M:%S', 'now', 'localtime');";
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
    "delete from cashio_tags where Tag='%s';";
const char SQL_QUERY_TAGS_HAS_TAG[] =
    "select Tag from cashio_tags where Tag='%s';";

/* based on cashio_account */
const char SQL_CREATE_TABLE_ACCOUNT[] =
    "create table if not exists cashio_account ("
    "Uuid text primary key,"
    "Date datetime,"
    "IO varchar(255) not null,"
    "Amount double not null,"
    "Note text );";
const char SQL_INSERT_ACCOUNT[] =
    "insert into cashio_account values('%s', '%s', '%s', %.2f, '%s');";
const char SQL_UPDATE_ACCOUNT[] =
    "update cashio_account set Date='%s', IO='%s', Amount=%f, Note='%s' where Uuid='%s';";
const char SQL_DELETE_ACCOUNT[] =
    "delete from cashio_account where Uuid='%s';";
const char SQL_QUERY_ACCOUNT_HAS_UUID[] =
    "select Uuid from cashio_account where Uuid='%s';";
const char SQL_QUERY_ACOUNT_ALL_DATE[] =
    "select Uuid from cashio_account order by Date desc;";
const char SQL_QUERY_ACCOUNT_ROW[] =
    "select Date,IO,Amount,Note from cashio_account where Uuid='%s';";

/* based on cashio_account_tag */
const char SQL_CREATE_TABLE_ACCOUNT_TAG[] =
    "create table if not exists cashio_account_tag ("
    "Uuid text primary key,"
    "AccountUuId text not null,"
    "Tag varchar(255) not null,"
    "foreign key(AccountUuId) references cashio_account(Uuid)"
    "   on delete cascade on update cascade,"
    "foreign key(Tag) references cashio_tags(Tag)"
    "   on delete cascade on update cascade );";
const char SQL_INSERT_ACCOUNT_TAG[] =
    "insert into cashio_account_tag values('%s', '%s', '%s');";
const char SQL_DELETE_ACCOUNT_TAG[] =
    "delete from cashio_account_tag where AccountUuId='%s';";
const char SQL_QUERY_ACCOUNT_TAG[] =
    "select Tag, Color from cashio_tags where Tag in ("
    "   select Tag from cashio_account_tag where AccountUuId='%s');";

#endif // DBDEF_H
