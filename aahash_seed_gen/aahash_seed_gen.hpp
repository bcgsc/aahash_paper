/*
 *
 * aahash_seed_gen.cpp
 * Author: Johnathan Wong
 * Canada's Michael Smith Genome Sciences Centre at BC Cancer
 * Modified from seedgen.cpp by Hamid Mohamadi
 */

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>

#define __STDC_FORMAT_MACROS
#include <inttypes.h>

void print_bin(uint64_t n)
{
    int count = 0, count1 = 0;
    while (++count <= 64)
    {
        if (n & ((uint64_t)1 << 63))
        {
            printf("1 ");
            ++count1;
        }
        else
            printf("0 ");
        n <<= 1;
    }
    printf(" count1=%d\n", count1);
}

void aahash_balance_seed()
{
    srand(time(NULL));

    const int seed_num = 20;
    std::vector<int> r1(seed_num, 32);
    int hash_seed[seed_num][64];
    for (int i = 0; i < seed_num; i++)
        for (int j = 0; j < 64; j++)
            hash_seed[i][j] = 0;

    for (int j = 0; j < 64; j++)
    {
        int ran_vec[seed_num];
        for (int i = 0; i < seed_num; i++)
            ran_vec[i] = i;
        for (int i = 0; i < seed_num / 2; i++)
        {
            int ran_ind = rand() % (seed_num - i);
            int tmp = ran_vec[seed_num - i - 1];
            ran_vec[seed_num - i - 1] = ran_vec[ran_ind];
            ran_vec[ran_ind] = tmp;
        }

        int counter = 0;
        for (int i = 0; i < seed_num; i++)
        {
            if (r1[ran_vec[i]] > 0)
            {
                hash_seed[ran_vec[i]][j] = 1;
                r1[ran_vec[i]]--;
                counter++;
                if (counter == seed_num / 2)
                    break;
            }
            if (seed_num - (i + 1) == seed_num / 2 - counter)
            {
                for (int k = i + 1; k < seed_num; ++k)
                {
                    hash_seed[ran_vec[k]][j] = 1;
                    r1[ran_vec[k]]--;
                    counter++;
                }
                break;
            }
        }
    }

    std::vector<int> ones_counter(64, 0);
    long long unsigned int all_seed[seed_num];
    for (int i = 0; i < seed_num; i++)
    {
        uint64_t h_seed = 0;
        for (int j = 0; j < 64; j++)
        {
            if (hash_seed[i][j] == 1)
                h_seed = (uint64_t)(h_seed << 1 | 1);
            else
                h_seed = (uint64_t)(h_seed << 1 | 0);
        }
        all_seed[i] = h_seed;
    }

    printf("static const uint64_t AAseedA = 0x%llx;\n", all_seed[0]);
    printf("static const uint64_t AAseedC = 0x%llx;\n", all_seed[1]);
    printf("static const uint64_t AAseedD = 0x%llx;\n", all_seed[2]);
    printf("static const uint64_t AAseedE = 0x%llx;\n", all_seed[3]);
    printf("static const uint64_t AAseedF = 0x%llx;\n", all_seed[4]);
    printf("static const uint64_t AAseedG = 0x%llx;\n", all_seed[5]);
    printf("static const uint64_t AAseedH = 0x%llx;\n", all_seed[6]);
    printf("static const uint64_t AAseedI = 0x%llx;\n", all_seed[7]);
    printf("static const uint64_t AAseedK = 0x%llx;\n", all_seed[8]);
    printf("static const uint64_t AAseedL = 0x%llx;\n", all_seed[9]);
    printf("static const uint64_t AAseedM = 0x%llx;\n", all_seed[10]);
    printf("static const uint64_t AAseedN = 0x%llx;\n", all_seed[11]);
    printf("static const uint64_t AAseedP = 0x%llx;\n", all_seed[12]);
    printf("static const uint64_t AAseedQ = 0x%llx;\n", all_seed[13]);
    printf("static const uint64_t AAseedR = 0x%llx;\n", all_seed[14]);
    printf("static const uint64_t AAseedS = 0x%llx;\n", all_seed[15]);
    printf("static const uint64_t AAseedT = 0x%llx;\n", all_seed[16]);
    printf("static const uint64_t AAseedV = 0x%llx;\n", all_seed[17]);
    printf("static const uint64_t AAseedW = 0x%llx;\n", all_seed[18]);
    printf("static const uint64_t AAseedY = 0x%llx;\n", all_seed[19]);
}

