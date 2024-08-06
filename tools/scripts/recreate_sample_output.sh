SOURCE_DIRECTORY="/home/neo/Code/WAGASCI/WagasciMC" # insert your source directory
BIN_DIRECTORY="/home/neo/Desktop/WagasciMC/bin" # insert you bin directory where B2MC executable is located
$BIN_DIRECTORY/B2MC \
  --output-file-path "$SOURCE_DIRECTORY/data/sample_output_files/13a_wagasci_upstream_numu_h2o.root" \
  --input-file-path "$SOURCE_DIRECTORY/data/sample_neut_files/13a_nd7_posi250_numu_h2o_1.root" \
  --neutrino-interaction-settings WagasciUpstream \
  --water-settings WgupInWgdownIn \
  --neutrino-flavor-settings MuonNeutrino \
  --magnetic-field \
  --debug-level warning
echo "Sample output file created!"
exit 0