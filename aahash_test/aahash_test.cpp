/*
 *
 * aahash_test.cpp
 * Author: Johnathan Wong
 * Canada's Michael Smith Genome Sciences Centre at BC Cancer
 * Modified from nttest.cpp by Hamid Mohamadi
 */

#include <string>
#include <iostream>
#include <limits>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdint.h>
#include <unistd.h>
#include <getopt.h>
#include "seqgen.hpp"
#include "rabin_karp.hpp"
#include "BloomFilter.hpp"
#include <btllib/aahash.hpp>

#ifdef _OPENMP
#include <omp.h>
#endif

#define PROGRAM "aahash_test"

static const char VERSION_MESSAGE[] =
    PROGRAM " Version 1.0.0 \n"
            "Written by Johnathan Wong.\n"
            "Copyright 2023 Canada's Michael Smith Genome Science Centre\n";

static const char USAGE_MESSAGE[] =
    "Usage: " PROGRAM " [OPTION]... QUERY\n"
    "Report bugs to jowong@bcgsc.ca.\n";

namespace opt
{
    unsigned threads = 1;
    unsigned kmer_len = 50;
    unsigned ibits = 8;
    unsigned num_hash = 1;
    unsigned dummy; // dummy variable
    unsigned level = 1;
    size_t num_seq;
    size_t len_seq;
    size_t num_seq_db;
    size_t len_seq_db;
    unsigned method;
    bool input_flag = false;
    bool uniformity = false;
    bool hash_print = false;
    bool ram = false;
    uint64_t testArray[1000] = {0};
} // namespace opt

using namespace std;

static const char shortopts[] = "k:h:j:q:l:t:g:a:iuzy:r";

enum
{
    OPT_HELP = 1,
    OPT_VERSION
};

static const struct option longopts[] = {
    {"method", required_argument, NULL, 'a'},
    {"threads", required_argument, NULL, 'j'},
    {"kmer", required_argument, NULL, 'k'},
    {"seq_num", required_argument, NULL, 'q'},
    {"seq_len", required_argument, NULL, 'l'},
    {"hash", required_argument, NULL, 'h'},
    {"db_seq_num", required_argument, NULL, 't'},
    {"db_seq_len", required_argument, NULL, 'g'},
    {"alg", required_argument, NULL, 'a'},
    {"input", no_argument, NULL, 'i'},
    {"level", no_argument, NULL, 'y'},
    {"ram", no_argument, NULL, 'r'},
    {"uniformity", no_argument, NULL, 'u'},
    {"help", no_argument, NULL, OPT_HELP},
    {"version", no_argument, NULL, OPT_VERSION},
    {NULL, 0, NULL, 0}};

static const string itm[] = {"aaHash", "CityHash", "MurmurHash", "xxHash", "Rabin-Karp"};

void check_file(const char *file_name)
{
    std::ifstream in(file_name);
    std::string first_line;
    bool good = static_cast<bool>(getline(in, first_line));
    in.close();
    if (!good)
    {
        std::cout << "Error in reading file: " << file_name << "\n";
        exit(EXIT_FAILURE);
    }
    if (first_line[0] != '>')
    {
        std::cout << "Error in file format: " << file_name << "\n";
        exit(EXIT_FAILURE);
    }
}

bool get_seq(std::ifstream &file_stream, std::string &line)
{
    bool good = false;
    std::string hline;
    line.clear();

    do
    {
        good = static_cast<bool>(getline(file_stream, hline));
        if (hline[0] == '>' && !line.empty())
            break; // !line.empty() for the first rec
        if (hline[0] != '>')
            line += hline;
    } while (good);
    if (!good && !line.empty())
        good = true;

    return good;
}

void load_seq_aahash(BloomFilter &my_filter, const string &seq)
{
    if (seq.size() < opt::kmer_len)
        return;
    uint64_t hash_val;
    my_filter.insert(seq.c_str(), hash_val);
    for (size_t i = 1; i < seq.size() - opt::kmer_len + 1; i++)
    {
        my_filter.insert(hash_val, seq[i - 1], seq[i + opt::kmer_len - 1]);
    }
}