void aahash_level_2_balance_seed()
{
    srand(time(NULL));

    const int seed_num = 22;
    std::vector<int> r1(seed_num, 32);
    int hash_seed[seed_num][64];
    for (int i = 0; i < seed_num; i++)
        for (int j = 0; j < 64; j++)
            hash_seed[i][j] = 0;

    for (int j = 0; j < 64; j++)
    {
        int ran_vec[seed_num];
        for (int i = 0; i < seed_num; i++)
            ran_vec[i] = i;
        for (int i = 0; i < seed_num / 2; i++)
        {
            int ran_ind = rand() % (seed_num - i);
            int tmp = ran_vec[seed_num - i - 1];
            ran_vec[seed_num - i - 1] = ran_vec[ran_ind];
            ran_vec[ran_ind] = tmp;
        }

        int counter = 0;
        for (int i = 0; i < seed_num; i++)
        {
            if (r1[ran_vec[i]] > 0)
            {
                hash_seed[ran_vec[i]][j] = 1;
                r1[ran_vec[i]]--;
                counter++;
                if (counter == seed_num / 2)
                    break;
            }
            if (seed_num - (i + 1) == seed_num / 2 - counter)
            {
                for (int k = i + 1; k < seed_num; ++k)
                {
                    hash_seed[ran_vec[k]][j] = 1;
                    r1[ran_vec[k]]--;
                    counter++;
                }
                break;
            }
        }
    }

    std::vector<int> ones_counter(64, 0);
    long long unsigned int all_seed[seed_num];
    for (int i = 0; i < seed_num; i++)
    {
        uint64_t h_seed = 0;
        for (int j = 0; j < 64; j++)
        {
            if (hash_seed[i][j] == 1)
                h_seed = (uint64_t)(h_seed << 1 | 1);
            else
                h_seed = (uint64_t)(h_seed << 1 | 0);
        }
        all_seed[i] = h_seed;
    }
    printf("static const uint64_t AA_SEED_C___ = 0x%llx;\n", all_seed[0] ^ all_seed[11]);
    printf("static const uint64_t AA_SEED_G___ = 0x%llx;\n", all_seed[1] ^ all_seed[12]);
    printf("static const uint64_t AA_SEED_A___ = 0x%llx;\n", all_seed[2] ^ all_seed[13]);
    printf("static const uint64_t AA_SEED_TS__ = 0x%llx;\n", all_seed[3] ^ all_seed[14]);
    printf("static const uint64_t AA_SEED_N___ = 0x%llx;\n", all_seed[4] ^ all_seed[15]);
    printf("static const uint64_t AA_SEED_DE__ = 0x%llx;\n", all_seed[5] ^ all_seed[16]);
    printf("static const uint64_t AA_SEED_QKR_ = 0x%llx;\n", all_seed[6] ^ all_seed[17]);
    printf("static const uint64_t AA_SEED_VILM = 0x%llx;\n", all_seed[7] ^ all_seed[18]);
    printf("static const uint64_t AA_SEED_WFY_ = 0x%llx;\n", all_seed[8] ^ all_seed[19]);
    printf("static const uint64_t AA_SEED_H___ = 0x%llx;\n", all_seed[9] ^ all_seed[20]);
    printf("static const uint64_t AA_SEED_P___ = 0x%llx;\n", all_seed[10] ^ all_seed[21]);
}

void aahash_level_3_balance_seed()
{
    srand(time(NULL));
    std::cerr << "checkpoint A" << std::endl;

    const int seed_num = 18;
    std::vector<int> r1(seed_num, 32);
    int hash_seed[seed_num][64];
    for (int i = 0; i < seed_num; i++)
        for (int j = 0; j < 64; j++)
            hash_seed[i][j] = 0;

    for (int j = 0; j < 64; j++)
    {
        int ran_vec[seed_num];
        for (int i = 0; i < seed_num; i++)
            ran_vec[i] = i;
        for (int i = 0; i < seed_num / 2; i++)
        {
            int ran_ind = rand() % (seed_num - i);
            int tmp = ran_vec[seed_num - i - 1];
            ran_vec[seed_num - i - 1] = ran_vec[ran_ind];
            ran_vec[ran_ind] = tmp;
        }

        int counter = 0;
        for (int i = 0; i < seed_num; i++)
        {
            if (r1[ran_vec[i]] > 0)
            {
                hash_seed[ran_vec[i]][j] = 1;
                r1[ran_vec[i]]--;
                counter++;
                if (counter == seed_num / 2)
                    break;
            }
            if (seed_num - (i + 1) == seed_num / 2 - counter)
            {
                for (int k = i + 1; k < seed_num; ++k)
                {
                    hash_seed[ran_vec[k]][j] = 1;
                    r1[ran_vec[k]]--;
                    counter++;
                }
                break;
            }
        }
    }

    std::vector<int> ones_counter(64, 0);
    long long unsigned int all_seed[seed_num];
    for (int i = 0; i < seed_num; i++)
    {
        uint64_t h_seed = 0;
        for (int j = 0; j < 64; j++)
        {
            if (hash_seed[i][j] == 1)
                h_seed = (uint64_t)(h_seed << 1 | 1);
            else
                h_seed = (uint64_t)(h_seed << 1 | 0);
        }
        all_seed[i] = h_seed;
    }

    printf("static const uint64_t AA_SEED_C___ = 0x%llx;\n", all_seed[0] ^ all_seed[9]);
    printf("static const uint64_t AA_SEED_G___ = 0x%llx;\n", all_seed[1] ^ all_seed[10]);
    printf("static const uint64_t AA_SEED_ATS_ = 0x%llx;\n", all_seed[2] ^ all_seed[11]);
    printf("static const uint64_t AA_SEED_NDE_ = 0x%llx;\n", all_seed[3] ^ all_seed[12]);
    printf("static const uint64_t AA_SEED_QKR_ = 0x%llx;\n", all_seed[4] ^ all_seed[13]);
    printf("static const uint64_t AA_SEED_VILM = 0x%llx;\n", all_seed[5] ^ all_seed[14]);
    printf("static const uint64_t AA_SEED_WFY_ = 0x%llx;\n", all_seed[6] ^ all_seed[15]);
    printf("static const uint64_t AA_SEED_H___ = 0x%llx;\n", all_seed[7] ^ all_seed[16]);
    printf("static const uint64_t AA_SEED_P___ = 0x%llx;\n", all_seed[8] ^ all_seed[17]);
}
