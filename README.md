steps to manipulate polarimetry csv file into something readable

NOTE: as of now, `update_table` executes everything below, including `mkTree.C`

1. copy csv data from polarimetry group; execute `update_table` to run the "old method" (see below)
  - old method: `http://www.phy.bnl.gov/cnipol/` --> fill results --> 
    table format = csv, save to `polarimetry.csv`; then put zeroes in the blank fields and get 
    rid of the "+-" symbols
  - new (more correct method): `https://wiki.bnl.gov/rhicspin/Results` --> Run * fill by fill results
    - this page won't be updated til after the run

2. run `mkTree.C` to build `pol.root`, which is a tree containing the data from the csv file

3. run `mkPlots.C` to draw some polarimetry plots