void load_seq_mumur(BloomFilter &my_filter, const string &seq)
{
    if (seq.size() < opt::kmer_len)
        return;
    for (size_t i = 0; i < seq.size() - opt::kmer_len + 1; i++)
    {
        string kmer = seq.substr(i, opt::kmer_len);
        my_filter.insertMur(kmer.c_str());
    }
}

void load_seq_city(BloomFilter &my_filter, const string &seq)
{
    if (seq.size() < opt::kmer_len)
        return;
    for (size_t i = 0; i < seq.size() - opt::kmer_len + 1; i++)
    {
        string kmer = seq.substr(i, opt::kmer_len);
        my_filter.insertCit(kmer.c_str());
    }
}

void load_seq_xxhash(BloomFilter &my_filter, const string &seq)
{
    if (seq.size() < opt::kmer_len)
        return;
    for (size_t i = 0; i < seq.size() - opt::kmer_len + 1; i++)
    {
        string kmer = seq.substr(i, opt::kmer_len);
        my_filter.insertXxh(kmer.c_str());
    }
}

void loadBf(BloomFilter &my_filter, const char *faqFile)
{
    check_file(faqFile);
    ifstream file_stream(faqFile);
    bool good = true;

#ifdef _OPENMP
#pragma omp parallel
#endif

    for (string line; good;)
    {

#ifdef _OPENMP
#pragma omp critical(file_stream)
#endif

        good = get_seq(file_stream, line);
        if (good)
        {
            if (itm[opt::method] == "CityHash")
            {
                load_seq_city(my_filter, line);
            }
            else if (itm[opt::method] == "MurmurHash")
            {
                load_seq_mumur(my_filter, line);
            }
            else if (itm[opt::method] == "xxHash")
            {
                load_seq_xxhash(my_filter, line);
            }
            else if (itm[opt::method] == "aaHash")
            {
                load_seq_aahash(my_filter, line);
            }
        }
    }
    file_stream.close();
}

void query_seq_aahash(BloomFilter &my_filter, const string &seq, size_t &false_hit)
{
    if (seq.size() < opt::kmer_len)
        return;
    uint64_t hash_val;
    if (my_filter.contains(seq.c_str(), hash_val))
    {
#ifdef _OPENMP
#pragma omp atomic
#endif
        ++false_hit;
    }
    for (size_t i = 1; i < seq.size() - opt::kmer_len + 1; i++)
    {
        if (my_filter.contains(hash_val, seq[i - 1], seq[i + opt::kmer_len - 1]))
        {
#ifdef _OPENMP
#pragma omp atomic
#endif
            ++false_hit;
        }
    }
}

void query_seq_murmur(BloomFilter &my_filter, const string &seq, size_t &false_hit)
{
    if (seq.size() < opt::kmer_len)
        return;
    for (size_t i = 0; i < seq.size() - opt::kmer_len + 1; i++)
    {
        string kmer = seq.substr(i, opt::kmer_len);
        if (my_filter.containsMur(kmer.c_str()))
        {
#ifdef _OPENMP
#pragma omp atomic
#endif
            ++false_hit;
        }
    }
}

void query_seq_city(BloomFilter &my_filter, const string &seq, size_t &false_hit)
{
    if (seq.size() < opt::kmer_len)
        return;
    for (size_t i = 0; i < seq.size() - opt::kmer_len + 1; i++)
    {
        string kmer = seq.substr(i, opt::kmer_len);
        if (my_filter.containsCit(kmer.c_str()))
        {
#ifdef _OPENMP
#pragma omp atomic
#endif
            ++false_hit;
        }
    }
}

void query_seq_xxhash(BloomFilter &my_filter, const string &seq, size_t &false_hit)
{
    if (seq.size() < opt::kmer_len)
        return;
    for (size_t i = 0; i < seq.size() - opt::kmer_len + 1; i++)
    {
        string kmer = seq.substr(i, opt::kmer_len);
        if (my_filter.containsXxh(kmer.c_str()))
        {
#ifdef _OPENMP
#pragma omp atomic
#endif
            ++false_hit;
        }
    }
}

