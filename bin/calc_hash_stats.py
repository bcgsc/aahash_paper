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

    # Maximum value in the input file is 1000000
    #bins = [0] * 1000000/args.bin + 1
    # read input and put values into bins of size args.bin
    # make list of 1000 elements
    bins = [0] * 1000
    # variable largest value in python
    # sys.maxsize
    hash_values = []
    with open(args.input, 'r') as f:
        lines = f.readlines()
        for line in lines:
            bin_idx = math.floor(float(line)*int(args.bin))
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

    # make an array of 1000 values all of which are 1000
    bins_expected = [1000] * 1000

    # run a ks test using the values in bins against a sample with only 1000 values
    # from a normal distribution with the same mean and standard deviation
    # as the values in bins
    # make a list of 1000 values with only 1000

    print('KS test: {}'.format(stats.kstest(hash_values, "uniform")))
    print(bins)


if __name__ == '__main__':
    main()
