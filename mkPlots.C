void mkPlots(const char * filename="pol.root")
{
  TFile * infile = new TFile(filename,"READ");
  TTree * pol = (TTree*) infile->Get("pol");

  Int_t fill;
  Float_t b_pol,b_pol_e,y_pol,y_pol_e;
  pol->SetBranchAddress("fill",&fill);
  pol->SetBranchAddress("b_pol",&b_pol);
  pol->SetBranchAddress("b_pol_e",&b_pol_e);
  pol->SetBranchAddress("y_pol",&y_pol);
  pol->SetBranchAddress("y_pol_e",&y_pol_e);

  Int_t ENT_tmp = pol->GetEntries("b_pol!=0 && y_pol!=0");
  const Int_t ENT = ENT_tmp;

  Float_t fill_arr[ENT];
  Float_t fill_e_arr[ENT];
  Float_t b_pol_arr[ENT];
  Float_t b_pol_e_arr[ENT];
  Float_t y_pol_arr[ENT];
  Float_t y_pol_e_arr[ENT];

  for(Int_t i=0; i<ENT; i++) fill_e_arr[i]=0;

  Int_t iter=0;

  for(Int_t i=0; i<pol->GetEntries(); i++)
  {
    pol->GetEntry(i);
    if(b_pol>0 && y_pol>0)
    {
      fill_arr[iter] = (Float_t) fill;
      b_pol_arr[iter] = b_pol;
      b_pol_e_arr[iter] = b_pol_e;
      y_pol_arr[iter] = y_pol;
      y_pol_e_arr[iter] = y_pol_e;
      iter++;
    };
  };

  TGraphErrors * b_graph = new TGraphErrors(iter,fill_arr,b_pol_arr,fill_e_arr,b_pol_e_arr);
  TGraphErrors * y_graph = new TGraphErrors(iter,fill_arr,y_pol_arr,fill_e_arr,y_pol_e_arr);

  b_graph->SetTitle("blue polarisation vs. fill");
  y_graph->SetTitle("yellow polarisation vs. fill");
  b_graph->SetMarkerStyle(kFullCircle);
  y_graph->SetMarkerStyle(kFullCircle);
  b_graph->SetMarkerColor(kBlue);
  y_graph->SetMarkerColor(kOrange);

  Int_t fill_min = pol->GetMinimum("fill");
  Int_t fill_max = pol->GetMaximum("fill");
  //fill_min=17217;
  //fill_max=17601;
  b_graph->Fit("pol0","","",fill_min,fill_max);
  y_graph->Fit("pol0","","",fill_min,fill_max);

  TCanvas * cc = new TCanvas("cc","cc",1200,600);
  gStyle->SetOptFit(1);
  cc->Divide(1,2);
  for(Int_t j=1; j<=2; j++) cc->GetPad(j)->SetGrid(1,1);
  cc->cd(1); b_graph->Draw("ape");
  cc->cd(2); y_graph->Draw("ape");
}