void query_bf(BloomFilter &my_filter, const char *faqFile)
{
    check_file(faqFile);
    ifstream file_stream(faqFile);
    size_t false_hit = 0, total_kmer = 0;
    bool good = true;
#ifdef _OPENMP
#pragma omp parallel
#endif
    for (string line; good;)
    {
#ifdef _OPENMP
#pragma omp critical(file_stream)
#endif
        good = get_seq(file_stream, line);
        if (good)
        {
            if (itm[opt::method] == "CityHash")
            {
                query_seq_city(my_filter, line, false_hit);
            }
            else if (itm[opt::method] == "MurmurHash")
            {
                query_seq_murmur(my_filter, line, false_hit);
            }
            else if (itm[opt::method] == "xxHash")
            {
                query_seq_xxhash(my_filter, line, false_hit);
            }
            else if (itm[opt::method] == "aaHash")
            {
                query_seq_aahash(my_filter, line, false_hit);
            }
#ifdef _OPENMP
#pragma omp atomic
#endif
            total_kmer += line.size() - opt::kmer_len + 1;
        }
    }
    file_stream.close();
    cout << "total_kmer=" << total_kmer << " ";
    cout << "false_hits=" << false_hit << " %" << setprecision(4) << fixed << (double)false_hit / (double)total_kmer << " ";
}

void hash_seq_aahash(const string &seq)
{

    uint64_t hash_val = btllib::aahash_base(seq.c_str(), opt::kmer_len, 1);
    for (size_t i = 1; i < seq.length() - opt::kmer_len + 1; i++)
    {
        hash_val = btllib::aahash_roll(hash_val, opt::kmer_len, seq[i - 1], seq[i - 1 + opt::kmer_len], 1);
    }
    if (hash_val)
    {
        ++opt::dummy; // dummy operation so compiler doesnt complain
    }
}

void hash_seq_out(const string &seq)
{

    uint64_t hash_val = btllib::aahash_base(seq.c_str(), opt::kmer_len, opt::level);
    std::cout << ((long double)hash_val / (long double)std::numeric_limits<uint64_t>::max()) << std::endl;
    for (size_t i = 1; i < seq.length() - opt::kmer_len + 1; i++)
    {
        hash_val = btllib::aahash_roll(hash_val, opt::kmer_len, seq[i - 1], seq[i - 1 + opt::kmer_len], opt::level);
        std::cout << ((long double)hash_val / (long double)std::numeric_limits<uint64_t>::max()) << std::endl;
    }
}

void hash_seq_rabin_karp(const string &seq)
{

    int k = (int)opt::kmer_len;
    int64_t hash_val = string_search::create_hash(seq, k);

    for (int i = 1; i < (int)seq.length() - k + 1; i++)
    {
        hash_val = string_search::recalculate_hash(seq, i - 1, i + k - 1, hash_val, k);
    }
    if (hash_val)
    {
        ++opt::dummy; // dummy operation so compiler doesnt complain
    }
}

void hash_seq_xxhash(const string &seq)
{

    uint64_t hash_val = 0;
    for (size_t i = 0; i < seq.length() - opt::kmer_len + 1; i++)
    {
        string kmer = seq.substr(i, opt::kmer_len);
        hash_val = XXH64(kmer.c_str(), opt::kmer_len, 0);
    }
    if (hash_val)
    {
        ++opt::dummy; // dummy operation so compiler doesnt complain
    }
}

void hash_seq_city(const string &seq)
{

    uint64_t hash_val = 0;
    for (size_t i = 0; i < seq.length() - opt::kmer_len + 1; i++)
    {
        string kmer = seq.substr(i, opt::kmer_len);
        hash_val = CityHash64(kmer.c_str(), opt::kmer_len);
    }
    if (hash_val)
    {
        ++opt::dummy; // dummy operation so compiler doesnt complain
    }
}

