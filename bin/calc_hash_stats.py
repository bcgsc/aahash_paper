import argparse
import os
import sys
import math
import scipy.stats as stats


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('input', help='input file')
    parser.add_argument('bin', help='size of bin')
    args = parser.parse_args()

    # make list of 1000 elements
    bins = [0] * 1000
    hash_values = []
    with open(args.input, 'r') as f:
        lines = f.readlines()
        for line in lines:
            bin_idx = math.floor(float(line)*1000000/int(args.bin))
            if bin_idx == 1000:
                bin_idx -= 1
            bins[bin_idx] += 1
            hash_values.append(float(line))

    # calculate the average and standard deviation of bins
    avg = sum(bins)/len(bins)
    std = (sum((x-avg)**2 for x in bins)/len(bins))**0.5

    # print the results
    print('Average: {}'.format(avg))
    print('Standard deviation: {}'.format(std))


    # run a ks test using the values in bins against a uniform dist

    print('KS test: {}'.format(stats.kstest(hash_values, "uniform")))


if __name__ == '__main__':
    main()
