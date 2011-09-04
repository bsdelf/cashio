#ifndef DBDEF_H
#define DBDEF_H

// for app store config
const char DB_CONF[] = "conf.db";
const char TABLE_CONF[] = "conf";

// for custom data
const char DB_DEFAULT[] = "a.db";
const char TABLE_TAGS[] = "cashio_tags";
const char TABLE_ACCOUNT_MISC[] = "cashio_account_misc";
const char TABLE_ACCOUNT_MISC_TAG[] = "cashio_account_misc_tag";
const char TABLE_ACCOUNT_ARCHIVE[] = "cashio_account_archive_%s";
const char TABLE_ACCOUNT_ARCHIVE_TAG[] = "cashio_account_archive_tag_%s";

// common sql command
const char SQL_BEGIN[] = "BEGIN;";
const char SQL_COMMIT[] = "COMMIT;";
const char SQL_CREATE_TABLE_TAGS[] =
    "create table if not exists %s ("
    "Tag varchar(255) primary key);";
const char SQL_CREATE_TABLE_ACCOUNT[] =
    "create table if not exists %s ("
    "InsTime datetime primary key,"
    "InOut int,"
    "CashAmount double);";
const char SQL_CREATE_TABLE_ACCOUNT_TAG[] =
    "create table if not exists %s ("
    "ID integer primary key autoincrement,"
    "InsTime datetime,"
    "IOTag varchar(255));";
const char SQL_DROP_TABLE[] =
    "drop table if exists %s;";
const char SQL_QUERY_TABLE_EXISTS[] =
    "select name from sqlite_master "
    "where type='table' and name='%s'";

#endif // DBDEF_H