void hash_seq_murmur(const string &seq)
{

    uint64_t hash_val = 0;
    for (size_t i = 0; i < seq.length() - opt::kmer_len + 1; i++)
    {
        string kmer = seq.substr(i, opt::kmer_len);
        hash_val = MurmurHash64A(kmer.c_str(), opt::kmer_len, 0);
    }
    if (hash_val)
    {
        ++opt::dummy; // dummy operation so compiler doesnt complain
    }
}

void hash_seq_aahash_multi(const string &seq)
{

    uint64_t hash_val = btllib::aahash_base(seq.c_str(), opt::kmer_len, 1);
    btllib::nte64(hash_val, opt::kmer_len, opt::num_hash, opt::testArray);
    for (size_t i = 1; i < seq.length() - opt::kmer_len + 1; i++)
    {
        hash_val = btllib::aahash_roll(hash_val, opt::kmer_len, seq[i - 1], seq[i - 1 + opt::kmer_len], 1);
        btllib::nte64(hash_val, opt::kmer_len, opt::num_hash, opt::testArray);
    }
    if (opt::testArray[0])
        ++opt::dummy; // dummy operation so compiler doesnt complain
}

void hash_seq_xxhash_multi(const string &seq)
{

    string kmer = seq.substr(0, opt::kmer_len);
    uint64_t hash_val = XXH64(kmer.c_str(), opt::kmer_len, 0);
    opt::testArray[0] = hash_val;
    for (unsigned h = 1; h < opt::num_hash; h++)
    {
        opt::testArray[h] = XXH64(kmer.c_str(), opt::kmer_len, h);
    }
    for (size_t i = 1; i < seq.length() - opt::kmer_len + 1; i++)
    {
        kmer = seq.substr(i, opt::kmer_len);
        for (unsigned h = 0; h < opt::num_hash; h++)
        {
            opt::testArray[h] = XXH64(kmer.c_str(), opt::kmer_len, h);
        }
    }
    if (opt::testArray[0])
        ++opt::dummy; // dummy operation so compiler doesnt complain
}

void hash_seq_city_multi(const string &seq)
{

    string kmer = seq.substr(0, opt::kmer_len);
    uint64_t hash_val = CityHash64WithSeed(kmer.c_str(), opt::kmer_len, 0);
    opt::testArray[0] = hash_val;
    for (unsigned h = 1; h < opt::num_hash; h++)
    {
        opt::testArray[h] = CityHash64WithSeed(kmer.c_str(), opt::kmer_len, h);
    }

    for (size_t i = 1; i < seq.length() - opt::kmer_len + 1; i++)
    {
        kmer = seq.substr(i, opt::kmer_len);

        for (unsigned h = 0; h < opt::num_hash; h++)
        {
            opt::testArray[h] = CityHash64WithSeed(kmer.c_str(), opt::kmer_len, h);
        }
    }
    if (opt::testArray[0])
        ++opt::dummy; // dummy operation so compiler doesnt complain
}

void hash_seq_murmur_multi(const string &seq)
{

    string kmer = seq.substr(0, opt::kmer_len);
    uint64_t hash_val = MurmurHash64A(kmer.c_str(), opt::kmer_len, 0);
    opt::testArray[0] = hash_val;
    for (unsigned h = 1; h < opt::num_hash; h++)
    {
        opt::testArray[h] = MurmurHash64A(kmer.c_str(), opt::kmer_len, h);
    }

    for (size_t i = 1; i < seq.length() - opt::kmer_len + 1; i++)
    {
        kmer = seq.substr(i, opt::kmer_len);

        for (unsigned h = 0; h < opt::num_hash; h++)
        {
            opt::testArray[h] = MurmurHash64A(kmer.c_str(), opt::kmer_len, h);
        }
    }
    if (opt::testArray[0])
        ++opt::dummy; // dummy operation so compiler doesnt complain
}

