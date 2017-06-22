#ifndef SQL_BUG_PROVIDER_H
#define SQL_BUG_PROVIDER_H

#include "bugtypes.h"
#include "sqlhelpers.h"

using namespace Ori::Sql;

class BugTableDef : public TableDef
{
public:
    BugTableDef() : TableDef("Issue") {}

    QString sqlSelectById(int id) const {
        return QString("SELECT * FROM %1 WHERE Id = %2").arg(tableName()).arg(id);
    }

    BugInfo recordToObject(const QSqlRecord& r) const;

//    DECLARE_COL(Id, QVariant::Int)
//    DECLARE_COL(Summary, QVariant::String)
//    DECLARE_COL(Extra, QVariant::String)
//    DECLARE_COL(Category, QVariant::Int)
//    DECLARE_COL(Severity, QVariant::Int)
//    DECLARE_COL(Priority, QVariant::Int)
//    DECLARE_COL(Repeat, QVariant::Int)
//    DECLARE_COL(Status, QVariant::Int)
//    DECLARE_COL(Solution, QVariant::Int)
//    DECLARE_COL(Created, QVariant::DateTime)
//    DECLARE_COL(Updated, QVariant::DateTime)
};

//-----------------------------------------------------------------------------------------------

class BugHistoryTableDef : public TableDef
{
public:
    BugHistoryTableDef() : TableDef("History") {}

    QString sqlSelectById(int id) const {
        return QString("SELECT * FROM %1 WHERE Issue = %2 ORDER BY EventNum").arg(tableName()).arg(id);
    }

    BugInfo recordToObject(const QSqlRecord& r) const;
};

//-----------------------------------------------------------------------------------------------

class BugRelationsTableDef : public TableDef
{
public:
    BugRelationsTableDef() : TableDef("Relations") {}

    QString sqlSelectById(int id) const {
        return QString("SELECT * FROM %1 WHERE Id1 = %2 OR Id2 = %2 ORDER BY Created").arg(tableName()).arg(id);
    }

    BugRelationItem recordToObject(const QSqlRecord& r) const;
};

//-----------------------------------------------------------------------------------------------

const BugTableDef& tableBugs();
const BugHistoryTableDef& tableHistory();
const BugRelationsTableDef& tableRelations();

//-----------------------------------------------------------------------------------------------

class SqlBugProvider : public BugProvider
{
public:
    BugHistoryResult getHistory(int id) override;
    //IntListResult getRelations(int id) override;
    QString bugParamName(int paramId) override;

//    bool isBugOpened(int status) override;
//    bool isBugClosed(int status) override;
//    bool isBugSolved(int status) override;

    //static BugInfo recordToBugInfo(const QSqlRecord& record);

private:
    BugHistoryItem::ChangedParam getChangedParam(const QSqlRecord& record);
};

#endif // SQL_BUG_PROVIDER_H

