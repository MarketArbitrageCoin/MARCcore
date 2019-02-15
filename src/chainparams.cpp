// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017-2018 The Marcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0x0000043b8be3fff987f6b27edf365ecd65adc162da80a0efe66e0d5048a02f97"))
    (64799, uint256("0x3da4d8cd90b4f2ab367627ec63bcd6638a85a5147db6358d3dcad7c28980b1aa"))
    (138730, uint256("0xf92c48e57092be635c8b61d45a5e06ef50c0d8d265f757b6b9447fa9a50daf26"))
    (141800, uint256("0x3ec625ca2da018b389d132e16c89e7f6f6e6744a6c93532b22d4db2390e02343"))
    (153720, uint256("0xf74c1fbbf329fddcc2a69974f804bd5718c95fd37a8c79b382e9ae9bf540bd86"))
    (156640, uint256("0xdf6a545023d1a5c554e6bcc9d41cb4989ea970d92fbeb034cbb4018fcbb9561c"))
    (160600, uint256("0x65e68d596dce347ae726c69bf5a0be5b42828c5bbe5aac63ee119b67a76445d0"))
    (168180, uint256("0xc0f79526c1afe5aa30469d4760206bf0d5c39d4a5b6affa89e93afa3458e7d9e"));


static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1550253833, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1740710,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x53;
        pchMessageStart[1] = 0xdb;
        pchMessageStart[2] = 0x11;
        pchMessageStart[3] = 0xad;
        vAlertPubKey = ParseHex("04b5ffd1ea6a33d60943a5b73070cc37797a04f645c2826ed88c236aae2328a47b2917f39c578955fa1c6b7af3f48af74c03abed1bd2ec554c2caa55edaff06420");
        nDefaultPort = 44004;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nSubsidyHalvingInterval = 1050000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Marcoin: 1 day
        nTargetSpacing = 2 * 60;  // Marcoin: 2 minutes
        nMaturity = 20;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 21000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;
        nModifierUpdateBlock = 1; // we use the version 2 for MARC

        const char* pszTimestamp = "Market Arbitrage Coin (MARC) was born";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("049b55d4a358c8aaca60149433f74c51c3b8267274d9da3ccb0d755922072d1e0f15c9c8ab905aa37ba5701c28fa89f69de063b182cdefc3a7440b9546128ebb02") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1536844393;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 757440;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000043b8be3fff987f6b27edf365ecd65adc162da80a0efe66e0d5048a02f97"));
        assert(genesis.hashMerkleRoot == uint256("0x5040be248dfe5a0c1b5b4a2249cf234a79832bbea9db264588b4b6ef4e842d10"));

        vSeeds.push_back(CDNSSeedData("seed1", "95.179.167.15"));  
        vSeeds.push_back(CDNSSeedData("seed2", "45.75.35.213"));  
        vSeeds.push_back(CDNSSeedData("seed3", "95.179.155.161"));  
        vSeeds.push_back(CDNSSeedData("seed4", "95.179.182.251"));
        vSeeds.push_back(CDNSSeedData("seed5", "95.179.142.133"));
        vSeeds.push_back(CDNSSeedData("seed6", "95.179.130.173"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 50);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 179);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0xde).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true; 
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true; 
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false; 
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false; 

        nPoolMaxTransactions = 3;
        strSporkKey = "0438a0bea56c19e62fec60b0fd7944b8a5e49bf47a237ff6d2b3f1a7bf5a8d1f3bf016ba9432c8b3641f71be3947bf662313e07272e1715546818165088a1add9b";
        strMasternodePoolDummyAddress = "MLEYML1mCq9u5GFM6rE44nD71vwrYvequm";
        nStartMasternodePayments = genesis.nTime + 86400; // 24 hours after genesis creation

        nBudget_Fee_Confirmations = 7; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x33;
        pchMessageStart[1] = 0x8a;
        pchMessageStart[2] = 0xe5;
        pchMessageStart[3] = 0xa8;
        vAlertPubKey = ParseHex("04ba89975265af1d4c6295d3587eb4a0e4b758bde1621ef2ab8f92b98e7ed1c85547c9b7a3f145a66aa2abb91db5c13295828e77d823ea6d9b4bb89912425e1efe");
        nDefaultPort = 44014;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Marcoin: 1 day
        nTargetSpacing = 2 * 60;  // Marcoin: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1;
        nMaxMoneyOut = 21000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1534570200;
        genesis.nNonce = 21148656;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x4d675a9630cec707e743c2f791f75cdb351fba62976a43cce95c6e478ff042ae"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 12);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 108);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "042618a580837586a9698ed56d2e4bc61d43fa9aca6433c2d21e3fb955b6b6523c6f8df1e755d48c553b7bedc16da241bf8c31e619216d1b50666ed07eb145b840";
        strMasternodePoolDummyAddress = "MbJ4Qad4xc77PpLzMx6rUegAs6aUPWkcUq";
        nStartMasternodePayments = genesis.nTime + 86400; // 24 hours after genesis
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x20;
        pchMessageStart[1] = 0xee;
        pchMessageStart[2] = 0x32;
        pchMessageStart[3] = 0xbc;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Marcoin: 1 day
        nTargetSpacing = 2 * 60;        // Marcoin: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1536844393;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 757440;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 44015;
        assert(hashGenesisBlock == uint256("0xfd6c53ed3061c4b3869d8022336c3d6ad8e9afb04abbf733c43fdad837c342f8"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 44016;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