void test_hash_bloom_filter(const char *db_name, const char *file_name)
{

#ifdef _OPENMP
    omp_set_num_threads(opt::threads);
#endif
    std::cout << "#threads=" << opt::threads << "\n";
    for (opt::method = 0; opt::method < 6; opt::method++)
    {
        std::cout << "method=" << itm[opt::method] << " ";
        for (unsigned k = 50; k <= opt::len_seq; k += 100)
        {
            opt::kmer_len = k;
            std::cout << "kmerl=" << opt::kmer_len << "\n";
            for (unsigned i = 1; i < 6; i += 2)
            {
                opt::num_hash = i;
                std::cout << "num_hash=" << opt::num_hash << " ";

#ifdef _OPENMP
                double sTime = omp_get_wtime();
#else
                clock_t start = clock();
#endif

                BloomFilter my_filter(opt::ibits * opt::num_seq_db * (opt::len_seq_db - opt::kmer_len + 1), opt::num_hash, opt::kmer_len);
                loadBf(my_filter, db_name);
                cout << "|popBF|=" << my_filter.getPop() << " ";

#ifdef _OPENMP
                std::cout << "load_time=" << setprecision(4) << fixed << omp_get_wtime() - sTime << "\n";
#else
                std::cout << "load_time=" << setprecision(4) << (double)(clock() - start) / CLOCKS_PER_SEC << "\n";
#endif

#ifdef _OPENMP
                sTime = omp_get_wtime();
#else
                start = clock();
#endif

                query_bf(my_filter, file_name);

#ifdef _OPENMP
                std::cout << "query_time=" << setprecision(4) << fixed << omp_get_wtime() - sTime << "\n";
#else
                std::cout << "query_time=" << setprecision(4) << (double)(clock() - start) / CLOCKS_PER_SEC << "\n";
#endif
            }
        }
        cout << "\n";
    }
}

void test_hash_time(const char *file_name)
{
    check_file(file_name);
    cout << "CPU time (sec) for hash algorithms for ";
    cout << "kmer=" << opt::kmer_len << "\n";
    cout << "num_hash=" << opt::num_hash << "\n";
    for (unsigned method = 0; method < 5; method++)
    {
        cout << itm[method];
        if (method != 4)
        {
            cout << "\t";
        }
    }
    cout << "\n";
    if (opt::num_hash > 1)
    {
        for (unsigned method = 0; method < 4; method++)
        {
            opt::dummy = 0;
            ifstream file_stream(file_name);
            string line;
            clock_t sTime = clock();
            while (get_seq(file_stream, line))
            {
                if (itm[method] == "CityHash")
                {
                    hash_seq_city_multi(line);
                }
                else if (itm[method] == "MurmurHash")
                {
                    hash_seq_murmur_multi(line);
                }
                else if (itm[method] == "aaHash")
                {
                    hash_seq_aahash_multi(line);
                }
                else if (itm[method] == "xxHash")
                {
                    hash_seq_xxhash_multi(line);
                }
            }
            cout << (double)(clock() - sTime) / CLOCKS_PER_SEC;
            if (method != 3)
            {
                cout << "\t";
            }
            file_stream.close();
        }
        cout << "\n";
    }
    else
    {
        for (unsigned method = 0; method < 5; method++)
        {
            opt::dummy = 0;
            ifstream file_stream(file_name);
            string line;
            clock_t sTime = clock();
            while (get_seq(file_stream, line))
            {
                if (itm[method] == "CityHash")
                {
                    hash_seq_city(line);
                }
                else if (itm[method] == "MurmurHash")
                {
                    hash_seq_murmur(line);
                }
                else if (itm[method] == "aaHash")
                {
                    hash_seq_aahash(line);
                }
                else if (itm[method] == "xxHash")
                {
                    hash_seq_xxhash(line);
                }
                else if (itm[method] == "Rabin-Karp")
                {
                    hash_seq_rabin_karp(line);
                }
            }
            cout << (double)(clock() - sTime) / CLOCKS_PER_SEC;
            if (method != 4)
            {
                cout << "\t";
            }
            file_stream.close();
        }
        cout << "\n"
             << std::endl;
    }
}

