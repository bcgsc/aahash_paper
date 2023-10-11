import scipy.stats as stats


def perform_paired_ttest(pair1, pair2, pair3, pair4, pair5, pair6):
    # Collect all the values for the two groups
    group1 = [pair1[0], pair2[0], pair3[0], pair4[0], pair5[0], pair6[0]]
    group2 = [pair1[1], pair2[1], pair3[1], pair4[1], pair5[1], pair6[1]]

    # Perform paired t-test
    t_stat, p_value = stats.ttest_rel(group1, group2, alternative='two-sided')

    return t_stat, p_value


def main():

    # (recorded FPR, theoretical FPR)

    hash_1_fpr = [(11.7, 11.8), (11.9, 11.8), (12.5, 11.8),
                  (11.8, 11.8), (11.8, 11.8), (11.8, 11.8)]

    hash_2_fpr = [(3.1, 3.1), (3.1, 3.1), (3.3, 3.1),
                  (3.1, 3.1), (3.1, 3.1), (3.1, 3.1)]

    hash_3_fpr = [(2.2, 2.2), (2.2, 2.2), (2.3, 2.2),
                  (2.2, 2.2), (2.2, 2.2), (2.2, 2.2)]

    num_hashes = ["1", "3", "5"]
    for idx, pairs in enumerate([hash_1_fpr, hash_2_fpr, hash_3_fpr], 1):
        t_stat, p_value = perform_paired_ttest(*pairs)

        print(
            f"Results for using FPR values from {num_hashes[idx-1]} hash functions:")
        print(f"t-statistic: {t_stat}")
        print(f"p-value: {p_value}\n")
        print('-' * 80)


if __name__ == '__main__':
    main()
