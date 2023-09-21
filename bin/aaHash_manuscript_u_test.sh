echo "##############################################"
echo "uniformity simulated"
echo "##############################################"
./aaTest -j 48 -q 1000000 -l 250 -g 250 -t 1000000 -m 3 -a 5 -h 5 -u ./
echo "##############################################"
echo "uniformity real"
echo "##############################################"
./aaTest -j 48 -q 1000000 -l 250 -g 250 -t 1000000 -m 3 -a 5 -h 5 -u -i genes.fa uniprot-reviewed_yes+AND+proteome_up000005640.singleLine.fasta