void test_hash_ram(const char *file_name)
{
    check_file(file_name);
    cout << "CPU time (sec) for hash algorithms for ";
    cout << "kmer=" << opt::kmer_len << "\n";
    cout << "num_hash=" << opt::num_hash << "\n";
    if (opt::num_hash > 1)
    {

        opt::dummy = 0;
        ifstream file_stream(file_name);
        string line;
        clock_t sTime = clock();
        if (itm[opt::method] == "CityHash")
        {
            std::cout << "CityHash" << std::endl;
        }
        else if (itm[opt::method] == "MurmurHash")
        {
            std::cout << "MurmurHash" << std::endl;
        }
        else if (itm[opt::method] == "aaHash")
        {
            std::cout << "aaHash" << std::endl;
        }
        else if (itm[opt::method] == "xxHash")
        {
            std::cout << "xxHash" << std::endl;
        }
        while (get_seq(file_stream, line))
        {
            if (itm[opt::method] == "CityHash")
            {
                hash_seq_city_multi(line);
            }
            else if (itm[opt::method] == "MurmurHash")
            {
                hash_seq_murmur_multi(line);
            }
            else if (itm[opt::method] == "aaHash")
            {
                hash_seq_aahash_multi(line);
            }
            else if (itm[opt::method] == "xxHash")
            {
                hash_seq_xxhash_multi(line);
            }
        }
        cout << (double)(clock() - sTime) / CLOCKS_PER_SEC << "\t";
        file_stream.close();
        cout << "\n";
    }
    else
    {

        opt::dummy = 0;
        ifstream file_stream(file_name);
        string line;
        clock_t sTime = clock();
        if (itm[opt::method] == "CityHash")
        {
            std::cout << "CityHash" << std::endl;
        }
        else if (itm[opt::method] == "MurmurHash")
        {
            std::cout << "MurmurHash" << std::endl;
        }
        else if (itm[opt::method] == "aaHash")
        {
            std::cout << "aaHash" << std::endl;
        }
        else if (itm[opt::method] == "xxHash")
        {
            std::cout << "xxHash" << std::endl;
        }
        while (get_seq(file_stream, line))
        {
            if (itm[opt::method] == "CityHash")
            {

                hash_seq_city(line);
            }
            else if (itm[opt::method] == "MurmurHash")
            {

                hash_seq_murmur(line);
            }
            else if (itm[opt::method] == "aaHash")
            {

                hash_seq_aahash(line);
            }
            else if (itm[opt::method] == "xxHash")
            {

                hash_seq_xxhash(line);
            }
        }
        cout << (double)(clock() - sTime) / CLOCKS_PER_SEC << "\t";
        file_stream.close();

        cout << "\n"
             << std::endl;
    }
}

void test_hash_print(const char *file_name)
{
    check_file(file_name);
    cout << "CPU time (sec) for hash algorithms for ";
    cout << "kmer=" << opt::kmer_len << "\n";
    cout << "num_hash=" << opt::num_hash << "\n";

    std::cout << "aaHash\n";

    ifstream file_stream(file_name);
    string line;
    while (get_seq(file_stream, line))
    {
        hash_seq_out(line);
    }
}

