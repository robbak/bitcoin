#define BOOST_TEST_MODULE Bitcoin Test Suite
#include <boost/test/unit_test.hpp>

#include bitcoin-db.h
#include "txdb.h"
#include "main.h"
#include "wallet.h"

CWallet* pwalletMain;
CClientUIInterface uiInterface;

extern bool fPrintToConsole;
extern void noui_connect();

struct TestingSetup {
    CCoinsViewDB *pcoinsdbview;

    TestingSetup() {
        fPrintToDebugger = true; // don't want to write to debug.log file
        noui_connect();
        bitdb.MakeMock();
        pblocktree = new CBlockTreeDB(1 << 20, true);
        pcoinsdbview = new CCoinsViewDB(1 << 23, true);
        pcoinsTip = new CCoinsViewCache(*pcoinsdbview);
        LoadBlockIndex();
        bool fFirstRun;
        pwalletMain = new CWallet("wallet.dat");
        pwalletMain->LoadWallet(fFirstRun);
        RegisterWallet(pwalletMain);
    }
    ~TestingSetup()
    {
        delete pwalletMain;
        pwalletMain = NULL;
        delete pcoinsTip;
        delete pcoinsdbview;
        delete pblocktree;
        bitdb.Flush(true);
    }
};

BOOST_GLOBAL_FIXTURE(TestingSetup);

void Shutdown(void* parg)
{
  exit(0);
}

void StartShutdown()
{
  exit(0);
}

