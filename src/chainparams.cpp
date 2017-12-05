// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Copyright (c) 2014-2017 The Dash Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
 *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
 *   vMerkleTree: e0028e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "18-01-14 - Anti-fracking campaigners chain themselves to petrol pumps";  // PM-Tech: ChainCoin
    const CScript genesisOutputScript = CScript() << ParseHex("04becedf6ebadd4596964d890f677f8d2e74fdcc313c6416434384a66d6d8758d1c92de272dc6713e4a81d98841dfdfdc95e204ba915447d2fe9313435c78af3e8") << OP_CHECKSIG; // PM-Tech: ChainCoin
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */


class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 700800; // PM-Tech: ChainCoin // 2 years
        consensus.nMasternodePaymentsStartBlock = 100000; // not true, but it's ok as long as it's less then nMasternodePaymentsIncreaseBlock
        consensus.nMasternodePaymentsIncreaseBlock = 2580000; // PM-Tech: to be defined
        consensus.nMasternodePaymentsIncreasePeriod = 576*30; // PM-Tech: to be defined
        consensus.nInstantSendKeepLock = 24;
        consensus.nBudgetPaymentsStartBlock = 1500000; // PM-Tech: to be defined
        consensus.nBudgetPaymentsCycleBlocks = 28800; // PM-Tech: to be defined
        consensus.nBudgetPaymentsWindowBlocks = 100;
        consensus.nBudgetProposalEstablishingTime = 60*60*24;
        consensus.nSuperblockStartBlock = 1600000; // PM-Tech: to be defined
        consensus.nSuperblockCycle = 28800; // PM-Tech: to be defined
        consensus.nGovernanceMinQuorum = 10;
        consensus.nGovernanceFilterElements = 20000;
        consensus.nMasternodeMinimumConfirmations = 15;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = 1;
        consensus.BIP34Hash = uint256S("0x00000012f1c40ff12a9e6b0e9076fe4fa7ad27012e256a5ad7bcb80dc02c0409"); // PM-Tech: ChainCoin
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000"); // PM-Tech: ChainCoin
        consensus.nPowTargetTimespan = 90; // PM-Tech: ChainCoin re-target at every block
        consensus.nPowTargetSpacing = 90; // PM-Tech: ChainCoin 90 seconds
        consensus.nInterval = 1; // PM-Tech: ChainCoin
        consensus.nAveragingInterval = 8; // PM-Tech: ChainCoin
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1916; // 95% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1508025600; // Oct 15th, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1539561600; // Oct 15th, 2018

        // Deployment of DIP0001
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nStartTime = 1508025600; // Oct 15th, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nTimeout = 1539561600; // Oct 15th, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nWindowSize = 4032;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nThreshold = 3226; // 80% of 4032

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000298679dd6a9ca29"); // 1300980 // PM-Tech: ChainCoin

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00000000006ca24b6c4eaf5235cae10e6fa3cb8717280cc1d79d438c46c01978"); //1300980 // PM-Tech: ChainCoin

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xa3; // PM-Tech: ChainCoin
        pchMessageStart[1] = 0xd2; // PM-Tech: ChainCoin
        pchMessageStart[2] = 0x7a; // PM-Tech: ChainCoin
        pchMessageStart[3] = 0x03; // PM-Tech: ChainCoin
        vAlertPubKey = ParseHex("04c5788ca1e268a7474763fa965210b6fa6b04a45f52d21056c62fb19a2de991aa15aa1d1c516f34d2a0016f51a87959c89f51a148db30c839f71bc525dde8c480"); // PM-Tech: ChainCoin
        nDefaultPort = 11994; // PM-Tech: ChainCoin
        nMaxTipAge = 6 * 60 * 60; // ~144 blocks behind -> 2 x fork detection time, was 24 * 60 * 60 in bitcoin
        nDelayGetHeadersTime = 24 * 60 * 60;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1390078220, 2099366979, 0x1e0fffff, 1, 16 * COIN); // PM-Tech: ChainCoin
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000f639db5734b2b861ef8dbccc33aebd7de44d13de000a12d093bcc866c64")); // PM-Tech: ChainCoin
        assert(genesis.hashMerkleRoot == uint256S("0xfa6ef9872494fa9662cf0fecf8c0135a6932e76d7a8764e1155207f3205c7c88")); // PM-Tech: ChainCoin


        vSeeds.push_back(CDNSSeedData("seed1.chaincoin.org", "seed1.chaincoin.org"));
        vSeeds.push_back(CDNSSeedData("seed2.chaincoin.org", "seed2.chaincoin.org"));
        vSeeds.push_back(CDNSSeedData("seed3.chaincoin.org", "seed3.chaincoin.org"));
        vSeeds.push_back(CDNSSeedData("seed4.chaincoin.org", "seed4.chaincoin.org"));
        vSeeds.push_back(CDNSSeedData("seed5.chaincoin.org", "seed5.chaincoin.org"));
        vSeeds.push_back(CDNSSeedData("seed6.chaincoin.org", "seed6.chaincoin.org"));
        vSeeds.push_back(CDNSSeedData("seed7.chaincoin.org", "seed7.chaincoin.org"));
        vSeeds.push_back(CDNSSeedData("seed8.chaincoin.org", "seed8.chaincoin.org"));
        vSeeds.push_back(CDNSSeedData("chc1.ignorelist.com", "chc1.ignorelist.com"));
        vSeeds.push_back(CDNSSeedData("chc2.ignorelist.com", "chc2.ignorelist.com"));
        vSeeds.push_back(CDNSSeedData("chc3.ignorelist.com", "chc3.ignorelist.com"));
        vSeeds.push_back(CDNSSeedData("chc4.ignorelist.com", "chc4.ignorelist.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,28); // PM-Tech: ChainCoin

        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,4); // PM-Tech: ChainCoin

        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,28 + 128); // PM-Tech: ChainCoin

        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0xFE)(0x52)(0xF8).convert_to_container<std::vector<unsigned char> >(); // PM-Tech: ChainCoin

        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0xFE)(0x52)(0xCC).convert_to_container<std::vector<unsigned char> >(); // PM-Tech: ChainCoin

        // Chaincoin BIP44 coin type is '5'
        nExtCoinType = 5;

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 60*60; // fulfilled requests expire in 1 hour
        strSporkPubKey = "04d30fc81685398b8a9f560145ca994f23cc38775e731ebf50f89ef7ead069c312c733ce17450b2c24fff3ed945e5bd096866d1445424f7ed81710f1a8e667ea5d";

        checkpointData = (CCheckpointData) // PM-Tech: ChainCoin
        {
            boost::assign::map_list_of
            (      0, uint256S("0x00000f639db5734b2b861ef8dbccc33aebd7de44d13de000a12d093bcc866c64"))
            (   6143, uint256S("0x0000000026fb51f5bc9943ed69d9ff7697ecf7fed419d88b417655f93a487ce1"))
            (  12797, uint256S("0x000000002c29644e179baa188fa6b9b9454721f1f21f2b9f31eebe9acc1a31db"))
            (  30092, uint256S("0x0000000098a23e1c503f71a6d61c333c5abaabb4c5fa1b474012e004db4bfbbe"))
            (  80998, uint256S("0x000000010ebcfe9a00a99f2b61104f4a141555a707f1c007aba8a978f6030cfb"))
            ( 144759, uint256S("0x000000047e7b7bfd63b4f019a0a24c8d65b10afa6eb80721e10fa7c49ce6fb6e"))
            ( 189046, uint256S("0x00000000bd507c435b46ee8a13b25b85ec38fdb0eb5b00faeaa0611cd6a483d3"))
            ( 277316, uint256S("0x00000016a20503fe496e79d34fb85c33f633059315c046ffa1b4826d08a1e856"))
            ( 483849, uint256S("0x000001eb7f8124282ab62296e63d3145ff6c84cf18afae4d4b8e02cd3182b6a8"))
            (1066428, uint256S("0x000000012dc5256d977b50270d1ca5642726308dcf26b6c219985edb8f2ab8f6")),

            1490629503, // * UNIX timestamp of last checkpoint block
            1179921,    // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            960         // * estimated number of transactions per day after checkpoint
        };
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 21024;
        consensus.nMasternodePaymentsStartBlock = 4010; // not true, but it's ok as long as it's less then nMasternodePaymentsIncreaseBlock
        consensus.nMasternodePaymentsIncreaseBlock = 4030;
        consensus.nMasternodePaymentsIncreasePeriod = 10;
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 4100;
        consensus.nBudgetPaymentsCycleBlocks = 50;
        consensus.nBudgetPaymentsWindowBlocks = 10;
        consensus.nBudgetProposalEstablishingTime = 60*20;
        consensus.nSuperblockStartBlock = 4200; // NOTE: Should satisfy nSuperblockStartBlock > nBudgetPeymentsStartBlock
        consensus.nSuperblockCycle = 24; // Superblocks can be issued hourly on testnet
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 500;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 100;
        consensus.BIP34Height = 1;
        consensus.BIP34Hash = uint256S("0x00000352de593a01e0efcbaec00345ec80d20c7bd2024ec7c2beec048af0e6d9");
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 90; // PM-Tech: ChainCoin
        consensus.nPowTargetSpacing = 90; // PM-Tech: ChainCoin
        consensus.nInterval = 1; // PM-Tech: ChainCoin
        consensus.nAveragingInterval = 8; // PM-Tech: ChainCoin
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1506556800; // September 28th, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1538092800; // September 28th, 2018

        // Deployment of DIP0001
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nStartTime = 1505692800; // Sep 18th, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nTimeout = 1537228800; // Sep 18th, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nWindowSize = 100;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nThreshold = 50; // 50% of 100

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("000000000000000000000000000000000000000000000000000000060e06d35d"); //2947

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("000000d9bd4820c3f64f31fb69d520baa5698d2700b5addfa4f27b264f2bc298"); //2947

        pchMessageStart[0] = 0xfb;
        pchMessageStart[1] = 0xc2;
        pchMessageStart[2] = 0x11;
        pchMessageStart[3] = 0x02;
        vAlertPubKey = ParseHex("040d3090a194381599d0f53f89ec60b9ec77f0e7b61978ef445142c8a4f1e154ca3441a5e46e12910540352edbd8af43fc1ee1da9a935c1c252fe7426c323d3d32");
        nDefaultPort = 21994;
        nMaxTipAge = 0x7fffffff; // allow mining on top of old blocks for testnet
        nDelayGetHeadersTime = 24 * 60 * 60;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1388868139, 423087994, 0x1e0fffff, 1, 16 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0000082f5939c2154dbcba35f784530d12e9d72472fcfaf29674ea312cdf4c83"));
        assert(genesis.hashMerkleRoot == uint256S("0xfa6ef9872494fa9662cf0fecf8c0135a6932e76d7a8764e1155207f3205c7c88"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,80);

        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,44);

        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,88+128);

        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3A)(0x80)(0x61)(0xA0).convert_to_container<std::vector<unsigned char> >();

        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3A)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();

        // Testnet Dash BIP44 coin type is '1' (All coin's testnet default)
        nExtCoinType = 1;

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes
        strSporkPubKey = "04d436c5ea78789b7bd4708c296b61cf2c0a14d0870245d164078e3c126dec0dd7ee041538437afd72508def9862f0f65160de94c9f48861a6a7b25bd59879eeef";

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (   0, uint256S("0x0000082f5939c2154dbcba35f784530d12e9d72472fcfaf29674ea312cdf4c83")),

            0, // * UNIX timestamp of last checkpoint block
            0,       // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            0         // * estimated number of transactions per day after checkpoint
        };

    }
};
static CTestNetParams testNetParams;

