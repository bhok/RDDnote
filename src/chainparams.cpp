// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "assert.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

//
// Main network
//

unsigned int pnSeed[] =
{
    0x12345678, 
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xb2;
        pchMessageStart[1] = 0xc2;
        pchMessageStart[2] = 0xcf;
        pchMessageStart[3] = 0x02;
        vAlertPubKey = ParseHex("046a83ab6fca24a3e4e748af248574741aa35840dcb1d77db686a9a7129d1d665dabfc86617f34b6f645abf38db9074a058b6c02daabea0e751efce9bc568395c9");
        nDefaultPort = 45450;
        nRPCPort = 45451;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        nSubsidyHalvingInterval = 210000;

        // PoSV
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 20);
        nLastProofOfWorkHeight = 10000 - 1;
        nStakeMinAge = 8 * 60 * 60; // 8 hours
        nStakeMaxAge = 45 * 24 *  60 * 60; // 45 days

        // Genesis Block:
        // CBlock(hash=12a765e31ffd4059bada, PoW=0000050c34a64b415b6b, ver=1, hashPrevBlock=00000000000000000000, hashMerkleRoot=97ddfbbae6, nTime=1317972665, nBits=1e0ffff0, nNonce=2084524493, vtx=1)
        //   CTransaction(hash=97ddfbbae6, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        //     CTxIn(COutPoint(0000000000, -1), coinbase 04ffff001d0104404e592054696d65732030352f4f63742f32303131205374657665204a6f62732c204170706c65e280997320566973696f6e6172792c2044696573206174203536)
        //     CTxOut(nValue=50.00000000, scriptPubKey=040184710fa689ad5023690c80f3a4)
        //   vMerkleTree: 97ddfbbae6
        const char* pszTimestamp = "VectoriumPlus - In CryptoEnergy we trust";
        CTransaction txNew(1548861334);
        txNew.nVersion = 1;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 1 * COIN;                
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("048a7ba09aecbd3d24b1c95234cc112a757b2f010dae568a99cb3ad1539b3f1256b0426631587330c7ea0bcccc4df7b4c522eafc8300a5736f302210f7f94e2233") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1548861334;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 222583475;
	    
	     // If genesis block hash does not match, then generate new genesis hash.
           if (block.GetHash() != hashGenesisBlock)
           {
               printf("Searching for genesis block...\n");
               // This will figure out a valid hash and Nonce if you're
               // creating a different genesis block:
               uint256 hashTarget = CBigNum().SetCompact(block.nBits).getuint256();
               uint256 thash;

               while(true)
               {
                   thash = scrypt_blockhash(BEGIN(block.nVersion));
                   if (thash <= hashTarget)
                       break;
                   if ((block.nNonce & 0xFFF) == 0)
                   {
                       printf("nonce %08X: hash = %s (target = %s)\n", block.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
                   }
                   ++block.nNonce;
                   if (block.nNonce == 0)
                   {
                       printf("NONCE WRAPPED, incrementing time\n");
                       ++block.nTime;
                   }
               }
               printf("block.nTime = %u \n", block.nTime);
               printf("block.nNonce = %u \n", block.nNonce);
               printf("block.GetHash = %s\n", block.GetHash().ToString().c_str());

         //if (true  && (genesis.GetHash() != hashGenesisBlock)) {
		// This will figure out a valid hash and Nonce if you're
		// creating a different genesis block:
		//	uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
		//	while (genesis.GetHash() > hashTarget)
		//	   {
			//	   ++genesis.nNonce;
			//	   if (genesis.nNonce == 0)
			//	   {
			//		   LogPrintf("NONCE WRAPPED, incrementing time");
			//		   ++genesis.nTime;
			//	   }
			 //  }
       // }
       // LogPrintf("block.GetHash() == %s\n", genesis.GetHash().ToString().c_str());
       // LogPrintf("block.hashMerkleRoot == %s\n", genesis.hashMerkleRoot.ToString().c_str());
       // LogPrintf("block.nTime = %u \n", genesis.nTime);
       // LogPrintf("block.nNonce = %u \n", genesis.nNonce);//* 
       
       
      
        hashGenesisBlock = genesis.GetHash();    
        assert(hashGenesisBlock == uint256("0xb868e0d95a3c3c0e0dadc67ee587aaf9dc8acbf99e3b4b3110fad4eb74c1decc"));
        assert(genesis.hashMerkleRoot == uint256("0xb502bc1dc42b07092b9187e92f70e32f9a53247feae16d821bebffa916af79ff"));

        vSeeds.push_back(CDNSSeedData("seed1-vctp.vectorium.co", "seed1-vctp.vectorium.co"));
        vSeeds.push_back(CDNSSeedData("seed2-vctp.vectorium.co", "seed2-vctp.vectorium.co"));
        vSeeds.push_back(CDNSSeedData("seed3-vctp.vectorium.co", "seed3-vctp.vectorium.co"));
        vSeeds.push_back(CDNSSeedData("seed4-vctp.vectorium.co", "seed4-vctp.vectorium.co"));
        vSeeds.push_back(CDNSSeedData("seed5-vctp.vectorium.co", "seed5-vctp.vectorium.co"));
        
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,71);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,33);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,199);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' of between one and two
            // weeks ago.
            const int64_t nOneWeek = 7*24*60*60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
            vFixedSeeds.push_back(addr);
        }
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x02;
        pchMessageStart[1] = 0xb3;
        pchMessageStart[2] = 0xb3;
        pchMessageStart[3] = 0xde;
        vAlertPubKey = ParseHex("0430bfe4ea2fc27e5d606f397d4cfc45b672a8a2e794277cbb6725a2c2e45eb466c4ea516f261e11695606691ea7e32769d6e62ddc24411a688bb884b2147c9f2b");
        nDefaultPort = 55460;
        nRPCPort = 55461;
        strDataDir = "testnet";
        nLastProofOfWorkHeight = 300 - 1; // Last POW block

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        // CTransaction txGenesis = genesis.vtx[0];
        genesis.nTime = 1548861300 ;
        // genesis.vtx[0] = txGenesis;
        genesis.nNonce = 2108003;
        
        
                if (true  && (genesis.GetHash() != hashGenesisBlock)) {
		// This will figure out a valid hash and Nonce if you're
		// creating a different genesis block:
			uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
			while (genesis.GetHash() > hashTarget)
			   {
				   ++genesis.nNonce;
				   if (genesis.nNonce == 0)
				   {
					   LogPrintf("NONCE WRAPPED, incrementing time");
					   ++genesis.nTime;
				   }
			   }
        }
        LogPrintf("block.GetHash() == %s\n", genesis.GetHash().ToString().c_str());
        LogPrintf("block.hashMerkleRoot == %s\n", genesis.hashMerkleRoot.ToString().c_str());
        LogPrintf("block.nTime = %u \n", genesis.nTime);
        LogPrintf("block.nNonce = %u \n", genesis.nNonce);
        
	hashGenesisBlock = genesis.GetHash();    
        assert(hashGenesisBlock == uint256("0x"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("testnet-vctp.vectorium.co", "testnet-vctp.vectorium.co"));
        

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,127);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0x04;
        pchMessageStart[1] = 0x03;
        pchMessageStart[2] = 0xba;
        pchMessageStart[3] = 0xba;
        nSubsidyHalvingInterval = 150;
        bnProofOfWorkLimit = bnProofOfStakeLimit = CBigNum(~uint256(0) >> 1);
        nLastProofOfWorkHeight = 350 - 1;
        genesis.nTime = 1548861000 ;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 3;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 56444;
        strDataDir = "regtest";
        assert(hashGenesisBlock == uint256("0x"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
