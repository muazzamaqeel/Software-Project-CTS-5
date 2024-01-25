#include "qtunittest.h"
#include "databasemanager.h"
#include <QtTest/QTest>

QTUnitTest::QTUnitTest()
{
    DatabaseManager dbManager;
    QVERIFY2(dbManager.getDatabase().isValid(), "Database connection failed to establish.");

}