/**
 * Regression test taken straigt from Chaincoin except port and timing
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.nMasternodePaymentsStartBlock = 240;
        consensus.nMasternodePaymentsIncreaseBlock = 350;
        consensus.nMasternodePaymentsIncreasePeriod = 10;
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 1000;
        consensus.nBudgetPaymentsCycleBlocks = 50;
        consensus.nBudgetPaymentsWindowBlocks = 10;
        consensus.nBudgetProposalEstablishingTime = 60*20;
        consensus.nSuperblockStartBlock = 1500;
        consensus.nSuperblockCycle = 10;
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 100;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = -1; // BIP34 has not necessarily activated on regtest
        consensus.BIP34Hash = uint256();
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 90; // PM-Tech: ChainCoin 90s
        consensus.nPowTargetSpacing = 90; // PM-Tech: ChainCoin 90s
        consensus.nInterval = 1; // PM-Tech: ChainCoin
        consensus.nAveragingInterval = 8; // PM-Tech: ChainCoin
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nTimeout = 999999999999ULL;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xfc;
        pchMessageStart[1] = 0x1f;
        pchMessageStart[2] = 0xc3;
        pchMessageStart[3] = 0x56;
        nMaxTipAge = 6 * 60 * 60; // ~144 blocks behind -> 2 x fork detection time, was 24 * 60 * 60 in bitcoin
        nDelayGetHeadersTime = 0; // never delay GETHEADERS in regtests
        nDefaultPort = 18444;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1296688602, 3, 0x207fffff, 1, 16 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes

        checkpointData = (CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("0x000008ca1832a4baf228eb1553c03d3a2c8e02399550dd6ea8d65cec3ef23d2e")),
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,80);

        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,44);

        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,88+128);

        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3A)(0x80)(0x61)(0xA0).convert_to_container<std::vector<unsigned char> >();

        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3A)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();


        // Regtest Chaincoin BIP44 coin type is '1' (All coin's testnet default)
        nExtCoinType = 1;
   }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}
