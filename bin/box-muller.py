import argparse
import math
import scipy.stats as stats
import matplotlib.pyplot as plt
import numpy as np


def plot_qq(data, ax, label_name, show_x_label=True, show_y_label=True):
    res = stats.probplot(data, plot=ax)

    ax.set_title('', weight='bold', fontsize=14)

    if show_x_label:
        ax.set_xlabel('Theoretical Quantiles', weight='bold', fontsize=12)
    else:
        ax.set_xlabel('')

    if show_y_label:
        ax.set_ylabel(
            f'Sample Quantiles {label_name}', weight='bold', fontsize=12)
    else:
        ax.set_ylabel('')


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('input_files', nargs='+', help='input files')
    args = parser.parse_args()

    input_files = args.input_files

    if len(input_files) != 3:
        raise ValueError("You must provide exactly 3 input files.")

    titles = ['Level 1 aaHash', 'Level 2 aaHash',
              'Level 3 aaHash'] 
    fig, axs = plt.subplots(2, 3, figsize=(18, 8))

    for idx, file in enumerate(input_files):
        with open(file, 'r') as f:
            hash_values = [float(line.strip()) for line in f.readlines()]

        z0 = []
        z1 = []
        i = 0

        while i < len(hash_values):
            z0.append(
                math.sqrt(-2.0 * math.log(hash_values[i])) * math.cos(2.0 * math.pi * hash_values[i+1]))
            z1.append(
                math.sqrt(-2.0 * math.log(hash_values[i])) * math.sin(2.0 * math.pi * hash_values[i+1]))
            i += 2

        D_z0, p_z0 = stats.kstest(z0, 'norm')
        D_z1, p_z1 = stats.kstest(z1, 'norm')
        print(f"[{titles[idx]}] KS Test for z0: D = {D_z0}, p-value = {p_z0}")
        print(f"[{titles[idx]}] KS Test for z1: D = {D_z1}, p-value = {p_z1}")

        show_x_label = False
        show_y_label = True if idx == 0 else False

        plot_qq(z0, axs[0, idx], "Z₀", show_x_label, show_y_label)
        plot_qq(z1, axs[1, idx], "Z₁", True, show_y_label)


        axs[0, idx].set_title(titles[idx], weight='bold', fontsize=14)
        z0 = np.array(z0[:1000])
        z1 = np.array(z1[:1000])

        corr_coefficient, _ = stats.pearsonr(z0, z1)
        print(
            f"[{titles[idx]}] Pearson correlation coefficient between z0 and z1: {corr_coefficient}")

        se_r = math.sqrt((1 - corr_coefficient**2) / (1000 - 2))
        print(f"[{titles[idx]}] Standard error of Pearson correlation coefficient: {se_r:.3f}")

        W_z0, p_z0 = stats.shapiro(z0[:5000])
        W_z1, p_z1 = stats.shapiro(z1[:5000])
        print(f"[{titles[idx]}] Shapiro-Wilk W for z0: {W_z0}, p-value: {p_z0}")
        print(f"[{titles[idx]}] Shapiro-Wilk W for z1: {W_z1}, p-value: {p_z1}")
        print('-' * 80)

    plt.tight_layout()
    plt.savefig('qq_plots.png', dpi=300)
    plt.show()


if __name__ == '__main__':
    main()
