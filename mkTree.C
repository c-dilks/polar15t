void mkTree(const char * datfile="polarimetry.dat")
{
  TFile * outfile = new TFile("pol.root","RECREATE");
  TTree * pol_in = new TTree("pol_in","pol_in");
  pol_in->ReadFile(datfile,"fill/I:energy/F:time/D:b_pol/F:b_pol_e/F:b_p0/F:b_p0_e/F:b_p1/F:b_p1_e/F:y_pol/F:y_pol_e/F:y_p0/F:y_p0_e/F:y_p1/F:y_p1_e/F");
  /*
    fill    = fill
    energy  = beam energy
    time    = start time
    b_pol   = blue polarisation
    b_pol_e = blue polarisation error
    b_p0    = blue p0
    b_p0_e  = blue p0 error
    b_p1    = blue slope
    b_p1_e  = blue slope error
    y_pol   = yellow polarisation
    y_pol_e = yellow polarisation error
    y_p0    = yellow p0
    y_p0_e  = yellow p0 error
    y_p1    = yellow slope
    y_p1_e  = yellow slope error
  */

  // divide blue and yellow beam polarisations and their 
  // uncertainties by 100
  //
  Int_t fill;
  Float_t energy;
  Double_t time;
  Float_t b_pol;
  Float_t b_pol_e;
  Float_t b_p0;
  Float_t b_p0_e;
  Float_t b_p1;
  Float_t b_p1_e;
  Float_t y_pol;
  Float_t y_pol_e;
  Float_t y_p0;
  Float_t y_p0_e;
  Float_t y_p1;
  Float_t y_p1_e;

  pol_in->SetBranchAddress("fill",&fill);
  pol_in->SetBranchAddress("energy",&energy);
  pol_in->SetBranchAddress("time",&time);
  pol_in->SetBranchAddress("b_pol",&b_pol);
  pol_in->SetBranchAddress("b_pol_e",&b_pol_e);
  pol_in->SetBranchAddress("b_p0",&b_p0);
  pol_in->SetBranchAddress("b_p0_e",&b_p0_e);
  pol_in->SetBranchAddress("b_p1",&b_p1);
  pol_in->SetBranchAddress("b_p1_e",&b_p1_e);
  pol_in->SetBranchAddress("y_pol",&y_pol);
  pol_in->SetBranchAddress("y_pol_e",&y_pol_e);
  pol_in->SetBranchAddress("y_p0",&y_p0);
  pol_in->SetBranchAddress("y_p0_e",&y_p0_e);
  pol_in->SetBranchAddress("y_p1",&y_p1);
  pol_in->SetBranchAddress("y_p1_e",&y_p1_e);

  TTree * pol = new TTree("pol","pol");

  pol->Branch("fill",&fill,"fill/I");
  pol->Branch("energy",&energy,"energy/F");
  pol->Branch("time",&time,"time/D");
  pol->Branch("b_pol",&b_pol,"b_pol/F");
  pol->Branch("b_pol_e",&b_pol_e,"b_pol_e/F");
  pol->Branch("b_p0",&b_p0,"b_p0/F");
  pol->Branch("b_p0_e",&b_p0_e,"b_p0_e/F");
  pol->Branch("b_p1",&b_p1,"b_p1/F");
  pol->Branch("b_p1_e",&b_p1_e,"b_p1_e/F");
  pol->Branch("y_pol",&y_pol,"y_pol/F");
  pol->Branch("y_pol_e",&y_pol_e,"y_pol_e/F");
  pol->Branch("y_p0",&y_p0,"y_p0/F");
  pol->Branch("y_p0_e",&y_p0_e,"y_p0_e/F");
  pol->Branch("y_p1",&y_p1,"y_p1/F");
  pol->Branch("y_p1_e",&y_p1_e,"y_p1_e/F");

  for(Int_t i=0; i<pol_in->GetEntries(); i++)
  {
    pol_in->GetEntry(i);
    b_pol /= 100.0;
    b_pol_e /= 100.0;
    y_pol /= 100.0;
    y_pol_e /= 100.0;
    pol->Fill();
  };
    
  pol->Write("pol");
};
