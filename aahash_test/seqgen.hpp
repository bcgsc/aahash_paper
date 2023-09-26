#ifndef SEQGEN_H_
#define SEQGEN_H_

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <btllib/randseq.hpp>

using namespace std;

void make_seq(const size_t rNum, const size_t rLen, std::string file_name)
{
    srand(time(NULL));
    ofstream rFile(file_name);

    for (size_t j = 0; j < rNum; j++)
    {
        rFile << ">f" << j << "\n";
        btllib::RandSeq protein_seq(btllib::RandSeq::SeqType::PROTEIN,
                                    btllib::RandSeq::Masking::NONE);

        rFile << protein_seq.generate(rLen)
              << "\n";
    }

    rFile.close();
}

void make_db(const size_t gNum, const size_t gLen, const size_t rNum, const size_t rLen, std::string db_name, std::string db_subseq_name)
{
    srand(time(NULL));
    string mygSeq;
    ofstream gFile(db_name);
    ofstream rFile(db_subseq_name);
    for (size_t j = 0; j < gNum; j++)
    {
        btllib::RandSeq protein_seq(btllib::RandSeq::SeqType::PROTEIN,
                                    btllib::RandSeq::Masking::NONE);
        mygSeq = protein_seq.generate(gLen);
        gFile << ">g" << j << "\n"
              << mygSeq << "\n";
        for (size_t k = 0; k < rNum / gNum; k++)
        {
            int ranR = rand() % (gLen - rLen + 1);
            rFile << ">t" << k << "\n"
                  << mygSeq.substr(ranR, rLen) << "\n";
        }
    }
    gFile.close();
    rFile.close();
}

#endif