int main(int argc, char **argv)
{

    bool die = false;
    for (int c; (c = getopt_long(argc, argv, shortopts, longopts, NULL)) != -1;)
    {
        std::istringstream arg(optarg != NULL ? optarg : "");
        switch (c)
        {
        case '?':
            die = true;
            break;
        case 'a':
            arg >> opt::method;
            break;
        case 'j':
            arg >> opt::threads;
            break;
        case 'q':
            arg >> opt::num_seq;
            break;
        case 'l':
            arg >> opt::len_seq;
            break;
        case 't':
            arg >> opt::num_seq_db;
            break;
        case 'g':
            arg >> opt::len_seq_db;
            break;
        case 'h':
            arg >> opt::num_hash;
            break;
        case 'k':
            arg >> opt::kmer_len;
            break;
        case 'i':
            opt::input_flag = true;
            break;
        case 'u':
            opt::uniformity = true;
            break;
        case 'z':
            opt::hash_print = true;
            break;
        case 'y':
            arg >> opt::level;
            break;
        case 'r':
            opt::ram = true;
            break;
        case OPT_HELP:
            std::cout << USAGE_MESSAGE;
            exit(EXIT_SUCCESS);
        case OPT_VERSION:
            std::cout << VERSION_MESSAGE;
            exit(EXIT_SUCCESS);
        }
        if (optarg != NULL && !arg.eof())
        {
            std::cout << PROGRAM ": invalid option: `-"
                      << (char)c << optarg << "'\n";
            exit(EXIT_FAILURE);
        }
    }
    if (argc - optind != 1 && argc - optind != 2)
    {
        std::cout << argc - optind << std::endl;
        std::cout << PROGRAM ": missing arguments\n";
        die = true;
    }

    if (die)
    {
        std::cout << "Try `" << PROGRAM
                  << " --help' for more information.\n";
        exit(EXIT_FAILURE);
    }

    const char *file_name(argv[argc - 1]);
    std::cout << "read name: " << argv[argc - 1] << std::endl;

    if (opt::ram)
    {
        if (!opt::input_flag)
        {
            // simulate seqs
            std::cout << "generating reads" << std::endl;
            make_seq(opt::num_seq, opt::len_seq, "seqs.fa");
            test_hash_ram("seqs.fa");
            exit(EXIT_SUCCESS);
        }
        else
        {
            // use existing seqs
            std::cout << "using seqs.fa" << std::endl;
            std::cout << "reads=" << file_name << "\n";
            test_hash_ram(file_name);
            exit(EXIT_SUCCESS);
        }
    }

    if (opt::hash_print)
    {
        if (opt::input_flag)
        {
            std::cout << "using seqs.fa" << std::endl;
            test_hash_print("seqs.fa");
            exit(EXIT_SUCCESS);
        }
        else
        {
            // simulate reads
            std::cout << "generating reads" << std::endl;
            make_seq(opt::num_seq, opt::len_seq, "seqs.fa");
            test_hash_print("seqs.fa");
            exit(EXIT_SUCCESS);
        }
    }

    if (opt::uniformity) // test uniformity
    {
        std::cout << "num_seq=" << opt::num_seq << "\n";         // number of reads
        std::cout << "len_seq=" << opt::len_seq << "\n";         // length of reads
        std::cout << "num_seq_db=" << opt::num_seq_db << "\n";   // number of genes
        std::cout << "len_seq_db=" << opt::len_seq_db << "\n\n"; // length of genes

        if (!opt::input_flag)
        {
            std::cout << "generating DB" << std::endl;
            make_db(opt::num_seq_db, opt::len_seq_db, opt::num_seq, opt::len_seq, "db.fa", "db_seq.fa");
            std::cout << "finished generating DB" << std::endl;
            std::cout << "generating seqs" << std::endl;
            make_seq(opt::num_seq, opt::len_seq, "seqs.fa");
            std::cout << "finished generating seqs" << std::endl;
            test_hash_bloom_filter("db.fa", "seqs.fa");
        }
        else
        {
            const char *db_name(argv[argc - 2]);
            std::cout << "Filling in Bloom filter with: " << argv[argc - 2] << std::endl;
            test_hash_bloom_filter(db_name, file_name);
        }
    }
    else
    {
        if (!opt::input_flag)
        {
            // simulate reads
            std::cout << "generating reads" << std::endl;
            make_seq(opt::num_seq, opt::len_seq, "seqs.fa");
            test_hash_time("seqs.fa");
        }
        else
        {
            // use existing reads
            std::cout << "reads=" << file_name << "\n";
            test_hash_time(file_name);
        }
    }

    return 0;
}
